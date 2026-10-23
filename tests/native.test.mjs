import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { createHash } from 'node:crypto';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { parseGmb, readGmb } from '../dist/gmc-loader.js';
import { decodeNativeText, parsePos, parseAct, NativePoseTimeline, NativeCombatController, NATIVE_WEAPONS } from '../dist/native-combat.js';

const root = new URL('../dist/assets/original/', import.meta.url);
const manifest = JSON.parse(await readFile(new URL('manifest.json', root), 'utf8'));
const weaponManifest = JSON.parse(await readFile(new URL('weapon-models/manifest.json', root), 'utf8'));
const poseBytes = await readFile(new URL('../dist/assets/native/combat/P0.POS', import.meta.url));
const actBytes = await readFile(new URL('../dist/assets/native/combat/character.act', import.meta.url));
const poses = parsePos(decodeNativeText(poseBytes)), actions = parseAct(decodeNativeText(actBytes));
const resources = JSON.parse(await readFile(new URL('characters/meteor-res-data.json', root), 'utf8'));
const native = { poses, actions,
  moveRecords: new Map(resources.allRecords.filter(r => r.type === 3).map(r => [r.id, r])),
  weaponRecords: new Map(resources.allRecords.filter(r => r.type === 1).map(r => [r.model.toLowerCase(), r])) };
const v = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
const arrayBuffer = bytes => bytes.buffer.slice(bytes.byteOffset, bytes.byteOffset + bytes.byteLength);

function deferred() {
  let resolve;
  const promise = new Promise(done => { resolve = done; });
  return { promise, resolve };
}

async function nativeMap(id) {
  const entry = manifest.maps.find(m => m.id === id);
  const [bytes, desText, metadataText] = await Promise.all([
    readFile(new URL(entry.model, root)), readFile(new URL(entry.description, root), 'utf8'),
    readFile(new URL(entry.metadata, root), 'utf8')
  ]);
  const metadata = JSON.parse(metadataText);
  const model = parseGmb(arrayBuffer(bytes), { scale: .08, groundZ: 0, texturePath: '', desText, unlit: true });
  model.updateMatrixWorld(true);
  const material = new THREE.MeshBasicMaterial({ side: THREE.DoubleSide });
  const colliders = model.children.filter(m => m.userData.collidable).map(mesh => {
    const collider = new THREE.Mesh(mesh.geometry, material);
    collider.name = mesh.name;
    collider.matrixWorld.copy(mesh.matrixWorld);
    collider.matrixAutoUpdate = false;
    return collider;
  });
  const des = metadata.files.find(f => f.path.endsWith('.des')).parsed;
  const user = des.objects.find(o => o.name === 'D_user01');
  const game = Object.create(MeteorGame.prototype);
  Object.assign(game, { currentMap: { colliders, metadata, bounds: new THREE.Box3().setFromObject(model) },
    raycaster: new THREE.Raycaster(), hostPhysics: { radius: .4, step: .55, gravity: 34 } });
  return { game, model, metadata, des, user, bytes };
}

test('the manifest exposes all actual maps and explicitly blocks the nonfinite map', () => {
  assert.equal(manifest.maps.length, 22);
  assert.equal(manifest.maps.find(m => m.id === 'sn01').name, '钟乳洞');
  assert.equal(manifest.maps.find(m => m.id === 'sn04').name, '炽雪城');
  assert.equal(manifest.maps.find(m => m.id === 'sn06').name, '四方阵');
  assert.equal(manifest.maps.find(m => m.id === 'sn10').name, '炼铁狱');
  const invalid = manifest.maps.find(m => m.id === 'sn22');
  assert.equal(invalid.available, false);
  assert.match(invalid.unavailableReason, /nonfinite/);
  assert.equal(manifest.maps.some(m => m.name === '蝴蝶谷'), false);
});

test('every imported model marked available has finite native geometry and matching source bytes', async () => {
  for (const entry of manifest.maps.filter(m => m.available)) {
    const bytes = await readFile(new URL(entry.model, root));
    const asset = manifest.assets.find(a => a.url === entry.model);
    assert.equal(createHash('sha256').update(bytes).digest('hex'), asset.source.sha256, entry.id);
    const parsed = readGmb(arrayBuffer(bytes));
    assert.equal(parsed.vertexCount, entry.stats.vertexCount, entry.id);
    for (const object of parsed.objects) {
      for (const vertex of object.vertices) assert.ok(vertex.position.every(Number.isFinite), `${entry.id}/${object.name}`);
    }
  }
});

test('POS and ACT are parsed from the preserved native files', () => {
  const declared = [...decodeNativeText(poseBytes).matchAll(/^\s*Pose\s+\d+/gm)].length;
  assert.equal(poses.size, declared);
  assert.ok(actions.groups.length > 0);
  for (const profile of Object.values(NATIVE_WEAPONS)) {
    for (const id of profile.basic) {
      const pose = poses.get(id);
      assert.ok(pose?.valid);
      assert.ok(pose.attacks.length > 0);
      assert.ok(pose.attacks.every(a => a.start >= pose.start && a.end <= pose.end));
    }
  }
});

test('native animation phase speeds remain deterministic across frame partitions', () => {
  const pose = poses.get(NATIVE_WEAPONS.sword.basic[0]);
  const whole = new NativePoseTimeline(pose), partitioned = new NativePoseTimeline(pose);
  whole.advance(.63);
  for (let i = 0; i < 63; i++) partitioned.advance(.01);
  assert.ok(Math.abs(whole.frame - partitioned.frame) < 1e-6);
  assert.equal(whole.finished, partitioned.finished);
  assert.equal(whole.pose.source, pose.source);
});

test('a POS attack window is inactive before its original start frame', () => {
  const pose = poses.get(NATIVE_WEAPONS.sword.basic[0]), attack = pose.attacks[0];
  const timeline = new NativePoseTimeline(pose);
  timeline.frame = attack.start - .1;
  assert.equal(timeline.advance(0).attacks.length, 0);
  const active = timeline.advance(.01);
  assert.ok(active.attacks.some(a => a.start === attack.start && a.end === attack.end));
  assert.equal(active.attacks[0].targetvalue, attack.targetvalue);
  timeline.frame = attack.end + 1.1;
  assert.equal(timeline.advance(0).attacks.length, 0);
});

test('active native combo transitions obey the original ACT link graph', () => {
  const [first, second] = NATIVE_WEAPONS.sword.basic;
  const controller = new NativeCombatController(native);
  assert.equal(controller.play(first), true);
  assert.equal(actions.canLink(first, second), true);
  const forbidden = [...poses.values()].find(p => p.valid && p.id !== first && !actions.canLink(first, p.id));
  assert.ok(forbidden);
  assert.equal(controller.play(forbidden.id), false);
  assert.equal(controller.play(second), true);
  assert.ok(controller.timeline.pose.id === second || controller.queued === second);
});

test('unverified native damage coefficients are reported without fabricating HP loss', () => {
  const game = Object.create(MeteorGame.prototype), pose = poses.get(NATIVE_WEAPONS.sword.basic[0]);
  const hitBone = new THREE.Object3D(); hitBone.position.set(0, 1.35, 0);
  const attacker = { hero: true, id: 0, root: new THREE.Group(), weapon: 'sword',
    attackHits: new Set(), character: { getAttachment: () => hitBone } };
  const target = { id: 1, root: new THREE.Group(), hp: 1500, contacts: 0, dead: false, guard: false };
  const events = [];
  Object.assign(game, { running: true, enemies: [target], contactHits: 0, damageResolver: null, combatData: native,
    _emit: (...event) => events.push(event), _soundDefinition() {}, _flash() {}, _hud() {} });
  const state = { poseId: pose.id, attacks: pose.attacks.map((a, index) => ({ ...a, index })) };
  game._resolveContacts(attacker, state);
  assert.equal(target.hp, 1500);
  assert.equal(game.contactHits, 1);
  assert.equal(events[0][4].damagePending, true);
  assert.equal(events[0][4].raw.targetValue, pose.attacks[0].targetvalue);
  assert.equal(events[0][4].raw.moveRecord, native.moveRecords.get(pose.id));
  assert.equal(events[0][4].raw.weaponRecord, native.weaponRecords.get('w0_0'));
  game._resolveContacts(attacker, state);
  assert.equal(game.contactHits, 1, 'one original attack window must not report the same target twice');
});

test('the original sword, blade and spear remain their verified RES model IDs', () => {
  const byType = Object.fromEntries(manifest.weapons.map(w => [w.type, w]));
  assert.equal(byType.sword.id, 'w0_0');
  assert.equal(byType.blade.id, 'w5_0');
  assert.equal(byType.spear.id, 'w7_0');
  for (const weapon of Object.values(byType)) {
    assert.equal(weapon.resourceEvidence.modelId, weapon.id);
    assert.ok(Number.isInteger(weapon.resourceEvidence.modelOffset));
    assert.equal(weapon.resourceEvidence.source.path, 'Meteor.res');
  }
});

test('native sound effects use the original PonEF-to-WAV references', async () => {
  const definition = manifest.sounds.effectDefinitions.find(e => e.id.toLowerCase() === 'w00bl090');
  assert.ok(definition);
  assert.deepEqual(definition.soundReferences.map(s => s.toLowerCase()), ['w00hit01.wav']);
  const wave = manifest.sounds.effects.find(e => e.id === 'w00hit01');
  const bytes = await readFile(new URL(wave.url, root));
  assert.equal(bytes.subarray(0, 4).toString('ascii'), 'RIFF');
  assert.equal(bytes.subarray(8, 12).toString('ascii'), 'WAVE');
});

test('original spawn points in Four Squares and Stalactite Cave have actual collision surfaces', async () => {
  for (const id of ['sn06', 'sn01']) {
    const { game, user } = await nativeMap(id);
    const [x, y, z] = user.position;
    const ground = game._ground(x * .08, -y * .08, z * .08 + 3);
    assert.ok(ground, `${id}/${user.name} has no floor`);
    assert.ok(Number.isFinite(ground.point.y));
    assert.ok(ground.point.y <= z * .08 + 3);
  }
});

test('an explicit native texture URL loads with an empty fallback path and retains a separate alpha mask', async () => {
  const entry = manifest.maps.find(m => m.id === 'sn01');
  const texture = entry.textures.find(t => t.alphaMask);
  assert.ok(texture);
  const bytes = await readFile(new URL(entry.model, root));
  const originalLoad = THREE.TextureLoader.prototype.load, requested = [];
  const colorURL = new URL(texture.url, root).href, alphaURL = new URL(texture.alphaMask, root).href;
  THREE.TextureLoader.prototype.load = function (url, done) {
    requested.push(url);
    const result = new THREE.Texture(); result.userData.url = url;
    done(result); return result;
  };
  try {
    const model = parseGmb(arrayBuffer(bytes), { texturePath: '',
      textureMap: { [texture.reference.toLowerCase()]: colorURL },
      textureAlphaMap: { [texture.reference.toLowerCase()]: alphaURL } });
    await model.userData.texturesReady;
    assert.ok(requested.includes(colorURL));
    assert.ok(requested.includes(alphaURL));
    const materials = model.children.flatMap(m => Array.isArray(m.material) ? m.material : [m.material]);
    const material = materials.find(m => m.map?.userData.url === colorURL);
    assert.ok(material);
    assert.equal(material.alphaMap?.userData.url, alphaURL);
  } finally {
    THREE.TextureLoader.prototype.load = originalLoad;
  }
});

test('hidden collision platforms below the original Forge spawns remain solid', async () => {
  const { game, model, user, des } = await nativeMap('sn10');
  const box = des.objects.find(o => o.name === 'Box20');
  assert.equal(box.properties.visible, '0');
  assert.notEqual(box.properties.blockplayer, 'no');
  const hidden = model.children.find(m => m.name === 'Box20');
  assert.ok(hidden, 'visible=0 must retain geometry for collision');
  assert.equal(hidden.visible, false, 'collision geometry must stay invisible');
  const [x, y, z] = user.position;
  const ground = game._ground(x * .08, -y * .08, z * .08 + 3);
  assert.ok(ground);
  assert.equal(ground.object.name, 'Box20');
  assert.ok(ground.point.y > 30, 'the original spawn platform is above the bottom of the furnace');
});

test('rapid character selection keeps the latest requested native character', async () => {
  const game = Object.create(MeteorGame.prototype), requests = new Map([[1, deferred()], [2, deferred()]]);
  const disposed = [];
  const actor = id => ({ root: new THREE.Group(), character: { dispose: () => disposed.push(id) } });
  Object.assign(game, { ready: Promise.resolve(), characterId: 0, characterRequest: 0, hero: actor(0),
    scene: new THREE.Scene(), weapon: 'sword', currentMap: { spawns: [{}] },
    _createFighter: id => requests.get(id).promise, _placeFighter() {}, _equip: async () => {}, _hud() {} });
  const first = game.setCharacter(1);
  await Promise.resolve(); // Let the first native asset request begin before superseding it.
  const latest = game.setCharacter(2);
  await Promise.resolve();
  requests.get(2).resolve(actor(2)); await latest;
  requests.get(1).resolve(actor(1)); await first;
  assert.equal(game.characterId, 2);
  assert.ok(disposed.includes(1), 'a stale loaded character must be disposed');
});

test('out-of-order native weapon loads attach only the latest selected model', async () => {
  const game = Object.create(MeteorGame.prototype), sword = deferred(), blade = deferred(), hand = new THREE.Group();
  const f = { weapon: 'sword', equipRequest: 0, combat: { setWeapon() {}, play() {} }, character: { getAttachment: () => hand } };
  Object.assign(game, { weaponCache: new Map(), combatData: native,
    weaponItems: new Map(weaponManifest.items.map(item => [Number(item.itemId), item])),
    _readWeapon: model => model === 'w0_0' ? sword.promise : blade.promise, _emit() {} });
  const first = game._equip(f, 'sword'), middle = game._equip(f, 'blade'), latest = game._equip(f, 'sword');
  sword.resolve(new THREE.Group()); await Promise.all([first, latest]);
  blade.resolve(new THREE.Group()); await middle;
  assert.equal(f.weapon, 'sword');
  assert.equal(hand.children.length, 1);
  assert.equal(f.weaponModel, hand.children[0]);
});

test('native map cache eviction protects the current scene and pending loads', () => {
  const game = Object.create(MeteorGame.prototype), disposed = [];
  const entries = ['old1', 'current', 'pending1', 'old2', 'pending2'];
  Object.assign(game, { currentMap: { id: 'current' },
    mapCache: new Map(entries.map(id => [id, Promise.resolve({ id })])),
    mapData: new Map(['old1', 'current', 'old2'].map(id => [id, { id }])),
    pendingMaps: new Set(['pending1', 'pending2']), _disposeMap: data => disposed.push(data.id) });
  game._trimMapCache();
  assert.ok(game.mapCache.has('current'));
  assert.ok(game.mapCache.has('pending1'));
  assert.ok(game.mapCache.has('pending2'));
  assert.deepEqual(disposed.sort(), ['old1', 'old2']);
  game.pendingMaps.clear();
  game.mapData.set('pending1', { id: 'pending1' });
  game.mapData.set('pending2', { id: 'pending2' });
  game._trimMapCache();
  assert.ok(game.mapCache.has('current'));
  assert.ok(game.mapCache.size <= 2);
  assert.ok(game.mapData.size <= 2);
});

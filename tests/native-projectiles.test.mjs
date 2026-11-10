import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { NativeProjectileSystem, NATIVE_DART_PROFILE, sweepActorCapsule } from '../dist/native-projectiles.js';
import { parseGmc } from '../dist/gmc-loader.js';
import { decodeNativeText, parsePos, parseAct, NativeCombatController, createNativeDamageResolver } from '../dist/native-combat.js';

const assetRoot = new URL('../dist/assets/', import.meta.url);
const poses = parsePos(decodeNativeText(await readFile(new URL('native/combat/P0.POS', assetRoot))));
const actions = parseAct(decodeNativeText(await readFile(new URL('native/combat/character.act', assetRoot))));
const resources = JSON.parse(await readFile(new URL('original/characters/meteor-res-data.json', assetRoot), 'utf8'));
const data = { poses, actions, moveRecords: new Map(resources.allRecords.filter(r => r.type === 3).map(r => [r.id, r])), weaponRecords: new Map(resources.allRecords.filter(r => r.type === 1).map(r => [r.model.toLowerCase(), r])) };
const sourceDart = parseGmc(await readFile(new URL('original/weapon-models/models/w3_0/w3_0.gmc', assetRoot), 'utf8'), { scale: 1, groundZ: 0, texturePath: '', unlit: true });
const v = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
let actorId = 0;
function actor(z = 0, weapon = 'dart', hero = false) {
  const root = new THREE.Group(), hand = new THREE.Group(); hand.position.set(.15, 1.45, .1); root.add(hand); root.position.z = z;
  const model = sourceDart.clone(true); model.rotation.x = Math.PI / 2; hand.add(model);
  const f = { id: ++actorId, root, hero, weapon, weaponId: weapon === 'dart' ? 1 : 7, hp: 1000, maxHp: 1000, rage: 0, guard: false,
    team: hero ? 1 : 2, teamMask: hero ? 1 : 2, nativeStats: {}, activeItems: [], velocity: v(), attackHits: new Set(), dead: false, contacts: 0,
    weaponModel: model, weaponRecord: data.weaponRecords.get(weapon === 'dart' ? 'w3_0' : 'w7_0'),
    character: { getAttachment: () => hand, setPoseFrame() {}, dispose() { root.removeFromParent(); } },
    combat: new NativeCombatController(data, { weapon }), heldPose: null };
  f.combat.play(weapon === 'dart' ? 1 : 7, { force: true }); root.updateMatrixWorld(true); return f;
}
function fixture({ targetZ = 10, colliders = [] } = {}) {
  const game = Object.create(MeteorGame.prototype), hero = actor(0, 'dart', true), target = actor(targetZ, 'spear'), events = [];
  Object.assign(game, { scene: new THREE.Scene(), hero, enemies: [target], mode: 'story', running: true, paused: false,
    hostPhysics: { radius: .4 }, currentMap: { colliders }, combatData: data, damageResolver: createNativeDamageResolver(data),
    keys: new Set(), directionBuffer: [], kills: 0, deaths: 0, contactHits: 0, totalDamage: 0, matchElapsed: 0, weapon: 'dart',
    _hud() {}, _emit(text, type, amount, point, extra) { events.push({ text, type, amount, point, ...extra }); },
    _soundDefinition() {}, onEvent: e => events.push(e), onEnd: e => events.push({ type: 'end', ...e }),
    _collisionCandidates: () => colliders });
  game.scene.add(hero.root, target.root); game._initializeProjectiles(); return { game, hero, target, events };
}
function release(game, hero, poseId = 200, dt = .25) {
  hero.combat.play(poseId, { force: true }); const state = hero.combat.update(dt); game._launchNativeProjectiles(hero, state); return state;
}
function wall(z) {
  const mesh = new THREE.Mesh(new THREE.PlaneGeometry(20, 20), new THREE.MeshBasicMaterial({ side: THREE.DoubleSide })); mesh.position.set(0, 2, z); mesh.updateMatrixWorld(true); return mesh;
}

test('original POS ground and air windows release one real W3_0 model, at native scale, once each', () => {
  for (const poseId of [200, 202]) {
    const { game, hero } = fixture(); hero.combat.play(poseId, { force: true });
    let state = hero.combat.update(.19); game._launchNativeProjectiles(hero, state); assert.equal(game.projectiles.size, 0);
    state = hero.combat.update(.04); game._launchNativeProjectiles(hero, state); game._launchNativeProjectiles(hero, state);
    assert.equal(game.projectiles.size, 1); const shot = game.projectiles.active[0];
    assert.equal(shot.context.state.poseId, poseId); assert.equal(shot.context.model, 'w3_0');
    assert.equal(shot.visual.children[0].geometry, sourceDart.children[0].geometry);
    assert.deepEqual(shot.visual.scale.toArray(), [.08, .08, .08]); assert.equal(shot.visual.rotation.x, 0);
    const size = new THREE.Box3().setFromObject(shot.visual).getSize(v()); assert.ok(size.length() < 1 && size.length() > .1);
    game.projectiles.dispose();
  }
});

test('actual dart movement hits once using original 75/65 RES and recovered damage 34', () => {
  const { game, hero, target, events } = fixture(); release(game, hero); const shot = game.projectiles.active[0];
  assert.equal(target.hp, 1000); game.projectiles.update(.25); assert.equal(target.hp, 966); assert.equal(shot.removalReason, 'actor');
  game.projectiles.update(2); assert.equal(target.hp, 966); assert.equal(game.contactHits, 1); assert.equal(game.totalDamage, 34);
  assert.equal(events.filter(e => e.type === 'hit').length, 1); assert.equal(target.rage, 4);
});

test('continuous swept contact does not tunnel through a capsule at a low frame rate', () => {
  const target = actor(5, 'spear'); assert.ok(sweepActorCapsule(v(0, 1.3, 0), v(0, 1.3, 100), target) < .06);
  let hits = 0; const system = new NativeProjectileSystem({ getTargets: () => [target], onActorHit: () => hits++, profile: { ...NATIVE_DART_PROFILE, speed: 1000 } });
  system.spawn({ owner: actor(), position: v(0, 1.3, 0), direction: v(0, 0, 1) }); system.update(.1);
  assert.equal(hits, 1); assert.equal(system.size, 0);
});

test('relative motion sweep catches a target crossing the projectile between frames', () => {
  const target = actor(5, 'spear'); target.root.position.x = 3; target.previousPosition = v(-3, 0, 5);
  let hits = 0; const system = new NativeProjectileSystem({ getTargets: () => [target], onActorHit: () => hits++ });
  system.spawn({ owner: actor(), position: v(0, 1.3, 0), direction: v(0, 0, 1) }); system.update(.2); assert.equal(hits, 1);
});

test('an original map triangle blocks a target behind it and the closest actor wins before a wall', () => {
  const first = fixture({ colliders: [wall(5)] }); release(first.game, first.hero); const shot = first.game.projectiles.active[0]; first.game.projectiles.update(.3);
  assert.equal(first.target.hp, 1000); assert.equal(shot.removalReason, 'world'); assert.equal(first.game.projectiles.size, 0);
  const second = fixture({ targetZ: 3, colliders: [wall(5)] }); release(second.game, second.hero); second.game.projectiles.update(.3); assert.equal(second.target.hp, 966);
});

test('a hand beyond a wall cannot spawn a projectile through that wall', () => {
  let world = 0; const system = new NativeProjectileSystem({ getColliders: () => [wall(.5)], onWorldHit: () => world++ });
  const shot = system.spawn({ owner: actor(), sourcePosition: v(0, 1.3, 0), position: v(0, 1.3, 1), direction: v(0, 0, 1) });
  assert.equal(shot, null); assert.equal(system.size, 0); assert.equal(world, 1);
});

test('a guarded dart is consumed once without HP loss; lethal impact emits one death', () => {
  const guarded = fixture(); guarded.target.guard = true; release(guarded.game, guarded.hero); guarded.game.projectiles.update(.3);
  assert.equal(guarded.target.hp, 1000); assert.equal(guarded.game.contactHits, 1); assert.equal(guarded.game.projectiles.size, 0);
  const lethal = fixture(); lethal.target.hp = 20; release(lethal.game, lethal.hero); lethal.game.projectiles.update(.3); lethal.game.projectiles.update(.3);
  assert.equal(lethal.target.hp, 0); assert.equal(lethal.target.dead, true); assert.equal(lethal.target.respawn, Infinity); assert.equal(lethal.game.kills, 1); assert.equal(lethal.game.totalDamage, 20);
});

test('a weapon change after release preserves original launch weapon, pose, team and item snapshot', () => {
  const { game, hero, target } = fixture(); release(game, hero); hero.weapon = 'dagger'; hero.weaponRecord = data.weaponRecords.get('w1_0'); hero.teamMask = 2; hero.nativeStats[3] = 9999;
  game.projectiles.update(.3); assert.equal(target.hp, 966);
});

test('self is excluded and friendly bodies use the original 0.2 team factor instead of being skipped', () => {
  const { game, hero, target } = fixture(); target.team = target.teamMask = 1; release(game, hero); game.projectiles.update(.3);
  assert.equal(hero.hp, 1000); assert.equal(target.hp, 994); assert.equal(game.contactHits, 1);
});

test('pause freezes motion and age, resume continues, expiry and match end remove every shot', () => {
  const { game, hero, target } = fixture(); release(game, hero); const shot = game.projectiles.active[0], position = shot.position.clone();
  game.pause(true); game.projectiles.update(2); assert.equal(shot.age, 0); assert.deepEqual(shot.position.toArray(), position.toArray()); assert.equal(target.hp, 1000);
  game.pause(false); game.projectiles.update(.3); assert.equal(target.hp, 966);
  release(game, hero); game._finish(false); assert.equal(game.projectiles.size, 0); game.projectiles.update(1); assert.equal(target.hp, 966);
  const system = new NativeProjectileSystem(); system.spawn({ owner: hero, position: v(), direction: v(0, 0, 1) }); system.update(10); assert.equal(system.size, 0); system.dispose();
});

test('map changes and menu exit clear shots before scene replacement', async () => {
  const { game, hero, target } = fixture(); release(game, hero);
  const next = { id: 'sn01', model: new THREE.Group(), bounds: new THREE.Box3(v(-20, -1, -20), v(20, 10, 20)), spawns: [{ position: v() }], metadata: { level: { integers: {} } } };
  Object.assign(game, { mapRequest: 0, manifest: { maps: [{ id: 'sn01', name: '钟乳洞' }] }, mapCache: new Map([['sn01', Promise.resolve(next)]]), mapData: new Map([['sn01', next]]), pendingMaps: new Set(), camera: new THREE.PerspectiveCamera(), renderer: { shadowMap: {} }, _loadStatus() {}, _trimMapCache() {} });
  game.scene.background = new THREE.Color(); await game._loadMap('cave'); assert.equal(game.projectiles.size, 0); assert.equal(target.hp, 1000);
  assert.equal(game.renderer.toneMapping, THREE.NoToneMapping); assert.equal(game.renderer.shadowMap.enabled, false);
  release(game, hero); Object.assign(game, { ready: Promise.resolve(), map: 'cave', sessionRequest: 0, _ground: () => null, _disposeNameplate() {} });
  await game.menu('cave'); assert.equal(game.projectiles.size, 0); assert.equal(game.running, false);
});

test('actual SKC/BNC/AMB, d_wpnR, W3_0 and original cave triangles launch and damage a real model at source waypoints', async () => {
  const previousFetch = globalThis.fetch, previousLoad = THREE.TextureLoader.prototype.load;
  const dist = new URL('../dist/', import.meta.url);
  globalThis.fetch = async input => { try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); } catch { return new Response('', { status: 404 }); } };
  THREE.TextureLoader.prototype.load = function (url, done) { const texture = new THREE.Texture(); done(texture); return texture; };
  let game;
  try {
    const manifest = JSON.parse(await readFile(new URL('assets/original/manifest.json', dist), 'utf8'));
    const wm = JSON.parse(await readFile(new URL('assets/original/weapon-models/manifest.json', dist), 'utf8'));
    game = Object.create(MeteorGame.prototype);
    Object.assign(game, { manifest, combatData: data, weaponManifest: wm,
      weaponItems: new Map(wm.items.map(item => [item.itemId, item])), weaponModels: new Map(wm.models.map(model => [model.modelId, model])), weaponCache: new Map(),
      scene: new THREE.Scene(), camera: new THREE.PerspectiveCamera(), raycaster: new THREE.Raycaster(), collisionMaterial: new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }),
      hostPhysics: { speed: 8, gravity: 34, jumpVelocity: 12, radius: .4, step: .55 }, weapon: 'dart', actorSerial: 0, enemies: [], running: true, paused: false, mode: 'story',
      cameraAngle: 0, keys: new Set(), directionBuffer: [], elapsed: 0, difficulty: 'normal', kills: 0, deaths: 0, totalDamage: 0, contactHits: 0,
      _nameplate() {}, _soundDefinition() {}, _hud() {}, _emit() {}, onEvent() {} });
    game.damageResolver = createNativeDamageResolver(data);
    game.currentMap = await game._readMap('sn01'); game.scene.add(game.currentMap.model);
    game.hero = await game._createFighter(0, '孟星魂', true); game.scene.add(game.hero.root);
    game._placeFighter(game.hero, { position: game.currentMap.points.find(point => point.id === 67).position }); await game._equip(game.hero, 1);
    const target = await game._createFighter(8, '铁枪哨兵﹒甲'); game.scene.add(target.root); game.enemies.push(target);
    game._placeFighter(target, { position: game.currentMap.points.find(point => point.id === 53).position }); await game._equip(target, 7); target.maxHp = target.hp = 1000;
    game.locked = target; game._initializeProjectiles(); const released = [];
    const originalSpawn = game.projectiles.spawn.bind(game.projectiles); game.projectiles.spawn = config => { const shot = originalSpawn(config); released.push({ shot, origin: config.position.clone() }); return shot; };
    for (let attack = 0; attack < 3; attack++) {
      game.action('attack');
      for (let frame = 0; frame < 60; frame++) { game.elapsed += 1 / 60; game._updateFighter(game.hero, 1 / 60); game.projectiles.update(1 / 60); }
    }
    assert.equal(released.length, 3); assert.ok(released.every(record => record.shot && record.origin.toArray().every(Number.isFinite)));
    assert.ok(released[0].origin.y > game.hero.root.position.y + 1.5 && released[0].origin.y < game.hero.root.position.y + 3);
    assert.equal(target.hp, 898); assert.equal(game.totalDamage, 102); assert.equal(game.contactHits, 3);
    assert.ok(released.every(record => record.shot.removalReason === 'actor'));
    // Reproduce the actual browser W12 bridge position: a locked actor behind
    // the bridge is occluded by original mesh T, not a reason to weaken walls.
    game._placeFighter(game.hero, { position: game.currentMap.points.find(point => point.id === 9).position });
    game.locked = null; game.cameraAngle = Math.PI / 2; game.keys.add('forward');
    for (let frame = 0; frame < 720; frame++) { game.elapsed += 1 / 60; game._updateFighter(game.hero, 1 / 60); }
    game.keys.clear(); game.locked = target; const blockedBy = [], priorWorldHit = game.projectiles.onWorldHit;
    game.projectiles.onWorldHit = (shot, hit) => { blockedBy.push(hit.object.name); priorWorldHit(shot, hit); };
    game.action('attack');
    for (let frame = 0; frame < 60; frame++) { game.elapsed += 1 / 60; game._updateFighter(game.hero, 1 / 60); game.projectiles.update(1 / 60); }
    assert.ok(game.hero.root.position.y > 10); assert.ok(blockedBy.includes('T'));
    assert.equal(target.hp, 898); assert.equal(game.contactHits, 3); assert.equal(released.at(-1).shot.removalReason, 'world');

  } finally {
    game?.projectiles?.dispose(); for (const actor of game ? [game.hero, ...game.enemies] : []) actor?.character.dispose();
    if (game?.currentMap) game._disposeMap(game.currentMap);
    globalThis.fetch = previousFetch; THREE.TextureLoader.prototype.load = previousLoad;
  }
});


test('original leader W7_1 defense zero receives 49 instead of the basic spear defense-15 result', () => {
  const { game, hero, target } = fixture(); target.weaponId = 16; target.weaponRecord = data.weaponRecords.get('w7_1');
  release(game, hero); game.projectiles.update(.3); assert.equal(target.hp, 951); assert.equal(target.rage, 6);
});

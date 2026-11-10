import test, { after } from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { NativeMissionHost } from '../dist/native-mission-host.js';

// Actual DES/cmodel/FMC/POS/PST. Omit texture decoding/rendering only; no scene
// attributes, transform matrices, source callbacks or collider lookup are mocked.
const dist = new URL('../dist/', import.meta.url), original = new URL('assets/original/', dist);
const priorFetch = globalThis.fetch, priorTextureLoad = THREE.TextureLoader.prototype.load;
globalThis.fetch = async input => {
  try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); }
  catch { return new Response('', { status: 404 }); }
};
THREE.TextureLoader.prototype.load = function(url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
const manifest = JSON.parse(await readFile(new URL('manifest.json', original), 'utf8')), games = [];
const v = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
async function map(id = 'sn01') {
  const game = Object.create(MeteorGame.prototype);
  Object.assign(game, { manifest, collisionMaterial: new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }), raycaster: new THREE.Raycaster(), onEvent() {}, _soundDefinition() {} });
  game.currentMap = await game._readMap(id); games.push(game); return game;
}
function snapshot(item) {
  return { attributes: { ...item.attributes }, pose: item.pose, frame: item.frame, time: item.time, playing: item.playing, loop: item.loop, state: item.state,
    visible: item.root.visible, position: item.root.position.toArray(), rotation: item.root.quaternion.toArray(), scale: item.root.scale.toArray(),
    bounds: [item.bounds.min.toArray(), item.bounds.max.toArray()], colliders: item.colliders.map(record => record.collider.matrixWorld.toArray()) };
}
async function sourceScene(game) {
  const host = await NativeMissionHost.create(game); host.call(host.sceneVm, 'Scene_OnLoad'); host.call(host.sceneVm, 'Scene_OnInit'); return host;
}
after(() => { for (const game of games) { game.missionHost?.dispose(); game._disposeMap(game.currentMap); } globalThis.fetch = priorFetch; THREE.TextureLoader.prototype.load = priorTextureLoad; });

test('a source cave destruction resets to the exact freshly loaded scene state and supports original Scene_OnInit again', async () => {
  const game = await map(), props = game.currentMap.props, stone = game.getSceneObject('D_St22'), meatbun = game.getSceneObject('D_itSt22');
  const initialStone = snapshot(stone), initialItem = snapshot(meatbun), originalAttributes = stone.attributes;
  const host = game.missionHost = await sourceScene(game);
  assert.equal(meatbun.attributes.active, 0);
  host.sceneItemAttack('D_St22', 0, 500);
  for (let frame = 0; frame < 600; frame++) { props.update(1 / 60); host.sceneItemIdle('D_St22'); }
  assert.equal(stone.attributes.active, 0); assert.equal(stone.attributes.collision, 0); assert.equal(meatbun.attributes.active, 1);
  assert.equal(props.reset(), props.instances.size);
  assert.deepEqual(snapshot(stone), initialStone); assert.deepEqual(snapshot(meatbun), initialItem);
  assert.equal(stone.attributes, originalAttributes, 'PST records keep the same live attribute object');
  assert.equal(host.sceneItem('D_St22').attributes, originalAttributes);
  host.call(host.sceneVm, 'Scene_OnInit');
  assert.equal(host.sceneVm.getGlobal('g_iStoneHP')[21], 500);
  assert.equal(stone.attributes.active, 1); assert.equal(stone.attributes.collision, 1);
  assert.equal(meatbun.attributes.active, 0); assert.equal(meatbun.attributes.interactive, 0);
  host.sceneItemAttack('D_St22', 0, 500); assert.equal(meatbun.attributes.active, 1);
  assert.equal(host.diagnostics.length, 0);
});

test('reset preserves source instance, shared GPU resources and grid collider references without allocating another map', async () => {
  const game = await map(), props = game.currentMap.props, stone = game.getSceneObject('D_St22');
  const instances = props.instances, root = stone.root, model = stone.model, attrs = stone.attributes, colliderRecords = stone.colliders;
  const colliders = colliderRecords.map(record => record.collider), geometries = new Set(), materials = new Set(), meshResources = [];
  model.traverse(object => { if (object.isMesh) meshResources.push({ object, geometry: object.geometry, material: object.material }); if (object.geometry) geometries.add(object.geometry); for (const material of Array.isArray(object.material) ? object.material : object.material ? [object.material] : []) materials.add(material); });
  let disposed = 0; const onDispose = () => disposed++;
  for (const resource of [...geometries, ...materials]) resource.addEventListener('dispose', onDispose);
  const initial = snapshot(stone);
  try {
    stone.attributes = { active: 0, collision: 0, interactive: 0, customSessionFlag: 1 };
    stone.root.position.add(v(20, 30, 40)); stone.root.scale.setScalar(.5); stone.root.quaternion.setFromAxisAngle(v(0, 1, 0), 1);
    stone.playPose(1, { loop: true }); props.update(.4); stone.root.visible = false;
    props.reset();
    assert.equal(props.instances, instances); assert.equal(game.getSceneObject('D_St22'), stone);
    assert.equal(stone.root, root); assert.equal(stone.model, model); assert.equal(stone.attributes, attrs);
    assert.equal(stone.colliders, colliderRecords); assert.ok(stone.colliders.every((record, i) => record.collider === colliders[i]));
    assert.deepEqual(snapshot(stone), initial); assert.equal('customSessionFlag' in attrs, false); assert.equal(disposed, 0);
    const nearby = props.getCollidersNear(root.position.x, root.position.z, 4);
    assert.ok(colliders.length > 0 && colliders.every(collider => nearby.includes(collider)), 'same source grid sees the restored original collider objects');
    const currentMeshes = []; model.traverse(object => { if (object.isMesh) currentMeshes.push(object); });
    assert.deepEqual(currentMeshes, meshResources.map(record => record.object));
    assert.ok(meshResources.every(record => record.object.geometry === record.geometry && record.object.material === record.material), 'source mesh geometry/material references survive reset');
  } finally { for (const resource of [...geometries, ...materials]) resource.removeEventListener('dispose', onDispose); }
});

test('reset is idempotent and removes session playback from static original props', async () => {
  const game = await map(), props = game.currentMap.props, meatbun = game.getSceneObject('D_itSt22');
  assert.equal(meatbun.asset.animation, null);
  const initial = snapshot(meatbun);
  meatbun.pose = 99; meatbun.state = 1; meatbun.frame = 55; meatbun.time = 19; meatbun.playing = true; meatbun.loop = true;
  meatbun.attributes.active = 0; meatbun.attributes.interactive = 0; meatbun.root.visible = false;
  props.reset(); assert.deepEqual(snapshot(meatbun), initial);
  const all = [...props.instances.values()].map(snapshot);
  props.reset(); assert.deepEqual([...props.instances.values()].map(snapshot), all);
  props.update(.5); assert.deepEqual(snapshot(meatbun), initial, 'a stale invalid animation cannot continue after a fresh-state reset');
});

test('a real falling platform restores its original FMC frame and collider matrices while retaining fresh-load animation semantics', async () => {
  const game = await map('sn09'), props = game.currentMap.props, platform = game.getSceneObject('D_sn09f01');
  assert.ok(platform?.asset.animation && platform.colliders.length);
  const initial = snapshot(platform), collider = platform.colliders[0].collider;
  assert.equal(platform.playPose(1, { loop: true }), true); props.update(2);
  assert.notDeepEqual(collider.matrixWorld.toArray(), initial.colliders[0], 'the source falling-floor animation must really move its collision mesh');
  props.reset(); assert.deepEqual(snapshot(platform), initial); assert.equal(platform.colliders[0].collider, collider);
  const freshGame = await map('sn09'), fresh = freshGame.getSceneObject('D_sn09f01');
  props.update(.3); freshGame.currentMap.props.update(.3);
  assert.deepEqual(snapshot(platform), snapshot(fresh), 'reset resumes exactly what a fresh original scene would do, rather than preserving the previous loop');
});

test('production story exit and same-map training start restore cached props, then a new story reinitializes its source state', async () => {
  const game = await map(), cachedMap = game.currentMap, props = cachedMap.props;
  const actor = (id = 0, hero = true) => ({ id, hero, root: new THREE.Group(), character: { dispose() {} }, weapon: 'dagger', hp: 1500, maxHp: 1500,
    velocity: v(), attackHits: new Set(), combat: { play() {}, setWeapon() {} } });
  Object.assign(game, { scene: new THREE.Scene(), cameraTarget: v(), hostPhysics: { radius: .4, step: .55 }, map: 'sn01', mode: 'story',
    hero: actor(), enemies: [], keys: new Set(), ready: Promise.resolve(), sessionRequest: 0, characterId: 0, disposed: false,
    _hud() {}, _tickCamera() {}, _unlockAudio() {}, _emit() {},
    _equip: async (fighter, weapon) => { fighter.weapon = typeof weapon === 'string' ? weapon : 'dagger'; }, _createFighter: async id => actor(id, false) });
  game.scene.add(cachedMap.model);
  const stone = game.getSceneObject('D_St22'), meatbun = game.getSceneObject('D_itSt22'), freshStone = snapshot(stone), freshItem = snapshot(meatbun);
  const host = game.missionHost = await sourceScene(game);
  host.sceneItemAttack('D_St22', 0, 500);
  for (let frame = 0; frame < 300; frame++) { props.update(1 / 60); host.sceneItemIdle('D_St22'); }
  assert.equal(stone.attributes.active, 0); assert.equal(meatbun.attributes.active, 1);
  await game.menu('sn01');
  assert.equal(host.disposed, true); assert.equal(game.missionHost, null);
  assert.deepEqual(snapshot(stone), freshStone); assert.deepEqual(snapshot(meatbun), freshItem);
  assert.equal(game.currentMap, cachedMap, 'menu should restore the cached instance, not load duplicate geometry');
  // A new training round must reset independently of whether menu was used.
  stone.playPose(1, { loop: true }); stone.setActive(false); stone.setCollision(false); props.update(.5);
  await game.start({ map: 'sn01', mode: 'training', weapon: 'sword', character: 0 });
  assert.equal(game.running, true); assert.equal(game.mode, 'training');
  assert.deepEqual(snapshot(stone), freshStone); assert.deepEqual(snapshot(meatbun), freshItem); assert.equal(game.currentMap, cachedMap);
  await game.start({ map: 'sn01', mode: 'story', character: 0 });
  assert.equal(game.missionHost.sceneVm.getGlobal('g_iStoneHP')[21], 500);
  assert.equal(stone.attributes.active, 1); assert.equal(stone.attributes.collision, 1);
  assert.equal(meatbun.attributes.active, 0); assert.equal(meatbun.attributes.interactive, 0);
  assert.equal(game.missionHost.diagnostics.length, 0);
});

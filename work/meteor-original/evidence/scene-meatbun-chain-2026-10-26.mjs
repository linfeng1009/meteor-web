// Independent CPU probe of one actual original cave stone-to-meatbun chain.
// Shot origins and the pickup actor location are synthetic probes, not ordinary
// player walking/aiming or a browser acceptance run. Original files stay read-only.
import { readFile } from 'node:fs/promises';
import assert from 'node:assert/strict';
import * as THREE from '../../../dist/vendor/three.module.js';
import { MeteorGame } from '../../../dist/engine.js';
import { NativeMissionHost } from '../../../dist/native-mission-host.js';
import { loadNativeCombat, createNativeSceneDamageResolver } from '../../../dist/native-combat.js';
import { NativeItemSystem } from '../../../dist/native-items.js';

const original = new URL('../../../dist/assets/original/', import.meta.url), dist = new URL('../../../dist/', import.meta.url);
globalThis.fetch = async input => {
  try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); }
  catch { return new Response('', { status: 404 }); }
};
THREE.TextureLoader.prototype.load = function (url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
const game = Object.create(MeteorGame.prototype), events = [];
Object.assign(game, {
  manifest: JSON.parse(await readFile(new URL('manifest.json', original), 'utf8')),
  scene: new THREE.Scene(), collisionMaterial: new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }),
  raycaster: new THREE.Raycaster(), hostPhysics: { radius: .4 }, hero: null, enemies: [],
  onEvent: event => events.push(event), _soundDefinition() {}
});
game.currentMap = await game._readMap('sn01'); game.scene.add(game.currentMap.model);
const combat = await loadNativeCombat(); game.sceneDamageResolver = createNativeSceneDamageResolver(combat);
game.missionHost = await NativeMissionHost.create(game);
game.missionHost.call(game.missionHost.sceneVm, 'Scene_OnLoad');
game.missionHost.call(game.missionHost.sceneVm, 'Scene_OnInit');
game._initializeProjectiles();
const stone = game.getSceneObject('D_St22'), meatbun = game.getSceneObject('D_itSt22');
assert.equal(meatbun.source.properties.model, '"item01"'); assert.equal(meatbun.attributes.active, 0);
const bounds = new THREE.Box3().setFromObject(stone.root), center = bounds.getCenter(new THREE.Vector3());
let probe;
for (const y of [1.35, 2.35, 5, center.y]) {
  for (let i = 0; i < 32; i++) {
    const angle = i * Math.PI / 16, target = new THREE.Vector3(center.x, y, center.z);
    const from = target.clone().add(new THREE.Vector3(Math.cos(angle) * 6, 0, Math.sin(angle) * 6));
    const hit = game.projectiles.worldContact(from, target, .12);
    if (hit?.object.userData.nativeSceneInstance === stone) { probe = { from, target, hit }; break; }
  }
  if (probe) break;
}
assert.ok(probe, 'an actual native scene geometric probe must hit D_St22');
const hitNames = [], oldWorldHit = game.projectiles.onWorldHit;
game.projectiles.onWorldHit = (shot, hit) => { hitNames.push(hit.object.userData.nativeSceneInstance?.name || hit.object.name); oldWorldHit(shot, hit); };
const attacker = { id: 999, scriptId: 0, hero: true, weapon: 'dart', nativeStats: {} };
const stoneHp = [game.missionHost.sceneVm.getGlobal('g_iStoneHP')[21]];
for (let i = 0; i < 11; i++) {
  game.projectiles.spawn({ owner: attacker, position: probe.from, direction: probe.target.clone().sub(probe.from).normalize(),
    context: { attacker, state: { poseId: 200 }, attack: { index: 0 } } });
  for (let f = 0; f < 120 && game.projectiles.size; f++) game.projectiles.update(1 / 60);
  stoneHp.push(game.missionHost.sceneVm.getGlobal('g_iStoneHP')[21]);
}
assert.equal(stoneHp.at(-1), -39); assert.equal(stone.attributes.collision, 0);
assert.equal(meatbun.attributes.active, 1); assert.equal(meatbun.attributes.interactive, 1);
assert.equal(hitNames.length, 11); assert.ok(hitNames.every(name => name === 'D_St22'));
const stateAfterImpact = { pose: stone.pose, state: stone.state, playing: stone.playing, frame: stone.frame, active: stone.attributes.active };
for (let f = 0; f < 600; f++) { game.currentMap.props.update(1 / 60); game.missionHost.sceneItemIdle('D_St22'); }
assert.equal(stone.attributes.active, 0); assert.equal(stone.state, 3);
const afterAnimation = { stonePose: stone.pose, stoneState: stone.state, stoneActive: stone.attributes.active, stoneCollision: stone.attributes.collision,
  itemModel: meatbun.source.properties.model, itemActive: meatbun.attributes.active, itemInteractive: meatbun.attributes.interactive };

const pickupEvents = [];
game.items = new NativeItemSystem({ itemRecords: combat.itemRecords, getInstances: () => game.currentMap.props.instances.values(),
  canReach: (actor, item) => game._canReachItem(actor, item), onPickup: result => pickupEvents.push(result) });
const actor = { id: 1000, hero: true, hp: 1000, maxHp: 1500, dead: false, root: new THREE.Group() };
let floorProbe;
// Place a valid living probe actor on actual collision ground near this item.
// A navigable path from the original player spawn is deliberately not asserted.
for (const radius of [0, .5, 1, 1.5]) {
  for (let i = 0; i < 16; i++) {
    const x = meatbun.root.position.x + Math.cos(i * Math.PI / 8) * radius, z = meatbun.root.position.z + Math.sin(i * Math.PI / 8) * radius;
    const floor = game._ground(x, z, meatbun.root.position.y + 3); if (!floor) continue;
    actor.root.position.set(x, floor.point.y + .015, z);
    const candidate = game.items.peek(actor);
    if (candidate?.objectName === 'D_itSt22') { floorProbe = { position: actor.root.position.clone(), ground: floor.object.name, distance: candidate.distance }; break; }
  }
  if (floorProbe) break;
}
assert.ok(floorProbe, 'an alive on-ground actor within the documented reach range can reach the actual meatbun');
const pickup = game.items.tryPickup(actor); assert.equal(pickup.ok, true); assert.equal(pickup.itemId, 1); assert.equal(pickup.healed, 300);
assert.equal(actor.hp, 1300); assert.equal(pickupEvents.length, 1); assert.equal(meatbun.attributes.active, 0);
const duplicate = game.items.tryPickup(actor); assert.equal(duplicate.ok, false); assert.equal(actor.hp, 1300); assert.equal(pickupEvents.length, 1);
game.missionHost.call(game.missionHost.sceneVm, 'Scene_OnInit'); game.items.reset();
assert.equal(stone.pose, 0); assert.equal(stone.attributes.active, 1); assert.equal(stone.attributes.collision, 1);
assert.equal(meatbun.attributes.active, 0); assert.equal(meatbun.attributes.interactive, 0);
assert.equal(game.missionHost.sceneVm.getGlobal('g_iStoneHP')[21], 500); assert.equal(game.items.peek(actor), null);
const result = {
  date: '2026-10-26', kind: 'single-chain-cpu-geometric-probe', passed: true,
  source: 'actual sn01 DES/cmodel/FMC/POS and scene PST; actual continuous projectile sweep, native scene damage resolver, NativeItemSystem and engine item reach ray',
  chain: ['D_St22 actual triangle hit', '11 original pose200/RES attack damage calls', 'original StoneOnAttack and break pose1', 'actual D_itSt22 Item01 activates', 'native meatbun effect HP+300 once', 'original Scene_OnInit reset'],
  shotProbe: { from: probe.from.toArray(), target: probe.target.toArray(), firstNativeHit: probe.hit.object.name }, hitNames, stoneHp, stateAfterImpact, afterAnimation,
  pickupProbe: { actorPosition: floorProbe.position.toArray(), groundObject: floorProbe.ground, distance: floorProbe.distance, placedByProbe: true },
  pickup: { ok: pickup.ok, name: pickup.name, itemId: pickup.itemId, objectName: pickup.objectName, hpBefore: pickup.hpBefore, hpAfter: pickup.hpAfter, healed: pickup.healed,
    effectValue: pickup.effectValue, recordOffset: pickup.recordOffset, valueOffset: pickup.valueOffset, events: pickupEvents.length },
  duplicate: { ok: duplicate.ok, reason: duplicate.reason, hpAfter: actor.hp },
  reinitialized: { stoneHp: game.missionHost.sceneVm.getGlobal('g_iStoneHP')[21], stonePose: stone.pose, stoneActive: stone.attributes.active, stoneCollision: stone.attributes.collision,
    itemActive: meatbun.attributes.active, itemInteractive: meatbun.attributes.interactive, nearbyItem: game.items.peek(actor) },
  notAsserted: ['actual character animation/hand release or player aiming', 'ordinary walking from the original player spawn', 'browser rendering or F/touch interaction', 'exact EXE flight or pickup trigger constants', 'full mission clear', 'original EXE execution'],
  diagnostics: game.missionHost.diagnostics
};
console.log(JSON.stringify(result, null, 2));
game.items.dispose(); game.projectiles.dispose(); game.missionHost.dispose(); game._disposeMap(game.currentMap);

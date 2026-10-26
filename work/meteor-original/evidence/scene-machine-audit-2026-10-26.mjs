// Read-only source/native asset audit. Does not execute the original EXE or
// modify runtime modules. Shot origins are synthetic geometric probes.
import { readFile } from 'node:fs/promises';
import assert from 'node:assert/strict';
import * as THREE from '../../../dist/vendor/three.module.js';
import { MeteorGame } from '../../../dist/engine.js';
import { NativeMissionHost } from '../../../dist/native-mission-host.js';
import { loadNativeCombat, createNativeSceneDamageResolver } from '../../../dist/native-combat.js';

const original = new URL('../../../dist/assets/original/', import.meta.url);
const dist = new URL('../../../dist/', import.meta.url);
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
game.sceneDamageResolver = createNativeSceneDamageResolver(await loadNativeCombat());
game.missionHost = await NativeMissionHost.create(game);
game.missionHost.call(game.missionHost.sceneVm, 'Scene_OnLoad');
game.missionHost.call(game.missionHost.sceneVm, 'Scene_OnInit');
game._initializeProjectiles();
const stone = game.getSceneObject('D_St20'), item = game.getSceneObject('D_itSt20');
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
assert.ok(probe, 'a 6m horizontal native scene geometry probe must be able to hit D_St20');
const hitNames = [], oldWorldHit = game.projectiles.onWorldHit;
game.projectiles.onWorldHit = (shot, hit) => { hitNames.push(hit.object.userData.nativeSceneInstance?.name || hit.object.name); oldWorldHit(shot, hit); };
const attacker = { id: 999, scriptId: 0, hero: true, weapon: 'dart', nativeStats: {} };
for (let i = 0; i < 11; i++) {
  game.projectiles.spawn({ owner: attacker, position: probe.from, direction: probe.target.clone().sub(probe.from).normalize(),
    context: { attacker, state: { poseId: 200 }, attack: { index: 0 } } });
  for (let f = 0; f < 120 && game.projectiles.size; f++) game.projectiles.update(1 / 60);
}
const hpAfterHits = game.missionHost.sceneVm.getGlobal('g_iStoneHP')[19];
assert.equal(hpAfterHits, -39); assert.equal(stone.attributes.collision, 0);
assert.equal(item.attributes.active, 1); assert.equal(item.attributes.interactive, 1);
assert.equal(hitNames.length, 11); assert.ok(hitNames.every(name => name === 'D_St20'));
const stateAfterImpact = { pose: stone.pose, state: stone.state, playing: stone.playing, frame: stone.frame, active: stone.attributes.active };
for (let f = 0; f < 600; f++) {
  game.currentMap.props.update(1 / 60); game.missionHost.sceneItemIdle('D_St20');
}
assert.equal(stone.attributes.active, 0); assert.equal(stone.state, 3);
const final = { stonePose: stone.pose, stoneState: stone.state, stoneActive: stone.attributes.active, stoneCollision: stone.attributes.collision, itemActive: item.attributes.active, itemInteractive: item.attributes.interactive };
game.missionHost.call(game.missionHost.sceneVm, 'Scene_OnInit');
assert.equal(stone.pose, 0); assert.equal(stone.attributes.active, 1); assert.equal(stone.attributes.collision, 1);
assert.equal(item.attributes.active, 0); assert.equal(item.attributes.interactive, 0);
assert.equal(game.missionHost.sceneVm.getGlobal('g_iStoneHP')[19], 500);
const result = {
  date: '2026-10-26', kind: 'cpu-geometric-audit', passed: true,
  source: 'actual sn01 DES/cmodel/FMC/POS and scene PST; actual NativeProjectileSystem continuous map sweep and createNativeSceneDamageResolver',
  probe: { from: probe.from.toArray(), target: probe.target.toArray(), firstNativeHit: probe.hit.object.name },
  hitNames, hpAfterHits, stateAfterImpact,
  final,
  reinitialized: { hp: game.missionHost.sceneVm.getGlobal('g_iStoneHP')[19], stonePose: stone.pose, stoneActive: stone.attributes.active, stoneCollision: stone.attributes.collision, itemActive: item.attributes.active, itemInteractive: item.attributes.interactive },
  notAsserted: ['actual character aim/release', 'reachable walk route to synthetic probe origin', 'browser rendering', 'item pickup or item effects', 'exact EXE flight constants'],
  diagnostics: game.missionHost.diagnostics
};
console.log(JSON.stringify(result, null, 2));
game.projectiles.dispose(); game.missionHost.dispose(); game._disposeMap(game.currentMap);

// Read-only local-source audit. Only image decoding / characters / presentation
// are omitted; original map props, PST, menu and start lifecycle are exercised.
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../../../dist/vendor/three.module.js';
import { MeteorGame } from '../../../dist/engine.js';
import { NativeMissionHost } from '../../../dist/native-mission-host.js';
const dist = new URL('../../../dist/', import.meta.url), original = new URL('assets/original/', dist);
globalThis.fetch = async input => { try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); } catch { return new Response('', { status: 404 }); } };
THREE.TextureLoader.prototype.load = function(url, done) { const t = new THREE.Texture(); done?.(t); return t; };
const actor = (id = 0, hero = true) => ({ id, hero, root: new THREE.Group(), character: { dispose() {} }, weapon: 'dagger', hp: 1500, maxHp: 1500,
  velocity: new THREE.Vector3(), attackHits: new Set(), combat: { play() {}, setWeapon() {} } });
const game = Object.create(MeteorGame.prototype);
Object.assign(game, { manifest: JSON.parse(await readFile(new URL('manifest.json', original), 'utf8')),
  scene: new THREE.Scene(), cameraTarget: new THREE.Vector3(), collisionMaterial: new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }), raycaster: new THREE.Raycaster(),
  onEvent() {}, onUpdate() {}, _soundDefinition() {}, _hud() {}, _tickCamera() {}, _unlockAudio() {}, _emit() {},
  hostPhysics: { radius: .4, step: .55 }, map: 'sn01', mode: 'story', hero: actor(), enemies: [], keys: new Set(),
  ready: Promise.resolve(), sessionRequest: 0, characterId: 0, disposed: false,
  _equip: async (f, weapon) => { f.weapon = typeof weapon === 'string' ? weapon : 'dagger'; },
  _createFighter: async id => actor(id, false) });
game.currentMap = await game._readMap('sn01'); game.scene.add(game.currentMap.model);
game.missionHost = await NativeMissionHost.create(game);
game.missionHost.call(game.missionHost.sceneVm, 'Scene_OnLoad'); game.missionHost.call(game.missionHost.sceneVm, 'Scene_OnInit');
const stone = game.getSceneObject('D_St22'), drop = game.getSceneObject('D_itSt22');
const snapshot = () => ({ stone: { pose: stone.pose, state: stone.state, active: stone.attributes.active, collision: stone.attributes.collision },
  drop: { active: drop.attributes.active, interactive: drop.attributes.interactive }, mode: game.mode });
const originalState = snapshot();
game.missionHost.sceneItemAttack('D_St22', 0, 500);
for (let n = 0; n < 600; n++) { game.currentMap.props.update(1 / 60); game.missionHost.sceneItemIdle('D_St22'); }
assert.equal(stone.attributes.active, 0); assert.equal(stone.attributes.collision, 0); assert.equal(drop.attributes.active, 1);
const destroyed = snapshot();
await game.menu('sn01'); const afterMenu = snapshot();
const leakedAfterMenu = afterMenu.stone.active === 0 && afterMenu.drop.active === 1;
await game.start({ map: 'sn01', mode: 'training', weapon: 'sword', character: 0 }); const afterTraining = snapshot();
assert.equal(game.running, true); assert.equal(game.mode, 'training');
const leakedAfterTraining = afterTraining.stone.active === 0 && afterTraining.drop.active === 1;
await game.start({ map: 'sn01', mode: 'story', character: 0 }); const afterStoryRestart = snapshot();
assert.equal(afterStoryRestart.stone.active, 1); assert.equal(afterStoryRestart.stone.collision, 1);
assert.equal(afterStoryRestart.drop.active, 0); assert.equal(afterStoryRestart.drop.interactive, 0);
console.log(JSON.stringify({ date: '2026-10-26', kind: 'scene-state-lifecycle-audit', leakPresent: leakedAfterMenu || leakedAfterTraining,
  originalState, destroyed, afterMenu, afterTraining, afterStoryRestart,
  finding: leakedAfterMenu || leakedAfterTraining ? 'Source story destruction/drop state leaks into a later session.' : 'Cached scene source state now resets at menu and training boundaries; original story initialization still restores the mission-specific state.',
  scope: 'Original sn01 DES/cmodel/FMC/PST and production menu/start; synthetic attack callback and lightweight actors, no browser or ordinary combat claim.' }, null, 2));
game.missionHost?.dispose(); game._disposeMap(game.currentMap);

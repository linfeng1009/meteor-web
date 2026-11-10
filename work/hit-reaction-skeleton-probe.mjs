import test, { after } from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { loadNativeCombat, NativeCombatController, createNativeDamageResolver } from '../dist/native-combat.js';

// Real POS, RES, SKC/BNC/AMB and native weapons on a plain CPU test floor.
// Textures, browser rendering/audio and NPC retaliation are intentionally absent;
// these tests prove the hit/reaction chain, not original AI or manual victory.
const dist = new URL('../dist/', import.meta.url), v = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
const priorFetch = globalThis.fetch, priorTextureLoad = THREE.TextureLoader.prototype.load;
globalThis.fetch = async input => { try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); } catch { return new Response('', { status: 404 }); } };
THREE.TextureLoader.prototype.load = function(url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
const data = await loadNativeCombat(), weapons = JSON.parse(await readFile(new URL('assets/original/weapon-models/manifest.json', dist), 'utf8'));
const fixtures = [];
after(() => {
  for (const { game, floor } of fixtures) {
    game.projectiles?.dispose(); for (const actor of [game.hero, ...game.enemies]) actor.character.dispose();
    for (const promise of game.weaponCache.values()) promise.then(model => model.traverse(node => {
      node.geometry?.dispose(); for (const material of Array.isArray(node.material) ? node.material : [node.material]) material?.dispose();
    }));
    floor.geometry.dispose(); floor.material.dispose();
  }
  globalThis.fetch = priorFetch; THREE.TextureLoader.prototype.load = priorTextureLoad;
});

async function fixture() {
  const game = Object.create(MeteorGame.prototype), events = [], sounds = [];
  const floor = new THREE.Mesh(new THREE.PlaneGeometry(200, 200), new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }));
  floor.rotation.x = -Math.PI / 2; floor.updateMatrixWorld(true);
  Object.assign(game, { combatData: data, weaponManifest: weapons,
    weaponItems: new Map(weapons.items.map(item => [Number(item.itemId), item])),
    weaponModels: new Map(weapons.models.map(model => [model.modelId.toLowerCase(), model])), weaponCache: new Map(),
    effectDefinitions: new Map(), waveFiles: new Map(), effects: [], scene: new THREE.Scene(), camera: new THREE.PerspectiveCamera(), raycaster: new THREE.Raycaster(),
    hostPhysics: { speed: 8, gravity: 34, jumpVelocity: 12, radius: .4, step: .55 },
    currentMap: { colliders: [floor], bounds: new THREE.Box3(v(-100, -1, -100), v(100, 30, 100)), metadata: {}, spawns: [{ position: v(0, .015, 0) }] },
    weapon: 'sword', actorSerial: 0, enemies: [], keys: new Set(), directionBuffer: [], cameraAngle: 0,
    running: true, paused: false, mode: 'training', elapsed: 0, matchElapsed: 0, kills: 0, deaths: 0, totalDamage: 0, contactHits: 0,
    onEvent: event => events.push(event), onUpdate() {}, _emit(text, type, amount, point, extra) { events.push({ text, type, amount, ...extra }); },
    _nameplate() {}, _unlockAudio() {}, _soundDefinition: name => sounds.push(name), _hud() {} });
  game.damageResolver = createNativeDamageResolver(data); game._initializeProjectiles();
  game.hero = await game._createFighter(0, '孟星魂', true); game.scene.add(game.hero.root);
  game._placeFighter(game.hero, { position: v(0, .015, 0) }); await game._equip(game.hero, 'sword');
  const target = await game._createFighter(8, '原版对练角色'); game.scene.add(target.root); game.enemies.push(target);
  game._placeFighter(target, { position: v(0, .015, 1.1) }); await game._equip(target, 'spear');
  target.maxHp = target.hp = 10000; target.team = target.teamMask = 2; game.hero.team = game.hero.teamMask = 1;
  target.scriptControlled = true; target.scriptControl = { paused: true }; game.locked = target;
  const result = { game, hero: game.hero, target, floor, events, sounds }; fixtures.push(result); return result;
}
function hit(game, attacker, target, poseId, attack = data.poses.get(poseId).attacks[0]) {
  return game._applyNativeHit(attacker, target, { poseId, pose: data.poses.get(poseId) }, attack, target.root.position.clone().add(v(0, 1.35, 0)));
}
function tick(game, dt = 1 / 60) {
  game.elapsed += dt; game.matchElapsed += dt;
  game._updateFighter(game.hero, dt); for (const actor of game.enemies) game._updateFighter(actor, dt);
  game.projectiles.update(dt);
}

const {target}=await fixture();for (const id of [7,93,98,112,119]) {const pose=data.poses.get(id);for(const frame of [pose.start,(pose.start+pose.end)/2,pose.end]){target.character.setPoseFrame(pose.source,frame);const head=target.character.getAttachment('bau_Head').getWorldPosition(v()),hip=target.character.getAttachment('bad_Pelvis').getWorldPosition(v());console.log(JSON.stringify({id,frame,head:head.clone().sub(target.root.position).toArray(),hip:hip.clone().sub(target.root.position).toArray()}));}}

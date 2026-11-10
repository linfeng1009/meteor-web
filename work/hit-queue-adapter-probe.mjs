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

const results=[];
for(const enabled of [false,true]) {
 const {game,hero,target,events}=await fixture();hero.combat.preserveQueuedStrikes=enabled;
 for(let frame=0;frame<360&&target.combat.timeline.pose.id!==98;frame++){if(frame%6===0)game.action('attack');tick(game);}
 results.push({preserveQueuedStrikes:enabled,hits:events.filter(e=>e.type==='hit').map(e=>({poseId:e.poseId,damage:e.amount})),contacts:game.contactHits,targetPose:target.combat.timeline.pose.id,targetHP:target.hp});
}
const {writeFile}=await import('node:fs/promises'),{createHash}=await import('node:crypto');
const files=['tests/native-hit-reaction.test.mjs','dist/native-combat.js','dist/engine.js','work/hit-queue-adapter-probe.mjs'];
const evidence={date:'2026-10-30',scope:'CPU original assets; 100ms public attack presses, no NPC retaliation; legacy immediate queue vs explicit Web preserveQueuedStrikes adapter.',results,files:await Promise.all(files.map(async path=>({path,sha256:createHash('sha256').update(await readFile(new URL('../'+path,import.meta.url))).digest('hex')})))};
await writeFile(new URL('meteor-original/evidence/E-hit-queue-replay-2026-10-30.json',import.meta.url),JSON.stringify(evidence,null,2)+'\n');console.log(JSON.stringify(results));

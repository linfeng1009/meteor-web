import test, { after } from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { nativeCanDiscover, findNativeEnemy } from '../dist/native-awareness.js';
import { MeteorGame } from '../dist/engine.js';
import { FEATURED_APPEARANCES, savedBattleCharacterSelection } from '../dist/character-appearances.js';
import { loadNativeCombat, createNativeDamageResolver } from '../dist/native-combat.js';
import { NativeNpcCombat } from '../dist/native-npc-combat.js';

const v = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
function observer() { return { root: new THREE.Group(), hp: 1000, team: 2, scriptConfig: { View: 400 } }; }
function enemy(position) { const actor = observer(); actor.team = 1; actor.root.position.copy(position); return actor; }

test('original discovery requires View, a forward half-space beyond80 native units, and line of sight', () => {
  const actor = observer(), target = enemy(v(0, 0, 31.9));
  assert.equal(nativeCanDiscover(actor, target, () => true), true);
  target.root.position.z = 32.1; assert.equal(nativeCanDiscover(actor, target, () => true), false);
  target.root.position.set(0, 0, -20); assert.equal(nativeCanDiscover(actor, target, () => true), false);
  target.root.position.set(20, 0, 0); assert.equal(nativeCanDiscover(actor, target, () => true), false);
  actor.root.rotation.y = Math.PI / 2; assert.equal(nativeCanDiscover(actor, target, () => true), true);
  assert.equal(nativeCanDiscover(actor, target, () => false), false);
  target.team = 2; assert.equal(nativeCanDiscover(actor, target, () => true), false);
});

test('native nearby awareness is omnidirectional but never bypasses range or an occluding wall', () => {
  const actor = observer(), target = enemy(v(0, 0, -6.39));
  assert.equal(nativeCanDiscover(actor, target, () => true), true);
  target.root.position.z = -6.41; assert.equal(nativeCanDiscover(actor, target, () => true), false);
  target.root.position.z = -5; actor.scriptConfig.View = 50;
  assert.equal(nativeCanDiscover(actor, target, () => true), false);
  actor.scriptConfig.View = 400; assert.equal(nativeCanDiscover(actor, target, () => false), false);
});

test('an unknown actor is not a target; a known nearby enemy is retained and lost at the original200-unit boundary', () => {
  const actor = observer(), target = enemy(v(0, 0, -12));
  assert.equal(findNativeEnemy(actor, [target], () => true), null);
  target.root.position.z = 20; assert.equal(findNativeEnemy(actor, [target], () => true), target);
  target.root.position.z = -15.9; assert.equal(findNativeEnemy(actor, [target], () => false), target);
  target.root.position.z = -16; assert.equal(findNativeEnemy(actor, [target], () => false), null);
  target.root.position.z = 5; findNativeEnemy(actor, [target], () => true);
  target.dead = true; assert.equal(findNativeEnemy(actor, [target], () => true), null);
  target.dead = false; target.disposed = true; assert.equal(findNativeEnemy(actor, [target], () => true), null);
});

const dist = new URL('../dist/', import.meta.url), priorFetch = globalThis.fetch, priorLoad = THREE.TextureLoader.prototype.load;
globalThis.fetch = async input => { try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); } catch { return new Response('', { status: 404 }); } };
THREE.TextureLoader.prototype.load = function (_url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
const combat = await loadNativeCombat();
const weapons = JSON.parse(await readFile(new URL('assets/original/weapon-models/manifest.json', dist), 'utf8'));
const originalManifest = JSON.parse(await readFile(new URL('assets/original/manifest.json', dist), 'utf8'));
const metadata = JSON.parse(await readFile(new URL('assets/original/maps/sn06/metadata.json', dist), 'utf8'));
const des = metadata.files.find(file => file.parsed?.format === 'DES').parsed;
const sourceSpawns = des.objects.filter(object => /^D_user\d+$/i.test(object.name)).sort((a, b) => a.name.localeCompare(b.name, undefined, { numeric: true }))
  .map(object => ({ name: object.name, position: v(object.position[0] * .08, object.position[2] * .08, -object.position[1] * .08), rotation: object.quaternion }));
const fixtures = [];
async function fixture({ originalMap = false } = {}) {
  const game = Object.create(MeteorGame.prototype), events = [], floor = new THREE.Mesh(new THREE.PlaneGeometry(250, 250), new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }));
  floor.rotation.x = -Math.PI / 2; floor.updateMatrixWorld(true);
  Object.assign(game, { ready: Promise.resolve(), sessionRequest: 0, characterRequest: 0, characterId: 0, map: 'sifang', actorSerial: 0, enemies: [],
    combatData: combat, weaponManifest: weapons, weaponItems: new Map(weapons.items.map(item => [Number(item.itemId), item])),
    weaponModels: new Map(weapons.models.map(model => [model.modelId.toLowerCase(), model])), weaponCache: new Map(),
    scene: new THREE.Scene(), camera: new THREE.PerspectiveCamera(), cameraTarget: v(), raycaster: new THREE.Raycaster(),
    effectDefinitions: new Map(), waveFiles: new Map(), effects: [], keys: new Set(), directionBuffer: [],
    hostPhysics: { speed: 8, gravity: 34, jumpVelocity: 12, radius: .4, step: .55 },
    currentMap: { id: 'sn06', entry: { name: '四方阵' }, metadata: {}, spawns: sourceSpawns, colliders: [floor], bounds: new THREE.Box3(v(-125, -1, -125), v(125, 60, 125)) },
    weapon: 'sword', elapsed: 0, mode: 'training', running: true, paused: false,
    onEvent: event => events.push(event), onUpdate() {}, _nameplate() {}, _unlockAudio() {}, _soundDefinition() {}, _hud() {}, _tickCamera() {} });
  if (originalMap) {
    game.manifest = originalManifest; game.collisionMaterial = new THREE.MeshBasicMaterial({ side: THREE.DoubleSide });
    game.currentMap = await game._readMap('sn06'); game.scene.add(game.currentMap.model);
  }
  game.damageResolver = createNativeDamageResolver(combat); game._initializeProjectiles();
  game.hero = await game._createFighter(0, '孟星魂', true); game.scene.add(game.hero.root);
  fixtures.push({ game, floor }); await game.start({ map: 'sifang', weapon: 'sword' });
  return { game, events };
}
function tick(game, dt = 1 / 60) {
  if (!game.running || game.paused) return;
  game.elapsed += dt; game.matchElapsed += dt; game._updateFighter(game.hero, dt);
  for (const actor of game.enemies) game._updateFighter(actor, dt);
  game._separateCharacters(dt); game.projectiles.update(dt); game.wheels.update(dt);
}
after(async () => {
  globalThis.fetch = priorFetch; THREE.TextureLoader.prototype.load = priorLoad;
  for (const { game, floor } of fixtures) {
    game.projectiles.dispose(); game.muskets.dispose(); game.wheels.dispose(); game.butterflyVfx?.dispose();
    for (const actor of [game.hero, ...game.enemies]) actor.character.dispose();
    for (const model of await Promise.all(game.weaponCache.values())) model.traverse(node => { node.geometry?.dispose(); for (const material of Array.isArray(node.material) ? node.material : [node.material]) material?.dispose(); });
    floor.geometry.dispose(); floor.material.dispose();
    if (game.collisionMaterial) { game._disposeMap(game.currentMap); game.collisionMaterial.dispose(); }
  }
});

test('actual training start with original四方阵 spawns wakes only the enemy that discovers the player and permits public combos', async t => {
  const { game, events } = await fixture();
  assert.deepEqual(game.enemies.map(actor => sourceSpawns[actor.spawnIndex].name), ['D_user09', 'D_user12', 'D_user05']);
  const start = game.enemies.map(actor => actor.root.position.clone());
  for (let frame = 0; frame < 60; frame++) tick(game);
  const moved = game.enemies.map((actor, index) => actor.root.position.distanceTo(start[index]));
  assert.ok(moved[0] > 1); assert.ok(moved[1] < .01); assert.ok(moved[2] < .01);
  assert.deepEqual(game.enemies.map(actor => !!actor.awarenessTarget), [true, false, false]);
  game.action('attack'); assert.equal(game.hero.combat.timeline.pose.id, 262);
  for (let frame = 0; frame < 60 && !game.hero.combat.timeline.canCancel; frame++) tick(game);
  game.action('attack');
  for (let frame = 0; frame < 120 && game.hero.combat.timeline.pose.id !== 263; frame++) tick(game);
  assert.equal(game.hero.combat.timeline.pose.id, 263, 'ordinary AA input starts its real second source pose before unseen enemies can interrupt it');
  assert.equal(events.filter(event => event.type === 'hit' && event.targetHero).length, 0);
  t.diagnostic(`Source DES starts on a CPU floor with live NPC AI: displacement=${moved.map(n => n.toFixed(3))}; awareness=true,false,false; public262→263.`);
});

test('unseen training enemies cannot discover through real collision triangles and respawn clears their cached target', async () => {
  const { game } = await fixture(), actor = game.enemies[1];
  actor.root.position.copy(game.hero.root.position).add(v(0, 0, -10)); actor.root.rotation.y = 0;
  const wall = new THREE.Mesh(new THREE.BoxGeometry(20, 8, 1), new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }));
  wall.position.copy(game.hero.root.position).add(v(0, 3, -5)); wall.updateMatrixWorld(true); game.currentMap.colliders.push(wall);
  const start = actor.root.position.clone(); for (let frame = 0; frame < 30; frame++) tick(game);
  assert.equal(actor.awarenessTarget, null); assert.ok(actor.root.position.distanceTo(start) < .01);
  game.currentMap.colliders.pop(); wall.geometry.dispose(); wall.material.dispose(); tick(game);
  assert.equal(actor.awarenessTarget, game.hero);
  game._placeFighter(actor, sourceSpawns[actor.spawnIndex]); assert.equal(actor.awarenessTarget, null);
  assert.equal(actor.root.rotation.y, 0); tick(game); assert.equal(actor.awarenessTarget, null);
});

test('original四方阵 geometry and normal start preserve discovery-gated live AI rather than an opening three-enemy rush', async t => {
  const { game } = await fixture({ originalMap: true });
  assert.ok(game.currentMap.colliders.length > 0); assert.ok(game.currentMap.props);
  assert.equal(game.hero.character.appearance, 'liuchao');
  assert.equal(game.hero.name, '琉潮');
  assert.equal(new Set(game.enemies.map(actor => actor.character.appearance)).size, 3);
  assert.ok(game.enemies.every(actor => FEATURED_APPEARANCES.includes(actor.character.appearance)));

  const start = game.enemies.map(actor => actor.root.position.clone());
  for (let frame = 0; frame < 60; frame++) tick(game);
  const moved = game.enemies.map((actor, index) => actor.root.position.distanceTo(start[index]));
  assert.equal(game.enemies.filter(actor => actor.awarenessTarget === game.hero).length, 1);
  assert.ok(moved[0] > 1); assert.ok(moved[1] < .01); assert.ok(moved[2] < .01);
  assert.equal(game.hero.hp, game.hero.maxHp);
  t.diagnostic(`Originalsn06 model/colliders/spawns plus live AI: displacement=${moved.map(n => n.toFixed(3))}; one enemy discovers the player, two remain unaware. CPU; no browser rendering.`);
});

test('an old default or retired character migrates to Liu Chao, while explicit original choices persist', () => {
  const defaultChoice = { character: 0, characterAppearance: 'liuchao' };
  assert.deepEqual(savedBattleCharacterSelection({ character: 0, characterAppearance: 'original' }), defaultChoice);
  assert.deepEqual(savedBattleCharacterSelection({ character: 0, characterAppearance: 'hd', characterSelected: true }), defaultChoice);
  assert.deepEqual(savedBattleCharacterSelection({ character: 0, characterAppearance: 'original', characterSelected: true }), { character: 0, characterAppearance: 'original' });
  assert.deepEqual(savedBattleCharacterSelection({ character: 1, characterAppearance: 'original', characterSelected: true }), { character: 1, characterAppearance: 'original' });
});

test('a manually picked original fighter remains selected when opening a battlefield with featured NPCs', async () => {
  const { game } = await fixture();
  await game.start({ map: 'sifang', character: 1, characterAppearance: 'original' });
  assert.equal(game.hero.modelId, 1);
  assert.equal(game.hero.character.appearance, 'original');
  assert.ok(game.enemies.every(actor => FEATURED_APPEARANCES.includes(actor.character.appearance)));
  await game.menu('sifang', { character: 0, characterAppearance: 'hutao' });
  assert.equal(game.hero.character.appearance, 'hutao');
  assert.equal(game.enemies.length, 0);
});

async function opponent(game, weapon, config, random) {
  const actor = game.enemies[0];
  for (const [index, other] of game.enemies.slice(1).entries()) game._placeFighter(other, { position: game.hero.root.position.clone().add(v(80 + index * 10, 0, 0)) });
  game._placeFighter(actor, { position: game.hero.root.position.clone().add(v(0, 0, 1.1)) }); actor.root.rotation.y = Math.PI;
  await game._equip(actor, weapon); actor.scriptConfig = config;
  actor.npcCombat = new NativeNpcCombat(game.combatData.npcAi, { random });
  return actor;
}

test('NPC source Guard weight drives real guard reactions instead of always restarting a basic attack', async () => {
  const { game, events } = await fixture(), actor = await opponent(game, 'sword', { Think: 100, Guard: 100, Attack1: 0, Attack2: 0, Attack3: 0 }, () => 1 / 32768);
  await game._equip(game.hero, 'spear');
  for (let frame = 0; frame < 120 && !actor.guard; frame++) tick(game);
  assert.equal(actor.guard, true);
  game.action('attack');
  for (let frame = 0; frame < 120 && !actor.contacts; frame++) tick(game);
  const hit = events.find(event => event.type === 'hit' && event.attackerHero);
  assert.ok(hit?.guarded); assert.equal(actor.hp, actor.maxHp);
  assert.ok(events.some(event => event.type === 'npc-decision' && event.kind === 'guard'));
  assert.equal(events.some(event => event.type === 'npc-decision' && event.kind === 'attack'), false);
});

test('NPC 原防御抽样的蹲守分支使用真实蹲姿，不伪装成格挡或攻击',async()=>{
  const {game,events}=await fixture(),actor=await opponent(game,'sword',{Think:100,Guard:100,Attack1:0,Attack2:0,Attack3:0},()=>0);
  for(let frame=0;frame<120&&!actor.npcCombat.crouch;frame++)tick(game);
  assert.equal(actor.npcCombat.crouch,true);assert.equal(actor.guard,false);
  tick(game);assert.ok([10,145,146,147,148].includes(actor.combat.timeline.pose.id));
  assert.ok(events.some(event=>event.type==='npc-decision'&&event.kind==='guard'&&event.defense==='crouch'));
  assert.equal(events.some(event=>event.type==='npc-decision'&&event.kind==='attack'),false);
  actor.scriptConfig={Think:100,Guard:0,Attack1:0,Attack2:0,Attack3:0};
  for(let frame=0;frame<120&&actor.npcCombat.crouch;frame++)tick(game);
  assert.equal(actor.npcCombat.crouch,false);assert.equal(actor.guard,false);
});

test('NPC Attack2 chooses the original spear forward program and damages through its real285 pose', async t => {
  const { game, events } = await fixture(), actor = await opponent(game, 'spear', { Think: 100, Guard: 0, Attack1: 0, Attack2: 100, Attack3: 0 }, () => 1 / 32768);
  for (let frame = 0; frame < 180 && !events.some(event => event.type === 'hit' && event.poseId === 285); frame++) tick(game);
  assert.ok(events.some(event => event.type === 'npc-decision' && event.kind === 'attack' && event.category === 1 && event.program === 'f' && event.poseId === 285 && event.accepted));
  const hit = events.find(event => event.type === 'hit' && event.poseId === 285);
  assert.ok(hit?.targetHero); assert.equal(hit.attackerHero, false); assert.ok(game.hero.hp < game.hero.maxHp);
  t.diagnostic(`Live NPC sourceAttack2→f→285 actual damage=${game.hero.maxHp - game.hero.hp}; source weapon and SKC/AMB; other NPCs remain out of view.`);
  assert.equal(actor.weapon, 'spear');
});

test('NPC long commands use restored buffs and retain rage gates, then pay once across the original293→294 link', async () => {
  const { game, events } = await fixture();
  const stream = (...values) => { let index = 0; return () => (values[Math.min(index++, values.length - 1)] || 0) / 32768; };
  const config = { Think: 100, Guard: 0, Attack1: 0, Attack2: 0, Attack3: 100 };
  const actor = await opponent(game, 'dual', config, stream(0, 0, 0, 1, 3)); actor.rage = 100;
  game._npcCombatAction(actor, game.hero, true, { reach: 10 });
  assert.ok(events.some(event => event.type === 'npc-decision' && event.poseId === 557 && event.accepted)); assert.equal(actor.combat.busy, true); assert.equal(actor.rage, 0);
  game._placeFighter(actor,{position:actor.root.position.clone()});
  await game._equip(actor, 'spear'); actor.rage = 0; actor.npcCombat = new NativeNpcCombat(game.combatData.npcAi, { random: stream(0, 0, 0, 1, 7) });
  game._npcCombatAction(actor, game.hero, true, { reach: 10 });
  assert.ok(events.some(event => event.type === 'npc-decision' && event.poseId === 293 && !event.accepted)); assert.equal(actor.combat.busy, false);
  actor.rage = 100; actor.npcCombat = new NativeNpcCombat(game.combatData.npcAi, { random: stream(0, 0, 0, 1, 7) });
  game._npcCombatAction(actor, game.hero, true, { reach: 10 });
  assert.equal(actor.combat.timeline.pose.id, 293); assert.equal(actor.rage, 0);
  const seen = new Set(); for (let frame = 0; frame < 420; frame++) { tick(game); seen.add(actor.combat.timeline.pose.id); }
  assert.ok(seen.has(294)); assert.equal(actor.rage, 0);
  assert.equal(events.filter(event => event.type === 'npc-decision' && event.poseId === 293 && event.accepted).length, 1);
});

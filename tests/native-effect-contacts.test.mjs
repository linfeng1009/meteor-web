import {nativeStrideSpeed} from '../dist/native-movement-profile.js';
import test, { after } from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { createHash } from 'node:crypto';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { loadNativeCombat, NativeCombatController, createNativeDamageResolver } from '../dist/native-combat.js';
import { NativeEffectContacts, nativeEffectBounds, intersectsEffectBody } from '../dist/native-effect-contacts.js';
import { NativeRageVfx } from '../dist/native-rage-vfx.js';
import { NativeImpactFeedback } from '../dist/native-impact-feedback.js';
import { nativeEffectiveStat } from '../dist/native-combat.js';
import { nativeMovementScale, useNativeScriptItem, updateNativeScriptItems, clearNativeScriptItems } from '../dist/native-items.js';

const dist = new URL('../dist/', import.meta.url), v = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
const oldFetch = globalThis.fetch, oldTextureLoad = THREE.TextureLoader.prototype.load;
globalThis.fetch = async input => { try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); } catch { return new Response('', { status: 404 }); } };
THREE.TextureLoader.prototype.load = function(url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
const data = await loadNativeCombat(), manifest = JSON.parse(await readFile(new URL('assets/original/rage-vfx/manifest.json', dist), 'utf8'));
const weapons = JSON.parse(await readFile(new URL('assets/original/weapon-models/manifest.json', dist), 'utf8')), fixtures = [];

async function fixture(positions = [v(3.5, 0, 0), v(-3.5, 0, 0), v(0, 0, -3.5)]) {
  const floor = new THREE.Mesh(new THREE.PlaneGeometry(300, 300), new THREE.MeshBasicMaterial({ side: THREE.DoubleSide })); floor.rotation.x = -Math.PI / 2; floor.updateMatrixWorld(true);
  const game = Object.create(MeteorGame.prototype), events = [];
  Object.assign(game, { combatData: data, weaponManifest: weapons,
    weaponItems: new Map(weapons.items.map(item => [Number(item.itemId), item])), weaponModels: new Map(weapons.models.map(model => [model.modelId.toLowerCase(), model])), weaponCache: new Map(),
    scene: new THREE.Scene(), camera: new THREE.PerspectiveCamera(), raycaster: new THREE.Raycaster(), effectDefinitions: new Map(), waveFiles: new Map(), effects: [],
    hostPhysics: { speed: 8, gravity: 34, jumpVelocity: 12, radius: .4, step: .55 },
    currentMap: { colliders: [floor], bounds: new THREE.Box3(v(-150, -1, -150), v(150, 60, 150)), metadata: {}, spawns: [{ position: v(0, .015, 0) }] },
    weapon: 'spear', actorSerial: 0, enemies: [], keys: new Set(), directionBuffer: [], cameraAngle: 0,
    running: true, paused: false, mode: 'training', elapsed: 0, matchElapsed: 0, kills: 0, deaths: 0, totalDamage: 0, contactHits: 0,
    onEvent: event => events.push({ ...event, time: game.elapsed }), onUpdate() {}, _nameplate() {}, _unlockAudio() {}, _soundDefinition() {}, _hud() {} });
  game.cameraAngle=Math.PI; // These fixtures face +Z toward their forward targets.
  game.damageResolver = createNativeDamageResolver(data); game._initializeProjectiles(); game._initializeEffectContacts(manifest); game.impactFeedback = new NativeImpactFeedback(game.scene);
  game.hero = await game._createFighter(0, '孟星魂', true); game.scene.add(game.hero.root);
  game._placeFighter(game.hero, { position: v(0, .015, 0) }); await game._equip(game.hero, 'spear'); game.hero.team = game.hero.teamMask = 1;
  for (const [index, position] of positions.entries()) {
    const actor = await game._createFighter(8, `原角色${index}`); game.scene.add(actor.root); game.enemies.push(actor);
    game._placeFighter(actor, { position }); await game._equip(actor, 'sword');
    actor.hp = actor.maxHp = 10000; actor.team = actor.teamMask = 2; actor.root.rotation.y = Math.atan2(-position.x, -position.z);
    actor.scriptControlled = true; actor.scriptControl = { paused: true };
  }
  const result = { game, events, floor }; fixtures.push(result); return result;
}
function tick(game, dt = 1 / 60) {
  if (game.paused || !game.running) return;
  game.elapsed += dt; game.matchElapsed += dt;
  game._updateFighter(game.hero, dt); for (const target of game.enemies) game._updateFighter(target, dt);
  game.projectiles.update(dt); game.wheels.update(dt);
}
function cast(game) {
  game.hero.rage = 100;
  for (const key of ['back', 'forward', 'forward']) { game.action(key); game.action(key, false); }
  game.action('attack');
  assert.equal(game.hero.combat.currentMove.poseId, 293); assert.equal(game.hero.rage, 0);
}
function dartCommand(game, directions, expected, rageCost) {
  for (const key of directions) { game.action(key); game.action(key, false); }
  const before = game.hero.rage; game.action('attack');
  assert.equal(game.hero.combat.timeline.pose.id, expected); assert.equal(game.hero.rage, before - rageCost);
}
after(async () => {
  for (const { game, floor } of fixtures) {
    game.effectContacts.dispose(); game.rageVfx?.dispose(); game.impactFeedback.dispose(); game.projectiles.dispose(); game.muskets.dispose(); game.wheels.dispose();
    for (const actor of [game.hero, ...game.enemies]) actor.character.dispose();
    for (const model of await Promise.all(game.weaponCache.values())) model.traverse(node => { node.geometry?.dispose(); for (const m of Array.isArray(node.material) ? node.material : [node.material]) m?.dispose(); });
    floor.geometry.dispose(); floor.material.dispose();
  }
  globalThis.fetch = oldFetch; THREE.TextureLoader.prototype.load = oldTextureLoad;
});

test('spear aura and wave use byte-identical original EF attack nodes and source POS effect windows', async () => {
  for (const id of [293, 294]) {
    const effect = manifest.effects[`pos${id}`], bytes = await readFile(new URL(`assets/original/${effect.source}`, dist));
    assert.equal(createHash('sha256').update(bytes).digest('hex'), effect.sha256);
    assert.ok(data.poses.get(id).attacks[0].bones.includes('effect'));
    assert.equal(data.poses.get(id).attacks[0].attacktype, 1);
  }
  const aura = manifest.effects.pos293.nodes.find(node => node.name === 'AttackBall01'), wave = manifest.effects.pos294.nodes.find(node => node.name === 'AttackShock');
  assert.equal(nativeEffectBounds(aura).half.x, 30);
  assert.deepEqual(nativeEffectBounds(wave).half.toArray(), [15, 15, 100]);
  assert.deepEqual(nativeEffectBounds(wave).center.toArray(), [0, 0, 100]);
  assert.deepEqual(aura.bindings, ['b', 'b']);
});

test('native EF seconds remain independent of accelerated POS frames and reset at automatic links', () => {
  const combat = new NativeCombatController(data, { weapon: 'spear' }); combat.attack({ poseId: 293, context: { rage: 100 } });
  const state = combat.update(.25, { grounded: true });
  assert.ok(Math.abs(state.effectTime - .25) < 1e-12); assert.ok((state.frame - state.pose.start) / 30 > state.effectTime + .05);
  let linked;
  for (let i = 0; i < 300 && !linked; i++) { const sample = combat.update(1 / 60, { grounded: true }); linked = sample.segments.find(s => s.poseId === 294 || s.pose?.id === 294); }
  assert.ok(linked); assert.ok(linked.effectTime < .02, 'the new EF starts its own clock rather than inheriting the old pose age');
});

test('dagger YanLuo uses its original effect-only box window, source109 reaction and349 finish through public input', async t => {
  const { game, events } = await fixture([v(0, 0, 5)]), actor = game.hero, target = game.enemies[0];
  await game._equip(actor, 'dagger'); actor.rage = 100;
  for (const key of ['back', 'forward', 'forward']) { game.action(key); game.action(key, false); }
  game.action('attack'); assert.equal(actor.combat.timeline.pose.id, 259); assert.equal(actor.rage, 0);
  for (let frame = 0; frame < 30; frame++) tick(game);
  assert.equal(target.hp, 10000, 'no weapon or body substitute may hit before the original effect window');
  const seen = new Set(); let reacting = false;
  for (let frame = 0; frame < 210; frame++) { tick(game); seen.add(actor.combat.timeline.pose.id); reacting ||= target.combat.timeline.pose.id === 109; }
  const hits = events.filter(event => event.type === 'hit' && event.poseId === 259);
  assert.equal(hits.length, 1); assert.equal(hits[0].contactSource, 'effect'); assert.equal(hits[0].effectNode, 'AttackBox');
  assert.equal(hits[0].raw.selectedTargetPose, 109); assert.ok(reacting); assert.ok(target.hp < 9900);
  assert.ok(seen.has(349)); assert.equal(actor.combat.busy, false); assert.equal(actor.combat.timeline.pose.id, 5);
  assert.equal(events.filter(event => event.type === 'move').length, 1);
  t.diagnostic(`Source effect-only dagger hit: damage=${10000 - target.hp}, attack259 then finish349; CPU actors with retaliation paused.`);
});

test('ground 八方绝 uses source effect contacts, gains victim rage before draining20, and skips guarded and rear actors', async t => {
  const { game, events } = await fixture([v(0, 0, 5), v(0, 0, 8), v(0, 0, -5)]);
  await game._equip(game.hero, 'dart'); game.hero.rage = 100;
  game.enemies[0].rage = 99; game.enemies[1].scriptControl.guard = true;
  dartCommand(game, ['back', 'forward'], 201, 60);
  for (let frame = 0; frame < 240; frame++) tick(game);
  const hits = events.filter(event => event.type === 'hit' && event.poseId === 201), normal = hits.find(event => event.targetName === game.enemies[0].name), guarded = hits.find(event => event.targetName === game.enemies[1].name);
  assert.ok(normal); assert.equal(normal.contactSource, 'effect'); assert.equal(normal.raw.attackItem.id, 22);
  assert.equal(normal.raw.attackItem.rageBefore, 100); assert.equal(game.enemies[0].rage, 80);
  assert.ok(guarded?.guarded); assert.equal(guarded.raw.attackItem, undefined); assert.equal(game.enemies[1].hp, 10000);
  assert.equal(game.enemies[2].hp, 10000, 'the authored fan does not become a circular damage pulse');
  assert.equal(game.enemies[0].scriptItems.length, 0); assert.equal(game.projectiles.size, 0, 'the special is not synthesized from ordinary dart projectiles');
  assert.equal(events.filter(event => event.type === 'attack-item').length, 1); assert.equal(game.hero.rage, 40);
  t.diagnostic(`Ground201 effect: ${normal.effectNode}; damage=${10000 - game.enemies[0].hp}; rage100→80 after the capped victim gain.`);
});

test('八方绝 respects source dynamic max rage, applies its item on zero damage, and skips lethal hits', async () => {
  const { game, events } = await fixture([v(0, 0, 5), v(0, 0, 8), v(0, 0, 10)]);
  await game._equip(game.hero, 'dart'); game.hero.rage = 100;
  const [low, high, lethal] = game.enemies;
  low.nativeStats = { 7: 50 }; low.rage = 49;
  high.nativeStats = { 4: 10000, 7: 200 }; high.rage = 195;
  lethal.hp = 1;
  dartCommand(game, ['back', 'forward'], 201, 60);
  for (let frame = 0; frame < 180; frame++) tick(game);
  assert.equal(low.rage, 30, 'victim gain must cap at50 before subtracting20');
  assert.equal(high.hp, 10000); assert.equal(high.rage, 175, 'zero damage does not suppress the source item or cap rage at100');
  assert.equal(lethal.dead, true); assert.equal(lethal.hp, 0);
  assert.equal(events.filter(event => event.type === 'attack-item' && event.actorId === lethal.id).length, 0);
  assert.equal(game.kills, 1);
});

test('air 八方绝 starts from a natural jump, uses its independent source effect and returns through211', async t => {
  const { game, events } = await fixture([v(0, 0, 5)]); await game._equip(game.hero, 'dart'); game.hero.rage = 100;
  game.action('jump'); game.action('jump', false);
  for (let frame = 0; frame < 3; frame++) tick(game);
  assert.equal(game.hero.grounded, false); assert.ok(game.hero.root.position.y > 1);
  dartCommand(game, ['back', 'forward'], 551, 60);
  const seen = new Set(); for (let frame = 0; frame < 360; frame++) { tick(game); seen.add(game.hero.combat.timeline.pose.id); }
  const hits = events.filter(event => event.type === 'hit' && event.poseId === 551);
  assert.equal(hits.length, 1); assert.equal(hits[0].contactSource, 'effect'); assert.equal(hits[0].raw.attackItem.id, 22);
  assert.ok(seen.has(211)); assert.equal(game.hero.grounded, true); assert.equal(game.hero.combat.busy, false);
  assert.equal(game.hero.rage, 40); assert.equal(events.filter(event => event.type === 'move').length, 1);
  t.diagnostic(`Natural-jump551 effect: ${hits[0].effectNode}; source211 observed; ordinary landing completed.`);
});

test('落樱雪 follows203→204→205→329 and poisons actual near and remote effect targets without stacking', async t => {
  const { game, events } = await fixture([v(0, 0, 2), v(0, 0, 5)]); await game._equip(game.hero, 'dart'); game.hero.rage = 100;
  dartCommand(game, ['back', 'forward', 'forward'], 203, 100);
  const seen = new Set(); for (let frame = 0; frame < 600; frame++) { tick(game); seen.add(game.hero.combat.timeline.pose.id); }
  for (const poseId of [203, 204, 205, 329]) assert.ok(seen.has(poseId), `missing source phase${poseId}`);
  const hits = events.filter(event => event.type === 'hit');
  assert.ok(hits.some(event => event.poseId === 203 && event.targetName === game.enemies[0].name));
  const remote = hits.find(event => event.poseId === 204 && event.targetName === game.enemies[1].name);
  assert.ok(remote); assert.equal(remote.contactSource, 'effect'); assert.equal(remote.raw.attackItem.id, 12);
  for (const target of game.enemies) {
    assert.equal(target.scriptItems.filter(item => item.id === 12).length, 1);
    assert.equal(target.activeItems.filter(item => item.id === 12).length, 1);
    const ticks = events.filter(event => event.type === 'item-tick' && event.actorId === target.id && event.itemId === 12);
    assert.ok(ticks.length >= 3); assert.ok(ticks.every(event => event.amount === 10));
    for (let index = 1; index < ticks.length; index++) assert.ok(Math.abs(ticks[index].time - ticks[index - 1].time - 2.2) < .02);
  }
  assert.equal(game.hero.combat.busy, false); assert.equal(game.hero.grounded, true); assert.equal(game.hero.rage, 0);
  assert.equal(events.filter(event => event.type === 'move').length, 1);
  t.diagnostic(`Source204 remote hit: ${remote.effectNode}; item12 tick counts=${game.enemies.map(target => events.filter(e => e.type === 'item-tick' && e.actorId === target.id).length).join(',')}; CPU NPC retaliation/navigation paused.`);
});

test('ordinary 赤练牙 applies its own source poison through a real released dart', async () => {
  const { game, events } = await fixture([v(0, 0, 5)]); await game._equip(game.hero, 'dart'); game.hero.rage = 0;
  dartCommand(game, ['back'], 210, 0);
  for (let frame = 0; frame < 300; frame++) tick(game);
  const hit = events.find(event => event.type === 'hit' && event.poseId === 210);
  assert.ok(hit?.projectileId); assert.equal(hit.raw.attackItem.id, 11);
  const ticks = events.filter(event => event.type === 'item-tick' && event.itemId === 11);
  assert.equal(ticks.length, 1); assert.equal(ticks[0].amount, 10);
  assert.equal(game.enemies[0].scriptItems[0].period, 3);
});

test('periodic damage pauses with game time, does not award an attacker kill, and clears at respawn', async () => {
  const { game, events } = await fixture([v(0, 0, 5)]), target = game.enemies[0]; target.hp = 15;
  assert.equal(game.useScriptItem(target, 12), true);
  game.paused = true; for (let frame = 0; frame < 600; frame++) tick(game); assert.equal(target.hp, 15);
  game.paused = false;
  for (let frame = 0; frame < 300 && !target.dead; frame++) tick(game);
  assert.equal(target.dead, true); assert.equal(target.hp, 0); assert.equal(game.kills, 0);
  assert.equal(events.filter(event => event.type === 'item-tick').length, 2);
  game._placeFighter(target, { position: v(0, .015, 5) }); const hp = target.hp;
  for (let frame = 0; frame < 240; frame++) tick(game);
  assert.equal(target.hp, hp); assert.deepEqual(target.scriptItems, []);
});

test('actual aura hits surrounding actors without textures, pays once and applies original recoil, knockdown and recovery', async t => {
  const { game, events } = await fixture(); assert.equal(game.rageVfx, undefined);
  const origins = game.enemies.map(actor => actor.root.position.clone()), farthest = origins.map(() => 0), phases = origins.map(() => new Set());
  cast(game);
  for (let i = 0; i < 420; i++) {
    tick(game);
    game.enemies.forEach((actor, index) => { farthest[index] = Math.max(farthest[index], actor.root.position.clone().sub(origins[index]).dot(origins[index].clone().setY(0).normalize())); phases[index].add(actor.combat.timeline.pose.id); });
  }
  const hits = events.filter(event => event.type === 'hit' && event.poseId === 293);
  for (const [index, actor] of game.enemies.entries()) {
    const own = hits.filter(event => event.targetName === actor.name); assert.equal(own.length, 1, actor.name);
    assert.equal(own[0].contactSource, 'effect'); assert.equal(own[0].effectNode, 'AttackBall01');
    assert.ok(actor.hp < actor.maxHp); assert.ok(farthest[index] > .2, `native recoil must move ${actor.name} outward: ${farthest[index]}`);
    assert.ok(phases[index].has(103) && phases[index].has(112) && phases[index].has(119), [...phases[index]].join(','));
  }
  assert.equal(events.filter(event => event.type === 'move').length, 1); assert.equal(game.hero.rage, 0);
  t.diagnostic(`Source aura outward displacement: ${farthest.map(n => n.toFixed(3)).join(', ')}m; isolated actors, not a live-AI playthrough.`);
});

test('linked forward wave hits beyond spear reach without a mirrored attack behind the caster', async () => {
  const { game, events } = await fixture([v(0, 0, 20), v(0, 0, -20), v(10, 0, 0)]); cast(game);
  for (let i = 0; i < 420; i++) tick(game);
  const wave = events.filter(event => event.type === 'hit' && event.poseId === 294);
  assert.equal(wave.length, 1); assert.equal(wave[0].targetName, game.enemies[0].name); assert.equal(wave[0].contactSource, 'effect');
  assert.ok(['AttackShock', 'AttackWave01'].includes(wave[0].effectNode));
  assert.ok(game.enemies[0].root.position.z > 20.2, 'the remote effect must drive original authored recoil too');
  assert.equal(game.enemies[1].hp, 10000); assert.equal(game.enemies[2].hp, 10000);
});

test('aura cannot hit outside its authored attack bounds, before activation, after interruption or while paused', async () => {
  const { game, events } = await fixture([v(6, 0, 0)]); cast(game);
  game.paused = true; const frame = game.hero.combat.timeline.frame; for (let i = 0; i < 60; i++) tick(game);
  assert.equal(game.hero.combat.timeline.frame, frame); assert.equal(game.enemies[0].hp, 10000); game.paused = false;
  for (let i = 0; i < 150; i++) tick(game);
  assert.equal(game.enemies[0].hp, 10000, 'the ordinary Sphere_7 visual is not an attack node');
  game.hero.combat.react(93); game.hero.heldPose = 'reaction';
  for (let i = 0; i < 240; i++) tick(game);
  assert.equal(events.filter(event => event.type === 'hit').length, 0);
});

test('effect and weapon contact share a POS window identity rather than dealing damage every render or per shape', async () => {
  const { game, events } = await fixture([v(0, 0, 1)]); cast(game);
  for (let i = 0; i < 420; i++) tick(game);
  const hits = events.filter(event => event.type === 'hit' && event.attackerHero);
  assert.equal(hits.filter(event => event.poseId === 293).length, 1); assert.ok(hits.filter(event => event.poseId === 294).length <= 1);
});

test('public spear AAA can chain into the original group-selected rage finish and its remote effect without replaying the windup', async () => {
  const { game, events } = await fixture([v(0, 0, 20)]), actor = game.hero; actor.rage = 100;
  for (const poseId of [279, 280, 281]) {
    game.action('attack');
    for (let i = 0; i < 300 && actor.combat.timeline.pose.id !== poseId; i++) tick(game);
    assert.equal(actor.combat.timeline.pose.id, poseId);
    for (let i = 0; i < 300 && !actor.combat.timeline.canCancel && !actor.combat.timeline.finished; i++) tick(game);
    assert.equal(actor.combat.timeline.canCancel, true);
  }
  for (const key of ['back', 'forward', 'forward']) { game.action(key); game.action(key, false); }
  game.action('attack');
  assert.equal(actor.combat.queuedMove?.poseId ?? actor.combat.currentMove?.poseId, 293);
  const seen = new Set(); for (let i = 0; i < 300; i++) { tick(game); seen.add(actor.combat.timeline.pose.id); }
  assert.ok(seen.has(294)); assert.equal(seen.has(293), false, 'source group can enter294 directly after281');
  assert.equal(actor.rage, 0); assert.equal(events.filter(e => e.type === 'move' && e.poseId === 293).length, 1);
  assert.ok(events.some(e => e.type === 'hit' && e.poseId === 294 && e.contactSource === 'effect'));
});

test('effect query rejects unresolved parents, zero scales, non-effect windows and disposed systems', async () => {
  const { game } = await fixture([]), actor = game.hero, pose = data.poses.get(293);
  const state = { pose, source: 0, serial: 99, previousFrame: pose.start, frame: pose.start + 90, previousEffectTime: 0, effectTime: 3 };
  const altered = structuredClone(manifest), node = altered.effects.pos293.nodes.find(node => node.name === 'AttackBall01');
  node.bindings = ['missing-parent', 'missing-parent']; const system = new NativeEffectContacts({ manifest: altered });
  assert.deepEqual(system.sample(actor, state, pose.attacks[0]), []);
  assert.deepEqual(game.effectContacts.sample(actor, state, { ...pose.attacks[0], bones: ['weapon'] }), []);
  node.bindings = ['b', 'b']; for (const key of node.keys) key.splice(8, 3, 0, 0, 0);
  assert.deepEqual(system.sample(actor, { ...state, serial: 100 }, pose.attacks[0]), []);
  system.dispose(); assert.deepEqual(system.sample(actor, state, pose.attacks[0]), []);
});

test('native attack nodes remain absent before their first source key and disappear at weapon changes', async () => {
  const { game } = await fixture([]), actor = game.hero, pose = data.poses.get(293);
  const state = { pose, source: 0, serial: 99, previousFrame: pose.start, frame: pose.start, previousEffectTime: .002, effectTime: .002 };
  assert.deepEqual(game.effectContacts.sample(actor, state, pose.attacks[0]), []);
  const live = { ...state, serial: 100, previousFrame: pose.start + 30, frame: pose.start + 30, previousEffectTime: 1, effectTime: 1 };
  assert.ok(game.effectContacts.sample(actor, live, pose.attacks[0]).length > 0);
  assert.equal(game.effectContacts.actors.size, 1);
  await game._equip(actor, 'sword'); assert.equal(game.effectContacts.actors.size, 0);
  game.effectContacts.clear(); assert.equal(game.effectContacts.actors.size, 0);
});

test('source wave contact survives coarse updates by sampling only the crossed original attack intervals', async () => {
  const { game } = await fixture([v(0, 0, 20)]), actor = game.hero, target = game.enemies[0], times = [];
  for (const dt of [1 / 120, 1 / 5]) {
    actor.combat.play(294, { force: true, attack: true, context: { rage: 100 } });
    let contact = null;
    for (let i = 0; i < Math.ceil(2 / dt) && !contact; i++) {
      const sample = actor.combat.update(dt, { grounded: true });
      for (const state of sample.segments) for (const attack of state.attacks) {
        contact ||= game.effectContacts.contact(game.effectContacts.sample(actor, state, attack), target);
      }
    }
    assert.ok(contact, `wave contact at dt=${dt}`); times.push(contact.effectTime);
  }
  assert.ok(Math.abs(times[0] - times[1]) < .02, times.join(','));
});

test('oriented effect bounds do not become an oversized world-axis box when the caster turns', () => {
  const e = [v(1, 0, 1).normalize().multiplyScalar(10), v(0, .2, 0), v(1, 0, -1).normalize().multiplyScalar(.2)];
  const volume = { center: v(0, 1.3, 0), edges: e };
  assert.equal(intersectsEffectBody(volume, v(5, 0, 5)), true);
  assert.equal(intersectsEffectBody(volume, v(5, 0, -5)), false);
});

test('visual and attack graphs agree on the source base-anchored cylinder and the elapsed effect clock', async () => {
  const { game } = await fixture([]), actor = game.hero, pose = data.poses.get(294);
  const renderer = new NativeRageVfx({ scene: game.scene, manifest, textures: new Map([['firl3600.bmp', new THREE.Texture()]]) }); game.rageVfx = renderer;
  const state = { pose, source: 0, serial: 100, context: { rage: 100 }, frame: pose.start + 8, previousFrame: pose.start + 8, previousEffectTime: .27, effectTime: .27 };
  actor.character.setPoseFrame(state.source, state.frame);
  const visual = renderer.sample(actor, state); renderer.update(0); assert.equal(visual.time, .27);
  const volume = game.effectContacts.sample(actor, state, pose.attacks[0]).find(volume => volume.nodeName === 'AttackShock'); assert.ok(volume);
  const mesh = visual.nodes.find(node => node.source.name === 'AttackShock').mesh; mesh.geometry.computeBoundingBox();
  const center = mesh.geometry.boundingBox.getCenter(v()).applyMatrix4(mesh.matrix);
  assert.ok(center.distanceTo(volume.center) < 1e-5);
});

function manual(game, keys) {
  if(game.hero.weapon==='musket'&&game.hero.musketAim&&game.hero.combat.timeline?.pose.id===212&&!game.hero.combat.timeline.finished)for(let i=0;i<70;i++)tick(game);
  if(game.hero.weapon==='musket'&&!game.hero.musketAim){game.action('attack');for(let i=0;i<70;i++)tick(game);game.directionBuffer=[];}
  for (const key of keys) { game.action(key); game.action(key, false); game.elapsed += .06; }
  game.action('attack'); game.action('attack', false);
}
function settle(game, seen = new Set()) {
  for (let frame = 0; frame < 900 && (game.hero.combat.busy || !game.hero.grounded); frame++) {
    seen.add(game.hero.combat.timeline.pose.id); tick(game);
  }
  for (let frame = 0; frame < 4; frame++) tick(game);
  assert.equal(game.hero.combat.busy, false, 'a complete special must release its attack state');
  assert.equal(game.hero.grounded, true, 'air/hammer recovery must return to the floor');
  return seen;
}

test('qiankun ultimate renders every final slash after pose456 ends without changing original hits or rage', async t => {
  const { game, events } = await fixture([v(0, .015, 8)]), actor = game.hero;
  await game._equip(actor, 'qiankun'); manual(game, ['back', 'back']); settle(game);
  const textures = new Map(Object.entries(manifest.textures).filter(([, record]) => record.url).map(([id]) => [id, new THREE.Texture()]));
  game.rageVfx = new NativeRageVfx({ scene: game.scene, manifest, textures });
  actor.rage = 100; const start = events.length; manual(game, ['back', 'back', 'forward']);
  const seen = new Set(), late = new Set(); let trails = false, endTime = 0;
  for (let frame = 0; frame < 470; frame++) {
    tick(game); game.rageVfx.update(1 / 60);
    trails ||= game.rageVfx.trails.strips.some(s => s.mesh.visible);
    for (const effect of game.rageVfx.active.filter(e => e.id === 'pos456')) {
      endTime = Math.max(endTime, effect.time);
      for (const node of effect.nodes.filter(n => /^SLASH/.test(n.source.name) && n.mesh?.visible)) {
        seen.add(node.source.name); if (!effect.live) late.add(node.source.name);
        assert.ok(node.mesh.matrix.elements.every(Number.isFinite));
      }
    }
  }
  assert.equal(seen.size, 12, 'six curved slashes and six matching flat slashes must all be drawn');
  assert.equal(late.size, 12, 'the actual POS animation ends before the source slash keys begin');
  assert.ok(endTime > 2.6); assert.ok(trails, 'the original red weapon Drag is visible during the cast');
  assert.equal(actor.rage, 0); assert.equal(events.slice(start).filter(e => e.type === 'move').length, 1);
  assert.ok(events.slice(start).some(e => e.type === 'hit' && e.contactSource === 'effect'));
  assert.equal(actor.combat.busy, false); assert.equal(game.rageVfx.active.length, 0);
  t.diagnostic(`Public ↓↓A → ↓↓↑A; final shapes=${seen.size}, detached=${late.size}, last EF sample=${endTime.toFixed(3)}s; one100-rage command.`);
});

test('reported weapon specials use public inputs, original attack contacts, one rage charge and complete recovery', async t => {
  const cases = [
    ['hammer', 325, ['back', 'back', 'forward'], 100, [325, 326, 327, 328]],
    ['musket', 216, ['back', 'forward'], 60, [216, 217, 212]],
    ['musket', 215, ['back', 'forward', 'forward'], 100, [215, 212]],
    ['wheel', 552, ['back', 'forward'], 60, [552]],
    ['wheel', 224, ['back', 'forward', 'forward'], 100, [224]],
    ['wheel', 554, ['back', 'forward'], 60, [554, 555], 'air'],
    ['knuckle', 416, ['left', 'right', 'forward'], 60, [416]],
    ['knuckle', 421, ['left', 'right', 'back'], 100, [421, 422, 423, 424, 425, 426, 488]],
    ['qiankun', 570, ['back', 'forward'], 60, [570], 'spear'],
    ['qiankun', 451, ['back', 'back', 'forward'], 100, [451, 452, 453, 454, 455, 456], 'sheath']
  ];
  for (const [weapon, pose, keys, cost, chain, posture] of cases) await t.test(`${weapon}/${pose}`, async () => {
    const { game, events } = await fixture([v(0, .015, 3), v(0, .015, 8), v(0, .015, 14)]);
    await game._equip(game.hero, weapon);
    if (posture === 'spear') { manual(game, ['left']); settle(game); }
    if (posture === 'sheath') { manual(game, ['back', 'back']); settle(game); }
    if (posture === 'air') {
      game.action('jump'); game.action('jump', false);
      // This source projectile travels forward at the caster's height. Test
      // airborne opponents with actual jumps instead of broadening it to a
      // fabricated ground-level damage area.
      for (const actor of game.enemies) game._beginJump(actor);
      for (let n = 0; n < 3; n++) tick(game);
    }
    game.hero.rage = 100; const firstEvent = events.length;
    manual(game, keys); assert.equal(game.hero.combat.currentMove?.poseId, pose);
    const seen = settle(game);
    for (const id of chain) assert.ok(seen.has(id), `missing automatic pose${id}`);
    const castEvents = events.slice(firstEvent), hits = castEvents.filter(e => e.type === 'hit' && chain.includes(e.poseId));
    assert.ok(hits.length, `no damage contacts for ${weapon}/${pose}; actor=${game.hero.root.position.toArray()}`);
    assert.ok(game.enemies.some(actor => actor.hp < 10000));
    assert.ok(hits.some(hit => hit.contactSource === 'effect'), 'special must use original EF attack volumes');
    assert.equal(castEvents.filter(e => e.type === 'move').length, 1);
    assert.equal(game.hero.rage, 100 - cost);
    assert.equal(game.wheels.size, 0, 'specials do not leave a normal returning disc blocking recovery');
    assert.equal(game.muskets.size || 0, 0);
    if (pose === 224) assert.ok(game.enemies.some(actor => actor.scriptItems?.some(item => item.id === 13)));
    manual(game, []); assert.equal(game.hero.combat.busy, true, 'the next normal attack must start');
    t.diagnostic(`${weapon}/${pose}: ${hits.length} source contacts; chain ${[...seen].join('→')}`);
  });
});

test('金钟罩 and 嗜血 finish on a miss, change real damage, refresh without stacking and clear on respawn', async t => {
  for (const [weapon, pose, keys, itemId, stat, value, duration] of [
    ['hammer', 567, ['back', 'forward', 'forward'], 40, 4, 20, 120],
    ['knuckle', 489, ['back', 'back', 'forward'], 34, 3, 40, 90]
  ]) await t.test(`${weapon}/${pose}`, async () => {
    const { game, events } = await fixture([v(0, .015, 50)]), actor = game.hero, target = game.enemies[0];
    await game._equip(actor, weapon);
    const context = () => stat === 3 ? { attacker: actor, target, poseId: 407 } : { attacker: target, target: actor, poseId: 262 };
    const before = game.damageResolver(context()); actor.rage = 100; manual(game, keys);
    assert.equal(actor.combat.currentMove.poseId, pose); assert.equal(actor.scriptItems.length, 0, 'no buff at input time');
    settle(game); assert.equal(target.hp, 10000, 'buff does not depend on hitting an enemy');
    assert.equal(actor.rage, 0); assert.equal(actor.scriptItems.length, 1); assert.equal(actor.scriptItems[0].id, itemId);
    assert.ok(actor.scriptItems[0].remaining >= duration - .21);
    assert.equal(nativeEffectiveStat(stat, 100, actor.activeItems), 100 + value);
    const after = game.damageResolver(context()); assert.ok(stat === 3 ? after > before : after < before);
    assert.equal(events.filter(e => e.type === 'self-item').length, 1, 'one completion applies the item once');
    actor.rage = 100; manual(game, keys); settle(game);
    assert.equal(actor.scriptItems.length, 1); assert.equal(actor.activeItems.filter(r => r.id === itemId).length, 1);
    assert.equal(nativeEffectiveStat(stat, 100, actor.activeItems), 100 + value);
    assert.equal(events.filter(e => e.type === 'self-item').at(-1).refreshed, true);
    game._placeFighter(actor, { position: v(0, .015, 0) });
    assert.equal(actor.scriptItems.length, 0); assert.equal(nativeEffectiveStat(stat, 100, actor.activeItems), 100);
  });
});

test('interruption and insufficient rage cannot grant self buffs, and wrong-mode qiankun input never becomes plain A', async () => {
  const { game, events } = await fixture([]), actor = game.hero;
  await game._equip(actor, 'knuckle'); actor.rage = 99; manual(game, ['back', 'back', 'forward']);
  assert.equal(actor.combat._attackChain, false); assert.equal(actor.combat.currentMove?.kind,'dash'); assert.equal(actor.rage, 99); assert.equal(actor.scriptItems.length, 0);
  actor.rage = 100; manual(game, ['back', 'back', 'forward']);
  actor.combat.react(103); settle(game); assert.equal(actor.scriptItems.length, 0);
  await game._equip(actor, 'qiankun'); actor.rage = 100;
  manual(game, ['back', 'back', 'forward']);
  assert.equal(actor.combat._attackChain, false); assert.equal(actor.combat.currentMove?.kind,'dash'); assert.equal(actor.rage, 100);
  assert.ok(events.some(e => /死斗需要拔刀式.*↓↓A/.test(e.text)));
  manual(game, ['back', 'forward']); assert.equal(actor.combat._attackChain, false); assert.equal(actor.combat.currentMove?.kind,'dash');
  assert.ok(events.some(e => /勾魂锁需要持枪式.*←A/.test(e.text)));
});

test('source wheel slow scales actual walking, expires, and rage loss uses the original immediate item', async () => {
  const { game } = await fixture([]), actor = game.hero;
  useNativeScriptItem(actor, data.itemRecords.get(13)); assert.equal(nativeMovementScale(actor), .3);
  game.action('forward'); for (let n = 0; n < 120; n++) tick(game); game.action('forward', false);
  assert.ok(Math.abs(actor.velocity.length()-nativeStrideSpeed(actor.character.nativeCharacterId??0,144)*.3)<1e-5);
  updateNativeScriptItems(actor, 60); assert.equal(nativeMovementScale(actor), 1);
  actor.rage = 3; useNativeScriptItem(actor, data.itemRecords.get(37)); assert.equal(actor.rage, 0);
  actor.rage = 100; useNativeScriptItem(actor, data.itemRecords.get(37)); assert.equal(actor.rage, 95);
  assert.equal(actor.scriptItems.length, 0, 'instant rage loss leaves no timed item');
  useNativeScriptItem(actor, data.itemRecords.get(13)); clearNativeScriptItems(actor); assert.equal(nativeMovementScale(actor), 1);
});

test('雷神锥真实飞镖命中施加原钝筋，刷新不叠加且移动恢复', async () => {
 const {game,events}=await fixture([v(0,0,5)]);await game._equip(game.hero,'dart');
 dartCommand(game,['forward'],209,0);for(let i=0;i<120;i++)tick(game);
 const target=game.enemies[0],hit=events.find(e=>e.type==='hit'&&e.poseId===209);
 assert.ok(hit?.projectileId);assert.equal(hit.raw.attackItem.id,10);assert.equal(nativeMovementScale(target),.5);
 assert.equal(target.scriptItems.filter(x=>x.id===10).length,1);
 useNativeScriptItem(target,data.itemRecords.get(10));assert.equal(target.scriptItems[0].remaining,15);assert.equal(nativeMovementScale(target),.5);
 updateNativeScriptItems(target,15.2);assert.equal(nativeMovementScale(target),1);
 useNativeScriptItem(game.hero,data.itemRecords.get(10));game.action('forward');for(let i=0;i<60;i++)tick(game);game.action('forward',false);
 assert.ok(Math.abs(game.hero.velocity.length()-nativeStrideSpeed(game.hero.character.nativeCharacterId??0,144)*.5)<1e-5);
 const guarded=await fixture([v(0,0,5)]);await guarded.game._equip(guarded.game.hero,'dart');guarded.game.enemies[0].scriptControl.guard=true;
 dartCommand(guarded.game,['forward'],209,0);for(let i=0;i<120;i++)tick(guarded.game);
 assert.ok(guarded.events.some(e=>e.type==='hit'&&e.poseId===209&&e.guarded));
 assert.equal(guarded.game.enemies[0].scriptItems.length,0);assert.equal(nativeMovementScale(guarded.game.enemies[0]),1);
});

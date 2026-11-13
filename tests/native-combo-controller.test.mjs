import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { decodeNativeText, parsePos, parseAct, NativeCombatController, NativePoseTimeline, createNativeDamageResolver } from '../dist/native-combat.js';

const poses = parsePos(decodeNativeText(await readFile(new URL('../dist/assets/native/combat/P0.POS', import.meta.url))));
const actions = parseAct(decodeNativeText(await readFile(new URL('../dist/assets/native/combat/character.act', import.meta.url))));
const records = JSON.parse(await readFile(new URL('../dist/assets/original/characters/meteor-res-data.json', import.meta.url), 'utf8')).allRecords;
const data = { poses, actions, moveRecords: new Map(records.filter(r => r.type === 3).map(r => [r.id, r])), weaponRecords: new Map(records.filter(r => r.type === 1).map(r => [r.model.toLowerCase(), r])) };
const controller = (weapon = 'sword', options = {}) => new NativeCombatController(data, { weapon, ...options });

test('the attackless sword dive startup reaches and holds its source one-frame attack until ground contact', () => {
  const combat = controller();
  assert.equal(poses.get(265).attacks.length, 0);
  assert.equal(poses.get(265).link, 342);
  assert.equal(combat.attack({ air: true, poseId: 265 }), true);
  assert.equal(combat.busy, true, 'movement must not replace this attackless startup');
  assert.equal(combat.attacking, false);
  let state = combat.update(.4, { grounded: false });
  assert.equal(state.poseId, 342);
  assert.equal(state.pose.loopStart, 9882);
  assert.ok(state.frame >= 9882 && state.frame < 9883);
  for (let i = 0; i < 120; i++) {
    state = combat.update(1 / 60, { grounded: false });
    assert.equal(combat.busy, true);
    assert.equal(state.poseId, 342);
    assert.equal(state.attacks.length, state.blend ? 0 : 1, 'the source contact window starts after the native linked blend completes');
    if (!state.blend) assert.equal(state.attacks[0].index, 0);
  }
  state = combat.update(2, { grounded: true });
  assert.equal(state.finished, true);
  assert.equal(combat.busy, false);
});

test('the blade automatic chain preserves attackless stages and every original attack segment', () => {
  const combat = controller('blade'), context = { id: 'blade-rage', cost: 100 }; let paid = 0;
  assert.equal(combat.attack({ poseId: 310, context, onStart: () => paid++ }), true);
  const state = combat.update(20, { grounded: true });
  assert.deepEqual(state.segments.filter(s => !s.blend).map(s => s.poseId), [310, 311, 312, 313, 314, 331]);
  assert.equal(state.segments.find(s => s.poseId === 311).attacks.length, 0);
  assert.deepEqual(state.segments.filter(s => s.attacks.length).map(s => s.poseId), [310, 312, 313, 331]);
  assert.deepEqual(state.segments.filter(s => !s.blend).map(s => s.serial), [1, 2, 3, 4, 5, 6]);
  assert.ok(state.segments.every(s => s.context === context));
  assert.equal(paid, 1, 'linked animation stages do not charge another attack cost');
  assert.equal(combat.busy, false);
});

test('a buffered input keeps the old Action then uses native NextPose time before entering the next Action', () => {
  const combat = controller(); let rage = 50, paid = 0;
  combat.attack({ poseId: 262 });
  const context = { id: 'sword-second', cost: 40 };
  assert.equal(combat.attack({ poseId: 263, context, canStart: move => rage >= move.cost, onStart: move => { rage -= move.cost; paid++; } }), true);
  assert.equal(combat.queued, 263);
  assert.equal(combat.queuedMove, context);
  assert.equal(rage, 50);
  const state = combat.update(1, { grounded: true });
  const old=state.segments.filter(segment=>segment.poseId===262),incoming=state.segments.find(segment=>segment.poseId===263&&segment.blend);
  assert.deepEqual(old.map(segment=>segment.frame),[9767,9777], 'accept at NextPose.Start, keep old Action until compiled first Blend');
  assert.ok(old.some(segment=>segment.attacks.length>0), 'the current source strike is preserved across the acceptance boundary');
  assert.equal(incoming.blend.duration, .2);
  assert.equal(incoming.frame, 9806, 'native first Action; skip incoming pre-Action Blend frames');
  assert.equal(combat.currentMove, context);
  assert.equal(combat.queuedMove, null);
  assert.equal(rage, 10);
  assert.equal(paid, 1);
});

test('a queued resource gate is rechecked when its pose starts and cannot overspend changed resources', () => {
  const combat = controller(); let rage = 50, paid = 0;
  combat.attack({ poseId: 262 });
  const serial = combat.serial;
  combat.attack({ poseId: 263, context: { cost: 40 }, canStart: move => rage >= move.cost, onStart: move => { rage -= move.cost; paid++; } });
  rage = 0;
  const state = combat.update(.6, { grounded: true });
  assert.equal(combat.serial, serial);
  assert.equal(state.poseId, 262);
  assert.equal(combat.queued, null);
  assert.equal(rage, 0);
  assert.equal(paid, 0);
});

test('death, weapon switching and an explicit failed start discard queued costs without a charge', () => {
  for (const interrupt of [combat => combat.play(117, { force: true }), combat => combat.setWeapon('blade')]) {
    const combat = controller(); let paid = 0;
    combat.attack({ poseId: 262 });
    combat.attack({ poseId: 263, context: { cost: 100 }, onStart: () => paid++ });
    interrupt(combat);
    combat.update(2, { grounded: true });
    assert.equal(combat.queuedMove, null);
    assert.equal(paid, 0);
    assert.equal(combat.busy, false);
  }
  const combat = controller();
  assert.equal(combat.attack({ poseId: 277, onStart: () => false }), false);
  assert.equal(combat.serial, 0);
  assert.equal(combat.timeline, null);
});

test('a held air recovery retains its real ACT continuation but cannot receive a forbidden ground attack', () => {
  const combat = controller();
  combat.attack({ air: true, poseId: 260 });
  combat.update(.7, { grounded: false });
  assert.equal(combat.timeline.pose.id, 340);
  assert.equal(combat.busy, true);
  assert.equal(actions.canLink(260, 277), false);
  assert.equal(combat.attack({ poseId: 277 }), false);
  assert.equal(combat.attack({ air: true }), true);
  assert.equal(combat.timeline.pose.id, 261);
});

test('finishing a basic attack resets the next click to its first move rather than reviving an expired continuation', () => {
  const combat = controller();
  combat.attack(); combat.update(3, { grounded: true });
  assert.equal(combat.busy, false);
  combat.attack();
  assert.equal(combat.timeline.pose.id, 262);
});

test('automatic links preserve elapsed time and root deltas across coarse and fine frame partitions', () => {
  const sampleRoot = (_source, frame) => ({ x: frame, y: 0, z: 0 });
  const coarse = controller('blade', { sampleRoot }), fine = controller('blade', { sampleRoot });
  coarse.attack({ poseId: 374 }); fine.attack({ poseId: 374 });
  const one = coarse.update(4, { grounded: true });
  let sum = 0;
  for (let i = 0; i < 400; i++) for (const state of fine.update(.01, { grounded: true }).segments) sum += state.rootDelta.x;
  assert.equal(coarse.timeline.pose.id, fine.timeline.pose.id);
  assert.equal(coarse.timeline.finished, fine.timeline.finished);
  // Compiled native phase speeds are float32. Compare at native precision
  // rather than requiring identical double rounding across400 partitions.
  assert.ok(Math.abs(one.segments.reduce((total, state) => total + state.rootDelta.x, 0) - sum) < 1e-6);
  assert.deepEqual(one.segments.filter(s => !s.blend).map(s => s.poseId), [374, 375]);
});

function contactFixture(weapon) {
  const point = new THREE.Object3D(); point.position.y = 1.35;
  const attacker = { hero: true, id: 0, root: new THREE.Group(), weapon, attackHits: new Set(), character: { getAttachment: () => point }, teamMask: 1 };
  const target = { hero: false, id: 1, root: new THREE.Group(), hp: 10000, rage: 0, contacts: 0, dead: false, guard: false, weapon: 'sword', teamMask: 2 };
  const game = Object.create(MeteorGame.prototype);
  Object.assign(game, { running: true, mode: 'training', enemies: [target], combatData: data, contactHits: 0, totalDamage: 0, damageResolver: createNativeDamageResolver(data), _emit() {}, _soundDefinition() {}, _hud() {} });
  return { game, attacker, target };
}

test('sword rapid thrust applies all five original windows to one overlapping opponent and never repeats a window', () => {
  const combat = controller(), { game, attacker, target } = contactFixture('sword');
  combat.attack({ poseId: 277 }); let lastSerial = -1;
  for (let i = 0; i < 360; i++) for (const state of combat.update(1 / 60, { grounded: true }).segments) {
    if (state.serial !== lastSerial) { attacker.attackHits.clear(); lastSerial = state.serial; }
    game._resolveContacts(attacker, state);
    game._resolveContacts(attacker, state);
  }
  assert.equal(poses.get(277).attacks.length, 5);
  assert.equal(target.contacts, 5);
  assert.equal(game.contactHits, 5);
  const damage = createNativeDamageResolver(data)({ attacker, target, poseId: 277 });
  assert.equal(target.hp, 10000 - damage * 5);
  assert.equal(game.totalDamage, damage * 5);
});

test('both original blade spin stages can damage the same overlapping opponent when a single update spans their link', () => {
  const combat = controller('blade'), { game, attacker, target } = contactFixture('blade');
  combat.attack({ poseId: 374 });
  const state = combat.update(8, { grounded: true });
  for (const segment of state.segments) { attacker.attackHits.clear(); game._resolveContacts(attacker, segment); }
  assert.equal(target.contacts, 2);
  const damage = createNativeDamageResolver(data)({ attacker, target, poseId: 374 }) + createNativeDamageResolver(data)({ attacker, target, poseId: 375 });
  assert.equal(target.hp, 10000 - damage);
});

test('holding the one-frame sword dive does not create repeat hits on the same target', () => {
  const combat = controller(), { game, attacker, target } = contactFixture('sword');
  combat.attack({ poseId: 265 }); let serial = -1;
  for (let i = 0; i < 120; i++) for (const segment of combat.update(1 / 60, { grounded: false }).segments) {
    if (segment.serial !== serial) { attacker.attackHits.clear(); serial = segment.serial; }
    game._resolveContacts(attacker, segment);
  }
  assert.equal(target.contacts, 1);
});

test('a timeline advanced across its final attack frame still reports that native contact window', () => {
  const timeline = new NativePoseTimeline(poses.get(331));
  const state = timeline.advance(4);
  assert.equal(state.finished, true);
  assert.equal(state.attacks.length, 1);
  assert.equal(timeline.advance(.1).attacks.length, 0);
});

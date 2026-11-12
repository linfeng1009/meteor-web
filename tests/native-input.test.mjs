import test from 'node:test';
import assert from 'node:assert/strict';
import { NATIVE_MOVE_CATALOG } from '../dist/native-move-catalog.js';
import { recordNativeDirection, selectNativeMove } from '../dist/native-input.js';

function taps(input, { start = 10, gap = .12, air = false } = {}) {
  let buffer = [], time = start;
  for (const direction of input.filter(key => key !== 'attack')) {
    buffer = recordNativeDirection(buffer, direction, time, air); time += gap;
  }
  return { buffer, time };
}
const select = options => selectNativeMove(NATIVE_MOVE_CATALOG, options);

test('every catalog command selects its original pose with its required stance and predecessor', () => {
  for (const move of NATIVE_MOVE_CATALOG) {
    const options = { weapon: move.weapon, weaponMode: move.weaponMode, air: move.stance === 'air', ...taps(move.input, { air: move.stance === 'air' }),
      busy: !!move.continuationOf, poseId: move.continuationOf?.[0] };
    assert.equal(select(options)?.id, move.id, move.command + ' ' + move.weapon);
    for (const input of move.alternateInputs || []) assert.equal(select({ ...options, ...taps(input, { air: move.stance === 'air' }) })?.id, move.id, 'documented alternate ' + move.id);
  }
});

test('three-direction commands win over two-direction and single-direction suffixes', () => {
  for (const [weapon, input, poseId] of [
    ['sword', ['down', 'up', 'up'], 277], ['spear', ['left', 'right', 'up'], 292],
    ['spear', ['up', 'up', 'up'], 571], ['blade', ['left', 'right', 'up'], 309]
  ]) {
    const state = taps(['left', ...input]);
    assert.equal(select({ weapon, ...state, held: [input.at(-1)] })?.poseId, poseId);
  }
  assert.equal(select({ weapon: 'blade', ...taps(['left', 'right']) })?.poseId, 374);
  assert.equal(select({ weapon: 'blade', ...taps(['right', 'left']) })?.poseId, 572);
});

test('slow, stale and opposite-posture taps cannot fabricate a long command', () => {
  assert.equal(select({ weapon: 'sword', ...taps(['down', 'up', 'up'], { gap: .6 }) })?.poseId, 262);
  const stale = taps(['down', 'up', 'up']);
  assert.equal(select({ weapon: 'sword', ...stale, time: stale.time + 2 })?.poseId, 262);
  assert.equal(select({ weapon: 'sword', air: true, ...taps(['down'], { air: false }) })?.poseId, 260);
  assert.equal(select({ weapon: 'sword', air: true, ...taps(['down'], { air: true }) })?.poseId, 265);
});

test('held movement supports a single directional attack without inventing a diagonal sequence', () => {
  assert.equal(select({ weapon: 'sword', time: 20, held: ['down'] })?.poseId, 267);
  assert.equal(select({ weapon: 'sword', time: 20, held: ['down', 'up'] })?.poseId, 262);
  assert.equal(select({ weapon: 'blade', time: 20, held: ['left', 'right'] })?.poseId, 295);
});

test('follow-ups need an active predecessor, including its actual linked air recovery', () => {
  assert.equal(select({ weapon: 'sword', time: 10, poseId: 267, busy: false })?.poseId, 262);
  assert.equal(select({ weapon: 'sword', time: 10, poseId: 267, busy: true })?.poseId, 268);
  assert.equal(select({ weapon: 'sword', air: true, time: 10, poseId: 340, movePoseId: 260, busy: true })?.poseId, 261);
  assert.equal(select({ weapon: 'dagger', time: 10, poseId: 249, busy: true })?.poseId, 248, 'third plain A must not become ↑A');
});

test('long specials preserve their selected command and its actual readiness instead of degrading to a suffix', () => {
  const ready = select({ weapon: 'dart', ...taps(['down', 'up', 'up']) });
  assert.equal(ready.poseId, 203); assert.equal(ready.pending, undefined);
  assert.notEqual(ready.poseId, 209, 'must not silently degrade the special to ↑A');
  const golden = select({ weapon: 'hammer', ...taps(['down', 'up', 'up']) });
  assert.equal(golden.poseId, 567); assert.equal(golden.pending, undefined);
  const pending = select({ weapon: 'dual', ...taps(['down', 'down', 'up']) });
  assert.equal(pending.poseId, 557); assert.equal(pending.pending,undefined,'乘风 now uses its original deferred speed item');
});

test('wrong-mode recognition preserves a full qiankun special and prioritizes the current mode on identical inputs', () => {
  const opts = { weapon: 'qiankun', includeOtherModes: true };
  assert.equal(select({ ...opts, ...taps(['down', 'down', 'up']) }).poseId, 451);
  assert.equal(select({ ...opts, ...taps(['down', 'up']) }).poseId, 570);
  assert.equal(select({ ...opts, weaponMode: 'sheath', ...taps(['down', 'up']) }).poseId, 449);
  assert.equal(select({ ...opts, weaponMode: 'spear', ...taps(['up', 'up']) }).poseId, 444);
});

import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { NativeNpcCombat, nativeNpcChoice, nativeNpcInterval, nativeNpcMove, nativeNpcInRange, nativeNpcFacing } from '../dist/native-npc-combat.js';
import * as THREE from '../dist/vendor/three.module.js';
import { NativeCombatController, parseAct, parsePos, decodeNativeText } from '../dist/native-combat.js';

const data = JSON.parse(await readFile(new URL('../dist/assets/original/npc-ai/manifest.json', import.meta.url), 'utf8'));
const draws = (...values) => { let index = 0; return () => (values[Math.min(index++, values.length - 1)] || 0) / 32768; };
const poses = parsePos(decodeNativeText(await readFile(new URL('../dist/assets/native/combat/P0.POS', import.meta.url))));
const actions = parseAct(decodeNativeText(await readFile(new URL('../dist/assets/native/combat/character.act', import.meta.url))));
function actor(weapon = 'sword') { return { root: new THREE.Group(), weapon, grounded: true, combat: new NativeCombatController({ poses, actions }, { weapon }) }; }

test('source NPC asset contains all twelve distinct weapon tables,36 vectors and127 ground programs', () => {
  assert.equal(data.source.sampleSha256, '289afb0aa44a47921d167fc24d6d404c60d6d00c299ac27d45fc61e16231b498');
  assert.equal(Object.keys(data.profiles).length, 12); assert.equal(data.airCommands.length, 17);
  assert.equal(Object.values(data.profiles).flatMap(row => row.commands).length, 36);
  assert.equal(Object.values(data.profiles).flatMap(row => row.commands.flat()).length, 127);
  assert.deepEqual(data.profiles.spear.commands, [[''], ['b', 'f', 'rl', 'bb'], ['bf', 'ff', 'lr', 'bbf', 'lrf', 'fff', 'lrb', 'bff']]);
  assert.deepEqual(data.profiles.musket.commands, [[''], ['f', 'b'], ['bf', 'bff']]);
  assert.ok(data.profiles.ninja.commands[2].includes('lrfb'));
  assert.equal(data.airCommands.filter(command => command === '').length, 7);
  for (const row of Object.values(data.profiles)) for (const group of row.commands) for (const program of group) assert.match(program, /^[fblr]*$/);
});

test('source action gate and attack category use independent100-way rolls, including unnormalized remainder', () => {
  const config = { Guard: 20, Attack1: 50, Attack2: 20, Attack3: 5 }, counts = { guard: 0, attack0: 0, attack1: 0, attack2: 0, wait: 0 };
  for (let roll = 0; roll < 100; roll++) for (let category = 0; category < 100; category++) {
    const c = nativeNpcChoice(config, roll, category); counts[c.kind === 'attack' ? `attack${c.category}` : c.kind]++;
  }
  assert.deepEqual(counts, { guard: 2000, attack0: 3750, attack1: 1500, attack2: 2250, wait: 500 });
  assert.equal(nativeNpcChoice({ Guard: 100, Attack1: 100, Attack2: 100, Attack3: 100 }, 99, 99).kind, 'guard');
  assert.deepEqual(nativeNpcChoice({ Guard: 0, Attack1: 0, Attack2: 100, Attack3: 0 }, 99, 99), { kind: 'attack', category: 1 });
});

test('source defense delays the next decision, and angle rejection consumes no command/category draw', () => {
  let calls = 0;
  const brain = new NativeNpcCombat(data, { random: () => { calls++; return 0; } }), f = actor();
  f.scriptConfig = { Guard: 100 }; assert.equal(brain.choose(f).kind, 'guard'); assert.equal(brain.baseDelay, Math.fround(.4));
  assert.equal(calls, 2); f.scriptConfig = { Guard: 0, Attack1: 100 };
  assert.equal(brain.choose(f, { canAttack: () => false }).kind, 'wait'); assert.equal(calls, 3);
});

test('native weapon decision range is separate from damage geometry and preserves the strict boundary and angle gate', () => {
  const f = actor('sword'), target = actor(), profile = data.profiles.sword;
  target.root.position.z = 4.8 - 1e-6; assert.equal(nativeNpcInRange(f, target, profile), true);
  target.root.position.z = 4.8; assert.equal(nativeNpcInRange(f, target, profile), false);
  f.grounded = false; assert.equal(nativeNpcInRange(f, target, profile), true);
  target.root.position.z = 4.8 * Math.sqrt(3) + 1e-6; assert.equal(nativeNpcInRange(f, target, profile), false);
  target.root.position.set(0, 0, 1); f.root.rotation.y = 29 * Math.PI / 180; assert.equal(nativeNpcFacing(f, target, profile), true);
  f.root.rotation.y = 31 * Math.PI / 180; assert.equal(nativeNpcFacing(f, target, profile), false);
  f.root.rotation.y = Math.PI * 2; assert.equal(nativeNpcFacing(f, target, profile), true);
  target.root.position.z = 160; assert.equal(nativeNpcInRange(f, target, data.profiles.musket), false, 'ranged weapons do not get the airborne distance multiplier');
});

test('native Think scales the source base delay and clamps the low speed without fabricating a cooldown range', () => {
  const base = Math.fround(.2);
  assert.ok(Math.abs(nativeNpcInterval(base, { Think: 40 }) - .5) < 1e-6);
  assert.ok(Math.abs(nativeNpcInterval(base, { Think: 100 }) - .2) < 1e-6);
  assert.ok(Math.abs(nativeNpcInterval(base, { Think: 0 }) - 2) < 1e-6);
  assert.equal(nativeNpcInterval(base, { Think: -100 }), nativeNpcInterval(base, { Think: 0 }));
  assert.equal(nativeNpcInterval(Math.fround(.4), { Think: 40 }), 2 * nativeNpcInterval(base, { Think: 40 }));
});

test('NPC clock preserves randomized source startup, one decision per update, pause and dropped overshoot', () => {
  const slow = new NativeNpcCombat(data, { random: draws(999) }), fast = new NativeNpcCombat(data, { random: draws(0) });
  assert.equal(slow.baseDelay, Math.fround(999 * Math.fround(.0005)));
  assert.equal(fast.advance(.01, { Think: 100 }, { hasTarget: true }), false, 'source discovery enters pursuit before it can choose an attack');
  assert.equal(fast.baseDelay, Math.fround(.4));
  assert.equal(slow.advance(.01, { Think: 100 }, { hasTarget: true }), false);
  const elapsed = slow.elapsed; assert.equal(slow.advance(10, { Think: 100 }, { paused: true }), false); assert.equal(slow.elapsed, elapsed);
  assert.equal(fast.advance(10, { Think: 100 }, { hasTarget: true }), true); assert.equal(fast.elapsed, 0); assert.equal(fast.baseDelay, Math.fround(.2));
  assert.equal(fast.advance(.01, { Think: 100 }, { hasTarget: true }), false, 'a stalled frame must not emit a backlog of attacks');
});

test('source fifty-percent repetition retains previous category/index and clamps it after weapon changes', () => {
  const brain = new NativeNpcCombat(data, { random: draws(0, 1, 2, 0, 0) });
  assert.equal(brain.command('sword', 1), 'l'); assert.equal(brain.category, 1); assert.equal(brain.index, 2);
  assert.equal(brain.command('sword', 2), 'l', 'repeat uses the previous category rather than the newly requested one');
  assert.equal(brain.command('musket', 0), 'b'); assert.equal(brain.category, 1); assert.equal(brain.index, 1);
});

test('native controllerstate0 selects the distinct original17-entry air program table without changing ground memory', () => {
  const brain = new NativeNpcCombat(data, { random: draws(0, 8) });
  assert.equal(brain.command('spear', 2, true), 'fb'); assert.equal(brain.category, 0); assert.equal(brain.index, 0);
});

test('NPC direction programs use actual catalog roots, prerequisites and existing ACT continuation gates', () => {
  const f = actor('dagger');
  assert.equal(nativeNpcMove(f, 'f').poseId, 250);
  f.combat.attack({ poseId: 250 }); assert.equal(nativeNpcMove(f, 'f').poseId, 251);
  const spear = actor('spear'); assert.equal(nativeNpcMove(spear, 'bff').poseId, 293); assert.equal(nativeNpcMove(spear, 'fff').poseId, 571);
  assert.equal(nativeNpcMove(actor('hammer'), 'bff').poseId, 567);
  assert.equal(nativeNpcMove(actor('hammer'), 'bff').pending, undefined);
  assert.equal(nativeNpcMove(actor('dual'), 'bbf').pending, undefined, '乘风 is available to the same NPC resource gate');
  assert.equal(nativeNpcMove(f, 'invented-program'), null);
});

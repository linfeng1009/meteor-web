import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { decodeNativeText, parsePos, createNativeDamageResolver } from '../dist/native-combat.js';

const poses = parsePos(decodeNativeText(await readFile(new URL('../dist/assets/native/combat/P0.POS', import.meta.url))));
const records = JSON.parse(await readFile(new URL('../dist/assets/original/characters/meteor-res-data.json', import.meta.url), 'utf8')).allRecords;
const data = { poses, moveRecords: new Map(records.filter(r => r.type === 3).map(r => [r.id, r])), weaponRecords: new Map(records.filter(r => r.type === 1).map(r => [r.model.toLowerCase(), r])) };
function fixture(weapon) {
  const models = { blade: 'w5_0', spear: 'w7_0' }, events = [], sounds = [];
  const attacker = { hero: true, id: 0, root: new THREE.Group(), weapon, weaponId: weapon === 'blade' ? 8 : 7, teamMask: 1, nativeStats: {}, activeItems: [], weaponRecord: data.weaponRecords.get(models[weapon]) };
  const target = { hero: false, id: 1, root: new THREE.Group(), weapon: 'spear', weaponId: 7, teamMask: 2, hp: 1000, rage: 0, contacts: 0, guard: true, dead: false, nativeStats: {}, activeItems: [], weaponRecord: data.weaponRecords.get('w7_0') };
  const game = Object.create(MeteorGame.prototype);
  Object.assign(game, { running: true, mode: 'training', combatData: data, damageResolver: createNativeDamageResolver(data), contactHits: 0, totalDamage: 0,
    _emit: (text, type, amount, point, extra) => events.push({ text, type, amount, ...extra }), _soundDefinition: name => sounds.push(name), _hud() {} });
  return { game, attacker, target, events, sounds };
}
function hit(fixture, poseId, attack = poses.get(poseId).attacks[0]) {
  return fixture.game._applyNativeHit(fixture.attacker, fixture.target, { poseId, pose: poses.get(poseId) }, attack, new THREE.Vector3(0, 1.35, 0));
}

test('an original type-zero blade strike remains guarded with no HP loss and the native guard-rage branch', () => {
  const f = fixture('blade'); assert.equal(poses.get(295).attacks[0].attacktype, 0);
  hit(f, 295);
  assert.equal(f.target.hp, 1000); assert.equal(f.target.rage, 1);
  assert.equal(f.game.totalDamage, 0); assert.equal(f.target.contacts, 1);
  assert.equal(f.events[0].guardBypassed, false); assert.match(f.sounds[0], /^W05GD/);
  f.target.guard = false; hit(f, 295);
  assert.equal(f.target.hp, 956, 'same original move deals44 when the guard condition is absent');
  assert.match(f.sounds[1], /^W05BL/);
});

for (const [weapon, poseId, expected] of [['blade', 298, 89], ['blade', 300, 50], ['spear', 286, 37], ['spear', 291, 122]]) {
  test(`original ${weapon} pose${poseId} type-one attack bypasses a raised guard and deals${expected}`, () => {
    const f = fixture(weapon), attack = poses.get(poseId).attacks[0]; assert.equal(attack.attacktype, 1);
    assert.equal(hit(f, poseId), true);
    assert.equal(f.target.hp, 1000 - expected);
    assert.equal(f.game.totalDamage, expected);
    assert.equal(f.target.rage, Math.floor(14 * expected / 100));
    assert.equal(f.events[0].guardBypassed, true);
    assert.equal(f.events[0].raw.attackType, 1);
    assert.match(f.sounds[0], /BL/);
    assert.equal(f.target.guard, true, 'this HP branch does not invent a separate persistent guard-state transition');
  });
}

test('guard recognition matches the original six-bit packet field rather than testing only the literal value one', () => {
  for (const [type, expected] of [[undefined, 0], [null, 0], [0, 0], [1, 44], [2, 44], [63, 44], [64, 0], [65, 44]]) {
    const f = fixture('blade'); hit(f, 295, { ...poses.get(295).attacks[0], attacktype: type });
    assert.equal(1000 - f.target.hp, expected, `attacktype=${type}`);
    assert.equal(f.events[0].guardBypassed, expected !== 0);
  }
});

test('both original spear-spin type-one windows bypass guard using the same recovered damage path', () => {
  const f = fixture('spear'); assert.equal(poses.get(286).attacks.length, 2);
  for (const attack of poses.get(286).attacks) hit(f, 286, attack);
  assert.equal(f.target.hp, 926); assert.equal(f.game.totalDamage, 74);
  assert.equal(f.events.length, 2); assert.ok(f.events.every(e => e.guardBypassed));
});

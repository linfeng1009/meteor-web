import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { NATIVE_MOVE_CATALOG, NATIVE_WEAPON_FAMILIES, getNativeMoves } from '../dist/native-move-catalog.js';
import { parsePos, parseAct, decodeNativeText } from '../dist/native-combat.js';
import { NATIVE_DART_PROFILE, NATIVE_MUSKET_PROFILE, NATIVE_WHEEL_PROFILE } from '../dist/native-projectiles.js';
import { nativeEffectBounds } from '../dist/native-effect-contacts.js';

const poseBytes = await readFile(new URL('../dist/assets/native/combat/P0.POS', import.meta.url));
const actBytes = await readFile(new URL('../dist/assets/native/combat/character.act', import.meta.url));
const records = JSON.parse(await readFile(new URL('../dist/assets/original/characters/meteor-res-data.json', import.meta.url), 'utf8'));
const poses = parsePos(decodeNativeText(poseBytes));
const actions = parseAct(decodeNativeText(actBytes));
const effectManifest = JSON.parse(await readFile(new URL('../dist/assets/original/rage-vfx/manifest.json', import.meta.url), 'utf8'));
const moveRecords = new Map(records.allRecords.filter(record => record.type === 3).map(record => [record.id, record]));
const byPose = (weapon, id) => getNativeMoves(weapon).find(move => move.poseId === id);

test('every advertised manual command addresses preserved native animation and RES data', () => {
  const ids = new Set();
  for (const move of NATIVE_MOVE_CATALOG) {
    assert.ok(!ids.has(move.id), `duplicate ${move.id}`); ids.add(move.id);
    assert.ok(poses.get(move.poseId)?.valid, `${move.id}: real source frames`);
    assert.ok(moveRecords.has(move.poseId), `${move.id}: original damage/stat record`);
    assert.equal(move.input.at(-1), 'attack');
    assert.ok(move.input.every(key => ['up', 'down', 'left', 'right', 'attack'].includes(key)));
    for (const from of move.continuationOf || []) {
      assert.ok(actions.canLink(from, move.poseId) || poses.get(from)?.link === move.poseId,
        `${from} → ${move.poseId}: claimed follow-up must exist in ACT or automatic POS Link`);
    }
    // Some native entry phases are a wind-up without attacks (e.g. sword 265).
    // Require a real attack in its local automatic chain instead of inventing one.
    let pose = poses.get(move.poseId), foundAttack = false; const seen = new Set();
    while (pose && !seen.has(pose.id)) {
      seen.add(pose.id); foundAttack ||= pose.attacks.length > 0;
      pose = poses.get(pose.link);
    }
    assert.ok(foundAttack || move.kind === 'movement' && move.pending, `${move.id}: source attack or explicitly pending movement`);
  }
});

test('the requested blade spin, sword flurry, spear circles and airborne stabs use distinct original poses', () => {
  assert.deepEqual(byPose('blade', 374).input, ['left', 'right', 'attack']);
  assert.equal(byPose('blade', 374).rage, 0);
  assert.equal(poses.get(374).link, 375);
  assert.match(poses.get(374).label, /刀.*旋風/);
  assert.deepEqual(byPose('sword', 277).input, ['down', 'up', 'up', 'attack']);
  assert.equal(byPose('sword', 277).rage, 0);
  assert.equal(poses.get(277).attacks.length, 5, 'five independently preserved thrust windows');
  assert.deepEqual(byPose('spear', 290).input, ['left', 'right', 'attack']);
  assert.deepEqual(byPose('spear', 292).input, ['left', 'right', 'up', 'attack']);
  for (const [weapon, id] of [['dagger', 252], ['sword', 265], ['spear', 282], ['blade', 298]]) {
    const move = byPose(weapon, id);
    assert.equal(move.stance, 'air');
    assert.deepEqual(move.input, ['down', 'attack']);
  }
  assert.equal(poses.get(265).attacks.length, 0);
  assert.equal(poses.get(265).link, 342);
  assert.ok(poses.get(342).attacks.length > 0, 'sword stab damage belongs to the linked descent, not its wind-up');
});

test('separate source command tables resolve the ambiguous spear and blade pose-reference rows', () => {
  assert.deepEqual(byPose('spear', 286).input, ['right', 'left', 'attack']);
  assert.deepEqual(byPose('spear', 290).input, ['left', 'right', 'attack']);
  assert.ok(poses.get(286).attacks.every(attack => attack.attacktype === 1));
  assert.ok(poses.get(290).attacks.every(attack => attack.attacktype === 0));
  assert.deepEqual(byPose('blade', 572).input, ['right', 'left', 'attack']);
  assert.equal(byPose('blade', 572).rage, 60);
  assert.equal(poses.get(572).link, 573);
  assert.equal(byPose('blade', 374).rage, 0);
});

test('ordinary chains and conditional second stages preserve their distinct command prerequisites', () => {
  assert.deepEqual(getNativeMoves('dagger').filter(move => move.stance === 'ground' && move.input.join() === 'attack').map(move => move.poseId), [248, 249]);
  assert.deepEqual(byPose('dagger', 251).continuationOf, [250]);
  assert.deepEqual(byPose('sword', 268).continuationOf, [267]);
  assert.deepEqual(byPose('sword', 273).continuationOf, [272]);
  assert.deepEqual(byPose('sword', 276).continuationOf, [275]);
  assert.deepEqual(byPose('blade', 304).continuationOf, [303]);
  assert.deepEqual(byPose('blade', 307).continuationOf, [306]);
  assert.deepEqual(byPose('spear', 283).continuationOf, [282]);
  assert.deepEqual(byPose('dagger', 251).alternateInputs, [['attack']]);
  assert.equal(byPose('dagger', 258), undefined, '257→258 is automatic, not a fabricated second manual command');
  assert.equal(byPose('dagger', 371), undefined, '370→371 is automatic, not a fabricated second manual command');
  for (const weapon of ['spear', 'blade']) assert.equal(getNativeMoves(weapon).find(move => move.stance === 'air' && move.input.join() === 'attack').poseId, 338);
});

test('catalog scope and unresolved projectile commands are explicit rather than silently substituted', () => {
  assert.equal(NATIVE_WEAPON_FAMILIES.length, 12);
  assert.deepEqual(NATIVE_WEAPON_FAMILIES.filter(weapon => weapon.available).map(weapon => weapon.id).sort(), ['blade', 'dagger', 'dart', 'dual', 'hammer', 'knuckle', 'musket', 'ninja', 'qiankun', 'spear', 'sword', 'wheel']);
  const pending = NATIVE_MOVE_CATALOG.filter(move => move.pending);
  assert.equal(NATIVE_MOVE_CATALOG.length, 196); assert.equal(pending.length, 14);
  assert.equal(byPose('dual',557).pending,undefined);
  for (const [weapon, ids] of [['hammer', [567, 325]], ['musket', [215, 216]], ['wheel', [552, 224, 554]], ['knuckle', [416, 489]], ['qiankun', [570]]])
    for (const id of ids) assert.equal(byPose(weapon, id).pending, undefined, `${weapon}-${id}`);
  for (const poseId of [201, 203, 551]) assert.equal(byPose('dart', poseId).pending, undefined);
  for (const move of pending) assert.ok(move.rage > 0 || move.kind === 'movement' || ['knuckle-412', 'knuckle-413', 'ninja-470'].includes(move.id), move.id);
  assert.deepEqual(poses.get(259).attacks.map(attack => attack.bones), [['effect']], '阎罗 cannot damage through a fabricated weapon hit');
  assert.equal(byPose('dagger', 259).pending, undefined);
  assert.match(byPose('dagger', 343).notes, /第二段.*effect窗推开/);
  assert.equal(getNativeMoves('dart').some(move => move.stance === 'air' && move.input.join() === 'down,attack'), false,
    'the original dart table has no air down-A stab');
  const starters = new Set();
  for (const move of NATIVE_MOVE_CATALOG.filter(move => !move.continuationOf)) {
    const key = `${move.weapon}/${move.weaponMode || 'all'}/${move.stance}/${move.input.join()}`;
    assert.ok(!starters.has(key), `ambiguous starter ${key}`); starters.add(key);
  }
});

test('every usable command has a source bone, projectile or supported original effect bound, including its automatic phases', () => {
  for (const move of NATIVE_MOVE_CATALOG.filter(move => !move.pending)) {
    const chain = [], visited = new Set(); let pose = poses.get(move.poseId);
    while (pose && !visited.has(pose.id)) {
      visited.add(pose.id); chain.push(pose); pose = poses.get(pose.link);
    }
    const nativeContact = chain.some(pose => pose.attacks.some(attack => attack.bones.some(bone => bone !== 'effect')));
    const emitter = { dart: NATIVE_DART_PROFILE, musket: NATIVE_MUSKET_PROFILE, wheel: NATIVE_WHEEL_PROFILE }[move.weapon];
    const implementedEmitter = emitter && chain.some(pose => emitter.poseIds.includes(pose.id));
    const sourceEffect = chain.some(pose => pose.attacks.some(attack => attack.bones.includes('effect')) &&
      effectManifest.effects[String(pose.raw.fields.effectid).toLowerCase()]?.nodes.some(node => /^[aA]/.test(node.name) && nativeEffectBounds(node)));
    assert.ok(nativeContact || implementedEmitter || sourceEffect, `${move.id}: an unsupported pure effect cannot be advertised as a functioning hit`);
  }
  assert.ok(poses.get(343).attacks[0].bones.some(bone => bone === 'weapon'));
  assert.deepEqual(poses.get(343).attacks[1].bones, ['effect']);
  assert.ok(effectManifest.effects.pos343.nodes.some(node => node.name === 'AttackBox' && nativeEffectBounds(node)), 'the second pure-effect window requires its actual source bound');
});

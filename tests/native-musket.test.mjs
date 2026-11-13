import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { NATIVE_MUSKET_PROFILE, NativeMusketSystem, sweepNativeMusketBody } from '../dist/native-projectiles.js';
import { NATIVE_WEAPONS, NATIVE_GUARD_REACTIONS, NativeCombatController, parsePos, parseAct, decodeNativeText, createNativeDamageResolver } from '../dist/native-combat.js';
import { parseGmc } from '../dist/gmc-loader.js';

const assets = new URL('../dist/assets/', import.meta.url), v = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
const poses = parsePos(decodeNativeText(await readFile(new URL('native/combat/P0.POS', assets))));
const actions = parseAct(decodeNativeText(await readFile(new URL('native/combat/character.act', assets))));
const resources = JSON.parse(await readFile(new URL('original/characters/meteor-res-data.json', assets), 'utf8'));
const data = { poses, actions, moveRecords: new Map(resources.allRecords.filter(r => r.type === 3).map(r => [r.id, r])),
  weaponRecords: new Map(resources.allRecords.filter(r => r.type === 1).map(r => [r.model.toLowerCase(), r])) };
let serial = 0;
function actor(z = 0, weapon = 'musket', item = 3) {
  const root = new THREE.Group(); root.position.z = z;
  return { id: ++serial, root, weapon, weaponId: item, weaponRecord: resources.allRecords.find(r => r.type === 1 && r.id === item),
    teamMask: weapon === 'musket' ? 2 : 1, nativeStats: {}, activeItems: [], hp: 1000, rage: 0 };
}
function wall(z) {
  const mesh = new THREE.Mesh(new THREE.PlaneGeometry(20, 20), new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }));
  mesh.position.set(0, 2, z); mesh.updateMatrixWorld(true); return mesh;
}
function fixture({ targets, colliders = [], item = 3 } = {}) {
  const owner = actor(0, 'musket', item), target = actor(10, 'sword', 6), hits = [], worlds = [];
  const damage = createNativeDamageResolver(data), combat = new NativeCombatController(data, { weapon: 'musket' });
  const system = new NativeMusketSystem({ getTargets: () => targets || [owner, target], getColliders: () => colliders,
    onActorHit: (shot, victim, point) => { const context = { attacker: shot.context.attacker, target: victim, poseId: shot.context.state.poseId, guarded: !!victim.guard };
      const amount = damage(context); victim.hp -= amount; victim.rage += context.nativeResult.victimRage; hits.push({ shot, victim, point, amount }); },
    onWorldHit: (shot, contact) => worlds.push({ shot, contact }) });
  const aim = { owner, position: v(0, 1.35, .2), sourcePosition: v(0, 1.35, 0), direction: v(0, 0, 1), range: 30, context: { attacker: owner } };
  return { owner, target, system, combat, aim, hits, worlds };
}
function sourceState(combat, poseId) { combat.play(poseId, { force: true }); return combat.update(1 / 60); }

test('original musket models, source stance and actual guard table are present', async () => {
  const manifest = JSON.parse(await readFile(new URL('original/weapon-models/manifest.json', assets), 'utf8'));
  const items = manifest.items.filter(item => /^w2_/i.test(item.modelId));
  assert.deepEqual(items.map(item => item.itemId), [3, 12, 21, 30, 39]); assert.ok(items.every(item => item.available));
  const model = parseGmc(await readFile(new URL('original/weapon-models/models/w2_0/w2_0.gmc', assets), 'utf8'), { scale: .08, groundZ: 0, texturePath: '', unlit: true });
  assert.ok(model.getObjectByProperty('isMesh', true));
  assert.equal(NATIVE_WEAPONS.musket.weaponId, 3); assert.equal(NATIVE_WEAPONS.musket.stance, 2); assert.equal(NATIVE_WEAPONS.musket.guard, 12);
  assert.deepEqual(NATIVE_GUARD_REACTIONS.musket, [44, 45, 46, 47, 77, 78, 79]);
  for (const poseId of [2, 12, ...NATIVE_GUARD_REACTIONS.musket]) assert.ok(poses.get(poseId).valid);
});

test('musket NPC ordinary attacks use source206 and do not invent airborne gunfire', () => {
  const { combat, system, aim } = fixture(); combat.play(2, { force: true });
  assert.equal(system.firePose({ ...aim, state: combat.update(.1) }).length, 0);
  assert.equal(combat.attack(), true); assert.equal(combat.timeline.pose.id, 206);
  assert.equal(combat.attack({ air: true }), false);
  assert.deepEqual(actions.links.get(206), new Set([208, 215, 216]));
  assert.deepEqual(poses.get(206).attacks[0].bones, []);
});

test('actual POS206/207/208 releases hit once using each original RES modifier', () => {
  for (const [poseId, expected] of [[206, 37], [207, 45], [208, 49]]) {
    const { combat, system, aim, target, hits } = fixture(); const state = sourceState(combat, poseId);
    const shots = system.firePose({ ...aim, state }); assert.equal(shots.length, 1); assert.equal(shots[0].removalReason, 'actor');
    assert.equal(target.hp, 1000 - expected); assert.equal(hits[0].amount, expected); assert.equal(system.size, 0);
    assert.equal(system.firePose({ ...aim, state }).length, 0);
    for (let frame = 0; frame < 180; frame++) system.firePose({ ...aim, state: combat.update(1 / 60) });
    assert.equal(hits.length, 1); assert.equal(target.hp, 1000 - expected);
    assert.equal(shots[0].context.state.poseId, poseId); assert.equal(shots[0].context.attack.targetposefront, poses.get(poseId).attacks[0].targetposefront);
  }
});

test('source weapon variants retain their own RES damage rather than default gun stats', () => {
  for (const [item, expected] of [[3, 37], [12, 48], [21, 26], [30, 31], [39, 63]]) {
    const { combat, system, aim, target, hits } = fixture({ item });
    system.firePose({ ...aim, state: sourceState(combat, 206) }); assert.equal(hits[0].amount, expected); assert.equal(target.hp, 1000 - expected);
  }
});

test('guard and friendly contact preserve recovered damage arithmetic', () => {
  const blocked = fixture(); blocked.target.guard = true;
  blocked.system.firePose({ ...blocked.aim, state: sourceState(blocked.combat, 206) }); assert.equal(blocked.hits.length, 1); assert.equal(blocked.target.hp, 1000);
  const friendly = fixture(); friendly.target.teamMask = friendly.owner.teamMask;
  friendly.system.firePose({ ...friendly.aim, state: sourceState(friendly.combat, 206) }); assert.equal(friendly.hits[0].amount, 7); assert.equal(friendly.target.hp, 993);
});

test('原场景截断火铳射线，命中角色不遮住后方墙体反馈', () => {
  const blocked = fixture({ colliders: [wall(5)] });
  blocked.system.firePose({ ...blocked.aim, state: sourceState(blocked.combat, 206) }); assert.equal(blocked.target.hp, 1000); assert.equal(blocked.worlds.length, 1);
  const close = actor(3, 'sword', 6), far = actor(7, 'sword', 6), first = fixture({ targets: [far, close], colliders: [wall(5)] });
  first.system.firePose({ ...first.aim, state: sourceState(first.combat, 206) }); assert.equal(close.hp, 963); assert.equal(far.hp, 1000); assert.equal(first.worlds.length, 1);
  const clipped = fixture({ colliders: [wall(.1)] });
  clipped.system.firePose({ ...clipped.aim, state: sourceState(clipped.combat, 206) }); assert.equal(clipped.target.hp, 1000); assert.equal(clipped.worlds.length, 1);
});

test('原火铳默认射程与暂停、短查询、旧动作及特殊EF去重', () => {
  const { combat, system, aim, target, hits } = fixture(); const state = sourceState(combat, 206);
  assert.equal(system.fire({ ...aim, range: NaN }), null);
  system.pause(); assert.equal(system.firePose({ ...aim, state }).length, 0); system.pause(false);
  assert.equal(system.firePose({ ...aim, range: 2, state })[0].removalReason, 'miss'); assert.equal(target.hp, 1000);
  assert.equal(system.firePose({ ...aim, state }).length, 0, 'a missed shot still consumes its release identity');
  const second = sourceState(combat, 207); system.firePose({ ...aim, state: second }); assert.equal(hits.length, 1);
  assert.equal(system.firePose({ ...aim, state }).length, 0, 'stale source serial cannot fire again');
  for (const poseId of [215, 216, 217]) assert.equal(system.firePose({ ...aim, state: sourceState(combat, poseId) }).length, 0);
  assert.equal(NATIVE_MUSKET_PROFILE.contactMode, 'native-scene-clipped-ray'); assert.equal(Object.hasOwn(NATIVE_MUSKET_PROFILE, 'speed'), false);
  assert.equal(NATIVE_MUSKET_PROFILE.range, 80); assert.equal(NATIVE_MUSKET_PROFILE.originHeight, 2.4); assert.equal(system.size, 0);
  system.dispose(); assert.equal(system.fire({ ...aim }), null);
});


test('原火铳可命中同一场景射线内的多名角色，墙后目标仍被阻挡', () => {
  const close = actor(3, 'sword', 6), middle = actor(7, 'sword', 6), behind = actor(14, 'sword', 6);
  const f = fixture({ targets: [middle, close, behind, close], colliders: [wall(10)] });
  const shot = f.system.firePose({ ...f.aim, state: sourceState(f.combat, 206) })[0];
  assert.equal(f.hits.length, 2); assert.equal(close.hp, 963); assert.equal(middle.hp, 963); assert.equal(behind.hp, 1000);
  assert.equal(f.worlds.length, 1); assert.ok(Math.abs(shot.position.z - 10) < 1e-6);
  assert.ok(f.hits.every(hit => hit.shot === shot));
});

test('原火铳目标盒为横向±7与脚底至36原单位，包括盒角和头顶', () => {
  const target = actor(10, 'sword', 6), width = 7 * .08, height = 36 * .08;
  assert.equal(NATIVE_MUSKET_PROFILE.bodyHalfWidth, width); assert.equal(NATIVE_MUSKET_PROFILE.bodyHeight, height);
  for (const x of [-width, 0, width]) for (const y of [0, 2.7, height]) assert.notEqual(sweepNativeMusketBody(v(x, y, 0), v(x, y, 20), target), null);
  assert.equal(sweepNativeMusketBody(v(width + 1e-6, 1, 0), v(width + 1e-6, 1, 20), target), null);
  assert.equal(sweepNativeMusketBody(v(0, height + 1e-6, 0), v(0, height + 1e-6, 20), target), null);
  assert.equal(sweepNativeMusketBody(v(0, -1e-6, 0), v(0, -1e-6, 20), target), null);
  assert.equal(sweepNativeMusketBody(v(0, 1, 0), v(0, 1, 8), target), null);
  assert.equal(sweepNativeMusketBody(v(0, 1, 10), v(0, 1, 11), target), 0);
});

test('原火铳不超过1000原单位，省略射程时仍使用原上限', () => {
  const near = actor(79, 'sword', 6), beyond = actor(81, 'sword', 6), f = fixture({ targets: [near, beyond] });
  f.system.firePose({ ...f.aim, range: undefined, state: sourceState(f.combat, 206) });
  assert.equal(near.hp, 963); assert.equal(beyond.hp, 1000);
  f.system.firePose({ ...f.aim, range: 1000, state: sourceState(f.combat, 206) });
  assert.equal(near.hp, 926); assert.equal(beyond.hp, 1000);
});

test('同一火铳动作即使重发或带多个攻击窗，也只消耗一次发射标志', () => {
  const f = fixture(), state = sourceState(f.combat, 206);
  state.attacks.push({ ...state.attacks[0], index: 99 });
  assert.equal(f.system.firePose({ ...f.aim, state }).length, 1);
  assert.equal(f.hits.length, 1);
  assert.equal(f.system.firePose({ ...f.aim, state }).length, 0);
});

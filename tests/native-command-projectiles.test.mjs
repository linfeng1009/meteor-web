import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { NATIVE_DART_PROFILE } from '../dist/native-projectiles.js';
import { parseGmc } from '../dist/gmc-loader.js';
import { decodeNativeText, parsePos, parseAct, NativeCombatController, createNativeDamageResolver } from '../dist/native-combat.js';

const root = new URL('../dist/assets/', import.meta.url);
const poses = parsePos(decodeNativeText(await readFile(new URL('native/combat/P0.POS', root))));
const actions = parseAct(decodeNativeText(await readFile(new URL('native/combat/character.act', root))));
const records = JSON.parse(await readFile(new URL('original/characters/meteor-res-data.json', root), 'utf8')).allRecords;
const data = { poses, actions, moveRecords: new Map(records.filter(r => r.type === 3).map(r => [r.id, r])), weaponRecords: new Map(records.filter(r => r.type === 1).map(r => [r.model.toLowerCase(), r])) };
const dart = parseGmc(await readFile(new URL('original/weapon-models/models/w3_0/w3_0.gmc', root), 'utf8'), { scale: 1, groundZ: 0, texturePath: '', unlit: true });
const vector = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
function fixture(colliders = []) {
  const heroRoot = new THREE.Group(), hand = new THREE.Group(); hand.position.set(.15, 1.45, .1); heroRoot.add(hand);
  const weaponModel = dart.clone(true); hand.add(weaponModel);
  const hero = { id: 1, hero: true, root: heroRoot, weapon: 'dart', weaponId: 1, hp: 1000, rage: 0, team: 1, teamMask: 1,
    nativeStats: {}, activeItems: [], attackHits: new Set(), weaponRecord: data.weaponRecords.get('w3_0'), weaponModel,
    character: { getAttachment: () => hand, setPoseFrame() {} }, combat: new NativeCombatController(data, { weapon: 'dart' }) };
  const target = { id: 2, hero: false, root: new THREE.Group(), weapon: 'spear', weaponId: 7, hp: 1000, rage: 0, team: 2, teamMask: 2, dead: false,
    nativeStats: {}, activeItems: [], weaponRecord: data.weaponRecords.get('w7_0'), attackHits: new Set() };
  target.root.position.z = 10;
  const game = Object.create(MeteorGame.prototype), sounds = [], events = [];
  Object.assign(game, { scene: new THREE.Scene(), hero, enemies: [target], mode: 'story', running: true, paused: false,
    hostPhysics: { radius: .4 }, currentMap: { colliders }, combatData: data, damageResolver: createNativeDamageResolver(data),
    kills: 0, deaths: 0, contactHits: 0, totalDamage: 0, _hud() {}, _emit: (...event) => events.push(event),
    _soundDefinition: effect => sounds.push(effect), _collisionCandidates: () => colliders });
  game.scene.add(heroRoot, target.root); heroRoot.updateMatrixWorld(true); game._initializeProjectiles();
  return { game, hero, target, sounds, events };
}
function stepRelease(fixture, dt) {
  const state = fixture.hero.combat.update(dt, { grounded: true });
  for (const segment of state.segments) fixture.game._launchNativeProjectiles(fixture.hero, segment);
  return state;
}

test('directional darts retain their original single release windows, RES damage and distinct EF sound references', async () => {
  for (const [poseId, start, end, sound] of [[209, 3550, 3553, 'W03FIR02.wav'], [210, 3593, 3596, 'W03FIR03.wav']]) {
    assert.ok(NATIVE_DART_PROFILE.poseIds.includes(poseId));
    const pose = poses.get(poseId);
    assert.equal(pose.attacks.length, 1);
    assert.equal(pose.attacks[0].start, start); assert.equal(pose.attacks[0].end, end);
    assert.deepEqual(pose.attacks[0].bones, [], 'the original input pose is projectile-only');
    const modifier = data.moveRecords.get(poseId).effects.find(e => e.statKey === 3);
    assert.equal(modifier.mode, 1); assert.equal(modifier.value, 50);
    const ef = await readFile(new URL(`original/sounds/definitions/pos${poseId}.ef`, root));
    assert.equal(ef.subarray(0, 11).toString(), 'PonEF V1.00');
    assert.ok(ef.includes(Buffer.from(sound)));
  }
});

for (const [poseId, before] of [[209, .49], [210, .57]]) {
  test(`command pose ${poseId} releases one original W3_0 only after its native animation reaches the attack window`, () => {
    const f = fixture();
    assert.equal(f.hero.combat.attack({ poseId }), true);
    stepRelease(f, before); assert.equal(f.game.projectiles.size, 0);
    const state = stepRelease(f, .02); assert.equal(f.game.projectiles.size, 1);
    for (const segment of state.segments) f.game._launchNativeProjectiles(f.hero, segment);
    stepRelease(f, .02); assert.equal(f.game.projectiles.size, 1, 'repeated animation samples cannot duplicate a release');
    const shot = f.game.projectiles.active[0];
    assert.equal(shot.context.state.poseId, poseId);
    assert.equal(shot.context.model, 'w3_0');
    assert.equal(shot.visual.children[0].geometry, dart.children[0].geometry);
    assert.deepEqual(shot.visual.scale.toArray(), [.08, .08, .08]);
    assert.deepEqual(f.sounds, [`Pos${poseId}`]);
    f.game.projectiles.update(.3);
    assert.equal(shot.removalReason, 'actor'); assert.equal(f.target.hp, 977);
    assert.equal(f.game.totalDamage, 23); assert.equal(f.game.contactHits, 1);
    f.game.projectiles.update(1); assert.equal(f.target.hp, 977);
    f.game.projectiles.dispose();
  });

  test(`command pose ${poseId} cannot damage an opponent behind an original-triangle-style wall`, () => {
    const wall = new THREE.Mesh(new THREE.PlaneGeometry(20, 20), new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }));
    wall.position.set(0, 2, 5); wall.updateMatrixWorld(true);
    const f = fixture([wall]); f.hero.combat.attack({ poseId }); stepRelease(f, 1);
    const shot = f.game.projectiles.active[0]; assert.ok(shot);
    f.game.projectiles.update(.4);
    assert.equal(shot.removalReason, 'world'); assert.equal(f.target.hp, 1000);
    assert.equal(f.game.contactHits, 0); f.game.projectiles.dispose();
  });
}

test('complex original EF files contain parented attack volumes which cannot be replaced by an invented dart fan', async () => {
  const inventory = async poseId => {
    const bytes = await readFile(new URL(`original/sounds/definitions/pos${poseId}.ef`, root)), nodes = [];
    for (const type of ['AUDIO', 'BOX', 'BILLBOARD', 'CYLINDER', 'DRAG', 'DONUT', 'MODEL', 'PARTICLE', 'PATH', 'PLANE', 'SPHERE', 'TRAPE']) {
      const signature = Buffer.alloc(16); signature.write(type); let from = 0, offset;
      while ((offset = bytes.indexOf(signature, from)) >= 0) {
        from = offset + 1;
        let cursor = offset + 16;
        const string = () => { const length = bytes.readUInt32LE(cursor); cursor += 4; const value = bytes.subarray(cursor, cursor + length).toString(); cursor += length; return value; };
        const name = string(); cursor += 16; nodes.push({ type, name, bindings: [string(), string()] });
      }
    }
    assert.equal(nodes.length, bytes.readUInt32LE(11), 'every declared EF node is identified');
    return nodes;
  };
  for (const poseId of [201, 551]) {
    const nodes = await inventory(poseId), attacks = nodes.filter(n => n.type === 'SPHERE' && n.name.startsWith('Attack'));
    assert.equal(attacks.length, 12);
    assert.ok(attacks.every(n => nodes.some(p => p.type === 'PLANE' && p.name === n.bindings[0])));
  }
  const rageStart = await inventory(203), rageRelease = await inventory(204);
  assert.equal(rageStart.filter(n => n.name === 'AttackBall').length, 1);
  assert.equal(rageRelease.filter(n => n.type === 'CYLINDER' && n.name.startsWith('AttackWave')).length, 7);
  const daggerRage = await inventory(259), daggerBox = daggerRage.find(n => n.name === 'AttackBox');
  assert.equal(daggerRage.length, 17);
  assert.equal(daggerBox.type, 'BOX'); assert.deepEqual(daggerBox.bindings, ['d_base', 'd_base']);
  assert.deepEqual(poses.get(259).attacks.flatMap(a => a.bones), ['effect']);
  assert.equal(poses.get(259).link, 349); assert.equal(poses.get(349).attacks.length, 0);
  for (const poseId of [201, 203, 204, 551]) assert.equal(NATIVE_DART_PROFILE.poseIds.includes(poseId), false);
});

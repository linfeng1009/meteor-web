import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { NATIVE_APPEARANCES, createNativeCharacter, loadNativeCharacterData, loadEnhancedCharacterData } from '../dist/native-character.js';

const imageSize = bytes => {
  if (bytes.subarray(0, 8).toString('hex') === '89504e470d0a1a0a') return [bytes.readUInt32BE(16), bytes.readUInt32BE(20)];
  const fourcc = bytes.subarray(12, 16).toString('ascii');
  if (fourcc === 'VP8X') return [1 + bytes.readUIntLE(24, 3), 1 + bytes.readUIntLE(27, 3)];
  if (fourcc === 'VP8 ') return [bytes.readUInt16LE(26) & 0x3fff, bytes.readUInt16LE(28) & 0x3fff];
  if (fourcc === 'VP8L') { const bits = bytes.readUInt32LE(21); return [1 + (bits & 0x3fff), 1 + ((bits >> 14) & 0x3fff)]; }
  return [0, 0];
};


// Deployment converts texture atlases to WebP to fit a slow uplink, so a
// runtime texture may be PNG or WebP. These helpers read either container.
const imageMagic = bytes => {
  const head = bytes.subarray(0, 12);
  if (head.subarray(0, 8).toString('hex') === '89504e470d0a1a0a') return 'png';
  if (head.subarray(0, 4).toString('ascii') === 'RIFF' && head.subarray(8, 12).toString('ascii') === 'WEBP') return 'webp';
  return 'unknown';
};



const fileFetch = async url => { try { return new Response(await readFile(new URL(url))); } catch { return new Response('', { status: 404 }); } };
const withFetch = async callback => { const before = globalThis.fetch; globalThis.fetch = fileFetch; try { return await callback(); } finally { globalThis.fetch = before; } };
const data = await withFetch(() => loadNativeCharacterData(0));
const matrices = actor => [...actor.bones, ...actor.dummies].map(bone => bone.matrixWorld.toArray());

test('Emilia has a separate p0 bundle; a missing resource preserves the live Raiden surface', async () => {
  assert.equal(Object.isFrozen(NATIVE_APPEARANCES.emilia), true);
  assert.equal(NATIVE_APPEARANCES.emilia.characterId, 0);
  assert.match(NATIVE_APPEARANCES.emilia.label, /RE0-爱蜜莉雅/);
  assert.equal(new Set(['hutao', 'raiden', 'emilia'].map(id => NATIVE_APPEARANCES[id].assetPath)).size, 3);
  const actor = createNativeCharacter(data, { loadTextures: false }), before = globalThis.fetch;
  globalThis.fetch = async url => new URL(url).pathname.includes('/enhanced/emilia/') ? new Response('', { status: 404 }) : fileFetch(url);
  try {
    await actor.setAppearance('raiden'); const mesh = actor.mesh;
    const rejected = await actor.setAppearance('emilia');
    assert.equal(rejected.available, false); assert.equal(rejected.appearance, 'raiden'); assert.match(rejected.reason, /404/); assert.equal(actor.mesh, mesh);
    const other = createNativeCharacter(await loadNativeCharacterData(1), { loadTextures: false });
    try {
      const original = other.mesh, incompatible = await other.setAppearance('emilia');
      assert.equal(incompatible.available, false); assert.equal(other.mesh, original); assert.equal(other.group.userData.characterId, 1);
    } finally { other.dispose(); }
  } finally { actor.dispose(); globalThis.fetch = before; }
});

test('Emilia loads the supplied complete face, costume and mapped PNG textures rather than a placeholder', async () => withFetch(async () => {
  const asset = await loadEnhancedCharacterData(0, 'emilia');
  assert.equal(asset.manifest.appearance, 'emilia'); assert.equal(asset.manifest.complete, true); assert.equal(asset.manifest.completeness.faceGeometry, true);
  assert.match(asset.manifest.label, /RE0-爱蜜莉雅|Emilia/);
  assert.ok(asset.skin.vertexCount >= 10000 && asset.skin.triangleCount >= 10000);
  assert.equal(asset.manifest.stats.vertices, asset.skin.vertexCount); assert.equal(asset.manifest.stats.triangles, asset.skin.triangleCount);
  assert.ok(asset.skin.materials.some(material => /face|顔|面/i.test(material.sourceName ?? material.name)), 'retain the real face material');
  const textureFiles = new Set(asset.skin.materials.map(material => material.texture).filter(name => name && name !== 'null'));
  assert.ok(textureFiles.size >= 4, 'retain separate supplied color maps');
  for (const texture of textureFiles) {
    const bytes = await readFile(new URL(texture, asset.path));
    assert.notEqual(imageMagic(bytes), 'unknown');
    assert.ok(bytes.readUInt32BE(16) >= 512 && bytes.readUInt32BE(20) >= 512);
  }
  const influences = new Set();
  for (let i = 0; i < asset.skin.skinWeights.length; i++) if (asset.skin.skinWeights[i] > .01) influences.add(asset.skin.skinIndices[i]);
  assert.ok(influences.size >= 12, 'imported body must articulate on the native skeleton');
}));

test('four appearances keep independent cached meshes on one live skeleton and weapon attachment', async () => withFetch(async () => {
  const actor = createNativeCharacter(data, { loadTextures: false });
  try {
    actor.group.position.set(3, 4, -5); actor.group.rotation.y = .7; actor.setPoseFrame(0, data.poses[262].start + 5.5);
    const hand = actor.getAttachment('d_wpnR'), weapon = new THREE.Group(); hand.add(weapon); actor.group.updateMatrixWorld(true);
    const skeleton = actor.skeleton, joints = matrices(actor), bind = actor.mesh.bindMatrix.toArray(), frame = actor.frame, weaponMatrix = weapon.matrixWorld.toArray(), meshes = new Map([['original', actor.mesh]]);
    for (const appearance of ['hutao', 'raiden', 'emilia', 'raiden', 'emilia', 'hutao', 'original']) {
      const result = await actor.setAppearance(appearance);
      assert.equal(result.available, true); assert.equal(result.complete, true); assert.equal(result.appearance, appearance);
      if (meshes.has(appearance)) assert.equal(actor.mesh, meshes.get(appearance)); else meshes.set(appearance, actor.mesh);
      assert.deepEqual(actor.mesh.skeleton.bones.slice(0, skeleton.bones.length), skeleton.bones); assert.deepEqual(actor.mesh.bindMatrix.toArray(), bind); assert.deepEqual(matrices(actor), joints); assert.equal(actor.frame, frame);
      assert.equal(actor.getAttachment('d_wpnR'), hand); assert.equal(weapon.parent, hand); assert.deepEqual(weapon.matrixWorld.toArray(), weaponMatrix);
      assert.equal(actor.nativeSpace.children.filter(child => child.isSkinnedMesh).length, 1);
    }
    assert.equal(new Set(meshes.values()).size, 4);
  } finally { actor.dispose(); }
}));

test('Emilia retains native joints and finite skin bounds across 45 running, airborne, guard and attack samples', async () => withFetch(async () => {
  const source = createNativeCharacter(data, { loadTextures: false }), actor = createNativeCharacter(data, { loadTextures: false });
  try {
    assert.equal((await actor.setAppearance('emilia')).available, true);
    // Actual recovered cloth edges: a pure-leg patch was accidentally reassigned
    // to the pelvis and gained .357 world units during falling. Bounds stayed finite, so
    // explicitly guard that defect while allowing this provisional cloth rig.
    const seamEdges = [[1224, 1226], [537, 536]].map(([a, b]) => ({ a, b, rest: new THREE.Vector3().fromArray(actor.mesh.geometry.attributes.position.array, a * 3).distanceTo(new THREE.Vector3().fromArray(actor.mesh.geometry.attributes.position.array, b * 3)) * actor.nativeSpace.scale.x }));
    const vertexA = new THREE.Vector3(), vertexB = new THREE.Vector3();
    for (const id of [6, 16, 90, 117, 144, 151, 152, 200, 202, 248, 262, 263, 264, 279, 295]) {
      const pose = data.poses[id];
      for (const frame of [pose.start, (pose.start + pose.end) / 2, pose.end]) {
        source.setPoseFrame(pose.source, frame); actor.setPoseFrame(pose.source, frame);
        assert.deepEqual(matrices(actor), matrices(source), `pose ${id} frame ${frame}`);
        actor.mesh.computeBoundingBox(); const box = actor.mesh.boundingBox.clone().applyMatrix4(actor.mesh.matrixWorld);
        assert.ok([...box.min.toArray(), ...box.max.toArray()].every(Number.isFinite));
        assert.ok(box.getSize(new THREE.Vector3()).length() < 10, `pose ${id} frame ${frame}: skin must not explode`);
        for (const edge of seamEdges) {
          vertexA.fromBufferAttribute(actor.mesh.geometry.attributes.position, edge.a); actor.mesh.applyBoneTransform(edge.a, vertexA); actor.mesh.localToWorld(vertexA);
          vertexB.fromBufferAttribute(actor.mesh.geometry.attributes.position, edge.b); actor.mesh.applyBoneTransform(edge.b, vertexB); actor.mesh.localToWorld(vertexB);
          assert.ok(vertexA.distanceTo(vertexB) - edge.rest < .3, `pose ${id} frame ${frame}: cloth ${edge.a}/${edge.b} cannot regain the severe seam regression`);
        }
      }
    }
  } finally { source.dispose(); actor.dispose(); }
}));

test('game adoption preserves mission identity, resources, airborne motion and the active manual command', async () => withFetch(async () => {
  const character = createNativeCharacter(data, { loadTextures: false }), game = Object.create(MeteorGame.prototype), events = [];
  const command = { id: 'sword-air-down', name: '空中招式' }, timeline = { pose: { id: 151 }, time: .31 }, combat = { timeline, combo: 2, currentMove: command }, mission = { id: 'sn01', stage: 'fighting' };
  const actor = { id: 1, scriptId: 0, name: '孟星魂', character, root: character.group, hp: 721, maxHp: 1500, rage: 33, weaponId: 5, weapon: 'dagger', vy: 3.2, grounded: false, team: 1, combat };
  Object.assign(game, { ready: Promise.resolve(), hero: actor, characterId: 0, appearanceRequest: 0, missionState: mission, _hud() {}, onEvent: event => events.push(event) });
  character.setPoseFrame(0, data.poses[151].start + 3); character.group.position.set(1, 4, 6);
  const hand = character.getAttachment('d_wpnR'), weapon = new THREE.Group(); hand.add(weapon); character.group.updateMatrixWorld(true);
  const frame = character.frame, source = character.source, joints = matrices(character), position = character.group.position.toArray(), weaponTransform = weapon.matrixWorld.toArray();
  try {
    const result = await game.setCharacterAppearance('emilia');
    assert.equal(result.available, true); assert.equal(result.complete, true); assert.equal(result.previewOnly, false); assert.equal(game.characterAppearance, 'emilia');
    assert.equal(game.hero, actor); assert.equal(game.characterId, 0); assert.equal(game.missionState, mission); assert.equal(actor.name, '孟星魂'); assert.equal(actor.scriptId, 0); assert.equal(actor.team, 1);
    assert.equal(actor.hp, 721); assert.equal(actor.maxHp, 1500); assert.equal(actor.rage, 33); assert.equal(actor.weaponId, 5); assert.equal(actor.weapon, 'dagger'); assert.equal(actor.vy, 3.2); assert.equal(actor.grounded, false);
    assert.equal(actor.combat, combat); assert.equal(combat.timeline, timeline); assert.equal(combat.currentMove, command); assert.equal(timeline.time, .31); assert.deepEqual(character.group.position.toArray(), position); assert.deepEqual(matrices(character), joints); assert.equal(character.frame, frame); assert.equal(character.source, source);
    assert.equal(character.getAttachment('d_wpnR'), hand); assert.equal(weapon.parent, hand); assert.deepEqual(weapon.matrixWorld.toArray(), weaponTransform); assert.equal(events.at(-1).appearance, 'emilia');
    await game.setCharacterAppearance('raiden'); assert.equal(game.characterAppearance, 'raiden'); assert.equal(combat.currentMove, command); assert.equal(actor.hp, 721);
  } finally { character.dispose(); }
}));

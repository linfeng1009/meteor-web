import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { createNativeCharacter, loadNativeCharacterData, loadEnhancedCharacterData, validateEnhancedSkin, parseNativeSkin, parseNativeBones, parseNativeAnimation, parseNativePoses } from '../dist/native-character.js';

// Both skins use the real supplied BNC/AMB/POS. Only image decoding is omitted
// for the CPU animation tests; browser verification covers the actual maps.
const originalRoot = new URL('../dist/assets/original/characters/', import.meta.url);
const text = file => readFile(new URL(file, originalRoot), 'utf8');
const buffer = async file => { const bytes = await readFile(new URL(file, originalRoot)); return bytes.buffer.slice(bytes.byteOffset, bytes.byteOffset + bytes.byteLength); };
const [skinText, bonesText, common, personal, poseText] = await Promise.all([text('p0/p0.skc'), text('p0/p0.bnc'), buffer('common/character.amb'), buffer('p0/p0.amb'), text('p0/p0.pos')]);
const data = { id: 0, path: new URL('p0/', originalRoot), skin: parseNativeSkin(skinText), skeleton: parseNativeBones(bonesText), animations: [parseNativeAnimation(common), parseNativeAnimation(personal)], poses: parseNativePoses(poseText) };
const fileFetch = async url => { try { const bytes = await readFile(new URL(url)); return new Response(bytes); } catch { return new Response('', { status: 404 }); } };
const withFetch = async callback => { const before = globalThis.fetch; globalThis.fetch = fileFetch; try { return await callback(); } finally { globalThis.fetch = before; } };
const matrices = character => [...character.bones, ...character.dummies].map(node => node.matrixWorld.toArray());

test('a missing featured bundle reports an explicit original fallback and leaves the original model usable', async () => {
  const previousFetch = globalThis.fetch, character = createNativeCharacter(data, { loadTextures: false }), original = character.mesh;
  globalThis.fetch = async () => new Response('', { status: 404 });
  try {
    const status = await character.setAppearance('hutao');
    assert.equal(status.requested, 'hutao'); assert.equal(status.available, false); assert.equal(status.appearance, 'original'); assert.match(status.reason, /404/);
    assert.equal(character.mesh, original); character.setPoseFrame(0, data.poses[151].start + 2);
    assert.equal(character.getAttachment('d_wpnR').isBone, true);
  } finally { character.dispose(); globalThis.fetch = previousFetch; }
});

test('hot appearance switching preserves the live skeleton, original pose, world transform and weapon attachment', async () => withFetch(async () => {
  const character = createNativeCharacter(data, { loadTextures: false });
  try {
    character.group.position.set(2, 4, -7); character.group.rotation.y = .7;
    const pose = data.poses[262]; character.setPoseFrame(pose.source, pose.start + 5.25);
    const hand = character.getAttachment('d_wpnR'), weapon = new THREE.Group(); hand.add(weapon); character.group.updateMatrixWorld(true);
    const originalMesh = character.mesh, skeleton = character.skeleton, beforeMatrices = matrices(character), frame = character.frame, source = character.source;
    const binding = originalMesh.bindMatrix.toArray(), root = character.group.matrixWorld.toArray(), weaponWorld = weapon.matrixWorld.toArray();
    const status = await character.setAppearance('hutao');
    assert.equal(status.available, true); assert.equal(character.appearance, 'hutao'); assert.notEqual(character.mesh, originalMesh);
    assert.equal(character.skeleton, skeleton); assert.deepEqual(character.mesh.skeleton.bones.slice(0, skeleton.bones.length), skeleton.bones);
    assert.deepEqual(character.mesh.bindMatrix.toArray(), binding);
    assert.deepEqual(matrices(character), beforeMatrices); assert.deepEqual(character.group.matrixWorld.toArray(), root);
    assert.equal(character.getAttachment('d_wpnR'), hand); assert.equal(weapon.parent, hand); assert.deepEqual(weapon.matrixWorld.toArray(), weaponWorld);
    assert.equal(character.source, source); assert.equal(character.frame, frame);
    await character.setAppearance('original'); assert.equal(character.mesh, originalMesh);
    assert.deepEqual(matrices(character), beforeMatrices); assert.equal(character.frame, frame);
  } finally { character.dispose(); }
}));

test('Featured playback keeps real jump, run, attack and dart attachment matrices identical to the native skin', async () => withFetch(async () => {
  const original = createNativeCharacter(data, { loadTextures: false }), enhanced = createNativeCharacter(data, { loadTextures: false });
  try {
    await enhanced.setAppearance('hutao'); assert.equal(enhanced.appearance, 'hutao');
    for (const id of [144, 151, 152, 200, 202, 262, 263, 264]) {
      const pose = data.poses[id];
      for (let frame = pose.start; frame <= pose.end; frame++) {
        original.setPoseFrame(pose.source, frame); enhanced.setPoseFrame(pose.source, frame);
        assert.deepEqual(matrices(enhanced), matrices(original), `pose ${id} frame ${frame}: cosmetic switching cannot alter a joint`);
        assert.ok(enhanced.getAttachment('d_base').getWorldPosition(new THREE.Vector3()).length() < .01, 'the jump scene-dummy correction remains active');
        enhanced.mesh.computeBoundingBox();
        assert.ok([...enhanced.mesh.boundingBox.min.toArray(), ...enhanced.mesh.boundingBox.max.toArray()].every(Number.isFinite), 'skinned vertices must stay finite');
      }
    }
  } finally { original.dispose(); enhanced.dispose(); }
}));

test('the game appearance API leaves HP, fighter identity, combat state, velocity and weapon untouched', async () => withFetch(async () => {
  const character = createNativeCharacter(data, { loadTextures: false }), game = Object.create(MeteorGame.prototype);
  const actor = { character, root: character.group, hp: 653, maxHp: 1500, rage: 41, weaponId: 5, weapon: 'dagger', vy: 4.5, grounded: false, combat: { timeline: { pose: { id: 151 }, time: .31 } } };
  Object.assign(game, { ready: Promise.resolve(), hero: actor, characterId: 0, appearanceRequest: 0, _hud() {}, onEvent() {} });
  character.group.position.set(1, 2, 3); character.setPoseFrame(0, data.poses[151].start + 3);
  const combat = actor.combat, position = character.group.position.toArray(), frame = character.frame;
  try {
    await game.setCharacterAppearance('hutao'); await game.setCharacterAppearance('original');
    assert.equal(game.hero, actor); assert.equal(actor.hp, 653); assert.equal(actor.maxHp, 1500); assert.equal(actor.rage, 41);
    assert.equal(actor.weaponId, 5); assert.equal(actor.weapon, 'dagger'); assert.equal(actor.combat, combat); assert.equal(actor.vy, 4.5); assert.equal(actor.grounded, false);
    assert.deepEqual(character.group.position.toArray(), position); assert.equal(character.frame, frame);
  } finally { character.dispose(); }
}));

test('rapid featured/original selection keeps the latest appearance and disposal cancels pending adoption', async () => withFetch(async () => {
  const character = createNativeCharacter(data, { loadTextures: false });
  const pending = character.setAppearance('hutao'); await character.setAppearance('original'); await pending;
  assert.equal(character.appearance, 'original'); assert.equal(character.nativeSpace.children.filter(child => child.isSkinnedMesh).length, 1);
  const original = character.mesh, switching = character.setAppearance('hutao'); character.dispose(); await switching;
  assert.equal(original.parent, null); assert.equal(character.group.parent, null);
}));

test('other nineteen native characters explicitly keep their original appearance', async () => withFetch(async () => {
  for (let id = 1; id < 20; id++) {
    const character = createNativeCharacter(await loadNativeCharacterData(id), { loadTextures: false });
    try {
      const original = character.mesh, status = await character.setAppearance('hutao');
      assert.equal(status.available, false); assert.equal(status.appearance, 'original'); assert.match(status.reason, /仅提供孟星魂/);
      assert.equal(character.mesh, original); assert.equal(character.skeleton.bones.length, 30);
    } finally { character.dispose(); }
  }
}));

test('invalid replacement meshes cannot introduce foreign bones, invalid weights or nonfinite positions', () => {
  const valid = { ...data.skin, positions: [...data.skin.positions], skinIndices: [...data.skin.skinIndices], skinWeights: [...data.skin.skinWeights] };
  assert.doesNotThrow(() => validateEnhancedSkin(valid));
  assert.throws(() => validateEnhancedSkin({ ...valid, positions: [NaN, ...valid.positions.slice(1)] }), /Invalid enhanced/);
  assert.throws(() => validateEnhancedSkin({ ...valid, skinIndices: [30, ...valid.skinIndices.slice(1)] }), /incompatible skeleton/);
  assert.throws(() => validateEnhancedSkin({ ...valid, skinWeights: [8, ...valid.skinWeights.slice(1)] }), /skin weights/);
});

test('color maps and PBR data maps use different color spaces and cached maps survive an actor disposal', async () => withFetch(async () => {
  const previousLoad = THREE.TextureLoader.prototype.load;
  const created = [];
  THREE.TextureLoader.prototype.load = function(url, loaded) { const map = new THREE.Texture(); map.name = url; created.push(map); loaded(map); return map; };
  let first, second;
  try {
    first = createNativeCharacter(data); await first.ready; await first.setAppearance('hutao');
    const maps = first.mesh.material.flatMap(material => [material.map, material.normalMap, material.roughnessMap].filter(Boolean));
    assert.ok(maps.length > 0);
    for (const material of first.mesh.material) {
      if (material.map) assert.equal(material.map.colorSpace, THREE.SRGBColorSpace);
      if (material.normalMap) assert.equal(material.normalMap.colorSpace, THREE.NoColorSpace);
      if (material.roughnessMap) assert.equal(material.roughnessMap.colorSpace, THREE.NoColorSpace);
      for (const map of [material.map, material.normalMap, material.roughnessMap].filter(Boolean)) { assert.equal(map.wrapS, THREE.ClampToEdgeWrapping); assert.equal(map.wrapT, THREE.ClampToEdgeWrapping); }
    }
    const asset = await loadEnhancedCharacterData(0);
    asset.skin.materials.forEach((source, index) => { if (typeof source.normalScale === 'number') assert.deepEqual(first.mesh.material[index].normalScale.toArray(), [source.normalScale, source.normalScale]); });
    let disposedMaps = 0; maps.forEach(map => map.addEventListener('dispose', () => disposedMaps++)); first.dispose();
    assert.equal(disposedMaps, 0, 'an actor cannot invalidate shared texture cache entries');
    second = createNativeCharacter(data); await second.ready; await second.setAppearance('hutao');
    const secondMaps = second.mesh.material.flatMap(material => [material.map, material.normalMap, material.roughnessMap].filter(Boolean));
    assert.deepEqual(secondMaps, maps); assert.equal(disposedMaps, 0);
  } finally { first?.dispose(); second?.dispose(); THREE.TextureLoader.prototype.load = previousLoad; }
}));

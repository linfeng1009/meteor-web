import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { NATIVE_APPEARANCES, createNativeCharacter, loadNativeCharacterData, loadEnhancedCharacterData } from '../dist/native-character.js';

const fileFetch = async url => { try { return new Response(await readFile(new URL(url))); } catch { return new Response('', { status: 404 }); } };
const withFetch = async callback => { const before = globalThis.fetch; globalThis.fetch = fileFetch; try { return await callback(); } finally { globalThis.fetch = before; } };
const data = await withFetch(() => loadNativeCharacterData(0));
const matrices = actor => [...actor.bones, ...actor.dummies].map(bone => bone.matrixWorld.toArray());

test('Raiden has a separate p0 appearance and a missing bundle retains the live HuTao mesh', async () => {
  assert.equal(Object.isFrozen(NATIVE_APPEARANCES.raiden), true);
  assert.equal(NATIVE_APPEARANCES.raiden.characterId, 0);
  assert.match(NATIVE_APPEARANCES.raiden.label, /YS-影/);
  assert.equal(new Set(['emilia', 'hutao', 'raiden'].map(id => NATIVE_APPEARANCES[id].assetPath)).size, 3);
  const actor = createNativeCharacter(data, { loadTextures: false }), before = globalThis.fetch;
  globalThis.fetch = async url => new URL(url).pathname.includes('/enhanced/raiden/') ? new Response('', { status: 404 }) : fileFetch(url);
  try {
    await actor.setAppearance('hutao'); const mesh = actor.mesh;
    const status = await actor.setAppearance('raiden');
    assert.equal(status.available, false); assert.equal(status.appearance, 'hutao'); assert.match(status.reason, /404/); assert.equal(actor.mesh, mesh);
    const other = createNativeCharacter(await loadNativeCharacterData(1), { loadTextures: false });
    try { const original = other.mesh, rejected = await other.setAppearance('raiden'); assert.equal(rejected.available, false); assert.equal(other.mesh, original); assert.equal(other.group.userData.characterId, 1); }
    finally { other.dispose(); }
  } finally { actor.dispose(); globalThis.fetch = before; }
});

test('an incomplete Raiden bundle cannot be adopted or bypass the gate with a cached workshop preview', async () => {
  const module = await import('../dist/native-character.js?raiden-partial-gate'), before = globalThis.fetch;
  const manifest = { characterId: 0, appearance: 'raiden', mesh: 'mesh.json', label: 'YS-影 · 不完整预览', complete: false, completeness: { faceGeometry: false } };
  globalThis.fetch = async url => {
    const path = new URL(url).pathname;
    if (path.endsWith('/enhanced/raiden/manifest.json')) return Response.json(manifest);
    if (path.endsWith('/enhanced/raiden/mesh.json')) return Response.json(data.skin);
    return fileFetch(url);
  };
  const actor = module.createNativeCharacter(data, { loadTextures: false });
  try {
    assert.equal((await actor.setAppearance('raiden')).available, false);
    assert.equal((await actor.setAppearance('raiden', { allowIncomplete: true })).previewOnly, true);
    await actor.setAppearance('hutao'); const current = actor.mesh;
    const blocked = await actor.setAppearance('raiden');
    assert.equal(blocked.available, false); assert.equal(blocked.appearance, 'hutao'); assert.equal(actor.mesh, current);
    assert.match(blocked.reason, /脸部网格/); assert.doesNotMatch(blocked.reason, /胡桃/);
  } finally { actor.dispose(); globalThis.fetch = before; }
});

test('the complete dress Raiden uses real mapped geometry and supplied texture files', async () => withFetch(async () => {
  const asset = await loadEnhancedCharacterData(0, 'raiden');
  assert.equal(asset.manifest.appearance, 'raiden'); assert.equal(asset.manifest.complete, true); assert.equal(asset.manifest.completeness.faceGeometry, true);
  assert.equal(asset.manifest.characterId, 0); assert.match(asset.manifest.label, /影/);
  assert.ok(asset.skin.vertexCount >= 10000 && asset.skin.triangleCount >= 10000);
  assert.equal(asset.manifest.stats.vertices, asset.skin.vertexCount); assert.equal(asset.manifest.stats.triangles, asset.skin.triangleCount);
  assert.ok(asset.skin.materials.some(material => /面|face|顔/i.test(material.name)), 'keep the supplied face surface');
  const textures = new Set(asset.skin.materials.map(material => material.texture).filter(texture => texture && texture !== 'null'));
  assert.ok(textures.size >= 2);
  const sizes = [];
  for (const texture of textures) {
    const bytes = await readFile(new URL(texture, asset.path));
    assert.equal(bytes.subarray(1, 4).toString(), 'PNG'); sizes.push([bytes.readUInt32BE(16), bytes.readUInt32BE(20)]);
  }
  assert.ok(sizes.some(([width, height]) => width >= 1024 && height >= 1024));
  const influences = new Set();
  for (let i = 0; i < asset.skin.skinWeights.length; i++) if (asset.skin.skinWeights[i] > .01) influences.add(asset.skin.skinIndices[i]);
  assert.ok(influences.size >= 12);
}));

test('four appearances reuse one live skeleton and keep distinct cached surfaces and weapon attachments', async () => withFetch(async () => {
  const actor = createNativeCharacter(data, { loadTextures: false });
  try {
    actor.group.position.set(3, 4, -5); actor.group.rotation.y = .7; actor.setPoseFrame(0, data.poses[262].start + 5.5);
    const hand = actor.getAttachment('d_wpnR'), weapon = new THREE.Group(); hand.add(weapon); actor.group.updateMatrixWorld(true);
    const skeleton = actor.skeleton, joints = matrices(actor), bind = actor.mesh.bindMatrix.toArray(), frame = actor.frame, weaponMatrix = weapon.matrixWorld.toArray(), meshes = new Map([['original', actor.mesh]]);
    for (const appearance of ['emilia', 'hutao', 'raiden', 'hutao', 'raiden', 'emilia', 'original']) {
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

test('Raiden remains finite and preserves original joints across 45 native motion samples', async () => withFetch(async () => {
  const source = createNativeCharacter(data, { loadTextures: false }), actor = createNativeCharacter(data, { loadTextures: false });
  try {
    assert.equal((await actor.setAppearance('raiden')).available, true);
    for (const id of [6, 16, 90, 117, 144, 151, 152, 200, 202, 248, 262, 263, 264, 279, 295]) {
      const pose = data.poses[id];
      for (const frame of [pose.start, (pose.start + pose.end) / 2, pose.end]) {
        source.setPoseFrame(pose.source, frame); actor.setPoseFrame(pose.source, frame);
        assert.deepEqual(matrices(actor), matrices(source), `pose ${id} frame ${frame}`);
        actor.mesh.computeBoundingBox(); const box = actor.mesh.boundingBox.clone().applyMatrix4(actor.mesh.matrixWorld);
        assert.ok([...box.min.toArray(), ...box.max.toArray()].every(Number.isFinite));
        assert.ok(box.getSize(new THREE.Vector3()).length() < 10, `pose ${id} frame ${frame} gross skin deformation`);
      }
    }
  } finally { source.dispose(); actor.dispose(); }
}));

test('game adoption changes only appearance while keeping mission, HP, rage, weapon, airborne state and pose', async () => withFetch(async () => {
  const character = createNativeCharacter(data, { loadTextures: false }), game = Object.create(MeteorGame.prototype), events = [];
  const combat = { timeline: { pose: { id: 151 }, time: .31 }, combo: 2 }, mission = { id: 'sn01', stage: 'fighting' };
  const actor = { id: 1, scriptId: 0, name: '孟星魂', character, root: character.group, hp: 721, maxHp: 1500, rage: 33, weaponId: 5, weapon: 'dagger', vy: 3.2, grounded: false, team: 1, combat };
  Object.assign(game, { ready: Promise.resolve(), hero: actor, characterId: 0, appearanceRequest: 0, missionState: mission, _hud() {}, onEvent: event => events.push(event) });
  character.setPoseFrame(0, data.poses[151].start + 3); character.group.position.set(1, 4, 6);
  const hand = character.getAttachment('d_wpnR'), weapon = new THREE.Group(); hand.add(weapon); character.group.updateMatrixWorld(true);
  const frame = character.frame, source = character.source, joints = matrices(character), position = character.group.position.toArray(), weaponTransform = weapon.matrixWorld.toArray();
  try {
    const result = await game.setCharacterAppearance('raiden');
    assert.equal(result.available, true); assert.equal(result.complete, true); assert.equal(result.previewOnly, false); assert.equal(game.characterAppearance, 'raiden');
    assert.equal(game.hero, actor); assert.equal(game.characterId, 0); assert.equal(game.missionState, mission); assert.equal(actor.name, '孟星魂'); assert.equal(actor.scriptId, 0); assert.equal(actor.team, 1);
    assert.equal(actor.hp, 721); assert.equal(actor.maxHp, 1500); assert.equal(actor.rage, 33); assert.equal(actor.weaponId, 5); assert.equal(actor.weapon, 'dagger'); assert.equal(actor.vy, 3.2); assert.equal(actor.grounded, false);
    assert.equal(actor.combat, combat); assert.equal(combat.timeline.time, .31); assert.deepEqual(character.group.position.toArray(), position); assert.deepEqual(matrices(character), joints); assert.equal(character.frame, frame); assert.equal(character.source, source);
    assert.equal(character.getAttachment('d_wpnR'), hand); assert.equal(weapon.parent, hand); assert.deepEqual(weapon.matrixWorld.toArray(), weaponTransform); assert.equal(events.at(-1).appearance, 'raiden');
    await game.setCharacterAppearance('hutao'); assert.equal(game.characterAppearance, 'hutao'); assert.equal(actor.combat, combat); assert.equal(actor.hp, 721);
  } finally { character.dispose(); }
}));

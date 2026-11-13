import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { NATIVE_APPEARANCES, createNativeCharacter, loadNativeCharacterData, loadEnhancedCharacterData, parseNativeSkin, parseNativeBones, parseNativeAnimation, parseNativePoses } from '../dist/native-character.js';

const imageMagic = bytes => {
  if (bytes.subarray(0, 8).toString('hex') === '89504e470d0a1a0a') return 'png';
  if (bytes.subarray(0, 4).toString('ascii') === 'RIFF' && bytes.subarray(8, 12).toString('ascii') === 'WEBP') return 'webp';
  return 'unknown';
};


const imageSize = bytes => {
  if (bytes.subarray(0, 8).toString('hex') === '89504e470d0a1a0a') return [bytes.readUInt32BE(16), bytes.readUInt32BE(20)];
  const fourcc = bytes.subarray(12, 16).toString('ascii');
  if (fourcc === 'VP8X') return [1 + bytes.readUIntLE(24, 3), 1 + bytes.readUIntLE(27, 3)];
  if (fourcc === 'VP8 ') return [bytes.readUInt16LE(26) & 0x3fff, bytes.readUInt16LE(28) & 0x3fff];
  if (fourcc === 'VP8L') { const bits = bytes.readUInt32LE(21); return [1 + (bits & 0x3fff), 1 + ((bits >> 14) & 0x3fff)]; }
  return [0, 0];
};


// The supplied PMX appearance reuses the original actor/bones. It is not a new
// native P20 or evidence of recovered Genshin runtime animation/physics.
const originalRoot = new URL('../dist/assets/original/characters/', import.meta.url);
const text = file => readFile(new URL(file, originalRoot), 'utf8');
const buffer = async file => { const bytes = await readFile(new URL(file, originalRoot)); return bytes.buffer.slice(bytes.byteOffset, bytes.byteOffset + bytes.byteLength); };
const [skinText, bonesText, common, personal, poseText] = await Promise.all([text('p0/p0.skc'), text('p0/p0.bnc'), buffer('common/character.amb'), buffer('p0/p0.amb'), text('p0/p0.pos')]);
const data = { id: 0, path: new URL('p0/', originalRoot), skin: parseNativeSkin(skinText), skeleton: parseNativeBones(bonesText), animations: [parseNativeAnimation(common), parseNativeAnimation(personal)], poses: parseNativePoses(poseText) };
const fileFetch = async url => { try { return new Response(await readFile(new URL(url))); } catch { return new Response('', { status: 404 }); } };
const withFetch = async callback => { const before = globalThis.fetch; globalThis.fetch = fileFetch; try { return await callback(); } finally { globalThis.fetch = before; } };
const matrices = character => [...character.bones, ...character.dummies].map(node => node.matrixWorld.toArray());

test('appearance registry keeps HuTao and drops the retired HD appearance', () => {
  assert.deepEqual(Object.keys(NATIVE_APPEARANCES), ['original', 'liuchao', 'hutao', 'raiden', 'emilia', 'doubao', 'springfield', 'ganyu', 'yaemiko', 'shogun', 'lumine', 'aether', 'furina', 'zhaojun', 'keqing', 'haku', 'ningguang']);
  assert.equal(NATIVE_APPEARANCES.hutao.characterId, 0);
  assert.equal(NATIVE_APPEARANCES.hd, undefined);
  assert.equal(Object.isFrozen(NATIVE_APPEARANCES), true); assert.equal(Object.isFrozen(NATIVE_APPEARANCES.hutao), true);
});

test('an absent HuTao bundle explicitly falls back to the original mesh and keeps its pose usable', async () => {
  const previous = globalThis.fetch, actor = createNativeCharacter(data, { loadTextures: false }), original = actor.mesh;
  globalThis.fetch = async () => new Response('', { status: 404 });
  try {
    const status = await actor.setAppearance('hutao');
    assert.equal(status.requested, 'hutao'); assert.equal(status.available, false); assert.equal(status.appearance, 'original'); assert.match(status.reason, /404/);
    assert.equal(actor.mesh, original); actor.setPoseFrame(0, data.poses[151].start + 2);
    assert.ok(Number.isFinite(actor.getAttachment('d_wpnR').getWorldPosition(new THREE.Vector3()).y));
    await assert.rejects(actor.setAppearance('not-a-character'), /Unknown character appearance/);
  } finally { actor.dispose(); globalThis.fetch = previous; }
});

test('explicit workshop permission is required on every incomplete adoption, including a cached preview', async () => {
  // Isolate metadata/cache behavior from the real recovered geometry, which is
  // exercised below. This synthetic partial record intentionally has no face.
  const module = await import('../dist/native-character.js?partial-gate-isolation'), previous = globalThis.fetch;
  const manifest = { characterId: 0, appearance: 'hutao', mesh: 'mesh.json', label: '胡桃 · 不完整预览', complete: false, completeness: { faceGeometry: false } };
  globalThis.fetch = async url => {
    const path = new URL(url).pathname;
    if (path.endsWith('/enhanced/hutao/manifest.json')) return Response.json(manifest);
    if (path.endsWith('/enhanced/hutao/mesh.json')) return Response.json(data.skin);
    return fileFetch(url);
  };
  const actor = module.createNativeCharacter(data, { loadTextures: false });
  try {
    const blocked = await actor.setAppearance('hutao');
    assert.equal(blocked.available, false); assert.equal(blocked.complete, false); assert.equal(actor.appearance, 'original');
    const preview = await actor.setAppearance('hutao', { allowIncomplete: true });
    assert.equal(preview.available, true); assert.equal(preview.complete, false); assert.equal(preview.previewOnly, true);
    await actor.setAppearance('raiden'); const current = actor.mesh;
    const cachedBlocked = await actor.setAppearance('hutao');
    assert.equal(cachedBlocked.available, false); assert.equal(cachedBlocked.appearance, 'raiden'); assert.equal(actor.mesh, current);
    const retry = await actor.setAppearance('hutao', { allowIncomplete: true });
    assert.equal(retry.previewOnly, true); assert.equal(actor.appearance, 'hutao');
  } finally { actor.dispose(); globalThis.fetch = previous; }
});

test('the complete PMX HuTao mesh has real face geometry, separate textures and normalized native bone weights', async () => withFetch(async () => {
  const asset = await loadEnhancedCharacterData(0, 'hutao');
  assert.equal(asset.manifest.characterId, 0); assert.match(asset.manifest.label, /胡桃/);
  assert.equal(asset.manifest.complete, true); assert.equal(asset.manifest.completeness.faceGeometry, true, 'the supplied complete PMX must replace the earlier headless MOD preview');
  assert.ok(asset.skin.vertexCount >= 10000 && asset.skin.triangleCount >= 10000, 'use the supplied PMX surface, not a procedural placeholder');
  assert.equal(asset.manifest.stats.vertices, asset.skin.vertexCount); assert.equal(asset.manifest.stats.triangles, asset.skin.triangleCount);
  const influences = new Set();
  for (let index = 0; index < asset.skin.skinWeights.length; index++) if (asset.skin.skinWeights[index] > .01) influences.add(asset.skin.skinIndices[index]);
  assert.ok(influences.size >= 12, 'the entire imported character must not be rigidly attached to one or a few bones');
  const dimensions = [];
  for (const material of asset.skin.materials) if (material.texture && material.texture !== 'null') {
    const bytes = await readFile(new URL(material.texture, asset.path));
    assert.ok(new Set(['png','webp']).has(imageMagic(bytes)), 'real texture container'); dimensions.push(imageSize(bytes));
  }
  assert.ok(dimensions.length >= 2, 'preserve the supplied model texture maps');
  assert.ok(dimensions.some(([width, height]) => width >= 1024 && height >= 1024), 'retain the supplied maps at a useful resolution');
}));

test('HuTao, Raiden and original hot switching retain distinct meshes on one live native skeleton', async () => withFetch(async () => {
  const actor = createNativeCharacter(data, { loadTextures: false });
  try {
    actor.group.position.set(7, 2, -4); actor.group.rotation.y = .6; actor.setPoseFrame(0, data.poses[262].start + 5.5);
    const hand = actor.getAttachment('d_wpnR'), weapon = new THREE.Group(); hand.add(weapon); actor.group.updateMatrixWorld(true);
    const native = actor.mesh, skeleton = actor.skeleton, bind = actor.mesh.bindMatrix.toArray(), joints = matrices(actor), frame = actor.frame, weaponMatrix = weapon.matrixWorld.toArray();
    const hutaoStatus = await actor.setAppearance('hutao'), hutao = actor.mesh;
    assert.equal(hutaoStatus.available, true); assert.equal(actor.appearance, 'hutao'); assert.match(actor.group.name, /胡桃/);
    assert.equal(hutaoStatus.complete, true); assert.equal(hutaoStatus.previewOnly, false); assert.equal(hutaoStatus.reason, null);
    await actor.setAppearance('raiden'); const raiden = actor.mesh;
    assert.equal(actor.appearance, 'raiden'); assert.notEqual(raiden, hutao); assert.notEqual(raiden, native);
    const restored = await actor.setAppearance('hutao');
    assert.equal(restored.available, true); assert.equal(restored.complete, true); assert.equal(actor.mesh, hutao, 'each variant keeps its own cache entry');
    assert.equal(actor.skeleton, skeleton); assert.deepEqual(actor.mesh.skeleton.bones.slice(0, skeleton.bones.length), skeleton.bones); assert.deepEqual(actor.mesh.bindMatrix.toArray(), bind);
    assert.deepEqual(matrices(actor), joints); assert.equal(actor.frame, frame);
    assert.equal(actor.getAttachment('d_wpnR'), hand); assert.equal(weapon.parent, hand); assert.deepEqual(weapon.matrixWorld.toArray(), weaponMatrix);
    await actor.setAppearance('original'); assert.equal(actor.mesh, native); assert.equal(actor.nativeSpace.children.filter(child => child.isSkinnedMesh).length, 1);
  } finally { actor.dispose(); }
}));

test('PMX skin remains bounded across native running, jumping, guarding, attacks and death poses', async () => withFetch(async () => {
  const original = createNativeCharacter(data, { loadTextures: false }), actor = createNativeCharacter(data, { loadTextures: false });
  try {
    await actor.setAppearance('hutao'); assert.equal(actor.appearance, 'hutao');
    for (const id of [6, 16, 90, 117, 144, 151, 152, 200, 202, 248, 262, 263, 264, 279, 295]) {
      const pose = data.poses[id];
      for (const frame of [pose.start, (pose.start + pose.end) / 2, pose.end]) {
        original.setPoseFrame(pose.source, frame); actor.setPoseFrame(pose.source, frame);
        assert.deepEqual(matrices(actor), matrices(original), `pose ${id} frame ${frame}: imported appearance cannot move source joints`);
        actor.mesh.computeBoundingBox(); const box = actor.mesh.boundingBox.clone().applyMatrix4(actor.mesh.matrixWorld);
        assert.ok([...box.min.toArray(), ...box.max.toArray()].every(Number.isFinite));
        assert.ok(box.getSize(new THREE.Vector3()).length() < 10, `pose ${id} frame ${frame}: grossly exploded skin must not pass as a working import`);
      }
    }
  } finally { original.dispose(); actor.dispose(); }
}));

test('the game refuses an incomplete MOD and retains its current HD appearance and mission state', async () => {
  const module = await import('../dist/native-character.js?partial-game-gate'), before = globalThis.fetch;
  const partial = { characterId: 0, appearance: 'hutao', mesh: 'mesh.json', complete: false, completeness: { faceGeometry: false } };
  globalThis.fetch = async url => {
    const path = new URL(url).pathname;
    if (path.endsWith('/enhanced/hutao/manifest.json')) return Response.json(partial);
    if (path.endsWith('/enhanced/hutao/mesh.json')) return Response.json(data.skin);
    return fileFetch(url);
  };
  const character = module.createNativeCharacter(data, { loadTextures: false }), game = Object.create(MeteorGame.prototype), events = [];
  const actor = { id: 1, scriptId: 0, name: '孟星魂', character, root: character.group, hp: 721, maxHp: 1500, rage: 33, weaponId: 5, weapon: 'dagger', vy: 3.2, grounded: false, team: 1, combat: { timeline: { pose: { id: 151 } } } };
  Object.assign(game, { ready: Promise.resolve(), hero: actor, characterId: 0, appearanceRequest: 0, _hud() {}, onEvent: event => events.push(event) });
  character.setPoseFrame(0, data.poses[151].start + 3); character.group.position.set(1, 4, 6);
  const position = character.group.position.toArray(), frame = character.frame;
  try {
    await game.setCharacterAppearance('raiden'); const priorMesh = character.mesh;
    const result = await game.setCharacterAppearance('hutao', { allowIncomplete: true }); // game API deliberately does not accept preview permission
    assert.equal(result.available, false); assert.equal(result.complete, false); assert.match(result.reason, /脸部网格|不完整/);
    assert.equal(character.mesh, priorMesh); assert.equal(character.appearance, 'raiden'); assert.equal(game.characterAppearance, 'raiden'); assert.equal(game.hero, actor); assert.equal(game.characterId, 0);
    assert.equal(actor.name, '孟星魂'); assert.equal(actor.scriptId, 0); assert.equal(actor.team, 1);
    assert.equal(actor.hp, 721); assert.equal(actor.maxHp, 1500); assert.equal(actor.rage, 33); assert.equal(actor.weaponId, 5); assert.equal(actor.vy, 3.2); assert.equal(actor.grounded, false);
    assert.deepEqual(character.group.position.toArray(), position); assert.equal(character.frame, frame); assert.equal(events.at(-1).type, 'appearance');
    assert.equal(events.at(-1).requested, 'hutao'); assert.equal(events.at(-1).appearance, 'raiden');
  } finally { character.dispose(); globalThis.fetch = before; }
});

test('the game adopts complete HuTao without resetting mission identity, HP, weapon, jump or live pose', async () => withFetch(async () => {
  const character = createNativeCharacter(data, { loadTextures: false }), game = Object.create(MeteorGame.prototype), events = [];
  const combat = { timeline: { pose: { id: 151 }, time: .31 }, combo: 2 };
  const actor = { id: 1, scriptId: 0, name: '孟星魂', character, root: character.group, hp: 721, maxHp: 1500, rage: 33, weaponId: 5, weapon: 'dagger', vy: 3.2, grounded: false, team: 1, combat };
  Object.assign(game, { ready: Promise.resolve(), hero: actor, characterId: 0, appearanceRequest: 0, _hud() {}, onEvent: event => events.push(event) });
  character.setPoseFrame(0, data.poses[151].start + 3); character.group.position.set(1, 4, 6); character.group.updateMatrixWorld(true);
  const frame = character.frame, source = character.source, joints = matrices(character), position = character.group.position.toArray();
  const hand = character.getAttachment('d_wpnR'), weapon = new THREE.Group(); hand.add(weapon); character.group.updateMatrixWorld(true);
  const weaponTransform = weapon.matrixWorld.toArray();
  try {
    const result = await game.setCharacterAppearance('hutao');
    assert.equal(result.available, true); assert.equal(result.complete, true); assert.equal(result.previewOnly, false);
    assert.equal(character.appearance, 'hutao'); assert.equal(game.characterAppearance, 'hutao'); assert.equal(game.hero, actor); assert.equal(game.characterId, 0);
    assert.equal(actor.name, '孟星魂'); assert.equal(actor.scriptId, 0); assert.equal(actor.team, 1);
    assert.equal(actor.hp, 721); assert.equal(actor.maxHp, 1500); assert.equal(actor.rage, 33); assert.equal(actor.weaponId, 5); assert.equal(actor.weapon, 'dagger');
    assert.equal(actor.vy, 3.2); assert.equal(actor.grounded, false); assert.equal(actor.combat, combat); assert.equal(combat.timeline.time, .31);
    assert.deepEqual(character.group.position.toArray(), position); assert.deepEqual(matrices(character), joints); assert.equal(character.frame, frame); assert.equal(character.source, source);
    assert.equal(character.getAttachment('d_wpnR'), hand); assert.equal(weapon.parent, hand); assert.deepEqual(weapon.matrixWorld.toArray(), weaponTransform);
    assert.equal(events.at(-1).type, 'appearance'); assert.equal(events.at(-1).appearance, 'hutao');
    await game.setCharacterAppearance('original'); assert.equal(character.appearance, 'original'); assert.equal(game.characterAppearance, 'original'); assert.equal(actor.combat, combat);
  } finally { character.dispose(); }
}));

test('PMX cutout cards preserve depth-writing opaque materials and their supplied alpha threshold', () => {
  const cutout = { ...data.skin.materials[0], name: 'eyelashes', twoSide: true, alphaTest: .42, opacity: 1, transparent: false };
  const character = createNativeCharacter({ ...data, skin: { ...data.skin, materials: [cutout, ...data.skin.materials.slice(1)] } }, { loadTextures: false });
  try {
    const material = character.mesh.material[0];
    assert.equal(material.name, 'eyelashes'); assert.equal(material.alphaTest, .42); assert.equal(material.transparent, false);
    assert.equal(material.depthWrite, true); assert.equal(material.opacity, 1); assert.equal(material.side, THREE.DoubleSide);
  } finally { character.dispose(); }
});

test('a HuTao request for another original character preserves that character instead of loading a P20 substitute', async () => withFetch(async () => {
  const character = createNativeCharacter(await loadNativeCharacterData(1), { loadTextures: false }), original = character.mesh;
  try { const status = await character.setAppearance('hutao'); assert.equal(status.available, false); assert.equal(status.appearance, 'original'); assert.equal(character.mesh, original); assert.equal(character.group.userData.characterId, 1); }
  finally { character.dispose(); }
}));

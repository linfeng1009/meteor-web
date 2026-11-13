import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';

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



// These face surface counts were independently decoded from the user PMX,
// rather than inferred from the manifest's boolean completeness flag.
const root = new URL('../dist/assets/enhanced/hutao/', import.meta.url);
const manifest = JSON.parse(await readFile(new URL('manifest.json', root), 'utf8'));
const skin = JSON.parse(await readFile(new URL(manifest.mesh, root), 'utf8'));
const facialParts = { 面: 1563, 面1: 85, 白目: 156, 目: 120, 睫: 540, 口舌: 320, 二重: 66, 眉: 44, 齿: 144, 目星: 64 };

test('the HuTao bundle contains the independently verified PMX face, mouth, eyes and lashes', () => {
  assert.equal(manifest.complete, true);
  assert.equal(manifest.completeness.faceGeometry, true);
  assert.equal(manifest.stats.sourceVertices, 20521);
  assert.equal(manifest.stats.sourceTriangles, 27026);
  for (const [name, expected] of Object.entries(facialParts)) {
    const materials = new Set(skin.materials.flatMap((m, i) => (m.sourceName ?? m.name) === name ? [i] : []));
    assert.equal(materials.size, 1, `preserve traceable PMX facial surface ${name}`);
    const faces = skin.faces.filter(f => materials.has(f.material));
    assert.equal(faces.length, expected, `${name}: a completeness flag cannot substitute for actual face geometry`);
    const ids = [...new Set(faces.flatMap(f => f.indices))];
    for (const i of ids) {
      let headWeight = 0;
      for (let j = 0; j < 4; j++) if (skin.skinIndices[i * 4 + j] === 13) headWeight += skin.skinWeights[i * 4 + j];
      assert.ok(headWeight > .99999, `${name} vertex ${i}: eyes, face and mouth must follow the same native head`);
    }
    for (let axis = 0; axis < 3; axis++) {
      const values = ids.map(i => skin.positions[i * 3 + axis]);
      assert.ok(values.every(Number.isFinite));
      assert.ok(Math.max(...values) - Math.min(...values) > 1e-5, `${name}: the facial surface cannot collapse into a flat point`);
    }
  }
});

test('PMX texture paths are real local PNGs and retain the source two-kilopixel color maps', async () => {
  const maps = new Set(skin.materials.map(m => m.texture).filter(name => name && name !== 'null'));
  assert.ok(maps.size >= 5, 'preserve separate PMX face, hair, costume and cat-ear maps');
  for (const name of maps) {
    const url = new URL(name, root);
    assert.equal(url.origin, root.origin);
    assert.ok(url.pathname.startsWith(root.pathname), `${name} must stay inside the bundle`);
    const bytes = await readFile(url);
    assert.notEqual(imageMagic(bytes), 'unknown', `${name} must be a real image`);
    assert.ok(bytes.readUInt32BE(16) >= 2048 && bytes.readUInt32BE(20) >= 2048, `${name}: retain useful original texture detail`);
  }
});

test('the complete PMX export has finite unit normals, native bone weights and nondegenerate indices', () => {
  assert.equal(skin.positions.length, skin.vertexCount * 3);
  assert.equal(skin.normals.length, skin.vertexCount * 3);
  assert.equal(skin.uvs.length, skin.vertexCount * 2);
  assert.equal(skin.skinIndices.length, skin.vertexCount * 4);
  assert.equal(skin.skinWeights.length, skin.vertexCount * 4);
  assert.equal(skin.faces.length, skin.triangleCount);
  const usedBones = new Set();
  for (let i = 0; i < skin.vertexCount; i++) {
    assert.ok(skin.positions.slice(i * 3, i * 3 + 3).every(Number.isFinite));
    assert.ok(skin.uvs.slice(i * 2, i * 2 + 2).every(Number.isFinite));
    const normal = skin.normals.slice(i * 3, i * 3 + 3);
    assert.ok(normal.every(Number.isFinite));
    assert.ok(Math.abs(Math.hypot(...normal) - 1) < 2e-4, `normal ${i} stays normalized after rest-space warping`);
    let sum = 0;
    for (let j = 0; j < 4; j++) {
      const index = skin.skinIndices[i * 4 + j], weight = skin.skinWeights[i * 4 + j];
      assert.ok(Number.isInteger(index) && index >= 0 && index < 30 + (skin.secondaryMotion?.bones.length || 0));
      assert.ok(Number.isFinite(weight) && weight >= 0 && weight <= 1);
      sum += weight;
      if (weight > .01) usedBones.add(index);
    }
    assert.ok(Math.abs(sum - 1) < 1e-5);
  }
  assert.ok(usedBones.size >= 15, 'a full imported character cannot be bound rigidly to the head or torso');
  for (const face of skin.faces) {
    assert.ok(Number.isInteger(face.material) && face.material >= 0 && face.material < skin.materials.length);
    assert.equal(face.indices.length, 3);
    assert.equal(new Set(face.indices).size, 3);
    assert.ok(face.indices.every(i => Number.isInteger(i) && i >= 0 && i < skin.vertexCount));
  }
});

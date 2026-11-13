import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { createHash } from 'node:crypto';

// Deployment converts texture atlases to WebP to fit a slow uplink, so a
// runtime texture may be PNG or WebP. These helpers read either container.
const imageMagic = bytes => {
  const head = bytes.subarray(0, 12);
  if (head.subarray(0, 8).toString('hex') === '89504e470d0a1a0a') return 'png';
  if (head.subarray(0, 4).toString('ascii') === 'RIFF' && head.subarray(8, 12).toString('ascii') === 'WEBP') return 'webp';
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


// Counts and alpha-bearing source hashes were independently decoded from the
// user's PMX and PNGs, rather than trusting a manifest's completeness flag.
const root = new URL('../dist/assets/enhanced/raiden/', import.meta.url);
const manifest = JSON.parse(await readFile(new URL('manifest.json', root), 'utf8'));
const skin = JSON.parse(await readFile(new URL(manifest.mesh, root), 'utf8'));
const facialParts = { 面: 1730, 面2: 92, 星目: 64, 口舌: 330, 二重: 36, 白目: 150, 睫: 452, 眉: 48, 齒: 144, 目: 232 };
const nameOf = material => material.sourceName ?? material.name;

test('Raiden retains the independently decoded complete face and rigid eye/mouth alignment', () => {
  assert.equal(manifest.complete, true); assert.equal(manifest.completeness.faceGeometry, true);
  assert.equal(manifest.stats.sourceVertices, 24203); assert.equal(manifest.stats.sourceTriangles, 30604);
  for (const [name, count] of Object.entries(facialParts)) {
    const ids = skin.materials.flatMap((m, i) => nameOf(m) === name ? [i] : []);
    assert.equal(ids.length, 1, `preserve source facial material ${name}`);
    const faces = skin.faces.filter(f => f.material === ids[0]);
    assert.equal(faces.length, count, `${name}: metadata cannot replace the actual face surface`);
    const vertices = [...new Set(faces.flatMap(f => f.indices))];
    for (const vertex of vertices) {
      let head = 0;
      for (let j = 0; j < 4; j++) if (skin.skinIndices[vertex * 4 + j] === 13) head += skin.skinWeights[vertex * 4 + j];
      assert.ok(head > .99999, `${name} vertex ${vertex}: eyes, face and mouth move with the same head`);
    }
    for (let axis = 0; axis < 3; axis++) {
      const values = vertices.map(i => skin.positions[i * 3 + axis]);
      assert.ok(values.every(Number.isFinite));
      assert.ok(Math.max(...values) - Math.min(...values) > 1e-5, `${name} cannot collapse to a point`);
    }
  }
  // A cross-head/torso blend stretched the long hair by 42cm in Pose264.
  // Secondary hair bones must still descend exclusively from the head. A torso
  // influence would reintroduce the old stretching defect during combat poses.
  const headBones = new Set([13]);
  for (const [i, bone] of (skin.secondaryMotion?.bones || []).entries()) {
    assert.ok(headBones.has(bone.parent), 'every hair chain is rooted in the head'); headBones.add(30 + i);
  }
  const hairMaterial = skin.materials.findIndex(m => nameOf(m) === '发'); assert.ok(hairMaterial >= 0);
  const hairVertices = new Set(skin.faces.filter(f => f.material === hairMaterial).flatMap(f => f.indices));
  for (const vertex of hairVertices) {
    let head = 0;
    for (let j = 0; j < 4; j++) if (headBones.has(skin.skinIndices[vertex * 4 + j])) head += skin.skinWeights[vertex * 4 + j];
    assert.ok(head > .99999, `hair vertex ${vertex}: no elastic cross-torso stretching`);
  }
});

test('Raiden preserves seven local color maps and the skin cutouts actually used by source UVs', async () => {
  const maps = new Set(skin.materials.map(m => m.texture).filter(n => n && n !== 'null'));
  assert.equal(maps.size, 7);
  const dimensions = [];
  for (const name of maps) {
    const url = new URL(name, root); assert.ok(url.pathname.startsWith(root.pathname));
    assert.equal(url.origin, root.origin);
    const data = await readFile(url); assert.notEqual(imageMagic(data), 'unknown');
    const size = imageSize(data); dimensions.push(size);
    assert.ok(size.every(n => n >= 1024), `${name}: retain original usable texture resolution`);
  }
  assert.equal(dimensions.filter(size => size.every(n => n >= 2048)).length, 6);
  const expected = { 肌: 'e003fa58e5c86fa933bb76555a9facdb741207b836bc76bcf215e797340b3d24', 肌2: '7ee139bcb9776a9890a974fe4fe2364f51f75f48ea3b166b4a56e7de431fdc8d' };
  for (const [name, hash] of Object.entries(expected)) {
    const material = skin.materials.find(m => nameOf(m) === name); assert.ok(material);
    // hash covers the archived source; the deployed copy may be WebP
    assert.ok(material.texture.endsWith('.webp') || material.texture.endsWith('.png'));
    assert.ok(material.alphaTest > 0 && material.alphaTest < 1, `${name}: source skin has visible alpha cutouts`);
    assert.notEqual(material.transparent, true, `${name}: cutouts should retain stable depth sorting`);
    // Deployment may transcode the atlas to WebP; what matters for the cutout is
    // that the alpha channel survived at the original resolution.
    const data = await readFile(new URL(material.texture, root));
    assert.notEqual(imageMagic(data), 'unknown', `${name}: cutout atlas stays a real image`);
    assert.deepEqual(imageSize(data), [2048, 2048], `${name}: cutout atlas keeps 2K resolution`);
  }
});

test('Raiden geometry uses normalized native and hair skinning with valid triangle surfaces', () => {
  assert.equal(skin.positions.length, skin.vertexCount * 3); assert.equal(skin.normals.length, skin.vertexCount * 3);
  assert.equal(skin.uvs.length, skin.vertexCount * 2); assert.equal(skin.skinIndices.length, skin.vertexCount * 4);
  assert.equal(skin.skinWeights.length, skin.vertexCount * 4); assert.equal(skin.faces.length, skin.triangleCount);
  const used = new Set();
  for (let i = 0; i < skin.vertexCount; i++) {
    assert.ok(skin.positions.slice(i * 3, i * 3 + 3).every(Number.isFinite));
    assert.ok(skin.uvs.slice(i * 2, i * 2 + 2).every(Number.isFinite));
    const normal = skin.normals.slice(i * 3, i * 3 + 3);
    assert.ok(normal.every(Number.isFinite)); assert.ok(Math.abs(Math.hypot(...normal) - 1) < 2e-4);
    let sum = 0;
    for (let j = 0; j < 4; j++) {
      const index = skin.skinIndices[i * 4 + j], weight = skin.skinWeights[i * 4 + j];
      assert.ok(Number.isInteger(index) && index >= 0 && index < 30 + (skin.secondaryMotion?.bones.length || 0));
      assert.ok(Number.isFinite(weight) && weight >= 0 && weight <= 1); sum += weight;
      if (weight > .01) used.add(index);
    }
    assert.ok(Math.abs(sum - 1) < 1e-5);
  }
  assert.ok(used.size >= 15);
  for (const face of skin.faces) {
    assert.ok(Number.isInteger(face.material) && face.material >= 0 && face.material < skin.materials.length);
    assert.equal(face.indices.length, 3); assert.equal(new Set(face.indices).size, 3);
    assert.ok(face.indices.every(i => Number.isInteger(i) && i >= 0 && i < skin.vertexCount));
  }
});

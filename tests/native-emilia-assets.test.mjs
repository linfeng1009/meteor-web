import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { createHash } from 'node:crypto';

const root = new URL('../dist/assets/enhanced/emilia/', import.meta.url);
const manifest = JSON.parse(await readFile(new URL('manifest.json', root), 'utf8'));
const skin = JSON.parse(await readFile(new URL(manifest.mesh, root), 'utf8'));
// Independently decoded from the user PMX, including the actual ordinary body
// surfaces. SHADING is a duplicate alpha overlay, verified to 1.91e-6 in source
// position/UV and identical weights; it is composed into the cloth color map.
const surfaces = { Cloth: 6978, Skin: 2640, Face: 1274, Face_NoOutline: 696, EYEBROW: 12, Hair: 2056, HairFront: 94, FlowerAcc: 486 };
const faceNames = new Set(['Face', 'Face_NoOutline', 'EYEBROW']);
const name = material => material.sourceName ?? material.name;
const originalHashes = { 'FACE.png': '7e67bbb000da3b9fe679cd8b119ccaaad7d848646f1a93bc29aa2e1779cc6367', 'HAIR.png': '6c335f00707e139c950359ea08cb98a21a9b583e103370e9c7e25eae4020fea0', 'ACCS.png': 'cc0fe917e269e94057b57f63c8ca2864b3c0b6c4075b8a23cdb7ea99244878d1' };
const sha256 = bytes => createHash('sha256').update(bytes).digest('hex');

test('Emilia keeps the real body, complete face and hair rather than substituting a completeness flag', () => {
  assert.equal(manifest.complete, true); assert.equal(manifest.completeness.faceGeometry, true);
  assert.equal(manifest.stats.sourceVertices, 16493); assert.equal(manifest.stats.sourceTriangles, 23854);
  assert.equal(skin.triangleCount, 14236);
  for (const [surface, count] of Object.entries(surfaces)) {
    const materials = new Set(skin.materials.flatMap((m, i) => name(m) === surface ? [i] : []));
    assert.equal(materials.size, 1, `one source ${surface} surface`);
    const faces = skin.faces.filter(face => materials.has(face.material));
    assert.equal(faces.length, count, `${surface}: preserve independently counted actual source geometry`);
    if (faceNames.has(surface)) for (const vertex of new Set(faces.flatMap(face => face.indices))) {
      let weight = 0;
      for (let j = 0; j < 4; j++) if (skin.skinIndices[vertex * 4 + j] === 13) weight += skin.skinWeights[vertex * 4 + j];
      assert.ok(weight > .99999, `${surface} ${vertex}: the face, eyes and mouth must follow one native head`);
    }
  }
  assert.equal(skin.materials.some(m => name(m) === 'SHADING'), false, 'avoid coplanar duplicate shading geometry');
});

test('Emilia keeps original face, hair and accessory maps and a full-resolution composed cloth map', async () => {
  const maps = new Set(skin.materials.map(m => m.texture).filter(Boolean)); assert.equal(maps.size, 4);
  const dimensions = new Map();
  for (const map of maps) {
    const path = new URL(map, root); assert.ok(path.pathname.startsWith(root.pathname));
    const bytes = await readFile(path); assert.equal(bytes.subarray(0, 8).toString('hex'), '89504e470d0a1a0a');
    dimensions.set(map, [bytes.readUInt32BE(16), bytes.readUInt32BE(20)]);
  }
  for (const [surface, source, resolution] of [['Face', 'FACE.png', 1024], ['Hair', 'HAIR.png', 1024], ['FlowerAcc', 'ACCS.png', 512]]) {
    const material = skin.materials.find(m => name(m) === surface);
    assert.deepEqual(dimensions.get(material.texture), [resolution, resolution]);
    assert.equal(sha256(await readFile(new URL(material.texture, root))), originalHashes[source], `${surface}: original color detail remains lossless`);
  }
  const cloth = skin.materials.find(m => name(m) === 'Cloth'), body = skin.materials.find(m => name(m) === 'Skin');
  assert.equal(cloth.texture, body.texture); assert.deepEqual(dimensions.get(cloth.texture), [2048, 2048]);
});

test('Emilia geometry has finite unit normals and normalized compatible native bone weights', () => {
  assert.equal(skin.positions.length, skin.vertexCount * 3); assert.equal(skin.normals.length, skin.vertexCount * 3);
  assert.equal(skin.uvs.length, skin.vertexCount * 2); assert.equal(skin.skinIndices.length, skin.vertexCount * 4);
  assert.equal(skin.skinWeights.length, skin.vertexCount * 4); assert.equal(skin.faces.length, skin.triangleCount);
  const bones = new Set();
  for (let i = 0; i < skin.vertexCount; i++) {
    assert.ok(skin.positions.slice(i * 3, i * 3 + 3).every(Number.isFinite));
    assert.ok(skin.uvs.slice(i * 2, i * 2 + 2).every(Number.isFinite));
    assert.ok(Math.abs(Math.hypot(...skin.normals.slice(i * 3, i * 3 + 3)) - 1) < 2e-4);
    let sum = 0;
    for (let j = 0; j < 4; j++) {
      const bone = skin.skinIndices[i * 4 + j], weight = skin.skinWeights[i * 4 + j];
      assert.ok(Number.isInteger(bone) && bone >= 0 && bone < 30 + (skin.secondaryMotion?.bones.length || 0)); assert.ok(Number.isFinite(weight) && weight >= 0);
      sum += weight; if (weight > .01) bones.add(bone);
    }
    assert.ok(Math.abs(sum - 1) < 2e-5);
  }
  assert.ok(bones.size >= 14);
  for (const face of skin.faces) { assert.equal(new Set(face.indices).size, 3); assert.ok(face.indices.every(i => Number.isInteger(i) && i >= 0 && i < skin.vertexCount)); assert.ok(Number.isInteger(face.material) && face.material >= 0 && face.material < skin.materials.length); }
});

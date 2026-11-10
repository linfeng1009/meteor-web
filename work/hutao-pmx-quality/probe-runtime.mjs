import { readFile, writeFile } from 'node:fs/promises';
import * as THREE from '../../dist/vendor/three.module.js';
import { loadNativeCharacterData, createNativeCharacter, loadEnhancedCharacterData } from '../../dist/native-character.js';
const before = globalThis.fetch;
globalThis.fetch = async url => { try { return new Response(await readFile(new URL(url))); } catch { return new Response('', { status: 404 }); } };
const data = await loadNativeCharacterData(0), asset = await loadEnhancedCharacterData(0, 'hutao');
const actor = createNativeCharacter(data, { loadTextures: false });
await actor.setAppearance('hutao');
const skin = asset.skin, n = skin.vertexCount;
const facialNames = new Set(['面', '面1', '白目', '目', '睫', '口舌', '二重', '眉', '齿', '目星']);
const faceMaterials = new Set(skin.materials.flatMap((m, i) => facialNames.has(m.name) ? [i] : []));
const faceIds = new Set(skin.faces.filter(f => faceMaterials.has(f.material)).flatMap(f => f.indices));
const facialWeights = new Map();
for (const i of faceIds) for (let j = 0; j < 4; j++) {
  const w = skin.skinWeights[i * 4 + j];
  if (w > 1e-6) facialWeights.set(skin.skinIndices[i * 4 + j], (facialWeights.get(skin.skinIndices[i * 4 + j]) ?? 0) + 1);
}
const edges = [...new Map(skin.faces.flatMap(f => [[f.indices[0], f.indices[1]], [f.indices[1], f.indices[2]], [f.indices[2], f.indices[0]]]).map(([a, b]) => [a < b ? `${a}:${b}` : `${b}:${a}`, [a, b]])).values()];
const restDistance = (a, b) => Math.hypot(...[0, 1, 2].map(k => (skin.positions[a * 3 + k] - skin.positions[b * 3 + k]) * .08));
const restLengths = edges.map(([a, b]) => restDistance(a, b));
const facialEdges = edges.flatMap(([a, b], i) => faceIds.has(a) && faceIds.has(b) && restLengths[i] > .00001 ? [i] : []);
const points = new Array(n), results = [], v = new THREE.Vector3();
for (const id of [6, 16, 90, 117, 144, 151, 152, 200, 202, 248, 262, 263, 264, 279, 295]) {
  const pose = data.poses[id];
  for (const frame of [pose.start, (pose.start + pose.end) / 2, pose.end]) {
    actor.setPoseFrame(pose.source, frame);
    const box = new THREE.Box3();
    for (let i = 0; i < n; i++) {
      v.fromArray(skin.positions, i * 3); actor.mesh.applyBoneTransform(i, v); actor.mesh.localToWorld(v);
      if (!v.toArray().every(Number.isFinite)) throw new Error(`nonfinite pose ${id} frame ${frame} vertex ${i}`);
      points[i] = v.clone(); box.expandByPoint(v);
    }
    const lengths = edges.map(([a, b]) => points[a].distanceTo(points[b]));
    const ratios = lengths.flatMap((length, i) => restLengths[i] > .00001 ? [length / restLengths[i]] : []);
    ratios.sort((a,b)=>a-b);
    let worst = 0;
    for (let i = 0; i < edges.length; i++) if (restLengths[i] > .00001 && lengths[i] / restLengths[i] > (restLengths[worst] > .00001 ? lengths[worst] / restLengths[worst] : 0)) worst = i;
    const [a,b] = edges[worst];
    const materials = [...new Set(skin.faces.filter(f=>f.indices.includes(a) && f.indices.includes(b)).map(f=>skin.materials[f.material].name))];
    const faceRatios = facialEdges.map(i => lengths[i] / restLengths[i]);
    results.push({ id, frame, source: pose.source, bounds: [box.min.toArray(), box.max.toArray()], dimensions: box.getSize(new THREE.Vector3()).toArray(), edgeStretchRatio: { p90: ratios[Math.floor(ratios.length * .9)], p99: ratios[Math.floor(ratios.length * .99)], max: ratios.at(-1) }, worstEdge: { a,b,materials,restLength:restLengths[worst],length:lengths[worst] }, faceEdgeStretchRange: [Math.min(...faceRatios), Math.max(...faceRatios)], maxEdgeLength: Math.max(...lengths), base: actor.getAttachment('d_base').getWorldPosition(v).toArray() });
  }
}
const report = { vertices: n, triangles: skin.triangleCount, facialVertices: faceIds.size, facialBones: [...facialWeights].map(([index,count]) => ({ index, name: data.skeleton.bones[index].name, count })), frames: results.length, maxDimensionDiagonal: Math.max(...results.map(r=>Math.hypot(...r.dimensions))), maxEdgeStretchRatio: Math.max(...results.map(r=>r.edgeStretchRatio.max)), maxFaceStretch: Math.max(...results.map(r=>r.faceEdgeStretchRange[1])), poses: results };
await writeFile(new URL('runtime-audit.json', import.meta.url), JSON.stringify(report,null,2));
console.log(JSON.stringify({ ...report, poses: undefined }, null, 2));
actor.dispose(); globalThis.fetch = before;

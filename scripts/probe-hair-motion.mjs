import { readFile, writeFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { createNativeCharacter, loadNativeCharacterData } from '../dist/native-character.js';

globalThis.fetch = async url => {
  try { return new Response(await readFile(new URL(url))); }
  catch { return new Response('', { status: 404 }); }
};
const data = await loadNativeCharacterData(0), results = [];
const point = new THREE.Vector3(), other = new THREE.Vector3();
function hairVertices(skin) {
  const materials = new Set(skin.secondaryMotion.hairMaterials);
  return [...new Set(skin.faces.filter(f => materials.has(f.material)).flatMap(f => f.indices))];
}
function vertex(mesh, id, out) {
  out.fromBufferAttribute(mesh.geometry.attributes.position, id);
  mesh.applyBoneTransform(id, out); return mesh.localToWorld(out);
}
for (const name of ['hutao', 'raiden', 'emilia']) {
  const skin = JSON.parse(await readFile(new URL(`../dist/assets/enhanced/${name}/mesh.json`, import.meta.url)));
  const ids = hairVertices(skin), live = createNativeCharacter(data, { loadTextures: false }), rigid = createNativeCharacter(data, { loadTextures: false, secondaryMotion: false });
  await live.setAppearance(name); await rigid.setAppearance(name);
  let maxOffset = 0, maxLengthError = 0, maxAngle = 0, peakAfterStop = 0, settledStep = 0;
  const inverseBindHead = live.skeleton.boneInverses[13].clone();
  const restHeadQ = new THREE.Quaternion(); inverseBindHead.clone().invert().decompose(new THREE.Vector3(), restHeadQ, new THREE.Vector3()); restHeadQ.invert();
  const axes = skin.secondaryMotion.bones.map(b => new THREE.Vector3().fromArray(b.tail).sub(new THREE.Vector3().fromArray(b.position)).normalize().applyQuaternion(restHeadQ));
  for (let frame = 0; frame < 240; frame++) {
    const moving = frame < 150, t = Math.min(frame, 149) / 60, pose = data.poses[144];
    for (const actor of [live, rigid]) {
      actor.group.position.set(Math.sin(t * 2) * .4, moving && frame > 75 ? Math.max(0, Math.sin((frame - 75) / 60 * Math.PI * 2)) * .5 : 0, 0);
      actor.group.rotation.y = Math.sin(t * 3) * .65;
      actor.setPoseFrame(pose.source, pose.start + (t * 30) % (pose.end - pose.start));
    }
    live.updateSecondaryMotion(1 / 60, { groundY: 0 });
    rigid.group.updateMatrixWorld(true); rigid.mesh.skeleton.update();
    for (const id of ids) maxOffset = Math.max(maxOffset, vertex(live.mesh, id, point).distanceTo(vertex(rigid.mesh, id, other)));
    const headQ = live.bones[13].getWorldQuaternion(new THREE.Quaternion()), snapshot = live.getSecondaryMotionSnapshot();
    let stepMotion = 0;
    snapshot.forEach((n, i) => {
      point.fromArray(n.tail).sub(other.fromArray(n.position));
      maxLengthError = Math.max(maxLengthError, Math.abs(point.length() - n.length));
      maxAngle = Math.max(maxAngle, point.normalize().angleTo(axes[i].clone().applyQuaternion(headQ)));
      stepMotion = Math.max(stepMotion, new THREE.Vector3().fromArray(n.tail).distanceTo(new THREE.Vector3().fromArray(n.previous)));
    });
    if (frame >= 150 && frame < 180) peakAfterStop = Math.max(peakAfterStop, stepMotion);
    if (frame === 239) settledStep = stepMotion;
  }
  results.push({ name, bones: skin.secondaryMotion.bones.length, maxHairVertexOffsetWorld: maxOffset, maxAngleDegrees: THREE.MathUtils.radToDeg(maxAngle), maxLengthError, peakStepAfterStop: peakAfterStop, settledStep });
  live.dispose(); rigid.dispose();
}
await writeFile(new URL('../work/hair-physics-2026-11-10/restrained-motion.json', import.meta.url), JSON.stringify(results, null, 2));
console.log(JSON.stringify(results, null, 2));

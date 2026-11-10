import * as THREE from './vendor/three.module.js';

// Visible-model adapter. POS supplies the draw/return phases; original DES
// trail endpoints supply the blade/sheath axes and seated tip. This is not a
// claim that the native renderer's complete binding compensation is recovered.
const CLOSING = [431, 441], DRAWING = [447, 448, 449, 450, 451, 522];
const CLOSED = [403, 486, 487, 520, 521];
const OPEN = [401, 402, 430, 432, 433, 434, 435, 436, 437, 438, 439, 440, 442, 443, 444, 445, 452, 453, 454, 455, 456];
const progress = (frame, from, to) => to > from ? THREE.MathUtils.clamp((frame - from) / (to - from), 0, 1) : 1;

export function qiankunSheathWeight(data, pose, { mode = 'blade', rootPoseId = null } = {}) {
  if (pose.blend) {
    const { from, to, weight } = pose.blend;
    return THREE.MathUtils.lerp(qiankunSheathWeight(data, from, { mode, rootPoseId }), qiankunSheathWeight(data, to, { mode, rootPoseId }), weight);
  }
  const at = id => { const p = data.poses.get(id); return p && p.source === pose.source && pose.frame >= p.start && pose.frame <= p.end + 1e-6 ? p : null; };
  for (const id of CLOSING) { const p = at(id); if (p) return progress(pose.frame, p.entryFrame, p.end); }
  const returning = at(485);
  if (returning) return CLOSING.includes(rootPoseId) ? 1 : progress(pose.frame, returning.start, returning.end);
  const finish = at(524);
  if (finish) return progress(pose.frame, finish.start, finish.end);
  if (CLOSED.some(at)) return 1;
  for (const id of DRAWING) {
    const p = at(id); if (!p) continue;
    const end = [447, 448].includes(id) ? p.end : Math.min(p.end, ...p.attacks.map(a => a.start));
    return 1 - progress(pose.frame, p.entryFrame, end);
  }
  if (OPEN.some(at)) return 0;
  return mode === 'sheath' ? 1 : 0;
}

export function qiankunSeatedBlade(manifest, bladeId, sheathId) {
  const point = (id, name) => {
    const value = manifest.weaponAttachments?.[id.toLowerCase()]?.[name]?.position;
    if (!value || value.length !== 3 || !value.every(Number.isFinite)) throw new Error(`Missing original qiankun socket ${id}/${name}`);
    return new THREE.Vector3(...value);
  };
  const base = point(bladeId, 'd_wpnrs'), tip = point(bladeId, 'd_wpnre');
  const end = point(sheathId, 'd_wpnls'), nearEnd = point(sheathId, 'd_wpnle');
  const rotation = new THREE.Quaternion().setFromUnitVectors(tip.clone().sub(base).normalize(), end.clone().sub(nearEnd).normalize());
  const position = end.clone().sub(tip.clone().applyQuaternion(rotation));
  return new THREE.Matrix4().compose(position, rotation, new THREE.Vector3(1, 1, 1));
}

export function bindQiankunGrip(actor, data, manifest) {
  const blade = actor.weaponModels.find(model => /r$/i.test(model.name));
  const sheath = actor.weaponModels.find(model => /l$/i.test(model.name));
  const left = actor.character.getAttachment('d_wpnLP'), right = actor.character.getAttachment('d_wpnRP');
  if (!blade || !sheath || !left || !right) throw new Error('Original qiankun grip is incomplete');
  const seated = qiankunSeatedBlade(manifest, blade.name, sheath.name);
  const closedPosition = new THREE.Vector3(), closedRotation = new THREE.Quaternion(), unit = new THREE.Vector3();
  seated.decompose(closedPosition, closedRotation, unit);
  const local = new THREE.Matrix4(), loaderUndo = new THREE.Matrix4().makeRotationX(Math.PI / 2);
  const position = new THREE.Vector3(), rotation = new THREE.Quaternion(), scale = new THREE.Vector3();
  // Both parts share the sheath's palm while closing. At weight zero the
  // inverse/compose reconstructs the unchanged right-palm grip exactly.
  left.add(blade); left.add(sheath); blade.matrixAutoUpdate = false;
  const update = pose => {
    const weight = qiankunSheathWeight(data, pose, { mode: actor.combat.weaponMode, rootPoseId: actor.combat.currentMove?.poseId });
    local.copy(left.matrixWorld).invert().multiply(right.matrixWorld).decompose(position, rotation, scale);
    position.lerp(closedPosition, weight); rotation.slerp(closedRotation, weight);
    blade.matrix.compose(position, rotation, scale).multiply(loaderUndo);
    blade.matrixWorldNeedsUpdate = true; blade.updateMatrixWorld(true);
    actor.qiankunSheathWeight = weight;
  };
  update({ source: actor.character.source, frame: actor.character.frame });
  return actor.character.onPoseUpdate(update);
}

import * as THREE from './vendor/three.module.js';

// Cosmetic secondary skeleton. Native BNC bones, animation and gameplay never
// receive physics transforms. Units below are the host's Web world units.
const STEP = 1 / 90;
const finite3 = v => Array.isArray(v) && v.length === 3 && v.every(Number.isFinite);
const clamp = THREE.MathUtils.clamp;

export function validateHairRig(rig, nativeCount = 30) {
  if (!rig) return 0;
  if (rig.schema !== 1 || rig.type !== 'web-spring-bone' || rig.nativeBoneCount !== nativeCount || !Array.isArray(rig.bones) || !rig.bones.length || rig.bones.length > 128 || !Array.isArray(rig.colliders)) throw new Error('Invalid hair spring rig');
  const names = new Set();
  for (let i = 0; i < rig.bones.length; i++) {
    const b = rig.bones[i];
    if (typeof b.name !== 'string' || names.has(b.name) || !Number.isInteger(b.parent) || b.parent < 0 || b.parent >= nativeCount + i || !finite3(b.position) || !finite3(b.tail) || !Array.isArray(b.rotation) || b.rotation.length !== 4 || !b.rotation.every(Number.isFinite) || Math.abs(Math.hypot(...b.rotation) - 1) > .001 || Math.hypot(...b.tail.map((v,j) => v-b.position[j])) < .001) throw new Error('Invalid hair spring bone');
    for (const [key, min, max] of [['stiffness', 1, 500], ['damping', .1, 40], ['maxAngle', .01, 1.4], ['gravity', 0, 1], ['radius', 0, 2]]) if (!Number.isFinite(b[key]) || b[key] < min || b[key] > max) throw new Error('Invalid hair spring parameters');
    for (const [key, min, max] of [['follow', 0, 1], ['globalMaxAngle', .005, 1.4]]) if (b[key] !== undefined && (!Number.isFinite(b[key]) || b[key] < min || b[key] > max)) throw new Error('Invalid hair spring parameters');
    names.add(b.name);
  }
  for (const c of rig.colliders) if (!['sphere', 'capsule'].includes(c.shape) || !Number.isInteger(c.bone) || c.bone < 0 || c.bone >= nativeCount || (c.shape === 'capsule' && (!Number.isInteger(c.endBone) || c.endBone < 0 || c.endBone >= nativeCount)) || (c.offset && !finite3(c.offset)) || !Number.isFinite(c.radius) || c.radius <= 0 || c.radius > 10) throw new Error('Invalid hair spring collider');
  return rig.bones.length;
}

export function createHairSprings({ rig, nativeBones, nativeSkeleton, root }) {
  validateHairRig(rig, nativeBones.length);
  const nativeCount = nativeBones.length, bones = [], nodes = [], roots = [];
  const inverses = nativeSkeleton.boneInverses.map(m => m.clone());
  const bindMatrices = nativeSkeleton.boneInverses.map(m => m.clone().invert());
  const tempMatrix = new THREE.Matrix4(), tempScale = new THREE.Vector3();
  const headRestQ=new THREE.Quaternion();bindMatrices[13].decompose(new THREE.Vector3(),headRestQ,new THREE.Vector3());headRestQ.invert();
  for (const spec of rig.bones) {
    const rest = new THREE.Matrix4().compose(new THREE.Vector3().fromArray(spec.position), new THREE.Quaternion().fromArray(spec.rotation), new THREE.Vector3(1,1,1));
    const local = tempMatrix.copy(bindMatrices[spec.parent]).invert().multiply(rest);
    const bone = new THREE.Bone(); bone.name = spec.name;
    local.decompose(bone.position, bone.quaternion, bone.scale);
    (spec.parent < nativeCount ? nativeBones[spec.parent] : bones[spec.parent-nativeCount]).add(bone);
    if (spec.parent < nativeCount) roots.push(bone);
    const axis = new THREE.Vector3().fromArray(spec.tail).sub(new THREE.Vector3().fromArray(spec.position));
    const length = axis.length(); axis.normalize().applyQuaternion(new THREE.Quaternion().fromArray(spec.rotation).invert());
    const settings={...spec,follow:spec.follow??.98,globalMaxAngle:spec.globalMaxAngle??.04};
    const headAxis=new THREE.Vector3().fromArray(spec.tail).sub(new THREE.Vector3().fromArray(spec.position)).normalize().applyQuaternion(headRestQ);
    nodes.push({ spec:settings, bone, restQuaternion: bone.quaternion.clone(), axis,headAxis,length, current: new THREE.Vector3(), previous: new THREE.Vector3(), previousAnchor:new THREE.Vector3(),previousBase:new THREE.Quaternion(),headRadius: null });
    bones.push(bone); bindMatrices.push(rest); inverses.push(rest.clone().invert());
  }
  const skeleton = new THREE.Skeleton([...nativeBones, ...bones], inverses);
  const colliders = rig.colliders.map(spec => ({ spec, a: new THREE.Vector3(), b: new THREE.Vector3(), radius: 0 }));
  const anchor = new THREE.Vector3(), target = new THREE.Vector3(), direction = new THREE.Vector3(), restDirection = new THREE.Vector3(), next = new THREE.Vector3(), velocity = new THREE.Vector3();
  const point = new THREE.Vector3(), closest = new THREE.Vector3(), segment = new THREE.Vector3(), normal = new THREE.Vector3(),headDirection=new THREE.Vector3(),anchorDelta=new THREE.Vector3();
  const parentQ = new THREE.Quaternion(), baseQ = new THREE.Quaternion(), deltaQ = new THREE.Quaternion(), desiredQ = new THREE.Quaternion(), limitedQ = new THREE.Quaternion();
  const previousRoot = new THREE.Vector3(), currentRoot = new THREE.Vector3(), previousHeadQ = new THREE.Quaternion(), headQ = new THREE.Quaternion();
  let enabled = true, initialized = false, accumulator = 0, time = 0, resets = 0, ground = null, disposed = false;

  function updateColliders() {
    for (const c of colliders) {
      c.a.fromArray(c.spec.offset || [0,0,0]).applyMatrix4(nativeBones[c.spec.bone].matrixWorld);
      c.b.copy(c.spec.shape === 'capsule' ? nativeBones[c.spec.endBone].getWorldPosition(point) : c.a);
      c.radius = c.spec.radius * nativeBones[c.spec.bone].getWorldScale(tempScale).x;
    }
  }
  function nearest(c, p, out) {
    if (c.spec.shape === 'sphere') return out.copy(c.a);
    segment.subVectors(c.b,c.a); const length2=segment.lengthSq();
    return out.copy(c.a).addScaledVector(segment, length2 ? clamp(normal.subVectors(p,c.a).dot(segment)/length2,0,1) : 0);
  }
  function restState(node) {
    node.bone.parent.getWorldQuaternion(parentQ);
    baseQ.copy(parentQ).multiply(node.restQuaternion);
    node.bone.getWorldPosition(anchor);
    restDirection.copy(node.axis).applyQuaternion(baseQ).normalize();
    return node.length * node.bone.getWorldScale(tempScale).x;
  }
  function reset() {
    if (disposed) return;
    accumulator=0; resets++;
    for (const n of nodes) n.bone.quaternion.copy(n.restQuaternion);
    root.updateMatrixWorld(true); updateColliders();
    for (const n of nodes) {
      const length=restState(n); n.current.copy(anchor).addScaledVector(restDirection,length); n.previous.copy(n.current);
      // Authored bangs may intentionally touch the face. Fit the skull sphere
      // to their rest clearance, instead of popping them off the forehead.
      n.headRadius=colliders.map(c=>{
        const endClearance=n.current.distanceTo(nearest(c,n.current,closest));point.copy(anchor).lerp(n.current,.5);
        const midClearance=point.distanceTo(nearest(c,point,closest));
        return Math.max(.008,Math.min(c.radius,Math.min(endClearance,midClearance)*.90-n.spec.radius*tempScale.x));
      });
      n.previousAnchor.copy(anchor);n.previousBase.copy(baseQ);
    }
    root.getWorldPosition(previousRoot); nativeBones[13].getWorldQuaternion(previousHeadQ);
    if (ground === null) ground=previousRoot.y;
    initialized=true; skeleton.update();
  }
  function constrainLength(length) {
    direction.subVectors(next,anchor);
    if (direction.lengthSq() < 1e-12) direction.copy(restDirection); else direction.normalize();
    next.copy(anchor).addScaledVector(direction,length);
  }
  function constrainAngle(axis,maximum,length){
    direction.subVectors(next,anchor).normalize();const angle=axis.angleTo(direction);
    if(angle>maximum){deltaQ.setFromUnitVectors(axis,direction);limitedQ.identity().slerp(deltaQ,maximum/angle);next.copy(anchor).addScaledVector(direction.copy(axis).applyQuaternion(limitedQ),length);}
  }
  function step() {
    for (const n of nodes) {
      n.bone.quaternion.copy(n.restQuaternion); n.bone.updateWorldMatrix(true,false);
      const length=restState(n), spec=n.spec;
      // Transport most of the root motion. Only a small fraction becomes hair
      // inertia; full world-space inertia made short strands whip to the limit.
      deltaQ.copy(baseQ).multiply(limitedQ.copy(n.previousBase).invert());limitedQ.identity().slerp(deltaQ,spec.follow);
      anchorDelta.subVectors(anchor,n.previousAnchor).multiplyScalar(spec.follow);
      n.current.sub(n.previousAnchor).applyQuaternion(limitedQ).add(n.previousAnchor).add(anchorDelta);
      n.previous.sub(n.previousAnchor).applyQuaternion(limitedQ).add(n.previousAnchor).add(anchorDelta);
      target.copy(anchor).addScaledVector(restDirection,length);
      velocity.subVectors(n.current,n.previous).multiplyScalar(Math.exp(-spec.damping*STEP));
      next.copy(n.current).add(velocity).addScaledVector(target.sub(n.current),spec.stiffness*STEP*STEP);
      next.y -= 9.8*spec.gravity*STEP*STEP;
      constrainLength(length);
      // A cone around the animated parent's rest direction limits whipping.
      constrainAngle(restDirection,spec.maxAngle,length);
      headDirection.copy(n.headAxis).applyQuaternion(headQ).normalize();constrainAngle(headDirection,spec.globalMaxAngle,length);
      if (spec.depth > 0) for (let pass=0; pass<4; pass++) {
        for (let i=0;i<colliders.length;i++) {
          const c=colliders[i], radius=Math.min(c.radius,n.headRadius[i])+spec.radius*tempScale.x;
          for (const fraction of [.5,1]) {
            point.copy(anchor).lerp(next,fraction); nearest(c,point,closest); normal.subVectors(point,closest);
            const distance=normal.length();
            if (distance < radius) {
              if (distance < 1e-7) normal.copy(restDirection); else normal.multiplyScalar(1/distance);
              next.addScaledVector(normal,Math.min(.012,(radius-distance)/fraction)); constrainLength(length);
            }
          }
        }
        if (ground !== null && next.y < ground+.018) { next.y=ground+.018; constrainLength(length); }
      }
      // Limit the complete strand relative to the head as well as each link.
      // Per-link cones alone accumulated into very large swings on long tails.
      constrainAngle(restDirection,spec.maxAngle,length);constrainAngle(headDirection,spec.globalMaxAngle,length);
      n.previous.copy(n.current); n.current.copy(next);
      n.previousAnchor.copy(anchor);n.previousBase.copy(baseQ);
      deltaQ.setFromUnitVectors(restDirection,direction.subVectors(next,anchor).normalize());
      desiredQ.copy(deltaQ).multiply(baseQ); n.bone.quaternion.copy(parentQ).invert().multiply(desiredQ).normalize();
      n.bone.updateMatrixWorld(true);
    }
    time+=STEP;
  }
  function update(dt, { groundY } = {}) {
    if (disposed || !enabled || !Number.isFinite(dt) || dt < 0) return;
    root.updateMatrixWorld(true);
    if (Number.isFinite(groundY)) ground=groundY;
    root.getWorldPosition(currentRoot); nativeBones[13].getWorldQuaternion(headQ);
    if (!initialized || dt > .2 || currentRoot.distanceTo(previousRoot) > 1.5 || headQ.angleTo(previousHeadQ) > 2.4) reset();
    previousRoot.copy(currentRoot); previousHeadQ.copy(headQ);
    updateColliders(); accumulator+=Math.min(dt,.0667);
    let iterations=0;
    while (accumulator+1e-10 >= STEP && iterations++ < 7) { step(); accumulator-=STEP; }
    root.updateMatrixWorld(true); skeleton.update();
  }
  return {
    skeleton, bones, update, reset,
    setEnabled(value) { enabled=!!value; reset(); },
    get status() { return { available:true, enabled, bones:bones.length, colliders:colliders.length, time, resets }; },
    snapshot() { return nodes.map(n => ({ name:n.spec.name, position:n.bone.getWorldPosition(new THREE.Vector3()).toArray(), tail:n.current.toArray(), previous:n.previous.toArray(), length:n.length*n.bone.getWorldScale(new THREE.Vector3()).x })); },
    dispose() { if(disposed)return; disposed=true; roots.forEach(b=>b.removeFromParent()); skeleton.dispose(); }
  };
}

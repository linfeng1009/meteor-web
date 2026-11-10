import * as THREE from './vendor/three.module.js';

const vector=value=>Array.isArray(value)&&value.length===3&&value.every(Number.isFinite);
export function validateProportionalRig(rig,nativeCount=30){
  if(!rig)return;
  if(rig.schema!==1||rig.type!=='source-proportions'||!Array.isArray(rig.bones)||rig.bones.length!==nativeCount||!vector(rig.nativeRootBind))throw new Error('Invalid source-proportion rig');
  for(let i=0;i<rig.bones.length;i++){
    const b=rig.bones[i];
    if(b.nativeBone!==i||typeof b.name!=='string'||!Number.isInteger(b.parent)||b.parent< -1||b.parent>=i||!vector(b.position)||!Array.isArray(b.rotation)||b.rotation.length!==4||!b.rotation.every(Number.isFinite)||Math.abs(Math.hypot(...b.rotation)-1)>.001)throw new Error('Invalid source-proportion bone');
  }
}

// Native bones continue to own gameplay and AMB/POS sampling. Only this display
// skeleton uses source joint spacing; source mesh positions are never warped.
export function createProportionalRig({rig,nativeBones,nativeSpace}){
  validateProportionalRig(rig,nativeBones.length);
  const bones=[],restMatrices=[],roots=[],local=new THREE.Matrix4();
  for(const spec of rig.bones){
    const rest=new THREE.Matrix4().compose(new THREE.Vector3().fromArray(spec.position),new THREE.Quaternion().fromArray(spec.rotation),new THREE.Vector3(1,1,1));
    const bone=new THREE.Bone();bone.name='source-display_'+spec.name;
    local.copy(spec.parent<0?rest:restMatrices[spec.parent].clone().invert().multiply(rest));
    local.decompose(bone.position,bone.quaternion,bone.scale);
    (spec.parent<0?nativeSpace:bones[spec.parent]).add(bone);
    if(spec.parent<0)roots.push(bone);
    bones.push(bone);restMatrices.push(rest);
  }
  const skeleton=new THREE.Skeleton(bones,restMatrices.map(m=>m.clone().invert()));
  const inverseSpace=new THREE.Matrix4(),nativeMatrix=new THREE.Matrix4();
  const position=new THREE.Vector3(),rotation=new THREE.Quaternion(),scale=new THREE.Vector3(),parentRotation=new THREE.Quaternion();
  const worldRotations=bones.map(()=>new THREE.Quaternion());
  let restPose=false,disposed=false;
  function sync(){
    if(disposed)return;
    inverseSpace.copy(nativeSpace.matrixWorld).invert();
    for(let i=0;i<bones.length;i++){
      const bone=bones[i],spec=rig.bones[i];
      if(restPose){
        local.copy(spec.parent<0?restMatrices[i]:restMatrices[spec.parent].clone().invert().multiply(restMatrices[i]));
        local.decompose(bone.position,bone.quaternion,bone.scale);
      }else{
        nativeMatrix.multiplyMatrices(inverseSpace,nativeBones[spec.nativeBone].matrixWorld).decompose(position,rotation,scale);
        worldRotations[i].copy(rotation);
        if(spec.parent<0){
          bone.position.fromArray(spec.position).add(position.sub(new THREE.Vector3().fromArray(rig.nativeRootBind)));
          bone.quaternion.copy(rotation);
        }else{
          bone.quaternion.copy(parentRotation.copy(worldRotations[spec.parent]).invert()).multiply(rotation).normalize();
        }
      }
    }
    roots.forEach(b=>b.updateMatrixWorld(true));skeleton.update();
  }
  return{bones,skeleton,sync,restMatrices,setRestPose(value){restPose=!!value;sync();},get restPose(){return restPose;},dispose(){if(disposed)return;disposed=true;roots.forEach(b=>b.removeFromParent());skeleton.dispose();}};
}

import {readFile,writeFile} from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import {createNativeCharacter,loadNativeCharacterData} from '../dist/native-character.js';
const runtimeRoot=new URL('../dist/',import.meta.url);
globalThis.fetch=async url=>{
  const target=new URL(url);
  if(target.protocol!=='file:'||!target.pathname.startsWith(runtimeRoot.pathname))throw new Error('Runtime dependency escaped dist: '+target.pathname);
  try{return new Response(await readFile(target));}catch{return new Response('',{status:404});}
};
const data=await loadNativeCharacterData(0),actor=createNativeCharacter(data,{loadTextures:false}),original=createNativeCharacter(data,{loadTextures:false});
await actor.setAppearance('yaemiko');
const skin=JSON.parse(await readFile(new URL('./assets/enhanced/yaemiko/mesh.json',runtimeRoot))),edges=[],seen=new Set(),rest=skin.positions;
for(const face of skin.faces)for(let i=0;i<3;i++){
  const a=Math.min(face.indices[i],face.indices[(i+1)%3]),b=Math.max(face.indices[i],face.indices[(i+1)%3]),key=a*skin.vertexCount+b;
  if(seen.has(key))continue;seen.add(key);
  edges.push({a,b,rest:Math.hypot(...[0,1,2].map(axis=>rest[a*3+axis]-rest[b*3+axis]))*.08});
}
const buffer=new Float32Array(rest.length),point=new THREE.Vector3(),reports=[];
actor.setSourceRestPose(true);actor.updateSecondaryMotion(1/60);
let sourceRestMaxError=0;const expected=new THREE.Vector3();
for(let i=0;i<skin.vertexCount;i++){
  point.fromBufferAttribute(actor.mesh.geometry.attributes.position,i);expected.copy(point).applyMatrix4(actor.mesh.matrixWorld);
  actor.mesh.applyBoneTransform(i,point);actor.mesh.localToWorld(point);sourceRestMaxError=Math.max(sourceRestMaxError,point.distanceTo(expected));
}
actor.setSourceRestPose(false);
for(const id of [6,16,90,117,144,151,152,200,202,248,262,263,264,279,295]){
  const pose=data.poses[id];
  for(const frame of [pose.start,(pose.start+pose.end)/2,pose.end]){
    actor.setPoseFrame(pose.source,frame);original.setPoseFrame(pose.source,frame);actor.resetSecondaryMotion();actor.updateSecondaryMotion(1/60,{groundY:-5});
    let finite=true;const bounds=new THREE.Box3();
    for(let i=0;i<skin.vertexCount;i++){
      point.fromBufferAttribute(actor.mesh.geometry.attributes.position,i);actor.mesh.applyBoneTransform(i,point);actor.mesh.localToWorld(point);
      point.toArray(buffer,i*3);bounds.expandByPoint(point);finite&&=point.toArray().every(Number.isFinite);
    }
    const worst=[];
    for(const edge of edges){
      const distance=Math.hypot(...[0,1,2].map(axis=>buffer[edge.a*3+axis]-buffer[edge.b*3+axis])),growth=distance-edge.rest;
      if(worst.length<5||growth>worst.at(-1).growth){worst.push({...edge,distance,growth});worst.sort((a,b)=>b.growth-a.growth);worst.length=Math.min(5,worst.length);}
    }
    const jointsMatch=[...actor.bones,...actor.dummies].every((bone,i)=>bone.matrixWorld.elements.every((v,j)=>v===[...original.bones,...original.dummies][i].matrixWorld.elements[j]));
    reports.push({pose:id,frame,finite,jointsMatch,bounds:{min:bounds.min.toArray(),max:bounds.max.toArray()},worstEdges:worst});
  }
}
actor.dispose();original.dispose();
await writeFile(new URL('../work/yaemiko-import-2026-11-10/motion-probe.json',import.meta.url),JSON.stringify(reports,null,2));
const worst=reports.flatMap(r=>r.worstEdges.map(e=>({...e,pose:r.pose,frame:r.frame}))).sort((a,b)=>b.growth-a.growth).slice(0,8);
const summary={vertices:skin.vertexCount,samples:reports.length,sourceRestMaxError,allFinite:reports.every(r=>r.finite),nativeJointsUnchanged:reports.every(r=>r.jointsMatch),worst};
await writeFile(new URL('../work/yaemiko-import-2026-11-10/motion-summary.json',import.meta.url),JSON.stringify(summary,null,2));
console.log(JSON.stringify(summary,null,2));

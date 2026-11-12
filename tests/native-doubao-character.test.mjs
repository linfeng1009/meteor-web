import test from 'node:test';
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {createHash} from 'node:crypto';
import * as THREE from '../dist/vendor/three.module.js';
import {createNativeCharacter,loadNativeCharacterData,loadEnhancedCharacterData,NATIVE_APPEARANCES} from '../dist/native-character.js';
import {appearanceCharacterName,WORKSHOP_APPEARANCES} from '../dist/character-appearances.js';
import {MeteorGame} from '../dist/engine.js';
import {sourcePmxVertices} from './helpers/source-pmx-vertices.mjs';

const root=new URL('../',import.meta.url),dist=new URL('dist/',root),assets=new URL('assets/enhanced/doubao/',dist);
const json=async path=>JSON.parse(await readFile(new URL(path,root)));
const sha=bytes=>createHash('sha256').update(bytes).digest('hex');
const fileFetch=async url=>{
  const target=new URL(url);
  assert.ok(target.protocol==='file:'&&target.pathname.startsWith(dist.pathname),'runtime must read only project dist assets');
  try{return new Response(await readFile(target));}catch{return new Response('',{status:404});}
};
const withFetch=async callback=>{const before=globalThis.fetch;globalThis.fetch=fileFetch;try{return await callback();}finally{globalThis.fetch=before;}};
const data=await withFetch(()=>loadNativeCharacterData(0));
const matrices=actor=>[...actor.bones,...actor.dummies].map(b=>b.matrixWorld.toArray());
const build=await json('work/doubao-import-2026-11-10/build-evidence.json');

test('Doubao source archive and build inputs remain in the project after Downloads is removed',async()=>{
  const inventory=await json('work/doubao-import-2026-11-10/source-copy.json');
  assert.equal(inventory.complete,true);assert.equal(inventory.archive,'assets/source/doubao');assert.equal(inventory.files.length,9);
  for(const file of inventory.files){const bytes=await readFile(new URL(inventory.archive+'/'+file.path,root));assert.equal(bytes.length,file.bytes);assert.equal(sha(bytes),file.sha256);}
  for(const script of ['scripts/blender/build_doubao.py','scripts/blender/proportional_authoring.py']){
    const text=await readFile(new URL(script,root),'utf8');
    assert.equal(/Path\(['"]\/Users\//.test(text),false);assert.equal(text.includes('/Downloads/'),false);
  }
  assert.equal(build.sourceDownloadsRequired,false);assert.ok(build.restMatrixError<1e-4);assert.ok(build.poseMatrixError<1e-3);
  assert.deepEqual(build.bakedActions.map(a=>a.pose),[6,144,151,262]);assert.ok(build.bakedActions.every(a=>a.frames>1));
});

test('Doubao retains the complete original surface and byte-identical 4K JPEG atlas',async()=>withFetch(async()=>{
  const asset=await loadEnhancedCharacterData(0,'doubao'),{skin,manifest}=asset;
  assert.equal(skin.vertexCount,107855);assert.equal(skin.triangleCount,180698);assert.equal(skin.materials.length,1);
  assert.equal(manifest.complete,true);assert.equal(manifest.completeness.faceGeometry,true);
  assert.deepEqual(manifest.stats.textureResolutions,[[4096,4096]]);
  const atlas=await readFile(new URL(skin.materials[0].texture,asset.path));
  assert.equal(atlas.subarray(0,3).toString('hex'),'ffd8ff');
  assert.equal(sha(atlas),'9352e39bc145ddd9227049d020b36c400d159746d9fdf0568f03abadc489baa6');
  assert.equal(sha(await readFile(new URL('assets/source/doubao/tex/Color.jpg',root))),sha(atlas));
  assert.equal(manifest.provenance.modelAuthor,'sdn1111');assert.equal(manifest.provenance.rigAuthor,'鹿铃');
  assert.ok(build.rigidHeadVertices.length>10000,'the actual supplied head/face surface is retained');
  assert.ok(build.hairVertices.length>100);assert.equal(skin.secondaryMotion.bones.length,9);
  const used=new Set();let valid=true;
  for(let i=0;i<skin.vertexCount;i++){
    valid&&=Math.abs(Math.hypot(...skin.normals.slice(i*3,i*3+3))-1)<2e-4;
    for(let j=0;j<4;j++)if(skin.skinWeights[i*4+j]>.001)used.add(skin.skinIndices[i*4+j]);
  }
  assert.equal(valid,true);assert.ok(used.size>=15);
  for(const relative of [manifest.mesh,...skin.materials.map(m=>m.texture)])assert.ok(new URL(relative,assets).pathname.startsWith(assets.pathname));
}));

test('Doubao appears in game/workshop and switching five surfaces preserves pose and live weapon',async()=>withFetch(async()=>{
  assert.equal(NATIVE_APPEARANCES.doubao.characterId,0);assert.equal(Object.isFrozen(NATIVE_APPEARANCES.doubao),true);
  assert.ok(WORKSHOP_APPEARANCES.includes('doubao'));assert.equal(appearanceCharacterName(0,'doubao'),'豆包');
  const actor=createNativeCharacter(data,{loadTextures:false});
  try{
    actor.group.position.set(2,3,-4);actor.group.rotation.y=.7;actor.setPoseFrame(0,data.poses[262].start+3.5);
    const attachment=actor.getAttachment('d_wpnR'),weapon=new THREE.Group();attachment.add(weapon);actor.group.updateMatrixWorld(true);
    const native=actor.skeleton,pose=matrices(actor),weaponTransform=weapon.matrixWorld.toArray(),frame=actor.frame,meshes=new Map();
    for(const appearance of ['original','hutao','raiden','emilia','doubao','original','doubao']){
      const status=await actor.setAppearance(appearance);assert.equal(status.available,true);assert.equal(status.appearance,appearance);
      if(meshes.has(appearance))assert.equal(actor.mesh===meshes.get(appearance),true);else meshes.set(appearance,actor.mesh);
      assert.equal(actor.skeleton===native,true);assert.equal(actor.skeleton.bones.length,30);
      assert.equal(actor.mesh.skeleton.bones.slice(0,30).every((b,i)=>b===actor.bones[i]),appearance!=='doubao');
      assert.deepEqual(matrices(actor),pose);assert.equal(actor.frame,frame);assert.deepEqual(weapon.matrixWorld.toArray(),weaponTransform);
      assert.equal(actor.getAttachment('d_wpnR')===attachment,true);assert.equal(actor.nativeSpace.children.filter(o=>o.isSkinnedMesh).length,1);
    }
    assert.equal(new Set(meshes.values()).size,5);
  }finally{actor.dispose();}
}));

test('Doubao native actions preserve the face and avoid the source skirt-stretching defect',async()=>withFetch(async()=>{
  const actor=createNativeCharacter(data,{loadTextures:false}),reference=createNativeCharacter(data,{loadTextures:false});
  try{
    await actor.setAppearance('doubao');const skin=actor.mesh.geometry;
    const seamEdges=[[55418,55423],[53883,55417],[55421,55423]].map(([a,b])=>({a,b,rest:new THREE.Vector3().fromBufferAttribute(skin.attributes.position,a).distanceTo(new THREE.Vector3().fromBufferAttribute(skin.attributes.position,b))*.08}));
    const point=new THREE.Vector3(),other=new THREE.Vector3(),headSamples=build.rigidHeadVertices.filter((_,i)=>i%701===0);
    for(const id of [6,16,90,117,144,151,152,200,202,248,262,263,264,279,295]){
      const pose=data.poses[id];
      for(const frame of [pose.start,(pose.start+pose.end)/2,pose.end]){
        actor.setPoseFrame(pose.source,frame);reference.setPoseFrame(pose.source,frame);actor.resetSecondaryMotion();actor.updateSecondaryMotion(1/60,{groundY:-5});
        assert.deepEqual(matrices(actor),matrices(reference));
        actor.mesh.computeBoundingBox();const box=actor.mesh.boundingBox.clone().applyMatrix4(actor.mesh.matrixWorld);
        assert.ok([...box.min.toArray(),...box.max.toArray()].every(Number.isFinite));assert.ok(box.getSize(point).length()<10);
        for(const edge of seamEdges){
          point.fromBufferAttribute(skin.attributes.position,edge.a);actor.mesh.applyBoneTransform(edge.a,point);actor.mesh.localToWorld(point);
          other.fromBufferAttribute(skin.attributes.position,edge.b);actor.mesh.applyBoneTransform(edge.b,other);actor.mesh.localToWorld(other);
          assert.ok(point.distanceTo(other)-edge.rest<.15,`pose ${id}: skirt ${edge.a}/${edge.b} must not regain the 0.64-unit stretch`);
        }
        const headMatrix=actor.mesh.skeleton.bones[13].matrixWorld.clone().multiply(actor.mesh.skeleton.boneInverses[13]);
        for(const index of headSamples){
          point.fromBufferAttribute(skin.attributes.position,index);other.copy(point).applyMatrix4(headMatrix);
          actor.mesh.applyBoneTransform(index,point);actor.mesh.localToWorld(point);
          assert.ok(point.distanceTo(other)<1e-5,'face remains rigidly coherent with native head');
        }
      }
    }
  }finally{actor.dispose();reference.dispose();}
}));

test('Doubao hair uses restrained springs and retains the disabled setting through appearance changes',async()=>withFetch(async()=>{
  const actor=createNativeCharacter(data,{loadTextures:false});
  try{
    await actor.setAppearance('doubao');assert.equal(actor.secondaryMotionStatus.bones,9);
    for(let frame=0;frame<180;frame++){
      const time=Math.min(frame,89)/60,pose=data.poses[144];actor.group.position.x=Math.sin(time*2)*.3;actor.group.rotation.y=Math.sin(time*3)*.6;
      actor.setPoseFrame(pose.source,pose.start+time*20%(pose.end-pose.start));actor.updateSecondaryMotion(1/60);
      for(const n of actor.getSecondaryMotionSnapshot()){
        assert.ok([...n.tail,...n.position].every(Number.isFinite));
        assert.ok(Math.abs(new THREE.Vector3().fromArray(n.tail).distanceTo(new THREE.Vector3().fromArray(n.position))-n.length)<1e-6);
      }
    }
    const motion=actor.getSecondaryMotionSnapshot().reduce((sum,n)=>sum+new THREE.Vector3().fromArray(n.tail).distanceToSquared(new THREE.Vector3().fromArray(n.previous)),0);
    assert.ok(motion<1e-7,'short hair settles instead of whipping after motion stops');
    actor.setSecondaryMotionEnabled(false);await actor.setAppearance('emilia');await actor.setAppearance('doubao');assert.equal(actor.secondaryMotionStatus.enabled,false);
    actor.setSecondaryMotionEnabled(true);assert.equal(actor.secondaryMotionStatus.enabled,true);
  }finally{actor.dispose();}
}));

test('Doubao keeps every original vertex, normal and UV under one uniform transform',async()=>withFetch(async()=>{
  const source=sourcePmxVertices(await readFile(new URL('assets/source/doubao/豆包模型.pmx',root))),{skin}=await loadEnhancedCharacterData(0,'doubao');
  let floor=Infinity,top=-Infinity;for(const v of source){floor=Math.min(floor,v.position[1]);top=Math.max(top,v.position[1]);}const scale=39.4/(top-floor);
  assert.equal(source.length,skin.vertexCount);assert.equal(skin.bodyRig.type,'source-proportions');assert.equal(build.proportionalDisplayRig,true);assert.equal(build.sourceGeometryMaxError,0);
  for(let i=0;i<source.length;i++){
    const {position:[x,y,z],normal:[nx,ny,nz],uv}=source[i],expected=[x*scale,z*scale,(y-floor)*scale],normal=[nx,nz,ny],length=Math.hypot(...normal);
    for(let axis=0;axis<3;axis++){assert.ok(Math.abs(skin.positions[i*3+axis]-expected[axis])<1e-5,'body must keep the source proportions');assert.ok(Math.abs(skin.normals[i*3+axis]-normal[axis]/length)<1e-5);}
    assert.ok(Math.abs(skin.uvs[i*2]-uv[0])<1e-7&&Math.abs(skin.uvs[i*2+1]-(1-uv[1]))<1e-7);
  }
}));

test('Doubao source-pose inspection reproduces the original shape and animation retains original joint lengths',async()=>withFetch(async()=>{
  const actor=createNativeCharacter(data,{loadTextures:false}),p=new THREE.Vector3(),expected=new THREE.Vector3();
  try{
    await actor.setAppearance('doubao');actor.group.position.set(3,1,-2);actor.group.rotation.y=.5;actor.setPoseFrame(0,data.poses[262].end);const native=matrices(actor);
    assert.equal(actor.setSourceRestPose(true),true);actor.updateSecondaryMotion(1/60);assert.equal(actor.secondaryMotionStatus.enabled,false);
    for(let i=0;i<actor.mesh.geometry.attributes.position.count;i++){
      p.fromBufferAttribute(actor.mesh.geometry.attributes.position,i);expected.copy(p).applyMatrix4(actor.mesh.matrixWorld);actor.mesh.applyBoneTransform(i,p);actor.mesh.localToWorld(p);assert.ok(p.distanceTo(expected)<1e-6);
    }
    assert.deepEqual(matrices(actor),native);
    await actor.setAppearance('springfield');await actor.setAppearance('doubao');assert.equal(actor.sourceRestPose,true);assert.equal(actor.secondaryMotionStatus.enabled,false);
    actor.setSourceRestPose(false);assert.equal(actor.secondaryMotionStatus.enabled,true);
    const bones=actor.mesh.skeleton.bones.slice(0,30),lengths=bones.map(b=>b.position.length());
    for(const id of [6,144,151,262])for(const frame of [data.poses[id].start,data.poses[id].end]){
      actor.setPoseFrame(data.poses[id].source,frame);for(let i=1;i<30;i++)assert.ok(Math.abs(bones[i].position.length()-lengths[i])<1e-6);
    }
    const weapon=new THREE.Group(),palm=actor.getAttachment('d_wpnRP');palm.add(weapon);actor.registerVisualAttachment(weapon,'d_wpnRP');
    for(const id of [6,144,151,262]){
      actor.setPoseFrame(data.poses[id].source,data.poses[id].start);actor.updateSecondaryMotion(1/60);
      assert.ok(weapon.getWorldPosition(p).distanceTo(bones[25].getWorldPosition(expected))<.2,'visible grip must follow the source right hand');
    }
    await actor.setAppearance('original');assert.equal(weapon.parent,palm);assert.equal(actor.sourceRestAvailable,false);
  }finally{actor.dispose();}
}));

test('Doubao game adoption keeps mission identity, air motion, health and current command',async()=>withFetch(async()=>{
  const character=createNativeCharacter(data,{loadTextures:false}),game=Object.create(MeteorGame.prototype),events=[];
  const command={id:'sword-air-down'},timeline={pose:{id:151},time:.31},combat={timeline,combo:2,currentMove:command},mission={id:'sn01',stage:'fighting'};
  const actor={id:1,scriptId:0,name:'孟星魂',character,root:character.group,hp:721,maxHp:1500,rage:33,weaponId:5,weapon:'dagger',vy:3.2,grounded:false,team:1,combat};
  Object.assign(game,{ready:Promise.resolve(),hero:actor,characterId:0,appearanceRequest:0,missionState:mission,_hud(){},onEvent:event=>events.push(event)});
  character.setPoseFrame(0,data.poses[151].start+3);character.group.position.set(1,4,6);character.group.updateMatrixWorld(true);
  const pose=matrices(character),position=character.group.position.toArray(),frame=character.frame;
  try{
    const result=await game.setCharacterAppearance('doubao');assert.equal(result.available,true);assert.equal(result.previewOnly,false);assert.equal(game.characterAppearance,'doubao');
    assert.equal(game.hero===actor,true);assert.equal(game.missionState===mission,true);assert.equal(actor.name,'孟星魂');assert.equal(actor.scriptId,0);
    assert.equal(actor.hp,721);assert.equal(actor.rage,33);assert.equal(actor.weaponId,5);assert.equal(actor.vy,3.2);assert.equal(actor.grounded,false);
    assert.equal(combat.currentMove===command,true);assert.equal(combat.timeline===timeline,true);assert.equal(timeline.time,.31);
    assert.deepEqual(matrices(character),pose);assert.deepEqual(character.group.position.toArray(),position);assert.equal(character.frame,frame);assert.equal(events.at(-1).appearance,'doubao');
  }finally{character.dispose();}
}));

test('a missing Doubao bundle preserves the live model and rejects incompatible native characters',async()=>{
  const module=await import('../dist/native-character.js?doubao-missing'),before=globalThis.fetch;
  globalThis.fetch=async url=>new URL(url).pathname.includes('/enhanced/doubao/')?new Response('',{status:404}):fileFetch(url);
  const actor=module.createNativeCharacter(data,{loadTextures:false});
  try{
    await actor.setAppearance('emilia');const mesh=actor.mesh,status=await actor.setAppearance('doubao');
    assert.equal(status.available,false);assert.equal(actor.mesh===mesh,true);assert.equal(status.appearance,'emilia');assert.match(status.reason,/404/);
    const other=module.createNativeCharacter(await module.loadNativeCharacterData(1),{loadTextures:false});
    try{const result=await other.setAppearance('doubao');assert.equal(result.available,false);assert.equal(other.appearance,'original');}finally{other.dispose();}
  }finally{actor.dispose();globalThis.fetch=before;}
});

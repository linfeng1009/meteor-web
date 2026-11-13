import test from 'node:test';
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {createHash} from 'node:crypto';
import * as THREE from '../dist/vendor/three.module.js';
import {createNativeCharacter,loadNativeCharacterData,loadEnhancedCharacterData,NATIVE_APPEARANCES} from '../dist/native-character.js';
import {appearanceCharacterName,WORKSHOP_APPEARANCES} from '../dist/character-appearances.js';
import {MeteorGame} from '../dist/engine.js';
import {bindQiankunGrip} from '../dist/native-qiankun-grip.js';
import {sourcePmxVertices} from './helpers/source-pmx-vertices.mjs';
// Runtime textures may be PNG or WebP (the deployment converts atlases to WebP
// to fit a 3 Mbit uplink), so the check is "a real image with a known magic".
const imageSize = bytes => {
  if (bytes.subarray(0,8).toString('hex')==='89504e470d0a1a0a') return [bytes.readUInt32BE(16),bytes.readUInt32BE(20)];
  const fourcc = bytes.subarray(12,16).toString('ascii');
  if (fourcc==='VP8X') return [1+bytes.readUIntLE(24,3),1+bytes.readUIntLE(27,3)];
  if (fourcc==='VP8 ') return [bytes.readUInt16LE(26)&0x3fff,bytes.readUInt16LE(28)&0x3fff];
  if (fourcc==='VP8L') { const bits=bytes.readUInt32LE(21); return [1+(bits&0x3fff),1+((bits>>14)&0x3fff)]; }
  return [0,0];
};

const imageMagic = bytes => {
  const head = bytes.subarray(0, 12);
  if (head.subarray(0, 8).toString('hex') === '89504e470d0a1a0a') return 'png';
  if (head.subarray(0, 4).toString('ascii') === 'RIFF' && head.subarray(8, 12).toString('ascii') === 'WEBP') return 'webp';
  return 'unknown';
};

const root=new URL('../',import.meta.url),dist=new URL('dist/',root);
const json=async path=>JSON.parse(await readFile(new URL(path,root)));
const sha=bytes=>createHash('sha256').update(bytes).digest('hex');
const fileFetch=async url=>{
  const target=new URL(url);assert.ok(target.protocol==='file:'&&target.pathname.startsWith(dist.pathname),'runtime loads project dist only');
  try{return new Response(await readFile(target));}catch{return new Response('',{status:404});}
};
const withFetch=async callback=>{const before=globalThis.fetch;globalThis.fetch=fileFetch;try{return await callback();}finally{globalThis.fetch=before;}};
const data=await withFetch(()=>loadNativeCharacterData(0));
const matrices=actor=>[...actor.bones,...actor.dummies].map(b=>b.matrixWorld.toArray());
const build=await json('work/springfield-import-2026-11-10/build-evidence.json');

test('Springfield archive and editable actions do not depend on the original download directory',async()=>{
  const inventory=await json('work/springfield-import-2026-11-10/source-copy.json');
  assert.equal(inventory.complete,true);assert.equal(inventory.archive,'assets/source/springfield');assert.equal(inventory.files.length,43);
  for(const file of inventory.files){const bytes=await readFile(new URL(inventory.archive+'/'+file.path,root));assert.equal(bytes.length,file.bytes);assert.equal(sha(bytes),file.sha256);}
  const script=await readFile(new URL('scripts/blender/build_springfield.py',root),'utf8');assert.equal(script.includes('/Downloads/'),false);assert.equal(/Path\(['"]\/Users\//.test(script),false);
  assert.equal(build.sourceDownloadsRequired,false);assert.ok(build.restMatrixError<1e-4);assert.ok(build.poseMatrixError<1e-3);
  assert.deepEqual(build.bakedActions.map(a=>a.pose),[6,144,151,262]);assert.equal(build.packedImages.length,33);assert.ok(build.packedImages.every(i=>i.packed));
});

test('Springfield keeps the complete default P3 surfaces, original textures, normals and author credits',async()=>withFetch(async()=>{
  const {skin,manifest,path}=await loadEnhancedCharacterData(0,'springfield');
  assert.equal(skin.vertexCount,61222);assert.equal(skin.triangleCount,81307);assert.equal(manifest.stats.sourceTriangles,87259);assert.equal(manifest.stats.omittedTriangles,5952);
  assert.equal(manifest.complete,true);assert.equal(manifest.completeness.faceGeometry,true);assert.equal(skin.materials.length,36);
  const expected={Face:2566,Mouth:172,Teeth:40,'Teeth.001':40,Tongue:160,EyeWhite:132,Brows:104,Lashers:380,Eyes:144,'Eyes+':144,HairA:4969,HairB:6951,'P3-Cloth1':7838,'P3-Body1':6560,'P3-Body1-TransparentSkirt':2898};
  for(const [name,count]of Object.entries(expected)){
    const material=skin.materials.findIndex(m=>m.name===name);assert.ok(material>=0);assert.equal(skin.faces.filter(f=>f.material===material).length,count,name);
  }
  assert.deepEqual(manifest.omittedRenderPasses.map(p=>p.material),['BodySkin(NoShoes/Hide)','ToeNails(NoShoes/Hide)','EyeShadow']);
  assert.equal(manifest.provenance.modelAuthor,'Sunborn Network Technology');assert.match(manifest.provenance.rigAuthor,/DesmondChan/);
  const sources=manifest.sourceFiles.filter(s=>s.runtime);assert.equal(sources.length,33);
  for(const source of sources){
    const target=new URL(source.runtime,path);assert.ok(target.pathname.startsWith(path.pathname));const bytes=await readFile(target);
    assert.equal(sha(bytes),source.runtimeSha256??source.sha256);assert.notEqual(imageMagic(bytes),'unknown');
    assert.deepEqual(imageSize(bytes),source.size,'runtime texture keeps its pixel size');
    assert.equal(sha(await readFile(new URL('assets/source/springfield/'+source.file,root))),source.sha256);
  }
  assert.ok(skin.materials.some(m=>m.normal));
  for(const name of ['P3-Cloth1-Transparent','P3-Body1-TransparentSkirt','P3-Body4-Transparent','Eyes+']){
    const material=skin.materials.find(m=>m.name===name);assert.equal(material.transparent,true);assert.equal(material.depthWrite,false);
  }
}));

test('Springfield face stays rigid while authored hair retains separate head-rooted chains',async()=>withFetch(async()=>{
  const {skin}=await loadEnhancedCharacterData(0,'springfield'),rig=skin.secondaryMotion;
  assert.equal(rig.bones.length,71);const headBones=new Set([13]);
  for(const [i,b]of rig.bones.entries()){assert.ok(headBones.has(b.parent));headBones.add(30+i);assert.ok(b.follow>=.98&&b.globalMaxAngle<=.04);}
  const faceNames=new Set(['Face','Mouth','Teeth','Teeth.001','Tongue','EyeWhite','Brows','Lashers','Eyes','Eyes+']);
  const faceMaterials=new Set(skin.materials.flatMap((m,i)=>faceNames.has(m.name)?[i]:[]));
  const faceVertices=new Set(skin.faces.filter(f=>faceMaterials.has(f.material)).flatMap(f=>f.indices));
  let valid=true;
  for(const v of faceVertices){let head=0;for(let j=0;j<4;j++)if(skin.skinIndices[v*4+j]===13)head+=skin.skinWeights[v*4+j];valid&&=head>.99999;}
  assert.equal(valid,true,'eyes and face must not inherit independent hair motion');assert.ok(build.hairVertices.length>5000);
  const hairMaterials=new Set(rig.hairMaterials),hairVertices=new Set(skin.faces.filter(f=>hairMaterials.has(f.material)).flatMap(f=>f.indices));
  for(const v of hairVertices)for(let j=0;j<4;j++)if(skin.skinWeights[v*4+j]>.00001)assert.ok(headBones.has(skin.skinIndices[v*4+j]),'long hair cannot stretch between torso and head');
}));

test('six appearance variants retain native joints, cached meshes and weapon anchors',async()=>withFetch(async()=>{
  assert.ok(WORKSHOP_APPEARANCES.includes('springfield'));assert.equal(appearanceCharacterName(0,'springfield'),'春田');assert.equal(NATIVE_APPEARANCES.springfield.characterId,0);
  const actor=createNativeCharacter(data,{loadTextures:false});
  try{
    actor.group.position.set(2,3,-4);actor.group.rotation.y=.7;actor.setPoseFrame(0,data.poses[262].start+3.5);
    const attachment=actor.getAttachment('d_wpnR'),weapon=new THREE.Group();attachment.add(weapon);actor.group.updateMatrixWorld(true);
    const skeleton=actor.skeleton,joints=matrices(actor),weaponTransform=weapon.matrixWorld.toArray(),frame=actor.frame,meshes=new Map();
    for(const appearance of ['original','hutao','raiden','emilia','doubao','springfield','original','springfield']){
      const status=await actor.setAppearance(appearance);assert.equal(status.available,true);assert.equal(status.complete,true);
      if(meshes.has(appearance))assert.equal(actor.mesh===meshes.get(appearance),true);else meshes.set(appearance,actor.mesh);
      assert.equal(actor.skeleton===skeleton,true);assert.equal(actor.skeleton.bones.length,30);assert.equal(actor.mesh.skeleton.bones.slice(0,30).every((b,i)=>b===actor.bones[i]),!['springfield','doubao'].includes(appearance));
      assert.deepEqual(matrices(actor),joints);assert.equal(actor.frame,frame);assert.deepEqual(weapon.matrixWorld.toArray(),weaponTransform);assert.equal(weapon.parent===attachment,true);
      assert.equal(actor.nativeSpace.children.filter(c=>c.isSkinnedMesh).length,1);
    }
    assert.equal(new Set(meshes.values()).size,6);
  }finally{actor.dispose();}
}));

test('Springfield run, jump, guard and attack samples preserve native transforms, face and skirt seams',async()=>withFetch(async()=>{
  const actor=createNativeCharacter(data,{loadTextures:false}),reference=createNativeCharacter(data,{loadTextures:false});
  try{
    await actor.setAppearance('springfield');const geometry=actor.mesh.geometry,point=new THREE.Vector3(),other=new THREE.Vector3();
    const seams=[[58945,58948],[58926,58944],[58889,58923]].map(([a,b])=>({a,b,rest:new THREE.Vector3().fromBufferAttribute(geometry.attributes.position,a).distanceTo(new THREE.Vector3().fromBufferAttribute(geometry.attributes.position,b))*.08}));
    const faceSamples=build.rigidHeadVertices.filter((_,i)=>i%231===0);
    for(const id of [6,16,90,117,144,151,152,200,202,248,262,263,264,279,295]){
      const pose=data.poses[id];
      for(const frame of [pose.start,(pose.start+pose.end)/2,pose.end]){
        actor.setPoseFrame(pose.source,frame);reference.setPoseFrame(pose.source,frame);actor.resetSecondaryMotion();actor.updateSecondaryMotion(1/60,{groundY:-5});assert.deepEqual(matrices(actor),matrices(reference));
        actor.mesh.computeBoundingBox();const box=actor.mesh.boundingBox.clone().applyMatrix4(actor.mesh.matrixWorld);
        assert.ok([...box.min.toArray(),...box.max.toArray()].every(Number.isFinite));assert.ok(box.getSize(point).length()<10);
        for(const edge of seams){
          point.fromBufferAttribute(geometry.attributes.position,edge.a);actor.mesh.applyBoneTransform(edge.a,point);actor.mesh.localToWorld(point);
          other.fromBufferAttribute(geometry.attributes.position,edge.b);actor.mesh.applyBoneTransform(edge.b,other);actor.mesh.localToWorld(other);
          assert.ok(point.distanceTo(other)-edge.rest<.1,`pose ${id}: skirt ${edge.a}/${edge.b} must stay attached to the pelvis`);
        }
        const head=actor.mesh.skeleton.bones[13].matrixWorld.clone().multiply(actor.mesh.skeleton.boneInverses[13]);
        for(const i of faceSamples){point.fromBufferAttribute(geometry.attributes.position,i);other.copy(point).applyMatrix4(head);actor.mesh.applyBoneTransform(i,point);actor.mesh.localToWorld(point);assert.ok(point.distanceTo(other)<1e-5);}
      }
    }
  }finally{actor.dispose();reference.dispose();}
}));

// Parse the original PMX vertex prefix independently of the Blender exporter.
// Comparing every vertex catches the torso/leg compression reported by users.

test('Springfield preserves every source vertex uniformly and can display the untouched source pose',async()=>withFetch(async()=>{
  const {skin}=await loadEnhancedCharacterData(0,'springfield'),source=sourcePmxVertices(await readFile(new URL('assets/source/springfield/春田_泳衣_全P3_刘海物理优化.pmx',root)));
  const floor=Math.min(...source.map(v=>v.position[1])),top=Math.max(...source.map(v=>v.position[1])),scale=39.4/(top-floor);
  assert.equal(source.length,skin.vertexCount);assert.ok(build.proportionalDisplayRig);assert.equal(build.sourceGeometryMaxError,0);
  for(let i=0;i<source.length;i++){
    const {position:[x,y,z],normal,uv}=source[i],expected=[x*scale,z*scale,(y-floor)*scale],length=Math.hypot(...normal);
    for(let axis=0;axis<3;axis++){assert.ok(Math.abs(skin.positions[i*3+axis]-expected[axis])<1e-5);assert.ok(Math.abs(skin.normals[i*3+axis]-[normal[0],normal[2],normal[1]][axis]/length)<1e-5);}
    assert.ok(Math.abs(skin.uvs[i*2]-uv[0])<1e-7&&Math.abs(skin.uvs[i*2+1]-(1-uv[1]))<1e-7);
  }
  const actor=createNativeCharacter(data,{loadTextures:false}),point=new THREE.Vector3(),expected=new THREE.Vector3();
  try{
    await actor.setAppearance('springfield');actor.group.position.set(3,1,-2);actor.group.rotation.y=.5;actor.setPoseFrame(0,data.poses[262].end);const native=matrices(actor);
    assert.equal(actor.setSourceRestPose(true),true);actor.updateSecondaryMotion(1/60);assert.equal(actor.secondaryMotionStatus.enabled,false);
    for(let i=0;i<skin.vertexCount;i++){
      point.fromBufferAttribute(actor.mesh.geometry.attributes.position,i);expected.copy(point).applyMatrix4(actor.mesh.matrixWorld);actor.mesh.applyBoneTransform(i,point);actor.mesh.localToWorld(point);assert.ok(point.distanceTo(expected)<1e-6,'original-pose inspection must reproduce the source surface');
    }
    assert.deepEqual(matrices(actor),native);
    await actor.setAppearance('original');await actor.setAppearance('springfield');assert.equal(actor.sourceRestPose,true);assert.equal(actor.secondaryMotionStatus.enabled,false);
    actor.setSourceRestPose(false);assert.equal(actor.secondaryMotionStatus.enabled,true);
    const bones=actor.mesh.skeleton.bones.slice(0,30),lengths=bones.map(b=>b.position.length());
    for(const id of [6,144,151,262])for(const frame of [data.poses[id].start,data.poses[id].end]){
      actor.setPoseFrame(data.poses[id].source,frame);for(let i=1;i<30;i++)assert.ok(Math.abs(bones[i].position.length()-lengths[i])<1e-6,'animation must retain original limb lengths');
    }
  }finally{actor.dispose();}
}));

test('Springfield skin uses source roughness and correctly unpacks Unity normal-map channels',async()=>withFetch(async()=>{
  const actor=createNativeCharacter(data,{loadTextures:false});
  try{
    await actor.setAppearance('springfield');const materials=actor.mesh.material,skin=materials.find(m=>m.name==='BodySkin');assert.ok(skin?.isMeshPhysicalMaterial);assert.equal(skin.roughness,1);
    const shader={fragmentShader:'#include <normal_fragment_maps>\n#include <roughnessmap_fragment>'};skin.onBeforeCompile(shader);
    assert.match(shader.fragmentShader,/sourcePackedNormal\.r \* sourcePackedNormal\.a/);assert.match(shader.fragmentShader,/sourcePackedNormal\.g/);assert.match(shader.fragmentShader,/sqrt\( max\( 1.0 - dot\( sourceNormalXY, sourceNormalXY \)/);assert.match(shader.fragmentShader,/texelRoughness\.r/);assert.equal(shader.fragmentShader.includes('texelRoughness.g'),false);
    const {skin:spec}=await loadEnhancedCharacterData(0,'springfield');for(const material of spec.materials.filter(m=>m.normal)){assert.equal(material.normalEncoding,'unity-rg-or-ag');assert.equal(material.roughnessChannel,'r');assert.ok(material.roughnessMap);}
  }finally{actor.dispose();}
}));

test('Springfield visible weapons follow source hands while native anchors and qiankun seating stay intact',async()=>withFetch(async()=>{
  const actor=createNativeCharacter(data,{loadTextures:false}),reference=createNativeCharacter(data,{loadTextures:false});
  const blade=new THREE.Group(),sheath=new THREE.Group(),undo=new THREE.Matrix4().makeRotationX(Math.PI/2);blade.name='w9_0R';sheath.name='w9_0L';
  blade.rotation.x=sheath.rotation.x=Math.PI/2;actor.getAttachment('d_wpnRP').add(blade);actor.getAttachment('d_wpnLP').add(sheath);actor.registerVisualAttachment(blade,'d_wpnRP');actor.registerVisualAttachment(sheath,'d_wpnLP');
  const hero={character:actor,weaponModels:[blade,sheath],combat:{weaponMode:'blade'}},manifest=await json('dist/assets/original/rage-vfx/manifest.json');
  const unsubscribe=bindQiankunGrip(hero,{poses:data.combatPoses},manifest);
  try{
    await actor.setAppearance('springfield');
    for(const id of [401,431,403,449,402]){
      const pose=data.combatPoses.get(id);hero.combat.currentMove={poseId:id};hero.combat.weaponMode=id===403?'sheath':'blade';
      for(const frame of [pose.start,(pose.start+pose.end)/2,pose.end]){
        actor.setPoseFrame(pose.source,frame);reference.setPoseFrame(pose.source,frame);actor.updateSecondaryMotion(1/60);assert.deepEqual(matrices(actor),matrices(reference));
        const left=actor.getVisualAttachmentMatrix('d_wpnLP');assert.ok(sheath.matrixWorld.elements.every((v,i)=>Math.abs(v-left.clone().multiply(undo).elements[i])<1e-6));
        if(hero.qiankunSheathWeight<1e-6){const right=actor.getVisualAttachmentMatrix('d_wpnRP').multiply(undo);assert.ok(blade.matrixWorld.elements.every((v,i)=>Math.abs(v-right.elements[i])<1e-5),'drawn blade follows the source right palm');}
        if(hero.qiankunSheathWeight>1-1e-6){
          const a=new THREE.Vector3().fromArray(manifest.weaponAttachments.w9_0r.d_wpnre.position).applyMatrix4(undo.clone().invert()).applyMatrix4(blade.matrixWorld),b=new THREE.Vector3().fromArray(manifest.weaponAttachments.w9_0l.d_wpnls.position).applyMatrix4(undo.clone().invert()).applyMatrix4(sheath.matrixWorld);assert.ok(a.distanceTo(b)<1e-5,'blade remains seated inside the source-hand sheath');
        }
      }
    }
    await actor.setAppearance('original');actor.setPoseFrame(0,data.poses[401].start);assert.equal(blade.parent,actor.getAttachment('d_wpnLP'));assert.equal(sheath.parent,actor.getAttachment('d_wpnLP'));
  }finally{unsubscribe();actor.dispose();reference.dispose();}
}));

test('Springfield long hair settles, obeys segment limits and retains a disabled setting after switches',async()=>withFetch(async()=>{
  const actor=createNativeCharacter(data,{loadTextures:false});
  try{
    await actor.setAppearance('springfield');assert.equal(actor.secondaryMotionStatus.bones,71);
    for(let frame=0;frame<240;frame++){
      const t=Math.min(frame,89)/60,pose=data.poses[144];actor.group.position.x=Math.sin(t*2)*.3;actor.group.rotation.y=Math.sin(t*3)*.6;
      actor.setPoseFrame(pose.source,pose.start+t*20%(pose.end-pose.start));actor.updateSecondaryMotion(1/60);
      for(const n of actor.getSecondaryMotionSnapshot()){assert.ok([...n.tail,...n.position].every(Number.isFinite));assert.ok(Math.abs(new THREE.Vector3().fromArray(n.tail).distanceTo(new THREE.Vector3().fromArray(n.position))-n.length)<1e-6);}
    }
    const motion=actor.getSecondaryMotionSnapshot().reduce((sum,n)=>sum+new THREE.Vector3().fromArray(n.tail).distanceToSquared(new THREE.Vector3().fromArray(n.previous)),0);assert.ok(motion<1e-7);
    actor.setSecondaryMotionEnabled(false);await actor.setAppearance('doubao');await actor.setAppearance('springfield');assert.equal(actor.secondaryMotionStatus.enabled,false);actor.setSecondaryMotionEnabled(true);assert.equal(actor.secondaryMotionStatus.enabled,true);
  }finally{actor.dispose();}
}));

test('Springfield game adoption preserves mission identity, air motion, HP and command timeline',async()=>withFetch(async()=>{
  const character=createNativeCharacter(data,{loadTextures:false}),game=Object.create(MeteorGame.prototype),events=[];
  const command={id:'sword-air-down'},timeline={pose:{id:151},time:.31},combat={timeline,combo:2,currentMove:command},mission={id:'sn01',stage:'fighting'};
  const actor={id:1,scriptId:0,name:'孟星魂',character,root:character.group,hp:721,maxHp:1500,rage:33,weaponId:5,weapon:'dagger',vy:3.2,grounded:false,team:1,combat};
  Object.assign(game,{ready:Promise.resolve(),hero:actor,characterId:0,appearanceRequest:0,missionState:mission,_hud(){},onEvent:e=>events.push(e)});
  character.setPoseFrame(0,data.poses[151].start+3);character.group.position.set(1,4,6);character.group.updateMatrixWorld(true);const joints=matrices(character),position=character.group.position.toArray(),frame=character.frame;
  try{
    const result=await game.setCharacterAppearance('springfield');assert.equal(result.available,true);assert.equal(game.characterAppearance,'springfield');assert.equal(game.hero===actor,true);assert.equal(game.missionState===mission,true);
    assert.equal(actor.name,'孟星魂');assert.equal(actor.scriptId,0);assert.equal(actor.hp,721);assert.equal(actor.rage,33);assert.equal(actor.weaponId,5);assert.equal(actor.vy,3.2);assert.equal(actor.grounded,false);
    assert.equal(combat.currentMove===command,true);assert.equal(combat.timeline===timeline,true);assert.equal(timeline.time,.31);assert.deepEqual(matrices(character),joints);assert.deepEqual(character.group.position.toArray(),position);assert.equal(character.frame,frame);assert.equal(events.at(-1).appearance,'springfield');
  }finally{character.dispose();}
}));

test('missing Springfield assets retain the previous appearance and incompatible bodies remain original',async()=>{
  const module=await import('../dist/native-character.js?springfield-missing'),before=globalThis.fetch;globalThis.fetch=async url=>new URL(url).pathname.includes('/enhanced/springfield/')?new Response('',{status:404}):fileFetch(url);
  const actor=module.createNativeCharacter(data,{loadTextures:false});
  try{
    await actor.setAppearance('doubao');const mesh=actor.mesh,status=await actor.setAppearance('springfield');assert.equal(status.available,false);assert.equal(status.appearance,'doubao');assert.equal(actor.mesh===mesh,true);assert.match(status.reason,/404/);
    const other=module.createNativeCharacter(await module.loadNativeCharacterData(1),{loadTextures:false});try{const result=await other.setAppearance('springfield');assert.equal(result.available,false);assert.equal(other.appearance,'original');}finally{other.dispose();}
  }finally{actor.dispose();globalThis.fetch=before;}
});

import test from 'node:test';
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {createHash} from 'node:crypto';
import * as THREE from '../dist/vendor/three.module.js';
import {createNativeCharacter,loadNativeCharacterData,loadEnhancedCharacterData,NATIVE_APPEARANCES} from '../dist/native-character.js';
import {appearanceCharacterName,WORKSHOP_APPEARANCES} from '../dist/character-appearances.js';
import {MeteorGame} from '../dist/engine.js';
import {sourcePmxVertices} from './helpers/source-pmx-vertices.mjs';

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


const root=new URL('../',import.meta.url),dist=new URL('dist/',root);
const json=async path=>JSON.parse(await readFile(new URL(path,root)));
const sha=bytes=>createHash('sha256').update(bytes).digest('hex');
const fileFetch=async url=>{
  const path=new URL(url);assert.ok(path.protocol==='file:'&&path.pathname.startsWith(dist.pathname),'runtime reads project dist only');
  try{return new Response(await readFile(path));}catch{return new Response('',{status:404});}
};
const withFetch=async fn=>{const before=globalThis.fetch;globalThis.fetch=fileFetch;try{return await fn();}finally{globalThis.fetch=before;}};
const data=await withFetch(()=>loadNativeCharacterData(0));
const matrices=actor=>[...actor.bones,...actor.dummies].map(b=>b.matrixWorld.toArray());
const build=await json('work/yaemiko-import-2026-11-10/build-evidence.json');
const headNames=new Set(['颜','颜2','睫','二重','眉','目','星目','口舌','齿','白目','头饰','耳饰+神之眼AL']);

test('Yae Miko archive, editable actions and rebuild inputs are independent of Downloads',async()=>{
  const inventory=await json('work/yaemiko-import-2026-11-10/source-copy.json');assert.equal(inventory.complete,true);assert.equal(inventory.archive,'assets/source/yaemiko');assert.equal(inventory.files.length,12);
  for(const item of inventory.files){const bytes=await readFile(new URL(inventory.archive+'/'+item.path,root));assert.equal(bytes.length,item.bytes);assert.equal(sha(bytes),item.runtimeSha256??item.sha256);}
  const script=await readFile(new URL('scripts/blender/build_yaemiko.py',root),'utf8');assert.equal(script.includes('/Downloads/'),false);assert.equal(/Path\(['"]\/Users\//.test(script),false);
  assert.equal(build.sourceDownloadsRequired,false);assert.equal(build.proportionalDisplayRig,true);assert.equal(build.sourceGeometryMaxError,0);assert.ok(build.restMatrixError<1e-4&&build.poseMatrixError<1e-3);
  assert.deepEqual(build.bakedActions.map(a=>a.pose),[6,144,151,262]);assert.equal(build.packedImages.length,5);assert.ok(build.packedImages.every(i=>i.packed));
});

test('Yae Miko keeps all original surfaces, 2K textures, transparent hair highlights and author credits',async()=>withFetch(async()=>{
  const {skin,manifest,path}=await loadEnhancedCharacterData(0,'yaemiko');
  assert.equal(skin.vertexCount,25219);assert.equal(skin.triangleCount,29140);assert.equal(skin.materials.length,25);assert.equal(manifest.stats.omittedTriangles,0);assert.equal(manifest.stats.sourceBones,456);
  assert.equal(manifest.complete,true);assert.equal(manifest.completeness.faceGeometry,true);assert.equal(manifest.provenance.modelAuthor,'miHoYo');assert.match(manifest.provenance.rigAuthor,/观海/);
  const sources=manifest.sourceFiles.filter(s=>s.runtime);assert.equal(sources.length,5);
  for(const item of sources){const bytes=await readFile(new URL(item.runtime,path));assert.equal(sha(bytes),item.runtimeSha256??item.sha256);assert.notEqual(imageMagic(bytes),'unknown');assert.deepEqual(imageSize(bytes),[2048,2048]);assert.equal(sha(await readFile(new URL('assets/source/yaemiko/'+item.file,root))),item.sha256);}
  for(const name of ['髪+','前髪+']){const m=skin.materials.find(m=>m.name===name);assert.equal(m.transparent,true);assert.equal(m.depthWrite,false);assert.match(m.texture,/spa_h\.(png|webp)$/);}
  assert.ok(skin.materials.find(m=>m.name==='肌').skinSurface);assert.ok(skin.materials.find(m=>m.name==='肌').alphaTest>0);
}));

test('Yae Miko preserves every source vertex, normal and UV under one uniform transform',async()=>withFetch(async()=>{
  const {skin}=await loadEnhancedCharacterData(0,'yaemiko'),source=sourcePmxVertices(await readFile(new URL('assets/source/yaemiko/八重神子.pmx',root)));
  let floor=Infinity,top=-Infinity;for(const v of source){floor=Math.min(floor,v.position[1]);top=Math.max(top,v.position[1]);}const scale=39.4/(top-floor);
  assert.equal(source.length,skin.vertexCount);assert.equal(skin.bodyRig.type,'source-proportions');
  for(let i=0;i<source.length;i++){
    const {position:[x,y,z],normal:[nx,ny,nz],uv}=source[i],expected=[x*scale,z*scale,(y-floor)*scale],normal=[nx,nz,ny],length=Math.hypot(...normal);
    for(let a=0;a<3;a++){assert.ok(Math.abs(skin.positions[i*3+a]-expected[a])<1e-5);assert.ok(Math.abs(skin.normals[i*3+a]-normal[a]/length)<1e-5);}
    assert.ok(Math.abs(skin.uvs[i*2]-uv[0])<1e-7&&Math.abs(skin.uvs[i*2+1]-(1-uv[1]))<1e-7);
  }
}));

test('Yae Miko source-pose inspection and cached appearance changes retain source shape and native gameplay anchors',async()=>withFetch(async()=>{
  assert.ok(WORKSHOP_APPEARANCES.includes('yaemiko'));assert.equal(appearanceCharacterName(0,'yaemiko'),'八重神子');assert.equal(NATIVE_APPEARANCES.yaemiko.characterId,0);
  const actor=createNativeCharacter(data,{loadTextures:false}),p=new THREE.Vector3(),expected=new THREE.Vector3();
  try{
    actor.group.position.set(2,3,-4);actor.group.rotation.y=.7;actor.setPoseFrame(0,data.poses[262].start+3.5);const native=matrices(actor),skeleton=actor.skeleton;
    await actor.setAppearance('yaemiko');const mesh=actor.mesh;
    actor.setSourceRestPose(true);actor.updateSecondaryMotion(1/60);assert.equal(actor.secondaryMotionStatus.enabled,false);
    for(let i=0;i<mesh.geometry.attributes.position.count;i++){
      p.fromBufferAttribute(mesh.geometry.attributes.position,i);expected.copy(p).applyMatrix4(mesh.matrixWorld);mesh.applyBoneTransform(i,p);mesh.localToWorld(p);assert.ok(p.distanceTo(expected)<1e-6);
    }
    actor.setSourceRestPose(false);
    for(const name of ['original','doubao','springfield','ganyu','yaemiko']){await actor.setAppearance(name);assert.deepEqual(matrices(actor),native);assert.equal(actor.skeleton,skeleton);assert.equal(actor.skeleton.bones.length,30);}
    assert.equal(actor.mesh,mesh);assert.equal(mesh.skeleton.bones.length,78);assert.equal(actor.nativeSpace.children.filter(n=>n.isSkinnedMesh).length,1);
    const weapon=new THREE.Group(),palm=actor.getAttachment('d_wpnRP');palm.add(weapon);actor.registerVisualAttachment(weapon,'d_wpnRP');
    for(const id of [6,144,151,262]){actor.setPoseFrame(data.poses[id].source,data.poses[id].start);actor.updateSecondaryMotion(1/60);assert.ok(weapon.getWorldPosition(p).distanceTo(mesh.skeleton.bones[25].getWorldPosition(expected))<.2);}
    await actor.setAppearance('original');assert.equal(weapon.parent,palm);
  }finally{actor.dispose();}
}));

test('Yae Miko run, jump, guard, attacks and blending keep the face coherent and limb lengths fixed',async()=>withFetch(async()=>{
  const actor=createNativeCharacter(data,{loadTextures:false}),reference=createNativeCharacter(data,{loadTextures:false});
  try{
    await actor.setAppearance('yaemiko');const {skin}=await loadEnhancedCharacterData(0,'yaemiko'),geometry=actor.mesh.geometry,bones=actor.mesh.skeleton.bones;
    const materials=new Set(skin.materials.flatMap((m,i)=>headNames.has(m.name)?[i]:[])),samples=[...new Set(skin.faces.filter(f=>materials.has(f.material)).flatMap(f=>f.indices))].filter((_,i)=>i%47===0);
    const lengths=bones.slice(0,30).map(b=>b.position.length()),p=new THREE.Vector3(),expected=new THREE.Vector3();
    for(const id of [6,16,90,117,144,151,152,200,202,248,262,263,264,279,295])for(const frame of [data.poses[id].start,(data.poses[id].start+data.poses[id].end)/2,data.poses[id].end]){
      actor.setPoseFrame(data.poses[id].source,frame);reference.setPoseFrame(data.poses[id].source,frame);actor.resetSecondaryMotion();actor.updateSecondaryMotion(1/60,{groundY:-5});assert.deepEqual(matrices(actor),matrices(reference));
      actor.mesh.computeBoundingBox();const box=actor.mesh.boundingBox.clone().applyMatrix4(actor.mesh.matrixWorld);assert.ok([...box.min.toArray(),...box.max.toArray()].every(Number.isFinite));assert.ok(box.getSize(p).length()<10);
      for(let i=1;i<30;i++)assert.ok(Math.abs(bones[i].position.length()-lengths[i])<1e-6);
      const head=bones[13].matrixWorld.clone().multiply(actor.mesh.skeleton.boneInverses[13]);
      for(const i of samples){p.fromBufferAttribute(geometry.attributes.position,i);expected.copy(p).applyMatrix4(head);actor.mesh.applyBoneTransform(i,p);actor.mesh.localToWorld(p);assert.ok(p.distanceTo(expected)<1e-5);}
    }
    const from={source:0,frame:data.poses[144].start+3},to={source:0,frame:data.poses[151].start+3};actor.setPoseBlend(from,to,.4);reference.setPoseBlend(from,to,.4);assert.deepEqual(matrices(actor),matrices(reference));
    for(let i=1;i<30;i++)assert.ok(Math.abs(bones[i].position.length()-lengths[i])<1e-6);
  }finally{actor.dispose();reference.dispose();}
}));

test('Yae Miko hair is restrained, settles and honors the disabled preference after switches',async()=>withFetch(async()=>{
  const actor=createNativeCharacter(data,{loadTextures:false});
  try{
    await actor.setAppearance('yaemiko');const {skin}=await loadEnhancedCharacterData(0,'yaemiko');assert.equal(actor.secondaryMotionStatus.bones,48);
    assert.ok(skin.secondaryMotion.bones.every(b=>b.follow>=.98&&b.globalMaxAngle<=.04));
    for(let f=0;f<240;f++){
      const t=Math.min(f,89)/60,pose=data.poses[144];actor.group.position.x=Math.sin(t*2)*.3;actor.group.rotation.y=Math.sin(t*3)*.6;actor.setPoseFrame(pose.source,pose.start+t*20%(pose.end-pose.start));actor.updateSecondaryMotion(1/60);
      for(const n of actor.getSecondaryMotionSnapshot()){assert.ok([...n.tail,...n.position].every(Number.isFinite));assert.ok(Math.abs(new THREE.Vector3().fromArray(n.tail).distanceTo(new THREE.Vector3().fromArray(n.position))-n.length)<1e-6);}
    }
    const energy=actor.getSecondaryMotionSnapshot().reduce((sum,n)=>sum+new THREE.Vector3().fromArray(n.tail).distanceToSquared(new THREE.Vector3().fromArray(n.previous)),0);assert.ok(energy<1e-7);
    actor.setSecondaryMotionEnabled(false);await actor.setAppearance('doubao');await actor.setAppearance('yaemiko');assert.equal(actor.secondaryMotionStatus.enabled,false);
  }finally{actor.dispose();}
}));

test('Yae Miko game adoption preserves story identity, HP, air motion and the current command',async()=>withFetch(async()=>{
  const character=createNativeCharacter(data,{loadTextures:false}),game=Object.create(MeteorGame.prototype),events=[];
  const move={id:'sword-air-down'},timeline={pose:{id:151},time:.31},combat={timeline,combo:2,currentMove:move},mission={id:'sn01',stage:'fighting'};
  const actor={id:1,scriptId:0,name:'孟星魂',character,root:character.group,hp:721,maxHp:1500,rage:33,weaponId:5,weapon:'dagger',vy:3.2,grounded:false,team:1,combat};
  Object.assign(game,{ready:Promise.resolve(),hero:actor,characterId:0,appearanceRequest:0,missionState:mission,_hud(){},onEvent:e=>events.push(e)});
  character.setPoseFrame(0,data.poses[151].start+3);character.group.position.set(1,4,6);character.group.updateMatrixWorld(true);const native=matrices(character),frame=character.frame;
  try{
    const result=await game.setCharacterAppearance('yaemiko');assert.equal(result.available,true);assert.equal(game.characterAppearance,'yaemiko');assert.equal(actor.name,'孟星魂');assert.equal(actor.scriptId,0);assert.equal(actor.hp,721);assert.equal(actor.rage,33);assert.equal(actor.vy,3.2);assert.equal(actor.grounded,false);assert.equal(actor.weaponId,5);
    assert.equal(game.hero,actor);assert.equal(game.missionState,mission);assert.equal(combat.timeline,timeline);assert.equal(combat.currentMove,move);assert.equal(timeline.time,.31);assert.equal(character.frame,frame);assert.deepEqual(matrices(character),native);assert.equal(events.at(-1).appearance,'yaemiko');
  }finally{character.dispose();}
}));

test('missing Yae Miko assets preserve the previous appearance and reject incompatible native bodies',async()=>{
  const module=await import('../dist/native-character.js?yaemiko-missing'),before=globalThis.fetch;globalThis.fetch=async url=>new URL(url).pathname.includes('/enhanced/yaemiko/')?new Response('',{status:404}):fileFetch(url);
  const actor=module.createNativeCharacter(data,{loadTextures:false});
  try{
    await actor.setAppearance('springfield');const mesh=actor.mesh,result=await actor.setAppearance('yaemiko');assert.equal(result.available,false);assert.equal(result.appearance,'springfield');assert.equal(actor.mesh,mesh);assert.match(result.reason,/404/);
    const other=module.createNativeCharacter(await module.loadNativeCharacterData(1),{loadTextures:false});try{assert.equal((await other.setAppearance('yaemiko')).available,false);assert.equal(other.appearance,'original');}finally{other.dispose();}
  }finally{actor.dispose();globalThis.fetch=before;}
});

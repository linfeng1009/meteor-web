import test from 'node:test';
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {createHash} from 'node:crypto';
import * as THREE from '../dist/vendor/three.module.js';
import {createNativeCharacter,loadNativeCharacterData,loadEnhancedCharacterData,NATIVE_APPEARANCES} from '../dist/native-character.js';
import {appearanceCharacterName,WORKSHOP_APPEARANCES} from '../dist/character-appearances.js';
import {sourcePmxVertices} from './helpers/source-pmx-vertices.mjs';

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
  const target=new URL(url);assert.ok(target.protocol==='file:'&&target.pathname.startsWith(dist.pathname),'runtime loads project dist only');
  try{return new Response(await readFile(target));}catch{return new Response('',{status:404});}
};
const withFetch=async callback=>{const before=globalThis.fetch;globalThis.fetch=fileFetch;try{return await callback();}finally{globalThis.fetch=before;}};
const data=await withFetch(()=>loadNativeCharacterData(0));
const matrices=actor=>[...actor.bones,...actor.dummies].map(b=>b.matrixWorld.toArray());
const build=await json('work/shogun-import-2026-11-10/build-evidence.json');
const proportions=await json('work/shogun-proportions-2026-11-10/proportions.json');

test('Raiden Shogun archive and editable actions do not depend on the original download directory',async()=>{
  const inventory=await json('work/shogun-import-2026-11-10/source-copy.json');
  assert.equal(inventory.complete,true);assert.equal(inventory.archive,'assets/source/shogun');assert.equal(inventory.files.length,20);
  for(const file of inventory.files){const bytes=await readFile(new URL(inventory.archive+'/'+file.path,root));assert.equal(bytes.length,file.bytes);assert.equal(sha(bytes),file.sha256);}
  const script=await readFile(new URL('scripts/blender/build_shogun.py',root),'utf8');
  assert.equal(script.includes('/Downloads/'),false);assert.equal(/Path\(['"]\/Users\//.test(script),false);
  assert.equal(build.sourceDownloadsRequired,false);assert.ok(build.restMatrixError<1e-4);assert.ok(build.poseMatrixError<1e-3);
  assert.deepEqual(build.bakedActions.map(a=>a.pose),[6,144,151,262]);
  assert.equal(build.sourceGeometryMaxError,0);assert.equal(build.proportionalDisplayRig,true);
  assert.ok(build.packedImages.every(i=>i.packed));
});

test('Raiden Shogun keeps every source vertex, texture and the author credits',async()=>withFetch(async()=>{
  const {skin,manifest,path}=await loadEnhancedCharacterData(0,'shogun');
  assert.equal(skin.vertexCount,20614);assert.equal(skin.triangleCount,22574);
  assert.equal(manifest.stats.sourceTriangles,25517);assert.equal(manifest.stats.omittedTriangles,2943);
  assert.equal(manifest.complete,true);assert.equal(manifest.completeness.faceGeometry,true);
  assert.equal(skin.materials.length,22);
  const sources=manifest.sourceFiles.filter(s=>s.runtime);assert.equal(sources.length,4);
  for(const source of sources){
    const target=new URL(source.runtime,path);assert.ok(target.pathname.startsWith(path.pathname));
    const bytes=await readFile(target);assert.equal(sha(bytes),source.runtimeSha256??source.sha256);
    assert.deepEqual(imageSize(bytes),source.size);
    assert.equal(sha(await readFile(new URL('assets/source/shogun/'+source.file,root))),source.sha256);
  }
  assert.equal(manifest.provenance.modelAuthor,'miHoYo');assert.match(manifest.provenance.rigAuthor,/观海/);
  assert.match(manifest.provenance.license,/forbids redistribution/);
  assert.ok(skin.materials.some(m=>m.hairSurface));assert.ok(skin.materials.some(m=>m.skinSurface));
}));

// The user-visible failure mode is a retarget that keeps total height but
// compresses the torso or widens the shoulders. Proving preservation means the
// same source vertex IDs land on the same uniform-scaled points.
test('Raiden Shogun preserves every source vertex uniformly: no torso, limb or head compression',async()=>withFetch(async()=>{
  const {skin}=await loadEnhancedCharacterData(0,'shogun');
  const source=sourcePmxVertices(await readFile(new URL('assets/source/shogun/雷电将军.pmx',root)));
  const floor=Math.min(...source.map(v=>v.position[1])),top=Math.max(...source.map(v=>v.position[1])),scale=39.4/(top-floor);
  assert.equal(source.length,skin.vertexCount);
  for(let i=0;i<source.length;i++){
    const {position:[x,y,z],normal,uv}=source[i],expected=[x*scale,z*scale,(y-floor)*scale],length=Math.hypot(...normal);
    for(let axis=0;axis<3;axis++){
      assert.ok(Math.abs(skin.positions[i*3+axis]-expected[axis])<1e-5,`vertex ${i} axis ${axis}`);
      assert.ok(Math.abs(skin.normals[i*3+axis]-[normal[0],normal[2],normal[1]][axis]/length)<1e-5);
    }
    assert.ok(Math.abs(skin.uvs[i*2]-uv[0])<1e-7&&Math.abs(skin.uvs[i*2+1]-(1-uv[1]))<1e-7);
  }
  assert.ok(proportions.maxVertexDeviationFromUniformSource<1e-6);
  assert.equal(proportions.maxDisplayRigPositionError,0);
  assert.deepEqual(proportions.segmentsThatChangeLength,[]);
  for(const metric of proportions.metrics)assert.ok(Math.abs(metric.relativeChangePct)<1e-3,`${metric.label} must not change`);
  assert.ok(Math.abs(proportions.metrics.find(m=>m.label==='total_rest_height').runtime-39.4)<1e-4);
  for(const band of proportions.measuredMeshBands){
    assert.ok(Math.abs(band.width.relativeChangePct)<1e-3,`band ${band.sourceHeightFraction} width`);
    assert.ok(Math.abs(band.depth.relativeChangePct)<1e-3,`band ${band.sourceHeightFraction} depth`);
  }
  assert.deepEqual(proportions.sourceBounds,proportions.runtimeBounds);
}));

test('Raiden Shogun display rig follows the original moves without changing limb lengths',async()=>withFetch(async()=>{
  const {skin}=await loadEnhancedCharacterData(0,'shogun');
  const actor=createNativeCharacter(data,{loadTextures:false}),point=new THREE.Vector3(),expected=new THREE.Vector3();
  try{
    await actor.setAppearance('shogun');
    assert.equal(actor.sourceRestAvailable,true);
    actor.group.position.set(3,1,-2);actor.group.rotation.y=.5;actor.setPoseFrame(0,data.poses[262].end);
    const native=matrices(actor);
    assert.equal(actor.setSourceRestPose(true),true);actor.updateSecondaryMotion(1/60);
    assert.equal(actor.secondaryMotionStatus.enabled,false);
    for(let i=0;i<skin.vertexCount;i+=37){
      point.fromBufferAttribute(actor.mesh.geometry.attributes.position,i);
      expected.copy(point).applyMatrix4(actor.mesh.matrixWorld);
      actor.mesh.applyBoneTransform(i,point);actor.mesh.localToWorld(point);
      assert.ok(point.distanceTo(expected)<1e-6,'original-pose inspection must reproduce the source surface');
    }
    assert.deepEqual(matrices(actor),native);
    actor.setSourceRestPose(false);assert.equal(actor.secondaryMotionStatus.enabled,true);
    const bones=actor.mesh.skeleton.bones.slice(0,30),lengths=bones.map(b=>b.position.length());
    for(const id of [6,144,151,262])for(const frame of [data.poses[id].start,data.poses[id].end]){
      actor.setPoseFrame(data.poses[id].source,frame);
      for(let i=1;i<30;i++)assert.ok(Math.abs(bones[i].position.length()-lengths[i])<1e-6,'animation must retain original limb lengths');
    }
  }finally{actor.dispose();}
}));

test('Raiden Shogun is selectable in the workshop with its own identity',async()=>{
  assert.ok(WORKSHOP_APPEARANCES.includes('shogun'));
  assert.equal(appearanceCharacterName(0,'shogun'),'雷电将军');
  assert.equal(NATIVE_APPEARANCES.shogun.characterId,0);
  assert.equal(Object.isFrozen(NATIVE_APPEARANCES.shogun),true);
});
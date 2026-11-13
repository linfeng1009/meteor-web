import test from 'node:test';
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {createHash} from 'node:crypto';
import * as THREE from '../dist/vendor/three.module.js';
import {createNativeCharacter,loadNativeCharacterData,loadEnhancedCharacterData,NATIVE_APPEARANCES} from '../dist/native-character.js';
import {appearanceCharacterName,WORKSHOP_APPEARANCES} from '../dist/character-appearances.js';

// Runtime textures may be PNG or WebP (the deployment converts atlases to WebP
// to fit a 3 Mbit uplink), so the check is "a real image with a known magic".
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
const build=await json('work/ningguang-import-2026-11-11/build-evidence.json');
const proportions=await json('work/ningguang-proportions-2026-11-11/proportions.json');

test('Ningguang archive is a single editable .blend and the build does not depend on Downloads',async()=>{
  const inventory=await json('work/ningguang-import-2026-11-11/source-copy.json');
  assert.equal(inventory.complete,true);assert.equal(inventory.archive,'assets/source/ningguang');assert.equal(inventory.files.length,1);
  for(const file of inventory.files){
    const bytes=await readFile(new URL(inventory.archive+'/'+file.path,root));
    assert.equal(bytes.length,file.bytes);assert.equal(sha(bytes),file.sha256);
  }
  assert.equal(build.sourceFormat,'blend');assert.equal(build.sourceDownloadsRequired,false);
  assert.ok(build.restMatrixError<1e-4);assert.ok(build.poseMatrixError<1e-3);
  assert.deepEqual(build.bakedActions.map(a=>a.pose),[6,144,151,262]);
  assert.equal(build.sourceGeometryMaxError,0);assert.equal(build.proportionalDisplayRig,true);
  const script=await readFile(new URL('scripts/blender/build_ningguang.py',root),'utf8');
  assert.equal(script.includes('/Downloads/'),false);
  assert.equal(/Path\(['"]\/Users\//.test(script),false);
});

test('Ningguang keeps every kept vertex and the textures packed inside the .blend',async()=>withFetch(async()=>{
  const {skin,manifest,path}=await loadEnhancedCharacterData(0,'ningguang');
  assert.equal(skin.vertexCount,24547);assert.equal(skin.triangleCount,23805);
  assert.equal(manifest.stats.sourceTriangles,31188);assert.equal(manifest.stats.omittedTriangles,7383);
  assert.equal(manifest.complete,true);assert.equal(manifest.completeness.faceGeometry,true);
  assert.equal(skin.materials.length,29);
  const blend=manifest.sourceFiles.find(s=>s.runtime===undefined);
  assert.equal(blend.file,'凝光_纱中幽兰_可编辑.blend');
  assert.equal(sha(await readFile(new URL('assets/source/ningguang/'+blend.file,root))),blend.sha256);
  const textures=manifest.sourceFiles.filter(s=>s.runtime);
  assert.equal(textures.length,3);
  for(const source of textures){
    const target=new URL(source.runtime,path);assert.ok(target.pathname.startsWith(path.pathname));
    const bytes=await readFile(target);assert.equal(sha(bytes),source.runtimeSha256??source.sha256);
    assert.notEqual(imageMagic(bytes),'unknown','runtime textures must be a real image');
  }
  assert.match(manifest.provenance.modelAuthor,/miHoYo/);
  assert.match(manifest.provenance.license,/No readme/);
  assert.deepEqual(manifest.omittedRenderPasses.map(p=>p.material).sort(),['肌','肌2']);
}));

// A .blend cannot be parsed in Node, so the vertex-level comparison is produced
// by audit_ningguang_proportions.py in Blender and asserted here together with
// the invariants that can be checked from mesh.json alone.
test('Ningguang preserves the source body: uniform vertices, unchanged segments, soles on the ground',async()=>withFetch(async()=>{
  const {skin}=await loadEnhancedCharacterData(0,'ningguang');
  assert.ok(proportions.maxVertexDeviationFromUniformSource<1e-6);
  // 颜2/白目/睫 share vertices exactly with the layer under them, so the build
  // gives them a bounded sub-millimetre outward bias against z-fighting.
  assert.equal(proportions.decalVertices,510);assert.equal(build.decalVertices,510);
  assert.ok(build.decalBiasMax>0&&build.decalBiasMax<proportions.sourceUniformScale*.004);
  assert.equal(proportions.maxDisplayRigPositionError,0);
  assert.deepEqual(proportions.segmentsThatChangeLength,[]);
  for(const metric of proportions.metrics)assert.ok(Math.abs(metric.relativeChangePct)<1e-3,`${metric.label} must not change`);
  assert.deepEqual(proportions.sourceBounds,proportions.runtimeBounds);
  for(const band of proportions.measuredMeshBands){
    assert.ok(Math.abs(band.width.relativeChangePct)<1e-3);
    assert.ok(Math.abs(band.depth.relativeChangePct)<1e-3);
  }
  // Feet on the ground: the lowest sole vertex must sit at z ~ 0 and the source
  // has nothing hanging below the soles.
  const FOOT_SLOTS=new Set([5,6,9,10]);let soleMin=Infinity,meshMin=Infinity;
  for(let i=0;i<skin.vertexCount;i++){
    const z=skin.positions[i*3+2];meshMin=Math.min(meshMin,z);
    let w=0;for(let k=0;k<4;k++)if(FOOT_SLOTS.has(skin.skinIndices[i*4+k]))w+=skin.skinWeights[i*4+k];
    if(w>=.5)soleMin=Math.min(soleMin,z);
  }
  assert.ok(Math.abs(soleMin)<.05,`sole must sit on the ground plane, got ${soleMin}`);
  assert.ok(Math.abs(build.geometryBelowSole)<.05,`nothing hangs below the soles, got ${build.geometryBelowSole}`);
  assert.ok(meshMin>-.05);
  assert.equal(skin.secondaryMotion,null,'this source has no hair spring chain');
}));

test('Ningguang display rig follows the original moves without changing limb lengths',async()=>withFetch(async()=>{
  const actor=createNativeCharacter(data,{loadTextures:false}),point=new THREE.Vector3(),expected=new THREE.Vector3();
  try{
    await actor.setAppearance('ningguang');
    assert.equal(actor.sourceRestAvailable,true);
    actor.group.position.set(3,1,-2);actor.group.rotation.y=.5;actor.setPoseFrame(0,data.poses[262].end);
    const native=matrices(actor);
    assert.equal(actor.setSourceRestPose(true),true);actor.updateSecondaryMotion(1/60);
    assert.equal(actor.secondaryMotionStatus.available,false,'this source has no hair spring chain');
    const geometry=actor.mesh.geometry;
    for(let i=0;i<geometry.attributes.position.count;i+=37){
      point.fromBufferAttribute(geometry.attributes.position,i);
      expected.copy(point).applyMatrix4(actor.mesh.matrixWorld);
      actor.mesh.applyBoneTransform(i,point);actor.mesh.localToWorld(point);
      assert.ok(point.distanceTo(expected)<1e-6,'original-pose inspection must reproduce the source surface');
    }
    assert.deepEqual(matrices(actor),native);
    const bones=actor.mesh.skeleton.bones.slice(0,30),lengths=bones.map(b=>b.position.length());
    for(const id of [6,144,151,262])for(const frame of [data.poses[id].start,data.poses[id].end]){
      actor.setPoseFrame(data.poses[id].source,frame);
      for(let i=1;i<30;i++)assert.ok(Math.abs(bones[i].position.length()-lengths[i])<1e-6,'animation must retain original limb lengths');
    }
  }finally{actor.dispose();}
}));

test('Ningguang is selectable in the workshop with its own identity',async()=>{
  assert.ok(WORKSHOP_APPEARANCES.includes('ningguang'));
  assert.equal(appearanceCharacterName(0,'ningguang'),'凝光');
  assert.equal(NATIVE_APPEARANCES.ningguang.characterId,0);
  assert.equal(Object.isFrozen(NATIVE_APPEARANCES.ningguang),true);
});
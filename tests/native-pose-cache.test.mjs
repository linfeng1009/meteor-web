import test from 'node:test';
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {createNativeCharacter,loadNativeCharacterData} from '../dist/native-character.js';
const previousFetch=globalThis.fetch;
globalThis.fetch=async input=>{try{return new Response(await readFile(new URL(input)));}catch{return new Response('',{status:404});}};
const original=await loadNativeCharacterData(0);globalThis.fetch=previousFetch;
function fixture(){
 let reads=0;const animations=original.animations.map(a=>({...a,decoder:{decode(bytes){reads++;return a.decoder.decode(bytes);}}}));
 const data={...original,animations},actors=[createNativeCharacter(data,{loadTextures:false}),createNativeCharacter(data,{loadTextures:false})];
 return {animations,actors,get reads(){return reads;},reset(){reads=0;},dispose(){actors.forEach(a=>a.dispose());}};
}
test('多角色共享同一源帧的挂点元数据，但各自保留骨骼、朝向和姿势更新',()=>{
 const f=fixture();try{
  f.reset();const[a,b]=f.actors;let updates=0;a.onPoseUpdate(()=>updates++);
  a.setPoseFrame(0,7000.25);const first=f.reads;assert.equal(first,f.animations[0].dummyCount);
  b.setPoseFrame(0,7000.75);a.setPoseFrame(0,7000.25);assert.equal(f.reads,first);assert.equal(updates,2);
  assert.notEqual(a.bones[0],b.bones[0]);a.group.rotation.y=1.2;a.setPoseFrame(0,7000.25);
  assert.notDeepEqual(a.bones[0].matrixWorld.toArray(),b.bones[0].matrixWorld.toArray());
  a.setPoseBlend({source:0,frame:7000.25},{source:0,frame:7010.25},.5);a.setPoseFrame(0,7000.25);
  assert.equal(a.frame,7000.25);assert.equal(a.source,0);
 }finally{f.dispose();}
});
test('缓存保留每帧原挂点换父级，切换动画源不串扰，并在128帧后逐出旧数据',()=>{
 const f=fixture();try{
  const actor=f.actors[0],decoder=new TextDecoder();
  for(const[source,frame]of[[0,12000],[0,12640],[1,2],[0,12000],[1,3]]){
   const a=f.animations[source],lo=Math.floor(frame);actor.setPoseFrame(source,frame);
   for(let i=0;i<a.dummyCount;i++){
    const offset=a.frameOffset(lo)+20+a.boneCount*16+i*33;
    const name=decoder.decode(a.bytes.subarray(offset,offset+5)).replace(/\0+$/,'');
    const parent=actor.getAttachment(name)||actor.nativeSpace;
    assert.equal(actor.dummies[i].parent,parent,`${source}:${frame}:${i}:${name}`);
   }
  }
  actor.setPoseFrame(0,9000);for(let i=1;i<=128;i++)actor.setPoseFrame(0,9000+i);
  f.reset();actor.setPoseFrame(0,9000);assert.equal(f.reads,f.animations[0].dummyCount,'bounded cache must decode an evicted frame again');
 }finally{f.dispose();}
});

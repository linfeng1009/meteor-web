import test from 'node:test';
import assert from 'node:assert/strict';
import * as THREE from '../dist/vendor/three.module.js';
import {NetworkReplicaMotion,NetworkGame,networkPoseBlend} from '../dist/network-game.js';

function fixture(){
  const actor={root:new THREE.Group(),hp:1000,combat:{timeline:{pose:{start:0,end:100},frame:0}},character:{frame:0,setPoseFrame(source,frame){this.source=source;this.frame=frame;}}};
  const motion=new NetworkReplicaMotion(),state={position:[0,0,0],angle:0,dead:false,source:0,frame:10};
  motion.receive(actor,state,.1);return {actor,motion,state};
}
test('replica interpolates position, shortest angle and same-motion frames without simulating HP',()=>{
  const {actor,motion,state}=fixture();actor.root.rotation.y=Math.PI-.1;
  motion.receive(actor,{...state,position:[2,1,0],angle:-Math.PI+.1,frame:20},.1);
  motion.update(actor,.05);assert.deepEqual(actor.root.position.toArray(),[1,.5,0]);assert.ok(Math.abs(actor.root.rotation.y-Math.PI)<1e-9);assert.equal(actor.character.frame,15);assert.equal(actor.hp,1000);
  motion.update(actor,.05);assert.deepEqual(actor.root.position.toArray(),[2,1,0]);assert.equal(actor.root.rotation.y,-Math.PI+.1);assert.equal(actor.character.frame,20);
  motion.update(actor,5);assert.deepEqual(actor.root.position.toArray(),[2,1,0],'no extrapolation on stalled network');
});
test('new snapshot blends from the displayed position rather than the unfinished old target',()=>{
  const {actor,motion,state}=fixture();motion.receive(actor,{...state,position:[2,0,0]},.1);motion.update(actor,.025);
  assert.equal(actor.root.position.x,.5);motion.receive(actor,{...state,position:[3,0,0]},.1);assert.equal(actor.root.position.x,.5);
  motion.update(actor,.05);assert.equal(actor.root.position.x,1.75);
});
test('death, respawn and large corrections snap and remain stable on the next render',()=>{
  const {actor,motion,state}=fixture();
  for(const next of [{...state,dead:true,position:[1,0,0]},{...state,position:[2,0,0]},{...state,position:[20,0,0]}]){
    motion.receive(actor,next,.1);assert.deepEqual(actor.root.position.toArray(),next.position);motion.update(actor,.016);assert.deepEqual(actor.root.position.toArray(),next.position);
  }
});
test('new actions and looping frames never blend unrelated animation frames',()=>{
  const {actor,motion,state}=fixture();motion.receive(actor,{...state,frame:50},.1,{poseChanged:true});assert.equal(actor.character.frame,50);
  motion.receive(actor,{...state,frame:5},.1);motion.update(actor,.05);assert.equal(actor.character.frame,5);
  motion.receive(actor,{...state,source:1,frame:30},.1);assert.equal(actor.character.frame,30);
});
test('guest interpolation runs on render presentation, independently of fixed combat ticks',()=>{
  const {actor,state}=fixture(),peer=fixture().actor;actor.networkId='guest';peer.networkId='host';let drawn=0;
  const original=function(){drawn++;},game={hero:actor,enemies:[peer],pause(){},_updatePresentation:original};
  const session=new NetworkGame(game,{host:false,playerId:'guest',send(){}},{players:[{id:'host'},{id:'guest'}]});session.active=true;
  session.presentation.receive(actor,state,.1);session.presentation.receive(actor,{...state,position:[2,0,0]},.1);
  game._updateFighter(actor,1/60);assert.equal(actor.root.position.x,0,'guest combat tick must not advance presentation or simulation');
  game._updatePresentation(.025);assert.equal(actor.root.position.x,.5);assert.equal(drawn,1);
  session.dispose();assert.equal(game._updatePresentation,original,'leaving restores the single-player presentation hook');
});

function blending(){
 const f=fixture(),calls=[];let captured=0;
 f.actor.character.setPoseBlend=function(from,to,weight){this.source=to.source;this.frame=to.frame;calls.push({from,to,weight});};
 f.actor.character.capturePose=function(){return {source:this.source,frame:this.frame,snapshot:{id:++captured,transforms:['本地姿势']}};};
 return {...f,calls,blend:{from:{source:0,frame:10},to:{source:0,frame:20},weight:.2,duration:.3}};
}

test('联机过渡只传帧描述和权重，不发送受击姿势的骨骼数组',()=>{
 const wire=networkPoseBlend({from:{source:0,frame:10,snapshot:{id:1,transforms:Array(100).fill({position:[1,2,3]})}},to:{source:0,frame:20},weight:.5,duration:.3});
 assert.equal(wire.fromSnapshot,true);assert.equal('snapshot' in wire.from,false);assert.ok(JSON.stringify(wire).length<200);assert.equal(networkPoseBlend(null),null);
});

test('客人按主机权重平滑换招，结束过渡时不会突然跳到完整目标姿势',()=>{
 const {actor,motion,state,calls,blend}=blending();
 motion.receive(actor,{...state,frame:20,serial:2,blend},.1,{poseChanged:true});assert.equal(calls.at(-1).weight,.2);
 motion.receive(actor,{...state,frame:20,serial:2,blend:{...blend,weight:.8}},.1);motion.update(actor,.05);assert.ok(Math.abs(calls.at(-1).weight-.5)<1e-9);
 motion.receive(actor,{...state,frame:30,serial:2},.1);assert.equal(calls.at(-1).weight,0);assert.ok(calls.at(-1).from.snapshot);
 motion.update(actor,.05);assert.equal(calls.at(-1).weight,.5);motion.update(actor,.05);assert.equal(calls.at(-1).weight,1);
 motion.receive(actor,{...state,frame:40,serial:2},.1);motion.update(actor,.05);assert.equal(actor.character.frame,35);assert.equal(actor.hp,1000);
});

test('受击过渡从客人当前显示姿势捕获一次，重复快照不重新捕获',()=>{
 const {actor,motion,state,calls,blend}=blending(),hit={...blend,fromSnapshot:true};
 motion.receive(actor,{...state,frame:20,serial:3,blend:hit},.1,{poseChanged:true});const first=calls.at(-1).from;
 assert.ok(first.snapshot);motion.receive(actor,{...state,frame:20,serial:3,blend:{...hit,weight:.6}},.1);motion.update(actor,.05);assert.equal(calls.at(-1).from,first);
 motion.receive(actor,{...state,frame:20,serial:4,blend:hit},.1,{poseChanged:true});assert.notEqual(calls.at(-1).from,first);
});

test('旧混合被主机新动作中断时，客人立即显示新动作而不补播旧混合',()=>{
 for(const poseChanged of [false,true]){
  const {actor,motion,state,calls,blend}=blending();
  motion.receive(actor,{...state,frame:20,serial:2,blend},.1,{poseChanged:true});
  motion.receive(actor,{...state,frame:20,serial:2,blend:{...blend,weight:.8}},.1);motion.update(actor,.025);
  assert.ok(calls.at(-1).weight<1);const count=calls.length;
  motion.receive(actor,{...state,frame:70,serial:3},.1,{poseChanged});
  assert.equal(calls.length,count);assert.equal(actor.character.source,0);assert.equal(actor.character.frame,70);
  assert.equal(motion.samples.get(actor).blend,undefined);
  motion.update(actor,.05);assert.equal(calls.length,count);assert.equal(actor.character.frame,70);
 }
});

test('动作编号改变时不延续旧混合，即使收到重复的施招序号',()=>{
 const {actor,motion,state,calls,blend}=blending();motion.receive(actor,{...state,frame:20,serial:2,blend},.1,{poseChanged:true});
 const count=calls.length;motion.receive(actor,{...state,frame:75,serial:2},.1,{poseChanged:true});
 assert.equal(calls.length,count);assert.equal(actor.character.frame,75);assert.equal(motion.samples.get(actor).blend,undefined);
});

test('网络停顿不把未完成的主机过渡外推到结束，静止姿势不重复采样',()=>{
 const {actor,motion,state,calls,blend}=blending();motion.receive(actor,{...state,frame:20,serial:2,blend},.1,{poseChanged:true});motion.update(actor,1);
 assert.equal(calls.at(-1).weight,.2);const count=calls.length;for(let i=0;i<60;i++)motion.update(actor,1/60);assert.equal(calls.length,count);
 motion.receive(actor,{...state,frame:0,serial:3,dead:true},.1);assert.equal(actor.character.frame,0,'死亡切换不能残留活人过渡');
});

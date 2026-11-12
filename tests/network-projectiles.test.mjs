import test from 'node:test';
import assert from 'node:assert/strict';
import * as T from '../dist/vendor/three.module.js';
import {NativeProjectileSystem,NativeWheelSystem} from '../dist/native-projectiles.js';
import {networkProjectileSnapshot,NetworkProjectileMotion} from '../dist/network-projectiles.js';
const v=(x=0,y=0,z=0)=>new T.Vector3(x,y,z);
const state=(patch={})=>({kind:'dart',id:1,ownerId:'owner',weaponId:1,position:[0,1,0],quaternion:[0,0,0,1],spin:0,phase:'outbound',...patch});
function fixture(){
 const scene=new T.Scene(),template=new T.Mesh(new T.BoxGeometry(1,1,1),new T.MeshBasicMaterial()),owner={networkId:'owner',root:new T.Group(),weapon:'wheel',weaponModel:template.clone(),hp:1000};
 let hits=0,loads=0;const game={scene,_prepareWeapon:async()=>{loads++;return [template];},_applyNativeHit(){hits++;}};
 const actors=new Map([['owner',owner]]),motion=new NetworkProjectileMotion(game,actors);
 return {game,scene,template,owner,actors,motion,get loads(){return loads;},get hits(){return hits;},dispose(){motion.dispose();template.geometry.dispose();template.material.dispose();}};
}

test('房主投射物快照区分飞镖飞轮序号，并保留发射时物品而非射手当前装备',()=>{
 const f=fixture(),darts=new NativeProjectileSystem({scene:f.scene}),wheels=new NativeWheelSystem({scene:f.scene});try{
  const owner=f.owner;darts.spawn({owner,position:v(1,2,3),direction:v(0,0,1),context:{weaponId:10}});
  wheels.spawn({owner,position:v(2,3,4),direction:v(1,0,0),context:{attacker:{weaponId:11}}});owner.weaponId=6;
  const packet=networkProjectileSnapshot({projectiles:darts,wheels});assert.equal(packet.length,2);
  assert.deepEqual(packet.map(s=>[s.kind,s.id,s.weaponId]),[['dart',1,10],['wheel',1,11]]);
  assert.deepEqual(packet[0].position,[1,2,3]);assert.deepEqual(packet[0].quaternion,[0,0,0,1]);
  owner.disposed=true;assert.deepEqual(networkProjectileSnapshot({projectiles:darts,wheels}),[]);
 }finally{darts.dispose();wheels.dispose();f.dispose();}
});

test('客人只插值权威位置方向及自转，网络停顿不外推且不执行伤害',async()=>{
 const f=fixture();try{
  f.motion.receive([state()],.1);const sample=f.motion.samples.get('dart:1');await sample.ready;assert.ok(sample.visual);assert.equal(f.loads,1);
  const q=new T.Quaternion().setFromAxisAngle(v(0,1,0),Math.PI).toArray();f.motion.receive([state({position:[2,1,0],quaternion:q,spin:10})],.1);
  f.motion.update(.05);assert.deepEqual(sample.root.position.toArray(),[1,1,0]);assert.ok(Math.abs(sample.root.quaternion.y-Math.SQRT1_2)<1e-9);assert.equal(sample.spin,5);
  f.motion.update(1);assert.deepEqual(sample.root.position.toArray(),[2,1,0]);assert.equal(sample.spin,10);
  for(let i=0;i<60;i++)f.motion.update(1/60);assert.deepEqual(sample.root.position.toArray(),[2,1,0]);assert.equal(f.owner.hp,1000);assert.equal(f.hits,0);assert.equal(f.loads,1);
 }finally{f.dispose();}
});

test('飞轮返程继续使用同一个模型，收回或旧快照缺省投射物时恢复手中模型',async()=>{
 const f=fixture();let disposed=0;f.template.geometry.addEventListener('dispose',()=>disposed++);try{
  f.motion.receive([state({kind:'wheel',weaponId:2})],.1);assert.equal(f.owner.weaponModel.visible,false);
  const sample=f.motion.samples.get('wheel:1');await sample.ready;const visual=sample.visual;
  f.motion.receive([state({kind:'wheel',weaponId:2,phase:'return',position:[2,1,0],spin:4})],.1);f.motion.update(.1);
  assert.equal(sample.visual,visual);assert.equal(sample.phase,'return');assert.equal(f.loads,1);
  const newlyLoaded=f.template.clone();f.owner.weaponModel=newlyLoaded;f.motion.update(.016);assert.equal(newlyLoaded.visible,false);
  f.motion.receive();assert.equal(f.motion.samples.size,0);assert.equal(newlyLoaded.visible,true);assert.equal(visual.parent.parent,null);assert.equal(disposed,0);
 }finally{f.dispose();}
});

test('投射物消失或退出联机后，迟到的模型加载不能重新生成幽灵模型',async()=>{
 for(const dispose of [false,true]){
  const f=fixture();try{
   let finish;f.game._prepareWeapon=()=>new Promise(resolve=>{finish=resolve;});f.motion.receive([state()]);const sample=f.motion.samples.get('dart:1');await Promise.resolve();
   if(dispose)f.motion.dispose();else f.motion.receive([]);finish([f.template]);await sample.ready;
   assert.equal(f.motion.samples.size,0);assert.equal(sample.visual,undefined);assert.equal(f.motion.group.children.length,0);
  }finally{f.dispose();}
 }
});

test('加载失败可在新快照重试，发射者换装备不改变已发射的原物品模型',async()=>{
 const f=fixture();try{
  let calls=0;f.game._prepareWeapon=async id=>{assert.equal(id,10);if(++calls===1)throw Error('temporary');return [f.template];};
  f.motion.receive([state({weaponId:10})]);const sample=f.motion.samples.get('dart:1');await sample.ready;assert.equal(sample.visual,undefined);
  f.owner.weapon='sword';f.owner.weaponId=6;f.motion.receive([state({weaponId:10,position:[3,1,0]})]);f.motion.update(.1);await sample.ready;
  assert.ok(sample.visual);assert.equal(calls,2);assert.deepEqual(sample.root.position.toArray(),[3,1,0]);assert.equal(sample.visual.geometry,f.template.geometry);
 }finally{f.dispose();}
});

test('离开的玩家立即移除客人投射物，退出清理不释放共享原武器材质',async()=>{
 const f=fixture();let disposed=0;f.template.material.addEventListener('dispose',()=>disposed++);try{
  f.motion.receive([state({kind:'wheel',weaponId:2}),state()]);await Promise.all([...f.motion.samples.values()].map(s=>s.ready));
  f.motion.removeOwner('owner');assert.equal(f.motion.samples.size,0);assert.equal(f.owner.weaponModel.visible,true);assert.equal(disposed,0);
  f.motion.dispose();assert.equal(f.motion.group.parent,null);assert.equal(disposed,0);
 }finally{f.dispose();}
});

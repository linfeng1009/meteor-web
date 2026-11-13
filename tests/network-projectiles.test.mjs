import test from 'node:test';
import assert from 'node:assert/strict';
import * as T from '../dist/vendor/three.module.js';
import {NativeProjectileSystem,NativeWheelSystem} from '../dist/native-projectiles.js';
import {networkProjectileSnapshot,NetworkProjectileMotion,NetworkShortFlights} from '../dist/network-projectiles.js';
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
  assert.equal(sample.visual.rotation.z,-10);assert.equal(sample.visual.rotation.y,0);
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

test('主机近距离命中已无在途飞镖时，客人仍按真实短飞行显示一次且不重复判伤',async()=>{
 const f=fixture(),target={id:2,root:new T.Group(),hp:1000};f.owner.id=1;target.root.position.z=2.5;
 let hits=0;const darts=new NativeProjectileSystem({scene:f.scene,getTargets:()=>[target],onActorHit:()=>hits++}),game={projectiles:darts,matchElapsed:0},history=new NetworkShortFlights(game);
 try{
  darts.spawn({owner:f.owner,position:v(0,1.35,0),direction:v(0,0,1),context:{weaponId:1}});
  for(let i=0;i<6;i++){game.matchElapsed+=1/60;darts.update(1/60);}
  assert.equal(hits,1);assert.deepEqual(networkProjectileSnapshot(game),[]);const flights=history.snapshot(f.actors);assert.equal(flights.length,1);assert.ok(flights[0].endTime<.1);
  f.motion.receive([],.1,[],0);f.motion.receive([],.1,flights,.1);const sample=f.motion.samples.get('dart:1');assert.ok(sample);await sample.ready;
  f.motion.update(.025);assert.equal(sample.root.visible,true);assert.ok(sample.root.position.z>0&&sample.root.position.z<2.5);assert.equal(f.hits,0);
  f.motion.update(.075);assert.equal(f.motion.samples.size,0);
  f.motion.receive([],.1,flights,.2);assert.equal(f.motion.samples.size,0,'重复历史快照不能重播');
  game.matchElapsed=1;assert.deepEqual(history.snapshot(f.actors),[]);
 }finally{history.dispose();darts.dispose();f.dispose();}
});

test('短飞行记录只保留有界真实采样，清场不产生假投掷，退出恢复原采样回调',()=>{
 const f=fixture(),darts=new NativeProjectileSystem({scene:f.scene}),game={projectiles:darts,matchElapsed:0};let observed=0;const previous=()=>observed++;darts.onFlightSample=previous;
 const history=new NetworkShortFlights(game);try{
  for(let i=0;i<40;i++){
   const shot=darts.spawn({owner:f.owner,position:v(),direction:v(0,0,1)});for(let j=0;j<20;j++){shot.age=(j+1)/100;shot.position.z=j;darts.onFlightSample(shot,'update');}
   darts.remove(shot,'actor');
  }
  game.matchElapsed=.2;const flights=history.snapshot(f.actors);assert.equal(flights.length,32);assert.ok(flights.every(f=>f.points.length<=16));assert.equal(history.active.size,0);
  const clearing=darts.spawn({owner:f.owner,position:v(),direction:v(0,0,1)});clearing.age=.02;darts.clear();assert.equal(history.snapshot(f.actors).length,32);
  assert.ok(observed>40);history.dispose();assert.equal(darts.onFlightSample,previous);assert.equal(history.recent.length,0);
 }finally{history.dispose();darts.dispose();f.dispose();}
});

test('短飞行严格按主机时间开始结束，过期历史不在新客人画面中延迟重播',async()=>{
 const f=fixture();try{
  const flight={kind:'wheel',id:1,ownerId:'owner',weaponId:2,quaternion:[0,0,0,1],startTime:.04,endTime:.09,points:[{time:.04,position:[0,1,0],spin:0},{time:.065,position:[1,1,0],spin:1},{time:.09,position:[0,1,0],spin:2}]};
  f.motion.receive([],.1,[],0);f.motion.receive([],.1,[flight],.1);const sample=f.motion.samples.get('wheel:1');await sample.ready;
  f.motion.update(.02);assert.equal(sample.root.visible,false);assert.equal(f.owner.weaponModel.visible,true);
  f.motion.update(.045);assert.equal(sample.root.visible,true);assert.equal(f.owner.weaponModel.visible,false);assert.ok(Math.abs(sample.root.position.x-1)<1e-9);
  f.motion.update(.03);assert.equal(f.motion.samples.size,0);assert.equal(f.owner.weaponModel.visible,true);
  const late=new NetworkProjectileMotion(f.game,f.actors);late.receive([],.1,[flight],1);assert.equal(late.samples.size,0);late.dispose();
 }finally{f.dispose();}
});

test('远程命中反馈等投射物显示时钟到达后播放，退出不补播未到期反馈',()=>{
 const f=fixture(),played=[];f.game._playCombatFeedback=(event,local)=>played.push([event.id,local]);try{
  f.motion.receive([],.1,[],0);f.motion.receive([],.1,[],.1);f.motion.scheduleFeedback({id:1,time:.08},true);
  f.motion.update(.04);assert.deepEqual(played,[]);f.motion.update(.04);assert.deepEqual(played,[[1,true]]);
  f.motion.update(.2);assert.equal(played.length,1);
  f.motion.receive([],.1,[],.2);f.motion.scheduleFeedback({id:2,time:.19},false);f.motion.dispose();f.motion.update(1);assert.equal(played.length,1);
 }finally{f.dispose();}
});

test('碰撞回收翻滚由房主传输，客人在快照与已完成短路径中都能插值',async()=>{
 const f=fixture();try{
  f.motion.receive([state({kind:'wheel',weaponId:2,tumble:2,spin:4})],.1);
  const sample=f.motion.samples.get('wheel:1');await sample.ready;
  assert.equal(sample.visual.rotation.x,2);assert.equal(sample.visual.rotation.y,4);
  f.motion.receive([state({kind:'wheel',weaponId:2,tumble:4,spin:6})],.1);f.motion.update(.05);
  assert.equal(sample.visual.rotation.x,3);assert.equal(sample.visual.rotation.y,5);
  // Legacy snapshots omit tumble and return to a level wheel smoothly.
  f.motion.receive([state({kind:'wheel',weaponId:2,spin:7})],.1);f.motion.update(.1);assert.equal(sample.visual.rotation.x,0);
  f.motion.receive([],.1,[],0);
  const flight={kind:'wheel',id:2,ownerId:'owner',weaponId:2,quaternion:[0,0,0,1],startTime:.02,endTime:.1,
    points:[{time:.02,position:[0,1,0],spin:1,tumble:2},{time:.1,position:[1,1,0],spin:3,tumble:6}]};
  f.motion.receive([],.1,[flight],.1);const short=f.motion.samples.get('wheel:2');await short.ready;f.motion.update(.06);
  assert.ok(Math.abs(short.visual.rotation.x-4)<1e-9);assert.equal(f.hits,0);
 }finally{f.dispose();}
});

test('碰撞返程的快照和短路径记录保留相同翻滚角度',()=>{
 const f=fixture(),wheels=new NativeWheelSystem({scene:f.scene}),game={wheels,matchElapsed:0},recorder=new NetworkShortFlights(game);
 try{
  const shot=wheels.spawn({owner:f.owner,position:v(0,1.6,8),direction:v(0,0,-1),visual:new T.Group()});shot.collisionReturn=true;
  wheels.update(.05);game.matchElapsed=.05;const snapshot=networkProjectileSnapshot(game)[0];assert.equal(snapshot.tumble,.8);
  wheels.remove(shot,'caught');const paths=recorder.snapshot(f.actors);assert.equal(paths.length,1);assert.equal(paths[0].points.at(-1).tumble,snapshot.tumble);
 }finally{recorder.dispose();wheels.dispose();f.dispose();}
});

test('较长飞行结束时仅保留最近实际路径，不把整段长飞行迟到重播',()=>{
 const f=fixture(),darts=new NativeProjectileSystem({scene:f.scene}),game={projectiles:darts,matchElapsed:0},history=new NetworkShortFlights(game);try{
  const shot=darts.spawn({owner:f.owner,position:v(),direction:v(0,0,1)});
  for(let i=1;i<=200;i++){shot.age=i/100;shot.position.z=i/10;darts.onFlightSample(shot,'update');}
  darts.remove(shot,'actor');game.matchElapsed=2;const flights=history.snapshot(f.actors);assert.equal(flights.length,1);
  assert.ok(flights[0].startTime>=1.75);assert.equal(flights[0].endTime,2);assert.ok(flights[0].points.every(p=>p.position[2]>=17.5));
 }finally{history.dispose();darts.dispose();f.dispose();}
});

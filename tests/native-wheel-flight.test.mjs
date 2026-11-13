import test from 'node:test';
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import * as T from '../dist/vendor/three.module.js';
import {MeteorGame} from '../dist/engine.js';
import {NativeWheelSystem, NATIVE_WHEEL_PROFILE as P, selectNativeWheelTarget} from '../dist/native-projectiles.js';
const v=(x=0,y=0,z=0)=>new T.Vector3(x,y,z);
const actor=(id=1,x=0,z=0,y=0,team=1)=>{const root=new T.Group();root.position.set(x,y,z);return {id,root,teamMask:team,hp:1000,velocity:v(),weapon:'wheel',weaponModel:new T.Group()};};
function fixture(targets=[],colliders=[]){
  const owner=actor(),hits=[],walls=[],samples=[];
  const system=new NativeWheelSystem({getTargets:()=>targets,getColliders:()=>colliders,onActorHit:(shot,target,point)=>hits.push({shot,target,point,phase:shot.phase,time:system.time}),onWorldHit:(shot,hit)=>walls.push({shot,hit})});
  system.onFlightSample=(shot,event)=>samples.push({age:shot.age,event,position:shot.position.clone()});
  const spawn=(options={})=>system.spawn({owner,position:v(0,P.originHeight,0),direction:v(0,0,1),visual:new T.Group(),...options});
  return {owner,system,spawn,hits,walls,samples};
}
const step=(system,seconds)=>{for(let i=0;i<Math.round(seconds*60);i++)system.update(1/60);};
function wall(z){const mesh=new T.Mesh(new T.PlaneGeometry(100,100),new T.MeshBasicMaterial({side:T.DoubleSide}));mesh.position.z=z;mesh.updateMatrixWorld(true);return mesh;}

test('原目标选择优先最接近正前方而非最近，按48单位三维距离与前半球过滤',()=>{
  const owner=actor(),near=actor(2,2,4,0,2),aligned=actor(3,0,40,0,2),behind=actor(4,0,-1,0,2),far=actor(5,0,49,0,2),ally=actor(6,0,1),high=actor(7,0,1,49,2);
  assert.equal(selectNativeWheelTarget(owner,[near,aligned,behind,far,ally,high],v(0,0,1)),aligned);
  assert.equal(selectNativeWheelTarget(owner,[behind,far,ally,high],v(0,0,1)),null);
  aligned.dead=true;assert.equal(selectNativeWheelTarget(owner,[aligned,near],v(0,0,1)),near);
  const edge=actor(8,0,48,0,2);assert.equal(selectNativeWheelTarget(owner,[edge],v(0,0,1)),edge);
});
test('原队列记录目标和出手位置，射手走开后不把回收点拖走',()=>{
  const target=actor(2,0,30,0,2),f=fixture([target]),shot=f.spawn();
  assert.deepEqual(shot.waypoints.map(p=>p.position.toArray()),[[0,1.6,30],[0,1.6,0]]);
  f.owner.root.position.x=20;step(f.system,2);
  assert.equal(shot.removalReason,'caught');assert.ok(shot.position.distanceTo(v(0,1.6,0))<P.arrivalRadius);
  assert.equal(f.owner.weaponModel.visible,true);f.system.dispose();
});
test('无目标飞轮只含出手点，先按惯性抛出后转回，不走固定24单位',()=>{
  const f=fixture(),shot=f.spawn();assert.equal(shot.waypoints.length,1);step(f.system,1);
  assert.equal(shot.removalReason,'caught');assert.ok(Math.max(...f.samples.map(s=>s.position.z))<10);f.system.dispose();
});
test('目标预测30Hz更新，包含0.2秒水平和竖直速度，返程点固定',()=>{
  const target=actor(2,0,30,0,2),f=fixture([target]),shot=f.spawn();target.velocity.set(10,3,-5);target.root.position.x=2;
  f.system.update(1/60);assert.deepEqual(shot.waypoints[0].position.toArray(),[0,1.6,30]);
  f.system.update(1/60);assert.deepEqual(shot.waypoints[0].position.toArray(),[4,2.2,29]);
  assert.deepEqual(shot.waypoints[1].position.toArray(),[0,1.6,0]);
  target.root.position.x=5;f.system.update(1/60);assert.equal(shot.waypoints[0].position.x,4);
  f.system.update(1/60);assert.equal(shot.waypoints[0].position.x,7);f.system.dispose();
});
test('宿主将跳跃速度放在vy时，飞轮仍正确预测跳起目标高度',()=>{
  const target=actor(2,0,30,0,2),f=fixture([target]),shot=f.spawn();target.velocity.set(5,0,0);target.vy=12;
  f.system.update(1/30);assert.deepEqual(shot.waypoints[0].position.toArray(),[1,4,30]);f.system.dispose();
});
test('目标离场后不重定向到其他人，保留最后目标点继续完成路径',()=>{
  for(const state of ['disposed','scriptRemoved']){
    const target=actor(2,0,20,0,2),f=fixture([target]),shot=f.spawn();target[state]=true;target.root.position.set(99,99,99);step(f.system,2);
    assert.equal(shot.removalReason,'caught',state);assert.equal(f.hits.length,0);f.system.dispose();
  }
});
test('目标死亡后物理对象还在原角色表时，预测仍跟随该对象而不重新选人',()=>{
  const target=actor(2,0,30,0,2),f=fixture([target]),shot=f.spawn();target.dead=true;target.hp=0;target.root.position.x=3;
  f.system.update(1/30);assert.equal(shot.target,target);assert.equal(shot.waypoints[0].position.x,3);assert.equal(f.hits.length,0);f.system.dispose();
});
test('去程命中不折返或销毁，普通返程超过0.4秒可再次命中同一目标',()=>{
  const target=actor(2,0,30,0,2),crossing=actor(3,.5,10,0,2),f=fixture([crossing,target]),shot=f.spawn();step(f.system,2);
  const hits=f.hits.filter(h=>h.target===crossing);
  assert.equal(hits.length,2);assert.deepEqual(hits.map(h=>h.phase),['outbound','return']);
  assert.ok(hits[1].time-hits[0].time>.4);assert.equal(shot.removalReason,'caught');f.system.dispose();
});
test('命中间隔属于受害者，在多名射手飞轮之间共享，严格大于0.4秒',()=>{
  const target=actor(3,0,0,0,2),f=fixture([target]);
  const a=f.spawn({position:v(0,1.6,-10),target:null}),b=f.spawn({owner:actor(2),position:v(0,1.6,-10),target:null});
  f.system.noteActorContact(target);f.system.update(.4);assert.equal(f.hits.length,0);
  // Place both paths inside the same victim on the next update.
  for(const shot of [a,b]){shot.position.set(0,1.6,0);shot.velocity.set(0,0,0);shot.waypoints=[{kind:'target',position:v(0,1.6,20)}];}
  f.system.update(1/60);assert.equal(f.hits.length,1);f.system.dispose();
});
test('每步只命中原候选顺序中第一个有效盒体，命中后仍走完整步长',()=>{
  const farther=actor(2,0,9,0,2),nearer=actor(3,0,5,0,2),f=fixture([farther,nearer]),shot=f.spawn();
  f.system.update(.25);assert.equal(f.hits.length,1);assert.equal(f.hits[0].target,farther);
  assert.ok(Math.abs(shot.position.z-12)<1e-9);assert.equal(shot.removed,false);f.system.dispose();
});
test('飞轮使用原2.6倍横向盒体，竖直仍为36原单位，盒外不命中',()=>{
  for(const [x,y,expected] of [[P.bodyHalfWidth,2.88,true],[P.bodyHalfWidth+1e-6,1.6,false],[0,2.880001,false]]){
    const target=actor(2,x,10,0,2),f=fixture([target]);f.spawn({position:v(0,y,0),target:null});f.system.update(.25);
    assert.equal(f.hits.length,expected?1:0,`${x},${y}`);f.system.dispose();
  }
});
test('场景碰撞优先于同一步中的任何角色，退回旧位置停下并跳过目标点',()=>{
  const blocker=wall(10),target=actor(2,0,5,0,2),f=fixture([target],[blocker]),shot=f.spawn();
  // Keep a distant target waypoint so arrival does not consume it first.
  shot.waypoints[0].position.z=40;shot.nextPrediction=99;f.system.update(.25);
  assert.equal(f.hits.length,0);assert.equal(f.walls.length,1);assert.deepEqual(shot.position.toArray(),[0,1.6,0]);
  assert.equal(shot.velocity.length(),0);assert.equal(shot.waypoints.length,1);assert.equal(shot.collisionReturn,false);
  assert.equal(shot.phase,'return');f.system.dispose();blocker.geometry.dispose();blocker.material.dispose();
});
test('最后返程点遇墙启用原碰撞回收状态：不再撞墙和伤人，速度上限1.2倍并翻滚',()=>{
  const blocker=wall(5),target=actor(2,0,8,0,2),f=fixture([target],[blocker]);
  const shot=f.spawn({position:v(0,1.6,10),direction:v(0,0,-1),target:null});f.system.update(.15);
  assert.equal(shot.collisionReturn,true);assert.deepEqual(shot.position.toArray(),[0,1.6,10]);assert.equal(f.walls.length,1);
  let maxSpeed=0;for(let i=0;i<120&&!shot.removed;i++){f.system.update(1/60);maxSpeed=Math.max(maxSpeed,shot.velocity.length());}
  assert.equal(shot.removalReason,'caught');assert.equal(f.hits.length,0);assert.equal(f.walls.length,1);
  assert.ok(maxSpeed>48&&maxSpeed<=48*P.collisionReturnScale+1e-8);assert.ok(shot.visual.rotation.x>0);f.system.dispose();
});
test('路径点接近半径严格小于2.08，消耗最后点后下一步才结束飞行',()=>{
  const f=fixture(),shot=f.spawn({target:null});shot.velocity.set(0,0,0);shot.position.set(0,1.6,P.arrivalRadius);
  f.system.update(.1);assert.equal(shot.waypoints.length,1);
  shot.position.set(0,1.6,P.arrivalRadius-1e-7);shot.velocity.set(0,0,0);f.system.update(1/60);
  assert.equal(shot.waypoints.length,0);assert.equal(shot.removed,false);f.system.update(1/60);assert.equal(shot.removalReason,'caught');f.system.dispose();
});
test('暂停冻结年龄与命中间隔；原5秒严格超时，射手死亡不取消在途飞轮',()=>{
  const f=fixture(),shot=f.spawn();shot.waypoints[0].position.z=10000;f.owner.dead=true;
  f.system.pause();f.system.update(2);assert.equal(shot.age,0);assert.equal(f.system.time,0);f.system.pause(false);
  f.system.update(5);assert.equal(shot.removed,false);f.system.update(.001);assert.equal(shot.removalReason,'expired');f.system.dispose();
});
test('离场和清理释放持有武器，过期回调不会重复释放或伤害；共享模型不销毁',()=>{
  const f=fixture(),shot=f.spawn();assert.equal(f.spawn(),null);f.owner.disposed=true;f.system.update(1/60);
  assert.equal(shot.removalReason,'departure');assert.equal(f.system.size,0);assert.equal(f.owner.weaponModel.visible,true);
  const events=f.samples.length;f.system.remove(shot);assert.equal(f.samples.length,events);f.system.dispose();
});

test('原钟乳洞GMB实际碰撞三角形触发回退和碰撞回收，而非只验证测试平面',async()=>{
  const previousFetch=globalThis.fetch,previousLoad=T.TextureLoader.prototype.load,dist=new URL('../dist/',import.meta.url);
  globalThis.fetch=async input=>{try{return new Response(await readFile(new URL(input instanceof Request?input.url:input,dist)),{status:200});}catch{return new Response('',{status:404});}};
  T.TextureLoader.prototype.load=function(url,done){const texture=new T.Texture();done?.(texture);return texture;};
  const game=Object.create(MeteorGame.prototype);let map,system;
  try{
    game.manifest=JSON.parse(await readFile(new URL('assets/original/manifest.json',dist),'utf8'));game.raycaster=new T.Raycaster();game.collisionMaterial=new T.MeshBasicMaterial({side:T.DoubleSide});
    map=await game._readMap('sn01');assert.ok(map.colliders.length>0);
    const mesh=map.colliders.find(m=>m.geometry.getAttribute('position').count>=3),positions=mesh.geometry.getAttribute('position'),indices=mesh.geometry.index;
    const points=[0,1,2].map(i=>v().fromBufferAttribute(positions,indices?indices.getX(i):i).applyMatrix4(mesh.matrixWorld));
    const center=points.reduce((sum,p)=>sum.add(p),v()).multiplyScalar(1/3),normal=points[1].clone().sub(points[0]).cross(points[2].clone().sub(points[0])).normalize();
    assert.ok(normal.length()>.99);const from=center.clone().addScaledVector(normal,2),owner=actor();owner.root.position.copy(from).addScaledVector(normal,30);
    const hits=[];system=new NativeWheelSystem({getColliders:()=>map.colliders,onWorldHit:(shot,hit)=>hits.push(hit)});
    const shot=system.spawn({owner,position:from,direction:normal.clone().negate(),target:null});system.update(.1);
    assert.equal(hits.length,1);assert.deepEqual(shot.position.toArray(),from.toArray());assert.equal(shot.collisionReturn,true);assert.equal(shot.velocity.length(),0);
    assert.ok(map.colliders.includes(hits[0].object));
  }finally{system?.dispose();if(map)game._disposeMap(map);game.collisionMaterial?.dispose();globalThis.fetch=previousFetch;T.TextureLoader.prototype.load=previousLoad;}
});

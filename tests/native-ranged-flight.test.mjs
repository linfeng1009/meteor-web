import test from 'node:test';
import assert from 'node:assert/strict';
import * as T from '../dist/vendor/three.module.js';
import {MeteorGame} from '../dist/engine.js';
import {NativeProjectileSystem, NativeWheelSystem, NativeMusketSystem, NATIVE_DART_PROFILE as D, NATIVE_WHEEL_PROFILE as W, aimNativeDart} from '../dist/native-projectiles.js';
const v=(x=0,y=0,z=0)=>new T.Vector3(x,y,z);
const owner=()=>({id:1,root:new T.Group(),hp:100});
test('飞镖按原初速度和重力先平移再更新速度，自转使用转换后的轴',()=>{
  const system=new NativeProjectileSystem(),visual=new T.Group();
  const shot=system.spawn({owner:owner(),position:v(),direction:v(0,0,1),visual});
  const up=Math.fround(.13)*48;
  assert.equal(D.speed,48);assert.equal(D.gravity,4);assert.equal(D.spin,8);
  system.update(.1);assert.ok(Math.abs(shot.position.y-up*.1)<1e-10);
  assert.ok(Math.abs(shot.velocity.y-(up-.4))<1e-10);
  system.update(.1);assert.ok(Math.abs(shot.position.y-(up*.2-.04))<1e-10);
  assert.equal(visual.rotation.y,0);assert.equal(visual.rotation.z,-1.6);system.dispose();
});
test('锁定辅助补偿弹道，实际固定步长能到达不同高度和距离的目标',()=>{
  for(const destination of [v(0,1.35,10),v(20,4,30),v(-12,-2,25)]){
    const origin=v(0,2,0),system=new NativeProjectileSystem();
    const shot=system.spawn({owner:owner(),position:origin,direction:aimNativeDart(origin,destination)});
    let nearest=Infinity;
    for(let i=0;i<120;i++){system.update(1/60);nearest=Math.min(nearest,shot.position.distanceTo(destination));}
    assert.ok(nearest<.5,`${destination.toArray()}: ${nearest}`);system.dispose();
  }
});
test('飞轮以原速度和自转飞行，返程通过加速度转向而非瞬间反向',()=>{
  const system=new NativeWheelSystem(),visual=new T.Group(),f=owner();
  const shot=system.spawn({owner:f,position:v(0,1.35,0),direction:v(0,0,1),visual});
  system.update(.1);assert.ok(Math.abs(shot.position.z-4.8)<1e-9);assert.equal(visual.rotation.y,1.6);
  assert.equal(W.acceleration,640);assert.equal(W.arrivalRadius,2.08);
  shot.phase='return';const previous=shot.position.z;system.update(1/60);
  assert.ok(shot.position.z>previous,'先按旧速度前进');assert.ok(shot.velocity.z>0&&shot.velocity.z<48,'加速度逐步改变速度');
  for(let i=0;i<180&&system.size;i++)system.update(1/60);
  assert.equal(system.size,0);system.dispose();
});
test('火铳命中回调重入不重复发射，非法参数后仍可重试',()=>{
  const f=owner(),target={id:2,root:new T.Group(),hp:100};target.root.position.z=5;
  const state={serial:1,poseId:206,attacks:[{index:0}]},args={owner:f,state,position:v(0,2.4,0),direction:v(0,0,1)};
  let hits=0;const system=new NativeMusketSystem({getTargets:()=>[target],onActorHit(){hits++;assert.deepEqual(system.firePose(args),[]);}});
  assert.deepEqual(system.firePose({...args,direction:v()}),[]);
  assert.equal(system.firePose(args).length,1);assert.equal(hits,1);system.dispose();
});
test('火铳瞄准相机和射线从同一原高度出发，不依赖未加载的武器模型',()=>{
  const f=owner(),game=Object.create(MeteorGame.prototype),camera=new T.PerspectiveCamera();
  f.hero=true;f.musketAim=true;f.root.position.set(4,3,7);
  let fired;Object.assign(game,{hero:f,running:true,currentMap:{},camera,cameraTarget:v(),cameraAngle:.7,aimPitch:.2,
    muskets:{firePose(args){fired=args;return [];}},_soundDefinition(){}});
  game._fireNativeMusket(f,{poseId:206,serial:1,attacks:[{index:0}]});game._tickCamera(1/60);
  assert.deepEqual(fired.position.toArray(),[4,5.4,7]);assert.deepEqual(camera.position.toArray(),fired.position.toArray());
  assert.ok(camera.getWorldDirection(v()).distanceTo(fired.direction)<1e-9);
});

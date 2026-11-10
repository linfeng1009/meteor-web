import test from 'node:test';
import assert from 'node:assert/strict';
import * as THREE from '../dist/vendor/three.module.js';
import { FrameMeter, RenderScaleController } from '../dist/frame-meter.js';
import { StaticColliderIndex } from '../dist/collision-index.js';
import { MeteorGame } from '../dist/engine.js';

test('frame meter reports actual 30/60/144Hz cadence and bounded p95 samples', () => {
  for (const hz of [30,60,144]) {
    const meter=new FrameMeter(120);
    for(let frame=0;frame<=hz*4;frame++)meter.sample(frame*1000/hz,{cpu:4,world:2,camera:.5,render:1.5});
    assert.ok(Math.abs(meter.latest.fps-hz)<.001);
    assert.ok(Math.abs(meter.latest.p95Ms-1000/hz)<.001);
    assert.equal(meter.latest.cpuMs,4);assert.equal(meter.latest.cameraMs,.5);
    assert.ok(meter.count<=120);
  }
  const meter=new FrameMeter();let at=0;
  for(let i=0;i<100;i++)meter.sample(at+=i%10===0?40:16);
  assert.equal(meter.latest.p95Ms,40);
  meter.sample(at+10000);assert.equal(meter.latest,null);
  for(let i=1;i<=60;i++)meter.sample(at+10000+i*1000/60);
  assert.ok(Math.abs(meter.latest.fps-60)<.001,'background time must not pollute resumed FPS');
});

test('render budget changes only after sustained pressure and recovers slowly within bounds',()=>{
  const scale=new RenderScaleController(2),slow={fps:40,frameMs:25,p95Ms:30,cpuMs:5},fast={fps:60,frameMs:16.67,p95Ms:18,cpuMs:5};
  assert.equal(scale.update(slow),2);assert.equal(scale.update(slow),2);assert.equal(scale.update(slow),1.85);
  for(let i=0;i<11;i++)assert.equal(scale.update(fast),1.85);
  assert.equal(scale.update(fast),1.9);
  for(let i=0;i<100;i++)scale.update(slow);assert.equal(scale.ratio,.75);
  for(let i=0;i<500;i++)scale.update(fast);assert.equal(scale.ratio,2);
  for(const [stats,active] of [[slow,false],[{...slow,cpuMs:35},true],[{...slow,frameMs:1000},true]])for(let i=0;i<10;i++)assert.equal(scale.update(stats,active),2);
  scale.reset(.6);for(let i=0;i<30;i++)scale.update(slow);assert.equal(scale.ratio,.6);
});

test('collision index retains boundary/large/transformed meshes and live scene props',()=>{
  const meshes=Array.from({length:80},(_,i)=>{const mesh=new THREE.Mesh(new THREE.BoxGeometry(2,2,2));mesh.position.set(i*20-800,0,0);mesh.updateMatrixWorld(true);return mesh;});
  const floor=new THREE.Mesh(new THREE.BoxGeometry(10000,1,10000));floor.updateMatrixWorld(true);meshes.push(floor);
  const index=new StaticColliderIndex(meshes);
  assert.ok(index.near(0,0,2).includes(meshes[40]));assert.ok(index.near(0,0,2).includes(floor));
  assert.ok(index.near(0,0,2).length<meshes.length/4);
  const ray=new THREE.Raycaster(new THREE.Vector3(0,5,0),new THREE.Vector3(0,-1,0));
  assert.deepEqual(ray.intersectObjects(index.near(0,0,2),false).map(h=>h.distance),ray.intersectObjects(meshes,false).map(h=>h.distance));
  assert.equal(index.near(0,0,Infinity),meshes);
  const game=Object.create(MeteorGame.prototype);let active=true;
  game.currentMap={colliders:meshes,props:{getCollidersNear:()=>active?[floor]:[]}};
  assert.equal(game._collisionCandidates(0,0).filter(m=>m===floor).length,2);
  active=false;assert.equal(game._collisionCandidates(0,0).filter(m=>m===floor).length,1);
});

test('locked mouse orbit applies in the same rendered frame with one collision ray',()=>{
  const game=Object.create(MeteorGame.prototype);let rays=0;
  Object.assign(game,{hero:{root:new THREE.Group()},currentMap:{},running:true,paused:false,locked:null,mouseLook:{locked:true},camera:new THREE.PerspectiveCamera(),cameraTarget:new THREE.Vector3(0,1.65,0),cameraAngle:0,cameraPitch:.4,cameraDistance:8,_safeCameraPosition:(target,desired)=>{rays++;return desired.clone();}});
  game.camera.position.set(0,5,8);game.cameraAngle=Math.PI/2;game._tickCamera(1/144);
  assert.ok(Math.abs(game.camera.position.x-8)<1e-8);
  assert.ok(Math.abs(game.camera.position.z)<1e-8);assert.equal(rays,1);
  const position=game.hero.root.position.clone();assert.deepEqual(position.toArray(),[0,0,0]);
  game.mouseLook.locked=false;game.cameraAngle=0;rays=0;game._tickCamera(1/144);
  assert.equal(rays,2);assert.ok(game.camera.position.x>7,'unlocked cinematic camera keeps smoothing');
});

test('direct mouse camera retains real wall occlusion and resumes free look after a dead lock',()=>{
  const game=Object.create(MeteorGame.prototype),wall=new THREE.Mesh(new THREE.PlaneGeometry(20,20),new THREE.MeshBasicMaterial({side:THREE.DoubleSide}));
  wall.position.z=.5;wall.updateMatrixWorld(true);
  Object.assign(game,{hero:{root:new THREE.Group()},currentMap:{colliders:[wall]},running:true,paused:false,locked:{dead:true},mouseLook:{locked:true},camera:new THREE.PerspectiveCamera(),cameraTarget:new THREE.Vector3(0,1.65,0),cameraAngle:0,cameraPitch:.4,cameraDistance:8,raycaster:new THREE.Raycaster()});
  game._tickCamera(1/144);assert.ok(game.camera.position.z>0&&game.camera.position.z<.5);
  assert.equal(game.hero.root.visible,false);assert.deepEqual(game.hero.root.position.toArray(),[0,0,0]);
});

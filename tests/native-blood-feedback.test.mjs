import test from 'node:test';
import assert from 'node:assert/strict';
import * as T from '../dist/vendor/three.module.js';
import {NativeBloodFeedback,BLOOD_FEEDBACK_ADAPTER as PROFILE} from '../dist/native-blood-feedback.js';
const point=new T.Vector3(0,1.2,0),direction=new T.Vector3(0,0,1);

test('blood requires confirmed HP loss and never substitutes blood for a guard spark',()=>{
  const scene=new T.Scene(),blood=new NativeBloodFeedback(scene);
  for(const damage of [0,-1,undefined,NaN,Infinity])assert.equal(blood.emit({point,direction,damage}),0);
  assert.equal(blood.emit({point,direction,damage:20,guarded:true}),0);assert.equal(blood.mesh.visible,false);
  assert.equal(blood.emit({point,direction,damage:20}),PROFILE.count);assert.equal(blood.mesh.visible,true);assert.ok(blood.alpha.some(n=>n>0));blood.dispose();
});

test('blood spreads from the contact in world space, falls, fades and clears within its bounded lifetime',()=>{
  const scene=new T.Scene(),blood=new NativeBloodFeedback(scene),origin=point.clone();blood.emit({point,direction,damage:1});point.set(200,200,200);
  blood.update(.12,new T.PerspectiveCamera(),1000);assert.ok(blood.positions[2]>origin.z);assert.ok(blood.alpha[0]<.9);assert.ok([...blood.positions].every(Number.isFinite));
  blood.update(1);assert.equal(blood.mesh.visible,false);assert.equal(blood.particles.filter(Boolean).length,0);assert.ok(blood.alpha.every(a=>a===0));blood.dispose();point.copy(origin);
});

test('blood uses one bounded draw object under repeated multi-target hits and disposes its GPU resources',()=>{
  const scene=new T.Scene(),blood=new NativeBloodFeedback(scene);for(let i=0;i<200;i++)blood.emit({point,direction,damage:10});
  assert.equal(scene.children.length,1);assert.equal(blood.particles.length,PROFILE.capacity);assert.equal(blood.particles.filter(Boolean).length,PROFILE.capacity);
  let geometries=0,materials=0;blood.mesh.geometry.addEventListener('dispose',()=>geometries++);blood.mesh.material.addEventListener('dispose',()=>materials++);
  blood.clear();assert.equal(blood.mesh.visible,false);blood.dispose();blood.dispose();assert.equal(geometries,1);assert.equal(materials,1);assert.equal(scene.children.length,0);
});

test('blood rejects invalid positions and directions and keeps depth testing without depth writes',()=>{
  const blood=new NativeBloodFeedback(new T.Scene());assert.equal(blood.emit({point:new T.Vector3(NaN,0,0),damage:1}),0);
  assert.equal(blood.emit({point,direction:new T.Vector3(Infinity,0,0),damage:1}),0);blood.emit({point,damage:1});blood.update(NaN);blood.update(-1);
  assert.equal(blood.particles[0].age,0);assert.equal(blood.mesh.material.depthTest,true);assert.equal(blood.mesh.material.depthWrite,false);blood.dispose();
});

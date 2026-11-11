import test from 'node:test';
import assert from 'node:assert/strict';
import * as T from '../dist/vendor/three.module.js';
import {NativeBloodFeedback,bloodStyleForHit,bloodProfile,validBloodStyle,BLOOD_FEEDBACK_ADAPTER as PROFILE} from '../dist/native-blood-feedback.js';
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


test('actual force, knockdown and source reaction lift select blood levels and distinct shapes',()=>{
 assert.deepEqual(bloodStyleForHit({damage:24,weapon:'sword',force:5}),{kind:'slash',level:0});
 assert.deepEqual(bloodStyleForHit({damage:60,weapon:'spear',force:4}),{kind:'thrust',level:1});
 assert.deepEqual(bloodStyleForHit({damage:24,weapon:'hammer',force:10}),{kind:'impact',level:1});
 assert.deepEqual(bloodStyleForHit({damage:24,weapon:'blade',knockdown:true,lift:.8}),{kind:'launch',level:2});
 assert.equal(bloodStyleForHit({damage:24,weapon:'musket'}).kind,'shot');
 assert.deepEqual(bloodStyleForHit({damage:24,weapon:'spear',reactionPose:100}),{kind:'launch',level:1});
 const profiles=[0,1,2].map(level=>bloodProfile({kind:'slash',level}));
 assert.ok(profiles[0].count<profiles[1].count&&profiles[1].count<profiles[2].count);assert.ok(profiles[2].size>profiles[0].size);assert.ok(profiles[2].life>profiles[0].life);
});

test('blood uses visible world-sized streaks and different directional fans without per-hit GPU objects',()=>{
 const samples={};for(const kind of ['slash','thrust','impact','launch','shot']){
  const blood=new NativeBloodFeedback(new T.Scene());assert.equal(blood.emit({point,direction,damage:20,style:{kind,level:2}}),80);
  blood.update(.15);samples[kind]=blood.particles.map(p=>p?.velocity.toArray()).filter(Boolean);
  assert.equal(blood.mesh.geometry.instanceCount,PROFILE.capacity);assert.equal(blood.mesh.geometry.index.count,6);assert.ok(blood.sizes.some(size=>size>.3));
  assert.equal(blood.mesh.material.depthWrite,false);blood.dispose();
 }
 assert.notDeepEqual(samples.slash,samples.thrust);assert.notDeepEqual(samples.launch,samples.impact);
 assert.ok(samples.launch[10][1]>samples.slash[10][1]);
});

test('guest blood style reproduces host density and trajectory independent of its HP-loss placeholder',()=>{
 const host=new NativeBloodFeedback(new T.Scene()),guest=new NativeBloodFeedback(new T.Scene()),style=bloodStyleForHit({damage:150,weapon:'spear',force:10});
 host.emit({point,direction,damage:150,style});guest.emit({point,direction,damage:1,style});host.update(.2);guest.update(.2);
 assert.deepEqual(guest.positions,host.positions);assert.deepEqual(guest.sizes,host.sizes);assert.deepEqual(guest.alpha,host.alpha);
 for(const invalid of [null,{kind:'unknown',level:1},{kind:'slash',level:3},{kind:'slash',level:NaN}])assert.equal(validBloodStyle(invalid),false);
 host.dispose();guest.dispose();
});

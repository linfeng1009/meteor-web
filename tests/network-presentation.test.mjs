import test from 'node:test';
import assert from 'node:assert/strict';
import * as THREE from '../dist/vendor/three.module.js';
import {NetworkReplicaMotion} from '../dist/network-game.js';

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

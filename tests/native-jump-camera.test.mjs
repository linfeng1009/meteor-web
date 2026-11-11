import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { NativeCombatController, decodeNativeText, parsePos, parseAct } from '../dist/native-combat.js';
import {NATIVE_DASH_POSES,NATIVE_CROUCH_POSES,NATIVE_GROUND_MOVE_POSES,NATIVE_JUMP_POSES,nativeTraversalDirection} from '../dist/native-traversal.js';
import { createNativeCharacter, parseNativeSkin, parseNativeBones, parseNativeAnimation, parseNativePoses } from '../dist/native-character.js';

// Use the supplied native skin, skeleton and every original jump frame. A
// synthetic floor/wall isolates the browser physics/camera adapter from map
// occlusion; no skeleton coordinates, animation windows or jump poses are faked.
const assets = new URL('../dist/assets/original/characters/', import.meta.url);
const text = file => readFile(new URL(file, assets), 'utf8');
const arrayBuffer = async file => { const b = await readFile(new URL(file, assets)); return b.buffer.slice(b.byteOffset, b.byteOffset + b.byteLength); };
const [skin, bones, personal, common, poses, act] = await Promise.all([
  text('p0/p0.skc'), text('p0/p0.bnc'), arrayBuffer('p0/p0.amb'), arrayBuffer('common/character.amb'), text('p0/p0.pos'),
  readFile(new URL('../dist/assets/native/combat/character.act', import.meta.url))
]);
const data = { id: 0, skin: parseNativeSkin(skin), skeleton: parseNativeBones(bones), animations: [parseNativeAnimation(common), parseNativeAnimation(personal)], poses: parseNativePoses(poses) };
const combatData = { poses: parsePos(poses), actions: parseAct(decodeNativeText(act)) };
const v = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);

function wallFixture(side='front',height=2){
  const state=fixture(),{game,hero,colliders}=state;
  const wall=new THREE.Mesh(new THREE.PlaneGeometry(100,100),new THREE.MeshBasicMaterial({side:THREE.DoubleSide}));
  if(side==='front')wall.position.z=-.5;
  else{wall.rotation.y=Math.PI/2;wall.position.x=side==='right'?.5:-.5;}
  wall.position.y=height;wall.updateMatrixWorld(true);colliders.push(wall);
  hero.root.position.y=height;hero.root.rotation.y=Math.PI;hero.grounded=false;hero.vy=0;game.cameraAngle=0;game.mouseLook={locked:true};game.action('forward');
  return {...state,wall};
}

test('three native wall families enter, animate, kick away and follow their real POS air links',()=>{
  for(const [side,entry,exit,air] of [['front',161,157,158],['right',162,159,156],['left',163,160,154]]){
    const state=wallFixture(side);try{
      const {game,hero}=state;game._updateFighter(hero,1/60);
      assert.equal(hero.wallRun?.side,side);assert.equal(hero.combat.timeline.pose.id,entry);
      const before=hero.character.bones[15].quaternion.toArray();
      for(let i=0;i<12;i++)game._updateFighter(hero,1/60);
      assert.notDeepEqual(hero.character.bones[15].quaternion.toArray(),before,'use original animated bones');
      const start=hero.root.position.clone();game.action('jump');
      assert.equal(hero.wallRun,null);assert.equal(hero.combat.timeline.pose.id,exit);assert.equal(hero.nativeJump.pose.id,exit);
      const seen=new Set();let escaped;
      for(let i=0;i<100;i++){game._updateFighter(hero,1/60);if(i===14)escaped=hero.root.position.clone();seen.add(hero.combat.timeline.pose.id);assert.ok(hero.root.position.toArray().every(Number.isFinite));}
      assert.ok(seen.has(air));assert.ok(seen.has(180));assert.equal(hero.grounded,true);assert.equal(hero.wallEntries,0);
      if(side==='front')assert.ok(escaped.z>start.z+.5);
      else assert.ok((escaped.x-start.x)*(side==='right'?-1:1)>.5);
    }finally{state.dispose();}
  }
});

test('wall contact expires, cannot recharge in midair and resets only on landing',()=>{
  const state=wallFixture('front',30);try{
    const {game,hero}=state;for(let i=0;i<50;i++)game._updateFighter(hero,1/60);
    assert.equal(hero.wallRun,null);assert.equal(hero.wallEntries,1);assert.ok(hero.root.position.y<=32.6);assert.equal(hero.grounded,false);
    assert.equal(game._beginWallJump(hero),false);assert.equal(game._beginJump(hero),false);
    for(let i=0;i<180;i++)game._updateFighter(hero,1/60);
    assert.equal(hero.grounded,true);assert.equal(hero.wallEntries,0);
  }finally{state.dispose();}
});

test('wall traversal releases on lost geometry, direction release, hits and input blocking',()=>{
  for(const stop of ['geometry','release','hit','blocked','dead']){
    const state=wallFixture();try{
      const {game,hero,wall}=state;game._updateFighter(hero,1/60);assert.ok(hero.wallRun);
      if(stop==='geometry'){wall.position.z=-4;wall.updateMatrixWorld(true);}
      if(stop==='release')game.action('forward',false);
      if(stop==='hit')hero.combat.react(90);
      if(stop==='blocked')hero.scriptInputBlocked=true;
      if(stop==='dead')hero.dead=true;
      game._updateFighter(hero,1/60);
      // Dead actors no longer update movement; kill itself clears the state.
      if(stop!=='dead'){assert.equal(hero.wallRun,null,stop);assert.equal(game._beginWallJump(hero),false);}
      else assert.equal(game._beginWallJump(hero),false);
    }finally{state.dispose();}
  }
});

test('short ledges and floor surfaces cannot count as a wall, and a roof stops climbing',()=>{
  const state=wallFixture();try{
    const {game,hero,wall}=state;wall.scale.y=.004;wall.position.y=2.85;wall.updateMatrixWorld(true);
    game._updateFighter(hero,1/60);assert.equal(hero.wallRun,undefined);
    wall.scale.y=1;wall.position.y=2;wall.updateMatrixWorld(true);
    const roof=new THREE.Mesh(new THREE.PlaneGeometry(10,10),new THREE.MeshBasicMaterial({side:THREE.DoubleSide}));
    roof.rotation.x=Math.PI/2;roof.position.y=4.4;roof.updateMatrixWorld(true);state.colliders.push(roof);
    for(let i=0;i<15;i++){game._updateFighter(hero,1/60);assert.ok(hero.root.position.y+2.2<=4.4+.001);}
    assert.equal(hero.wallRun,null);
  }finally{state.dispose();}
});

test('remote wall traversal uses its own input, including the wall jump action',()=>{
  const state=wallFixture('left');try{
    const {game,hero}=state;hero.hero=false;hero.playerControl={keys:new Set(['forward']),lookLocked:true,cameraAngle:0,directionBuffer:[]};game.keys.clear();
    game._updateFighter(hero,1/60);assert.equal(hero.wallRun?.side,'left');
    game._actionFighter(hero,hero.playerControl,'jump',true);assert.equal(hero.combat.timeline.pose.id,160);assert.equal(hero.wallRun,null);
  }finally{state.dispose();}
});

test('wall exit impulse cannot pass through an opposite wall and yields to a hit',()=>{
  const state=wallFixture();try{
    const {game,hero}=state;game._updateFighter(hero,1/60);assert.equal(game._beginWallJump(hero),true);
    const opposite=new THREE.Mesh(new THREE.PlaneGeometry(100,100),new THREE.MeshBasicMaterial({side:THREE.DoubleSide}));opposite.position.z=1;opposite.updateMatrixWorld(true);state.colliders.push(opposite);
    for(let i=0;i<12;i++){game._updateFighter(hero,1/60);assert.ok(hero.root.position.z<.61,'the normal collision radius stops the kick');}
    assert.ok(hero.wallKick);hero.combat.react(90);game._updateFighter(hero,1/60);assert.equal(hero.wallKick,null);
  }finally{state.dispose();}
});

test('wall contact rechecks live prop colliders and pause, guard and script gates',()=>{
  const state=wallFixture('right');try{
    const {game,hero,wall}=state;state.colliders.pop();let present=true;
    game.currentMap.props={getCollidersNear:()=>present?[wall]:[]};
    game.paused=true;game._updateWallTraversal(hero,v(0,0,-1),1/60);assert.equal(hero.wallRun,undefined);game.paused=false;
    hero.guard=true;game._updateWallTraversal(hero,v(0,0,-1),1/60);assert.equal(hero.wallRun,undefined);hero.guard=false;
    hero.scriptInputBlocked=true;game._updateWallTraversal(hero,v(0,0,-1),1/60);assert.equal(hero.wallRun,undefined);hero.scriptInputBlocked=false;
    game._updateFighter(hero,1/60);assert.equal(hero.wallRun?.side,'right');
    present=false;game._updateFighter(hero,1/60);assert.equal(hero.wallRun,null);assert.equal(game._beginWallJump(hero),false);
    state.colliders.push(wall);
  }finally{state.dispose();}
});

function fixture({ locked = false, wall = false } = {}) {
  const game = Object.create(MeteorGame.prototype), character = createNativeCharacter(data, { inPlace: true, loadTextures: false });
  const floor = new THREE.Mesh(new THREE.PlaneGeometry(200, 200), new THREE.MeshBasicMaterial({ side: THREE.DoubleSide })); floor.rotation.x = -Math.PI / 2; floor.updateMatrixWorld(true);
  const colliders = [floor];
  if (wall) { const mesh = new THREE.Mesh(new THREE.PlaneGeometry(30, 20), new THREE.MeshBasicMaterial({ side: THREE.DoubleSide })); mesh.position.set(0, 5, 4); mesh.updateMatrixWorld(true); colliders.push(mesh); }
  const hero = { character, root: character.group, hero: true, id: 0, name: '孟星魂', weapon: 'dagger', velocity: v(), vy: 0, grounded: true, guard: false, dead: false, disposed: false, attackHits: new Set(), lastSerial: 0, heldPose: null };
  hero.root.position.y = .015; hero.combat = new NativeCombatController(combatData, { weapon: 'dagger', sampleRoot: character.sampleRoot });
  hero.combat.play(9, { force: true, loop: true });
  const opponent = { root: new THREE.Group(), dead: false, disposed: false }; opponent.root.position.set(0, .015, -8);
  Object.assign(game, { hero, locked: locked ? opponent : null, enemies: [opponent], keys: new Set(), directionBuffer: [], elapsed: 10, running: true, paused: false, mode: 'training',
    currentMap: { bounds: new THREE.Box3(v(-100, -1, -100), v(100, 20, 100)), colliders }, hostPhysics: { speed: 8, gravity: 34, jumpVelocity: 12, radius: .4, step: .55 },
    camera: new THREE.PerspectiveCamera(48, 16 / 9, .1, 1000), cameraTarget: v(0, 1.665, 0), cameraAngle: 0, cameraPitch: .4, cameraDistance: 8,
    cameraManualUntil: 0, raycaster: new THREE.Raycaster(), _unlockAudio() {} });
  game.camera.position.set(0, 5, 8);
  for (let i = 0; i < 90; i++) { game._updateFighter(hero, 1 / 60); game._tickCamera(1 / 60); }
  return { game, hero, colliders, dispose() { character.dispose(); for (const mesh of colliders) { mesh.geometry.dispose(); mesh.material.dispose(); } } };
}

function visualBounds(hero) {
  hero.root.updateMatrixWorld(true); hero.character.skeleton.update(); hero.character.mesh.computeBoundingBox();
  return hero.character.mesh.boundingBox.clone().applyMatrix4(hero.character.mesh.matrixWorld);
}
function projection(game, box) {
  game.camera.updateMatrixWorld(true);
  return box.getCenter(v()).project(game.camera);
}
function jump(fixture, visit) {
  const { game, hero } = fixture; game.action('jump'); assert.equal(hero.grounded, false);
  const frames = [];
  for (let i = 0; i < 120; i++) {
    game.elapsed += 1 / 60; game._updateFighter(hero, 1 / 60); game._tickCamera(1 / 60);
    const bounds = visualBounds(hero), screen = projection(game, bounds), base = hero.character.getAttachment('d_base').getWorldPosition(v());
    const frame = { i, bounds, screen, base, root: hero.root.position.clone(), camera: game.camera.position.clone(), pose: hero.combat.timeline.pose.id, grounded: hero.grounded };
    frames.push(frame); visit?.(frame);
  }
  return frames;
}

test('crouch walking plays each original directional loop and resumes crouch idle when stopped',()=>{
  for(const direction of ['forward','right','left','back']){
    const state=fixture();
    try{
      const {game,hero}=state;game.cameraAngle=0;hero.root.rotation.y=Math.PI;
      const start=hero.root.position.clone();game.action('crouch');game.action(direction);
      const samples=[];
      for(let i=0;i<40;i++){game._updateFighter(hero,1/60);samples.push({pose:hero.combat.timeline.pose.id,frame:hero.character.frame,bone:hero.character.bones[15].quaternion.toArray()});}
      assert.ok(samples.every(s=>s.pose===NATIVE_CROUCH_POSES[direction]),direction);
      assert.notDeepEqual(samples[5].bone,samples[30].bone,`${direction}: original bones must animate, not slide in pose10`);
      assert.ok(hero.root.position.distanceTo(start)>1);
      assert.ok(Math.abs(hero.root.rotation.y-Math.PI)<1e-6,'strafe animation keeps its facing instead of turning into a forward shuffle');
      game.action(direction,false);for(let i=0;i<60;i++)game._updateFighter(hero,1/60);
      assert.equal(hero.combat.timeline.pose.id,10);
      game.action('crouch',false);game._updateFighter(hero,1/60);assert.equal(hero.combat.timeline.pose.id,hero.combat.stance);
    }finally{state.dispose();}
  }
});

test('mouse-facing movement uses native side/back steps instead of playing forward run backwards',()=>{
  for(const [direction,poseId] of Object.entries(NATIVE_GROUND_MOVE_POSES)){
    const state=fixture();
    try{
      const {game,hero}=state;game.mouseLook={locked:true};game.cameraAngle=0;hero.root.rotation.y=Math.PI;
      game.action(direction);for(let i=0;i<30;i++)game._updateFighter(hero,1/60);
      assert.equal(hero.combat.timeline.pose.id,poseId,direction);assert.equal(hero.combat.busy,false);
      assert.ok(Math.abs(hero.root.rotation.y-Math.PI)<1e-6);assert.ok(hero.character.frame>combatData.poses.get(poseId).start);
      game.action(direction,false);for(let i=0;i<60;i++)game._updateFighter(hero,1/60);
      assert.equal(hero.combat.timeline.pose.id,hero.combat.stance);
    }finally{state.dispose();}
  }
});

test('remote directional stepping reads its own control and can yield directly to an attack',()=>{
  const state=fixture();
  try{
    const {game,hero}=state;hero.hero=false;hero.playerControl={keys:new Set(['right']),lookLocked:true,cameraAngle:0,directionBuffer:[]};
    game.keys.add('back');hero.weapon='sword';hero.combat.setWeapon('sword');hero.combat.play(6,{force:true});
    for(let i=0;i<20;i++)game._updateFighter(hero,1/60);assert.equal(hero.combat.timeline.pose.id,141);
    game._actionFighter(hero,hero.playerControl,'attack',true);assert.equal(hero.combat.attacking,true);assert.notEqual(hero.combat.timeline.pose.id,141);
  }finally{state.dispose();}
});

test('directional jumps preserve original takeoff and air families through landing',()=>{
  for(const direction of ['forward','right','left','back']){
    const state=fixture();
    try{
      const {game,hero}=state,profile=NATIVE_JUMP_POSES[direction];game.action(direction);
      game.action('jump');assert.equal(hero.combat.timeline.pose.id,profile.start);
      assert.equal(hero.nativeJump.pose.id,profile.start,'vertical scene track must use the selected native jump');
      const facing=hero.root.rotation.y,seen=new Set();
      for(let i=0;i<120;i++){
        game._updateFighter(hero,1/60);game._tickCamera(1/60);
        if(!hero.grounded&&!hero.combat.busy){seen.add(hero.combat.timeline.pose.id);assert.ok(Math.abs(hero.root.rotation.y-facing)<1e-6);}
        assert.ok(hero.root.position.toArray().every(Number.isFinite));
      }
      assert.ok(seen.has(profile.start),direction);assert.ok(seen.has(profile.air),direction);
      assert.equal(hero.grounded,true);assert.equal(hero.jumpSequence,null);
    }finally{state.dispose();}
  }
});

test('every directional jump follows its authored air-to-fall link without restarting the short air clip',()=>{
  for(const direction of ['forward','right','left','back']){
    const state=fixture();
    try{
      const {game,hero}=state,profile=NATIVE_JUMP_POSES[direction];game.action(direction);game.action('jump');
      const seen=[],airSerials=new Set(),fallFrames=[];
      for(let i=0;i<120;i++){
        game._updateFighter(hero,1/60);
        if(!hero.grounded){const id=hero.combat.timeline.pose.id;if(seen.at(-1)!==id)seen.push(id);
          if(id===profile.air){airSerials.add(hero.combat.serial);assert.equal(hero.combat.timeline.loop,false);}
          if(id===180){fallFrames.push(hero.character.frame);assert.equal(hero.combat.timeline.loop,true);}
        }
      }
      assert.deepEqual(seen,[profile.start,profile.air,180],direction);
      assert.equal(airSerials.size,1,'the host must not replay a POS-linked air entry');
      assert.ok(fallFrames.length>5);assert.ok(fallFrames.every(frame=>frame===combatData.poses.get(180).loopStart));
      assert.equal(hero.grounded,true);assert.notEqual(hero.combat.timeline.pose.id,180);
    }finally{state.dispose();}
  }
});

test('walking off a ledge enters the authored falling hold instead of replaying a jump',()=>{
  const state=fixture();
  try{
    const {game,hero}=state;hero.root.position.y=20;hero.grounded=false;hero.vy=0;hero.nativeJump=null;hero.jumpSequence=null;
    for(let i=0;i<20;i++){game._updateFighter(hero,1/60);assert.equal(hero.combat.timeline.pose.id,180);assert.equal(hero.nativeJump,null);}
    assert.ok(hero.root.position.y<20);assert.equal(hero.combat.timeline.frame,combatData.poses.get(180).loopStart);
    for(let i=0;i<120;i++)game._updateFighter(hero,1/60);
    assert.equal(hero.grounded,true);assert.notEqual(hero.combat.timeline.pose.id,180);
  }finally{state.dispose();}
});

test('falling locomotion yields to a native air attack and its ACT follow-up',()=>{
  const state=fixture();
  try{
    const {game,hero}=state;hero.weapon='sword';hero.combat.setWeapon('sword');hero.combat.play(6,{force:true});
    game.action('jump');for(let i=0;i<45;i++)game._updateFighter(hero,1/60);
    assert.equal(hero.grounded,false);assert.equal(hero.combat.timeline.pose.id,180);
    game.action('attack');assert.equal(hero.combat.attacking,true);assert.equal(hero.combat.timeline.pose.id,260);
    for(let i=0;i<6;i++){game._updateFighter(hero,1/60);assert.notEqual(hero.combat.timeline.pose.id,180);}
    game.action('attack');assert.ok(hero.combat.queued!=null||hero.combat.timeline.pose.id===261);
  }finally{state.dispose();}
});

test('jump direction follows the controlling player with forward/back priority and opposing keys cancel',()=>{
  assert.equal(nativeTraversalDirection(new Set(['back','right'])),'back');
  assert.equal(nativeTraversalDirection(new Set(['forward','back','left'])),'left');
  assert.equal(nativeTraversalDirection(new Set(['forward','back','left','right'])),null);
  const state=fixture();
  try{
    const {game,hero}=state;hero.hero=false;hero.playerControl={keys:new Set(['left']),cameraAngle:.8,directionBuffer:[]};
    game.keys.add('back');assert.equal(game._beginJump(hero),true);assert.equal(hero.combat.timeline.pose.id,155);
    hero.playerControl.keys.clear();hero.playerControl.keys.add('right');
    for(let i=0;i<36;i++)game._updateFighter(hero,1/60);
    assert.equal(hero.jumpSequence.start,155,'air steering must not restart another takeoff');
  }finally{state.dispose();}
});

test('four crouch double-tap rolls play original poses and consume their actual d_base displacement',()=>{
  for(const [direction,poseId,axis,sign] of [['forward',176,'z',-1],['right',177,'x',1],['left',178,'x',-1],['back',179,'z',1]]){
    const f=fixture();
    try{
      const {game,hero}=f;hero.combat.sampleRoot=hero.character.sampleSceneMotion;game.cameraAngle=0;game.action('crouch');game.action(direction);game.action(direction,false);game.elapsed+=.15;game.action(direction);
      assert.equal(hero.combat.timeline.pose.id,poseId);assert.equal(hero.combat.busy,true);assert.equal(hero.combat.attacking,false);assert.deepEqual(game.directionBuffer,[]);
      game.action(direction,false);const start=hero.root.position.clone(),pose=hero.combat.data.poses.get(poseId);
      const a=hero.character.sampleSceneMotion(pose.source,pose.start),b=hero.character.sampleSceneMotion(pose.source,pose.end);
      const expected=Math.hypot(b.x-a.x,b.y-a.y)*.08;
      for(let i=0;i<35;i++){game.elapsed+=1/60;game._updateFighter(hero,1/60);}
      const delta=hero.root.position.clone().sub(start);assert.ok(delta[axis]*sign>4,`${direction}: ${delta.toArray()}`);assert.ok(Math.abs(Math.hypot(delta.x,delta.z)-expected)<.02);
      assert.equal(hero.combat.busy,false);assert.equal(hero.combat.timeline.pose.id,10);assert.equal(hero.hp,undefined,'locomotion must not invent HP or immunity');
    }finally{f.dispose();}
  }
});

test('verified standing dashes use original scene trajectories for each weapon and direction',()=>{
  for(const [weapon,mapping] of Object.entries(NATIVE_DASH_POSES))for(const [direction,poseId] of Object.entries(mapping)){
    const f=fixture();try{
      const {game,hero}=f;hero.weapon=weapon;hero.combat.setWeapon(weapon);hero.combat.sampleRoot=hero.character.sampleSceneMotion;hero.combat.play(hero.combat.stance,{force:true});
      game.cameraAngle=0;game.action(direction);game.action(direction,false);game.elapsed+=.15;game.action(direction);
      assert.equal(hero.combat.timeline.pose.id,poseId);assert.equal(hero.combat.busy,true);assert.equal(hero.combat.attacking,false);assert.equal(game.directionBuffer.length,2,'dash must retain both taps for attack recognition');
      game.action(direction,false);const start=hero.root.position.clone(),pose=hero.combat.timeline.pose,a=hero.character.sampleSceneMotion(pose.source,pose.start),b=hero.character.sampleSceneMotion(pose.source,pose.end);
      const expected=Math.hypot(b.x-a.x,b.y-a.y)*.08;
      for(let i=0;i<45;i++){game.elapsed+=1/60;game._updateFighter(hero,1/60);}
      const delta=hero.root.position.clone().sub(start);assert.ok(expected>.5);assert.ok(Math.abs(Math.hypot(delta.x,delta.z)-expected)<.03,`${weapon}/${direction}: ${delta.toArray()} vs ${expected}`);
      assert.equal(hero.combat.busy,false);assert.equal(hero.hp,undefined);
    }finally{f.dispose();}
  }
});
test('standing dash can enter an attack while crouch roll cannot invent an ACT transition',()=>{
  const f=fixture();try{
    const {game,hero}=f;hero.weapon='sword';hero.combat.setWeapon('sword');hero.combat.play(6,{force:true});game.cameraAngle=0;
    game.action('back');game.action('back',false);game.elapsed+=.1;game.action('back');game.action('back',false);assert.equal(hero.combat.currentMove.kind,'dash');
    game.action('attack');assert.equal(hero.combat.currentMove?.kind==='dash',false);assert.equal(hero.combat._motionChain,false);assert.ok(hero.combat._attackChain);
    hero.combat.play(6,{force:true});game.keys.clear();game.action('crouch');assert.equal(game._beginRoll('forward',176),true);assert.equal(hero.combat.attack({poseId:262}),false);
  }finally{f.dispose();}
});
test('standing dash respects wall collision and airborne, guard and script gates, and a hit interrupts it',()=>{
  const f=fixture({wall:true});try{
    const {game,hero}=f;hero.weapon='sword';hero.combat.setWeapon('sword');hero.combat.sampleRoot=hero.character.sampleSceneMotion;hero.combat.play(6,{force:true});game.cameraAngle=0;
    assert.equal(game._beginDash('back',174),true);for(let i=0;i<45;i++){game.elapsed+=1/60;game._updateFighter(hero,1/60);}assert.ok(hero.root.position.z<3.7);
    for(const mutate of [()=>hero.grounded=false,()=>hero.dead=true,()=>hero.guard=true,()=>hero.scriptInputBlocked=true,()=>game.paused=true]){
      hero.grounded=true;hero.dead=false;hero.guard=false;hero.scriptInputBlocked=false;game.paused=false;mutate();assert.equal(game._beginDash('forward',165),false);
    }
    hero.grounded=true;hero.dead=false;hero.guard=false;hero.scriptInputBlocked=false;game.paused=false;assert.equal(game._beginDash('forward',165),true);assert.equal(hero.combat.react(90),true);assert.equal(hero.combat._motionChain,false);
  }finally{f.dispose();}
});

test('held direction repeats, air, dead, paused and script-blocked players cannot force a roll',()=>{
  const f=fixture();try{const {game,hero}=f;game.action('crouch');game.action('forward');game.elapsed+=.1;game.action('forward');assert.notEqual(hero.combat.timeline.pose.id,176);
    for(const mutate of [()=>hero.grounded=false,()=>hero.dead=true,()=>game.paused=true,()=>hero.scriptInputBlocked=true]){
      hero.grounded=true;hero.dead=false;game.paused=false;hero.scriptInputBlocked=false;mutate();assert.equal(game._beginRoll('forward',176),false);
    }
  }finally{f.dispose();}
});

test('native roll is stopped by actual wall geometry and remains interruptible by a hit',()=>{
  const f=fixture({wall:true});try{
    const {game,hero}=f;hero.combat.sampleRoot=hero.character.sampleSceneMotion;game.cameraAngle=0;game.action('crouch');assert.equal(game._beginRoll('back',179),true);
    for(let i=0;i<35;i++){game.elapsed+=1/60;game._updateFighter(hero,1/60);}
    assert.ok(hero.root.position.z<3.7&&hero.root.position.z>2,'roll must stop on the wall at z=4');
    assert.equal(game._beginRoll('forward',176),true);game._updateFighter(hero,.05);assert.equal(hero.combat.react(90),true);assert.equal(hero.combat.currentMove,null);assert.equal(hero.combat.reacting,true);assert.equal(hero.combat._motionChain,false);
  }finally{f.dispose();}
});

test('pausing clears a pending double tap and does not advance the native roll clip',()=>{
  const f=fixture();try{const {game,hero}=f;game._hud=()=>{};game.action('crouch');game.action('right');game.action('right',false);game.pause(true);assert.equal(game.traversalTap,null);game.pause(false);game.action('crouch');game.elapsed+=.1;game.action('right');assert.notEqual(hero.combat.timeline.pose.id,177);
  }finally{f.dispose();}
});

test('battle lock keeps tracking its opponent even after a previous free-camera override',()=>{
  const f=fixture({locked:true});
  try{f.game.cameraManualUntil=Infinity;f.game.cameraAngle=1;for(let i=0;i<90;i++)f.game._tickCamera(1/60);assert.ok(Math.abs(f.game.cameraAngle)<.05,'locked camera must not wait for the free-look timer');}
  finally{f.dispose();}
});

test('native in-place jump removes scene translation from d_base while preserving the authored skeleton pose', () => {
  const character = createNativeCharacter(data, { inPlace: true, loadTextures: false });
  const base = character.getAttachment('d_base'), originalParent = character.bones[0].parent;
  try {
    for (const id of [151, 152, 180]) for (let frame = data.poses[id].start; frame <= data.poses[id].end; frame++) {
      character.setPoseFrame(0, frame); const position = base.getWorldPosition(v());
      assert.ok(position.length() < .01, `pose ${id} frame ${frame}: scene dummy escaped the physics root by ${position.length().toFixed(3)}m`);
      assert.equal(character.bones[0].parent, originalParent);
      assert.ok(Math.abs(character.bones[0].position.z - character.sampleRoot(0, frame).z) < 1e-6, 'pelvis local height must remain authored');
    }
  } finally { character.dispose(); }
});

test('authored non-in-place jump remains available with its original d_base displacement', () => {
  const character = createNativeCharacter(data, { inPlace: false, loadTextures: false });
  try {
    character.setPoseFrame(0, 663);
    assert.ok(Math.abs(character.getAttachment('d_base').position.z - 72.97940063476562) < 1e-5);
    assert.ok(character.getAttachment('d_base').getWorldPosition(v()).y > 5.8);
  } finally { character.dispose(); }
});

test('normal L takeoff moves the collision root by the original d_base curve without adding it twice to the skin', () => {
  const state = fixture();
  try {
    const { game, hero } = state, pose = hero.combat.data.poses.get(151), start = hero.root.position.y;
    const origin = hero.character.sampleSceneMotion(pose.source, pose.start).z;
    game.action('jump');
    for (let index = 1; index <= 27; index++) {
      game._updateFighter(hero, 1/60);
      const expected = (hero.character.sampleSceneMotion(pose.source, pose.start + index/2).z - origin)*.08;
      assert.ok(Math.abs(hero.root.position.y - start - expected) < 1e-5);
      assert.ok(Math.abs(hero.character.getAttachment('d_base').getWorldPosition(v()).y - hero.root.position.y) < .01);
    }
    assert.ok(hero.root.position.y > 5.5, 'authored elevation must permit the sn09 central platform');
  } finally { state.dispose(); }
});

for (const locked of [false, true]) test(`the real L jump stays in view ${locked ? 'with an enemy locked' : 'on open ground'} and lands with the collider`, () => {
  const state = fixture({ locked });
  try {
    const frames = jump(state), airborne = frames.filter(f => !f.grounded), last = frames.at(-1);
    assert.ok(airborne.some(f => f.pose === 151) && airborne.some(f => f.pose === 152), 'exercise both original takeoff and airborne poses');
    assert.ok(Math.max(...airborne.map(f => f.root.y)) > 1.8, 'the collision root must really jump');
    for (const f of frames) {
      assert.ok(Math.abs(f.base.y - f.root.y) < .01, `frame ${f.i}: visual scene translation diverged from collider by ${(f.base.y - f.root.y).toFixed(3)}m`);
      assert.ok(f.screen.z > -1 && f.screen.z < 1 && Math.abs(f.screen.x) < .95 && Math.abs(f.screen.y) < .95, `frame ${f.i} pose ${f.pose}: rendered body center left view: ${f.screen.toArray()}`);
    }
    assert.equal(last.grounded, true); assert.ok(Math.abs(last.root.y - .015) < 1e-5); assert.equal(state.hero.vy, 0);
    assert.ok(last.bounds.min.y > -.15 && last.bounds.min.y < .2, 'landed native feet must meet the collision floor');
  } finally { state.dispose(); }
});

test('jump camera follows the native body without crossing a nearby wall', () => {
  const state = fixture({ wall: true });
  try {
    const frames = jump(state);
    for (const f of frames) {
      assert.ok(f.camera.z < 4, 'camera must stay on the player side of the wall');
      assert.ok(Math.abs(f.base.y - f.root.y) < .01, 'wall collision cannot be bypassed by moving only the camera to the displaced skin');
      assert.ok(Math.abs(f.screen.y) < 1, `frame ${f.i}: body escaped the clipped camera view: ${f.screen.toArray()}`);
    }
  } finally { state.dispose(); }
});


test('in-place correction keeps native dart hand attachments aligned with the same skin pose', () => {
  const inPlace = createNativeCharacter(data, { inPlace: true, loadTextures: false }), authored = createNativeCharacter(data, { inPlace: false, loadTextures: false });
  try {
    for (const id of [200, 202]) for (let frame = data.poses[id].start; frame <= data.poses[id].end; frame++) {
      inPlace.setPoseFrame(0, frame); authored.setPoseFrame(0, frame);
      const inPelvis = inPlace.bones[0].getWorldPosition(v()), authoredPelvis = authored.bones[0].getWorldPosition(v());
      for (const name of ['d_wpnR', 'd_wpnL']) {
        const fixedHand = inPlace.getAttachment(name).getWorldPosition(v()), rawHand = authored.getAttachment(name).getWorldPosition(v());
        assert.ok(fixedHand.sub(inPelvis).distanceTo(rawHand.sub(authoredPelvis)) < 1e-6, `pose ${id} frame ${frame}: scene correction changed ${name} relative to skin`);
      }
      assert.ok(inPlace.getAttachment('d_base').getWorldPosition(v()).length() < .01);
    }
  } finally { inPlace.dispose(); authored.dispose(); }
});

test('native attack 259 cannot leave the skin behind its collision root and raw per-frame override remains usable', () => {
  const character = createNativeCharacter(data, { inPlace: true, loadTextures: false });
  try {
    const pose = data.poses[259];
    for (let frame = pose.start; frame <= pose.end; frame++) {
      character.setPoseFrame(pose.source, frame);
      assert.ok(character.getAttachment('d_base').getWorldPosition(v()).length() < .01, `attack frame ${frame}: inherited scene displacement bypasses root collision`);
    }
    character.setPoseFrame(pose.source, pose.end, { rootMotion: true });
    assert.ok(Math.abs(character.getAttachment('d_base').position.y + 91.01268768310547) < 1e-5, 'raw authoring preview retains the original scene trajectory');
    character.setPoseFrame(pose.source, pose.end, { rootMotion: false });
    assert.ok(character.getAttachment('d_base').position.length() < .01, 'a frame override can explicitly return to collision-aligned playback');
  } finally { character.dispose(); }
});

test('vertical camera follow preserves its settled height over the collision root throughout a real jump', () => {
  const state = fixture();
  try {
    const targetOffset = state.game.cameraTarget.y - state.hero.root.position.y;
    const cameraOffset = state.game.camera.position.y - state.hero.root.position.y;
    jump(state, frame => {
      assert.ok(Math.abs(state.game.cameraTarget.y - frame.root.y - targetOffset) < .001, `frame ${frame.i}: look target lagged behind the jump root`);
      assert.ok(Math.abs(frame.camera.y - frame.root.y - cameraOffset) < .001, `frame ${frame.i}: vertical camera smoothing detached from the jumping player`);
    });
  } finally { state.dispose(); }
});

test('moving forward during the native jump keeps the rendered body on screen and lands while moving', () => {
  const state = fixture();
  try {
    const start = state.hero.root.position.clone(); state.game.action('forward');
    const frames = jump(state), last = frames.at(-1);
    assert.ok(last.root.distanceTo(start) > 10, 'the original actor must actually travel while airborne and after landing');
    for (const f of frames) assert.ok(Math.abs(f.screen.x) < .95 && Math.abs(f.screen.y) < .95 && f.screen.z < 1, `moving frame ${f.i}: body escaped view: ${f.screen.toArray()}`);
    assert.equal(last.grounded, true); assert.ok(Math.abs(last.root.y - .015) < 1e-5);
  } finally { state.dispose(); }
});

test('all twenty supplied characters share the scene dummy hierarchy used by the in-place adapter', async () => {
  for (let id = 0; id < 20; id++) {
    const skeleton = parseNativeBones(await text(`p${id}/p${id}.bnc`));
    const base = skeleton.dummies.filter(entry => entry.name === 'd_base');
    assert.equal(base.length, 1, `p${id} needs one unambiguous scene dummy`);
    assert.equal(base[0].parent, 'NULL', `p${id}: scene dummy must be top level`);
    assert.deepEqual(base[0].position, id === 19 ? [.308, -.265, 0] : [0, 0, 0], `p${id}: preserve the actual BNC scene origin, including p19's nonzero pivot`);
    assert.equal(skeleton.bones[0].parent, 'd_base', `p${id}: skin root must descend from scene dummy`);
  }
});

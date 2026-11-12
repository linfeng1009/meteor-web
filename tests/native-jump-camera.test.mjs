import {nativeStrideSpeed} from '../dist/native-movement-profile.js';
import {turnMouseCamera} from '../dist/mouse-look.js';
import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import {NetworkGame} from '../dist/network-game.js';
import {createPlayerControl} from '../dist/player-control.js';
import {nativeWallJumpVelocity,nativeAirWallJumpVelocity} from '../dist/native-wall-traversal.js';
import { NativeCombatController, decodeNativeText, parsePos, parseAct } from '../dist/native-combat.js';
import {NATIVE_AIR_PHYSICS,NATIVE_DASH_POSES,NATIVE_CROUCH_POSES,NATIVE_GROUND_MOVE_POSES,NATIVE_JUMP_POSES,nativeTraversalDirection,nativeAirPose,nativeActionMomentum} from '../dist/native-traversal.js';
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
  // Represent an existing jump older than.1s; walking off a ledge alone
  // does not grant the original actor+e4 wall-entry permission.
  hero.wallJumpReady=true;hero.wallJumpAge=.1;
  return {...state,wall};
}

test('three native wall families enter, animate, kick away and apply the source descent initializer',()=>{
  for(const [side,entry,exit,air] of [['front',161,157,158],['right',162,159,152],['left',163,160,152]]){
    const state=wallFixture(side,20);try{
      const {game,hero}=state;game._updateFighter(hero,1/60);
      assert.equal(hero.wallRun?.side,side);assert.equal(hero.combat.timeline.pose.id,entry);
      const before=hero.character.bones[15].quaternion.toArray();
      for(let i=0;i<12;i++)game._updateFighter(hero,1/60);
      assert.notDeepEqual(hero.character.bones[15].quaternion.toArray(),before,'use original animated bones');
      const start=hero.root.position.clone();game.action('jump');game.action('jump',false);
      assert.equal(hero.wallRun,null);assert.equal(hero.combat.timeline.pose.id,exit);assert.equal(hero.nativeJump,null);assert.equal(hero.jumpSequence.ballistic,true);
      const seen=new Set();let escaped;
      for(let i=0;i<100;i++){game._updateFighter(hero,1/60);if(i===14)escaped=hero.root.position.clone();seen.add(hero.combat.timeline.pose.id);assert.ok(hero.root.position.toArray().every(Number.isFinite));}
      assert.ok(seen.has(air));assert.ok(seen.has(180));assert.equal(hero.grounded,true);assert.equal(hero.wallEntries,0);
      if(side==='front')assert.ok(escaped.z>start.z+.5);
      else assert.ok((escaped.x-start.x)*(side==='right'?-1:1)>.5);
    }finally{state.dispose();}
  }
});

test('普通腾空可直接蹬墙，三向使用原157/159/160，小跳180与大跳260区别于走壁跳开',()=>{
  for(const [side,pose] of [['front',157],['right',159],['left',160]])for(const large of [false,true]){
    const state=wallFixture(side,20);try{
      const {game,hero}=state;game.action('forward',false);hero.wallJumpReady=false;
      assert.equal(hero.wallRun,undefined);assert.equal(game._beginAirWallJump(hero,{large}),true);
      assert.equal(hero.combat.timeline.pose.id,pose);assert.equal(hero.wallRun,null);assert.equal(hero.nativeJump,null);
      assert.ok(Math.abs(hero.vy-(large?20.8:14.4)/Math.SQRT2)<1e-5);
      assert.equal(hero.wallJumpReady,true);assert.equal(hero.wallJumpAge,0);
      for(let i=0;i<180;i++)game._updateFighter(hero,1/60);
      assert.equal(hero.grounded,true);assert.equal(hero.wallJumpReady,false);
    }finally{state.dispose();}
  }
});

test('普通空中蹬墙去掉入墙法向速度，但保留切向与下坠速度，空地不能凭空二段跳',()=>{
  const normal=v(0,0,1),result=nativeAirWallJumpVelocity(v(4,-20,-8),normal);
  assert.ok(Math.abs(result.x-4)<1e-6);assert.ok(Math.abs(result.y-(-20+14.4/Math.SQRT2))<1e-5);
  assert.ok(Math.abs(result.z-14.4/Math.SQRT2)<1e-5);assert.ok(result.y<0);
  const state=fixture();try{
    const {game,hero}=state;game._beginJump(hero);const serial=hero.combat.serial,vertical=hero.vy;
    game.action('jump');game.action('jump',false);assert.equal(hero.combat.serial,serial);assert.equal(hero.vy,vertical);
    assert.equal(game._beginAirWallJump(hero),false);assert.equal(hero.wallRun,null);
  }finally{state.dispose();}
});

test('普通腾空蹬墙的本地和远端大小跳仍使用各自的操作时钟，蹬墙后立即攻击保留新速度',()=>{
  for(const remote of [false,true])for(const large of [false,true]){
    const state=wallFixture('front',30);try{
      const {game,hero}=state;game.action('forward',false);hero.wallJumpReady=false;
      if(remote){hero.playerControl=createPlayerControl({lookLocked:true});hero.playerControl.inputTime=10;}
      const control=remote?hero.playerControl:game.localControl,begin=game._beginAirWallJump;let received;
      game._beginAirWallJump=function(actor,options){received=options.large;return begin.call(this,actor,options);};
      const act=active=>remote?game._actionFighter(hero,control,'jump',active):game.action('jump',active);
      act(true);
      if(remote){for(let i=0;i<10;i++)game._updateFighter(hero,1/60);assert.equal(received,undefined);control.inputTime=large?10.11:10.04;}
      else if(large)for(let i=0;i<7;i++)game._updateFighter(hero,1/60);
      act(false);assert.equal(received,large);assert.equal(hero.combat.timeline.pose.id,157);
      const incoming=hero.velocity.clone();assert.equal(game._beginAttack(hero),true);
      assert.ok(hero.actionMomentum.distanceTo(incoming)<1e-5);assert.equal(hero.wallKick,null);
    }finally{state.dispose();}
  }
});

test('接墙必须有未消费许可、上升速度、前进输入和0.1秒起跳年龄，蹬墙可恢复许可',()=>{
  for(const mode of ['no-permission','descending','too-early','no-forward']){
    const state=wallFixture('front',20);try{
      const {game,hero}=state;
      if(mode==='no-permission')hero.wallJumpReady=false;
      if(mode==='descending')hero.vy=-1;
      if(mode==='too-early')hero.wallJumpAge=0;
      if(mode==='no-forward'){game.action('forward',false);game.action('right');}
      game._updateFighter(hero,1/60);assert.equal(hero.wallRun,undefined,mode);
    }finally{state.dispose();}
  }
  const state=wallFixture('front',20);try{
    const {game,hero}=state;game._updateFighter(hero,1/60);assert.equal(hero.wallJumpReady,false);assert.equal(hero.wallEntries,1);
    game.action('forward',false);game._updateFighter(hero,1/60);game.action('forward');game._updateFighter(hero,1/60);
    assert.equal(hero.wallRun,null,'脱墙本身不恢复接墙许可');
    assert.equal(game._beginAirWallJump(hero),true);assert.equal(hero.wallJumpReady,true);
  }finally{state.dispose();}
  const chain=wallFixture('front',20);try{
    const {game,hero}=chain;game._updateFighter(hero,1/60);
    assert.equal(game._beginWallJump(hero,{large:true}),true);
    const opposite=new THREE.Mesh(new THREE.PlaneGeometry(100,100),new THREE.MeshBasicMaterial({side:THREE.DoubleSide}));
    opposite.position.set(0,20,.9);opposite.updateMatrixWorld(true);chain.colliders.push(opposite);
    for(let i=0;i<30&&!hero.wallRun;i++)game._updateFighter(hero,1/60);
    assert.equal(hero.wallRun?.side,'front');assert.equal(hero.wallEntries,2);assert.equal(hero.wallJumpReady,false);
  }finally{chain.dispose();}
});

test('蹬墙大小跳采用原法线加向上方向的初速度，并以物理高度对齐蒙皮',()=>{
  for(const side of ['front','right','left'])for(const large of [false,true]){
    const state=wallFixture(side,20);try{
      const {game,hero}=state;game._updateFighter(hero,1/60);
      const normal=hero.wallRun.planeNormal.clone(),speed=large?30:22.56,start=hero.root.position.y;
      assert.equal(game._beginWallJump(hero,{large}),true);
      assert.ok(Math.abs(hero.vy-speed/Math.SQRT2)<1e-5);
      assert.ok(Math.abs(hero.velocity.length()-speed/Math.SQRT2)<1e-5);
      assert.ok(hero.velocity.dot(normal)>0);assert.equal(hero.nativeJump,null);
      assert.equal(hero.jumpSequence.ballistic,true);
      let top=start;
      for(let i=0;i<120;i++){
        game._updateFighter(hero,1/60);top=Math.max(top,hero.root.position.y);
        assert.ok(Math.abs(hero.character.getAttachment('d_base').getWorldPosition(v()).y-hero.root.position.y)<.01);
      }
      assert.ok(top-start>(large?2.7:1.4)&&top-start<(large?3.3:1.9),`${side}/${large}: ${top-start}`);
      assert.equal(hero.grounded,true);
    }finally{state.dispose();}
  }
  for(const normal of [v(0,.2,Math.sqrt(.96)),v(0,-.2,Math.sqrt(.96))]){
    const result=nativeWallJumpVelocity(normal),expected=normal.clone().add(v(0,1,0)).normalize().multiplyScalar(22.56);
    assert.ok(v(result.x,result.y,result.z).distanceTo(expected)<1e-5,'保留真实三维法线，不能先抹平墙面斜度');
  }
});

test('本地和远端蹬墙短按小跳，长按大跳，并使用各自的操作时钟',()=>{
  for(const remote of [false,true])for(const large of [false,true]){
    const state=wallFixture('front',30);try{
      const {game,hero}=state;
      if(remote){hero.playerControl=createPlayerControl({lookLocked:true});hero.playerControl.keys.add('forward');hero.playerControl.inputTime=10;}
      const control=remote?hero.playerControl:game.localControl;
      game._updateFighter(hero,1/60);
      const begin=game._beginWallJump;let received;
      game._beginWallJump=function(actor,options){received=options.large;return begin.call(this,actor,options);};
      const act=(active)=>remote?game._actionFighter(hero,control,'jump',active):game.action('jump',active);
      act(true);
      if(remote){
        for(let i=0;i<15;i++)game._updateFighter(hero,1/60);
        assert.equal(received,undefined,'主机等待不能代替客人按住时长');
        control.inputTime=large?10.11:10.04;
      }else if(large){for(let i=0;i<7;i++)game._updateFighter(hero,1/60);}
      act(false);assert.equal(received,large);assert.equal(hero.wallRun,null);
    }finally{state.dispose();}
  }
});

test('走壁不能直接攻击或开始防御，脱墙后允许空中攻击',()=>{
  const state=wallFixture('front',30);try{
    const {game,hero}=state;game._updateFighter(hero,1/60);
    game.action('guard');assert.equal(hero.guard,false);
    assert.equal(game._beginAttack(hero),false);
    game._updateFighter(hero,1/60);assert.ok(hero.wallRun);assert.equal(hero.combat.timeline.pose.id,161);
    game.action('guard',false);game.action('forward',false);game._updateFighter(hero,1/60);
    assert.equal(hero.wallRun,null);assert.equal(hero.grounded,false);
    assert.equal(game._beginAttack(hero),true);assert.equal(hero.combat.attacking,true);
  }finally{state.dispose();}
});

test('空中按住防御不能开始格挡，落地后才进入防御',()=>{
  for(const remote of [false,true]){
    const state=fixture();try{
      const {game,hero}=state;
      if(remote)hero.playerControl=createPlayerControl();
      const act=(name,active=true)=>remote?game._actionFighter(hero,hero.playerControl,name,active):game.action(name,active);
      act('jump');act('jump',false);act('guard');assert.equal(hero.guard,false);
      let frames=0;
      do{game._updateFighter(hero,1/60);frames++;if(!hero.grounded)assert.equal(hero.guard,false);}while(!hero.grounded&&frames<120);
      assert.ok(frames>20&&frames<120);assert.equal(hero.grounded,true);
      game._updateFighter(hero,1/60);assert.equal(hero.guard,true);
      act('guard',false);assert.equal(hero.guard,false);
    }finally{state.dispose();}
  }
});

test('走壁继承入墙竖直速度，脱墙继续升空，达到原下降速度门限后进入152',()=>{
  for(const side of ['front','right','left'])for(const dt of [1/60,1/120]){
    const state=wallFixture(side,30);try{
      const {game,hero}=state;hero.vy=12;
      for(let i=0;i<Math.round(.5/dt);i++)game._updateFighter(hero,dt);
      assert.equal(hero.wallRun?.side,side);
      const terminal=-70.56*.1/1.2,expected=terminal+(12-terminal)*Math.exp(-1.2*.5);
      assert.ok(Math.abs(hero.vy-expected)<.15,`${side}/${dt}: ${hero.vy} vs ${expected}`);
      assert.ok(hero.root.position.y>33.6&&hero.root.position.y<33.9);
      const before=hero.root.position.y;game.action('forward',false);game._updateFighter(hero,dt);
      assert.equal(hero.wallRun,null);assert.ok(hero.vy>0);assert.ok(hero.root.position.y>before);
      assert.equal(hero.combat.timeline.pose.id,{front:161,right:162,left:163}[side]);
      for(let i=0;i<120&&hero.vy>=-3.2;i++)game._updateFighter(hero,dt);
      game._updateFighter(hero,dt);assert.equal(hero.combat.timeline.pose.id,152);assert.equal(hero.combat.timeline.loop,false);
      for(let i=0;i<300;i++)game._updateFighter(hero,dt);assert.equal(hero.grounded,true);
    }finally{state.dispose();}
  }
});

test('原走壁时限为1.8秒，没有上升动量时自然下滑，落地后重置接墙次数',()=>{
  const state=wallFixture('front',30);try{
    const {game,hero}=state;for(let i=0;i<60;i++)game._updateFighter(hero,1/60);
    assert.ok(hero.wallRun,'1秒时仍未超过原1.8秒时限');assert.ok(hero.vy<0);assert.ok(hero.root.position.y<30);
    for(let i=0;i<60;i++)game._updateFighter(hero,1/60);
    assert.equal(hero.wallRun,null);assert.equal(hero.wallEntries,1);
  }finally{state.dispose();}
});

test('wall contact expires without automatically renewing permission, and landing resets the state',()=>{
  const state=wallFixture('front',30);try{
    const {game,hero}=state;for(let i=0;i<120;i++)game._updateFighter(hero,1/60);
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
    hero.vy=10;
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
    game._actionFighter(hero,hero.playerControl,'jump',true);game._actionFighter(hero,hero.playerControl,'jump',false);assert.equal(hero.combat.timeline.pose.id,160);assert.equal(hero.wallRun,null);
  }finally{state.dispose();}
});

test('ceiling contact covers the body edge and an already flush head without penetrating',()=>{
  for(const [x,z,height] of [[.35,0,4.25],[.25,.25,4.25],[0,0,4.2]]){
    const state=wallFixture();try{
      const {game,hero}=state;hero.vy=10;
      const roof=new THREE.Mesh(new THREE.PlaneGeometry(.2,.2),new THREE.MeshBasicMaterial({side:THREE.DoubleSide}));
      roof.rotation.x=Math.PI/2;roof.position.set(x,height,z);roof.updateMatrixWorld(true);state.colliders.push(roof);
      for(let i=0;i<8;i++){game._updateFighter(hero,1/60);assert.ok(hero.root.position.y+2.2<=height+1e-6,`roof ${x}/${z}/${height}: ${hero.root.position.y}`);}
      assert.equal(hero.wallRun,null);assert.equal(hero.nativeJump,null);assert.equal(hero.jumpSequence?.air,152);assert.ok(hero.vy<=0);
    }finally{state.dispose();}
  }
});

test('nonuniformly scaled wall geometry uses the geometric normal for attachment',()=>{
  const state=wallFixture();try{
    const {game,hero,wall}=state;
    wall.geometry.rotateX(.5);wall.scale.y=4;wall.position.set(0,3.2,-.45);wall.updateMatrixWorld(true);
    game._updateFighter(hero,1/60);assert.equal(hero.wallRun?.side,'front');
    assert.ok(hero.wallRun.normal.z>.99);
    for(let i=0;i<5;i++)game._updateFighter(hero,1/60);
    assert.equal(hero.wallRun?.side,'front','plane continuity uses the 3D plane, not the horizontal kick direction');
    assert.equal(game._beginWallJump(hero),true);
  }finally{state.dispose();}
});

test('ordinary jumps cancel their takeoff sequence on ceiling contact and resume falling',()=>{
  const state=fixture();try{
    const {game,hero}=state;
    const roof=new THREE.Mesh(new THREE.PlaneGeometry(10,10),new THREE.MeshBasicMaterial({side:THREE.DoubleSide}));
    roof.rotation.x=Math.PI/2;roof.position.y=4.8;roof.updateMatrixWorld(true);state.colliders.push(roof);
    game.action('jump');game.action('jump',false);assert.equal(hero.grounded,false);let collided=false;
    for(let i=0;i<80;i++){
      game._updateFighter(hero,1/60);assert.ok(hero.root.position.y+2.2<=4.8+1e-6);
      if(!hero.grounded&&hero.jumpSequence===null){collided=true;assert.equal(hero.nativeJump,null);}
    }
    assert.equal(collided,true);assert.equal(hero.grounded,true);assert.equal(hero.vy,0);
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
    currentMap: { bounds: new THREE.Box3(v(-100, -1, -100), v(100, 20, 100)), colliders }, hostPhysics: { speed: 8, gravity: NATIVE_AIR_PHYSICS.gravity, jumpVelocity: NATIVE_AIR_PHYSICS.jumpVelocity, radius: .4, step: .55 },
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

test('原地鼠标转身播放站立和蹲姿左右原动画，不移动角色且连续输入不重启动作',()=>{
  for(const crouched of [false,true])for(const dx of [-8,8]){
    const state=fixture();try{
      const {game,hero}=state;game.enemies=[];game.locked=null;game.mouseLook={locked:true};
      if(crouched){game.action('crouch');game._updateFighter(hero,1/60);}
      const position=hero.root.position.clone(),pose=crouched?(dx>0?146:147):(dx>0?141:142);
      turnMouseCamera(game,dx,0);game._updateFighter(hero,1/60);
      assert.equal(hero.combat.timeline.pose.id,pose);const serial=hero.combat.serial,bones=hero.character.bones[15].quaternion.toArray();
      for(let i=0;i<8;i++){turnMouseCamera(game,dx,0);game._updateFighter(hero,1/60);}
      assert.equal(hero.combat.serial,serial);assert.notDeepEqual(hero.character.bones[15].quaternion.toArray(),bones);
      assert.ok(hero.root.position.distanceTo(position)<1e-6);
      for(let i=0;i<12;i++)game._updateFighter(hero,1/60);
      assert.equal(hero.combat.timeline.pose.id,pose,'0.2秒边界仍保留转身');
      game._updateFighter(hero,1/60);assert.equal(hero.combat.timeline.pose.id,crouched?10:hero.combat.stance);
    }finally{state.dispose();}
  }
});

test('转身阈值按原默认鼠标输入缩放，逐逻辑步合并输入且纵向输入不刷新转身',()=>{
  const state=fixture();try{
    const {game,hero}=state;game.enemies=[];game.locked=null;game.mouseLook={locked:true};
    for(const dx of [1,2,-1,-2]){turnMouseCamera(game,dx,0);game._updateFighter(hero,1/60);assert.equal(hero.combat.timeline.pose.id,hero.combat.stance);}
    turnMouseCamera(game,3,0);turnMouseCamera(game,-3,0);game._updateFighter(hero,1/60);assert.equal(hero.combat.timeline.pose.id,hero.combat.stance);
    turnMouseCamera(game,2,0);turnMouseCamera(game,2,0);game._updateFighter(hero,1/60);assert.equal(hero.combat.timeline.pose.id,141);
    for(let i=0;i<8;i++)game._updateFighter(hero,1/60);
    turnMouseCamera(game,-1,0);game._updateFighter(hero,1/60);assert.equal(hero.combat.timeline.pose.id,141,'小输入保留当前方向并刷新计时');
    for(let i=0;i<13;i++){turnMouseCamera(game,0,1);game._updateFighter(hero,1/60);}
    assert.equal(hero.combat.timeline.pose.id,hero.combat.stance);
  }finally{state.dispose();}
});

test('转身被移动、跳跃、攻击和格挡中断，忙碌期间鼠标输入不延迟重放',()=>{
  for(const action of ['forward','jump','attack','guard']){
    const state=fixture();try{
      const {game,hero}=state;game.enemies=[];game.locked=null;game.mouseLook={locked:true};
      turnMouseCamera(game,8,0);game._updateFighter(hero,1/60);assert.equal(hero.combat.timeline.pose.id,141);
      game.action(action);if(action==='jump')game.action(action,false);
      game._updateFighter(hero,1/60);assert.equal(hero.standingTurn,null,action);
      if(action==='attack'||action==='guard'){
        turnMouseCamera(game,50,0);game._updateFighter(hero,1/60);game.action(action,false);
        for(let i=0;i<180;i++)game._updateFighter(hero,1/60);
        assert.equal(hero.standingTurn,null);assert.equal(hero.combat.timeline.pose.id,hero.combat.stance);
      }
    }finally{state.dispose();}
  }
});
function projection(game, box) {
  game.camera.updateMatrixWorld(true);
  return box.getCenter(v()).project(game.camera);
}
function jump(fixture, visit) {
  const { game, hero } = fixture; game.action('jump');game.action('jump',false); assert.equal(hero.grounded, false);
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
      assert.ok(Math.abs(hero.root.position.distanceTo(start)-nativeStrideSpeed(0,NATIVE_CROUCH_POSES[direction])*40/60)<.03);
      assert.ok(Math.abs(hero.root.rotation.y-Math.PI)<1e-6,'strafe animation keeps its facing instead of turning into a forward shuffle');
      game.action(direction,false);for(let i=0;i<60;i++)game._updateFighter(hero,1/60);
      assert.equal(hero.combat.timeline.pose.id,10);
      game.action('crouch',false);game._updateFighter(hero,1/60);assert.equal(hero.combat.timeline.pose.id,hero.combat.stance);
    }finally{state.dispose();}
  }
});

test('NPC 蹲下决策播放原蹲姿并按步幅行走，格挡和受击仍优先',()=>{
  const state=fixture();try{
    const {game,hero}=state;hero.hero=false;hero.npcCombat={crouch:true,guard:false,advance:()=>false};
    hero.scriptControlled=true;hero.scriptControl={moveTarget:v(0,.015,-20),speedScale:1};
    game.hasScriptLineOfSight=()=>true;game._npcCombatAction=()=>{};
    for(let i=0;i<30;i++)game._updateFighter(hero,1/60);
    const start=hero.root.position.clone();for(let i=0;i<30;i++)game._updateFighter(hero,1/60);
    assert.equal(hero.combat.timeline.pose.id,NATIVE_CROUCH_POSES.forward);
    assert.ok(Math.abs(hero.root.position.distanceTo(start)-nativeStrideSpeed(0,NATIVE_CROUCH_POSES.forward)*.68*.5)<.03);
    hero.npcCombat.guard=true;game._updateFighter(hero,1/60);assert.equal(hero.combat.timeline.pose.id,15);
    hero.combat.react(103);game._updateFighter(hero,1/60);assert.equal(hero.combat.timeline.pose.id,103);
  }finally{state.dispose();}
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
      game.action('jump');game.action('jump',false);assert.equal(hero.combat.timeline.pose.id,profile.start);
      assert.equal(hero.jumpSequence.start,profile.start,'物理起跳保留选择的原方向动画');assert.equal(hero.nativeJump,null);
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

test('四向跳跃可随鼠标转向，不重启动画、不改变竖直速度，空中出招后停止自由转身',()=>{
  for(const [direction,locked] of ['forward','right','left','back'].flatMap(direction=>[[direction,false],[direction,true]])){
    const state=fixture();try{
      const {game,hero}=state;game.enemies=[];game.mouseLook={locked};game.action(direction);game._beginJump(hero,{large:true});
      const serial=hero.combat.serial,pose=hero.combat.timeline.pose.id,vertical=hero.vy,position=hero.root.position.clone();
      turnMouseCamera(game,60,0);assert.ok(Math.abs(game.cameraAngle+.3)<1e-9);
      assert.equal(hero.combat.serial,serial);assert.equal(hero.combat.timeline.pose.id,pose);assert.equal(hero.vy,vertical);assert.ok(hero.root.position.equals(position));
      game._updateFighter(hero,1/60);assert.ok(Math.abs(hero.root.rotation.y-(Math.PI-.3))<1e-9);
      game._updateFighter(hero,1/60);assert.ok(Math.abs(hero.root.rotation.y-(Math.PI-.3))<1e-9,'单次视角输入消费后也不能回弹到起跳方向');
      turnMouseCamera(game,40,0);assert.equal(game._beginAttack(hero),true);
      assert.ok(Math.abs(hero.root.rotation.y-(Math.PI-.5))<1e-9);const attackFacing=hero.root.rotation.y;
      turnMouseCamera(game,80,0);game._updateFighter(hero,1/60);assert.equal(hero.root.rotation.y,attackFacing);
    }finally{state.dispose();}
  }
});

test('腾空蹬离后用鼠标转身可在同次飞行中接上对面墙，走壁中不被鼠标直接扭转',()=>{
  const state=wallFixture('front',20);try{
    const {game,hero}=state;game.action('forward',false);assert.equal(game._beginAirWallJump(hero),true);
    const opposite=new THREE.Mesh(new THREE.PlaneGeometry(100,100),new THREE.MeshBasicMaterial({side:THREE.DoubleSide}));
    opposite.position.set(0,20,.9);opposite.updateMatrixWorld(true);state.colliders.push(opposite);
    turnMouseCamera(game,-Math.PI/.005,0);game.action('forward');
    for(let i=0;i<10&&!hero.wallRun;i++)game._updateFighter(hero,1/60);
    assert.equal(hero.wallRun?.side,'front');assert.equal(hero.wallEntries,1);const facing=hero.root.rotation.y;
    turnMouseCamera(game,20,0);game._updateFighter(hero,1/60);assert.ok(hero.wallRun);assert.equal(hero.root.rotation.y,facing);
  }finally{state.dispose();}
});

test('客人原地转身复用既有角度包与原动作，重复相同角度不会延长转身',()=>{
  for(const crouched of [false,true]){
    const state=fixture();try{
      const {game,hero}=state;game.enemies=[];hero.hero=false;hero.networkId='guest';hero.playerControl=createPlayerControl({lookLocked:true});
      if(crouched){hero.playerControl.keys.add('crouch');game._updateFighter(hero,1/60);}
      const session=Object.create(NetworkGame.prototype);Object.assign(session,{client:{host:true},active:true,game,actors:new Map([['guest',hero]]),controls:new Map([['guest',hero.playerControl]])});
      const input=angle=>session.inputs([{playerId:'guest',action:'look',angle,time:10,held:crouched?['crouch']:[]}]);
      input(-.04);game._updateFighter(hero,1/60);assert.equal(hero.combat.timeline.pose.id,crouched?146:141);
      for(let i=0;i<13;i++){input(-.04);game._updateFighter(hero,1/60);}
      assert.equal(hero.combat.timeline.pose.id,crouched?10:hero.combat.stance);
      input(.04);game._updateFighter(hero,1/60);assert.equal(hero.combat.timeline.pose.id,crouched?147:142);
    }finally{state.dispose();}
  }
});

test('客人同批转向和空中攻击在主机按顺序处理，不等下一个物理步才更新朝向',()=>{
  const state=fixture();try{
    const {game,hero}=state;game.enemies=[];hero.hero=false;hero.networkId='guest';hero.playerControl=createPlayerControl({lookLocked:true});
    game._beginJump(hero,{large:true});const position=hero.root.position.clone(),vertical=hero.vy;
    const session=Object.create(NetworkGame.prototype);Object.assign(session,{client:{host:true},active:true,game,actors:new Map([['guest',hero]]),controls:new Map([['guest',hero.playerControl]])});
    session.inputs([{playerId:'guest',action:'look',angle:.8,time:10,held:[]},{playerId:'guest',action:'attack',angle:.8,time:10.01,active:true}]);
    assert.ok(Math.abs(hero.root.rotation.y-(Math.PI+.8))<1e-9);assert.equal(hero.combat.attacking,true);
    assert.ok(hero.root.position.equals(position));assert.equal(hero.vy,vertical);
  }finally{state.dispose();}
});

test('自由防御时鼠标可转镜头但不扭转身体，松开防御后的逻辑步恢复跟随',()=>{
  const state=fixture();try{
    const {game,hero}=state;game.enemies=[];game.mouseLook={locked:true};hero.root.rotation.y=Math.PI;
    game.action('guard');game.action('forward');const position=hero.root.position.clone();
    turnMouseCamera(game,60,0);game._updateFighter(hero,1/60);
    assert.equal(hero.guard,true);assert.equal(hero.root.rotation.y,Math.PI);assert.ok(hero.root.position.equals(position));
    game.action('guard',false);game._updateFighter(hero,1/60);assert.ok(Math.abs(hero.root.rotation.y-(Math.PI-.3))<1e-9);
  }finally{state.dispose();}
});

test('every directional jump follows its authored air-to-fall link without restarting the short air clip',()=>{
  for(const direction of ['forward','right','left','back']){
    const state=fixture();
    try{
      const {game,hero}=state,profile=NATIVE_JUMP_POSES[direction];game.action(direction);game.action('jump');game.action('jump',false);
      const seen=[],airSerials=new Set(),fallFrames=[];
      for(let i=0;i<120;i++){
        game._updateFighter(hero,1/60);
        if(!hero.grounded){const id=hero.combat.timeline.pose.id;if(seen.at(-1)!==id)seen.push(id);
          if(id===profile.air){airSerials.add(hero.combat.serial);assert.equal(hero.combat.timeline.loop,false);}
          if(id===180){fallFrames.push(hero.character.frame);assert.equal(hero.combat.timeline.loop,true);}
        }
      }
      assert.deepEqual(seen.slice(0,2),[profile.start,profile.air],direction);
      assert.ok(seen.every(id=>[profile.start,profile.air,180].includes(id)));
      assert.equal(airSerials.size,1,'the host must not replay a POS-linked air entry');
      // The original linked air descent can reach the floor before falling hold.assert.ok(fallFrames.every(frame=>frame===combatData.poses.get(180).loopStart));
      assert.equal(hero.grounded,true);assert.notEqual(hero.combat.timeline.pose.id,180);
    }finally{state.dispose();}
  }
});

test('原下降初始化严格使用负40门限和方向映射，不重播已有空中片段',()=>{
  const mappings=[[151,152],[153,154],[155,156],[157,158],[159,152],[160,152],[161,152],[162,152],[163,152],[5,152]];
  for(const [current,next] of mappings){
    assert.equal(nativeAirPose(current,0),current);assert.equal(nativeAirPose(current,-3.2),current);
    assert.equal(nativeAirPose(current,-3.2001),next);
    const state=fixture();try{
      const {game,hero}=state;hero.root.position.y=20;hero.grounded=false;hero.vy=-4;
      hero.combat.play(current,{force:true});const serial=hero.combat.serial;
      game._updateFighter(hero,1/60);assert.equal(hero.combat.timeline.pose.id,next);
      assert.ok(hero.combat.serial>serial);const airSerial=hero.combat.serial;
      game._updateFighter(hero,1/60);assert.equal(hero.combat.timeline.pose.id,next);assert.equal(hero.combat.serial,airSerial);
    }finally{state.dispose();}
  }
  for(const current of [152,154,156,158,180])assert.equal(nativeAirPose(current,-100),current);
});

test('walking off a ledge waits for native downward speed then enters152 and follows its falling link',()=>{
  const state=fixture();
  try{
    const {game,hero}=state;hero.root.position.y=20;hero.grounded=false;hero.vy=0;hero.nativeJump=null;hero.jumpSequence=null;
    const initial=hero.combat.timeline.pose.id;
    for(let i=0;i<3;i++){game._updateFighter(hero,1/60);assert.equal(hero.combat.timeline.pose.id,initial);assert.equal(hero.nativeJump,null);}
    game._updateFighter(hero,1/60);assert.equal(hero.combat.timeline.pose.id,152);
    const serial=hero.combat.serial;
    for(let i=0;i<5;i++){game._updateFighter(hero,1/60);assert.equal(hero.combat.timeline.pose.id,152);assert.equal(hero.combat.serial,serial);}
    assert.ok(hero.root.position.y<20);
    for(let i=0;i<120;i++)game._updateFighter(hero,1/60);
    assert.equal(hero.grounded,true);assert.notEqual(hero.combat.timeline.pose.id,180);
  }finally{state.dispose();}
});

test('falling locomotion yields to a native air attack and its ACT follow-up',()=>{
  const state=fixture();
  try{
    const {game,hero}=state;hero.weapon='sword';hero.combat.setWeapon('sword');hero.combat.play(6,{force:true});
    game._beginJump(hero,{large:true});for(let i=0;i<45;i++)game._updateFighter(hero,1/60);
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

test('点按小跳、按住自动大跳共享原物理与方向姿态，松键不重复起跳',()=>{
  const results=[];
  for(const large of [false,true])for(const dt of [1/60,1/120]){
    const state=fixture();try{
      const {game,hero}=state;game.action('jump');assert.equal(hero.grounded,true);
      if(!large){for(let i=0;i<Math.floor(.05/dt);i++)game._updateFighter(hero,dt);assert.equal(hero.grounded,true);game.action('jump',false);assert.equal(hero.vy,22.56);}
      else {for(let i=0;i<Math.ceil(.12/dt);i++)game._updateFighter(hero,dt);assert.equal(hero.grounded,false);assert.ok(hero.vy>27);}
      const serial=hero.combat.serial;game.action('jump',false);assert.equal(hero.combat.serial,serial);
      let top=hero.root.position.y,elapsed=0;while(!hero.grounded&&elapsed<1.5){game._updateFighter(hero,dt);top=Math.max(top,hero.root.position.y);elapsed+=dt;}
      assert.equal(hero.grounded,true);assert.equal(hero.vy,0);assert.equal(game.jumpCharge,null);
      assert.ok(large?top>5.85&&top<6.4:top>3.3&&top<3.7,`${large}/${dt}: ${top}`);results.push({large,top});
      for(let i=0;i<30;i++)game._updateFighter(hero,dt);assert.equal(hero.grounded,true,'持续按住的自动起跳只执行一次');
    }finally{state.dispose();}
  }
  assert.ok(Math.abs(results[0].top-results[1].top)<.12);assert.ok(Math.abs(results[2].top-results[3].top)<.16);
});

test('跳跃充能在释放时读取方向，清空与暂停释放不触发意外小跳',()=>{
  const state=fixture();try{
    const {game,hero}=state;game.action('right');game.action('jump');game.action('right',false);game.action('left');game.action('jump',false);
    assert.equal(hero.combat.timeline.pose.id,155);for(let i=0;i<100;i++)game._updateFighter(hero,1/60);
    game.action('jump');assert.ok(game.jumpCharge);game.action('clear',false);game.action('jump',false);assert.equal(hero.grounded,true);
    game.action('jump');game.keyboard={reset(){game.action('jump',false);}};game.releaseInput({releaseMouse:false});assert.equal(hero.grounded,true);assert.equal(game.jumpCharge,null);
    game.action('jump');game.action('attack');game.action('jump',false);assert.equal(hero.grounded,true);assert.equal(game.jumpCharge,null);
  }finally{state.dispose();}
});

test('翻滚不吞掉此前按住的跳跃计时，忙碌期间松开则取消起跳',()=>{
  for(const release of [false,true]){
    const state=fixture();try{
      const {game,hero}=state;hero.combat.sampleRoot=hero.character.sampleSceneMotion;
      game.action('jump');game.action('crouch');assert.equal(game._beginRoll('forward',176),true);assert.ok(game.jumpCharge);
      if(release)game.action('jump',false);
      let jumped=false;for(let i=0;i<100;i++){game._updateFighter(hero,1/60);if(hero.jumpSequence?.ballistic){jumped=true;assert.ok(hero.vy>27);break;}}
      assert.equal(jumped,!release);assert.equal(game.jumpCharge,null);
    }finally{state.dispose();}
  }
});

test('联机跳跃按有序客户端时钟区分大小跳，主机延迟不放大小跳且清空可取消',()=>{
  for(const duration of [.04,.11]){
    const state=fixture();try{
      const {game,hero}=state;hero.hero=false;hero.playerControl=createPlayerControl();
      const session={client:{host:true},active:true,actors:new Map([['remote',hero]]),controls:new Map([['remote',hero.playerControl]]),game};
      const input=(action,active,time)=>NetworkGame.prototype.inputs.call(session,[{playerId:'remote',action,active,time,angle:0}]);
      input('jump',true,10);for(let i=0;i<30;i++)game._updateFighter(hero,1/60);assert.equal(hero.grounded,true,'没有新的客户端时钟时，轮询延迟不代表持续按住');
      input('jump',false,10+duration);assert.equal(hero.grounded,false);assert.equal(hero.vy,duration<.11?22.56:30);
      const serial=hero.combat.serial;input('jump',false,10+duration);assert.equal(hero.combat.serial,serial);
      for(let i=0;i<100;i++)game._updateFighter(hero,1/60);
      input('jump',true,20);input('clear',false,20.03);input('jump',false,20.04);assert.equal(hero.grounded,true);assert.equal(hero.playerControl.jumpCharge,null);
      input('jump',true,30);input('look',false,30.12);game._updateFighter(hero,1/60);assert.equal(hero.grounded,false);assert.ok(hero.vy>27);
    }finally{state.dispose();}
  }
});

test('火铳瞄准时仍能点按跳跃收枪，不把瞄准状态当作禁止起跳',()=>{
  const state=fixture();try{
    const {game,hero}=state;hero.weapon='musket';hero.combat.setWeapon('musket');hero.combat.play(2,{force:true});
    game.action('attack');assert.equal(hero.musketAim,true);game.action('jump');assert.equal(hero.grounded,true);
    game.action('jump',false);assert.equal(hero.grounded,false);assert.equal(hero.musketAim,false);assert.equal(hero.combat.timeline.pose.id,151);
  }finally{state.dispose();}
});

test('原重力控制离台自由下落，两个固定步长均正常落地并保持蒙皮对齐',()=>{
  for(const dt of [1/60,1/120]){
    const state=fixture();try{
      const {game,hero}=state;hero.weapon='sword';hero.combat.sampleRoot=hero.character.sampleSceneMotion;hero.combat.setWeapon('sword');hero.combat.play(6,{force:true});
      assert.equal(NATIVE_AIR_PHYSICS.gravity,70.56);assert.equal(NATIVE_AIR_PHYSICS.jumpVelocity,22.56);
      const floor=hero.root.position.y;game.action('jump');game.action('jump',false);assert.equal(hero.vy,22.56);
      // A fall has no casting/reaction d_base vertical override. Keep the real
      // native fall pose and ground collision, starting20m above that floor.
      hero.root.position.y=floor+20;hero.vy=0;hero.nativeJump=null;hero.jumpSequence=null;
      let elapsed=0;
      while(!hero.grounded&&elapsed<1){
        game._updateFighter(hero,dt);elapsed+=dt;
        if(elapsed===dt){assert.ok(Math.abs(hero.vy+70.56*dt)<.001);assert.ok(Math.abs(hero.root.position.y-(floor+20-70.56*dt*dt))<.0001);}
        assert.ok(Math.abs(hero.character.getAttachment('d_base').getWorldPosition(v()).y-hero.root.position.y)<.01);
      }
      // Free fall20m under source gravity takes sqrt(40/70.56)=.7529s.
      assert.ok(elapsed>.73&&elapsed<.78,`flight=${elapsed}`);
      assert.equal(hero.grounded,true);assert.equal(hero.vy,0);assert.ok(Math.abs(hero.root.position.y-floor)<1e-5);
    }finally{state.dispose();}
  }
});

test('普通跳跃使用原物理初速度，不再把动画 d_base 高度充当碰撞轨迹', () => {
  const state = fixture();
  try {
    const { game, hero } = state, pose = hero.combat.data.poses.get(151), start = hero.root.position.y;
    const origin = hero.character.sampleSceneMotion(pose.source, pose.start).z;
    game.action('jump');game.action('jump',false);
    for (let index = 1; index <= 27; index++) {
      game._updateFighter(hero, 1/60);
      assert.ok(Math.abs(hero.character.getAttachment('d_base').getWorldPosition(v()).y - hero.root.position.y) < .01);
    }
    const authored=(hero.character.sampleSceneMotion(pose.source,pose.start+13.5).z-origin)*.08;
    assert.ok(authored>5.3,'保留原动画位移数据，供攻击等独立动作使用');
    assert.ok(hero.root.position.y-start>2&&hero.root.position.y-start<3,'普通小跳已越过顶点，没有叠加原动画约5.5m高度');
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


test('连剑在原接招接受帧采样惯性，后续切换动作时不再重采样',()=>{
  const state=fixture();try{
    const {game,hero}=state;hero.weapon='sword';hero.combat.setWeapon('sword');hero.combat.play(6,{force:true});
    hero.combat.sampleRoot=(source,frame)=>hero.character.sampleSceneMotion(source,frame);
    const capture=game._captureActionMomentum,records=[];
    game._captureActionMomentum=function(actor,options){
      const before=actor.motionVelocity.clone();capture.call(this,actor,options);
      records.push({pose:actor.combat.timeline?.pose.id,frame:actor.combat.timeline?.frame,before,after:actor.actionMomentum.clone()});
    };
    assert.equal(game._beginAttack(hero),true);assert.equal(hero.combat.timeline.pose.id,262);records.length=0;
    assert.equal(game._beginAttack(hero),true);assert.equal(records.length,0);
    for(let i=0;i<100&&!records.length;i++)game._updateFighter(hero,1/120);
    assert.equal(records.length,1);assert.equal(records[0].pose,262);assert.equal(records[0].frame,9767);
    assert.ok(records[0].before.distanceTo(records[0].after)<1e-5);assert.equal(hero.combat.timeline.pose.id,262);
    for(let i=0;i<100&&hero.combat.timeline.pose.id===262;i++)game._updateFighter(hero,1/120);
    assert.equal(hero.combat.timeline.pose.id,263);assert.equal(records.length,1);
  }finally{state.dispose();}
});

test('跑动出招继承实际速度，地面与空中按原9和0.2阻尼衰减，碰撞清掉受阻分量',()=>{
  for(const grounded of [false,true]){
    const state=fixture();try{
      const {game,hero}=state;hero.grounded=grounded;hero.root.position.y=grounded?.015:20;
      game._move(hero,v(1,0,1).normalize(),8,1/60);
      const incoming=hero.motionVelocity.clone();assert.ok(incoming.length()>7.9);
      assert.equal(game._beginAttack(hero),true);assert.ok(hero.actionMomentum.distanceTo(incoming)<1e-5);
      const before=hero.root.position.clone(),factor=grounded?.85:1-.2/60;
      game._move(hero,v(),0,1/60);
      assert.ok(Math.abs(hero.actionMomentum.x-incoming.x*factor)<1e-5);
      assert.ok(Math.abs(hero.root.position.x-before.x-incoming.x*factor/60)<1e-6);
      const wall=new THREE.Mesh(new THREE.PlaneGeometry(100,100),new THREE.MeshBasicMaterial({side:THREE.DoubleSide}));
      wall.rotation.y=Math.PI/2;wall.position.set(hero.root.position.x+.41,hero.root.position.y,0);wall.updateMatrixWorld(true);state.colliders.push(wall);
      const blocked=hero.root.position.x;game._move(hero,v(),0,1/60);
      assert.equal(hero.root.position.x,blocked);assert.equal(hero.actionMomentum.x,0);assert.ok(hero.actionMomentum.z>0);
      assert.equal(hero.motionVelocity.x,0);
    }finally{state.dispose();}
  }
  assert.ok(Math.abs(nativeActionMomentum(8,1/60,true)-6.8)<1e-6);
  assert.ok(Math.abs(nativeActionMomentum(8,1/60,false)-7.9733333333)<1e-6);
});

test('忍刀出招只缩放继承的水平惯性，不缩放竖直起跳速度或重复处理早期连点',()=>{
  for(const weapon of ['dagger','ninja']){
    const state=fixture();try{
      const {game,hero}=state;hero.weapon=weapon;hero.combat.setWeapon(weapon);
      hero.root.position.y=20;hero.grounded=false;hero.vy=5;
      game._move(hero,v(1,0,0),8,1/60);const incoming=hero.motionVelocity.x,vertical=hero.vy;
      assert.equal(game._beginAttack(hero),true);
      assert.ok(Math.abs(hero.actionMomentum.x-incoming*(weapon==='ninja'?.67:1))<1e-5);assert.equal(hero.vy,vertical);
      const serial=hero.combat.serial,before=hero.actionMomentum.clone();
      game._beginAttack(hero);game._beginAttack(hero);
      assert.equal(hero.combat.serial,serial);assert.ok(hero.actionMomentum.distanceTo(before)<1e-8);
    }finally{state.dispose();}
  }
});

test('跑动闪身与蹲滚继承入招速度，原动作位移不会变成下一帧的第二份惯性',()=>{
  for(const crouched of [false,true]){
    const state=fixture();try{
      const {game,hero}=state;hero.weapon='sword';hero.combat.setWeapon('sword');hero.combat.play(6,{force:true});
      game._move(hero,v(1,0,0),8,1/60);if(crouched)game.action('crouch');
      const accepted=crouched?game._beginRoll('forward',176):game._beginDash('forward',165);
      assert.equal(accepted,true);assert.ok(Math.abs(hero.actionMomentum.x-8)<1e-6);
      const start=hero.root.position.x;game._move(hero,v(),0,1/60,v(1,0,0));
      assert.ok(Math.abs(hero.root.position.x-start-(1+6.8/60))<1e-6);
      game._move(hero,v(),0,1/60);assert.ok(Math.abs(hero.actionMomentum.x-5.78)<1e-5);
    }finally{state.dispose();}
  }
});

test('stride-calibrated ground movement stops on release and attack without inertial sliding',()=>{
 for(const [direction,pose] of Object.entries(NATIVE_GROUND_MOVE_POSES)){
  const state=fixture();try{const {game,hero}=state;game.mouseLook={locked:true};game.action(direction);const start=hero.root.position.clone();
   for(let i=0;i<60;i++)game._updateFighter(hero,1/60);
   assert.ok(Math.abs(hero.root.position.distanceTo(start)-nativeStrideSpeed(0,pose))<.03,direction);
   game.action(direction,false);const stopped=hero.root.position.clone();game._updateFighter(hero,1/60);assert.ok(hero.root.position.distanceTo(stopped)<1e-6);
   game.action('attack');game._updateFighter(hero,1/60);assert.equal(hero.velocity.length(),0);
  }finally{state.dispose();}
 }
});

test('键盘四向起跳保留身体朝向，显式新视角才在起跳前消费且不清除锁定',()=>{
  for(const direction of ['forward','right','left','back'])for(const look of [false,true]){
    const state=fixture();try{
      const {game,hero}=state;game.enemies=[];game.locked=null;game.cameraAngle=1.2;hero.root.rotation.y=-.7;
      game.action(direction);if(look)turnMouseCamera(game,20,0);
      const expected=look?game.cameraAngle+Math.PI:hero.root.rotation.y;
      game.action('jump');game.action('jump',false);
      assert.equal(hero.combat.timeline.pose.id,NATIVE_JUMP_POSES[direction].start);assert.equal(hero.root.rotation.y,expected);
      assert.equal(hero.jumpSequence.facing,expected);game._updateFighter(hero,1/60);assert.equal(hero.root.rotation.y,expected);
    }finally{state.dispose();}
  }
  const state=fixture({locked:true});try{
    const {game,hero}=state,target=game.locked;hero.root.rotation.y=.4;
    game.action('jump');game.action('jump',false);assert.equal(game.locked,target);assert.equal(hero.root.rotation.y,.4);
  }finally{state.dispose();}
});

test('四向小跳共享原初速度和重力，动画衔接不叠加第二条跳跃曲线',()=>{
 for(const direction of ['forward','right','left','back']){
  const state=fixture();try{const {game,hero}=state;game.action(direction);game.action('jump');game.action('jump',false);let ticks=0,top=0;
   for(;ticks<120;ticks++){game._updateFighter(hero,1/60);top=Math.max(top,hero.root.position.y);if(hero.grounded)break;}
   assert.ok(ticks>30&&ticks<45,`${direction}: ${ticks} ticks`);assert.ok(top>3.3&&top<3.7);assert.ok(hero.root.position.length()<10);
  }finally{state.dispose();}
 }
});

test('musket first attack raises original212, holds first-person aim, blocks translation and lowers for guard',()=>{
 const state=fixture();try{const {game,hero}=state;hero.weapon='musket';hero.combat.setWeapon('musket');hero.combat.play(2,{force:true});
  game.action('attack');assert.equal(hero.musketAim,true);assert.equal(hero.combat.timeline.pose.id,212);assert.equal(hero.combat.attacking,false);
  game.action('forward');const start=hero.root.position.clone();for(let i=0;i<70;i++)game._updateFighter(hero,1/60);assert.ok(hero.root.position.distanceTo(start)<1e-6);
  turnMouseCamera(game,40,-30);game._tickCamera(1/60);assert.equal(hero.root.visible,false);assert.equal(game.aimPitch,.09);assert.ok(game.camera.getWorldDirection(v()).y>0);
  game.action('forward',false);game.directionBuffer=[];game.action('attack');assert.equal(hero.combat.timeline.pose.id,206);
  game.action('guard');game._updateFighter(hero,1/60);assert.equal(hero.musketAim,false);assert.equal(hero.velocity.length(),0);
 }finally{state.dispose();}
});


test('changing character animation calibration does not grant a movement speed advantage',()=>{
 const state=fixture();try{const {game,hero}=state;hero.character.nativeCharacterId=13;game.action('forward');const start=hero.root.position.clone();for(let i=0;i<60;i++)game._updateFighter(hero,1/60);
 assert.ok(Math.abs(hero.root.position.distanceTo(start)-nativeStrideSpeed(0,144))<.03);assert.ok(Math.abs(hero.combat.timeline.playbackRate-nativeStrideSpeed(0,144)/nativeStrideSpeed(13,144))<1e-6);
 }finally{state.dispose();}
});

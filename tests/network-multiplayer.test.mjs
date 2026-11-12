import {NATIVE_WHEEL_PROFILE} from '../dist/native-projectiles.js';
import test from 'node:test';
import assert from 'node:assert/strict';
import {NetworkRooms} from '../network-server.mjs';
import {roomRules,matchResult} from '../dist/network-rules.js';
import {NetworkGame} from '../dist/network-game.js';
import {MeteorGame} from '../dist/engine.js';
import {createPlayerControl} from '../dist/player-control.js';
import * as T from '../dist/vendor/three.module.js';

function room(mode='leader'){
 const rooms=new NetworkRooms(),host=rooms.create('房主',{mode,maxPlayers:4}),players=[host,...['甲','乙','丙'].map(name=>rooms.join(host.room.code,name))];
 const call=(p,op,data={})=>rooms.request(host.room.code,p.token,op,{round:rooms.rooms.get(host.room.code)?.round||0,...data});
 const start=()=>{for(const p of players)call(p,'ready',{ready:true});call(host,'start');for(const p of players)call(p,'loaded');};
 const frame=(sequence=1)=>({sequence,time:1,players:players.map(p=>({id:p.playerId,position:[0,0,0],angle:0,hp:1000,maxHp:1000,rage:0,pose:6,source:0,frame:7400,serial:1,effectTime:0,kills:0,deaths:0}))});
 return {rooms,host,players,call,start,frame};
}
test('四人房间逐人准备载入，队伍合法后开局，每路输入独立确认与重试',()=>{
 const f=room('deathmatch'),{host,players,call}=f;assert.throws(()=>f.rooms.join(host.room.code,'第五人'),/满/);
 assert.throws(()=>call(host,'start'),/准备/);for(const p of players)call(p,'team',{team:1});for(const p of players)call(p,'ready',{ready:true});assert.throws(()=>call(host,'start'),/红蓝/);
 call(players[3],'team',{team:2});for(const p of players)call(p,'ready',{ready:true});call(host,'start');for(const p of players.slice(0,3))assert.equal(call(p,'loaded').room.phase,'loading');assert.equal(call(players[3],'loaded').room.phase,'playing');
 for(const p of players.slice(1))call(p,'sync',{input:[{action:'attack',active:true,sequence:1,angle:0}]});
 const first=call(host,'sync',{frame:f.frame()}).input;assert.equal(first.length,3);assert.equal(new Set(first.map(p=>p.playerId)).size,3);assert.deepEqual(call(host,'sync').input,first);
 call(host,'sync',{inputAck:{[players[1].playerId]:1}});assert.equal(call(host,'sync').input.length,2);
 assert.throws(()=>call(players[2],'sync',{frame:f.frame(2)}),/房主/);
});
test('跳跃按下与松开重试保持时间间隔，部分确认不会吞掉松开事件',()=>{
  const f=room();f.start();const {host,players,call}=f,guest=players[1];
  const input=[{action:'jump',active:true,sequence:1,angle:0,time:10},{action:'jump',active:false,sequence:2,angle:0,time:10.04}];
  call(guest,'sync',{input});const first=call(host,'sync').input;
  assert.deepEqual(first.map(event=>[event.action,event.active,event.sequence,event.time]),[['jump',true,1,10],['jump',false,2,10.04]]);
  call(guest,'sync',{input});assert.deepEqual(call(host,'sync').input,first);
  call(host,'sync',{inputAck:{[guest.playerId]:1}});const release=call(host,'sync').input;
  assert.equal(release.length,1);assert.equal(release[0].active,false);assert.equal(release[0].time,10.04);
  call(guest,'sync',{input:[input[1]]});assert.deepEqual(call(host,'sync').input,release);
  call(host,'sync',{inputAck:{[guest.playerId]:2}});assert.equal(call(host,'sync').input.length,0);
});

test('三人继续游戏时客人离场刷新名册，不吞旧队列，不接受幽灵帧',()=>{
 const f=room();f.start();const {host,players,call}=f;call(players[1],'leave');const stale=call(host,'sync',{frame:f.frame()});assert.equal(stale.room.phase,'playing');assert.equal(stale.room.players.length,3);assert.equal(f.rooms.rooms.get(host.room.code).frame,null);
 const frame=f.frame();frame.players=frame.players.filter(p=>p.id!==players[1].playerId);call(host,'sync',{frame});assert.equal(call(players[2],'sync').frame.players.length,3);
 assert.throws(()=>call(players[2],'sync',{frame}),/房主/);
});
test('盟主按击杀上限和时限结算，死斗按全灭结算，双灭与超时平局',()=>{
 const players=[{id:'a',team:1,kills:5,dead:false},{id:'b',team:2,kills:3,dead:false},{id:'c',team:1,kills:1,dead:true}];
 assert.deepEqual(matchResult(roomRules({scoreLimit:5}),players,10).winnerIds,['a']);assert.equal(matchResult(roomRules(),players,10),null);
 assert.deepEqual(matchResult(roomRules(),players,600).winnerIds,['a']);const rules=roomRules({mode:'deathmatch'});assert.equal(matchResult(rules,players,10),null);players[1].dead=true;assert.deepEqual(matchResult(rules,players,10).winnerIds,['a','c']);players[0].dead=true;assert.deepEqual(matchResult(rules,players,10).winnerIds,[]);
});
test('结算帧可重取且重开清空准备，旧局写入被拒绝',()=>{
 const f=room();f.start();const {host,players,call}=f,frame=f.frame();frame.result={reason:'score',winnerIds:[host.playerId]};assert.equal(call(host,'sync',{frame}).room.phase,'finished');assert.equal(call(players[1],'sync').frame.result.reason,'score');assert.equal(call(players[2],'sync').frame.result.reason,'score');
 assert.throws(()=>call(players[1],'rematch'),/不能/);assert.equal(call(host,'rematch').room.phase,'waiting');f.start();assert.throws(()=>call(players[1],'sync',{round:1,input:[]}),/对局/);assert.equal(call(players[2],'sync').frame,null);
});
function game(mode='leader'){
 const g=Object.create(MeteorGame.prototype),actors=Array.from({length:4},(_,i)=>({id:i,networkId:String(i),name:String(i),root:new T.Group(),team:mode==='deathmatch'?i%2+1:1<<i,hp:1000,dead:false,grounded:true,weapon:'sword',velocity:new T.Vector3(),combat:{busy:false,update(){return null;},play(){}},character:{dispose(){}}}));
 Object.assign(g,{hero:actors[0],enemies:actors.slice(1),running:true,paused:false,elapsed:0,matchElapsed:0,localControl:createPlayerControl(),_hud(){},_soundDefinition(){},_clearDroppedWeapons(){},_disposeNameplate(){},pause(v){this.paused=v;},_updateFighter(){},_updatePresentation(){},_stepWorld(dt){this.matchElapsed+=dt;},_kill(target){target.dead=true;target.respawn=3;},action(){},releaseInput(){}});actors[0].hero=true;
 const r={mode,players:actors.map((a,i)=>({id:a.networkId,name:a.name,team:i%2+1}))},session=new NetworkGame(g,{host:true,playerId:'0',send(){}},r);session.play();return {g,actors,session};
}
test('四名战斗玩家控制独立，第三人击杀不记给房主，环境死亡不乱记分',()=>{
 const {g,actors,session}=game();session.inputs([{playerId:'1',action:'forward',active:true,angle:1,time:1},{playerId:'2',action:'left',active:true,angle:2,time:2}]);assert.ok(session.controls.get('1').keys.has('forward'));assert.ok(session.controls.get('2').keys.has('left'));assert.equal(session.controls.get('3').keys.size,0);
 g._kill(actors[1],{attacker:actors[2]});assert.equal(session.scores.get('2').kills,1);assert.equal(session.scores.get('0').kills,0);g._kill(actors[1],{attacker:actors[2]});assert.equal(session.scores.get('2').kills,1);g._kill(actors[3],{awardKill:false});assert.equal(session.scores.get('2').kills,1);assert.equal(session.snapshot().players.length,4);session.dispose();
});
test('死斗队友近战不造成伤害，死亡不自动复活，清空敌队后冻结结算',()=>{
 const {g,actors,session}=game('deathmatch');assert.equal(MeteorGame.prototype._applyNativeHit.call(g,actors[0],actors[2],{}, {},new T.Vector3()),false);
 g._kill(actors[1],{attacker:actors[0]});assert.equal(actors[1].respawn,Infinity);g._stepWorld(1/60);assert.equal(session.result,null);g._kill(actors[3],{attacker:actors[2]});g._stepWorld(1/60);assert.equal(session.result.winnerTeam,1);assert.deepEqual(session.result.winnerIds,['0','2']);const time=g.matchElapsed;g._stepWorld(1);assert.equal(g.matchElapsed,time);session.dispose();
});

test('投射物保存的攻击者快照按角色身份正确记分',()=>{
 const {g,actors,session}=game();const projectileAttacker={root:actors[2].root,team:actors[2].team};g._kill(actors[1],{attacker:projectileAttacker});assert.equal(session.scores.get('2').kills,1);assert.equal(session.scores.get('0').kills,0);
 const shooter=actors[2],chosen=actors[3],hand=new T.Group();shooter.root.add(hand);hand.position.y=1.35;shooter.root.position.set(0,0,0);chosen.root.position.set(5,0,0);actors[0].root.position.set(0,0,5);
 shooter.weapon='dart';shooter.attackHits=new Set();shooter.character.getAttachment=()=>hand;shooter.weaponModel=new T.Mesh(new T.BoxGeometry(.1,.1,.1),new T.MeshBasicMaterial());session.controls.get(shooter.networkId).locked=chosen;
 let launched;g.projectiles={spawn(shot){launched=shot;}};g._launchNativeProjectiles(shooter,{poseId:200,serial:1,pose:{raw:{fields:{effectid:'pos200'}}},attacks:[{index:0}]});assert.ok(launched.direction.x>.99);assert.ok(Math.abs(launched.direction.z)<.01,'remote dart must aim at its chosen rival, not the host');
 let wheel;g.wheels={hasOwner:()=>false,spawn(shot){wheel=shot;return shot;}};shooter.weapon='wheel';g._launchNativeWheel(shooter,{poseId:NATIVE_WHEEL_PROFILE.poseIds[0],serial:2,pose:{raw:{fields:{effectid:'pos218'}}},attacks:[{index:0}]});assert.ok(wheel.direction.x>.99);assert.ok(Math.abs(wheel.direction.z)<.01);
 shooter.weaponModel.geometry.dispose();shooter.weaponModel.material.dispose();session.dispose();
});

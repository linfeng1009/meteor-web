import test from 'node:test';import assert from 'node:assert/strict';import {NetworkRooms,createNetworkServer} from '../network-server.mjs';import {roomRules} from '../dist/network-rules.js';import {networkSpawns} from '../dist/network-spawns.js';import * as T from '../dist/vendor/three.module.js';
test('房间允许2至16人，拒绝超限、分数及小数容量',()=>{assert.equal(roomRules().maxPlayers,16);for(let i=2;i<=16;i++)assert.equal(roomRules({maxPlayers:i}).maxPlayers,i);for(const maxPlayers of [1,17,3.5,NaN,'16'])assert.throws(()=>roomRules({maxPlayers}));});
test('16个身份完整准备载入、15路输入重取确认、锁定状态同步与队伍分配',()=>{
 const rooms=new NetworkRooms(),host=rooms.create('房主',{mode:'deathmatch'}),players=[host,...Array.from({length:15},(_,i)=>rooms.join(host.room.code,'同道'+i))],call=(p,op,data={})=>rooms.request(host.room.code,p.token,op,{round:1,...data});
 assert.throws(()=>rooms.join(host.room.code,'第17人'),/满/);assert.equal(players.at(-1).room.players.filter(p=>p.team===1).length,8);
 for(const p of players)call(p,'ready',{ready:true});call(host,'start');for(const p of players)call(p,'loaded');
 for(const p of players.slice(1))call(p,'sync',{input:[{action:'attack',active:true,angle:0,sequence:1}]});const first=call(host,'sync').input;assert.equal(first.length,15);assert.deepEqual(call(host,'sync').input,first);
 const frame={sequence:1,time:1,players:players.map((p,i)=>({id:p.playerId,lockTargetId:players[(i+1)%16].playerId,autoLockEnabled:true,position:[i*2,0,0],angle:0,hp:1000,maxHp:1000,rage:0,pose:6,source:0,frame:7400,serial:1,effectTime:0}))};
 call(host,'sync',{frame,inputAck:Object.fromEntries(players.slice(1).map(p=>[p.playerId,1]))});assert.equal(call(host,'sync').input.length,0);for(const p of players.slice(1))assert.equal(call(p,'sync').frame.players.length,16);
 assert.throws(()=>call(host,'sync',{frame:{...frame,sequence:2,players:frame.players.map((p,i)=>i? p:{...p,lockTargetId:'missing'})}}),/无效/);
});
test('原版出生点不足时使用有地面、无阻隔且互不重叠的16个出生位置',()=>{
 const game={currentMap:{spawns:[{position:new T.Vector3(0,0,0)}],points:[]},_ground:(x,z)=>({point:new T.Vector3(x,0,z)}),_horizontalBlocked:()=>false};const points=networkSpawns(game,16);assert.equal(points.length,16);assert.equal(new Set(points.map(p=>p.position.toArray().join(','))).size,16);for(const a of points)for(const b of points)if(a!==b)assert.ok(a.position.distanceTo(b.position)>=1.5);game._ground=()=>null;assert.throws(()=>networkSpawns(game,16),/安全出生点/);
});
test('16人携带道具状态的有效大帧可经HTTP传输，不被旧32KB上限截断',async()=>{
 const rooms=new NetworkRooms(),server=createNetworkServer({rooms});await new Promise(r=>server.listen(0,'127.0.0.1',r));const base=`http://127.0.0.1:${server.address().port}`;
 try{const post=async(path,data,token)=>{const r=await fetch(base+path,{method:'POST',headers:{'Content-Type':'application/json',...(token?{Authorization:'Bearer '+token}:{})},body:JSON.stringify(data)});return {status:r.status,body:await r.json()};},host=(await post('/api/rooms/create',{name:'主机'})).body,players=[host];
 for(let i=1;i<16;i++)players.push((await post('/api/rooms/join',{code:host.room.code,name:'同道'+i})).body);const cmd=(p,op,data={})=>post(`/api/rooms/${host.room.code}/${op}`,{round:1,...data},p.token);for(const p of players)await cmd(p,'ready',{ready:true});await cmd(host,'start');for(const p of players)await cmd(p,'loaded');
 const frame={sequence:1,time:1,players:players.map(p=>({id:p.playerId,position:[0,0,0],angle:0,hp:1000,maxHp:1000,rage:0,pose:6,source:0,frame:7400,serial:1,effectTime:0,statuses:Array.from({length:32},(_,id)=>({id,name:'中毒效果',statKey:1,remaining:10,value:1,period:1}))}))};assert.ok(JSON.stringify(frame).length>32000);assert.equal((await cmd(host,'sync',{frame})).status,200);assert.equal((await cmd(players[15],'sync')).body.frame.players.length,16);
 }finally{await new Promise(r=>server.close(r));}
});

import {NetworkGame} from '../dist/network-game.js';
test('16人混战只显示附近三人及锁定目标姓名牌，退出恢复可见性',()=>{const actors=Array.from({length:16},(_,i)=>{const root=new T.Group();root.position.x=i*2;return {networkId:String(i),root,nameplate:{visible:true}};});const game={hero:actors[0],enemies:actors.slice(1),locked:actors[15],pause(){},_clearDroppedWeapons(){}};const session=new NetworkGame(game,{host:true,playerId:'0'},{players:actors.map(a=>({id:a.networkId}))});session.updateNameplates();assert.equal(actors.filter(a=>a.nameplate.visible).length,4);assert.equal(actors[15].nameplate.visible,true);assert.equal(actors[8].nameplate.visible,false);session.dispose();assert.ok(actors.every(a=>a.nameplate.visible));});


test('联机姓名牌不暴露隐身敌人，保留同队提示并在状态结束后恢复',()=>{
 const actors=Array.from({length:4},(_,i)=>({networkId:String(i),root:new T.Group(),team:i===1?1:2,nameplate:{visible:true}}));actors[0].team=1;actors[1].nativeStats={10:1};actors[2].nativeStats={10:1};
 const game={hero:actors[0],enemies:actors.slice(1),locked:actors[2],pause(){},_clearDroppedWeapons(){}};
 const session=new NetworkGame(game,{host:true,playerId:'0'},{players:actors.map(a=>({id:a.networkId}))});
 try{session.updateNameplates();assert.equal(actors[1].nameplate.visible,true);assert.equal(actors[2].nameplate.visible,false);actors[2].nativeStats[10]=0;session.updateNameplates();assert.equal(actors[2].nameplate.visible,true);}finally{session.dispose();}
});

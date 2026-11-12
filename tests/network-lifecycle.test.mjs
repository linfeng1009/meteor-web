import test from 'node:test';
import assert from 'node:assert/strict';
import * as THREE from '../dist/vendor/three.module.js';
import {NetworkLobby} from '../dist/network-lobby.js';
import {NetworkGame} from '../dist/network-game.js';
const deferred=()=>{let resolve,reject;const promise=new Promise((a,b)=>{resolve=a;reject=b;});return {promise,resolve,reject};};
const room=(code='ABCDEF',phase='waiting')=>({code,phase,round:1,protocol:4,hostId:'host',players:[{id:'host'},{id:'guest'}]});

test('old connection failure cannot clear a newer connection or its connecting state',async()=>{
  const attempts=[],stops=[];
  const lobby=new NetworkLobby({getGame:()=>({}),onStart(){},onStop:message=>stops.push(message),onNotice(){},createClient:options=>{
    const pending=deferred(),client={closed:false,connect:()=>pending.promise,async leave(){this.closed=true;}};attempts.push({pending,client,options});return client;
  }});
  const old=lobby.connect('create',{});await lobby.leave(false);const next=lobby.connect('create',{});
  attempts[0].pending.reject(Error('旧请求失败'));await old;assert.equal(lobby.client,attempts[1].client);assert.equal(lobby.connecting,true);
  attempts[0].options.onError('旧错误');await attempts[0].options.onRoom(room());assert.equal(stops.length,0);
  attempts[1].client.room=room('FEDCBA');attempts[1].pending.resolve();await next;assert.equal(lobby.client.room.code,'FEDCBA');assert.equal(lobby.connecting,false);
});
test('leaving during scene start cancels session creation without stopping a newer room',async()=>{
  const start=deferred(),game={},stops=[];let valid,creates=0;
  const lobby=new NetworkLobby({getGame:()=>game,onStart:check=>{valid=check;return start.promise;},onStop:m=>stops.push(m),onNotice(){},createSession(){creates++;}});
  const client={room:room('ABCDEF','loading'),closed:false,async leave(){this.closed=true;}};lobby.client=client;lobby.generation=1;
  const loading=lobby.roomChanged(client.room);assert.equal(valid(),true);await lobby.leave(false);
  const newer={room:room('FEDCBA'),closed:false};lobby.client=newer;assert.equal(valid(),false);start.resolve();await loading;
  assert.equal(creates,0);assert.equal(lobby.client,newer);assert.equal(lobby.session,null);assert.equal(stops.length,0);assert.equal(lobby.loading,null);
});
test('a late session is disposed and never acknowledged after leaving during creation',async()=>{
  const created=deferred(),entered=deferred();let disposed=0,loaded=0;
  const lobby=new NetworkLobby({getGame:()=>game,onStart(){},onStop(){},onNotice(){},createSession(){entered.resolve();return created.promise;}}),game={};
  const client={room:room('ABCDEF','loading'),closed:false,async leave(){this.closed=true;},async command(){loaded++;}};lobby.client=client;lobby.generation=1;
  const loading=lobby.roomChanged(client.room);await entered.promise;await lobby.leave(false);created.resolve({dispose(){disposed++;}});await loading;
  assert.equal(disposed,1);assert.equal(loaded,0);assert.equal(lobby.session,null);assert.equal(lobby.loading,null);
});
test('old loader failure cannot leave or stop a newly connected room',async()=>{
  const pending=deferred(),entered=deferred(),game={},stops=[];
  const lobby=new NetworkLobby({getGame:()=>game,onStart(){},onStop:m=>stops.push(m),onNotice(){},createSession(){entered.resolve();return pending.promise;}});
  const old={room:room('ABCDEF','loading'),closed:false,async leave(){this.closed=true;}};lobby.client=old;lobby.generation=1;
  const loading=lobby.roomChanged(old.room);await entered.promise;await lobby.leave(false);
  const newer={room:room('FEDCBA'),closed:false};lobby.client=newer;pending.reject(Error('旧角色载入失败'));await loading;
  assert.equal(lobby.client,newer);assert.equal(newer.closed,false);assert.equal(stops.length,0);assert.equal(lobby.loading,null);
});
test('normal loading acknowledges and starts exactly one session despite repeated room updates',async()=>{
  let creates=0,loaded=0,plays=0;const game={},session={active:false,play(){this.active=true;plays++;}};
  const lobby=new NetworkLobby({getGame:()=>game,onStart(){},onStop(){},onNotice(){},createSession:async()=>{creates++;return session;}});
  const client={room:room('ABCDEF','loading'),closed:false,async command(){loaded++;}};lobby.client=client;lobby.generation=1;
  await Promise.all([lobby.roomChanged(client.room),lobby.roomChanged(client.room)]);client.room={...client.room,phase:'playing'};
  await lobby.roomChanged(client.room);await lobby.roomChanged(client.room);assert.deepEqual({creates,loaded,plays},{creates:1,loaded:1,plays:1});
});
test('cancelled fighter creation disposes late assets and never installs gameplay hooks',async()=>{
  const equip=deferred(),entered=deferred();let current=true,disposed=0,placed=0,equips=0,selected;
  const peer={root:new THREE.Group(),character:{dispose(){disposed++;}}},action=()=>{};
  const game={hero:{},enemies:[],scene:new THREE.Scene(),action,pause(){},setInfiniteRage(){},_disposeNameplate(){},_nameplate(){},_placeFighter(){placed++;},
    async _equip(){if(++equips===2){entered.resolve();await equip.promise;}},async _createFighter(...args){selected=args;return peer;}};
  const selectionRoom=room();selectionRoom.players[1].selection={character:0,characterAppearance:'raiden'};
  const creating=NetworkGame.create(game,{playerId:'host',host:true},selectionRoom,{isCurrent:()=>current});await entered.promise;
  assert.deepEqual(selected,[0,undefined,false,null,'raiden']);
  assert.equal(peer.root.parent,game.scene);current=false;equip.resolve();assert.equal(await creating,null);
  assert.equal(disposed,1);assert.equal(placed,0);assert.equal(peer.root.parent,null);assert.deepEqual(game.enemies,[]);assert.equal(game.action,action);
});

test('连接失败清除等待状态并保留可见错误，能够立即重新连接',async()=>{
 let attempts=0;const states=[];
 const lobby=new NetworkLobby({getGame(){},onStart(){},onStop(){},onNotice(){},createClient:()=>({closed:false,async connect(){if(++attempts===1)throw Error('房间不存在或房主已离开');this.room=room();},async leave(){this.closed=true;}})});
 lobby.render=()=>states.push({connecting:lobby.connecting,error:lobby.error,client:!!lobby.client});
 await assert.rejects(lobby.connect('join',{code:'AAAAAA'}),/房间不存在/);assert.equal(states.at(-1).connecting,false);assert.equal(states.at(-1).client,false);assert.match(states.at(-1).error,/房间不存在/);
 await lobby.connect('join',{code:'ABCDEF'});assert.equal(lobby.client.room.code,'ABCDEF');assert.equal(lobby.connecting,false);assert.equal(lobby.error,'');
});

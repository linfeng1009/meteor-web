import test from 'node:test';
import assert from 'node:assert/strict';
import {NetworkRooms,createNetworkServer} from '../network-server.mjs';
function room(){const rooms=new NetworkRooms(),a=rooms.create('房主',{maxPlayers:2}),b=rooms.join(a.room.code,'剑客');return {rooms,a,b,call:(p,op,data={})=>rooms.request(a.room.code,p.token,op,{round:rooms.rooms.get(a.room.code)?.round||0,...data})};}
const frame=(a,b,sequence=1)=>({sequence,time:1,players:[a,b].map(p=>({id:p.playerId,position:[0,0,0],angle:0,hp:1000,maxHp:1000,rage:0,pose:6,source:0,frame:7400,serial:1,effectTime:0}))});

test('host impact snapshots are bounded, validated atomically and cannot mark guarded contacts as blood',()=>{
  const {a,b,call}=playing(),event={id:1,time:1,point:[0,1,0],direction:[0,0,1],guarded:false,knockdown:false,blood:true,sound:'W00BL090',attackerId:a.playerId,targetId:b.playerId};
  const state={...frame(a,b),impacts:[event]};call(a,'sync',{frame:state});assert.deepEqual(call(b,'sync').frame.impacts,[event]);
  for(const impacts of [[{...event,point:[NaN,0,0]}],[{...event,guarded:true}],[event,event],Array.from({length:33},(_,i)=>({...event,id:i+1}))]){
    assert.throws(()=>call(a,'sync',{frame:{...state,sequence:2,impacts}}),/无效/);assert.equal(call(b,'sync').frame.sequence,1);
  }
  assert.throws(()=>call(b,'sync',{frame:{...state,sequence:2}}),/房主/);
});
test('room needs two prepared players and only the host may start; both clients must finish loading',()=>{
  const {a,b,call}=room();assert.throws(()=>call(a,'start'),/准备/);assert.throws(()=>call(b,'start'),/房主/);
  call(a,'ready',{ready:true});call(b,'ready',{ready:true});assert.equal(call(a,'start').room.phase,'loading');
  assert.equal(call(a,'loaded').room.phase,'loading');assert.equal(call(b,'loaded').room.phase,'playing');
  assert.throws(()=>call(a,'ready',{ready:true}),/已经|开始/);
});
test('guest submits ordered inputs but cannot publish combat state or impersonate another player',()=>{
  const {a,b,call,rooms}=room();call(a,'ready',{ready:true});call(b,'ready',{ready:true});call(a,'start');call(a,'loaded');call(b,'loaded');
  const input={action:'attack',active:true,angle:0,sequence:1};call(b,'sync',{input:[input,input]});const batch=call(a,'sync',{frame:frame(a,b)}).input;
  assert.equal(batch.length,1);assert.equal(batch[0].playerId,b.playerId);assert.deepEqual(call(b,'sync').frame,frame(a,b));
  assert.throws(()=>call(b,'sync',{frame:frame(a,b)}),/房主/);assert.throws(()=>rooms.request(a.room.code,'wrong','sync'),/身份/);
  assert.throws(()=>call(b,'sync',{input:[{...input,action:'setHp',sequence:2}]}),/无效/);assert.throws(()=>call(b,'sync',{input:[{...input,sequence:2,angle:NaN}]}),/无效/);
});
test('full rooms reject joins; leaving resets readiness, host leave closes room, stale host expires',()=>{
  const {rooms,a,b,call}=room();assert.throws(()=>rooms.join(a.room.code,'第三人'),/满/);call(b,'leave');assert.equal(call(a,'sync').room.players.length,1);call(a,'leave');assert.throws(()=>call(b,'sync'),/关闭/);
  let now=0;const r=new NetworkRooms({now:()=>now}),p=r.create('房主');now=20001;assert.throws(()=>r.request(p.room.code,p.token,'sync'),/关闭/);
});
test('HTTP integration shares authoritative frame between two independent room identities',async()=>{
  const server=createNetworkServer();await new Promise(resolve=>server.listen(0,'127.0.0.1',resolve));const base=`http://127.0.0.1:${server.address().port}`;
  const post=async(path,data={},credential)=>{const response=await fetch(base+path,{method:'POST',headers:{'Content-Type':'application/json',...(credential?{Authorization:'Bearer '+credential}:{})},body:JSON.stringify(data)});return {status:response.status,body:await response.json()};};
  try{const a=(await post('/api/rooms/create',{name:'房主'})).body,b=(await post('/api/rooms/join',{code:a.room.code,name:'加入者'})).body;
    const cmd=(p,op,data={})=>post(`/api/rooms/${a.room.code}/${op}`,{round:1,...data},p.token);
    await cmd(a,'ready',{ready:true});await cmd(b,'ready',{ready:true});await cmd(a,'start');await cmd(a,'loaded');await cmd(b,'loaded');
    await cmd(b,'sync',{input:[{action:'forward',active:true,angle:0,sequence:1}]});const host=await cmd(a,'sync',{frame:frame(a,b)}),guest=await cmd(b,'sync');
    assert.equal(host.body.input[0].action,'forward');assert.equal(guest.body.frame.players.length,2);assert.equal((await cmd(b,'sync',{frame:frame(a,b,2)})).status,403);
    const cross=await fetch(base+'/api/rooms/create',{method:'POST',headers:{Origin:'http://evil.invalid'},body:'{}'});assert.equal(cross.status,403);
  }finally{await new Promise(resolve=>server.close(resolve));}
});

function playing(){const f=room();f.call(f.a,'ready',{ready:true});f.call(f.b,'ready',{ready:true});f.call(f.a,'start');f.call(f.a,'loaded');f.call(f.b,'loaded');return f;}
test('relay retains delivery until host confirmation, accepts repeat confirmation, and rejects guest or future acknowledgements',()=>{
  const {rooms,a,b,call}=playing(),input={action:'attack',active:true,sequence:1,angle:0};
  call(b,'sync',{input:[input]});const first=call(a,'sync');assert.deepEqual(call(a,'sync').input,first.input);
  assert.throws(()=>call(b,'sync',{inputAck:{[b.playerId]:1}}),/房主/);
  assert.throws(()=>call(a,'sync',{inputAck:{[b.playerId]:2}}),/无效/);
  assert.throws(()=>call(a,'sync',{inputAck:{[b.playerId]:1},frame:{sequence:1}}),/无效/);
  assert.equal(rooms.rooms.get(a.room.code).players[1].input.length,1,'invalid frame must not commit an acknowledgement');
  assert.equal(call(a,'sync',{inputAck:{[b.playerId]:1}}).input.length,0);assert.equal(call(a,'sync',{inputAck:{[b.playerId]:1}}).input.length,0);
});
test('malformed batches are atomic and queue saturation never silently evicts accepted operations',()=>{
  const {rooms,a,b,call}=playing(),input=sequence=>({action:'attack',active:true,sequence,angle:0});
  assert.throws(()=>call(b,'sync',{input:[input(1),{...input(2),action:'invalid'}]}),/无效/);
  assert.equal(rooms.rooms.get(a.room.code).players[1].lastSequence,0);assert.equal(call(a,'sync').input.length,0);
  for(let batch=0;batch<4;batch++)call(b,'sync',{input:Array.from({length:64},(_,i)=>input(batch*64+i+1))});
  assert.throws(()=>call(b,'sync',{input:[input(257)]}),/积压/);
  assert.equal(call(a,'sync').input.length,256);assert.equal(rooms.rooms.get(a.room.code).players[1].lastSequence,256);
  call(a,'sync',{inputAck:{[b.playerId]:256}});assert.equal(call(b,'sync',{input:[input(257)]}).acceptedSequence,257);
  assert.deepEqual(call(a,'sync').input.map(x=>x.sequence),[257]);
});
test('old-round writes and acknowledgements cannot affect the next match',()=>{
  const next=playing();next.call(next.a,'sync',{frame:{...frame(next.a,next.b),result:{reason:'score',winnerIds:[next.a.playerId]}}});next.call(next.a,'rematch');next.call(next.b,'leave');const guest=next.rooms.join(next.a.room.code,'新玩家');
  next.call(next.a,'ready',{ready:true});next.call(guest,'ready',{ready:true});next.call(next.a,'start');next.call(next.a,'loaded');next.call(guest,'loaded');
  assert.throws(()=>next.call(guest,'sync',{round:1,input:[{action:'attack',active:true,sequence:1,angle:0}]}),/对局/);
  assert.throws(()=>next.call(next.a,'sync',{round:1,inputAck:{[guest.playerId]:1}}),/对局/);
  assert.equal(next.call(next.a,'sync').input.length,0);assert.equal(next.call(guest,'sync').room.round,2);
});
test('room revisions advance for membership, preparation and loading, but remain stable during polling',()=>{
  const {rooms,a,b,call}=room(),revisions=[a.room.revision,b.room.revision];
  revisions.push(call(a,'ready',{ready:true}).room.revision,call(b,'ready',{ready:true}).room.revision,call(a,'start').room.revision,call(a,'loaded').room.revision,call(b,'loaded').room.revision);
  for(let i=1;i<revisions.length;i++)assert.ok(revisions[i]>revisions[i-1]);
  assert.equal(call(a,'sync').room.revision,revisions.at(-1));assert.equal(call(a,'sync').room.revision,revisions.at(-1));
  call(b,'leave');const waiting=call(a,'sync').room;assert.ok(waiting.revision>revisions.at(-1));assert.equal(waiting.phase,'playing');assert.equal(waiting.players.length,1);assert.throws(()=>rooms.join(a.room.code,'新客人'),/开局/);
});
test('guest timeout publishes a newer waiting-state revision while host remains connected',()=>{
  let now=0;const rooms=new NetworkRooms({now:()=>now}),host=rooms.create('房主'),guest=rooms.join(host.room.code,'客人');
  now=10000;rooms.request(host.room.code,host.token,'sync');now=20001;
  const state=rooms.request(host.room.code,host.token,'sync').room;assert.ok(state.revision>guest.room.revision);assert.equal(state.players.length,1);
});
test('operation timestamps preserve short intervals, reject invalid/backward batches atomically and tolerate retries',()=>{
  const {a,b,call,rooms}=playing(),input=(sequence,time)=>({action:'forward',active:true,angle:0,sequence,time});
  for(const time of [NaN,Infinity,-1,1e9+1])assert.throws(()=>call(b,'sync',{input:[input(1,time)]}),/时间/);
  assert.throws(()=>call(b,'sync',{input:[input(1,10),input(2,9)]}),/时间/);
  assert.equal(rooms.rooms.get(a.room.code).players[1].lastSequence,0);assert.equal(call(a,'sync').input.length,0);
  const batch=[input(1,10),{...input(2,10.03),active:false},input(3,10.12)];call(b,'sync',{input:batch});call(b,'sync',{input:batch});
  assert.deepEqual(call(a,'sync').input.map(x=>x.time),[10,10.03,10.12]);
  assert.throws(()=>call(b,'sync',{input:[input(4,10.1)]}),/时间/);assert.equal(rooms.rooms.get(a.room.code).players[1].lastSequence,3);
});


test('aim pitch is bounded on input and snapshot without partially accepting invalid state',()=>{
 const {a,b,call}=playing();for(const pitch of [NaN,Infinity,1.21,-1.21])assert.throws(()=>call(b,'sync',{input:[{sequence:1,action:'look',active:false,angle:0,pitch}]}),/无效/);
 call(b,'sync',{input:[{sequence:1,action:'look',active:false,angle:0,pitch:.4}]});assert.equal(call(a,'sync').input[0].pitch,.4);
 const state=frame(a,b);state.players[0].musketAim=true;state.players[0].aimPitch=.4;call(a,'sync',{frame:state});
 for(const patch of [{musketAim:1},{aimPitch:NaN},{aimPitch:1.3}]){const invalid=structuredClone(state);invalid.sequence=2;Object.assign(invalid.players[0],patch);assert.throws(()=>call(a,'sync',{frame:invalid}),/无效/);assert.equal(call(b,'sync').frame.sequence,1);}
});


test('blood style relays only bounded host-selected kind and force level, and legacy events still work',()=>{
 const {a,b,call}=playing(),event={id:1,time:1,point:[0,1,0],direction:[0,0,1],guarded:false,knockdown:true,blood:true,bloodStyle:{kind:'launch',level:2}};
 const state={...frame(a,b),impacts:[event]};call(a,'sync',{frame:state});assert.deepEqual(call(b,'sync').frame.impacts[0].bloodStyle,event.bloodStyle);
 for(const bloodStyle of [{kind:'unknown',level:1},{kind:'slash',level:NaN},{kind:'slash',level:3},{kind:'slash',level:-1}]){assert.throws(()=>call(a,'sync',{frame:{...state,sequence:2,impacts:[{...event,bloodStyle}]}}),/无效/);assert.equal(call(b,'sync').frame.sequence,1);}
 assert.throws(()=>call(a,'sync',{frame:{...state,sequence:2,impacts:[{...event,blood:false}]}}),/无效/);
});

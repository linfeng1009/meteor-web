import test from 'node:test';
import assert from 'node:assert/strict';
import {NetworkClient} from '../dist/network-client.js';
import {NetworkRooms,createNetworkServer} from '../network-server.mjs';

function fixture(){
  const rooms=new NetworkRooms(),host=rooms.create('房主'),guest=rooms.join(host.room.code,'剑客');
  const request=(p,op,data={})=>rooms.request(host.room.code,p.token,op,{round:rooms.rooms.get(host.room.code)?.round||0,...data});
  request(host,'ready',{ready:true});request(guest,'ready',{ready:true});request(host,'start');request(host,'loaded');request(guest,'loaded');
  const client=new NetworkClient();Object.assign(client,{room:request(guest,'sync').room,code:host.room.code,playerId:guest.playerId});
  client.api=async(path,data)=>request(guest,path.split('/').at(-1),data);
  return {client,request,host,guest,rooms};
}

test('lost response retries the identical batch without executing an attack twice',async()=>{
  const {client,request,host}=fixture(),api=client.api;let fail=true;
  client.api=async(path,data)=>{const result=await api(path,data);if(fail){fail=false;throw Error('响应丢失');}return result;};
  client.send('attack');await client.sync();
  assert.equal(client.failures,1);const pending=structuredClone(client.pendingInput);
  client.send('jump');await client.sync();
  assert.equal(client.pendingInput,null);assert.equal(client.failures,0);
  const first=request(host,'sync').input;assert.deepEqual(first.map(x=>x.action),['attack','look']);
  assert.equal(first[0].sequence,pending[0].sequence);
  request(host,'sync',{inputAck:{[first[0].playerId]:first.at(-1).sequence}});
  await client.sync();assert.deepEqual(request(host,'sync').input.map(x=>x.action),['jump','look']);
});

test('request failure preserves press and release ordering while new input waits',async()=>{
  const {client,request,host}=fixture(),api=client.api;let fail=true;
  client.api=async(path,data)=>{if(fail){fail=false;throw Error('请求未送达');}return api(path,data);};
  client.send('forward');await client.sync();client.send('forward',false);
  await client.sync();await client.sync();
  const input=request(host,'sync').input;
  assert.deepEqual(input.map(x=>[x.action,x.active]),[['forward',true],['look',false],['forward',false],['look',false]]);
  assert.deepEqual(input.at(-1).held,[]);
});

test('large bursts drain in ordered batches without dropping attacks or held-key releases',async()=>{
  const {client,request,host}=fixture();client.send('forward');
  for(let i=0;i<100;i++)client.send('attack');
  await client.sync();await client.sync();const input=request(host,'sync').input;
  assert.equal(input.filter(x=>x.action==='attack').length,100);assert.equal(input[0].action,'forward');assert.deepEqual(input.at(-1).held,['forward']);
  client.send('clear',false);await client.sync();assert.deepEqual(request(host,'sync').input.at(-1).held,[]);
});

function hostClient(f,onInput=()=>{}){
  const client=new NetworkClient({onInput});Object.assign(client,{room:f.client.room,code:f.client.code,playerId:f.host.playerId});
  client.api=async(path,data)=>f.request(f.host,path.split('/').at(-1),data);return client;
}
test('host response loss and acknowledgement response loss never drop or replay applied operations',async()=>{
  const f=fixture(),applied=[],host=hostClient(f,batch=>applied.push(...batch)),api=host.api;let request=0;
  host.api=async(path,data)=>{const result=await api(path,data);if([1,3].includes(++request))throw Error('房主响应丢失');return result;};
  for(const [action,active] of [['attack',true],['guard',true],['guard',false],['jump',true],['lock',true]])f.client.send(action,active);
  await f.client.sync();await host.sync();assert.equal(applied.length,0);
  await host.sync();assert.deepEqual(applied.filter(x=>x.action!=='look').map(x=>[x.action,x.active]),[['attack',true],['guard',true],['guard',false],['jump',true],['lock',true]]);
  f.client.send('attack');await f.client.sync();await host.sync(); // Ack commits, but newly delivered input response is lost.
  assert.equal(applied.filter(x=>x.action==='attack').length,1);
  await host.sync();await host.sync();assert.equal(applied.filter(x=>x.action==='attack').length,2);
  const peer=f.rooms.rooms.get(f.client.code).players.find(p=>p.id===f.guest.playerId);assert.equal(peer.input.length,0);
  assert.equal(new Set(applied.map(x=>x.sequence)).size,applied.length);
});
test('host retries an acknowledgement which never reached the server without applying duplicates',async()=>{
  const f=fixture(),applied=[],host=hostClient(f,batch=>applied.push(...batch)),api=host.api;
  f.client.send('attack');await f.client.sync();await host.sync();
  let fail=true;host.api=async(path,data)=>{if(fail){fail=false;throw Error('确认未送达');}return api(path,data);};
  await host.sync();await host.sync();await host.sync();assert.equal(applied.filter(x=>x.action==='attack').length,1);
  assert.equal(f.rooms.rooms.get(f.client.code).players[1].input.length,0);
});
test('host-local menu clear does not accumulate unsent guest operations',()=>{
  const host=hostClient(fixture());for(let i=0;i<300;i++)host.send('clear',false);
  assert.equal(host.closed,false);assert.equal(host.queue.length,0);assert.equal(host.sequence,0);
});
test('consumer errors stop the session instead of blindly retrying partially applied actions',async()=>{
  const f=fixture(),applied=[],errors=[],host=hostClient(f,batch=>{applied.push(batch[0].action);if(batch[0].action==='jump')throw Error('执行失败');});host.onError=message=>errors.push(message);
  f.client.send('attack');f.client.send('jump');await f.client.sync();await host.sync();await host.sync();
  assert.deepEqual(applied,['attack','jump']);assert.equal(host.closed,true);assert.equal(errors.length,1);assert.match(errors[0],/执行失败/);
});
test('leaving during an in-flight response prevents room, frame and input callbacks',async()=>{
  const f=fixture();let resolve,callbacks=0;const host=hostClient(f,()=>callbacks++);host.onRoom=host.onFrame=()=>callbacks++;
  host.api=()=>new Promise(done=>resolve=done);const syncing=host.sync();const result=f.request(f.host,'sync');host.closed=true;host.resetInput();resolve(result);await syncing;assert.equal(callbacks,0);
});
test('late old-round responses cannot replace new-round state or replay old inputs',async()=>{
  const f=fixture();let resolve,applied=0;const host=hostClient(f,()=>applied++),oldRoom=f.client.room;
  host.api=()=>new Promise(done=>resolve=done);const syncing=host.sync();host.setRoom({...oldRoom,round:oldRoom.round+1});
  resolve({room:oldRoom,input:[{playerId:f.guest.playerId,action:'attack',sequence:1}]});await syncing;
  assert.equal(applied,0);assert.equal(host.room.round,oldRoom.round+1);assert.equal(host.processed.size,0);
});
test('queue overload is explicit and bounded; a partial receipt acknowledgement is never treated as success',async()=>{
  const f=fixture(),errors=[];f.client.onError=message=>errors.push(message);
  for(let i=0;i<257;i++)f.client.send('attack');assert.equal(f.client.closed,true);assert.equal(errors.length,1);assert.match(errors[0],/积压/);
  const other=fixture();other.client.onError=message=>errors.push(message);other.client.send('jump');
  other.client.api=async()=>({room:other.client.room,acceptedSequence:0});await other.client.sync();assert.equal(other.client.closed,true);assert.match(errors.at(-1),/未确认/);
});
test('real HTTP clients recover dropped guest and host responses and clear acknowledged input',async()=>{
  const f=fixture(),server=createNetworkServer({rooms:f.rooms}),applied=[];await new Promise(resolve=>server.listen(0,'127.0.0.1',resolve));
  const base=`http://127.0.0.1:${server.address().port}`,host=hostClient(f,batch=>applied.push(...batch));
  f.client.token=f.guest.token;host.token=f.host.token;
  for(const client of [f.client,host]){
    let drop=true;client.api=async(path,data,auth)=>{const result=await NetworkClient.prototype.api.call(client,base+path,data,auth);if(drop){drop=false;throw Error('模拟响应丢失');}return result;};
  }
  try{
    f.client.send('attack');f.client.send('guard');f.client.send('guard',false);
    await f.client.sync();await f.client.sync();await host.sync();await host.sync();await host.sync();
    assert.deepEqual(applied.map(x=>[x.action,x.active]),[['attack',true],['guard',true],['guard',false],['look',false]]);
    assert.equal(f.rooms.rooms.get(f.client.code).players[1].input.length,0);
  }finally{await new Promise(resolve=>server.close(resolve));}
});
test('leaving before create completes releases the late room without callbacks or a polling timer',async()=>{
  const rooms=new NetworkRooms();let finish,callbacks=0,leaves=0;
  const created=rooms.create('迟到房主'),client=new NetworkClient({onRoom:()=>callbacks++});
  client.api=async(path)=>{if(path.endsWith('/create'))return new Promise(resolve=>finish=resolve);leaves++;return rooms.request(created.room.code,created.token,'leave');};
  const connecting=client.connect('create',{});await client.leave();finish(created);assert.equal(await connecting,null);
  assert.equal(client.closed,true);assert.equal(callbacks,0);assert.equal(client.timer,undefined);assert.equal(leaves,1);assert.equal(rooms.rooms.size,0);
});
test('invalid protocol releases the newly created room instead of leaking membership',async()=>{
  let leaves=0;const client=new NetworkClient();client.api=async path=>path.endsWith('/create')?{token:'test',playerId:'host',room:{code:'ABCDEF',round:0,protocol:1}}:(leaves++,{left:true});
  await assert.rejects(client.connect('create',{}),/协议/);assert.equal(leaves,1);assert.equal(client.closed,true);assert.equal(client.timer,undefined);
});
test('normal HTTP connect starts polling and leave stops it and removes the room',async()=>{
  const rooms=new NetworkRooms(),server=createNetworkServer({rooms}),client=new NetworkClient();await new Promise(resolve=>server.listen(0,'127.0.0.1',resolve));
  const base=`http://127.0.0.1:${server.address().port}`;client.api=(path,data,auth)=>NetworkClient.prototype.api.call(client,base+path,data,auth);
  try{await client.connect('create',{name:'正常连接'});assert.equal(client.room.phase,'waiting');assert.ok(client.timer);assert.equal(rooms.rooms.size,1);await client.leave();assert.equal(client.closed,true);assert.equal(rooms.rooms.size,0);}
  finally{await client.leave().catch(()=>{});await new Promise(resolve=>server.close(resolve));}
});
test('late ready and loaded command responses cannot roll back newer same-round room state',async()=>{
  const f=fixture(),client=f.client,base=client.room;let finish,updates=0;client.onRoom=()=>updates++;
  client.room={...base,phase:'loading',revision:10};client.api=()=>new Promise(resolve=>finish=resolve);
  const command=client.command('loaded');client.setRoom({...base,phase:'playing',revision:11});
  finish({room:{...base,phase:'loading',revision:10}});await command;
  assert.equal(client.room.phase,'playing');assert.equal(client.room.revision,11);assert.equal(updates,1);
  client.setRoom({...base,phase:'waiting',revision:12});assert.equal(client.room.phase,'waiting','newer waiting state after a peer leaves is valid');
  assert.equal(client.setRoom({...base,phase:'playing',revision:11}),false);assert.equal(client.room.phase,'waiting');
});
test('stale polling responses cannot revive peer state or apply old combat input after leaving',async()=>{
  const f=fixture();let finish,inputs=0,frames=0;const host=hostClient(f,()=>inputs++);host.onFrame=()=>frames++;
  const base=host.room;host.api=()=>new Promise(resolve=>finish=resolve);const syncing=host.sync();
  host.setRoom({...base,phase:'waiting',revision:base.revision+1,players:[base.players[0]]});
  finish({room:base,input:[{action:'attack',sequence:1,playerId:f.guest.playerId}],frame:{sequence:1}});await syncing;
  assert.equal(host.room.phase,'waiting');assert.equal(host.room.players.length,1);assert.equal(inputs,0);assert.equal(frames,0);assert.equal(host.closed,false);
});
test('input retries preserve capture timestamps rather than the later resend clock',async()=>{
  const f=fixture(),api=f.client.api;let time=100,drop=true;f.client.now=()=>time;
  f.client.api=async(path,data)=>{const result=await api(path,data);if(drop){drop=false;throw Error('响应丢失');}return result;};
  f.client.send('forward');time=100.03;f.client.send('forward',false);time=100.12;f.client.send('forward');
  await f.client.sync();time=105;await f.client.sync();
  const batch=f.request(f.host,'sync').input;assert.deepEqual(batch.map(x=>x.time),[100,100.03,100.12,100.12]);
});

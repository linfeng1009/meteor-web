import test from 'node:test';
import assert from 'node:assert/strict';
import {setTimeout as delay} from 'node:timers/promises';
import {NetworkClient} from '../dist/network-client.js';
import {NetworkRooms,createNetworkServer} from '../network-server.mjs';

async function until(predicate){for(let i=0;i<300;i++){if(predicate())return;await delay(5);}assert.fail('等待实时状态超时');}
async function fixture(){
  const rooms=new NetworkRooms(),h=rooms.create('房主'),g=rooms.join(h.room.code,'客人');
  const request=(p,op,data={})=>rooms.request(h.room.code,p.token,op,{round:rooms.rooms.get(h.room.code)?.round||0,...data});
  for(const p of [h,g])request(p,'ready',{ready:true});request(h,'start');for(const p of [h,g])request(p,'loaded');
  const server=createNetworkServer({rooms});await new Promise(resolve=>server.listen(0,'127.0.0.1',resolve));const base=`http://127.0.0.1:${server.address().port}`;
  const applied=[],frames=[],host=new NetworkClient({stream:true,streamUrl:p=>base+p,onInput:batch=>applied.push(...batch)}),guest=new NetworkClient({stream:true,streamUrl:p=>base+p,onFrame:frame=>frames.push(frame)});
  for(const [client,p] of [[host,h],[guest,g]]){Object.assign(client,{room:request(p,'sync').room,code:h.room.code,playerId:p.playerId,token:p.token});client.api=(path,data,auth)=>NetworkClient.prototype.api.call(client,base+path,data,auth);client.timer=setInterval(()=>client.sync(),10000);client.startStream();}
  await until(()=>host.streamActive&&guest.streamActive);
  const state=p=>({id:p.playerId,position:[0,0,0],angle:0,hp:100,maxHp:100,rage:0,pose:1,source:0,frame:0,serial:1,effectTime:0});
  return {rooms,server,base,h,g,host,guest,request,applied,frames,frame:(sequence=1)=>({sequence,time:sequence/30,players:[state(h),state(g)]}),async close(){await guest.leave().catch(()=>{});await host.leave().catch(()=>{});server.closeAllConnections();await new Promise(resolve=>server.close(resolve));}};
}
test('不等房主和客人轮询即可推送输入与状态，轮询重送不重复执行',async()=>{
  const f=await fixture();try{
    f.guest.send('forward');f.guest.send('attack');f.guest.send('forward',false);
    await until(()=>f.applied.filter(x=>x.action!=='look').length===3);
    assert.deepEqual(f.applied.filter(x=>x.action!=='look').map(x=>[x.action,x.active]),[['forward',true],['attack',true],['forward',false]]);
    f.host.getFrame=()=>f.frame();f.host.flushFrame();await until(()=>f.frames.some(x=>x.sequence===1));
    assert.equal(f.request(f.g,'sync',{afterFrame:1}).frame,null,'已推送的状态不再随轮询重复下载');
    assert.equal(f.request(f.g,'sync').frame.sequence,1,'旧客户端仍可正常轮询');
    assert.throws(()=>f.request(f.g,'sync',{afterFrame:999}),/状态确认/);
    f.host.getFrame=()=>null;await f.host.sync();assert.equal(f.applied.filter(x=>x.action==='attack').length,1);
  }finally{await f.close();}
});
test('推送确认不吞掉响应丢失后的重试批次，补发与推送不重复攻击',async()=>{
  const f=await fixture();try{
    const api=f.guest.api;let lost=true;f.guest.api=async(...args)=>{const r=await api(...args);if(lost){lost=false;throw Error('丢失POST响应');}return r;};
    f.guest.send('attack');await until(()=>f.applied.some(x=>x.action==='attack')&&f.guest.failures===1);
    assert.ok(f.guest.pendingInput,'只能由POST完整批次确认清理重试数据');
    await f.guest.sync();assert.equal(f.guest.pendingInput,null);await f.host.sync();
    assert.equal(f.applied.filter(x=>x.action==='attack').length,1);
  }finally{await f.close();}
});
test('推送断线回退到原确认链路，重连后继续推送且不回放已执行攻击',async()=>{
  const f=await fixture();try{
    f.host.streamer.controller.abort();await until(()=>!f.host.streamActive);
    f.guest.send('jump');await until(()=>!f.guest.pendingInput&&f.guest.sequence>0);await f.host.sync();assert.equal(f.applied.filter(x=>x.action==='jump').length,1);
    await until(()=>f.host.streamActive);f.guest.send('attack');await until(()=>f.applied.some(x=>x.action==='attack'));
    assert.equal(f.applied.filter(x=>x.action==='jump').length,1);
  }finally{await f.close();}
});
test('推送接口验证身份和来源，不接受URL里的凭证，退房取消监听',async()=>{
  const f=await fixture();try{
    for(const [suffix,headers] of [['',{}],['?token='+f.h.token,{}],['',{Authorization:'Bearer '+f.h.token,Origin:'http://evil.example'}]]){
      const response=await fetch(`${f.base}/api/rooms/${f.h.room.code}/events${suffix}`,{headers});assert.equal(response.status,403);await response.text();
    }
    await f.guest.leave();await until(()=>!f.rooms.listeners.get(f.h.room.code)?.has(f.g.token));
  }finally{await f.close();}
});
test('慢订阅有数量限制，通知按任务合批且不替代玩家在线心跳',async()=>{
  let now=0;const rooms=new NetworkRooms({now:()=>now}),h=rooms.create('房主');let calls=0;
  const off1=rooms.subscribe(h.room.code,h.token,()=>calls++),off2=rooms.subscribe(h.room.code,h.token,()=>{});
  assert.throws(()=>rooms.subscribe(h.room.code,h.token,()=>{}),/上限/);
  rooms.notify(h.room.code);rooms.notify(h.room.code);await new Promise(resolve=>setImmediate(resolve));assert.equal(calls,1);
  now=100;rooms.request(h.room.code,h.token,'sync',{}, {touch:false});assert.equal(rooms.rooms.get(h.room.code).players[0].seen,0);
  off1();off2();assert.equal(rooms.listeners.size,0);
});

test('客人输入只通知房主，房主快照只通知客人，避免人数平方级重复广播',async()=>{
  const rooms=new NetworkRooms(),h=rooms.create('房主'),g=rooms.join(h.room.code,'客人');let hosts=0,guests=0;
  const a=rooms.subscribe(h.room.code,h.token,()=>hosts++),b=rooms.subscribe(h.room.code,g.token,()=>guests++);
  try{rooms.notify(h.room.code,'host');await new Promise(resolve=>setImmediate(resolve));assert.deepEqual([hosts,guests],[1,0]);
    rooms.notify(h.room.code,'guest');await new Promise(resolve=>setImmediate(resolve));assert.deepEqual([hosts,guests],[1,1]);
  }finally{a();b();}
});

test('16人同时推送操作与接收房主状态，不吞键且不重复结算',async()=>{
  const rooms=new NetworkRooms(),h=rooms.create('房主',{maxPlayers:16}),players=[h];
  for(let i=1;i<16;i++)players.push(rooms.join(h.room.code,'客人'+i));
  const request=(p,op,data={})=>rooms.request(h.room.code,p.token,op,{round:rooms.rooms.get(h.room.code)?.round||0,...data});
  for(const p of players)request(p,'ready',{ready:true});request(h,'start');for(const p of players)request(p,'loaded');
  const server=createNetworkServer({rooms});await new Promise(resolve=>server.listen(0,'127.0.0.1',resolve));const base=`http://127.0.0.1:${server.address().port}`;
  const applied=[],seen=new Set(),clients=[];let sequence=0;
  try{
    for(const p of players){const client=new NetworkClient({stream:true,streamUrl:path=>base+path,onInput:batch=>applied.push(...batch),onFrame:()=>seen.add(p.playerId)});
      Object.assign(client,{room:request(p,'sync').room,code:h.room.code,playerId:p.playerId,token:p.token});
      client.api=(path,data,auth)=>NetworkClient.prototype.api.call(client,base+path,data,auth);client.timer=setInterval(()=>client.sync(),10000);clients.push(client);client.startStream();
    }
    await until(()=>clients.every(c=>c.streamActive));for(const c of clients.slice(1))c.send('attack');
    await until(()=>applied.filter(x=>x.action==='attack').length===15);
    assert.equal(new Set(applied.filter(x=>x.action==='attack').map(x=>x.playerId)).size,15);
    clients[0].getFrame=()=>({sequence:++sequence,time:sequence/30,players:players.map(p=>({id:p.playerId,position:[0,0,0],angle:0,hp:100,maxHp:100,rage:0,pose:1,source:0,frame:0,serial:1,effectTime:0}))});
    clients[0].flushFrame();await until(()=>seen.size===15);await clients[0].sync();assert.equal(applied.filter(x=>x.action==='attack').length,15);
  }finally{for(const client of clients.slice().reverse())await client.leave().catch(()=>{});server.closeAllConnections();await new Promise(resolve=>server.close(resolve));}
});

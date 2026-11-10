import test from 'node:test';
import assert from 'node:assert/strict';
import {NetworkClient} from '../dist/network-client.js';
import {NetworkRooms} from '../network-server.mjs';

function fixture(){
  const rooms=new NetworkRooms(),host=rooms.create('房主'),guest=rooms.join(host.room.code,'剑客');
  const request=(p,op,data)=>rooms.request(host.room.code,p.token,op,data);
  request(host,'ready',{ready:true});request(guest,'ready',{ready:true});request(host,'start');request(host,'loaded');request(guest,'loaded');
  const client=new NetworkClient();Object.assign(client,{room:request(guest,'sync').room,code:host.room.code,playerId:guest.playerId});
  client.command=async(op,data)=>request(guest,op,data);
  return {client,request,host};
}

test('lost response retries the identical batch without executing an attack twice',async()=>{
  const {client,request,host}=fixture(),command=client.command;let fail=true;
  client.command=async(op,data)=>{const result=await command(op,data);if(fail){fail=false;throw Error('响应丢失');}return result;};
  client.send('attack');await client.sync();
  assert.equal(client.failures,1);const pending=structuredClone(client.pendingInput);
  client.send('jump');await client.sync();
  assert.equal(client.pendingInput,null);assert.equal(client.failures,0);
  const first=request(host,'sync').input;assert.deepEqual(first.map(x=>x.action),['attack','look']);
  assert.equal(first[0].sequence,pending[0].sequence);
  await client.sync();assert.deepEqual(request(host,'sync').input.map(x=>x.action),['jump','look']);
});

test('request failure preserves press and release ordering while new input waits',async()=>{
  const {client,request,host}=fixture(),command=client.command;let fail=true;
  client.command=async(op,data)=>{if(fail){fail=false;throw Error('请求未送达');}return command(op,data);};
  client.send('forward');await client.sync();client.send('forward',false);
  await client.sync();await client.sync();
  const input=request(host,'sync').input;
  assert.deepEqual(input.map(x=>[x.action,x.active]),[['forward',true],['look',false],['forward',false],['look',false]]);
  assert.deepEqual(input.at(-1).held,[]);
});

test('overflow remains bounded and publishes held keys after clearing stale events',async()=>{
  const {client,request,host}=fixture();client.send('forward');
  for(let i=0;i<100;i++)client.send('attack');
  await client.sync();const input=request(host,'sync').input;
  assert.ok(input.length<=64);assert.equal(input[0].action,'clear');assert.deepEqual(input.at(-1).held,['forward']);
  client.send('clear',false);await client.sync();assert.deepEqual(request(host,'sync').input.at(-1).held,[]);
});

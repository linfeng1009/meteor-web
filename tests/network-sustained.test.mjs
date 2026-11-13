import test from 'node:test';
import assert from 'node:assert/strict';
import {performance} from 'node:perf_hooks';
import {setTimeout as delay} from 'node:timers/promises';
import {NetworkRooms,createNetworkServer} from '../network-server.mjs';
import {NetworkClient,NETWORK_SYNC_MS} from '../dist/network-client.js';
async function until(fn){const end=performance.now()+5000;while(performance.now()<end){if(fn())return;await delay(5);}assert.fail('多人同步未在期限内完成');}

// Real HTTP/stream clients and a deterministic 60Hz transport fixture. These
// positions isolate scheduling from native collision/animation CPU; native
// multi-fighter combat is exercised separately in native-command-engine.
for(const count of [4,16])test(`${count}人持续移动、转向和连击：响应丢失后输入完整，松键及时生效且快照不重复洪泛`,async t=>{
  const rooms=new NetworkRooms(),h=rooms.create('房主',{maxPlayers:count}),players=[h];
  for(let i=1;i<count;i++)players.push(rooms.join(h.room.code,'同道'+i));
  const call=(p,op,data={})=>rooms.request(h.room.code,p.token,op,{round:rooms.rooms.get(h.room.code)?.round||0,...data});
  for(const p of players)call(p,'ready',{ready:true});call(h,'start');for(const p of players)call(p,'loaded');
  const server=createNetworkServer({rooms});await new Promise(resolve=>server.listen(0,'127.0.0.1',resolve));const base=`http://127.0.0.1:${server.address().port}`;
  const controls=new Map(players.map(p=>[p.playerId,{keys:new Set(),z:0,angle:0,attacks:0}])),sent=new Map(),seen=new Map(),clients=[],latencies=[];
  let ticks=0,sequence=0,published=0,dirty=false,physics,lose=true;
  const host=new NetworkClient({stream:true,streamUrl:path=>base+path,
    onInput:batch=>{for(const input of batch){const c=controls.get(input.playerId);dirty=true;c.angle=input.angle;
      if(input.action==='look')c.keys=new Set(input.held||[]);
      else if(input.action==='clear')c.keys.clear();
      else if(['forward','back'].includes(input.action)){if(input.active)c.keys.add(input.action);else c.keys.delete(input.action);}
      else if(input.action==='attack'&&input.active)c.attacks++;
    }},
    getFrame:()=>({sequence:++sequence,time:ticks/60,players:players.map(p=>{const c=controls.get(p.playerId);return {id:p.playerId,position:[0,0,c.z],angle:c.angle,hp:1000,maxHp:1000,rage:c.attacks,pose:1,source:0,frame:0,serial:1,effectTime:0};})})});
  try{
    for(const [i,p] of players.entries()){
      sent.set(p.playerId,[]);seen.set(p.playerId,0);
      const client=i?new NetworkClient({stream:true,streamUrl:path=>base+path,getAngle:()=>controls.get(p.playerId).testAngle||0,onFrame:frame=>{
        const own=frame.players.find(s=>s.id===p.playerId);let at=seen.get(p.playerId);
        while(at<own.rage){latencies.push(performance.now()-sent.get(p.playerId)[at]);at++;}seen.set(p.playerId,at);
      }}):host;
      Object.assign(client,{room:call(p,'sync').room,code:h.room.code,token:p.token,playerId:p.playerId});
      client.api=async(path,data,auth)=>{if(data?.frame)published++;const result=await NetworkClient.prototype.api.call(client,base+path,data,auth);
        if(i===1&&lose&&data?.input){lose=false;throw Error('模拟已送达但响应丢失');}return result;};
      client.timer=setInterval(()=>client.sync(),NETWORK_SYNC_MS);clients.push(client);client.startStream();
    }
    physics=setInterval(()=>{ticks++;for(const c of controls.values())c.z+=((c.keys.has('forward')?1:0)-(c.keys.has('back')?1:0))*8/60;if(dirty){dirty=false;host.flushFrame();}},1000/60);
    await until(()=>clients.every(c=>c.streamActive));
    for(const client of clients.slice(1))client.send('forward');
    for(let round=0;round<6;round++){
      for(const client of clients.slice(1)){controls.get(client.playerId).testAngle=round*.15;sent.get(client.playerId).push(performance.now());client.send('attack');client.send('attack',false);
        if(round===3){client.send('forward',false);client.send('back');}}
      await delay(70);
    }
    for(const client of clients.slice(1)){client.send('forward',false);client.send('back',false);}
    await until(()=>clients.slice(1).every(c=>seen.get(c.playerId)===6&&controls.get(c.playerId).keys.size===0&&!c.pendingInput&&c.queue.length===0));
    await host.sync();
    for(const client of clients.slice(1)){const c=controls.get(client.playerId);assert.equal(c.attacks,6);assert.equal(c.angle,.75);assert.ok(Math.abs(c.z)<20);}
    const positions=[...controls.values()].map(c=>c.z);await delay(60);assert.deepEqual([...controls.values()].map(c=>c.z),positions);
    assert.ok(published<=ticks+1,`${published}份完整快照不应超过${ticks}个物理帧`);
    latencies.sort((a,b)=>a-b);t.diagnostic(JSON.stringify({players:count,attacks:latencies.length,p50Ms:latencies[Math.floor(latencies.length*.5)],p95Ms:latencies[Math.floor(latencies.length*.95)],ticks,fullFrames:published}));
  }finally{clearInterval(physics);for(const client of clients.slice().reverse())await client.leave().catch(()=>{});server.closeAllConnections();await new Promise(resolve=>server.close(resolve));}
});

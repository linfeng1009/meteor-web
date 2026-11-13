import {performance} from 'node:perf_hooks';
import {setTimeout as delay} from 'node:timers/promises';
import {NetworkClient,NETWORK_SYNC_MS} from '../../dist/network-client.js';
import {NetworkRooms,createNetworkServer} from '../../network-server.mjs';
const rooms=new NetworkRooms(),server=createNetworkServer({rooms});
await new Promise(resolve=>server.listen(0,'127.0.0.1',resolve));
const base=`http://127.0.0.1:${server.address().port}`;
async function measure(interval,immediate,push=false){
 const h=rooms.create('延迟测量房主'),g=rooms.join(h.room.code,'延迟测量客人');
 const request=(p,op,data={})=>rooms.request(h.room.code,p.token,op,{round:rooms.rooms.get(h.room.code)?.round||0,...data});
 for(const p of [h,g])request(p,'ready',{ready:true});request(h,'start');for(const p of [h,g])request(p,'loaded');
 let sequence=0,applied=0,pending=0,seen=0;const started=performance.now(),sent=[],latencies=[];
 const state=p=>({id:p.playerId,position:[p===g?applied:0,0,0],angle:0,hp:100,maxHp:100,rage:0,pose:1,source:0,frame:0,serial:1,effectTime:0});
 const host=new NetworkClient({getFrame:()=>({sequence:++sequence,time:(performance.now()-started)/1000,players:[state(h),state(g)]}),onInput:batch=>{for(const x of batch)if(x.action==='attack')pending++;}});
 const guest=new NetworkClient({onFrame:frame=>{const count=frame.players.find(p=>p.id===g.playerId).position[0];while(seen<count){latencies.push(performance.now()-sent[seen]);seen++;}}});
 for(const [client,p] of [[host,h],[guest,g]]){Object.assign(client,{room:request(p,'sync').room,code:h.room.code,playerId:p.playerId,token:p.token});client.api=(path,data,auth)=>NetworkClient.prototype.api.call(client,base+path,data,auth);client.timer=setInterval(()=>client.sync(),interval);client.enableStream=push;client.streamUrl=path=>base+path;client.startStream();}
 const physics=setInterval(()=>{if(pending){applied+=pending;pending=0;if(immediate)host.flushFrame();}},1000/60);
 if(!immediate)guest.flushInput=()=>{};
 try{
  await delay(150);if(push&&(!host.streamActive||!guest.streamActive))throw Error('推送连接未建立');
  for(let i=0;i<16;i++){sent.push(performance.now());guest.send('attack');await delay(83);}
  for(let i=0;i<100&&seen<sent.length;i++)await delay(10);
  if(seen!==sent.length)throw Error('操作未全部回传');
  latencies.sort((a,b)=>a-b);return {intervalMs:interval,immediateInput:immediate,push,samples:seen,medianMs:+latencies[8].toFixed(2),p95Ms:+latencies[15].toFixed(2),hostApplied:applied};
 }finally{clearInterval(physics);await guest.leave();await host.leave();}
}
try{console.log(JSON.stringify({legacy:await measure(70,false),previous:await measure(NETWORK_SYNC_MS,true),push:await measure(NETWORK_SYNC_MS,true,true)},null,2));}
finally{server.closeAllConnections();await new Promise(resolve=>server.close(resolve));}

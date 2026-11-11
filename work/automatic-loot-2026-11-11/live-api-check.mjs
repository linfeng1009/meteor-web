import assert from 'node:assert/strict';
import {writeFile} from 'node:fs/promises';
const base=process.env.LOOT_TEST_URL||'http://127.0.0.1:4173';
async function post(path,body={},token){const response=await fetch(base+path,{method:'POST',headers:{'Content-Type':'application/json',...(token?{Authorization:'Bearer '+token}:{})},body:JSON.stringify(body)});return {status:response.status,data:await response.json()};}
const host=(await post('/api/rooms/create',{name:'拾取验收房主'})).data;
try{
  const guest=(await post('/api/rooms/join',{code:host.room.code,name:'拾取验收客人'})).data;
  const call=(player,op,data={})=>post(`/api/rooms/${host.room.code}/${op}`,{round:1,...data},player.token);
  assert.equal(host.room.protocol,3);await call(host,'ready',{ready:true});await call(guest,'ready',{ready:true});await call(host,'start');await call(host,'loaded');await call(guest,'loaded');
  const input=['switch','drop','pickup'].map((action,i)=>({action,active:true,angle:0,sequence:i+1,time:i}));
  assert.equal((await call(guest,'sync',{input})).status,200);await call(guest,'sync',{input});const batch=await call(host,'sync');assert.equal(batch.data.input.length,3);
  const frame={sequence:1,time:1,loot:{consumed:['D_Wpn01'],drops:[{name:'web-drop-1',weaponId:6,position:[0,0,0]}]},players:[host,guest].map(p=>({id:p.playerId,position:[0,0,0],angle:0,hp:1000,maxHp:1000,rage:0,pose:6,source:0,frame:7400,serial:1,effectTime:0,weaponId:6,weapon2Id:null,pickupSerial:1}))};
  assert.equal((await call(host,'sync',{frame,inputAck:{[guest.playerId]:3}})).status,200);
  assert.deepEqual((await call(guest,'sync')).data.frame.loot,frame.loot);assert.equal((await call(host,'sync')).data.input.length,0);
  assert.equal((await call(guest,'sync',{frame})).status,403);
  assert.equal((await call(host,'sync',{frame:{...frame,sequence:2,loot:{consumed:[],drops:[{name:'web-drop-1',weaponId:6,position:[null,0,0]}]}}})).status,400);
  const report={protocol:3,actions:['switch','drop','pickup'],duplicateRetryInputs:3,afterAcknowledgement:0,lootSnapshot:true,guestCannotPublish:true,invalidDropRejected:true};
  await writeFile(new URL('live-api-result.json',import.meta.url),JSON.stringify(report,null,2)+'\n');console.log(JSON.stringify(report));
}finally{await post(`/api/rooms/${host.room.code}/leave`,{},host.token);}

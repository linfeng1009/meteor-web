import {NETWORK_PROTOCOL,roomRules} from './dist/network-rules.js';
const validBloodStyle=s=>!!s&&['slash','thrust','impact','launch','shot'].includes(s.kind)&&Number.isInteger(s.level)&&s.level>=0&&s.level<=2;
import http from 'node:http';
import { battleCharacterSelection } from './dist/character-appearances.js';
import {randomBytes} from 'node:crypto';
import {readFile} from 'node:fs/promises';
import {resolve,extname,sep} from 'node:path';
import {fileURLToPath} from 'node:url';
const actions=new Set(['forward','back','left','right','attack','guard','jump','crouch','lock','clear','look','switch','drop','pickup']);
const token=()=>randomBytes(20).toString('hex');
const finite=n=>typeof n==='number'&&Number.isFinite(n);
const validReactionPhase=phase=>phase==null||['hit','guard','down','recover'].includes(phase);
const validWeaponMode=mode=>mode==null||['blade','spear','sheath'].includes(mode);
const validPoseBlend=(b,source,frame)=>b==null||b&&[b.from,b.to].every(d=>d&&Number.isInteger(d.source)&&d.source>=0&&d.source<=1&&finite(d.frame)&&d.frame>=0&&d.frame<=200000)&&b.to.source===source&&b.to.frame===frame&&finite(b.weight)&&b.weight>=0&&b.weight<=1&&finite(b.duration)&&b.duration>0&&b.duration<=2&&(b.fromSnapshot===undefined||typeof b.fromSnapshot==='boolean');
const validDeathContext=(s,time)=>s.context?.deathEffectTime===undefined||s.dead===true&&s.pose===469&&s.context.poseId===468&&finite(s.context.deathEffectTime)&&s.context.deathEffectTime>=0&&s.context.deathEffectTime<=30&&finite(s.context.deathEffectAt)&&s.context.deathEffectAt>=0&&s.context.deathEffectAt<=time+.001;
const weaponId=id=>Number.isInteger(id)&&id>0&&id<1000;
const validProjectileIdentity=(s,players)=>s&&['dart','wheel'].includes(s.kind)&&Number.isSafeInteger(s.id)&&s.id>0&&s.id<1e9&&players.some(p=>p.id===s.ownerId)&&weaponId(s.weaponId);
const validProjectilePosition=p=>Array.isArray(p)&&p.length===3&&p.every(n=>finite(n)&&Math.abs(n)<5000);
const validProjectileRotation=q=>Array.isArray(q)&&q.length===4&&q.every(n=>finite(n)&&Math.abs(n)<=1.001)&&Math.abs(Math.hypot(...q)-1)<.001;
const uniqueProjectiles=shots=>new Set(shots.map(s=>`${s?.kind}:${s?.id}`)).size===shots.length;
const validProjectiles=(shots,players)=>shots===undefined||Array.isArray(shots)&&shots.length<=80&&uniqueProjectiles(shots)&&shots.every(s=>validProjectileIdentity(s,players)&&['outbound','return'].includes(s.phase)&&(s.kind==='wheel'||s.phase==='outbound')&&validProjectilePosition(s.position)&&validProjectileRotation(s.quaternion)&&finite(s.spin)&&Math.abs(s.spin)<1e6);
const validShortFlights=(flights,players,time)=>flights===undefined||Array.isArray(flights)&&flights.length<=32&&uniqueProjectiles(flights)&&flights.every(f=>validProjectileIdentity(f,players)&&validProjectileRotation(f.quaternion)&&finite(f.startTime)&&f.startTime>=0&&finite(f.endTime)&&f.endTime>f.startTime&&f.endTime-f.startTime<=.250001&&f.endTime<=time+.001&&Array.isArray(f.points)&&f.points.length>=2&&f.points.length<=16&&f.points.every((p,i)=>p&&finite(p.time)&&p.time>=f.startTime&&p.time<=f.endTime&&(!i||p.time>f.points[i-1].time)&&validProjectilePosition(p.position)&&finite(p.spin)&&Math.abs(p.spin)<1e6)&&Math.abs(f.points[0].time-f.startTime)<1e-6&&Math.abs(f.points.at(-1).time-f.endTime)<1e-6);
const validImpacts=(events,time)=>events===undefined||Array.isArray(events)&&events.length<=32&&events.every((e,i)=>e&&Number.isSafeInteger(e.id)&&e.id>0&&(!i||e.id>events[i-1].id)&&finite(e.time)&&e.time>=0&&e.time<=time+.001&&(e.projectile===undefined||e.projectile&&['dart','wheel'].includes(e.projectile.kind)&&Number.isSafeInteger(e.projectile.id)&&e.projectile.id>0&&e.projectile.id<1e9)&&Array.isArray(e.point)&&e.point.length===3&&e.point.every(n=>finite(n)&&Math.abs(n)<5000)&&Array.isArray(e.direction)&&e.direction.length===3&&e.direction.every(n=>finite(n)&&Math.abs(n)<=1.01)&&['guarded','knockdown','blood'].every(key=>typeof e[key]==='boolean')&&(!e.guarded||!e.blood)&&(e.bloodStyle===undefined||e.blood&&validBloodStyle(e.bloodStyle))&&(e.sound==null||typeof e.sound==='string'&&/^W\d{2}(BL|GD)\d{3}$/.test(e.sound))&&['attackerId','targetId'].every(key=>e[key]===undefined||typeof e[key]==='string'&&e[key].length<=32));
const validInventory=s=>!!s&&(s.weaponId===undefined||weaponId(s.weaponId))&&(s.weapon2Id===undefined||s.weapon2Id===null||s.weapon2Id===0||weaponId(s.weapon2Id))&&(s.pickupSerial===undefined||Number.isSafeInteger(s.pickupSerial)&&s.pickupSerial>=0&&s.pickupSerial<1e9)&&(s.statuses===undefined||Array.isArray(s.statuses)&&s.statuses.length<=32&&s.statuses.every(item=>item&&Number.isInteger(item.id)&&typeof item.name==='string'&&item.name.length<=128&&[item.statKey,item.remaining,item.value,item.period].every(finite)));
const validLoot=loot=>loot===undefined||!!loot&&Array.isArray(loot.consumed)&&loot.consumed.length<=512&&loot.consumed.every(name=>typeof name==='string'&&name.length<=128)&&Array.isArray(loot.drops)&&loot.drops.length<=64&&new Set(loot.drops.map(drop=>drop?.name)).size===loot.drops.length&&loot.drops.every(drop=>drop&&typeof drop.name==='string'&&/^web-drop-\d{1,12}$/.test(drop.name)&&weaponId(drop.weaponId)&&Array.isArray(drop.position)&&drop.position.length===3&&drop.position.every(n=>finite(n)&&Math.abs(n)<5000));
const fail=(message,status=400)=>{throw Object.assign(Error(message),{status});};
export class NetworkRooms{
  constructor({now=()=>Date.now()}={}){this.rooms=new Map();this.now=now;}
  list(){this.sweep();return {rooms:[...this.rooms.values()].map(r=>({code:r.code,hostName:r.players[0].name,mode:r.rules.mode,players:r.players.length,maxPlayers:r.rules.maxPlayers,phase:r.phase}))};}
  public(room){return {code:room.code,revision:room.revision||0,round:room.round||0,protocol:NETWORK_PROTOCOL,...room.rules,phase:room.phase,hostId:room.hostId,map:'sifang',result:room.result||null,scores:(room.frame?.players||[]).map(p=>({id:p.id,kills:p.kills||0,deaths:p.deaths||0,dead:!!p.dead})),players:room.players.map(p=>({id:p.id,name:p.name,ready:p.ready,loaded:p.loaded,team:p.team,selection:p.selection}))};}

  remove(room,player){
    (room.removedIds||=new Set()).add(player.id);room.players=room.players.filter(p=>p!==player);if(room.phase!=='finished')room.frame=null;room.revision=(room.revision||0)+1;
    if(room.phase==='loading'||room.phase==='waiting'){room.phase='waiting';for(const p of room.players){p.ready=false;p.loaded=false;}}
  }
  sweep(){for(const [code,r] of this.rooms){if(this.now()-r.players[0].seen>20000)this.rooms.delete(code);else for(const p of [...r.players].slice(1))if(this.now()-p.seen>20000)this.remove(r,p);}}
  player(name,selection){return {id:token().slice(0,12),token:token(),name:String(name||'江湖来客').trim().slice(0,16)||'江湖来客',selection:battleCharacterSelection(selection),seen:this.now(),ready:false,loaded:false,input:[],lastSequence:0,deliveredSequence:0,ackSequence:0};}
  create(name,options={}){this.sweep();if(this.rooms.size>=32)fail('房间数量已达上限');let rules;try{rules=roomRules(options);}catch{fail('房间规则无效');}const p=this.player(name,options.selection);p.team=1;let code;do{code=randomBytes(3).toString('hex').toUpperCase();}while(this.rooms.has(code));const r={code,hostId:p.id,phase:'waiting',rules,players:[p],frame:null,frameSequence:0};this.rooms.set(code,r);return {room:this.public(r),playerId:p.id,token:p.token};}
  join(code,name,selection){this.sweep();const r=this.rooms.get(code);if(!r)fail('房间不存在或房主已离开',404);if(r.phase!=='waiting'||r.players.length>=r.rules.maxPlayers)fail('房间已满或已经开局',409);const p=this.player(name,selection);p.team=r.players.filter(x=>x.team===1).length<=r.players.filter(x=>x.team===2).length?1:2;r.players.push(p);for(const x of r.players)x.ready=false;r.revision=(r.revision||0)+1;return {room:this.public(r),playerId:p.id,token:p.token};}
  request(code,credential,operation,data={}){
    this.sweep();const r=this.rooms.get(code);if(!r)fail('房间已关闭',404);const p=r.players.find(p=>p.token===credential);if(!p)fail('房间身份无效',403);p.seen=this.now();
    const host=p.id===r.hostId;
    if(operation==='team'){if(r.phase!=='waiting'||![1,2].includes(data.team))fail('当前不能切换队伍');p.team=data.team;for(const x of r.players)x.ready=false;}
    else if(operation==='ready'){if(r.phase!=='waiting')fail('对战已开始');p.ready=data.ready===true;}
    else if(operation==='start'){if(!host)fail('只有房主可以开局',403);if(r.players.length<2||!r.players.every(p=>p.ready))fail('至少两名玩家且所有玩家均需准备');if(r.rules.mode==='deathmatch'&&new Set(r.players.map(p=>p.team)).size!==2)fail('死斗需要红蓝两队均有玩家');r.round=(r.round||0)+1;r.phase='loading';r.frame=null;r.result=null;r.frameSequence=0;for(const x of r.players){x.loaded=false;x.input=[];x.lastSequence=0;x.deliveredSequence=0;x.ackSequence=0;x.lastInputTime=null;}}
    else if(operation==='rematch'){if(!host||r.phase!=='finished')fail('当前不能重开',409);r.phase='waiting';r.frame=null;r.result=null;for(const x of r.players){x.ready=false;x.loaded=false;}}
    else if(operation==='loaded'){if(r.phase!=='loading')fail('当前不在载入阶段');p.loaded=true;if(r.players.every(p=>p.loaded))r.phase='playing';}
    else if(operation==='leave'){if(host)this.rooms.delete(code);else this.remove(r,p);return {left:true};}
    else if(operation==='sync'){
      if((data.input!==undefined||data.frame!==undefined||data.inputAck!==undefined)&&data.round!==(r.round||0))fail('对局已变化，请重新进入房间',409);
      if(r.phase!=='playing')return {room:this.public(r),input:[],acceptedSequence:p.lastSequence,frame:r.phase==='finished'&&!host?r.frame:null};
      if(host&&Array.isArray(data.frame?.players)&&data.frame.players.some(s=>r.removedIds?.has(s.id)))return {room:this.public(r),input:[],acceptedSequence:p.lastSequence,frame:null};
      const additions=[],acknowledgements=[];
      if(data.input!==undefined){
        if(host||r.phase!=='playing')fail('当前不能提交操作',409);
        if(!Array.isArray(data.input)||data.input.length>64)fail('输入批次无效');
        let sequence=p.lastSequence,order=0,inputTime=p.lastInputTime;
        for(const input of data.input){
          if(!input||!actions.has(input.action)||typeof input.active!=='boolean'||!Number.isSafeInteger(input.sequence)||input.sequence<1||input.sequence<order||(input.pitch!==undefined&&(!finite(input.pitch)||Math.abs(input.pitch)>1.2))||!finite(input.angle)||Math.abs(input.angle)>1e6||(input.held!==undefined&&(!Array.isArray(input.held)||input.held.length>7||input.held.some(a=>!['forward','back','left','right','guard','crouch'].includes(a)))))fail('操作输入无效');
          if(input.time!==undefined&&(!finite(input.time)||input.time<0||input.time>1e9))fail('操作时间无效');
          order=input.sequence;if(input.sequence<=sequence)continue;
          if(input.time!==undefined){if(inputTime!=null&&input.time<inputTime)fail('操作时间无效');inputTime=input.time;}
          sequence=input.sequence;additions.push({...input,held:input.held?[...input.held]:undefined,playerId:p.id});
        }
        if(p.input.length+additions.length>256)fail('房主操作确认积压，请重试',409);
      }
      if(data.inputAck!==undefined){
        if(!host)fail('只有房主能确认操作',403);
        if(!data.inputAck||typeof data.inputAck!=='object'||Array.isArray(data.inputAck))fail('操作确认无效');
        for(const [id,sequence] of Object.entries(data.inputAck)){
          if(r.removedIds?.has(id))continue;const peer=r.players.find(x=>x.id===id&&x!==p);
          if(!peer||!Number.isSafeInteger(sequence)||sequence<0||sequence>peer.deliveredSequence)fail('操作确认无效');
          acknowledgements.push([peer,sequence]);
        }
      }
      if(data.frame!==undefined){if(!host)fail('只有房主能发布战斗状态',403);if(r.phase!=='playing')fail('对战尚未开始');const frame=data.frame;if(!frame||!validImpacts(frame.impacts,frame.time)||!validProjectiles(frame.projectiles,r.players)||!validShortFlights(frame.projectileFlights,r.players,frame.time)||!validLoot(frame.loot)||!Number.isSafeInteger(frame.sequence)||frame.sequence<=r.frameSequence||!Array.isArray(frame.players)||frame.players.length!==r.players.length||new Set(frame.players.map(p=>p.id)).size!==r.players.length||!finite(frame.time)||frame.time<0||r.frame&&frame.time<r.frame.time||frame.players.some(s=>!validInventory(s)||!validReactionPhase(s.reactionPhase)||!validWeaponMode(s.weaponMode)||!validPoseBlend(s.blend,s.source,s.frame)||!validDeathContext(s,frame.time)||(s.queuedMoveName!==undefined&&s.queuedMoveName!==null&&(typeof s.queuedMoveName!=='string'||s.queuedMoveName.length>64))||(s.lockTargetId!==undefined&&s.lockTargetId!==null&&(!r.players.some(p=>p.id===s.lockTargetId)||s.lockTargetId===s.id))||(s.autoLockEnabled!==undefined&&typeof s.autoLockEnabled!=='boolean')||(s.musketAim!==undefined&&typeof s.musketAim!=='boolean')||(s.aimPitch!==undefined&&(!finite(s.aimPitch)||Math.abs(s.aimPitch)>1.2))||!r.players.some(p=>p.id===s.id)||!Array.isArray(s.position)||s.position.length!==3||!s.position.every(n=>finite(n)&&Math.abs(n)<5000)||!finite(s.angle)||!finite(s.hp)||!finite(s.maxHp)||s.maxHp<=0||!finite(s.rage)||!Number.isInteger(s.pose)||!finite(s.frame)||!Number.isInteger(s.source)||!Number.isInteger(s.serial)||!finite(s.effectTime)))fail('战斗状态无效');if(frame.result!==undefined&&frame.result!==null&&(!['score','time','elimination','departure'].includes(frame.result.reason)||!Array.isArray(frame.result.winnerIds)||new Set(frame.result.winnerIds).size!==frame.result.winnerIds.length||frame.result.winnerIds.some(id=>!r.players.some(p=>p.id===id))))fail('结算状态无效');r.frame=frame;r.frameSequence=frame.sequence;if(frame.result){r.result=frame.result;r.phase='finished';r.revision=(r.revision||0)+1;}}
      // Commit only after every field is validated: a rejected request must
      // neither consume operations nor partially accept an input batch.
      if(additions.length){p.input.push(...additions);p.lastSequence=additions.at(-1).sequence;for(const input of additions)if(input.time!==undefined)p.lastInputTime=input.time;}
      for(const [peer,sequence] of acknowledgements){peer.ackSequence=Math.max(peer.ackSequence,sequence);peer.input=peer.input.filter(x=>x.sequence>peer.ackSequence);}
    }else fail('未知房间操作',404);
    if(operation!=='sync')r.revision=(r.revision||0)+1;
    const input=host&&operation==='sync'&&r.phase==='playing'?r.players.filter(x=>x!==p).flatMap(x=>{
      const q=x.input.map(input=>({...input,held:input.held?[...input.held]:undefined}));
      if(q.length)x.deliveredSequence=Math.max(x.deliveredSequence,q.at(-1).sequence);
      if(this.now()-x.seen>1500)q.push({playerId:x.id,action:'clear',active:false,angle:0,sequence:0});return q;
    }):[];
    return {room:this.public(r),input,acceptedSequence:p.lastSequence,frame:host?null:r.frame};
  }
}
const types={'.html':'text/html; charset=utf-8','.js':'text/javascript; charset=utf-8','.css':'text/css; charset=utf-8','.json':'application/json; charset=utf-8','.png':'image/png','.jpg':'image/jpeg','.bmp':'image/bmp','.svg':'image/svg+xml','.mp3':'audio/mpeg','.wav':'audio/wav','.webp':'image/webp'};
export function createNetworkServer({rooms=new NetworkRooms(),root=fileURLToPath(new URL('./dist/',import.meta.url))}={}){
  return http.createServer(async(req,res)=>{
    const json=(status,data)=>{res.writeHead(status,{'Content-Type':'application/json; charset=utf-8','Cache-Control':'no-store','X-Content-Type-Options':'nosniff'});res.end(JSON.stringify(data));};
    try{
      const url=new URL(req.url,'http://localhost');
      if(url.pathname.startsWith('/api/')){
        if(req.method!=='POST')fail('只接受POST',405);if(req.headers.origin&&new URL(req.headers.origin).host!==req.headers.host)fail('不允许跨站请求',403);
        let raw='',size=0;for await(const chunk of req){size+=chunk.length;if(size>262144)fail('请求过大',413);raw+=chunk;}let data;try{data=JSON.parse(raw||'{}');}catch{fail('JSON无效');}
        let result;if(url.pathname==='/api/rooms/list')result=rooms.list();else if(url.pathname==='/api/rooms/create')result=rooms.create(data.name,data);else if(url.pathname==='/api/rooms/join')result=rooms.join(String(data.code||'').toUpperCase(),data.name,data.selection);else{const match=url.pathname.match(/^\/api\/rooms\/([A-F0-9]{6})\/(ready|start|loaded|sync|leave|team|rematch)$/);if(!match)fail('接口不存在',404);result=rooms.request(match[1],req.headers.authorization?.replace(/^Bearer /,''),match[2],data);}json(200,result);return;

      }
      if(!['GET','HEAD'].includes(req.method))fail('方法不允许',405);
      const target=resolve(root,'.'+decodeURIComponent(url.pathname==='/'?'/index.html':url.pathname));if(!target.startsWith(root.endsWith(sep)?root:root+sep))fail('禁止访问',403);
      const body=await readFile(target);res.writeHead(200,{'Content-Type':types[extname(target)]||'application/octet-stream','Cache-Control':'no-cache','X-Content-Type-Options':'nosniff'});res.end(req.method==='HEAD'?undefined:body);
    }catch(error){json(error.status|| (error.code==='ENOENT'?404:500),{error:error.status?error.message:error.code==='ENOENT'?'文件不存在':'服务器处理失败'});}
  });
}
export function startNetworkServers(){
  const rooms=new NetworkRooms(),port=Number(process.env.PORT)||4173;
  for(const host of [...new Set([process.env.HOST||'127.0.0.1',process.env.LAN_HOST].filter(Boolean))]){
    const server=createNetworkServer({rooms});server.on('error',e=>console.error(`联机服务监听失败：${e.code}`));server.listen(port,host,()=>console.log(`联机开发版 http://${host}:${port}/`));
  }
}

if(process.argv[1]&&resolve(process.argv[1])===fileURLToPath(import.meta.url))startNetworkServers();

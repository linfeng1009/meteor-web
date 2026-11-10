import http from 'node:http';
import {randomBytes} from 'node:crypto';
import {readFile} from 'node:fs/promises';
import {resolve,extname,sep} from 'node:path';
import {fileURLToPath} from 'node:url';
const actions=new Set(['forward','back','left','right','attack','guard','jump','crouch','lock','clear','look']);
const token=()=>randomBytes(20).toString('hex');
const finite=n=>typeof n==='number'&&Number.isFinite(n);
const fail=(message,status=400)=>{throw Object.assign(Error(message),{status});};
export class NetworkRooms{
  constructor({now=()=>Date.now()}={}){this.rooms=new Map();this.now=now;}
  public(room){return {code:room.code,revision:room.revision||0,round:room.round||0,protocol:2,phase:room.phase,hostId:room.hostId,map:'sifang',mode:'duel',players:room.players.map(p=>({id:p.id,name:p.name,ready:p.ready,loaded:p.loaded}))};}
  sweep(){for(const [code,r] of this.rooms){if(this.now()-r.players[0].seen>20000)this.rooms.delete(code);else if(r.players.length===2&&this.now()-r.players[1].seen>20000){r.players.pop();r.phase='waiting';r.frame=null;r.players[0].ready=false;r.players[0].loaded=false;r.revision=(r.revision||0)+1;}}}
  player(name){return {id:token().slice(0,12),token:token(),name:String(name||'江湖来客').trim().slice(0,16)||'江湖来客',seen:this.now(),ready:false,loaded:false,input:[],lastSequence:0,deliveredSequence:0,ackSequence:0};}
  create(name){this.sweep();if(this.rooms.size>=32)fail('房间数量已达上限');const p=this.player(name);let code;do{code=randomBytes(3).toString('hex').toUpperCase();}while(this.rooms.has(code));const r={code,hostId:p.id,phase:'waiting',players:[p],frame:null,frameSequence:0};this.rooms.set(code,r);return {room:this.public(r),playerId:p.id,token:p.token};}
  join(code,name){this.sweep();const r=this.rooms.get(code);if(!r)fail('房间不存在或房主已离开',404);if(r.phase!=='waiting'||r.players.length>=2)fail('房间已满或已经开局',409);const p=this.player(name);r.players.push(p);r.players[0].ready=false;r.revision=(r.revision||0)+1;return {room:this.public(r),playerId:p.id,token:p.token};}
  request(code,credential,operation,data={}){
    this.sweep();const r=this.rooms.get(code);if(!r)fail('房间已关闭',404);const p=r.players.find(p=>p.token===credential);if(!p)fail('房间身份无效',403);p.seen=this.now();
    const host=p.id===r.hostId;
    if(operation==='ready'){if(r.phase!=='waiting')fail('对战已开始');p.ready=data.ready===true;}
    else if(operation==='start'){if(!host)fail('只有房主可以开局',403);if(r.players.length!==2||!r.players.every(p=>p.ready))fail('需要两名玩家均准备');r.round=(r.round||0)+1;r.phase='loading';r.frame=null;r.frameSequence=0;for(const x of r.players){x.loaded=false;x.input=[];x.lastSequence=0;x.deliveredSequence=0;x.ackSequence=0;}}
    else if(operation==='loaded'){if(r.phase!=='loading')fail('当前不在载入阶段');p.loaded=true;if(r.players.every(p=>p.loaded))r.phase='playing';}
    else if(operation==='leave'){if(host)this.rooms.delete(code);else{r.players=r.players.filter(x=>x!==p);r.phase='waiting';r.frame=null;r.players[0].ready=false;r.players[0].loaded=false;r.revision=(r.revision||0)+1;}return {left:true};}
    else if(operation==='sync'){
      if((data.input!==undefined||data.frame!==undefined||data.inputAck!==undefined)&&data.round!==(r.round||0))fail('对局已变化，请重新进入房间',409);
      if(r.phase!=='playing')return {room:this.public(r),input:[],acceptedSequence:p.lastSequence,frame:null};
      const additions=[],acknowledgements=[];
      if(data.input!==undefined){
        if(host||r.phase!=='playing')fail('当前不能提交操作',409);
        if(!Array.isArray(data.input)||data.input.length>64)fail('输入批次无效');
        let sequence=p.lastSequence,order=0;
        for(const input of data.input){
          if(!input||!actions.has(input.action)||typeof input.active!=='boolean'||!Number.isSafeInteger(input.sequence)||input.sequence<1||input.sequence<order||!finite(input.angle)||Math.abs(input.angle)>1e6||(input.held!==undefined&&(!Array.isArray(input.held)||input.held.length>7||input.held.some(a=>!['forward','back','left','right','guard','crouch'].includes(a)))))fail('操作输入无效');
          order=input.sequence;if(input.sequence<=sequence)continue;
          sequence=input.sequence;additions.push({...input,held:input.held?[...input.held]:undefined,playerId:p.id});
        }
        if(p.input.length+additions.length>256)fail('房主操作确认积压，请重试',409);
      }
      if(data.inputAck!==undefined){
        if(!host)fail('只有房主能确认操作',403);
        if(!data.inputAck||typeof data.inputAck!=='object'||Array.isArray(data.inputAck))fail('操作确认无效');
        for(const [id,sequence] of Object.entries(data.inputAck)){
          const peer=r.players.find(x=>x.id===id&&x!==p);
          if(!peer||!Number.isSafeInteger(sequence)||sequence<0||sequence>peer.deliveredSequence)fail('操作确认无效');
          acknowledgements.push([peer,sequence]);
        }
      }
      if(data.frame!==undefined){if(!host)fail('只有房主能发布战斗状态',403);if(r.phase!=='playing')fail('对战尚未开始');const frame=data.frame;if(!frame||!Number.isSafeInteger(frame.sequence)||frame.sequence<=r.frameSequence||!Array.isArray(frame.players)||frame.players.length!==2||new Set(frame.players.map(p=>p.id)).size!==2||!finite(frame.time)||frame.players.some(s=>!r.players.some(p=>p.id===s.id)||!Array.isArray(s.position)||s.position.length!==3||!s.position.every(n=>finite(n)&&Math.abs(n)<5000)||!finite(s.angle)||!finite(s.hp)||!finite(s.maxHp)||s.maxHp<=0||!finite(s.rage)||!Number.isInteger(s.pose)||!finite(s.frame)||!Number.isInteger(s.source)||!Number.isInteger(s.serial)||!finite(s.effectTime)))fail('战斗状态无效');r.frame=frame;r.frameSequence=frame.sequence;}
      // Commit only after every field is validated: a rejected request must
      // neither consume operations nor partially accept an input batch.
      if(additions.length){p.input.push(...additions);p.lastSequence=additions.at(-1).sequence;}
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
        let raw='',size=0;for await(const chunk of req){size+=chunk.length;if(size>32000)fail('请求过大',413);raw+=chunk;}let data;try{data=JSON.parse(raw||'{}');}catch{fail('JSON无效');}
        let result;if(url.pathname==='/api/rooms/create')result=rooms.create(data.name);else if(url.pathname==='/api/rooms/join')result=rooms.join(String(data.code||'').toUpperCase(),data.name);else{const match=url.pathname.match(/^\/api\/rooms\/([A-F0-9]{6})\/(ready|start|loaded|sync|leave)$/);if(!match)fail('接口不存在',404);result=rooms.request(match[1],req.headers.authorization?.replace(/^Bearer /,''),match[2],data);}json(200,result);return;
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

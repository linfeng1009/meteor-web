import {NETWORK_PROTOCOL} from './network-rules.js';
import {NetworkPushStream} from './network-push-stream.js';
const continuous=['forward','back','left','right','guard','crouch'];
export const NETWORK_SYNC_MS=1000/30;
export class NetworkClient{
  constructor({onRoom=()=>{},onInput=()=>{},onFrame=()=>{},onError=()=>{},getFrame=()=>null,getAngle=()=>0,getPitch=()=>0,now=()=>performance.now()/1000,stream=typeof window!=='undefined',streamUrl=path=>path}={}){
    Object.assign(this,{onRoom,onInput,onFrame,onError,getFrame,getAngle,getPitch,now});this.resetInput();this.failures=0;this.closed=false;
    this.enableStream=stream;this.streamUrl=streamUrl;
  }
  resetInput(){this.queue=[];this.held=new Set();this.pendingInput=null;this.sequence=0;this.processed=new Map();this.lastReceivedFrameSequence=0;}
  setRoom(room){
    if(room.protocol!==NETWORK_PROTOCOL||!Number.isSafeInteger(room.round)||!Number.isSafeInteger(room.revision??0)||(room.revision??0)<0)throw Error('联机协议已更新，请重启服务并刷新所有玩家页面。');
    if(this.room?.code===room.code&&(room.round<this.room.round||room.round===this.room.round&&(room.revision??0)<(this.room.revision??0)))return false;
    if(this.room?.round!==room.round)this.resetInput();this.room=room;for(const id of this.processed.keys())if(!room.players.some(p=>p.id===id))this.processed.delete(id);this.onRoom(room);return true;
  }
  fail(message){if(this.closed)return;this.closed=true;this.streamer?.stop();clearInterval(this.timer);this.resetInput();this.onError(message);}
  async api(path,data={},auth=false){
    const controller=typeof AbortController==='function'?new AbortController():null;let timer;
    const deadline=new Promise((_,reject)=>{timer=setTimeout(()=>{reject(Error('连接超时，请确认使用同一个局域网游戏地址后重试。'));controller?.abort();},6000);});
    try{return await Promise.race([deadline,(async()=>{
      const response=await fetch(path,{method:'POST',headers:{'Content-Type':'application/json',...(auth?{Authorization:'Bearer '+this.token}:{})},body:JSON.stringify(data),...(controller?{signal:controller.signal}:{})});
      if(!response.headers.get('Content-Type')?.includes('application/json'))throw Error('当前服务未启用联机，请重启开发服务后刷新。');
      const result=await response.json();if(!response.ok)throw Error(result.error||'联机请求失败');return result;
    })()]);}catch(error){if(error instanceof TypeError)throw Error('无法连接联机服务，请确认大家使用同一个局域网游戏地址。');throw error;}finally{clearTimeout(timer);}
  }

  async connect(kind,data){
    const result=await this.api('/api/rooms/'+kind,data);
    Object.assign(this,{token:result.token,playerId:result.playerId,code:result.room.code});
    // A room may be created after the user has already left the connecting UI.
    // Release that server identity without callbacks or a resurrected timer.
    if(this.closed){try{await this.command('leave');}catch{}return null;}
    try{this.setRoom(result.room);}catch(error){await this.leave().catch(()=>{});throw error;}
    if(this.closed)return null;
    this.timer=setInterval(()=>this.sync(),NETWORK_SYNC_MS);this.startStream();return result;
  }
  startStream(){
    if(this.closed||!this.enableStream||this.room?.stream!==1||this.streamer)return;
    const code=this.code;
    this.streamer=new NetworkPushStream({url:this.streamUrl(`/api/rooms/${code}/events`),token:this.token,
      onStatus:active=>{this.streamActive=active&&!this.closed;},onPacket:result=>{
        if(this.closed||this.code!==code||result.room?.code!==code)return;
        try{if(!this.setRoom(result.room))return;if(this.closed)return;
          if(result.room.phase==='playing'&&this.host)this.applyInputs(result.input||[]);
          if(result.frame)this.deliverFrame(result.frame);
        }catch(error){this.fail('联机状态处理失败：'+error.message);}
      }});this.streamer.start();
  }
  deliverFrame(frame){
    if(frame.sequence<=this.lastReceivedFrameSequence)return;
    this.lastReceivedFrameSequence=frame.sequence;this.onFrame(frame);
  }
  applyInputs(inputs){
    for(const input of inputs){const previous=this.processed.get(input.playerId)||0;
      if(input.sequence!==0&&input.sequence<=previous)continue;
      this.onInput([input]);if(input.sequence>0)this.processed.set(input.playerId,input.sequence);
    }
  }
  get host(){return this.room?.hostId===this.playerId;}
  async command(action,data={}){const result=await this.api(`/api/rooms/${this.code}/${action}`,data,true);if(!this.closed&&result.room)this.setRoom(result.room);return result;}
  send(action,active=true){
    if(this.closed||this.host||this.room?.phase!=='playing')return;
    // Never silently discard queued attacks. Close explicitly on overload.
    if(this.queue.length+(this.pendingInput?.length||0)>=256){this.fail('联机操作积压过多，本局已断开，请重新加入。');return;}
    if(continuous.includes(action)){if(active)this.held.add(action);else this.held.delete(action);}if(action==='clear')this.held.clear();
    this.queue.push({action,active:!!active,sequence:++this.sequence,angle:this.getAngle(),pitch:this.getPitch(),time:this.now()});
    this.flushInput();
  }
  // Coalesce events from the same task, but do not make a key press wait for
  // the next poll. One in-flight request still owns its exact retry batch.
  flushInput(){
    if(!this.timer||this.closed||this.host||this.room?.phase!=='playing'||!this.queue.length||this.inputScheduled)return;
    this.inputScheduled=true;queueMicrotask(()=>{this.inputScheduled=false;this.sync();});
  }
  // Called after the host has actually simulated a newly received input.
  // Publish that result without another full polling interval of latency.
  flushFrame(){
    if(!this.timer||this.closed||!this.host||this.room?.phase!=='playing')return;
    this.frameDirty=true;
    if(this.busy||this.frameScheduled)return;
    this.frameScheduled=true;queueMicrotask(()=>{this.frameScheduled=false;this.sync();});
  }
  async sync(){
    if(this.busy||this.closed||!this.code)return;this.busy=true;
    const code=this.code,round=this.room.round,playing=this.room.phase==='playing',host=this.host,data={};
    try{
      if(playing){
        data.round=round;
        if(host){this.frameDirty=false;data.inputAck=Object.fromEntries(this.processed);const frame=this.getFrame();if(frame)data.frame=frame;}
        else{
          // A later look sequence must never jump ahead of queued operations.
          if(!this.pendingInput){this.pendingInput=this.queue.splice(0,63);if(!this.queue.length)this.pendingInput.push({action:'look',active:false,sequence:++this.sequence,angle:this.getAngle(),pitch:this.getPitch(),time:this.now(),held:[...this.held]});}
          data.input=this.pendingInput;if(this.streamActive)data.afterFrame=this.lastReceivedFrameSequence;
        }
      }
      let result;
      try{result=await this.api(`/api/rooms/${code}/sync`,data,true);}
      catch(error){if(!this.closed&&this.code===code&&this.room.round===round&&++this.failures>=3)this.fail(error.message);return;}
      // Discard responses belonging to a room or round which is no longer active.
      if(this.closed||this.code!==code||this.room.round!==round)return;
      this.failures=0;if(!this.setRoom(result.room))return;
      if(this.closed||result.room.round!==round)return;if(result.room.phase==='finished'){if(result.frame)this.deliverFrame(result.frame);return;}if(result.room.phase!=='playing')return;
      if(!host&&playing){
        const last=this.pendingInput?.at(-1)?.sequence||0;
        if(!Number.isSafeInteger(result.acceptedSequence)||result.acceptedSequence<last)throw Error('服务未确认完整操作批次，本局已停止。');
        this.pendingInput=null;
      }
      if(host)this.applyInputs(result.input||[]);
      if(result.frame)this.deliverFrame(result.frame);
    }catch(error){this.fail('联机状态处理失败：'+error.message);}
    finally{this.busy=false;if(!this.pendingInput)this.flushInput();if(this.frameDirty)this.flushFrame();}
  }
  async leave(){this.closed=true;this.streamer?.stop();clearInterval(this.timer);this.resetInput();if(this.code)await this.command('leave');}
}

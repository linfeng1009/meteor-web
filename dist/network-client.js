const continuous=['forward','back','left','right','guard','crouch'];
export class NetworkClient{
  constructor({onRoom=()=>{},onInput=()=>{},onFrame=()=>{},onError=()=>{},getFrame=()=>null,getAngle=()=>0,now=()=>performance.now()/1000}={}){
    Object.assign(this,{onRoom,onInput,onFrame,onError,getFrame,getAngle,now});this.resetInput();this.failures=0;this.closed=false;
  }
  resetInput(){this.queue=[];this.held=new Set();this.pendingInput=null;this.sequence=0;this.processed=new Map();}
  setRoom(room){
    if(room.protocol!==2||!Number.isSafeInteger(room.round)||!Number.isSafeInteger(room.revision??0)||(room.revision??0)<0)throw Error('联机协议已更新，请重启服务并刷新双方页面。');
    if(this.room?.code===room.code&&(room.round<this.room.round||room.round===this.room.round&&(room.revision??0)<(this.room.revision??0)))return false;
    if(this.room?.round!==room.round)this.resetInput();this.room=room;this.onRoom(room);return true;
  }
  fail(message){if(this.closed)return;this.closed=true;clearInterval(this.timer);this.resetInput();this.onError(message);}
  async api(path,data={},auth=false){const response=await fetch(path,{method:'POST',headers:{'Content-Type':'application/json',...(auth?{Authorization:'Bearer '+this.token}:{})},body:JSON.stringify(data),signal:AbortSignal.timeout(6000)});if(!response.headers.get('Content-Type')?.includes('application/json'))throw Error('当前服务未启用联机，请重启开发服务后刷新。');const result=await response.json();if(!response.ok)throw Error(result.error||'联机请求失败');return result;}
  async connect(kind,data){
    const result=await this.api('/api/rooms/'+kind,data);
    Object.assign(this,{token:result.token,playerId:result.playerId,code:result.room.code});
    // A room may be created after the user has already left the connecting UI.
    // Release that server identity without callbacks or a resurrected timer.
    if(this.closed){try{await this.command('leave');}catch{}return null;}
    try{this.setRoom(result.room);}catch(error){await this.leave().catch(()=>{});throw error;}
    if(this.closed)return null;
    this.timer=setInterval(()=>this.sync(),70);return result;
  }
  get host(){return this.room?.hostId===this.playerId;}
  async command(action,data={}){const result=await this.api(`/api/rooms/${this.code}/${action}`,data,true);if(!this.closed&&result.room)this.setRoom(result.room);return result;}
  send(action,active=true){
    if(this.closed||this.host||this.room?.phase!=='playing')return;
    // Never silently discard queued attacks. Close explicitly on overload.
    if(this.queue.length+(this.pendingInput?.length||0)>=256){this.fail('联机操作积压过多，本局已断开，请重新加入。');return;}
    if(continuous.includes(action)){if(active)this.held.add(action);else this.held.delete(action);}if(action==='clear')this.held.clear();
    this.queue.push({action,active:!!active,sequence:++this.sequence,angle:this.getAngle(),time:this.now()});
  }
  async sync(){
    if(this.busy||this.closed||!this.code)return;this.busy=true;
    const code=this.code,round=this.room.round,playing=this.room.phase==='playing',host=this.host,data={};
    try{
      if(playing){
        data.round=round;
        if(host){data.inputAck=Object.fromEntries(this.processed);const frame=this.getFrame();if(frame)data.frame=frame;}
        else{
          // A later look sequence must never jump ahead of queued operations.
          if(!this.pendingInput){this.pendingInput=this.queue.splice(0,63);if(!this.queue.length)this.pendingInput.push({action:'look',active:false,sequence:++this.sequence,angle:this.getAngle(),time:this.now(),held:[...this.held]});}
          data.input=this.pendingInput;
        }
      }
      let result;
      try{result=await this.api(`/api/rooms/${code}/sync`,data,true);}
      catch(error){if(!this.closed&&this.code===code&&this.room.round===round&&++this.failures>=3)this.fail(error.message);return;}
      // Discard responses belonging to a room or round which is no longer active.
      if(this.closed||this.code!==code||this.room.round!==round)return;
      this.failures=0;if(!this.setRoom(result.room))return;
      if(this.closed||result.room.phase!=='playing'||result.room.round!==round)return;
      if(!host&&playing){
        const last=this.pendingInput?.at(-1)?.sequence||0;
        if(!Number.isSafeInteger(result.acceptedSequence)||result.acceptedSequence<last)throw Error('服务未确认完整操作批次，本局已停止。');
        this.pendingInput=null;
      }
      if(host)for(const input of result.input||[]){
        const previous=this.processed.get(input.playerId)||0;
        if(input.sequence!==0&&input.sequence<=previous)continue;
        this.onInput([input]);
        // Confirm successful application, not merely receipt of the response.
        if(input.sequence>0)this.processed.set(input.playerId,input.sequence);
      }
      if(result.frame)this.onFrame(result.frame);
    }catch(error){this.fail('联机状态处理失败：'+error.message);}
    finally{this.busy=false;}
  }
  async leave(){this.closed=true;clearInterval(this.timer);this.resetInput();if(this.code)await this.command('leave');}
}

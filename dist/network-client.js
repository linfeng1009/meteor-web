export class NetworkClient{
  constructor({onRoom=()=>{},onInput=()=>{},onFrame=()=>{},onError=()=>{},getFrame=()=>null,getAngle=()=>0}={}){Object.assign(this,{onRoom,onInput,onFrame,onError,getFrame,getAngle});this.queue=[];this.held=new Set();this.failures=0;this.sequence=0;this.closed=false;}
  async api(path,data={},auth=false){const response=await fetch(path,{method:'POST',headers:{'Content-Type':'application/json',...(auth?{Authorization:'Bearer '+this.token}:{})},body:JSON.stringify(data),signal:AbortSignal.timeout(6000)});if(!response.headers.get('Content-Type')?.includes('application/json'))throw Error('当前服务未启用联机，请重启开发服务后刷新。');const result=await response.json();if(!response.ok)throw Error(result.error||'联机请求失败');return result;}
  async connect(kind,data){const result=await this.api('/api/rooms/'+kind,data);Object.assign(this,{token:result.token,playerId:result.playerId,code:result.room.code,room:result.room});this.onRoom(this.room);this.timer=setInterval(()=>this.sync(),70);return result;}
  get host(){return this.room?.hostId===this.playerId;}
  async command(action,data={}){const result=await this.api(`/api/rooms/${this.code}/${action}`,data,true);if(result.room){this.room=result.room;this.onRoom(this.room);}return result;}
  send(action,active=true){if(this.closed||this.room?.phase!=='playing')return;if(['forward','back','left','right','guard','crouch'].includes(action)){if(active)this.held.add(action);else this.held.delete(action);}if(action==='clear')this.held.clear();this.queue.push({action,active:!!active,sequence:++this.sequence,angle:this.getAngle()});if(this.queue.length>63){this.queue=[{action:'clear',active:false,sequence:++this.sequence,angle:this.getAngle()}];}}
  async sync(){if(this.busy||this.closed||!this.code)return;this.busy=true;try{
    const data={};if(this.room.phase==='playing'){if(this.host){const frame=this.getFrame();if(frame)data.frame=frame;}else{data.input=this.queue.splice(0);data.input.push({action:'look',active:false,sequence:++this.sequence,angle:this.getAngle(),held:[...this.held]});}}
    const result=await this.command('sync',data);this.failures=0;if(result.input?.length)this.onInput(result.input);if(result.frame)this.onFrame(result.frame);
  }catch(e){if(++this.failures>=3){this.closed=true;clearInterval(this.timer);this.onError(e.message);}}finally{this.busy=false;}}
  async leave(){this.closed=true;clearInterval(this.timer);try{if(this.code)await this.command('leave');}finally{this.queue=[];}}
}

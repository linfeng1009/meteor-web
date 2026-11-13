// Authenticated server-to-browser push. Writes still use the acknowledged POST
// path; a failed stream only falls back to polling, never drops queued inputs.
export class NetworkPushStream {
  constructor({url,token,onPacket,onStatus=()=>{}}){Object.assign(this,{url,token,onPacket,onStatus});}
  async start(){
    if(this.closed||this.running)return;this.running=true;
    const controller=this.controller=new AbortController();let idle,reader;
    const arm=ms=>{clearTimeout(idle);idle=setTimeout(()=>controller.abort(),ms);};
    try{
      arm(6000);
      const response=await fetch(this.url,{headers:{Authorization:'Bearer '+this.token},cache:'no-store',signal:controller.signal});
      if(!response.ok||!response.headers.get('Content-Type')?.includes('application/x-ndjson')||!response.body){this.unsupported=true;await response.body?.cancel();return;}
      reader=response.body.getReader();const decoder=new TextDecoder();let pending='';this.onStatus(true);
      while(!this.closed){
        arm(12000);const {value,done}=await reader.read();if(done)break;
        pending+=decoder.decode(value,{stream:true});if(pending.length>1048576)throw Error('实时状态过大');
        let end;while((end=pending.indexOf('\n'))>=0){const line=pending.slice(0,end);pending=pending.slice(end+1);if(!line.trim())continue;
          const packet=JSON.parse(line);if(packet.error)throw Error(packet.error);this.onPacket(packet);
        }
      }
    }catch{/* Polling remains the reliable fallback during reconnects. */}
    finally{
      clearTimeout(idle);controller.abort();reader?.releaseLock();this.running=false;this.onStatus(false);
      if(!this.closed&&!this.unsupported)this.retry=setTimeout(()=>this.start(),1000);
    }
  }
  stop(){this.closed=true;clearTimeout(this.retry);this.controller?.abort();this.onStatus(false);}
}

// A short presentation queue absorbs HTTP arrival jitter. It never predicts
// positions, executes inputs, or advances authoritative combat.
export class NetworkFrameBuffer {
  constructor(apply,{delay=1/30,maxFrames=8}={}){this.apply=apply;this.delay=delay;this.maxFrames=maxFrames;this.clear();}
  clear(){this.frames=[];this.latestSequence=0;this.latestTime=null;this.clock=null;}
  receive(frame){
    if(!frame||!Number.isSafeInteger(frame.sequence)||!Number.isFinite(frame.time)||frame.sequence<=this.latestSequence||this.latestTime!==null&&frame.time<this.latestTime)return;
    this.latestSequence=frame.sequence;this.latestTime=frame.time;
    if(this.clock===null||frame.result){this.frames=[];this.clock=frame.time-this.delay;this.apply(frame);return;}
    if(this.frames.at(-1)?.time===frame.time)this.frames.pop();
    this.frames.push(frame);
    if(this.frames.length>this.maxFrames)this.frames.splice(0,this.frames.length-this.maxFrames);
    // Resume near the live stream after a long outage instead of replaying
    // seconds of stale movement. Ordinary packet jitter keeps its cadence.
    if(frame.time-this.clock>.25)this.clock=frame.time-this.delay;
  }
  update(dt){
    if(this.clock===null||!Number.isFinite(dt)||dt<=0)return;
    this.clock=Math.min(this.latestTime+this.delay,this.clock+dt);
    while(this.frames.length&&this.frames[0].time<=this.clock+1e-9)this.apply(this.frames.shift());
  }
}

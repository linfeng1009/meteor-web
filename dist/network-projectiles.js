import * as THREE from './vendor/three.module.js';

// Snapshot presentation of the host's existing Web projectile adapters.
// No new trajectory, collision, hit or damage simulation runs on guests.
export function networkProjectileSnapshot(game){
  const result=[];
  for(const [kind,system,fallback] of [['dart',game.projectiles,1],['wheel',game.wheels,2]]){
    for(const shot of system?.active||[]){
      if(shot.removed||!shot.owner?.networkId||shot.owner.disposed||shot.owner.scriptRemoved)continue;
      result.push({kind,id:shot.id,ownerId:shot.owner.networkId,weaponId:shot.context?.weaponId??shot.context?.attacker?.weaponId??fallback,
        position:shot.root.position.toArray(),quaternion:shot.root.quaternion.toArray(),spin:(kind==='dart'?-(shot.visual?.rotation.z||0):(shot.visual?.rotation.y||0)),phase:shot.phase||'outbound',...(kind==='wheel'?{tumble:shot.tumble||0}:{})});
    }
  }
  return result;
}

// Preserve completed flights which can disappear between network snapshots.
// All points come from the host's actual simulation; no path is predicted.
export class NetworkShortFlights{
  constructor(game){
    this.game=game;this.active=new Map();this.recent=[];this.hooks=[];this.stepStart=null;
    for(const [kind,system,fallback] of [['dart',game.projectiles,1],['wheel',game.wheels,2]]){
      if(!system)continue;const previous=system.onFlightSample;
      const hook=(shot,event)=>{previous?.call(system,shot,event);this.sample(kind,shot,event,fallback);};
      system.onFlightSample=hook;this.hooks.push({system,previous,hook});
    }
  }
  sample(kind,shot,event,fallback){
    if(!shot.owner?.networkId)return;const key=`${kind}:${shot.id}`;
    if(event==='spawn'){
      this.active.set(key,{kind,id:shot.id,ownerId:shot.owner.networkId,weaponId:shot.context?.weaponId??shot.context?.attacker?.weaponId??fallback,
        startTime:this.stepStart??this.game.matchElapsed,quaternion:shot.root.quaternion.toArray(),points:[]});
    }
    const flight=this.active.get(key);if(!flight)return;
    const point={time:flight.startTime+shot.age,position:shot.position.toArray(),spin:(kind==='dart'?-(shot.visual?.rotation.z||0):(shot.visual?.rotation.y||0)),...(kind==='wheel'?{tumble:shot.tumble||0}:{})};
    if(flight.points.at(-1)?.time===point.time)flight.points.pop();flight.points.push(point);
    if(flight.points.length>16)flight.points.splice(1,1);
    if(!['spawn','update'].includes(event)){
      this.active.delete(key);flight.endTime=point.time;
      if(!['departure','clear','dispose','network-start','match-end','capacity'].includes(event)&&flight.endTime>flight.startTime){
        flight.points=flight.points.filter(p=>p.time>=flight.endTime-.25);flight.startTime=flight.points[0]?.time;
        if(flight.points.length>=2){this.recent.push(flight);if(this.recent.length>32)this.recent.shift();}
      }
    }
  }
  snapshot(actors){this.recent=this.recent.filter(f=>f.endTime>=this.game.matchElapsed-.5&&actors.has(f.ownerId));return this.recent;}
  dispose(){for(const {system,previous,hook} of this.hooks)if(system.onFlightSample===hook)system.onFlightSample=previous;this.hooks=[];this.active.clear();this.recent=[];}
}

export class NetworkProjectileMotion{
  constructor(game,actors){
    this.game=game;this.actors=actors;this.samples=new Map();this.seenFlights=new Map();this.feedback=[];this.disposed=false;
    this.group=new THREE.Group();this.group.name='联机权威投射物';game.scene?.add(this.group);this.hiddenWheels=new Set();
  }
  receive(states=[],duration=.07,flights=[],worldTime=null){
    if(this.disposed)return;
    const span=Math.max(1/120,Math.min(.15,duration||.07));
    const worldFrom=Number.isFinite(this.worldTime)?Math.max(this.worldTime,worldTime-.15):worldTime-span;
    if(Number.isFinite(worldTime))this.worldTime=worldTime;
    if(Number.isFinite(worldTime)){this.clockFrom=worldFrom;this.clockTo=worldTime;this.clockTime=worldFrom;this.clockElapsed=0;this.clockDuration=span;this.flushFeedback();}
    const seen=new Set();
    for(const state of states){
      if(!this.actors.has(state.ownerId))continue;
      const key=`${state.kind}:${state.id}`;seen.add(key);let sample=this.samples.get(key);
      if(sample&&(sample.ownerId!==state.ownerId||sample.weaponId!==state.weaponId)){this.remove(key);sample=null;}
      if(!sample){
        sample=this.create(state,key);
      }
      sample.from.copy(sample.root.position);sample.to.fromArray(state.position);
      sample.fromQuaternion.copy(sample.root.quaternion);sample.toQuaternion.fromArray(state.quaternion);
      sample.fromSpin=sample.spin;sample.toSpin=state.spin;sample.fromTumble=sample.tumble||0;sample.toTumble=state.tumble||0;sample.elapsed=0;sample.duration=Math.max(1/120,Math.min(.15,duration||.07));sample.phase=state.phase;
      if(!sample.visual&&!sample.loading)this.load(sample);
    }
    for(const flight of flights){
      const key=`${flight.kind}:${flight.id}`,existing=this.samples.get(key);
      if(this.seenFlights.has(key)){if(existing?.flight)seen.add(key);continue;}
      this.seenFlights.set(key,flight.endTime);
      if(seen.has(key)||!Number.isFinite(worldTime)||!this.actors.has(flight.ownerId)||flight.endTime<=worldFrom||flight.startTime>=worldTime)continue;
      const first=flight.points[0],sample=existing||this.create({...flight,position:first.position,spin:first.spin,tumble:first.tumble},key);
      sample.flight=flight;sample.worldFrom=worldFrom;sample.worldTo=worldTime;sample.elapsed=0;sample.duration=span;
      sample.root.visible=worldFrom>=flight.startTime;sample.root.quaternion.fromArray(flight.quaternion);
      seen.add(key);if(!sample.visual&&!sample.loading)this.load(sample);
    }
    for(const [key,endTime] of this.seenFlights)if(Number.isFinite(worldTime)&&endTime<worldTime-.5)this.seenFlights.delete(key);
    for(const key of this.samples.keys())if(!seen.has(key))this.remove(key);
    this.updateHeldWheels();
  }
  create(state,key){
    const root=new THREE.Group();root.position.fromArray(state.position);root.quaternion.fromArray(state.quaternion);
    const sample={key,root,kind:state.kind,ownerId:state.ownerId,weaponId:state.weaponId,from:new THREE.Vector3(),to:new THREE.Vector3(),
      fromQuaternion:new THREE.Quaternion(),toQuaternion:new THREE.Quaternion(),spin:state.spin,tumble:state.tumble||0,loading:false};
    this.samples.set(key,sample);this.group.add(root);return sample;
  }
  load(sample){
    sample.loading=true;
    sample.ready=Promise.resolve().then(()=>this.game._prepareWeapon?.(sample.weaponId)).then(templates=>{
      if(this.disposed||this.samples.get(sample.key)!==sample||!templates?.[0])return;
      const visual=templates[0].clone(true);visual.visible=true;visual.rotation.set(0,0,0);visual.position.set(0,0,0);visual.scale.setScalar(.08);
      visual.position.sub(new THREE.Box3().setFromObject(visual).getCenter(new THREE.Vector3()));
      if(sample.kind==='dart')visual.rotation.z=-sample.spin;else {visual.rotation.y=sample.spin;visual.rotation.x=sample.tumble||0;}sample.visual=visual;sample.root.add(visual);
    }).catch(()=>{}).finally(()=>{sample.loading=false;});
  }
  updateHeldWheels(){
    const hidden=new Set();for(const sample of this.samples.values())if(sample.kind==='wheel'&&(!sample.flight||sample.root.visible))hidden.add(sample.ownerId);
    for(const id of this.hiddenWheels)if(!hidden.has(id)){const actor=this.actors.get(id);if(actor?.weapon==='wheel'&&actor.weaponModel)actor.weaponModel.visible=true;}
    for(const id of hidden){const actor=this.actors.get(id);if(actor?.weapon==='wheel'&&actor.weaponModel)actor.weaponModel.visible=false;}
    this.hiddenWheels=hidden;
  }
  update(dt){
    if(this.disposed||!(dt>0)||!Number.isFinite(dt))return;
    let removed=false,visibilityChanged=false;for(const sample of this.samples.values()){
      if(sample.elapsed>=sample.duration)continue;
      sample.elapsed=Math.min(sample.duration,sample.elapsed+dt);const t=sample.elapsed/sample.duration;
      if(sample.flight){
        const time=sample.worldFrom+(sample.worldTo-sample.worldFrom)*t,{flight}=sample;
        if(time>=flight.endTime){this.remove(sample.key);removed=true;continue;}
        const visible=time>=flight.startTime;if(sample.root.visible!==visible)visibilityChanged=true;sample.root.visible=visible;if(!visible)continue;
        const points=flight.points;let i=1;while(i<points.length-1&&points[i].time<time)i++;
        const a=points[i-1],b=points[i],weight=Math.max(0,Math.min(1,(time-a.time)/(b.time-a.time)));
        sample.from.fromArray(a.position);sample.to.fromArray(b.position);sample.root.position.lerpVectors(sample.from,sample.to,weight);
        sample.spin=a.spin+(b.spin-a.spin)*weight;sample.tumble=(a.tumble||0)+((b.tumble||0)-(a.tumble||0))*weight;if(sample.visual){if(sample.kind==='dart')sample.visual.rotation.z=-sample.spin;else {sample.visual.rotation.y=sample.spin;sample.visual.rotation.x=sample.tumble||0;}}continue;
      }
      sample.root.position.lerpVectors(sample.from,sample.to,t);sample.root.quaternion.slerpQuaternions(sample.fromQuaternion,sample.toQuaternion,t);
      sample.spin=sample.fromSpin+(sample.toSpin-sample.fromSpin)*t;sample.tumble=sample.fromTumble+(sample.toTumble-sample.fromTumble)*t;if(sample.visual){if(sample.kind==='dart')sample.visual.rotation.z=-sample.spin;else {sample.visual.rotation.y=sample.spin;sample.visual.rotation.x=sample.tumble||0;}}
    }
    if(removed||visibilityChanged)this.updateHeldWheels();
    // Equipment may finish loading between snapshots. Apply visibility to
    // the newly attached hand model too, without changing weapon ownership.
    for(const id of this.hiddenWheels){const actor=this.actors.get(id);if(actor?.weapon==='wheel'&&actor.weaponModel)actor.weaponModel.visible=false;}
    if(Number.isFinite(this.clockTo)){this.clockElapsed=Math.min(this.clockDuration,this.clockElapsed+dt);this.clockTime=this.clockFrom+(this.clockTo-this.clockFrom)*this.clockElapsed/this.clockDuration;this.flushFeedback();}
  }
  scheduleFeedback(event,local){
    if(this.disposed)return;this.feedback.push({event,local});if(this.feedback.length>64)this.feedback.shift();this.flushFeedback();
  }
  flushFeedback(){
    for(let i=0;i<this.feedback.length;){const item=this.feedback[i];
      if(this.worldTime-item.event.time>.4){this.feedback.splice(i,1);continue;}
      if(item.event.time<=this.clockTime+1e-9){this.feedback.splice(i,1);this.game._playCombatFeedback?.(item.event,item.local);}
      else i++;
    }
  }
  remove(key){const sample=this.samples.get(key);if(!sample)return;sample.root.removeFromParent();this.samples.delete(key);}
  removeOwner(id){for(const [key,sample] of this.samples)if(sample.ownerId===id)this.remove(key);this.updateHeldWheels();}
  dispose(){
    if(this.disposed)return;for(const key of this.samples.keys())this.remove(key);this.updateHeldWheels();
    this.disposed=true;this.seenFlights.clear();this.feedback=[];this.group.removeFromParent();
    // Model geometry/material/textures belong to the shared weapon cache.
  }
}

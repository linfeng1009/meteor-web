import * as THREE from './vendor/three.module.js';

// Snapshot presentation of the host's existing Web projectile adapters.
// No new trajectory, collision, hit or damage simulation runs on guests.
export function networkProjectileSnapshot(game){
  const result=[];
  for(const [kind,system,fallback] of [['dart',game.projectiles,1],['wheel',game.wheels,2]]){
    for(const shot of system?.active||[]){
      if(shot.removed||!shot.owner?.networkId||shot.owner.disposed||shot.owner.scriptRemoved)continue;
      result.push({kind,id:shot.id,ownerId:shot.owner.networkId,weaponId:shot.context?.weaponId??shot.context?.attacker?.weaponId??fallback,
        position:shot.root.position.toArray(),quaternion:shot.root.quaternion.toArray(),spin:shot.visual?.rotation.y||0,phase:shot.phase||'outbound'});
    }
  }
  return result;
}

export class NetworkProjectileMotion{
  constructor(game,actors){
    this.game=game;this.actors=actors;this.samples=new Map();this.disposed=false;
    this.group=new THREE.Group();this.group.name='联机权威投射物';game.scene?.add(this.group);this.hiddenWheels=new Set();
  }
  receive(states=[],duration=.07){
    if(this.disposed)return;
    const seen=new Set();
    for(const state of states){
      if(!this.actors.has(state.ownerId))continue;
      const key=`${state.kind}:${state.id}`;seen.add(key);let sample=this.samples.get(key);
      if(sample&&(sample.ownerId!==state.ownerId||sample.weaponId!==state.weaponId)){this.remove(key);sample=null;}
      if(!sample){
        const root=new THREE.Group();root.position.fromArray(state.position);root.quaternion.fromArray(state.quaternion);
        sample={key,root,kind:state.kind,ownerId:state.ownerId,weaponId:state.weaponId,from:new THREE.Vector3(),to:new THREE.Vector3(),
          fromQuaternion:new THREE.Quaternion(),toQuaternion:new THREE.Quaternion(),spin:state.spin,loading:false};
        this.samples.set(key,sample);this.group.add(root);
      }
      sample.from.copy(sample.root.position);sample.to.fromArray(state.position);
      sample.fromQuaternion.copy(sample.root.quaternion);sample.toQuaternion.fromArray(state.quaternion);
      sample.fromSpin=sample.spin;sample.toSpin=state.spin;sample.elapsed=0;sample.duration=Math.max(.03,Math.min(.15,duration||.07));sample.phase=state.phase;
      if(!sample.visual&&!sample.loading)this.load(sample);
    }
    for(const key of this.samples.keys())if(!seen.has(key))this.remove(key);
    this.updateHeldWheels();
  }
  load(sample){
    sample.loading=true;
    sample.ready=Promise.resolve().then(()=>this.game._prepareWeapon?.(sample.weaponId)).then(templates=>{
      if(this.disposed||this.samples.get(sample.key)!==sample||!templates?.[0])return;
      const visual=templates[0].clone(true);visual.visible=true;visual.rotation.set(0,0,0);visual.position.set(0,0,0);visual.scale.setScalar(.08);
      visual.position.sub(new THREE.Box3().setFromObject(visual).getCenter(new THREE.Vector3()));
      visual.rotation.y=sample.spin;sample.visual=visual;sample.root.add(visual);
    }).catch(()=>{}).finally(()=>{sample.loading=false;});
  }
  updateHeldWheels(){
    const hidden=new Set();for(const sample of this.samples.values())if(sample.kind==='wheel')hidden.add(sample.ownerId);
    for(const id of this.hiddenWheels)if(!hidden.has(id)){const actor=this.actors.get(id);if(actor?.weapon==='wheel'&&actor.weaponModel)actor.weaponModel.visible=true;}
    for(const id of hidden){const actor=this.actors.get(id);if(actor?.weapon==='wheel'&&actor.weaponModel)actor.weaponModel.visible=false;}
    this.hiddenWheels=hidden;
  }
  update(dt){
    if(this.disposed||!(dt>0)||!Number.isFinite(dt))return;
    for(const sample of this.samples.values()){
      if(sample.elapsed>=sample.duration)continue;
      sample.elapsed=Math.min(sample.duration,sample.elapsed+dt);const t=sample.elapsed/sample.duration;
      sample.root.position.lerpVectors(sample.from,sample.to,t);sample.root.quaternion.slerpQuaternions(sample.fromQuaternion,sample.toQuaternion,t);
      sample.spin=sample.fromSpin+(sample.toSpin-sample.fromSpin)*t;if(sample.visual)sample.visual.rotation.y=sample.spin;
    }
    // Equipment may finish loading between snapshots. Apply visibility to
    // the newly attached hand model too, without changing weapon ownership.
    for(const id of this.hiddenWheels){const actor=this.actors.get(id);if(actor?.weapon==='wheel'&&actor.weaponModel)actor.weaponModel.visible=false;}
  }
  remove(key){const sample=this.samples.get(key);if(!sample)return;sample.root.removeFromParent();this.samples.delete(key);}
  removeOwner(id){for(const [key,sample] of this.samples)if(sample.ownerId===id)this.remove(key);this.updateHeldWheels();}
  dispose(){
    if(this.disposed)return;for(const key of this.samples.keys())this.remove(key);this.updateHeldWheels();
    this.disposed=true;this.group.removeFromParent();
    // Model geometry/material/textures belong to the shared weapon cache.
  }
}

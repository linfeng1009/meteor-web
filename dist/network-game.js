// Listen-host simulation adapter: guests submit inputs, never HP/damage.
// Uses the same native POS/ACT/RES combat, movement and collision paths.
const continuous=['forward','back','left','right','guard','crouch'];
const fields=['hero','enemies','keys','directionBuffer','recoveryAttack','traversalTap','locked','cameraAngle','mouseLook','onEvent'];
// Presentation only: never advance combat, collisions, damage or movement rules.
export class NetworkReplicaMotion{
  constructor(){this.samples=new Map();}
  receive(actor,state,duration,{poseChanged=false}={}){
    const previous=this.samples.get(actor),position=actor.root.position,from=position.toArray();
    const snap=!previous||previous.dead!==!!state.dead||Math.hypot(...state.position.map((n,i)=>n-from[i]))>6;
    const sample={from,to:[...state.position],angle:actor.root.rotation.y,
      turn:Math.atan2(Math.sin(state.angle-actor.root.rotation.y),Math.cos(state.angle-actor.root.rotation.y)),
      targetAngle:state.angle,elapsed:0,duration:Math.max(.03,Math.min(.15,duration||.07)),dead:!!state.dead,
      source:state.source,frame:state.frame,fromFrame:actor.character.frame,
      animate:!snap&&!poseChanged&&previous.source===state.source&&state.frame>=actor.character.frame};
    this.samples.set(actor,sample);
    if(snap){position.fromArray(state.position);actor.root.rotation.y=state.angle;sample.elapsed=sample.duration;}
    if(!sample.animate)this.frame(actor,state.source,state.frame);
  }
  frame(actor,source,frame){const pose=actor.combat.timeline?.pose;if(!pose)return;const at=Math.max(pose.start,Math.min(pose.end,frame));actor.combat.timeline.frame=at;actor.character.setPoseFrame(source,at);}
  update(actor,dt){const s=this.samples.get(actor);if(!s||!(dt>0)||!Number.isFinite(dt))return;
    s.elapsed=Math.min(s.duration,s.elapsed+dt);const t=s.elapsed/s.duration;
    actor.root.position.fromArray(s.from.map((n,i)=>n+(s.to[i]-n)*t));
    // Snapped states must stay at their destination, including after respawn.
    if(t===1)actor.root.position.fromArray(s.to);
    actor.root.rotation.y=t===1?s.targetAngle:s.angle+s.turn*t;
    if(s.animate)this.frame(actor,s.source,s.fromFrame+(s.frame-s.fromFrame)*t);
  }
}
export class NetworkGame{
  static async create(game,client,room){
    game.pause(true);
    for(const f of game.enemies){game._disposeNameplate(f);f.character.dispose();f.root.removeFromParent();}
    game.enemies=[];await game._equip(game.hero,'sword');game.setInfiniteRage(false);
    const self=room.players.find(p=>p.id===client.playerId),other=room.players.find(p=>p.id!==client.playerId);
    game.hero.name=self.name;game.hero.networkId=self.id;game.hero.team=game.hero.teamMask=client.host?1:2;
    const peer=await game._createFighter(0,other.name);peer.networkId=other.id;peer.team=peer.teamMask=client.host?2:1;
    peer.spawnIndex=client.host?1:0;game.scene.add(peer.root);game.enemies.push(peer);await game._equip(peer,'sword');
    game._placeFighter(game.hero,game.currentMap.spawns[client.host?0:1]);game._placeFighter(peer,game.currentMap.spawns[client.host?1:0]);
    game._disposeNameplate(peer);game._nameplate(peer);
    return new NetworkGame(game,client,room);
  }
  constructor(game,client,room){
    Object.assign(this,{game,client,room,active:false,sequence:0,lastFrame:0,actors:new Map([[game.hero.networkId,game.hero],[game.enemies[0].networkId,game.enemies[0]]])});
    this.scores=new Map(room.players.map(p=>[p.id,{kills:0,deaths:0}]));
    this.presentation=new NetworkReplicaMotion();
    this.remote={keys:new Set(),directionBuffer:[],recoveryAttack:null,traversalTap:null,locked:null,cameraAngle:Math.PI};
    this.original={};for(const key of ['action','pause','_updateFighter','_updatePresentation','_separateCharacters','_hud','_kill'])this.original[key]=game[key];
    const session=this;
    game.action=function(name,down=true){
      if(!session.active)return;if(name==='switch'||/^weapon/.test(name)||name==='pickup')return;
      if(!client.host){if(name==='lock'){game.locked=game.locked?null:game.enemies[0];game.cameraManualUntil=0;}client.send(name,down);return;}
      return session.original.action.call(game,name,down);
    };
    game.pause=function(value=true){client.send('clear',false);if(client.host)session.original.action.call(game,'guard',false);session.original.pause.call(game,session.active?false:value);if(value){game.keyboard?.reset();game.mouseLook?.release();game.keys.clear();}};
    game._updateFighter=function(f,dt){if(!session.active||!client.host)return;if(f===game.hero)return session.original._updateFighter.call(game,f,dt);session.context(f,()=>session.original._updateFighter.call(game,f,dt));};
    game._updatePresentation=function(dt){if(session.active&&!client.host)for(const actor of session.actors.values())session.presentation.update(actor,dt);session.original._updatePresentation.call(game,dt);};
    game._separateCharacters=function(dt){if(client.host&&session.active){const actors=[game.hero,...game.enemies],flags=actors.map(f=>f.hero);try{for(const f of actors)f.hero=false;session.original._separateCharacters.call(game,dt);}finally{actors.forEach((f,i)=>f.hero=flags[i]);}}};
    game._hud=function(){if(!session.inRemote)session.original._hud.call(game);};
    game._kill=function(target,options){const wasDead=target.dead;session.original._kill.call(game,target,options);if(!wasDead&&target.dead){session.scores.get(target.networkId).deaths++;if(options?.awardKill!==false){const rival=[...session.scores.keys()].find(id=>id!==target.networkId);session.scores.get(rival).kills++;}}const score=session.scores.get(client.playerId);game.kills=score.kills;game.deaths=score.deaths;};
  }
  context(actor,fn){
    const g=this.game,saved=Object.fromEntries(fields.map(k=>[k,g[k]])),spawns=g.currentMap.spawns,wasHero=actor.hero;
    this.inRemote=true;Object.assign(g,this.remote,{hero:actor,enemies:[saved.hero],mouseLook:{locked:true},onEvent:()=>{}});actor.hero=true;
    g.currentMap.spawns=[spawns[actor.spawnIndex]||spawns[1],...spawns];
    try{return fn();}finally{for(const key of ['directionBuffer','recoveryAttack','traversalTap','locked','cameraAngle'])this.remote[key]=g[key];actor.hero=wasHero;g.currentMap.spawns=spawns;Object.assign(g,saved);this.inRemote=false;}
  }
  play(){this.active=true;this.original.pause.call(this.game,false);}
  inputs(batch){if(!this.client.host||!this.active)return;const actor=this.game.enemies[0];for(const input of batch){if(input.playerId!==actor.networkId)continue;this.context(actor,()=>{
    if(input.action==='clear'){for(const key of [...this.game.keys])this.original.action.call(this.game,key,false);this.game.traversalTap=null;this.game.directionBuffer=[];this.game.recoveryAttack=null;actor.guard=false;return;}
    this.game.cameraAngle=input.angle;
    if(input.action==='look'){const held=new Set(input.held||[]);for(const key of continuous){if(this.game.keys.has(key)&&!held.has(key))this.original.action.call(this.game,key,false);else if(!this.game.keys.has(key)&&held.has(key))this.original.action.call(this.game,key,true);}return;}
    this.original.action.call(this.game,input.action,input.active);
  });}}
  snapshot(){if(!this.active||!this.client.host)return null;const g=this.game;return {sequence:++this.sequence,time:g.matchElapsed,players:[g.hero,...g.enemies].map(f=>({id:f.networkId,position:f.root.position.toArray(),angle:f.root.rotation.y,hp:f.hp,maxHp:f.maxHp,rage:f.rage,dead:f.dead,grounded:f.grounded,guard:f.guard,pose:f.combat.timeline?.pose.id||0,source:f.character.source??0,frame:f.character.frame??0,serial:f.combat.serial,effectTime:f.combat._effectElapsed||0,context:f.combat.currentMove?{name:f.combat.currentMove.name||'',rage:f.combat.currentMove.rage||0,poseId:f.combat.currentMove.poseId,command:f.combat.currentMove.command||''}:null,...this.scores.get(f.networkId)}))};}
  apply(frame){if(this.client.host||!this.active||frame.sequence<=this.lastFrame)return;this.lastFrame=frame.sequence;const g=this.game,duration=frame.time-this.presentationTime;this.presentationTime=frame.time;g.matchElapsed=frame.time;
    for(const state of frame.players){const f=this.actors.get(state.id);if(!f||!f.combat.data.poses.has(state.pose))continue;
      Object.assign(f,{hp:state.hp,maxHp:state.maxHp,rage:state.rage,dead:!!state.dead,grounded:!!state.grounded,guard:!!state.guard});
      const serial=f.networkSerial!==state.serial||f.combat.timeline?.pose.id!==state.pose;
      if(serial){f.combat.play(state.pose,{force:true,context:state.context,attack:f.combat.data.poses.get(state.pose).attacks.length>0});f.networkSerial=state.serial;}
      this.presentation.receive(f,state,duration,{poseChanged:serial});
      const pose=f.combat.timeline.pose,at=Math.max(pose.start,Math.min(pose.end,state.frame));
      g.rageVfx?.sample(f,{pose,context:state.context,serial:state.serial,frame:at,source:state.source,effectTime:state.effectTime});
      if(f===g.hero){g.kills=state.kills;g.deaths=state.deaths;}
    }if(g.locked?.dead)g.locked=null;g._hud();
  }
  dispose(){this.active=false;for(const [key,value] of Object.entries(this.original))this.game[key]=value;this.original.pause.call(this.game,true);}
}

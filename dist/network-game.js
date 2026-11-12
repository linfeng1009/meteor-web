import {nativeIsInvisible} from './native-items.js';
import {networkSpawns} from './network-spawns.js';
import {roomRules,matchResult,NETWORK_MODES} from './network-rules.js';
import { battleCharacterSelection } from './character-appearances.js';
// Listen-host simulation adapter: guests submit inputs, never HP/damage.
// Uses the same native POS/ACT/RES combat, movement and collision paths.
const continuous=['forward','back','left','right','guard','crouch'];
import {createPlayerControl,clearPlayerCommands,applyPlayerLook,PLAYER_LOOK_YAW_SCALE} from './player-control.js';
import {nativeSameTeam} from './native-teams.js';
export function networkPoseBlend(blend){
  if(!blend)return null;
  // Interrupted-hit snapshots stay local: transmit two frame descriptors,
  // then capture the guest's currently displayed pose once per cast serial.
  const descriptor=value=>({source:value.source,frame:value.frame});
  return {from:descriptor(blend.from),to:descriptor(blend.to),weight:blend.weight,duration:blend.duration,fromSnapshot:!!blend.from.snapshot};
}
// Presentation only: never advance combat, collisions, damage or movement rules.
export class NetworkReplicaMotion{
  constructor(){this.samples=new Map();}
  receive(actor,state,duration,{poseChanged=false}={}){
    const previous=this.samples.get(actor),position=actor.root.position,from=position.toArray();
    const snap=!previous||previous.dead!==!!state.dead||Math.hypot(...state.position.map((n,i)=>n-from[i]))>6;
    const sample={from,to:[...state.position],angle:actor.root.rotation.y,
      turn:Math.atan2(Math.sin(state.angle-actor.root.rotation.y),Math.cos(state.angle-actor.root.rotation.y)),
      targetAngle:state.angle,elapsed:0,duration:Math.max(.03,Math.min(.15,duration||.07)),dead:!!state.dead,
      source:state.source,frame:state.frame,fromFrame:actor.character.frame,serial:state.serial,
      animate:!snap&&!poseChanged&&previous.serial===state.serial&&previous.source===state.source&&state.frame>=actor.character.frame};
    if(state.blend&&actor.character.setPoseBlend){
      const same=previous?.hostBlend&&previous.serial===state.serial;
      const from=same?previous.blend.from:state.blend.fromSnapshot?actor.character.capturePose?.()||{source:actor.character.source,frame:actor.character.frame}:state.blend.from;
      sample.blend={from,to:state.blend.to};sample.hostBlend=true;sample.serial=state.serial;
      sample.fromWeight=same?previous.weight:state.blend.weight;sample.toWeight=state.blend.weight;
      if(snap||sample.fromWeight>sample.toWeight)sample.fromWeight=sample.toWeight;
      sample.weight=sample.fromWeight;sample.animate=false;
    }else if(!snap&&!poseChanged&&previous?.serial===state.serial&&previous?.blend&&previous.weight<1&&actor.character.setPoseBlend){
      // Only finish a partial blend within the same authoritative action.
      // An unblended new action must not inherit an interrupted old blend.
      sample.blend={from:actor.character.capturePose?.()||{source:actor.character.source,frame:actor.character.frame},to:{source:state.source,frame:state.frame}};
      sample.fromWeight=0;sample.toWeight=1;sample.weight=0;sample.animate=false;
    }
    this.samples.set(actor,sample);
    if(snap){position.fromArray(state.position);actor.root.rotation.y=state.angle;sample.elapsed=sample.duration;}
    if(sample.blend)this.blend(actor,sample);else if(!sample.animate)this.frame(actor,state.source,state.frame);
  }
  blend(actor,sample){actor.combat.timeline.frame=sample.blend.to.frame;actor.character.setPoseBlend(sample.blend.from,sample.blend.to,sample.weight);}
  frame(actor,source,frame){const pose=actor.combat.timeline?.pose;if(!pose)return;const at=Math.max(pose.start,Math.min(pose.end,frame));actor.combat.timeline.frame=at;actor.character.setPoseFrame(source,at);}
  update(actor,dt){const s=this.samples.get(actor);if(!s||!(dt>0)||!Number.isFinite(dt))return;
    if(s.elapsed>=s.duration&&s.presented)return; // No extrapolation or repeated skeleton work while stalled.
    s.elapsed=Math.min(s.duration,s.elapsed+dt);const t=s.elapsed/s.duration;
    actor.root.position.fromArray(s.from.map((n,i)=>n+(s.to[i]-n)*t));
    // Snapped states must stay at their destination, including after respawn.
    if(t===1)actor.root.position.fromArray(s.to);
    actor.root.rotation.y=t===1?s.targetAngle:s.angle+s.turn*t;
    if(s.blend){s.weight=s.fromWeight+(s.toWeight-s.fromWeight)*t;this.blend(actor,s);}
    else if(s.animate)this.frame(actor,s.source,s.fromFrame+(s.frame-s.fromFrame)*t);
    s.presented=true;
  }
}
export class NetworkGame{
  static async create(game,client,room,{isCurrent=()=>true}={}){
    const valid=()=>isCurrent()&&!client.closed&&!game.disposed;
    if(!valid())return null;
    game.pause(true);
    for(const f of game.enemies){game._disposeNameplate(f);f.character.dispose();f.root.removeFromParent();}
    game.enemies=[];await game._equip(game.hero,'sword');if(!valid())return null;game.setInfiniteRage(false);
    const self=room.players.find(p=>p.id===client.playerId),created=[];let retained=false,previousSpawns,matchSpawns;
    game.hero.name=self.name;game.hero.networkId=self.id;
    try{
      for(const player of room.players.filter(p=>p.id!==client.playerId)){
        const selection=battleCharacterSelection(player.selection);
        const peer=await game._createFighter(selection.character,player.name,false,null,selection.characterAppearance);created.push(peer);
        if(!valid())return null;peer.networkId=player.id;game.scene.add(peer.root);game.enemies.push(peer);await game._equip(peer,'sword');if(!valid())return null;
      }
      previousSpawns=game.currentMap.spawns;matchSpawns=networkSpawns(game,room.players.length);game.currentMap.spawns=matchSpawns;
      for(const player of room.players){
        const actor=player.id===self.id?game.hero:created.find(f=>f.networkId===player.id),index=room.players.indexOf(player);
        actor.team=actor.teamMask=room.mode==='deathmatch'?(player.team||index%2+1):1<<index;actor.spawnIndex=index;
        game._placeFighter(actor,game.currentMap.spawns[index%game.currentMap.spawns.length]);
        if(actor!==game.hero){game._disposeNameplate(actor);game._nameplate(actor);}
      }
      if(game.localControl){game.localControl.locked=null;game.localControl.autoLockEnabled=true;}
      const session=new NetworkGame(game,client,room);session.previousSpawns=previousSpawns;session.matchSpawns=matchSpawns;retained=true;return session;
    }finally{if(!retained&&previousSpawns&&game.currentMap.spawns===matchSpawns)game.currentMap.spawns=previousSpawns;if(!retained)for(const peer of created){game.enemies=game.enemies.filter(actor=>actor!==peer);game._disposeNameplate(peer);peer.disposed=true;peer.character.dispose();peer.root.removeFromParent();}}
  }

  constructor(game,client,room){
    Object.assign(this,{game,client,room,active:false,sequence:0,lastFrame:0,actors:new Map([game.hero,...game.enemies].map(f=>[f.networkId,f]))});
    this.rules=roomRules(room);this.result=null;this.scores=new Map(room.players.map(p=>[p.id,{kills:0,deaths:0}]));
    this.presentation=new NetworkReplicaMotion();
    this.lastImpactId=0;game.combatFeedbackEvents=[];
    this.previousLootReplica=game.lootReplica;game.lootReplica=!client.host;
    this.controls=new Map();this.previousControls=new Map();
    for(const actor of game.enemies){const control=createPlayerControl({cameraAngle:(actor.root.rotation.y||0)-Math.PI,lookLocked:true});this.controls.set(actor.networkId,control);this.previousControls.set(actor,actor.playerControl);actor.playerControl=control;}
    this.peer=game.enemies[0];this.remote=this.controls.get(this.peer?.networkId);
    this.previousNetworkCombat=game.networkCombat;game.networkCombat=true;
    this.original={};for(const key of ['action','pause','releaseInput','_updateFighter','_updatePresentation','_separateCharacters','_kill','_stepWorld'])this.original[key]=game[key];
    const session=this;
    if(typeof document!=='undefined'&&game.renderer?.domElement?.parentElement){this.board=document.createElement('aside');this.board.className='network-match-board';this.board.setAttribute('aria-label','联机比分');this.board.style.cssText='position:absolute;right:20px;top:110px;padding:12px 16px;background:#101818cc;border:1px solid #a88b5880;color:#eee7cf;white-space:pre-line;pointer-events:none;z-index:5;max-height:52vh;overflow:auto;font:12px/1.45 system-ui';game.renderer.domElement.parentElement.append(this.board);}

    game.action=function(name,down=true){
      if(!session.active||session.result||session.inputSuspended&&down)return;if(/^weapon/.test(name))return;
      if(!client.host){if(name==='lock'&&down){game._toggleCombatLock?.(game.hero,game.localControl||game);game.cameraManualUntil=0;}client.send(name,down);return;}
      return session.original.action.call(game,name,down);
    };
    game.releaseInput=function(options={}){if(options.releaseMouse!==false)session.inputSuspended=true;client.send('clear',false);session.original.releaseInput.call(game,options);};
    game.pause=function(value=true){session.inputSuspended=!!value;session.original.pause.call(game,session.result?true:session.active?false:value);if(value)game.mouseLook?.release();};
    game._updateFighter=function(f,dt){if(session.active&&client.host&&!session.result){if(session.rules.mode==='deathmatch'&&f.dead){const state=f.combat?.update(dt);if(state)f.character?.setPoseFrame(state.source,state.frame);return;}return session.original._updateFighter.call(game,f,dt);}};
    game._separateCharacters=function(dt){if(session.active&&client.host)return session.original._separateCharacters.call(game,dt);};
    game._updatePresentation=function(dt){if(session.active&&!client.host)for(const actor of session.actors.values())session.presentation.update(actor,dt);session.original._updatePresentation.call(game,dt);session.boardTime=(session.boardTime||0)+dt;if(session.boardTime>.15){session.boardTime=0;session.updateBoard();session.updateNameplates();}};
    game._stepWorld=function(dt){if(session.result)return;session.original._stepWorld?.call(game,dt);if(client.host&&session.active)session.checkFinished();};
    game._kill=function(target,options={}){
      const wasDead=target.dead;session.original._kill.call(game,target,options);
      if(!wasDead&&target.dead){
        const victim=session.scores.get(target.networkId);if(victim)victim.deaths++;
        const killer=options.attacker?.networkId||[...session.actors].find(([,actor])=>actor.root===options.attacker?.root)?.[0];
        if(options.awardKill!==false&&killer&&killer!==target.networkId&&!nativeSameTeam(options.attacker,target)&&session.scores.has(killer))session.scores.get(killer).kills++;
        if(session.rules.mode==='deathmatch')target.respawn=Infinity;
      }
      const score=session.scores.get(client.playerId);if(score){game.kills=score.kills;game.deaths=score.deaths;}
    };
  }
  reconcile(room){
    this.room=room;
    for(const [id,actor] of this.actors){if(room.players.some(p=>p.id===id))continue;
      if(this.game.locked===actor)this.game.locked=null;for(const control of this.controls.values())if(control.locked===actor)control.locked=null;
      this.controls.delete(id);this.actors.delete(id);this.scores.delete(id);this.presentation.samples.delete(actor);
      actor.disposed=true;this.game._disposeNameplate?.(actor);actor.character?.dispose();actor.root.removeFromParent();this.game.enemies=this.game.enemies.filter(f=>f!==actor);
    }
  }
  checkFinished(){
    if(this.result)return;
    const players=[...this.actors].map(([id,f])=>({id,team:f.team,dead:f.dead,...this.scores.get(id)}));
    const result=matchResult(this.rules,players,this.game.matchElapsed);if(result)this.finish(result);
  }
  updateNameplates(){
    const hero=this.game.hero,near=[...this.actors.values()].filter(f=>f!==hero&&!f.dead&&!f.disposed&&(!nativeIsInvisible(f)||nativeSameTeam(f,hero))).sort((a,b)=>a.root.position.distanceToSquared(hero.root.position)-b.root.position.distanceToSquared(hero.root.position));
    const visible=new Set(near.slice(0,3));if(this.game.locked&&!this.game.locked.dead&&!nativeIsInvisible(this.game.locked))visible.add(this.game.locked);
    for(const actor of this.actors.values())if(actor.nameplate)actor.nameplate.visible=visible.has(actor);
  }
  updateBoard(){
    if(!this.board)return;
    const rows=[`${NETWORK_MODES[this.rules.mode]} · 击杀 / 阵亡`];
    for(const [id,actor] of [...this.actors].sort((a,b)=>(this.scores.get(b[0])?.kills||0)-(this.scores.get(a[0])?.kills||0))){const score=this.scores.get(id)||{};rows.push(`${this.rules.mode==='deathmatch'?(actor.team===1?'红队 ':'蓝队 '):''}${actor.name||id} · ${score.kills||0}/${score.deaths||0}${actor.dead?' · 阵亡':''}`);}
    this.board.textContent=rows.join('\n');
  }
  finish(result){if(this.result||!result)return;this.result=result;this.inputSuspended=true;this.original.pause.call(this.game,true);this.updateBoard();}


  play(){this.active=true;this.inputSuspended=false;this.original.pause.call(this.game,false);}
  inputs(batch){if(!this.client.host||!this.active)return;for(const input of batch){const actor=this.actors.get(input.playerId),control=this.controls.get(input.playerId);if(!actor||!control||this.result)continue;
      // Client clock is used only for command intervals. World time, movement,
      // recovery expiration and damage continue on the host's fixed ticks.
      control.inputTime=Number.isFinite(input.time)?input.time:this.game.elapsed;
      if(input.action==='clear'){control.keys.clear();clearPlayerCommands(control);actor.guard=false;actor.musketAim=false;continue;}
      if(input.action==='look')control.lookDeltaX=(control.lookDeltaX||0)-(input.angle-control.cameraAngle)/PLAYER_LOOK_YAW_SCALE;
      control.cameraAngle=input.angle;control.aimPitch=input.pitch??0;
      applyPlayerLook(actor,control);
      if(input.action==='look'){const held=new Set(input.held||[]);for(const key of continuous){if(control.keys.has(key)&&!held.has(key))this.game._actionFighter(actor,control,key,false);else if(!control.keys.has(key)&&held.has(key))this.game._actionFighter(actor,control,key,true);}continue;}
      this.game._actionFighter(actor,control,input.action,input.active);
    }
  }
  snapshot(){if(!this.active||!this.client.host)return null;const g=this.game;return {sequence:++this.sequence,time:g.matchElapsed,result:this.result,loot:g._lootSnapshot?.(),impacts:g._combatFeedbackSnapshot?.(),players:[...this.actors.values()].map(f=>({id:f.networkId,team:f.team,lockTargetId:this.game._controlFor?.(f)?.locked?.networkId??null,autoLockEnabled:this.game._controlFor?.(f)?.autoLockEnabled!==false,weaponId:f.weaponId,weaponMode:f.combat.weaponMode??'blade',weapon2Id:f.weapon2Id??null,pickupSerial:f.pickupSerial||0,statuses:(f.scriptItems||[]).map(item=>({id:item.id,name:item.name,statKey:item.statKey,remaining:item.remaining,value:item.value,period:item.period||0})),position:f.root.position.toArray(),angle:f.root.rotation.y,hp:f.hp,maxHp:f.maxHp,rage:f.rage,dead:f.dead,grounded:f.grounded,guard:f.guard,reactionPhase:f.combat.reactionPhase??null,queuedMoveName:f.combat.queuedMove?.name??null,musketAim:!!f.musketAim,aimPitch:this.game._controlFor?.(f)?.aimPitch||0,pose:f.combat.timeline?.pose.id||0,source:f.character.source??0,frame:f.character.frame??0,serial:f.combat.serial,effectTime:f.combat._effectElapsed||0,blend:networkPoseBlend(f.combat.poseBlend),context:f.combat.currentMove?{name:f.combat.currentMove.name||'',rage:f.combat.currentMove.rage||0,poseId:f.combat.currentMove.poseId,command:f.combat.currentMove.command||'',...(Number.isFinite(f.combat.currentMove.deathEffectTime)?{deathEffectTime:f.combat.currentMove.deathEffectTime,deathEffectAt:f.combat.currentMove.deathEffectAt}:{})}:null,...this.scores.get(f.networkId)}))};}
  apply(frame){if(this.client.host||!this.active||frame.sequence<=this.lastFrame)return;this.lastFrame=frame.sequence;const g=this.game,duration=frame.time-this.presentationTime;this.presentationTime=frame.time;g.matchElapsed=frame.time;
    g._applyLootState?.(frame.loot);
    for(const state of frame.players){const f=this.actors.get(state.id);if(!f||!f.combat.data.poses.has(state.pose))continue;
      const previousFrame=f.character.frame,previousSerial=f.networkSerial;
      const enteringAim=!f.musketAim&&state.musketAim;if(f===g.hero&&enteringAim){(g.localControl||g).aimPitch=Number.isFinite(state.aimPitch)?state.aimPitch:0;g.cameraAngle=state.angle-Math.PI;}
      if(Number.isInteger(state.kills)&&Number.isInteger(state.deaths))this.scores.set(state.id,{kills:state.kills,deaths:state.deaths});
      Object.assign(f,{hp:state.hp,maxHp:state.maxHp,rage:state.rage,dead:!!state.dead,grounded:!!state.grounded,guard:!!state.guard,networkReactionPhase:state.reactionPhase??null,networkQueuedMoveName:state.queuedMoveName??null});
      const weaponChanged=Number.isInteger(state.weaponId)&&g.weaponItems?.has(state.weaponId)&&f.weaponId!==state.weaponId;
      if(weaponChanged)g._equip(f,state.weaponId).catch(()=>{});
      // Equip initializes local defaults synchronously; authority wins after it.
      f.musketAim=!!state.musketAim;
      if(['blade','spear','sheath'].includes(state.weaponMode))f.combat.weaponMode=state.weaponMode;
      if(state.weapon2Id!==undefined)f.weapon2Id=state.weapon2Id;
      if(Array.isArray(state.statuses))f.networkItemStatuses=state.statuses.map(item=>({...item}));
      if(Number.isInteger(state.pickupSerial)){if(f.pickupSerial!==undefined&&state.pickupSerial>f.pickupSerial){g._soundDefinition?.('getitem');g.rageVfx?.playItem(f,'getitem');}f.pickupSerial=state.pickupSerial;}
      const serial=weaponChanged||f.networkSerial!==state.serial||f.combat.timeline?.pose.id!==state.pose;
      if(serial){f.combat.play(state.pose,{force:true,context:state.context,attack:f.combat.data.poses.get(state.pose).attacks.length>0});f.networkSerial=state.serial;}
      this.presentation.receive(f,state,duration,{poseChanged:serial});
      const pose=f.combat.timeline.pose,at=Math.max(pose.start,Math.min(pose.end,state.frame));
      const from=previousSerial===state.serial&&previousFrame<=at?Math.max(pose.start,previousFrame):Math.max(pose.start,at-1),span=Math.min(.15,Math.max(1/60,Number.isFinite(duration)?duration:1/15));
      const displayed=this.presentation.samples.get(f),fxBlend=state.blend&&displayed?.blend?{...displayed.blend,weight:displayed.weight,duration:state.blend.duration}:state.blend;
      g.rageVfx?.sample(f,{pose,context:state.context,serial:state.serial,frame:at,source:state.source,effectTime:state.effectTime,blend:fxBlend,deathEffectAge:Math.max(0,frame.time-(state.context?.deathEffectAt??frame.time)),consumed:span,frameIntervals:[{from,to:at,timeFrom:0,timeTo:span}]});
      if(displayed?.blend)this.presentation.blend(f,displayed);
      if(serial&&state.context)g._soundDefinition?.(pose.raw?.fields.effectid);
      if(f===g.hero){g.kills=state.kills;g.deaths=state.deaths;}
    }
    const self=frame.players.find(state=>state.id===this.client.playerId);if(self&&Object.hasOwn(self,'lockTargetId')){const control=g.localControl||g;control.locked=self.lockTargetId?this.actors.get(self.lockTargetId)||null:null;control.autoLockEnabled=self.autoLockEnabled!==false;}
    for(const event of frame.impacts||[]){if(event.id<=this.lastImpactId)continue;this.lastImpactId=event.id;if(frame.time-event.time>.4)continue;
      g._playCombatFeedback?.(event,event.attackerId===this.client.playerId||event.targetId===this.client.playerId);}
    if(frame.result){for(const actor of this.actors.values())this.presentation.update(actor,.15);this.finish(frame.result);}this.updateBoard();if(g.locked?.dead)g.locked=null;g._hud();
  }
  dispose(){this.active=false;if(this.matchSpawns&&this.game.currentMap?.spawns===this.matchSpawns)this.game.currentMap.spawns=this.previousSpawns;this.board?.remove();this.game.lootReplica=this.previousLootReplica;this.game.networkCombat=this.previousNetworkCombat;for(const actor of this.actors.values()){this.game.stealthFeedback?.clearActor(actor);delete actor.networkItemStatuses;delete actor.networkQueuedMoveName;delete actor.networkReactionPhase;if(actor.nameplate)actor.nameplate.visible=true;}this.game._clearDroppedWeapons?.();for(const [actor,previous] of this.previousControls){const control=this.controls.get(actor.networkId);control?.keys.clear();clearPlayerCommands(control);if(actor.playerControl===control){if(previous)actor.playerControl=previous;else delete actor.playerControl;}}for(const [key,value] of Object.entries(this.original))this.game[key]=value;this.original.pause.call(this.game,true);}
}

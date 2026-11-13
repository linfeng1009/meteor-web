// Per-player gameplay input. Camera rendering and HUD stay on the local game.
import {validCombatTarget} from './combat-targeting.js';
import {nativeTraversalDirection,nativeStandingTurnDirection,NATIVE_STANDING_TURN,NATIVE_CROUCH_POSES,NATIVE_GROUND_MOVE_POSES} from './native-traversal.js';
export const PLAYER_LOOK_YAW_SCALE=.005;
export function usesPlayerLook(control){return !!(control?.lookLocked||control?.mouseLook?.locked||control?.lookPending);}
function recordStandingTurn(actor,control,mouseX){
  if(!mouseX||!actor.grounded||actor.musketAim||nativeTraversalDirection(control.keys))return;
  const crouched=!!control.keys?.has('crouch'),poses=crouched?NATIVE_CROUCH_POSES:NATIVE_GROUND_MOVE_POSES;
  const current=actor.combat?.timeline?.pose.id,stance=crouched?NATIVE_CROUCH_POSES.idle:actor.combat?.stance;
  if(current!==stance&&current!==poses.right&&current!==poses.left)return;
  const direction=nativeStandingTurnDirection(mouseX),poseId=direction?poses[direction]:current;
  if(poseId!==poses.right&&poseId!==poses.left)return;
  if(actor.combat?.data?.poses.get(poseId)?.valid)actor.standingTurn={poseId,crouched,elapsed:0};
}
export function updatePlayerTurn(actor,control,dt){
  const eligible=control&&actor.grounded&&!actor.dead&&!actor.guard&&!actor.wallRun&&!actor.scriptInputBlocked&&!actor.scriptCrouched&&!actor.musketAim&&!actor.combat?.busy&&!validCombatTarget(actor,control.locked)&&!nativeTraversalDirection(control.keys);
  if(!eligible){actor.standingTurn=null;if(control)control.lookDeltaX=0;return;}
  const turn=actor.standingTurn;if(!turn)return;
  turn.elapsed+=dt;
  if(turn.crouched!==!!control.keys?.has('crouch')||turn.elapsed>NATIVE_STANDING_TURN.hold+1e-9)actor.standingTurn=null;
}
// 004cb6b0 accepts native actor states0/1, rotating the model in ordinary
// air as well as on the ground. Wall/action/guard states do not take this
// free-input path. Camera-angle conversion remains the Web input adapter.
export function applyPlayerLook(actor,control){
  if(!actor?.root?.rotation||actor.dead||actor.disposed||actor.scriptRemoved||actor.scriptInputBlocked||actor.scriptCrouched||actor.wallRun||actor.guard||actor.combat?.busy||!Number.isFinite(control?.cameraAngle))return false;
  if(validCombatTarget(actor,control.locked))return false;
  if(control.locked)control.locked=null;
  recordStandingTurn(actor,control,control.lookDeltaX||0);
  const heading=control.cameraAngle+Math.PI;
  if(actor.root.rotation.y!==heading)actor.root.rotation.y=heading;
  control.lookPending=false;
  control.lookDeltaX=0;
  return true;
}
export function createPlayerControl({cameraAngle=0,lookLocked=false}={}) {
  return {keys:new Set(),directionBuffer:[],recoveryAttack:null,traversalTap:null,jumpCharge:null,locked:null,autoLockEnabled:true,cameraAngle,aimPitch:0,lookLocked,lookPending:false,lookDeltaX:0};
}
export function clearPlayerCommands(control,{preserveJump=false}={}) {
  if(!control)return;
  control.directionBuffer=[];control.recoveryAttack=null;control.traversalTap=null;if(!preserveJump)control.jumpCharge=null;
  control.lookDeltaX=0;
}
export function bindLocalPlayerControl(game) {
  const control=createPlayerControl();
  // Existing menus/camera/keyboard use these names; keep aliases while the
  // simulation consumes the explicit control object rather than the game.
  for(const key of ['keys','directionBuffer','recoveryAttack','traversalTap','jumpCharge','locked','cameraAngle']){
    if(game[key]!==undefined)control[key]=game[key];
    Object.defineProperty(game,key,{configurable:true,enumerable:true,get:()=>control[key],set:value=>{control[key]=value;}});
  }
  Object.defineProperty(control,'mouseLook',{get:()=>game.mouseLook});
  game.localControl=control;return control;
}

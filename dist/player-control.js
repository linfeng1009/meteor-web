// Per-player gameplay input. Camera rendering and HUD stay on the local game.
import {validCombatTarget} from './combat-targeting.js';
export function usesPlayerLook(control){return !!(control?.lookLocked||control?.mouseLook?.locked||control?.lookPending);}
// 004cb6b0 accepts native actor states0/1, rotating the model in ordinary
// air as well as on the ground. Wall/action/guard states do not take this
// free-input path. Camera-angle conversion remains the Web input adapter.
export function applyPlayerLook(actor,control){
  if(!actor?.root?.rotation||actor.dead||actor.disposed||actor.scriptRemoved||actor.scriptInputBlocked||actor.scriptCrouched||actor.wallRun||actor.guard||actor.combat?.busy||!Number.isFinite(control?.cameraAngle))return false;
  if(validCombatTarget(actor,control.locked))return false;
  if(control.locked)control.locked=null;
  const heading=control.cameraAngle+Math.PI;
  if(actor.root.rotation.y!==heading)actor.root.rotation.y=heading;
  control.lookPending=false;
  return true;
}
export function createPlayerControl({cameraAngle=0,lookLocked=false}={}) {
  return {keys:new Set(),directionBuffer:[],recoveryAttack:null,traversalTap:null,jumpCharge:null,locked:null,autoLockEnabled:true,cameraAngle,aimPitch:0,lookLocked,lookPending:false};
}
export function clearPlayerCommands(control,{preserveJump=false}={}) {
  if(!control)return;
  control.directionBuffer=[];control.recoveryAttack=null;control.traversalTap=null;if(!preserveJump)control.jumpCharge=null;
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

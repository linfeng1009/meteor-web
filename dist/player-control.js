// Per-player gameplay input. Camera rendering and HUD stay on the local game.
export function createPlayerControl({cameraAngle=0,lookLocked=false}={}) {
  return {keys:new Set(),directionBuffer:[],recoveryAttack:null,traversalTap:null,locked:null,cameraAngle,aimPitch:0,lookLocked};
}
export function clearPlayerCommands(control) {
  if(!control)return;
  control.directionBuffer=[];control.recoveryAttack=null;control.traversalTap=null;
}
export function bindLocalPlayerControl(game) {
  const control=createPlayerControl();
  // Existing menus/camera/keyboard use these names; keep aliases while the
  // simulation consumes the explicit control object rather than the game.
  for(const key of ['keys','directionBuffer','recoveryAttack','traversalTap','locked','cameraAngle']){
    if(game[key]!==undefined)control[key]=game[key];
    Object.defineProperty(game,key,{configurable:true,enumerable:true,get:()=>control[key],set:value=>{control[key]=value;}});
  }
  Object.defineProperty(control,'mouseLook',{get:()=>game.mouseLook});
  game.localControl=control;return control;
}

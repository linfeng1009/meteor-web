import { bindingMap, defaultBindings } from './keybindings.js';
import {validCombatTarget} from './combat-targeting.js';
export function turnMouseCamera(game, dx, dy) {
  if(game.hero?.musketAim){if(!Number.isFinite(dx)||!Number.isFinite(dy))return false;game.cameraAngle-=dx*.003;const c=game.localControl||game;c.aimPitch=Math.max(-1.2,Math.min(1.2,(c.aimPitch||0)-dy*.003));return true;}
  if(validCombatTarget(game.hero,game.locked))return false;
  if(!Number.isFinite(dx)||!Number.isFinite(dy))return false;
  if(game.locked)game.locked=null;
  game.cameraManualUntil=game.elapsed+2;
  game.cameraAngle-=dx*.005;
  game.cameraPitch=Math.max(.15,Math.min(.95,game.cameraPitch+dy*.003));
  (game.localControl||game).lookPending=true;
  // Raw mouse events update the camera only. Fixed steps and action entry
  // consume this angle, avoiding model/quaternion work at sensor frequency.
  return true;
}
// Pointer Lock must be requested synchronously from a user gesture, before scene loading.
export function createMouseLook(canvas, { document:doc=canvas.ownerDocument, active, move, action, onUnlock=()=>{}, onError=()=>{}, onReset=()=>{}, bindings=defaultBindings() }) {
  let mapping=bindingMap(bindings); const held=new Map();
  const resetButtons=()=>{if(held.size)onReset();for(const name of new Set(held.values()))action(name,false);held.clear();};
  let wasLocked=false, wanted=false, pending=false, disposed=false, reported=false;
  const locked=()=>doc.pointerLockElement===canvas;
  const fail=()=>{pending=false;if(wanted&&!reported){reported=true;onError();}};
  const release=()=>{resetButtons();wanted=false;pending=false;if(locked())doc.exitPointerLock?.();};
  const change=()=>{
    pending=false;const now=locked(),lost=wasLocked&&!now;wasLocked=now;
    if(now&&(!wanted||disposed)){release();return;}
    if(lost&&wanted){resetButtons();wanted=false;if(active())onUnlock();}
  };
  const motion=e=>{if(locked()&&active()&&Number.isFinite(e.movementX)&&Number.isFinite(e.movementY))move(e.movementX,e.movementY);};
  doc.addEventListener('pointerlockchange',change);doc.addEventListener('pointerlockerror',fail);doc.addEventListener('mousemove',motion);
  function request(){
    if(disposed||typeof canvas.requestPointerLock!=='function')return false;
    wanted=true;if(locked()||pending)return true;pending=true;reported=false;
    try{const result=canvas.requestPointerLock();result?.catch?.(fail);}catch{fail();}
    return true;
  }
  return {
    get locked(){return locked();},request,release,
    setBindings(next){resetButtons();mapping=bindingMap(next);},
    pointerUp(e){const name=held.get(e.button);held.delete(e.button);if(name&&![...held.values()].includes(name))action(name,false);},
    pointerDown(e){
      if(e.pointerType==='touch'||e.pointerType==='pen'||typeof canvas.requestPointerLock!=='function')return false;
      if(!active())return true;
      e.preventDefault();
      if(!locked()){request();return true;}
      const name=mapping['Mouse'+e.button];if(name&&!held.has(e.button)){held.set(e.button,name);action(name,true);}
      return true;
    },
    dispose(){disposed=true;release();doc.removeEventListener('pointerlockchange',change);doc.removeEventListener('pointerlockerror',fail);doc.removeEventListener('mousemove',motion);}
  };
}

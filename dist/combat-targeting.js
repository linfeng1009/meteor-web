// Web adapter parameters, not recovered native constants. Acquisition respects intent.
import {nativeIsInvisible} from './native-items.js';
import {nativeSameTeam} from './native-teams.js';
export function validCombatTarget(actor,target){return !!target&&target!==actor&&!target.dead&&!target.disposed&&!target.scriptRemoved&&!nativeSameTeam(actor,target);}
export function acquireCombatTarget(actor,candidates,{angle=actor.root.rotation.y,range=12,minDot=.5,lineOfSight=()=>true}={}){
  let best=null,score=Infinity;for(const target of candidates){if(!validCombatTarget(actor,target)||nativeIsInvisible(target)||Math.abs(target.root.position.y-actor.root.position.y)>=6)continue;const dx=target.root.position.x-actor.root.position.x,dz=target.root.position.z-actor.root.position.z,distance=Math.hypot(dx,dz);if(distance>range||distance<.001)continue;const dot=(dx*Math.sin(angle)+dz*Math.cos(angle))/distance;if(dot<minDot||!lineOfSight(actor,target))continue;const value=distance+(1-dot)*4;if(value<score){score=value;best=target;}}return best;
}

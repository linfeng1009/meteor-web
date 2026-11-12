import {nativeIsInvisible} from './native-items.js';

// 00556445 defaults the native model's hidden alpha factor to0.1;
// 0048aeb0 reads effective stat10 and calls005591b0. Material isolation and
// transparent sorting are Web presentation adapters, with no hit immunity.
export class NativeStealthFeedback {
  constructor(){this.actors=new Map();}
  clearActor(actor){
    const state=this.actors.get(actor);if(!state)return;
    for(const entry of state.bindings)if(entry.node.material===entry.replacement)entry.node.material=entry.original;
    for(const material of state.clones.values())material.dispose();
    if(state.nameplate)state.nameplate.visible=state.nameplateVisible;
    this.actors.delete(actor);
  }
  update(actors,observer){
    for(const actor of this.actors.keys())if(!actors.includes(actor)||actor.dead||actor.disposed||actor.scriptRemoved||!nativeIsInvisible(actor))this.clearActor(actor);
    for(const actor of actors){
      if(!actor?.root||actor.dead||actor.disposed||actor.scriptRemoved||!nativeIsInvisible(actor))continue;
      let state=this.actors.get(actor);
      if(state&&(state.mesh!==actor.character?.mesh||state.weapon!==actor.weaponModel||state.butterfly!==actor.butterflySword||state.raiden!==actor.raidenSword||state.phoenix!==actor.phoenixSpear)){
        this.clearActor(actor);state=null;
      }
      if(!state){
        state={mesh:actor.character?.mesh,weapon:actor.weaponModel,butterfly:actor.butterflySword,raiden:actor.raidenSword,phoenix:actor.phoenixSpear,bindings:[],clones:new Map()};
        const clone=material=>{if(!state.clones.has(material)){const copy=material.clone();copy.opacity=material.opacity*.1;copy.transparent=true;copy.depthWrite=false;copy.forceSinglePass=true;state.clones.set(material,copy);}return state.clones.get(material);};
        actor.root.traverse(node=>{if(!node.isMesh||!node.material)return;const original=node.material,replacement=Array.isArray(original)?original.map(clone):clone(original);state.bindings.push({node,original,replacement});node.material=replacement;});
        this.actors.set(actor,state);
      }
      if(actor.nameplate&&observer&&actor!==observer&&actor.team!==observer.team){
        if(!state.nameplate){state.nameplate=actor.nameplate;state.nameplateVisible=actor.nameplate.visible;}
        actor.nameplate.visible=false;
      }
    }
  }
  clear(){for(const actor of this.actors.keys())this.clearActor(actor);}
  dispose(){this.clear();}
}

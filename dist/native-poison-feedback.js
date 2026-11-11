import * as THREE from './vendor/three.module.js';
import { sampleEffectKeys } from './native-effect-transforms.js';

// AttrPOIS provides three green ZS2 channels. Spread, looping and attachment
// are bounded Web presentation adapters, not recovered native emitter physics.
export const POISON_ADAPTER=Object.freeze({maxActors:32,particlesPerChannel:8,cycle:2,size:.42,colorGain:4});
export function hasNativePoison(actor){
  return !!actor&&!actor.dead&&!actor.disposed&&!actor.scriptRemoved&&actor.hp>0&&actor.root?.visible!==false&&
    (actor.networkItemStatuses??actor.scriptItems??[]).some(s=>[11,12,14,18].includes(s.id)&&s.statKey===2&&s.value<0&&Number.isFinite(s.remaining)&&s.remaining>0&&s.period>0);
}
export function hasNativeSlow(actor){
  return !!actor&&!actor.dead&&!actor.disposed&&!actor.scriptRemoved&&actor.hp>0&&actor.root?.visible!==false&&
    (actor.networkItemStatuses??actor.scriptItems??[]).some(s=>[10,13].includes(s.id)&&s.statKey===5&&s.value>0&&s.value<100&&Number.isFinite(s.remaining)&&s.remaining>0);
}
export async function loadNativePoisonFeedback(scene,id='attrpois'){
  const response=await fetch(new URL('./assets/original/poison-vfx.json',import.meta.url));
  if(!response.ok)throw Error('Original poison definition unavailable');
  const manifest=await response.json();
  const texture=await new THREE.TextureLoader().loadAsync(new URL('./assets/original/rage-vfx/textures/zs2_tga.png',import.meta.url).href);
  texture.colorSpace=THREE.SRGBColorSpace;
  return new NativePoisonFeedback(scene,manifest.effects[id],texture);
}
export class NativePoisonFeedback{
  constructor(scene,definition,texture){
    this.slow=definition.id==='attrslow';this.definition=definition;this.texture=texture;this.actors=new Map();this.disposed=false;
    this.channels=definition.nodes.filter(n=>n.type==='PARTICLE');
    const capacity=POISON_ADAPTER.maxActors*this.channels.length*POISON_ADAPTER.particlesPerChannel;
    this.positions=new Float32Array(capacity*3);this.colors=new Float32Array(capacity*3);
    const geometry=new THREE.BufferGeometry();geometry.setAttribute('position',new THREE.BufferAttribute(this.positions,3).setUsage(THREE.DynamicDrawUsage));geometry.setAttribute('color',new THREE.BufferAttribute(this.colors,3).setUsage(THREE.DynamicDrawUsage));geometry.setDrawRange(0,0);
    const material=new THREE.PointsMaterial({map:texture,size:POISON_ADAPTER.size,vertexColors:true,transparent:true,opacity:1,depthWrite:false,depthTest:true,blending:THREE.AdditiveBlending,toneMapped:false});
    this.mesh=new THREE.Points(geometry,material);this.mesh.name=this.slow?'原版减速持续粒子 · 网页运动适配':'原版中毒持续粒子 · 网页运动适配';this.mesh.frustumCulled=false;this.mesh.visible=false;scene.add(this.mesh);
    this.origin=new THREE.Vector3();this.key=new Array(28);
  }
  update(dt,actors=[]){
    if(this.disposed)return;
    const wanted=new Set(actors.filter(this.slow?hasNativeSlow:hasNativePoison).slice(0,POISON_ADAPTER.maxActors));
    for(const actor of this.actors.keys())if(!wanted.has(actor))this.actors.delete(actor);
    const step=Number.isFinite(dt)?Math.max(0,dt):0;let slot=0;
    for(const actor of wanted){
      let state=this.actors.get(actor);if(!state){state={age:0};this.actors.set(actor,state);}state.age+=step;
      actor.root.getWorldPosition(this.origin);
      for(let channel=0;channel<this.channels.length;channel++){
        const node=this.channels[channel],end=node.keys.at(-1)[0]||POISON_ADAPTER.cycle;
        sampleEffectKeys(node.keys,state.age%end,this.key);
        for(let i=0;i<POISON_ADAPTER.particlesPerChannel;i++){
          const phase=(state.age/(this.slow?3:POISON_ADAPTER.cycle)+i/POISON_ADAPTER.particlesPerChannel+channel/this.channels.length)%1;
          const angle=i*2.399963+channel*2.094+state.age*.6,radius=.18+phase*.30;
          this.positions.set([this.origin.x+Math.cos(angle)*radius,this.origin.y+.15+phase*(this.slow?.7:1.8),this.origin.z+Math.sin(angle)*radius],slot*3);
          const fade=Math.sin(phase*Math.PI)*Math.max(0,Math.min(1,this.key[24]));
          for(let c=0;c<3;c++)this.colors[slot*3+c]=Math.max(0,Math.min(1,this.key[11+c]))*fade*POISON_ADAPTER.colorGain;
          slot++;
        }
      }
    }
    this.mesh.geometry.setDrawRange(0,slot);this.mesh.visible=slot>0;
    this.mesh.geometry.attributes.position.needsUpdate=true;this.mesh.geometry.attributes.color.needsUpdate=true;
  }
  clear(){this.actors.clear();this.mesh.visible=false;this.mesh.geometry.setDrawRange(0,0);}
  dispose(){if(this.disposed)return;this.clear();this.mesh.removeFromParent();this.mesh.geometry.dispose();this.mesh.material.dispose();this.texture?.dispose();this.disposed=true;}
}

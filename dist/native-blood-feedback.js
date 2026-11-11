import * as THREE from './vendor/three.module.js';

// Presentation adapter, not recovered EXE emitter constants. Original damage,
// TargetMove and the selected reaction's d_base lift choose distinct feedback.
export const BLOOD_KINDS=Object.freeze(['slash','thrust','impact','launch','shot']);
export const BLOOD_FEEDBACK_ADAPTER=Object.freeze({capacity:768,count:40,lifetime:.68,gravity:8});
export function bloodStyleForHit({damage=0,force=0,weapon='',knockdown=false,lift=0,reactionPose=null}={}){
  const power=Number.isFinite(damage)?Math.max(0,damage):0,push=Number.isFinite(force)?Math.max(0,force):0;
  const level=knockdown||power>=90?2:power>=45||push>=8||reactionPose===100?1:0;
  const kind=lift>=.45||reactionPose===100?'launch':weapon==='musket'||weapon==='dart'?'shot':weapon==='hammer'||weapon==='knuckle'?'impact':weapon==='spear'||weapon==='dagger'?'thrust':'slash';
  return {kind,level};
}
export function validBloodStyle(style){return !!style&&BLOOD_KINDS.includes(style.kind)&&Number.isInteger(style.level)&&style.level>=0&&style.level<=2;}
export function bloodProfile(style){
  const {kind,level}=validBloodStyle(style)?style:{kind:'slash',level:0};
  return {kind,level,count:[40,76,128][level],cores:[4,8,14][level],size:[1.5,2.3,3.4][level],speed:[1.1,1.55,2.15][level],life:[.68,.86,1.02][level],hold:[.07,.11,.16][level]};
}
export class NativeBloodFeedback{
  constructor(scene){
    this.scene=scene;this.cursor=0;this.disposed=false;this.particles=Array(BLOOD_FEEDBACK_ADAPTER.capacity).fill(null);
    const count=this.particles.length;this.positions=new Float32Array(count*3);this.alpha=new Float32Array(count);this.sizes=new Float32Array(count*2);this.velocities=new Float32Array(count*3);this.shapes=new Float32Array(count);this.seeds=new Float32Array(count);
    const geometry=new THREE.InstancedBufferGeometry();geometry.setAttribute('position',new THREE.Float32BufferAttribute([-1,-1,0,1,-1,0,1,1,0,-1,1,0],3));geometry.setIndex([0,1,2,0,2,3]);geometry.instanceCount=count;
    for(const [name,array,width] of [['offset',this.positions,3],['opacity',this.alpha,1],['size',this.sizes,2],['velocity',this.velocities,3],['shape',this.shapes,1],['seed',this.seeds,1]])geometry.setAttribute(name,new THREE.InstancedBufferAttribute(array,width).setUsage(THREE.DynamicDrawUsage));
    const material=new THREE.ShaderMaterial({transparent:true,depthWrite:false,depthTest:true,toneMapped:false,side:THREE.DoubleSide,
      vertexShader:`attribute vec3 offset;attribute float opacity;attribute vec2 size;attribute vec3 velocity;attribute float shape;attribute float seed;
        varying vec2 vBloodUv;varying float fade;varying float form;varying float noiseSeed;
        void main(){vec4 eye=modelViewMatrix*vec4(offset,1.);vec2 axis=(mat3(modelViewMatrix)*velocity).xy;
          if(length(axis)<.001)axis=vec2(cos(seed),sin(seed));else axis=normalize(axis);
          eye.xy+=axis*position.y*size.y+vec2(axis.y,-axis.x)*position.x*size.x;
          gl_Position=opacity>0.?projectionMatrix*eye:vec4(2.,2.,2.,1.);vBloodUv=position.xy;fade=opacity;form=shape;noiseSeed=seed;}`,
      fragmentShader:`varying vec2 vBloodUv;varying float fade;varying float form;varying float noiseSeed;
        void main(){if(fade<=0.)discard;float d=length(vBloodUv),angle=atan(vBloodUv.y,vBloodUv.x);
          if(form<.5){float edge=.66+.14*sin(angle*5.+noiseSeed)+.10*sin(angle*9.-noiseSeed);d/=edge;}
          else if(form<1.5){float width=.23+.67*(vBloodUv.y+1.)*.5;d=length(vec2(vBloodUv.x/width,vBloodUv.y));}
          if(d>1.)discard;float a=(1.-smoothstep(.50,1.,d))*fade;
          gl_FragColor=vec4(mix(vec3(.16,.002,.006),vec3(.55,.012,.018),1.-d*.6),a);
          #include <colorspace_fragment>
        }`});
    this.mesh=new THREE.Mesh(geometry,material);this.mesh.name='分级血花与血流 · 网页表现';this.mesh.frustumCulled=false;this.mesh.visible=false;scene.add(this.mesh);
  }
  emit({point,direction,damage=0,guarded=false,style=null,...features}={}){
    if(this.disposed||guarded||!Number.isFinite(damage)||!(damage>0)||!point||![point.x,point.y,point.z].every(Number.isFinite)||direction&&![direction.x,direction.y,direction.z].every(Number.isFinite))return 0;
    const profile=bloodProfile(validBloodStyle(style)?style:bloodStyleForHit({damage,...features}));
    const forward=direction?.clone()||new THREE.Vector3(0,0,1);forward.y=0;if(forward.lengthSq()<1e-8)forward.set(0,0,1);forward.normalize();
    const right=new THREE.Vector3(forward.z,0,-forward.x),count=profile.count;
    for(let i=0;i<count;i++){
      const slot=this.cursor++%this.particles.length,a=i*2.3999632297,phase=(i%11)/10;
      let lateral=Math.cos(a)*2.6,along=.8+phase*2.2,up=.8+Math.sin(a)*1.6;
      if(profile.kind==='slash'){lateral=Math.sin(a)*3.6;along=.5+Math.cos(a)*1.2;up=.9+Math.sin(a*1.7)*1.5;}
      if(profile.kind==='thrust'||profile.kind==='shot'){lateral=Math.cos(a)*(profile.kind==='shot'?1.7:1);along=1.8+phase*3;up=.7+Math.sin(a)*.9;}
      if(profile.kind==='impact'){lateral=Math.cos(a)*3;along=Math.sin(a)*2.6;up=.8+phase*2;}
      if(profile.kind==='launch'){lateral=Math.cos(a)*2;along=.7+phase;up=2.6+phase*3;}
      const velocity=forward.clone().multiplyScalar(along*profile.speed).addScaledVector(right,lateral*profile.speed);velocity.y=up*profile.speed;
      const core=i<profile.cores,streak=!core&&i%3!==0,life=profile.life+(i%4)*.03;
      const origin=point.clone();if(core){origin.addScaledVector(right,Math.sin(a)*.1*profile.size);origin.y+=Math.sin(a*1.7)*.08*profile.size;velocity.multiplyScalar(.35);}
      const delay=core?0:(i%7)*.012,width=(core?.20:streak?.034:.062)*profile.size*(.8+phase*.6),height=(core?.24:streak?.17:.085)*profile.size*(.8+phase*.6);
      this.particles[slot]={origin,velocity,age:0,life,delay,hold:profile.hold,width,height,style:profile.kind,level:profile.level};this.positions.set(origin.toArray(),slot*3);this.alpha[slot]=delay?0:core?.4:.9;
      this.sizes[slot*2]=width*(core?.65:1);
      this.sizes[slot*2+1]=height*(core?.65:1);
      this.velocities.set(velocity.toArray(),slot*3);this.shapes[slot]=core?0:streak?1:2;this.seeds[slot]=a;
    }
    this.mesh.visible=true;this._dirty();return count;
  }
  _dirty(){for(const attribute of Object.values(this.mesh.geometry.attributes))if(attribute.isInstancedBufferAttribute)attribute.needsUpdate=true;}
  update(dt){
    if(this.disposed)return;const step=Number.isFinite(dt)?Math.max(0,dt):0;let active=0;
    for(let i=0;i<this.particles.length;i++){
      const p=this.particles[i];if(!p)continue;p.age+=step;
      const age=p.age-p.delay;
      if(age>=p.life){this.particles[i]=null;this.alpha[i]=0;continue;}
      active++;if(age<0){this.alpha[i]=0;continue;}
      const core=this.shapes[i]===0,growth=core?.65+.65*Math.min(age/.12,1):1;
      this.sizes[i*2]=p.width*growth;this.sizes[i*2+1]=p.height*growth;
      this.positions[i*3]=p.origin.x+p.velocity.x*age;this.positions[i*3+1]=p.origin.y+p.velocity.y*age-.5*BLOOD_FEEDBACK_ADAPTER.gravity*age*age;
      this.positions[i*3+2]=p.origin.z+p.velocity.z*age;
      const fade=Math.max(0,age-p.hold)/Math.max(.01,p.life-p.hold);
      this.alpha[i]=(core?.4:.9)*Math.pow(1-fade,.9);
    }
    this.mesh.visible=active>0;this._dirty();
  }
  clear(){this.particles.fill(null);this.alpha.fill(0);this.mesh.visible=false;this._dirty();}
  dispose(){if(this.disposed)return;this.clear();this.mesh.removeFromParent();this.mesh.geometry.dispose();this.mesh.material.dispose();this.disposed=true;}
}

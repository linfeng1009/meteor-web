import * as THREE from './vendor/three.module.js';

// Bounded presentation adapter. Emitted only after confirmed positive HP loss;
// blood motion, density and lifetime are not recovered EXE particle constants.
export const BLOOD_FEEDBACK_ADAPTER=Object.freeze({capacity:384,count:18,lifetime:.48,gravity:8});
export class NativeBloodFeedback{
  constructor(scene){
    this.scene=scene;this.cursor=0;this.disposed=false;this.particles=Array(BLOOD_FEEDBACK_ADAPTER.capacity).fill(null);
    const count=this.particles.length;this.positions=new Float32Array(count*3);this.alpha=new Float32Array(count);this.sizes=new Float32Array(count);
    const geometry=new THREE.BufferGeometry();
    geometry.setAttribute('position',new THREE.BufferAttribute(this.positions,3).setUsage(THREE.DynamicDrawUsage));
    geometry.setAttribute('opacity',new THREE.BufferAttribute(this.alpha,1).setUsage(THREE.DynamicDrawUsage));
    geometry.setAttribute('size',new THREE.BufferAttribute(this.sizes,1).setUsage(THREE.DynamicDrawUsage));
    const material=new THREE.ShaderMaterial({transparent:true,depthWrite:false,depthTest:true,toneMapped:false,uniforms:{focalScale:{value:900}},
      vertexShader:`attribute float opacity; attribute float size; uniform float focalScale; varying float fade;
        void main(){vec4 eye=modelViewMatrix*vec4(position,1.);fade=opacity;gl_Position=projectionMatrix*eye;
        gl_PointSize=opacity>0.&&eye.z<0.?clamp(size*focalScale/max(.1,-eye.z),1.,14.):0.;}`,
      fragmentShader:`varying float fade;void main(){vec2 p=(gl_PointCoord-.5)*2.;float d=length(p*vec2(1.,.72));
        if(d>1.||fade<=0.)discard;float a=(1.-smoothstep(.45,1.,d))*fade;
        gl_FragColor=vec4(mix(vec3(.24,.005,.012),vec3(.72,.025,.035),1.-d),a);
        #include <colorspace_fragment>
      }`});
    this.mesh=new THREE.Points(geometry,material);this.mesh.name='命中血滴 · 网页表现';this.mesh.frustumCulled=false;this.mesh.visible=false;scene.add(this.mesh);
  }
  emit({point,direction,damage=0,guarded=false}={}){
    if(this.disposed||guarded||!Number.isFinite(damage)||!(damage>0)||!point||![point.x,point.y,point.z].every(Number.isFinite)||direction&&![direction.x,direction.y,direction.z].every(Number.isFinite))return 0;
    const forward=direction?.clone()||new THREE.Vector3(0,0,1);forward.y=0;if(forward.lengthSq()<1e-8)forward.set(0,0,1);forward.normalize();
    const right=new THREE.Vector3(forward.z,0,-forward.x),count=BLOOD_FEEDBACK_ADAPTER.count;
    for(let i=0;i<count;i++){
      const slot=this.cursor++%this.particles.length,a=i*2.3999632297,speed=.6+(i%5)*.24;
      const velocity=forward.clone().multiplyScalar(speed).addScaledVector(right,Math.cos(a)*2.8);velocity.y=.8+Math.sin(a)*1.3+(i%3)*.22;
      const life=BLOOD_FEEDBACK_ADAPTER.lifetime+(i%4)*.035;
      this.particles[slot]={origin:point.clone(),velocity,age:0,life};this.positions.set(point.toArray(),slot*3);this.alpha[slot]=.9;this.sizes[slot]=.035+(i%4)*.009;
    }
    this.mesh.visible=true;this._dirty();return count;
  }
  _dirty(){for(const attribute of Object.values(this.mesh.geometry.attributes))attribute.needsUpdate=true;}
  update(dt,camera=null,height=900){
    if(this.disposed)return;const step=Number.isFinite(dt)?Math.max(0,dt):0;let active=0;
    if(camera?.fov&&Number.isFinite(height)&&height>0)this.mesh.material.uniforms.focalScale.value=height/(2*Math.tan(THREE.MathUtils.degToRad(camera.fov/2)));
    for(let i=0;i<this.particles.length;i++){
      const p=this.particles[i];if(!p)continue;p.age+=step;
      if(p.age>=p.life){this.particles[i]=null;this.alpha[i]=0;continue;}
      this.positions[i*3]=p.origin.x+p.velocity.x*p.age;this.positions[i*3+1]=p.origin.y+p.velocity.y*p.age-.5*BLOOD_FEEDBACK_ADAPTER.gravity*p.age*p.age;
      this.positions[i*3+2]=p.origin.z+p.velocity.z*p.age;this.alpha[i]=.9*(1-p.age/p.life)**1.5;active++;
    }
    this.mesh.visible=active>0;this._dirty();
  }
  clear(){this.particles.fill(null);this.alpha.fill(0);this.mesh.visible=false;this._dirty();}
  dispose(){if(this.disposed)return;this.clear();this.mesh.removeFromParent();this.mesh.geometry.dispose();this.mesh.material.dispose();this.disposed=true;}
}

import * as THREE from './vendor/three.module.js';

// Bounded object-URL ownership, including jobs that finish after leaving menus.
export class SnapshotCache {
  constructor(limit, revoke = url => URL.revokeObjectURL(url)) { this.limit=limit;this.revoke=revoke;this.entries=new Map();this.pending=new Map();this.generation=0; }
  async get(key, create) {
    if(this.entries.has(key)){const value=this.entries.get(key);this.entries.delete(key);this.entries.set(key,value);return value;}
    if(this.pending.has(key))return this.pending.get(key);
    const generation=this.generation;
    const job=(async()=>{
      const value=await create();if(!value)return null;
      if(generation!==this.generation){this.revoke(value);return null;}
      this.entries.set(key,value);
      while(this.entries.size>this.limit){const oldest=this.entries.keys().next().value;this.revoke(this.entries.get(oldest));this.entries.delete(oldest);}
      return value;
    })();
    this.pending.set(key,job);
    try{return await job;}finally{if(this.pending.get(key)===job)this.pending.delete(key);}
  }
  clear(){this.generation++;for(const value of this.entries.values())this.revoke(value);this.entries.clear();this.pending.clear();}
}

export function weaponPreviewSource(hero, swordStyle, spearStyle) {
  if(!hero)return null;
  if(hero.weapon==='sword'&&swordStyle==='butterfly'&&hero.butterflySword?.visible)return {style:'butterfly',models:[hero.butterflySword]};
  if(hero.weapon==='sword'&&swordStyle==='raiden'&&hero.raidenSword?.visible)return {style:'raiden',models:[hero.raidenSword]};
  if(hero.weapon==='spear'&&spearStyle==='phoenix'&&hero.phoenixSpear?.visible)return {style:'phoenix',models:[hero.phoenixSpear]};
  const models=(hero.weaponModels||[hero.weaponModel]).filter(model=>model?.visible);
  return models.length?{style:'original',models}:null;
}

export class MenuSnapshots {
  constructor(game){this.game=game;this.maps=new SnapshotCache(3);this.weapons=new SnapshotCache(6);}
  allowed(){return !this.game.disposed&&this.game.menuIdle&&!this.game.running;}
  clear(){this.maps.clear();this.weapons.clear();}
  async map(key){
    if(!this.allowed())return null;
    return this.maps.get(key,async()=>{
      if(!this.allowed())return null;
      const game=this.game,camera=game.camera.clone();camera.aspect=16/9;camera.updateProjectionMatrix();
      const spawn=game.hero.root.position;
      if(game.currentMap.menuCamera){camera.position.fromArray(game.currentMap.menuCamera.position);camera.lookAt(new THREE.Vector3(...game.currentMap.menuCamera.target));}
      else{const focus=spawn.clone().add(new THREE.Vector3(0,1.8,0)),desired=spawn.clone().add(new THREE.Vector3(7.5,5.5,11));camera.position.copy(game._safeCameraPosition?game._safeCameraPosition(focus,desired):desired);camera.fov=58;camera.updateProjectionMatrix();camera.lookAt(focus);}
      const actors=[game.hero,...game.enemies].map(actor=>[actor.root,actor.root.visible]);
      try{for(const [root] of actors)root.visible=false;return this.render(game.scene,camera,960,540);}
      finally{for(const [root,visible] of actors)root.visible=visible;}
    });
  }
  async weapon(key){
    if(!this.allowed())return null;
    const source=weaponPreviewSource(this.game.hero,this.game.swordStyle,this.game.spearStyle);if(!source)return null;
    const url=await this.weapons.get(key+':'+source.style,async()=>{
      if(!this.allowed())return null;
      const scene=new THREE.Scene(),group=new THREE.Group();scene.add(group);
      scene.add(new THREE.HemisphereLight(0xf5e7cc,0x385047,3));
      const light=new THREE.DirectionalLight(0xffffff,3);light.position.set(3,5,7);scene.add(light);
      source.models.forEach((model,index)=>{
        // Borrow geometry/materials; never dispose the equipment's shared assets.
        const clone=model.clone(true);clone.visible=true;clone.position.set(0,0,0);clone.rotation.set(0,0,0);
        clone.updateMatrixWorld(true);const box=new THREE.Box3().setFromObject(clone),center=box.getCenter(new THREE.Vector3());
        clone.position.sub(center);if(source.models.length>1)clone.position.x+=(index-(source.models.length-1)/2)*Math.max(box.getSize(new THREE.Vector3()).length()*.5,.1);
        group.add(clone);
      });
      group.updateMatrixWorld(true);const rawSize=new THREE.Box3().setFromObject(group).getSize(new THREE.Vector3());
      if(rawSize.z>rawSize.x&&rawSize.z>rawSize.y)group.rotation.y=Math.PI/2;else if(rawSize.y>rawSize.x)group.rotation.z=-Math.PI/2;
      group.quaternion.premultiply(new THREE.Quaternion().setFromEuler(new THREE.Euler(.1,.22,-.22)));group.updateMatrixWorld(true);
      const box=new THREE.Box3().setFromObject(group),size=box.getSize(new THREE.Vector3()),center=box.getCenter(new THREE.Vector3());
      if(!Number.isFinite(size.length())||size.length()===0)return null;
      group.position.sub(center);group.updateMatrixWorld(true);
      const half=Math.max(size.y,size.x/2,.01)*.6,distance=Math.max(size.length()*3,1);
      const camera=new THREE.OrthographicCamera(-half*2,half*2,half,-half,.01,distance*3);camera.position.set(0,0,distance);camera.lookAt(0,0,0);
      try{return await this.render(scene,camera,520,260);}finally{scene.clear();}
    });
    return url?{url,style:source.style}:null;
  }
  render(scene,camera,width,height){
    if(!this.allowed())return Promise.resolve(null);
    const renderer=this.game.renderer,target=new THREE.WebGLRenderTarget(width,height,{depthBuffer:true});
    target.texture.colorSpace=THREE.SRGBColorSpace;
    const previous={target:renderer.getRenderTarget(),viewport:renderer.getViewport(new THREE.Vector4()),scissor:renderer.getScissor(new THREE.Vector4()),scissorTest:renderer.getScissorTest(),color:renderer.getClearColor(new THREE.Color()),alpha:renderer.getClearAlpha(),autoClear:renderer.autoClear};
    const pixels=new Uint8Array(width*height*4);
    try{renderer.setRenderTarget(target);renderer.setScissorTest(false);renderer.autoClear=true;renderer.setClearColor(0x101919,0);renderer.render(scene,camera);renderer.readRenderTargetPixels(target,0,0,width,height,pixels);}
    finally{renderer.setRenderTarget(previous.target);renderer.setViewport(previous.viewport);renderer.setScissor(previous.scissor);renderer.setScissorTest(previous.scissorTest);renderer.setClearColor(previous.color,previous.alpha);renderer.autoClear=previous.autoClear;target.dispose();}
    const canvas=this.game.canvas.ownerDocument.createElement('canvas');canvas.width=width;canvas.height=height;
    const context=canvas.getContext('2d'),data=context.createImageData(width,height),stride=width*4;
    for(let y=0;y<height;y++)data.data.set(pixels.subarray((height-y-1)*stride,(height-y)*stride),y*stride);
    context.putImageData(data,0,0);
    return new Promise((resolve,reject)=>canvas.toBlob(blob=>{if(blob)resolve(URL.createObjectURL(blob));else reject(Error('预览图编码失败'));},'image/webp',.88));
  }
}

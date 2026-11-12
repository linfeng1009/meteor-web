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

export function visibleModelBounds(root){
  root.updateWorldMatrix(true,true);const box=new THREE.Box3();
  const visit=(node,visible)=>{visible=visible&&node.visible;if(!visible)return;if(node.isMesh)box.union(new THREE.Box3().setFromObject(node,true));for(const child of node.children)visit(child,visible);};visit(root,true);return box;
}
export function previewCamera(box,aspect,{yaw=0,pitch=0,zoom=1}={}){
  const center=box.getCenter(new THREE.Vector3()),size=box.getSize(new THREE.Vector3());
  const radius=Math.max(size.length(),.1),camera=new THREE.OrthographicCamera(-1,1,1,-1,.01,radius*6);
  const direction=new THREE.Vector3(Math.sin(yaw)*Math.cos(pitch),Math.sin(pitch),Math.cos(yaw)*Math.cos(pitch));
  camera.position.copy(center).addScaledVector(direction,radius*3);camera.lookAt(center);camera.updateMatrixWorld();
  let half=0;for(const x of [box.min.x,box.max.x])for(const y of [box.min.y,box.max.y])for(const z of [box.min.z,box.max.z]){const corner=new THREE.Vector3(x,y,z).applyMatrix4(camera.matrixWorldInverse);half=Math.max(half,Math.abs(corner.y),Math.abs(corner.x)/aspect);}
  half=Math.max(half,.05)*1.18/Math.max(.65,Math.min(zoom,2.5));camera.left=-half*aspect;camera.right=half*aspect;camera.top=half;camera.bottom=-half;camera.updateProjectionMatrix();return camera;
}

export class MenuSnapshots {
  constructor(game){this.game=game;this.maps=new SnapshotCache(3);this.weapons=new SnapshotCache(6);this.characters=new SnapshotCache(1);}
  allowed(){return !this.game.disposed&&this.game.menuIdle&&!this.game.running;}
  clear(){this.maps.clear();this.weapons.clear();this.characters.clear();this.characterBoundsKey=null;this.characterBounds=null;}
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
  async character(key,view={},canvas=null){
    if(!this.allowed())return null;
    const create=()=>{
      if(!this.allowed())return null;
      const root=this.game.hero.root,parent=root.parent,index=parent?.children.indexOf(root),scene=new THREE.Scene();
      const light=new THREE.DirectionalLight(0xffefd9,3);light.position.set(3,6,5);scene.add(light,new THREE.HemisphereLight(0xf1f5ff,0x425858,3));
      if(this.characterBoundsKey!==key){this.characterBoundsKey=key;this.characterBounds=visibleModelBounds(root);}
      const box=this.characterBounds.isEmpty()?new THREE.Box3(root.position.clone(),root.position.clone().add(new THREE.Vector3(1,3,1))):this.characterBounds;
      const width=canvas?.width||360,height=canvas?.height||480,camera=previewCamera(box,width/height,view);
      try{scene.add(root);return canvas?this.capture(scene,camera,width,height,canvas):this.render(scene,camera,width,height);}
      finally{scene.remove(root);if(parent){parent.add(root);parent.children.splice(parent.children.indexOf(root),1);parent.children.splice(index,0,root);}scene.clear();}
    };
    return canvas?create():this.characters.get(key,create);
  }
  async weapon(key,view={},canvas=null){
    if(!this.allowed())return null;
    const source=weaponPreviewSource(this.game.hero,this.game.swordStyle,this.game.spearStyle);if(!source)return null;
    const create=async()=>{
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
      const width=canvas?.width||520,height=canvas?.height||260;
      const camera=previewCamera(new THREE.Box3().setFromObject(group),width/height,{yaw:.35,pitch:.18,...view});
      try{return canvas?this.capture(scene,camera,width,height,canvas):await this.render(scene,camera,width,height);}finally{scene.clear();}
    };
    const url=canvas?await create():await this.weapons.get(key+':'+source.style,create);
    return canvas?url:url?{url,style:source.style}:null;
  }
  capture(scene,camera,width,height,destination){
    if(!this.allowed())return null;
    const renderer=this.game.renderer,target=new THREE.WebGLRenderTarget(width,height,{depthBuffer:true});
    target.texture.colorSpace=THREE.SRGBColorSpace;
    const previous={target:renderer.getRenderTarget(),viewport:renderer.getViewport(new THREE.Vector4()),scissor:renderer.getScissor(new THREE.Vector4()),scissorTest:renderer.getScissorTest(),color:renderer.getClearColor(new THREE.Color()),alpha:renderer.getClearAlpha(),autoClear:renderer.autoClear};
    const pixels=new Uint8Array(width*height*4);
    try{renderer.setRenderTarget(target);renderer.setScissorTest(false);renderer.autoClear=true;renderer.setClearColor(0x101919,0);renderer.render(scene,camera);renderer.readRenderTargetPixels(target,0,0,width,height,pixels);}
    finally{renderer.setRenderTarget(previous.target);renderer.setViewport(previous.viewport);renderer.setScissor(previous.scissor);renderer.setScissorTest(previous.scissorTest);renderer.setClearColor(previous.color,previous.alpha);renderer.autoClear=previous.autoClear;target.dispose();}
    const canvas=destination||this.game.canvas.ownerDocument.createElement('canvas');if(canvas.width!==width)canvas.width=width;if(canvas.height!==height)canvas.height=height;
    const context=canvas.getContext('2d'),data=context.createImageData(width,height),stride=width*4;
    for(let y=0;y<height;y++)data.data.set(pixels.subarray((height-y-1)*stride,(height-y)*stride),y*stride);
    context.putImageData(data,0,0);
    return canvas;
  }
  render(scene,camera,width,height){
    const canvas=this.capture(scene,camera,width,height);if(!canvas)return Promise.resolve(null);
    return new Promise((resolve,reject)=>canvas.toBlob(blob=>{if(blob)resolve(URL.createObjectURL(blob));else reject(Error('预览图编码失败'));},'image/webp',.88));
  }
}

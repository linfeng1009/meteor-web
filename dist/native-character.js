import * as THREE from './vendor/three.module.js';

// Original SKC skin + BNC rest skeleton + BANIM frame data. No procedural body.
// All input assets are read-only copies extracted by scripts/extract-character-assets.py.
const baseURL=new URL('./assets/original/characters/',import.meta.url);
const dataCache=new Map(), textureCache=new Map();
const clamp=(v,a,b)=>Math.max(a,Math.min(b,v));
export const NATIVE_POSES=Object.freeze({idle:0,swordReady:6,spearReady:7,bladeReady:8,guard:16,spearGuard:17,bladeGuard:18,walk:140,run:144,jump:151,fall:152,hit:90,death:117,attack:262,attack2:263,attack3:264,spearAttack:279,bladeAttack:295});
export const NATIVE_CHARACTERS=Object.freeze([{"id":0,"name":"孟星魂","portrait":"./assets/original/characters/portraits/p0.jpg"},{"id":1,"name":"冷燕","portrait":"./assets/original/characters/portraits/p1.jpg"},{"id":2,"name":"铁胡子","portrait":"./assets/original/characters/portraits/p2.jpg"},{"id":3,"name":"破空","portrait":"./assets/original/characters/portraits/p3.jpg"},{"id":4,"name":"夜猫子","portrait":"./assets/original/characters/portraits/p4.jpg"},{"id":5,"name":"冯浩","portrait":"./assets/original/characters/portraits/p5.jpg"},{"id":6,"name":"孙剑","portrait":"./assets/original/characters/portraits/p6.jpg"},{"id":7,"name":"萧安","portrait":"./assets/original/characters/portraits/p7.jpg"},{"id":8,"name":"子与","portrait":"./assets/original/characters/portraits/p8.jpg"},{"id":9,"name":"王强","portrait":"./assets/original/characters/portraits/p9.jpg"},{"id":10,"name":"无名","portrait":"./assets/original/characters/portraits/p10.jpg"},{"id":11,"name":"叶翔","portrait":"./assets/original/characters/portraits/p11.jpg"},{"id":12,"name":"小何","portrait":"./assets/original/characters/portraits/p12.jpg"},{"id":13,"name":"凤凰","portrait":"./assets/original/characters/portraits/p13.jpg"},{"id":14,"name":"石群","portrait":"./assets/original/characters/portraits/p14.jpg"},{"id":15,"name":"屠城","portrait":"./assets/original/characters/portraits/p15.jpg"},{"id":16,"name":"范璇","portrait":"./assets/original/characters/portraits/p16.jpg"},{"id":17,"name":"高寄萍","portrait":"./assets/original/characters/portraits/p17.jpg"},{"id":18,"name":"孙玉伯","portrait":"./assets/original/characters/portraits/p18.jpg"},{"id":19,"name":"律香川","portrait":"./assets/original/characters/portraits/p19.jpg"}]);

export function parseNativeSkin(text){
  const materials=[...text.matchAll(/^\s*Material\s*\r?\n([\s\S]*?)(?=^\s*Material\s*$|^\s*Vertices:)/gm)].map(m=>({texture:m[1].match(/Texture\s+(\S+)/)?.[1].toLowerCase(),twoSide:/TwoSide\s+TRUE/i.test(m[1]),alpha:/Option\s+ALPHA/i.test(m[1]),opacity:Number(m[1].match(/Opacity\s+(\S+)/)?.[1]??1)}));
  const positions=[],uvs=[],skinIndices=[],skinWeights=[],faces=[];
  for(const m of text.matchAll(/^\s*v\s+([^\r\n]+)/gm)){
    const t=m[1].trim().split(/\s+/),uv=t.indexOf('vt'),bp=t.indexOf('Bones'),count=Number(t[bp+1]);
    positions.push(...t.slice(0,3).map(Number));uvs.push(Number(t[uv+1]),Number(t[uv+2]));
    const influences=Array.from({length:count},(_,i)=>[Number(t[bp+2+i*2]),Number(t[bp+3+i*2])]).sort((a,b)=>b[1]-a[1]).slice(0,4);
    const sum=influences.reduce((n,v)=>n+v[1],0)||1;
    for(let i=0;i<4;i++){skinIndices.push(influences[i]?.[0]??0);skinWeights.push((influences[i]?.[1]??0)/sum);}
  }
  for(const m of text.matchAll(/^\s*f\s+([^\r\n]+)/gm)){
    const t=m[1].trim().split(/\s+/).map(Number);if(t[0]!==3)throw new Error('Native skin uses unsupported non-triangle face');faces.push({material:t[1],indices:t.slice(2,5)});
  }
  const nv=Number(text.match(/Vertices:\s*(\d+)/)?.[1]),nf=Number(text.match(/Triangles:\s*(\d+)/)?.[1]);
  if(positions.length!==nv*3||faces.length!==nf||!materials.length||positions.some(v=>!Number.isFinite(v))||faces.some(f=>f.material<0||f.material>=materials.length||f.indices.some(v=>v<0||v>=nv)))throw new Error('Invalid native SKC geometry');
  return {materials,positions,uvs,skinIndices,skinWeights,faces,vertexCount:nv,triangleCount:nf};
}

export function parseNativeBones(text){
  const entries=[...text.matchAll(/\b(bone|Dummey)\s+(\S+)\s*\{([^}]+)\}/g)].map(m=>{
    const get=name=>m[3].match(new RegExp(name+'\\s+([^\\r\\n]+)'))?.[1].trim();
    return {kind:m[1]==='bone'?'bone':'dummy',name:m[2],parent:get('parent'),position:get('pivot').split(/\s+/).map(Number),quaternion:get('quaternion').split(/\s+/).map(Number)};
  });
  const bones=entries.filter(e=>e.kind==='bone'),dummies=entries.filter(e=>e.kind==='dummy');
  if(bones.length!==Number(text.match(/Bones:\s*(\d+)/)?.[1])||dummies.length!==Number(text.match(/Dummey:\s*(\d+)/)?.[1]))throw new Error('Invalid BNC skeleton count');
  return {entries,bones,dummies};
}

export function parseNativeAnimation(buffer){
  const bytes=new Uint8Array(buffer),v=new DataView(buffer),decoder=new TextDecoder();
  if(decoder.decode(bytes.subarray(0,5))!=='BANIM')throw new Error('Unsupported native animation');
  const boneCount=v.getInt32(5,true),dummyCount=v.getInt32(9,true),frameCount=v.getInt32(13,true),fps=v.getInt32(17,true),stride=20+boneCount*16+dummyCount*33;
  if(boneCount<=0||boneCount>512||dummyCount<0||dummyCount>512||frameCount<=0||fps<=0||21+stride*frameCount!==bytes.length)throw new Error('Invalid BANIM dimensions');
  const frameOffset=frame=>21+clamp(Math.floor(frame),0,frameCount-1)*stride;
  for(let frame=0;frame<frameCount;frame++){const o=frameOffset(frame);if(v.getInt32(o,true)!==-1||v.getInt32(o+4,true)!==frame)throw new Error('Invalid BANIM frame sequence');}
  return {buffer,view:v,bytes,decoder,boneCount,dummyCount,frameCount,fps,stride,frameOffset};
}

export function parseNativePoses(text){
  const poses={};
  for(const m of text.matchAll(/^Pose\s+(\d+)[^\r\n]*\r?\n\s*\{/gm)){
    let depth=1,end=m.index+m[0].length;
    for(;end<text.length&&depth;end++){if(text[end]==='{')depth++;else if(text[end]==='}')depth--;}
    const block=text.slice(m.index+m[0].length,end-1),get=key=>block.match(new RegExp('^\\s*'+key+'\\s+(-?[\\d.]+)','im'))?.[1];
    const start=get('Start'),finish=get('End');if(start===undefined||finish===undefined)continue;
    poses[Number(m[1])]={id:Number(m[1]),source:Number(get('source')??0),start:Number(start),end:Number(finish),loopStart:get('LoopStart')===undefined?null:Number(get('LoopStart')),loopEnd:get('LoopEnd')===undefined?null:Number(get('LoopEnd')),link:get('link')===undefined?null:Number(get('link'))};
  }
  return poses;
}

async function resource(url,type='text'){
  const response=await fetch(url);if(!response.ok)throw new Error(`Native character asset ${response.status}: ${url}`);return type==='buffer'?response.arrayBuffer():response.text();
}
function cachedData(id){
  const key=String(id).replace(/^p/,'');
  if(!/^\d+$/.test(key))throw new Error('Invalid character id');
  if(!dataCache.has(key))dataCache.set(key,(async()=>{
    const path=new URL(`p${key}/`,baseURL);
    const [skin,bnc,personal,common,pos]=await Promise.all([resource(new URL(`p${key}.skc`,path)),resource(new URL(`p${key}.bnc`,path)),resource(new URL(`p${key}.amb`,path),'buffer'),getCommon(),resource(new URL(`p${key}.pos`,path))]);
    return {id:Number(key),path,skin:parseNativeSkin(skin),skeleton:parseNativeBones(bnc),animations:[common,parseNativeAnimation(personal)],poses:parseNativePoses(pos)};
  })().catch(error=>{dataCache.delete(key);throw error;}));
  return dataCache.get(key);
}
let commonPromise;
function getCommon(){return commonPromise??=(resource(new URL('common/character.amb',baseURL),'buffer').then(parseNativeAnimation).catch(e=>{commonPromise=null;throw e;}));}
function nativeTexture(url){
  const key=String(url);if(!textureCache.has(key))textureCache.set(key,new Promise((resolve,reject)=>new THREE.TextureLoader().load(key,t=>{t.colorSpace=THREE.SRGBColorSpace;t.anisotropy=4;resolve(t);},undefined,reject)));
  return textureCache.get(key);
}
function webTextureName(name){return name.replace(/\.(tga|bmp)$/i,'.png');}
function applyQuaternion(target,wxyz){target.set(wxyz[1],wxyz[2],wxyz[3],wxyz[0]).normalize();}

export function createNativeCharacter(data,options={}){
  const {scale=.08,inPlace=true,interpolate=true,loadTextures=true}=options;
  const group=new THREE.Group();group.name=`原版${NATIVE_CHARACTERS.find(c=>c.id===data.id)?.name??`角色${data.id}`}`;
  group.userData={nativeCharacter:true,characterId:data.id,sourceFormat:'SKC+BNC+AMB+POS',nativeScale:scale};
  const nativeSpace=new THREE.Group();group.add(nativeSpace);
  const byName=new Map(),boneNodes=[],dummyNodes=[];
  for(const entry of data.skeleton.entries){const bone=new THREE.Bone();bone.name=entry.name;bone.position.fromArray(entry.position);applyQuaternion(bone.quaternion,entry.quaternion);byName.set(entry.name,bone);(entry.kind==='bone'?boneNodes:dummyNodes).push(bone);}
  const resolve=name=>byName.get(name)||(/^b\d+$/.test(name)?boneNodes[Number(name.slice(1))]:/^d\d+$/.test(name)?dummyNodes[Number(name.slice(1))]:null);
  for(const entry of data.skeleton.entries){const node=byName.get(entry.name),parent=resolve(entry.parent);(parent||nativeSpace).add(node);}
  const materials=data.skin.materials.map(s=>new THREE.MeshStandardMaterial({color:0xffffff,roughness:.85,metalness:0,side:s.twoSide?THREE.DoubleSide:THREE.FrontSide,transparent:s.opacity<.99,opacity:s.opacity,alphaTest:s.alpha ? 0.35 : 0}));
  const geometry=new THREE.BufferGeometry();geometry.setAttribute('position',new THREE.Float32BufferAttribute(data.skin.positions,3));geometry.setAttribute('uv',new THREE.Float32BufferAttribute(data.skin.uvs,2));geometry.setAttribute('skinIndex',new THREE.Uint16BufferAttribute(data.skin.skinIndices,4));geometry.setAttribute('skinWeight',new THREE.Float32BufferAttribute(data.skin.skinWeights,4));
  const indices=[];for(let i=0;i<materials.length;i++){const start=indices.length;for(const f of data.skin.faces)if(f.material===i)indices.push(...f.indices);if(indices.length>start)geometry.addGroup(start,indices.length-start,i);}
  geometry.setIndex(indices);geometry.computeVertexNormals();geometry.computeBoundingSphere();
  const mesh=new THREE.SkinnedMesh(geometry,materials);mesh.name=`p${data.id}.skc`;mesh.castShadow=true;mesh.receiveShadow=true;mesh.frustumCulled=false;nativeSpace.add(mesh);
  nativeSpace.updateMatrixWorld(true);const skeleton=new THREE.Skeleton(boneNodes);mesh.bind(skeleton);mesh.normalizeSkinWeights();
  nativeSpace.rotation.x=-Math.PI/2;nativeSpace.scale.setScalar(scale);
  const animationState={pose:null,time:0,rate:1,loop:false,finished:false,external:false};
  const qa=new THREE.Quaternion(),qb=new THREE.Quaternion(),positionA=new THREE.Vector3(),positionB=new THREE.Vector3();
  let previousParentNames='',stateName='idle';
  const sampleRoot=(source,frame)=>{
    const a=data.animations[Number(source)];if(!a)throw new Error('Invalid animation source');
    const f=clamp(Number(frame)||0,0,a.frameCount-1),lo=Math.floor(f),hi=Math.min(lo+1,a.frameCount-1),t=f-lo,o=a.frameOffset(lo)+8,p=a.frameOffset(hi)+8,v=a.view;
    return {x:THREE.MathUtils.lerp(v.getFloat32(o,true),v.getFloat32(p,true),t),y:THREE.MathUtils.lerp(v.getFloat32(o+4,true),v.getFloat32(p+4,true),t),z:THREE.MathUtils.lerp(v.getFloat32(o+8,true),v.getFloat32(p+8,true),t)};
  };
  function readQ(v,o,q){q.set(v.getFloat32(o+4,true),v.getFloat32(o+8,true),v.getFloat32(o+12,true),v.getFloat32(o,true)).normalize();}
  function setPoseFrame(source,frame,frameOptions={}){
    if(!frameOptions.managed)animationState.external=true;
    const a=data.animations[Number(source)];if(!a||a.boneCount!==boneNodes.length||a.dummyCount!==dummyNodes.length)throw new Error('Animation does not match native skeleton');
    const f=clamp(Number(frame)||0,0,a.frameCount-1),lo=Math.floor(f),hi=Math.min(lo+1,a.frameCount-1),t=interpolate?f-lo:0,o=a.frameOffset(lo),p=a.frameOffset(hi),v=a.view;
    const root=sampleRoot(source,f),rootMotion=frameOptions.rootMotion??!inPlace;
    boneNodes[0].position.set(rootMotion?root.x:0,rootMotion?root.y:0,root.z);
    for(let i=0;i<boneNodes.length;i++){readQ(v,o+20+i*16,qa);readQ(v,p+20+i*16,qb);boneNodes[i].quaternion.copy(qa).slerp(qb,t);}
    const start=o+20+a.boneCount*16,next=p+20+a.boneCount*16;
    const parents=dummyNodes.map((_,i)=>a.decoder.decode(a.bytes.subarray(start+i*33,start+i*33+5)).replace(/\0+$/,''));
    const signature=parents.join('|');
    if(signature!==previousParentNames){for(const dummy of dummyNodes)nativeSpace.add(dummy);for(let i=0;i<dummyNodes.length;i++){const parent=resolve(parents[i]);(parent||nativeSpace).add(dummyNodes[i]);}previousParentNames=signature;}
    for(let i=0;i<dummyNodes.length;i++){
      const x=start+i*33+5,y=next+i*33+5;
      positionA.set(v.getFloat32(x,true),v.getFloat32(x+4,true),v.getFloat32(x+8,true));positionB.set(v.getFloat32(y,true),v.getFloat32(y+4,true),v.getFloat32(y+8,true));dummyNodes[i].position.copy(positionA).lerp(positionB,t);
      readQ(v,x+12,qa);readQ(v,y+12,qb);dummyNodes[i].quaternion.copy(qa).slerp(qb,t);
    }
    group.updateMatrixWorld(true);skeleton.update();api.source=Number(source);api.frame=f;return api;
  }
  function playPose(poseId,{loop,rate=1,restart=false}={}){
    const pose=data.poses[typeof poseId==='string'&&!/^\d+$/.test(poseId)?NATIVE_POSES[poseId]:Number(poseId)];if(!pose)return false;
    if(animationState.pose?.id===pose.id&&!restart&&!animationState.external)return true;
    Object.assign(animationState,{pose,time:0,rate,loop:loop??pose.loopStart!==null,finished:false,external:false});setPoseFrame(pose.source,pose.start,{managed:true});return true;
  }
  function update(dt,state){
    if(state&&typeof state==='object'&&state.source!==undefined&&state.frame!==undefined){setPoseFrame(state.source,state.frame,state);animationState.external=true;return;}
    if(state!==undefined){const next=typeof state==='string'?state:state.pose??state.state;if(next!==undefined){const poseId=typeof next==='number'?next:(NATIVE_POSES[next]??(/^\d+$/.test(String(next))?Number(next):NATIVE_POSES.idle));if(String(next)!==stateName||animationState.pose?.id!==poseId||animationState.external){stateName=String(next);playPose(poseId,{loop:typeof state==='object'?state.loop:undefined,rate:typeof state==='object'?state.rate??1:1,restart:animationState.external});}}}
    if(!animationState.pose||animationState.external)return;
    const pose=animationState.pose,a=data.animations[pose.source];animationState.time+=Math.max(0,dt)*animationState.rate;
    let frame=pose.start+animationState.time*a.fps;
    if(frame>pose.end){if(animationState.loop){const begin=pose.loopStart??pose.start,end=pose.loopEnd??pose.end;frame=begin+(frame-begin)%Math.max(1,end-begin+1);}else{frame=pose.end;animationState.finished=true;}}
    setPoseFrame(pose.source,frame,{managed:true});
  }
  const api={group,mesh,skeleton,bones:boneNodes,dummies:dummyNodes,nativeSpace,poses:data.poses,animations:data.animations,source:1,frame:1,update,playPose,setPoseFrame,sampleRoot,getAttachment:name=>byName.get(name)||resolve(name),get finished(){return animationState.finished;},get currentPose(){return animationState.pose?.id??null;},getAttachmentPosition(name,target=new THREE.Vector3()){return resolve(name)?.getWorldPosition(target)||null;},dispose(){geometry.dispose();materials.forEach(m=>m.dispose());skeleton.dispose();group.removeFromParent();}};
  api.ready=loadTextures?Promise.all(materials.map(async(material,i)=>{const textureName=data.skin.materials[i].texture;if(!textureName||textureName==='null')return;const url=new URL(`textures/${webTextureName(textureName)}`,data.path);material.map=await nativeTexture(url);material.needsUpdate=true;})):Promise.resolve();
  playPose(0,{loop:true});return api;
}

export async function loadNativeCharacter(id=0,options={}){const data=await cachedData(id),character=createNativeCharacter(data,options);await character.ready;return character;}
export const loadNativeCharacterData=cachedData;

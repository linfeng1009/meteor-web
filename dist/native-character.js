import * as THREE from './vendor/three.module.js';
import { parsePos } from './native-combat.js';
import { createHairSprings, validateHairRig } from './hair-springs.js';
import {createProportionalRig,validateProportionalRig} from './proportional-rig.js';
import {configureSourceMaterial} from './character-materials.js';

// Original SKC skin + BNC rest skeleton + BANIM frame data. No procedural body.
// All input assets are read-only copies extracted by scripts/extract-character-assets.py.
const baseURL=new URL('./assets/original/characters/',import.meta.url);
const dataCache=new Map(), textureCache=new Map(), enhancedCache=new Map();
const clamp=(v,a,b)=>Math.max(a,Math.min(b,v));
export const NATIVE_APPEARANCES=Object.freeze({
  original:Object.freeze({id:'original',label:'原版人物',characterId:null}),
  hd:Object.freeze({id:'hd',label:'孟星魂 · 高清试制',characterId:0,assetPath:'./assets/enhanced/p0/'}),
  hutao:Object.freeze({id:'hutao',label:'YS-胡桃 · 模型适配',characterId:0,assetPath:'./assets/enhanced/hutao/'}),
  raiden:Object.freeze({id:'raiden',label:'YS-影 · 模型适配',characterId:0,assetPath:'./assets/enhanced/raiden/'}),
  emilia:Object.freeze({id:'emilia',label:'RE0-爱蜜莉雅 · 模型适配',characterId:0,assetPath:'./assets/enhanced/emilia/'}),
  doubao:Object.freeze({id:'doubao',label:'豆包 · 模型适配',characterId:0,assetPath:'./assets/enhanced/doubao/'}),
  springfield:Object.freeze({id:'springfield',label:'春田 · 泳装P3',characterId:0,assetPath:'./assets/enhanced/springfield/'}),
  ganyu:Object.freeze({id:'ganyu',label:'甘雨 · 模型适配',characterId:0,assetPath:'./assets/enhanced/ganyu/'}),
  yaemiko:Object.freeze({id:'yaemiko',label:'八重神子 · 模型适配',characterId:0,assetPath:'./assets/enhanced/yaemiko/'}),
  shogun:Object.freeze({id:'shogun',label:'雷电将军 · 模型适配',characterId:0,assetPath:'./assets/enhanced/shogun/'}),
  lumine:Object.freeze({id:'lumine',label:'荧 · 模型适配',characterId:0,assetPath:'./assets/enhanced/lumine/'}),
  aether:Object.freeze({id:'aether',label:'空 · 模型适配',characterId:0,assetPath:'./assets/enhanced/aether/'}),
  furina:Object.freeze({id:'furina',label:'芙宁娜 · 模型适配',characterId:0,assetPath:'./assets/enhanced/furina/'}),
  zhaojun:Object.freeze({id:'zhaojun',label:'王昭君 · 长夜焕生',characterId:0,assetPath:'./assets/enhanced/zhaojun/'})
});
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
    return {id:Number(key),path,skin:parseNativeSkin(skin),skeleton:parseNativeBones(bnc),animations:[common,parseNativeAnimation(personal)],poses:parseNativePoses(pos),combatPoses:parsePos(pos,{file:`pmodel/P${key}.POS`})};
  })().catch(error=>{dataCache.delete(key);throw error;}));
  return dataCache.get(key);
}
let commonPromise;
function getCommon(){return commonPromise??=(resource(new URL('common/character.amb',baseURL),'buffer').then(parseNativeAnimation).catch(e=>{commonPromise=null;throw e;}));}
function nativeTexture(url,color=true){
  // Textures are shared between actors and appearance variants. Only the
  // actor-owned geometry/materials are disposed; these cached maps stay alive.
  const key=`${color?'color':'data'}:${url}`;if(!textureCache.has(key))textureCache.set(key,new Promise((resolve,reject)=>new THREE.TextureLoader().load(String(url),t=>{t.colorSpace=color?THREE.SRGBColorSpace:THREE.NoColorSpace;t.anisotropy=4;resolve(t);},undefined,reject)).catch(error=>{textureCache.delete(key);throw error;}));
  return textureCache.get(key);
}
function webTextureName(name){return name.replace(/\.(tga|bmp)$/i,'.png');}
function applyQuaternion(target,wxyz){target.set(wxyz[1],wxyz[2],wxyz[3],wxyz[0]).normalize();}

// The Blender export uses the same native Z-up coordinates, bone indices and
// UV convention as SKC. Never replace BNC, AMB, POS or the attachment hierarchy.
export function validateEnhancedSkin(skin,boneCount=30){
  validateProportionalRig(skin?.bodyRig,boneCount);
  const totalBones=boneCount+validateHairRig(skin?.secondaryMotion,boneCount);
  const finite=values=>Array.isArray(values)&&values.every(Number.isFinite),nv=skin?.positions?.length/3;
  if(!Number.isInteger(nv)||nv<3||!finite(skin.positions)||!finite(skin.uvs)||skin.uvs.length!==nv*2||!finite(skin.skinIndices)||skin.skinIndices.length!==nv*4||!finite(skin.skinWeights)||skin.skinWeights.length!==nv*4||!Array.isArray(skin.materials)||!skin.materials.length||!Array.isArray(skin.faces)||!skin.faces.length)throw new Error('Invalid enhanced character geometry');
  if(skin.skinIndices.some(i=>!Number.isInteger(i)||i<0||i>=totalBones)||skin.skinWeights.some(w=>w<0))throw new Error('Enhanced character uses an incompatible skeleton');
  for(let i=0;i<nv;i++){const sum=skin.skinWeights.slice(i*4,i*4+4).reduce((a,b)=>a+b,0);if(Math.abs(sum-1)>.01)throw new Error('Invalid enhanced character skin weights');}
  if(skin.faces.some(f=>!Number.isInteger(f.material)||f.material<0||f.material>=skin.materials.length||!Array.isArray(f.indices)||f.indices.length!==3||f.indices.some(i=>!Number.isInteger(i)||i<0||i>=nv)))throw new Error('Invalid enhanced character faces');
  if(skin.normals!==undefined&&(!finite(skin.normals)||skin.normals.length!==nv*3))throw new Error('Invalid enhanced character normals');
  return {...skin,vertexCount:nv,triangleCount:skin.faces.length};
}
export async function loadEnhancedCharacterData(id=0,appearance='hd'){
  const descriptor=NATIVE_APPEARANCES[appearance];
  if(!descriptor?.assetPath)throw new Error('Unknown enhanced character appearance');
  if(Number(id)!==descriptor.characterId)throw new Error(`${descriptor.label}目前仅提供孟星魂骨架适配`);
  const key=`${Number(id)}:${appearance}`,enhancedURL=new URL(descriptor.assetPath,import.meta.url);
  if(!enhancedCache.has(key))enhancedCache.set(key,(async()=>{
    const manifestResponse=await fetch(new URL('manifest.json',enhancedURL));if(!manifestResponse.ok)throw new Error(`高清资源尚未就绪（${manifestResponse.status}）`);
    const manifest=await manifestResponse.json();if(manifest.characterId!==descriptor.characterId||typeof manifest.mesh!=='string'||(manifest.appearance!==undefined&&manifest.appearance!==appearance))throw new Error('人物外观资源清单与骨架或外观不匹配');
    const meshURL=new URL(manifest.mesh,enhancedURL),meshResponse=await fetch(meshURL);if(!meshResponse.ok)throw new Error(`高清模型读取失败（${meshResponse.status}）`);
    return {manifest,skin:validateEnhancedSkin(await meshResponse.json()),path:new URL('./',meshURL)};
  })().catch(error=>{enhancedCache.delete(key);throw error;}));
  return enhancedCache.get(key);
}

function appearanceCompleteness(manifest){
  const complete=manifest?.complete!==false&&manifest?.completeness?.faceGeometry!==false;
  const reason=complete?null:(manifest?.incompleteReason|| (manifest?.completeness?.faceGeometry===false?'人物模型缺少脸部网格，当前只能查看不完整预览':'人物模型资源尚不完整，当前只能查看不完整预览'));
  return {complete,completeness:manifest?.completeness??null,reason};
}

function createSkinVisual(skin,path,{enhanced=false,loadTextures=true}={}){
  const materials=skin.materials.map(s=>{
    const opacity=Number.isFinite(s.opacity)?clamp(s.opacity,0,1):1;
    // PMX hair/eyelash cards use cutout textures. Keep those depth-writing and
    // opaque; alpha blending would sort overlapping eyes, hair and face badly.
    const alphaTest=Number.isFinite(s.alphaTest)?clamp(s.alphaTest,0,1):(s.alpha ? .35 : 0);
    const transparent=typeof s.transparent==='boolean'?s.transparent:opacity<.99;
    const Material=enhanced&&(s.hairSurface||s.skinSurface)?THREE.MeshPhysicalMaterial:THREE.MeshStandardMaterial;
    const material=new Material({name:s.name??'',color:enhanced?(s.color??0xffffff):0xffffff,roughness:enhanced?(s.roughness??.78):.85,metalness:enhanced?(s.metalness??0):0,side:s.twoSide?THREE.DoubleSide:THREE.FrontSide,transparent,opacity,alphaTest,depthWrite:s.depthWrite??true});
    if(enhanced)configureSourceMaterial(material,s);
    return material;
  });
  if(enhanced)materials.forEach((material,i)=>{const strength=skin.materials[i].normalScale;if(Number.isFinite(strength))material.normalScale.setScalar(strength);else if(Array.isArray(strength)&&strength.length===2&&strength.every(Number.isFinite))material.normalScale.fromArray(strength);});
  const geometry=new THREE.BufferGeometry();geometry.setAttribute('position',new THREE.Float32BufferAttribute(skin.positions,3));geometry.setAttribute('uv',new THREE.Float32BufferAttribute(skin.uvs,2));geometry.setAttribute('skinIndex',new THREE.Uint16BufferAttribute(skin.skinIndices,4));geometry.setAttribute('skinWeight',new THREE.Float32BufferAttribute(skin.skinWeights,4));
  const indices=[];for(let i=0;i<materials.length;i++){const start=indices.length;for(const f of skin.faces)if(f.material===i)indices.push(...f.indices);if(indices.length>start)geometry.addGroup(start,indices.length-start,i);}
  geometry.setIndex(indices);if(skin.normals)geometry.setAttribute('normal',new THREE.Float32BufferAttribute(skin.normals,3));else geometry.computeVertexNormals();geometry.computeBoundingSphere();
  const mesh=new THREE.SkinnedMesh(geometry,materials);mesh.castShadow=true;mesh.receiveShadow=true;mesh.frustumCulled=false;
  const dispose=()=>{geometry.dispose();materials.forEach(m=>m.dispose());mesh.removeFromParent();};
  const ready=loadTextures?Promise.all(materials.map(async(material,i)=>{
    const s=skin.materials[i],textureName=s.texture;
    if(textureName&&textureName!=='null'){material.map=await nativeTexture(new URL(enhanced?textureName:`textures/${webTextureName(textureName)}`,path));if(enhanced&&Number.isFinite(s.textureAnisotropy))material.map.anisotropy=clamp(s.textureAnisotropy,1,16);material.needsUpdate=true;}
    if(enhanced)for(const [key,name] of [['normalMap',s.normal],['roughnessMap',s.roughnessMap]])if(name){material[key]=await nativeTexture(new URL(name,path),false);material.needsUpdate=true;}
  })):Promise.resolve();
  return {mesh,ready,secondaryMotion:null,proportionalRig:null,dispose(){this.secondaryMotion?.dispose();this.proportionalRig?.dispose();dispose();}};
}

export function createNativeCharacter(data,options={}){
  const {scale=.08,inPlace=true,interpolate=true,loadTextures=true}=options;
  const characterName=NATIVE_CHARACTERS.find(c=>c.id===data.id)?.name??`角色${data.id}`;
  const group=new THREE.Group();group.name=`原版${characterName}`;
  group.userData={nativeCharacter:true,characterId:data.id,appearance:'original',sourceFormat:'SKC+BNC+AMB+POS',nativeScale:scale};
  const nativeSpace=new THREE.Group();group.add(nativeSpace);
  const byName=new Map(),boneNodes=[],dummyNodes=[],poseListeners=new Set();
  for(const entry of data.skeleton.entries){const bone=new THREE.Bone();bone.name=entry.name;bone.position.fromArray(entry.position);applyQuaternion(bone.quaternion,entry.quaternion);byName.set(entry.name,bone);(entry.kind==='bone'?boneNodes:dummyNodes).push(bone);}
  const resolve=name=>byName.get(name)||(/^b\d+$/.test(name)?boneNodes[Number(name.slice(1))]:/^d\d+$/.test(name)?dummyNodes[Number(name.slice(1))]:null);
  for(const entry of data.skeleton.entries){const node=byName.get(entry.name),parent=resolve(entry.parent);(parent||nativeSpace).add(node);}
  const motionBase=byName.get('d_base'),motionBaseRest=motionBase?.position.clone();
  const originalVisual=createSkinVisual(data.skin,data.path,{loadTextures});
  let mesh=originalVisual.mesh;mesh.name=`p${data.id}.skc`;nativeSpace.add(mesh);
  nativeSpace.updateMatrixWorld(true);const skeleton=new THREE.Skeleton(boneNodes);mesh.bind(skeleton);mesh.normalizeSkinWeights();
  const bindMatrix=mesh.bindMatrix.clone(),visuals=new Map([['original',originalVisual]]),pendingVisuals=new Map();
  let disposed=false,appearanceRequest=0,appearance='original',appearanceState={requested:'original',appearance:'original',available:true,complete:true,previewOnly:false,reason:null,label:`原版${characterName}`};
  let secondaryMotionEnabled=options.secondaryMotion!==false;
  const visualAttachments=new Map(),visualSockets=new Map();
  const socketMatrix=new THREE.Matrix4(),socketTarget=new THREE.Matrix4(),socketOffset=new THREE.Vector3(),socketPosition=new THREE.Vector3();
  function syncDisplayRig(){visuals.get(appearance)?.proportionalRig?.sync();}
  function getVisualAttachmentMatrix(name,target=new THREE.Matrix4()){
    const host=resolve(name);if(!host)return null;
    target.copy(host.matrixWorld);
    const rig=visuals.get(appearance)?.proportionalRig;
    if(rig){
      let parent=host;while(parent&&!boneNodes.includes(parent))parent=parent.parent;
      const index=boneNodes.indexOf(parent);
      if(index>=0){socketOffset.setFromMatrixPosition(rig.bones[index].matrixWorld).sub(socketPosition.setFromMatrixPosition(parent.matrixWorld));target.setPosition(socketPosition.setFromMatrixPosition(host.matrixWorld).add(socketOffset));}
    }
    return target;
  }
  function syncVisualAttachments(){
    const rig=visuals.get(appearance)?.proportionalRig;
    for(const [model,entry]of visualAttachments){
      if(!model.parent){visualAttachments.delete(model);continue;}
      if(dummyNodes.includes(model.parent))entry.name=model.parent.name;
      const host=resolve(entry.name);if(!host)continue;
      if(!rig){if(model.parent!==host)host.add(model);continue;}
      let socket=visualSockets.get(entry.name);
      if(!socket){socket=new THREE.Group();socket.name='source-display_'+entry.name;socket.matrixAutoUpdate=false;host.add(socket);visualSockets.set(entry.name,socket);}
      getVisualAttachmentMatrix(entry.name,socketTarget);
      socket.matrix.copy(socketMatrix.copy(host.matrixWorld).invert().multiply(socketTarget));socket.matrixWorldNeedsUpdate=true;
      if(model.parent!==socket)socket.add(model);socket.updateMatrixWorld(true);
    }
  }
  function registerVisualAttachment(model,name){visualAttachments.set(model,{name});syncVisualAttachments();return model;}
  nativeSpace.rotation.x=-Math.PI/2;nativeSpace.scale.setScalar(scale);
  const animationState={pose:null,time:0,rate:1,loop:false,finished:false,external:false};
  const qa=new THREE.Quaternion(),qb=new THREE.Quaternion(),positionA=new THREE.Vector3(),positionB=new THREE.Vector3();
  let previousParentNames='',stateName='idle';
  const sampleRoot=(source,frame)=>{
    const a=data.animations[Number(source)];if(!a)throw new Error('Invalid animation source');
    const f=clamp(Number(frame)||0,0,a.frameCount-1),lo=Math.floor(f),hi=Math.min(lo+1,a.frameCount-1),t=f-lo,o=a.frameOffset(lo)+8,p=a.frameOffset(hi)+8,v=a.view;
    return {x:THREE.MathUtils.lerp(v.getFloat32(o,true),v.getFloat32(p,true),t),y:THREE.MathUtils.lerp(v.getFloat32(o+4,true),v.getFloat32(p+4,true),t),z:THREE.MathUtils.lerp(v.getFloat32(o+8,true),v.getFloat32(p+8,true),t)};
  };
  // d_base is the authored scene-motion track, distinct from the pelvis.
  // Read it without moving the rendered skin or any weapon attachment.
  const sampleSceneMotion=(source,frame)=>{
    const a=data.animations[Number(source)],index=dummyNodes.indexOf(motionBase);
    if(!a||index<0)throw new Error('Native scene-motion track is absent');
    const f=clamp(Number(frame)||0,0,a.frameCount-1),lo=Math.floor(f),hi=Math.min(lo+1,a.frameCount-1),t=f-lo;
    const offset=20+a.boneCount*16+index*33+5,o=a.frameOffset(lo)+offset,p=a.frameOffset(hi)+offset,v=a.view;
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
      // d_base carries scene displacement independently of the pelvis/root
      // bone. The host already moves the actor and its collision body. Keep
      // the whole skin/attachment tree in place, including during jump/fall;
      // retain the authored bone-local height and all rotations unchanged.
      if(!rootMotion&&dummyNodes[i]===motionBase)motionBase.position.copy(motionBaseRest);
      readQ(v,x+12,qa);readQ(v,y+12,qb);dummyNodes[i].quaternion.copy(qa).slerp(qb,t);
    }
    group.updateMatrixWorld(true);skeleton.update();api.source=Number(source);api.frame=f;
    syncDisplayRig();for(const listener of poseListeners)listener({source:api.source,frame:f});syncVisualAttachments();return api;
  }
  const transformNodes=[...boneNodes,...dummyNodes],blendMatrix=new THREE.Matrix4(),nativeInverse=new THREE.Matrix4();
  let blendCache=null,poseSnapshotSerial=0;
  function snapshotTransforms(){
    group.updateMatrixWorld(true);
    nativeInverse.copy(nativeSpace.matrixWorld).invert();
    return transformNodes.map(node=>{
      const nativePosition=new THREE.Vector3(),nativeRotation=new THREE.Quaternion(),nativeScale=new THREE.Vector3();
      blendMatrix.multiplyMatrices(nativeInverse,node.matrixWorld).decompose(nativePosition,nativeRotation,nativeScale);
      return {position:node.position.clone(),quaternion:node.quaternion.clone(),parent:node.parent.name,nativePosition,nativeRotation};
    });
  }
  function capturePose(){return{source:api.source,frame:api.frame,snapshot:{id:++poseSnapshotSerial,transforms:snapshotTransforms()}};}
  function snapshotFrame(descriptor,frameOptions){
    if(descriptor.snapshot)return descriptor.snapshot.transforms;
    setPoseFrame(descriptor.source,descriptor.frame,frameOptions);
    return snapshotTransforms();
  }
  function setPoseBlend(from,to,weight,frameOptions={}){
    const alpha=clamp(Number(weight)||0,0,1),key=`${from.snapshot?.id??''}:${from.source}:${from.frame}:${to.source}:${to.frame}:${frameOptions.rootMotion??!inPlace}`;
    if(blendCache?.key!==key){
      const start=snapshotFrame(from,frameOptions),end=snapshotFrame(to,frameOptions);
      blendCache={key,start,end};
    }else setPoseFrame(to.source,to.frame,frameOptions);
    const {start,end}=blendCache,changed=[];
    for(let i=0;i<transformNodes.length;i++){
      const node=transformNodes[i],a=start[i],b=end[i];
      if(a.parent!==b.parent){changed.push(i);continue;}
      node.position.copy(a.position).lerp(b.position,alpha);node.quaternion.copy(a.quaternion).slerp(b.quaternion,alpha);
    }
    group.updateMatrixWorld(true);
    // Native animation may reparent a weapon dummy. Interpolate it in native
    // model space, then convert into its target parent, so it cannot teleport.
    for(const i of changed){
      const node=transformNodes[i],a=start[i],b=end[i];
      positionA.copy(a.nativePosition).lerp(b.nativePosition,alpha);qa.copy(a.nativeRotation).slerp(b.nativeRotation,alpha);
      blendMatrix.compose(positionA,qa,new THREE.Vector3(1,1,1)).premultiply(nativeSpace.matrixWorld);
      nativeInverse.copy(node.parent.matrixWorld).invert();blendMatrix.premultiply(nativeInverse).decompose(node.position,node.quaternion,node.scale);
      node.updateMatrixWorld(true);
    }
    group.updateMatrixWorld(true);skeleton.update();api.source=Number(to.source);api.frame=to.frame;
    syncDisplayRig();for(const listener of poseListeners)listener({source:api.source,frame:api.frame,blend:{from,to,weight:alpha}});syncVisualAttachments();return api;
  }
  function playPose(poseId,{loop,rate=1,restart=false}={}){
    const pose=data.poses[typeof poseId==='string'&&!/^\d+$/.test(poseId)?NATIVE_POSES[poseId]:Number(poseId)];if(!pose)return false;
    if(animationState.pose?.id===pose.id&&!restart&&!animationState.external)return true;
    Object.assign(animationState,{pose,time:0,rate,loop:loop??pose.loopStart!==null,finished:false,external:false});setPoseFrame(pose.source,pose.start,{managed:true});return true;
  }
  function update(dt,state){
    if(state&&typeof state==='object'&&state.source!==undefined&&state.frame!==undefined){setPoseFrame(state.source,state.frame,state);animationState.external=true;updateSecondaryMotion(dt);return;}
    if(state!==undefined){const next=typeof state==='string'?state:state.pose??state.state;if(next!==undefined){const poseId=typeof next==='number'?next:(NATIVE_POSES[next]??(/^\d+$/.test(String(next))?Number(next):NATIVE_POSES.idle));if(String(next)!==stateName||animationState.pose?.id!==poseId||animationState.external){stateName=String(next);playPose(poseId,{loop:typeof state==='object'?state.loop:undefined,rate:typeof state==='object'?state.rate??1:1,restart:animationState.external});}}}
    if(!animationState.pose||animationState.external){updateSecondaryMotion(dt);return;}
    const pose=animationState.pose,a=data.animations[pose.source];animationState.time+=Math.max(0,dt)*animationState.rate;
    let frame=pose.start+animationState.time*a.fps;
    if(frame>pose.end){if(animationState.loop){const begin=pose.loopStart??pose.start,end=pose.loopEnd??pose.end;frame=begin+(frame-begin)%Math.max(1,end-begin+1);}else{frame=pose.end;animationState.finished=true;}}
    setPoseFrame(pose.source,frame,{managed:true});
    updateSecondaryMotion(dt);
  }
  function updateSecondaryMotion(dt,settings={}){syncDisplayRig();visuals.get(appearance)?.secondaryMotion?.update(dt,settings);syncVisualAttachments();}
  function resetSecondaryMotion(){visuals.get(appearance)?.secondaryMotion?.reset();}
  function setSecondaryMotionEnabled(enabled){secondaryMotionEnabled=!!enabled;const visual=visuals.get(appearance);visual?.secondaryMotion?.setEnabled(secondaryMotionEnabled&&!visual.proportionalRig?.restPose);}
  function applyVisual(key){
    const next=visuals.get(key).mesh;if(next!==mesh){mesh.removeFromParent();mesh=next;nativeSpace.add(mesh);group.updateMatrixWorld(true);skeleton.update();}
    appearance=key;group.userData.appearance=key;group.userData.sourceFormat=key!=='original'?'Blender JSON+BNC+AMB+POS':'SKC+BNC+AMB+POS';group.name=key==='original'?`原版${characterName}`:(visuals.get(key).manifest.label??NATIVE_APPEARANCES[key].label);
    syncDisplayRig();syncVisualAttachments();
    const visual=visuals.get(key);visual.secondaryMotion?.setEnabled(secondaryMotionEnabled&&!visual.proportionalRig?.restPose);
  }
  async function setAppearance(requested='original',{allowIncomplete=false}={}){
    if(!Object.hasOwn(NATIVE_APPEARANCES,requested))throw new Error('Unknown character appearance');
    const request=++appearanceRequest;
    if(disposed)return {...appearanceState,reason:'角色已释放'};
    if(requested==='original'){
      applyVisual('original');appearanceState={requested,appearance,available:true,complete:true,previewOnly:false,reason:null,label:`原版${characterName}`};return {...appearanceState};
    }
    let requestedCompleteness=null;
    try{
      // Completeness gates game adoption even if a previous explicit workshop
      // preview already cached this mesh. A texture override does not supply a
      // missing source face mesh, and preview permission is never persistent.
      const asset=visuals.has(requested)?null:await loadEnhancedCharacterData(data.id,requested);
      if(disposed||request!==appearanceRequest)return {...appearanceState};
      const manifest=visuals.get(requested)?.manifest||asset.manifest;
      requestedCompleteness=appearanceCompleteness(manifest);
      if(!requestedCompleteness.complete&&allowIncomplete!==true)throw new Error(requestedCompleteness.reason);
      if(!pendingVisuals.has(requested)&&!visuals.has(requested))pendingVisuals.set(requested,(async()=>{
        validateEnhancedSkin(asset.skin,boneNodes.length);
        if(disposed)return null;
        const visual=createSkinVisual(asset.skin,asset.path,{enhanced:true,loadTextures});visual.mesh.name=`p${data.id}.blender-${requested}`;visual.manifest=asset.manifest;
        // Reuse the original binding transform as well as the live skeleton.
        // Binding from the actor's current animated pose would deform the mesh.
        try{
          if(asset.skin.bodyRig)visual.proportionalRig=createProportionalRig({rig:asset.skin.bodyRig,nativeBones:boneNodes,nativeSpace});
          const displayBones=visual.proportionalRig?.bones||boneNodes,displaySkeleton=visual.proportionalRig?.skeleton||skeleton;
          if(asset.skin.secondaryMotion)visual.secondaryMotion=createHairSprings({rig:asset.skin.secondaryMotion,nativeBones:displayBones,nativeSkeleton:displaySkeleton,root:group});
          visual.mesh.bind(visual.secondaryMotion?.skeleton||displaySkeleton,bindMatrix);visual.mesh.normalizeSkinWeights();
        }catch(error){visual.dispose();throw error;}
        try{await visual.ready;}catch(error){visual.dispose();throw error;}
        if(disposed){visual.dispose();return null;}visuals.set(requested,visual);return visual;
      })().finally(()=>pendingVisuals.delete(requested)));
      await pendingVisuals.get(requested);
      if(disposed||request!==appearanceRequest)return {...appearanceState};
      applyVisual(requested);appearanceState={requested,appearance,available:true,complete:requestedCompleteness.complete,previewOnly:!requestedCompleteness.complete,completeness:requestedCompleteness.completeness,reason:requestedCompleteness.reason,label:visuals.get(requested).manifest.label??NATIVE_APPEARANCES[requested].label,stats:visuals.get(requested).manifest.stats??null};
    }catch(error){
      if(disposed||request!==appearanceRequest)return {...appearanceState};
      const current=visuals.get(appearance);
      appearanceState={requested,appearance,available:false,complete:requestedCompleteness?.complete??false,previewOnly:false,completeness:requestedCompleteness?.completeness??null,reason:error.message,label:appearance==='original'?`原版${characterName}`:(current?.manifest.label??NATIVE_APPEARANCES[appearance].label)};
    }
    return {...appearanceState};
  }
  const api={nativeCharacterId:data.id,group,get mesh(){return mesh;},skeleton,bones:boneNodes,dummies:dummyNodes,nativeSpace,poses:data.poses,combatPoses:data.combatPoses,animations:data.animations,source:1,frame:1,onPoseUpdate(listener){poseListeners.add(listener);return()=>poseListeners.delete(listener);},update,updateSecondaryMotion,resetSecondaryMotion,setSecondaryMotionEnabled,get secondaryMotionStatus(){return visuals.get(appearance)?.secondaryMotion?.status||{available:false,enabled:false};},getSecondaryMotionSnapshot(){return visuals.get(appearance)?.secondaryMotion?.snapshot()||[];},playPose,setPoseFrame,setPoseBlend,capturePose,sampleRoot,sampleSceneMotion,setAppearance,get appearance(){return appearance;},get appearanceStatus(){return {...appearanceState};},getAttachment:name=>byName.get(name)||resolve(name),getVisualAttachmentMatrix,registerVisualAttachment,setSourceRestPose(value){const visual=visuals.get(appearance),rig=visual?.proportionalRig;if(!rig)return false;rig.setRestPose(value);visual.secondaryMotion?.setEnabled(!value&&secondaryMotionEnabled);syncVisualAttachments();return true;},get sourceRestAvailable(){return !!visuals.get(appearance)?.proportionalRig;},get sourceRestPose(){return visuals.get(appearance)?.proportionalRig?.restPose||false;},get finished(){return animationState.finished;},get currentPose(){return animationState.pose?.id??null;},getAttachmentPosition(name,target=new THREE.Vector3()){return resolve(name)?.getWorldPosition(target)||null;},dispose(){if(disposed)return;disposed=true;++appearanceRequest;blendCache=null;poseListeners.clear();for(const visual of visuals.values())visual.dispose();visuals.clear();visualAttachments.clear();visualSockets.clear();skeleton.dispose();group.removeFromParent();}};
  api.ready=originalVisual.ready.then(async()=>{if(options.appearance&&options.appearance!=='original'&&appearanceRequest===0)await setAppearance(options.appearance);});
  playPose(0,{loop:true});return api;
}

export async function loadNativeCharacter(id=0,options={}){const data=await cachedData(id),character=createNativeCharacter(data,options);try{await character.ready;return character;}catch(error){character.dispose();throw error;}}
export const loadNativeCharacterData=cachedData;

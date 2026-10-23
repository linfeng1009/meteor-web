import * as THREE from './vendor/three.module.js';

// Native Meteor Blade GMDL V1.00 / GMC V1.0 model reader.
// Format notes and asset attribution: ./assets/SOURCES.md.
// Native models contain world-space vertices, with Z pointing up.
export function readGmb(buffer) {
  const bytes = new Uint8Array(buffer);
  const view = new DataView(buffer);
  const decoder = new TextDecoder();
  let offset = 0;
  const need = n => { if (offset + n > bytes.length) throw new Error('Truncated GMB model'); };
  const int = () => { need(4); const v=view.getInt32(offset,true); offset+=4; return v; };
  const float = () => { need(4); const v=view.getFloat32(offset,true); offset+=4; return v; };
  const byte = () => { need(1); return bytes[offset++]; };
  const string = () => { const n=int(); if(n<0||n>65536)throw new Error('Invalid GMB string');need(n);const s=decoder.decode(bytes.subarray(offset,offset+n)).replace(/\0+$/,'');offset+=n;return s; };
  need(10);
  if (decoder.decode(bytes.subarray(0,10)) !== 'GMDL V1.00') throw new Error('Unsupported GMB model');
  offset=10;
  const textureCount=int();
  if(textureCount<0||textureCount>4096)throw new Error('Invalid GMB texture count');
  const textures=Array.from({length:textureCount},string);
  const shaderCount=int();
  if(shaderCount<0||shaderCount>4096)throw new Error('Invalid GMB shader count');
  const shaders=Array.from({length:shaderCount},()=>({texture:int(),mode:string(),twoSide:byte()!==0,blend:string(),opacity:float()}));
  const objectCount=int(),dummyCount=int(),vertexCount=int(),faceCount=int();
  if(objectCount<0||objectCount>10000||vertexCount<0||vertexCount>5000000||faceCount<0||faceCount>5000000)throw new Error('Invalid GMB geometry count');
  const objects=[];
  let verticesRead=0,facesRead=0;
  for(let k=0;k<objectCount;k++){
    const name=string(),nv=int(),nf=int();
    if(nv<0||nf<0||verticesRead+nv>vertexCount||facesRead+nf>faceCount)throw new Error('Invalid GMB object size');
    const vertices=Array.from({length:nv},()=>({position:[float(),float(),float()],normal:[float(),float(),float()],color:[byte()/255,byte()/255,byte()/255,byte()/255],uv:[float(),float()]}));
    const faces=Array.from({length:nf},()=>({shader:int(),indices:[int(),int(),int()],normal:[float(),float(),float()]}));
    if(faces.some(f=>f.shader < -1 || f.shader>=shaderCount || f.indices.some(i=>i<0||i>=nv)))throw new Error('Invalid GMB face index');
    objects.push({name,vertices,faces});verticesRead+=nv;facesRead+=nf;
  }
  if(verticesRead!==vertexCount||facesRead!==faceCount||offset!==bytes.length)throw new Error('GMB geometry totals do not match');
  return {format:'GMB',textures,shaders,objects,vertexCount,faceCount,dummyCount};
}

export function readGmc(text) {
  const clean=text.replace(/#[^\r\n]*/g,'');
  const textures=(clean.match(/Textures\s+\d+\s*\{([^}]+)\}/i)?.[1]||'').trim().split(/\s+/).filter(Boolean);
  const shaders=[];
  for(const m of clean.matchAll(/shader\s+(\d+)\s*\{([^}]+)\}/gi)){
    const s=m[2];shaders[Number(m[1])]={texture:Number(s.match(/Texture\s+(-?\d+)/i)?.[1]??-1),mode:s.match(/Texture\s+-?\d+\s+(\w+)/i)?.[1]||'NORMAL',twoSide:/TwoSide\s+1/i.test(s),blend:s.match(/Blend\s+([^\r\n}]+)/i)?.[1].trim()||'DISABLE 1 0',opacity:Number(s.match(/Opaque\s+([\d.]+)/i)?.[1]??1)};
  }
  const objects=[];
  for(const m of clean.matchAll(/Object\s+(\S+)\s*\{([^}]+)\}/gi)){
    const vertices=[],faces=[];
    for(const line of m[2].split(/\r?\n/)){
      const t=line.trim().split(/\s+/);
      if(t[0]==='v'){
        const n=t.indexOf('n'),c=t.indexOf('c'),uv=t.indexOf('t');
        vertices.push({position:t.slice(1,4).map(Number),normal:n>=0?t.slice(n+1,n+4).map(Number):[0,0,1],color:c>=0?t.slice(c+1,c+5).map(x=>Number(x)/255):[1,1,1,1],uv:uv>=0?t.slice(uv+1,uv+3).map(Number):[0,0]});
      }else if(t[0]==='f')faces.push({shader:Number(t[1]),indices:t.slice(2,5).map(Number),normal:t.slice(5,8).map(Number)});
    }
    objects.push({name:m[1],vertices,faces});
  }
  return {format:'GMC',textures,shaders,objects,vertexCount:objects.reduce((n,o)=>n+o.vertices.length,0),faceCount:objects.reduce((n,o)=>n+o.faces.length,0)};
}

function makeModel(data, options={}) {
  const {scale=0.015,groundZ=-360.545,texturePath='',textureMap={},textureAlphaMap={},unlit=false,skipEffects=true,vertexColors=true,desText=''}=options;
  const descriptions=new Map();
  for(const m of desText.matchAll(/Object\s+(\S+)\s*\{([\s\S]*?)\n\}/g)) descriptions.set(m[1],m[2]);
  const group=new THREE.Group();
  group.name=options.name||(data.format==='GMB'?'四方阵 · 流星蝴蝶剑原版地图':'流星蝴蝶剑社区武器');
  group.userData={source:options.source||(data.format==='GMB'?'https://www.lxres.com/DiTuXiaZai/YuanBanMeiHua/4798.html':'https://www.lxres.com/RenWuWuQi/ZiZhiWuQi/635.html'),originalFormat:data.format,vertexCount:data.vertexCount,faceCount:data.faceCount,scale,groundZ};
  const used=new Set(data.objects.flatMap(o=>o.faces.map(f=>f.shader)));
  const textureLoader=new THREE.TextureLoader(),pending=[],loaded=new Map();
  const materials=data.shaders.map((s,i)=>{
    const transparent=s.opacity<0.999||/^ENABLE/i.test(s.blend);
    const Material=unlit?THREE.MeshBasicMaterial:THREE.MeshStandardMaterial;
    const material=new Material({color:0xffffff,...(unlit?{toneMapped:false}:{roughness:0.91,metalness:0.02}),vertexColors,side:s.twoSide?THREE.DoubleSide:THREE.FrontSide,transparent,opacity:s.opacity,depthWrite:!transparent,alphaTest:s.mode==='ALPHACHANNEL'?0.1:0});
    const name=data.textures[s.texture]?.toLowerCase().replace(/\\/g,'/').split('/').pop();
    if(name&&(texturePath||textureMap[name])&&used.has(i)){
      if(!loaded.has(name))loaded.set(name,new Promise(resolve=>textureLoader.load(textureMap[name]||texturePath+name,t=>{
        t.colorSpace=THREE.SRGBColorSpace;t.wrapS=t.wrapT=THREE.RepeatWrapping;t.anisotropy=4;resolve(t);
      },undefined,()=>resolve(null))));
      pending.push(loaded.get(name).then(t=>{if(t){material.map=t;material.needsUpdate=true;}}));
      if(textureAlphaMap[name]){
        const maskKey='alpha:'+name;
        if(!loaded.has(maskKey))loaded.set(maskKey,new Promise(resolve=>textureLoader.load(textureAlphaMap[name],t=>{t.wrapS=t.wrapT=THREE.RepeatWrapping;resolve(t);},undefined,()=>resolve(null))));
        pending.push(loaded.get(maskKey).then(t=>{if(t){material.alphaMap=t;material.alphaTest=.1;material.transparent=true;material.needsUpdate=true;}}));
      }
    }
    return material;
  });
  const untextured=new THREE.MeshStandardMaterial({color:0x647178,roughness:1,side:THREE.DoubleSide,vertexColors});
  const allMaterials=[...materials,untextured];
  for(const object of data.objects){
    const description=descriptions.get(object.name)||'';
    if(!object.faces.length)continue;
    const hidden=object.faces.every(f=>f.shader<0)||/visible\s*=\s*0/i.test(description);
    if(skipEffects&&(/^(wu\d*|Cylinder01)$/i.test(object.name)||object.faces.every(f=>f.shader>=0&&materials[f.shader].transparent)))continue;
    const positions=[],normals=[],colors=[],uvs=[],indices=[];
    for(const v of object.vertices){
      positions.push(v.position[0]*scale,(v.position[2]-groundZ)*scale,-v.position[1]*scale);
      normals.push(v.normal[0],v.normal[2],-v.normal[1]);
      colors.push(...v.color.slice(0,3));uvs.push(v.uv[0],v.uv[1]);
    }
    const geometry=new THREE.BufferGeometry();
    geometry.setAttribute('position',new THREE.Float32BufferAttribute(positions,3));
    geometry.setAttribute('normal',new THREE.Float32BufferAttribute(normals,3));
    geometry.setAttribute('color',new THREE.Float32BufferAttribute(colors,3));
    geometry.setAttribute('uv',new THREE.Float32BufferAttribute(uvs,2));
    const byShader=new Map();
    for(const face of object.faces){const material=face.shader<0?materials.length:face.shader;if(!byShader.has(material))byShader.set(material,[]);byShader.get(material).push(...face.indices);}
    for(const [material,triangles] of byShader){geometry.addGroup(indices.length,triangles.length,material);indices.push(...triangles);}
    geometry.setIndex(indices);geometry.computeBoundingBox();geometry.computeBoundingSphere();
    const mesh=new THREE.Mesh(geometry,allMaterials);mesh.name=object.name;mesh.receiveShadow=true;mesh.castShadow=!/^Plane/i.test(object.name);mesh.userData.originalMap=true;
    mesh.visible=!hidden;mesh.userData.hidden=hidden;
    const textureNames=object.faces.map(f=>data.textures[data.shaders[f.shader]?.texture]||'');
    mesh.userData.collidable=!/blockplayer\s*=\s*no/i.test(description)&&!textureNames.every(t=>/sky|wu/i.test(t));
    group.add(mesh);
  }
  group.userData.texturesReady=Promise.all(pending);
  return group;
}

export function parseGmb(buffer,options={}) {return makeModel(readGmb(buffer),options);}
export function parseGmc(text,options={}) {return makeModel(readGmc(text),options);}
export async function loadGmb(url,options={}) {
  const response=await fetch(url);
  if(!response.ok)throw new Error(`Map load failed: ${response.status}`);
  const desUrl=options.desUrl??url.replace(/\.gmb(?=\?|$)/i,'.des');
  let desText=options.desText||'';
  if(!desText&&desUrl!==url){try{const des=await fetch(desUrl);if(des.ok)desText=await des.text();}catch{}}
  const group=parseGmb(await response.arrayBuffer(),{...options,desText});
  await group.userData.texturesReady;
  return group;
}
export async function loadGmc(url,options={}) {
  const response=await fetch(url);
  if(!response.ok)throw new Error(`Map load failed: ${response.status}`);
  const group=parseGmc(await response.text(),options);
  await group.userData.texturesReady;
  return group;
}

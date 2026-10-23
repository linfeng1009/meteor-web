import{readFile,writeFile}from'node:fs/promises';
const project = new URL('../', import.meta.url);
const THREE=await import(new URL('dist/vendor/three.module.js',project));
const {loadOriginalSceneModels}=await import(new URL('dist/native-scene-models.js',project));
const sourceFetch=globalThis.fetch;globalThis.fetch=async url=>{try{return new Response(await readFile(new URL(url)),{status:200});}catch{return new Response('',{status:404});}};
const originalLoad=THREE.TextureLoader.prototype.load;THREE.TextureLoader.prototype.load=function(url,done){const texture=new THREE.Texture();done(texture);return texture;};
const manifest=JSON.parse(await readFile(new URL('dist/assets/original/manifest.json',project),'utf8'));
const material=new THREE.MeshBasicMaterial({side:THREE.DoubleSide}), results=[];
for(const id of['sn01','sn02','sn09','sn10','sn18']){
 const map=manifest.maps.find(m=>m.id===id),metadata=JSON.parse(await readFile(new URL('dist/assets/original/'+map.metadata,project),'utf8')),des=metadata.files.find(f=>f.parsed?.format==='DES').parsed;
 const props=await loadOriginalSceneModels(des.objects,{scale:.08,collisionMaterial:material});
 const entry={id,instances:props.instances.size,collidableInstances:[...props.instances.values()].filter(i=>i.colliders.length).length,warnings:props.warnings,animated:[...props.instances.values()].filter(i=>i.asset.animation).length};
 if(['sn02','sn10'].includes(id)){const name=id==='sn02'?'d_wpbbox12':'d_wp06',instance=props.instances.get(name);entry.alias={name,parts:instance?.asset.entry.pairedModels,meshes:0};instance?.model.traverse(o=>{if(o.isMesh)entry.alias.meshes++;});if(!instance||entry.alias.meshes<2)throw new Error('Paired source weapon alias not resolved '+id);}
 if(id==='sn09'){const instance=props.instances.get('d_sn09f01');if(!instance)throw new Error('Original sn09 floor missing');entry.floor={name:instance.name,pose1:instance.playPose(1),start:new THREE.Box3().setFromObject(instance.root).getCenter(new THREE.Vector3()).toArray()};props.update(4);entry.floor.end=new THREE.Box3().setFromObject(instance.root).getCenter(new THREE.Vector3()).toArray();if(entry.floor.end[1]>=entry.floor.start[1])throw new Error('Original falling-floor FMC did not move downward');}
 results.push(entry);
}
THREE.TextureLoader.prototype.load=originalLoad;globalThis.fetch=sourceFetch;
const evidence={observedAt:new Date().toISOString(),method:'Node actual original geometry/FMC loading with filesystem fetch and no-op texture decoder; no browser rendering asserted',results};
await writeFile(new URL('work/meteor-original/evidence/E-scene-runtime-verification.json',project),JSON.stringify(evidence,null,2)+'\n');console.log(JSON.stringify(evidence,null,2));

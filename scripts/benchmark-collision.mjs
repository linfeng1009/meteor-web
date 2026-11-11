// CPU raycast microbenchmark on shipped maps; this is not a GPU/FPS benchmark.
import {readFile} from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import {parseGmb} from '../dist/gmc-loader.js';
import {StaticColliderIndex} from '../dist/collision-index.js';
const root=new URL('../dist/assets/original/',import.meta.url);
const manifest=JSON.parse(await readFile(new URL('manifest.json',root),'utf8'));
const reports=[];
for(const id of ['sn06','sn14']){
  const entry=manifest.maps.find(map=>map.id===id),bytes=await readFile(new URL(entry.model,root));
  const desText=await readFile(new URL(entry.description,root),'utf8');
  const model=parseGmb(bytes.buffer.slice(bytes.byteOffset,bytes.byteOffset+bytes.byteLength),{scale:.08,groundZ:0,desText});
  model.updateMatrixWorld(true);
  const colliders=model.children.filter(mesh=>mesh.userData.collidable),index=new StaticColliderIndex(colliders);
  const bounds=new THREE.Box3().setFromObject(model),center=bounds.getCenter(new THREE.Vector3()),size=bounds.getSize(new THREE.Vector3());
  const rays=Array.from({length:600},(_,i)=>{
    const x=center.x+Math.sin(i*2.399)*size.x*.4,z=center.z+Math.cos(i*1.723)*size.z*.4;
    const origin=new THREE.Vector3(x,bounds.max.y+2,z),direction=new THREE.Vector3(0,-1,0);
    if(i%2){origin.y=center.y;direction.set(Math.sin(i),.1,Math.cos(i)).normalize();}
    const far=i%2?9:Math.max(1,size.y+10);
    return {origin,direction,far,radius:i%2?9:1};
  });
  const ray=new THREE.Raycaster();let totalCandidates=0;
  for(const r of rays){ray.set(r.origin,r.direction);ray.far=r.far;const near=index.near(r.origin.x,r.origin.z,r.radius);totalCandidates+=near.length;
    const all=ray.intersectObjects(colliders,false),filtered=ray.intersectObjects(near,false);
    if(all.length!==filtered.length||all.some((h,i)=>Math.abs(h.distance-filtered[i].distance)>1e-7))throw Error(`${id}: collision mismatch`);
  }
  const run=filtered=>{const start=performance.now();for(let round=0;round<3;round++)for(const r of rays){ray.set(r.origin,r.direction);ray.far=r.far;ray.intersectObjects(filtered?index.near(r.origin.x,r.origin.z,r.radius):colliders,false);}return performance.now()-start;};
  run(false);run(true);const full=[],indexed=[];
  for(let i=0;i<7;i++){if(i%2){indexed.push(run(true));full.push(run(false));}else{full.push(run(false));indexed.push(run(true));}}
  const median=values=>values.sort((a,b)=>a-b)[3];
  reports.push({map:id,rays:rays.length,colliders:colliders.length,averageCandidates:totalCandidates/rays.length,baselineMs:median(full),indexedMs:median(indexed),equivalent:true});
}
console.log(JSON.stringify(reports,null,2));

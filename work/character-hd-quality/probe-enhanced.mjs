import { readFile, writeFile } from 'node:fs/promises';
import { createHash } from 'node:crypto';
import * as THREE from '../../dist/vendor/three.module.js';
import { createNativeCharacter, parseNativeSkin, parseNativeBones, parseNativeAnimation, parseNativePoses } from '../../dist/native-character.js';
const root = new URL('../../', import.meta.url);
const text = p => readFile(new URL(p, root),'utf8');
const buffer = async p => { const b=await readFile(new URL(p,root)); return b.buffer.slice(b.byteOffset,b.byteOffset+b.byteLength); };
const [skin,bones,common,personal,poses,hd] = await Promise.all([text('dist/assets/original/characters/p0/p0.skc'),text('dist/assets/original/characters/p0/p0.bnc'),buffer('dist/assets/original/characters/common/character.amb'),buffer('dist/assets/original/characters/p0/p0.amb'),text('dist/assets/original/characters/p0/p0.pos'),text('dist/assets/enhanced/p0/mesh.json')]);
const data={id:0,skin:parseNativeSkin(skin),skeleton:parseNativeBones(bones),animations:[parseNativeAnimation(common),parseNativeAnimation(personal)],poses:parseNativePoses(poses)};
const enhanced=JSON.parse(hd), groups=new Map();
for(let i=0;i<enhanced.vertexCount;i++) { const k=enhanced.positions.slice(i*3,i*3+3).join(','); if(!groups.has(k))groups.set(k,[]); groups.get(k).push(i); }
const repeated=[...groups.values()].filter(g=>g.length>1);
const weightSignature=i=>enhanced.skinIndices.slice(i*4,i*4+4).map((b,j)=>[b,enhanced.skinWeights[i*4+j]]).filter(([,w])=>w>0).sort((a,b)=>a[0]-b[0]).map(([b,w])=>`${b}:${w.toFixed(5)}`).join(',');
const mismatch=repeated.filter(g=>new Set(g.map(weightSignature)).size>1);
const normalLengths=[];for(let i=0;i<enhanced.vertexCount;i++)normalLengths.push(Math.hypot(...enhanced.normals.slice(i*3,i*3+3)));
let degenerate=0,reversedNormal=0;const p=new THREE.Vector3(),q=new THREE.Vector3(),r=new THREE.Vector3(),normal=new THREE.Vector3(),a=new THREE.Vector3(),b=new THREE.Vector3();
for(const f of enhanced.faces) {p.fromArray(enhanced.positions,f.indices[0]*3);q.fromArray(enhanced.positions,f.indices[1]*3);r.fromArray(enhanced.positions,f.indices[2]*3);a.subVectors(q,p);b.subVectors(r,p);a.cross(b);if(a.length()<1e-10){degenerate++;continue;}normal.set(0,0,0);for(const i of f.indices)normal.add(p.fromArray(enhanced.normals,i*3));if(a.dot(normal)<-1e-8)reversedNormal++;}
const beforeFetch=globalThis.fetch;globalThis.fetch=async url=>{try{return new Response(await readFile(new URL(url)))}catch{return new Response('',{status:404})}};
const original=createNativeCharacter(data,{loadTextures:false}),character=createNativeCharacter(data,{loadTextures:false});await character.setAppearance('hd');
const frames=[];let maxAnimatedSeamGap=0;
for(const id of [0,144,151,152,16,262,263,264,90,117]) {const pose=data.poses[id];for(const frame of new Set([pose.start,Math.floor((pose.start+pose.end)/2),pose.end])) {original.setPoseFrame(pose.source,frame);character.setPoseFrame(pose.source,frame);original.mesh.computeBoundingBox();character.mesh.computeBoundingBox();const ob=original.mesh.boundingBox,eb=character.mesh.boundingBox;let gap=0;for(const g of mismatch){const first=character.mesh.getVertexPosition(g[0],new THREE.Vector3());for(const i of g.slice(1))gap=Math.max(gap,first.distanceTo(character.mesh.getVertexPosition(i,new THREE.Vector3())));}maxAnimatedSeamGap=Math.max(maxAnimatedSeamGap,gap);frames.push({pose:id,source:pose.source,frame,originalBounds:ob.toArray?ob.toArray():[ob.min.toArray(),ob.max.toArray()],enhancedBounds:[eb.min.toArray(),eb.max.toArray()],coincidentPositionMaxSkinGapNative:gap});}}
original.dispose();character.dispose();globalThis.fetch=beforeFetch;
const expected=JSON.parse(await text('work/character-hd-quality/original-hashes.json'));const changedOriginal=[];for(const[file,hash]of Object.entries(expected)){if(createHash('sha256').update(await readFile(new URL(file,root))).digest('hex')!==hash)changedOriginal.push(file);}
const out={date:'2026-10-26',meshSha256:createHash('sha256').update(hd).digest('hex'),vertexCount:enhanced.vertexCount,triangleCount:enhanced.triangleCount,exactPositionGroups:groups.size,coincidentGroups:repeated.length,coincidentWeightMismatchGroups:mismatch.length,maxAnimatedSeamGapNative:maxAnimatedSeamGap,maxAnimatedSeamGapWorld:maxAnimatedSeamGap*.08,normalLengthRange:[Math.min(...normalLengths),Math.max(...normalLengths)],degenerateRestTriangles:degenerate,reversedRestFaceVsVertexNormalCount:reversedNormal,changedOriginal,frames};
await writeFile(new URL('enhanced-probe.json',import.meta.url),JSON.stringify(out,null,2));console.log(JSON.stringify({...out,frames:`${frames.length} actual native pose frames inspected`},null,2));

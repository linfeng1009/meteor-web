import fs from 'node:fs/promises';
import * as THREE from '../../dist/vendor/three.module.js';
import {loadNativeCharacter} from '../../dist/native-character.js';
import {loadNativeCombat} from '../../dist/native-combat.js';
import {loadGmb} from '../../dist/gmc-loader.js';
const dist=new URL('../../dist/',import.meta.url);globalThis.fetch=async path=>{try{return new Response(await fs.readFile(new URL(path,dist)));}catch{return new Response('',{status:404});}};
THREE.TextureLoader.prototype.load=function(u,done){const t=new THREE.Texture();done?.(t);return t;};
const c=await loadNativeCharacter(0,{inPlace:true}),data=await loadNativeCombat(),models=[];
for(const id of ['w9_0r','w9_0l']){const m=await loadGmb(new URL(`assets/original/weapon-models/models/${id}/${id}.gmb`,dist).href,{scale:1,groundZ:0,unlit:true});m.name=id;m.rotation.x=Math.PI/2;c.getAttachment(id.endsWith('l')?'d_wpnL':'d_wpnR').add(m);models.push(m);}
const hands=c.bones.filter(b=>/Hand$/.test(b.name));
console.log('hands',hands.map(b=>b.name));
for(const id of [6,401,402,403]){const pose=data.poses.get(id);c.setPoseFrame(pose.source,pose.entryFrame);c.group.updateMatrixWorld(true);console.log(JSON.stringify({pose:id,source:pose.source,frame:pose.entryFrame,hands:hands.map(h=>({name:h.name,p:h.getWorldPosition(new THREE.Vector3()).toArray()})),attachments:c.dummies.map(d=>d.name).map(n=>{const d=c.getAttachment(n);return {n,parent:d.parent.name,local:d.position.toArray(),q:d.quaternion.toArray(),p:d.getWorldPosition(new THREE.Vector3()).toArray()};}),weapons:models.map(m=>{const mesh=m.children.find(ch=>ch.visible);let box=new THREE.Box3().setFromObject(mesh);return {name:m.name,box:{min:box.min.toArray(),max:box.max.toArray()},handDistances:hands.map(h=>box.distanceToPoint(h.getWorldPosition(new THREE.Vector3())))};})}));}

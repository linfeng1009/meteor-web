// Offline source-geometry audit. Direct native poses intentionally bypass
// pending production command gates. No status application, live AI or UI claim.
import { readFile, writeFile } from 'node:fs/promises';
import { createHash } from 'node:crypto';
import * as THREE from '../../../dist/vendor/three.module.js';
import { MeteorGame } from '../../../dist/engine.js';
import { loadNativeCombat, createNativeDamageResolver } from '../../../dist/native-combat.js';
import { NativeEffectContacts } from '../../../dist/native-effect-contacts.js';
const here=new URL('./',import.meta.url),dist=new URL('../../../dist/',import.meta.url),v=(x=0,y=0,z=0)=>new THREE.Vector3(x,y,z);
const oldFetch=globalThis.fetch,oldLoad=THREE.TextureLoader.prototype.load;
globalThis.fetch=async input=>{try{return new Response(await readFile(new URL(input instanceof Request?input.url:input,dist)),{status:200});}catch{return new Response('',{status:404});}};
THREE.TextureLoader.prototype.load=function(_url,done){const t=new THREE.Texture();done?.(t);return t;};
const data=await loadNativeCombat(),manifest=JSON.parse(await readFile(new URL('source-effects.json',here))),weapons=JSON.parse(await readFile(new URL('assets/original/weapon-models/manifest.json',dist)));
const floor=new THREE.Mesh(new THREE.PlaneGeometry(300,300),new THREE.MeshBasicMaterial({side:THREE.DoubleSide}));floor.rotation.x=-Math.PI/2;floor.updateMatrixWorld(true);
const game=Object.create(MeteorGame.prototype);
Object.assign(game,{combatData:data,weaponManifest:weapons,weaponItems:new Map(weapons.items.map(x=>[Number(x.itemId),x])),weaponModels:new Map(weapons.models.map(x=>[x.modelId.toLowerCase(),x])),weaponCache:new Map(),scene:new THREE.Scene(),camera:new THREE.PerspectiveCamera(),raycaster:new THREE.Raycaster(),effectDefinitions:new Map(),waveFiles:new Map(),effects:[],hostPhysics:{speed:8,gravity:34,jumpVelocity:12,radius:.4,step:.55},currentMap:{colliders:[floor],bounds:new THREE.Box3(v(-150,-1,-150),v(150,60,150)),metadata:{},spawns:[{position:v(0,.015,0)}]},weapon:'dart',actorSerial:0,enemies:[],keys:new Set(),directionBuffer:[],cameraAngle:0,running:true,paused:false,mode:'training',elapsed:0,matchElapsed:0,kills:0,deaths:0,totalDamage:0,contactHits:0,onEvent(){},onUpdate(){},_nameplate(){},_unlockAudio(){},_soundDefinition(){},_hud(){}});
game.damageResolver=createNativeDamageResolver(data);game._initializeProjectiles();game._initializeEffectContacts(manifest);
const actor=game.hero=await game._createFighter(0,'孟星魂',true);game.scene.add(actor.root);await game._equip(actor,'dart');actor.team=actor.teamMask=1;
const tick=dt=>{game.elapsed+=dt;game.matchElapsed+=dt;game._updateFighter(actor,dt);game.projectiles.update(dt);game.wheels.update(dt);};
let collected=[],windows=[];
const sampleBefore=game.effectContacts.sample.bind(game.effectContacts);
game.effectContacts.sample=(f,s,a,fps)=>{const out=sampleBefore(f,s,a,fps);collected.push(...out);if(out.length)windows.push({pose:s.poseId,frame:s.frame,previousFrame:s.previousFrame,time:out[0].time,lastTime:out.at(-1).time,root:f.root.position.toArray()});return out;};
const results=[];
for(const [pose,air,yaw]of[[201,false,0],[201,false,Math.PI/3],[551,true,0],[203,false,0],[204,false,0]]){
  game._placeFighter(actor,{position:v(0,.015,0)});actor.root.rotation.y=yaw;actor.rage=100;actor.hitstop=0;actor.heldPose=null;game.effectContacts.clear();
  if(air){game.action('jump');for(let i=0;i<50&&actor.root.position.y<2;i++)tick(1/120);}
  const origin=actor.root.position.clone();collected=[];windows=[];
  actor.combat.play(pose,{force:true,attack:true,context:{poseId:pose,rage:100}});
  const seen=new Set(),heights=[];
  for(let i=0;i<1000;i++){tick(1/120);seen.add(actor.combat.timeline.pose.id);heights.push(actor.root.position.y);if(!actor.combat.busy&&i>10)break;}
  const chosen=collected.filter(x=>x.effectId===`pos${pose}`),names=[...new Set(chosen.map(x=>x.nodeName))];
  const time=[Math.min(...chosen.map(x=>x.time)),Math.max(...chosen.map(x=>x.time))];
  const examples=[];
  for(const y of[.015,origin.y])for(const[x,z]of[[0,0],[0,1],[0,2],[0,3],[0,5],[0,8],[0,10],[0,-2],[2,0],[-2,0],[3,3],[-3,-3],[5,0],[-5,0]]){const target={root:{position:v(x,y,z)}},contact=game.effectContacts.contact(chosen,target);examples.push({position:target.root.position.toArray(),hit:!!contact,node:contact?.effectNode,time:contact?.effectTime});}
  const bounds=chosen.length?Object.fromEntries(['x','y','z'].map(k=>[k,[Math.min(...chosen.map(q=>q.center[k]-q.edges.reduce((sum,e)=>sum+Math.abs(e[k]),0))),Math.max(...chosen.map(q=>q.center[k]+q.edges.reduce((sum,e)=>sum+Math.abs(e[k]),0)))]])):null;
  const nodeSamples=chosen.filter((q,i)=>i===0||chosen[i-1].nodeName!==q.nodeName).slice(0,20).map(q=>({node:q.nodeName,time:q.time,center:q.center.toArray(),half:q.edges.map(e=>e.length())}));
  const phaseGeometry=[];
  for(const effectId of [...new Set(collected.map(x=>x.effectId))]) {
    const volumes=collected.filter(x=>x.effectId===effectId),hits=[];
    for(const[x,z]of[[0,0],[0,1],[0,2],[0,3],[0,5],[0,8],[0,10],[0,15],[0,20],[0,-2],[2,0],[-2,0],[3,3],[-3,-3],[5,0],[-5,0]]){
      const contact=game.effectContacts.contact(volumes,{root:{position:v(x,.015,z)}});if(contact)hits.push({position:[x,.015,z],node:contact.effectNode,time:contact.effectTime});
    }
    phaseGeometry.push({effectId,volumes:volumes.length,names:[...new Set(volumes.map(x=>x.nodeName))],groundTargetExamples:hits});
  }
  const poseWindows=windows.filter(w=>w.pose===pose);
  results.push({pose,air,yaw,origin:origin.toArray(),final:actor.root.position.toArray(),grounded:actor.grounded,posesObserved:[...seen],heightRange:[Math.min(...heights),Math.max(...heights)],volumes:chosen.length,attackNodeNames:names,distinctNamedNodes:names.length,windowTime:time,firstWindow:poseWindows[0],lastWindow:poseWindows.at(-1),sourceVolumesAabbEnvelope:bounds,nodeSamples,examples,phaseGeometry});
}
const result={scope:'Source EF201/551/203/204 parsed unchanged; real P0 SKC/BNC/AMB/POS through production character/engine movement and current effect contact host. Direct native play bypasses pending public commands. No damage/status/live-AI/browser acceptance; examples query static target boxes. Air551 begins with a normal jump. 204 is also inspected directly so its separate geometry is visible.',sha256:{sourceEffects:createHash('sha256').update(await readFile(new URL('source-effects.json',here))).digest('hex')},results};
await writeFile(new URL('probe-dart-effects.json',here),JSON.stringify(result,null,2)+'\n');
console.log(JSON.stringify(result,null,2));
game.effectContacts.dispose();game.projectiles.dispose();game.muskets.dispose();game.wheels.dispose();actor.character.dispose();floor.geometry.dispose();floor.material.dispose();
for(const m of await Promise.all(game.weaponCache.values()))m.traverse(n=>{n.geometry?.dispose();for(const x of Array.isArray(n.material)?n.material:[n.material])x?.dispose();});
globalThis.fetch=oldFetch;THREE.TextureLoader.prototype.load=oldLoad;

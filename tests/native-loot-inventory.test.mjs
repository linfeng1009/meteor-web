import test from 'node:test';
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import * as T from '../dist/vendor/three.module.js';
import {NativeItemSystem} from '../dist/native-items.js';
import {MeteorGame} from '../dist/engine.js';
import {NetworkGame} from '../dist/network-game.js';
import {NetworkRooms} from '../network-server.mjs';
import {loadBindings,defaultBindings} from '../dist/keybindings.js';
import {NativeCombatController,parsePos} from '../dist/native-combat.js';
const json=async path=>JSON.parse(await readFile(new URL(path,import.meta.url)));
const res=await json('../dist/assets/original/characters/meteor-res-data.json');
const weapons=(await json('../dist/assets/original/weapon-models/manifest.json')).items;
const weapon=weapons.find(w=>w.available&&w.modelId==='w0_0'),other=weapons.find(w=>w.available&&w.modelId==='w1_0');
const actor=()=>({hp:500,maxHp:1000,rage:0,root:new T.Group(),grounded:true,hero:true,weaponId:weapon.itemId,weapon2Id:null,combat:{busy:false}});
function item(name,model){const root=new T.Group(),visual=new T.Group();root.add(visual);return {name,root,model:visual,source:{properties:{model}},attributes:{active:1,interactive:1,collision:1},setActive(value){this.attributes.active=Number(value);root.visible=!!value;},setCollision(value){this.attributes.collision=Number(value);}};}
function fixture(instances){const events=[],system=new NativeItemSystem({itemRecords:res.allRecords.filter(r=>r.type===2),weaponItems:weapons,getInstances:()=>instances,onPickup:e=>events.push(e)});return {system,events};}

test('two simultaneous players cannot consume the same real RES weapon twice; capacity preserves the next one',()=>{
  const first=item('weapon1',other.modelId),second=item('weapon2',other.modelId),{system,events}=fixture([first,second]),a=actor(),b=actor();
  assert.equal(system.tryPickup(a).ok,true);assert.equal(a.weaponId,weapon.itemId);assert.equal(a.weapon2Id,other.itemId);
  assert.equal(system.tryPickup(a).reason,'full-weapons');assert.equal(second.attributes.active,1);
  assert.equal(system.tryPickup(b).ok,true);assert.equal(events.length,2);assert.notEqual(events[0].instance,events[1].instance);
  assert.equal(system.tryPickup(b).ok,false);
});

test('a dropped weapon is available to others immediately but its owner must leave and return',()=>{
  const drop=item('web-drop-1',other.modelId),owner=actor(),otherPlayer=actor();drop.dropOwner=owner;
  const {system}=fixture([drop]);assert.equal(system.peek(owner),null);assert.equal(system.peek(otherPlayer).kind,'weapon');
  owner.root.position.x=3;assert.equal(system.peek(owner),null);owner.root.position.x=0;assert.equal(system.tryPickup(owner).ok,true);
});

test('automatic pickup uses the common world step in training/story and does not run for replicas or blocked players',()=>{
  for(const mode of ['training','story']){
    const bun=item('bun','Item01'),{system}=fixture([bun]),hero=actor();
    const game=Object.assign(Object.create(MeteorGame.prototype),{hero,enemies:[],keys:new Set(),running:true,paused:false,mode,items:system});
    for(const block of ['paused','replica','air','script','dead','guard','busy']){
      game.paused=block==='paused';game.lootReplica=block==='replica';hero.grounded=block!=='air';hero.scriptInputBlocked=block==='script';hero.dead=block==='dead';hero.guard=block==='guard';hero.combat.busy=block==='busy';
      game._updateLoot();assert.equal(hero.hp,500,block);
    }
    game.paused=game.lootReplica=hero.scriptInputBlocked=hero.dead=hero.guard=hero.combat.busy=false;hero.grounded=true;
    game._updateLoot();assert.equal(hero.hp,800);game._updateLoot();assert.equal(hero.hp,800);
  }
});

test('ground presentation animates only supported static loot, preserves collision roots, and resets without accumulating transforms',()=>{
  const loot=item('bun','Item01'),unknown=item('decoration','unknown'),{system}=fixture([loot,unknown]);loot.root.scale.setScalar(.08);
  const origin=loot.root.position.clone();system.updateVisuals(1);const at=loot.model.quaternion.clone();assert.notEqual(loot.model.position.y,0);assert.deepEqual(loot.root.position,origin);assert.equal(loot.attributes.collision,1,'render presentation must not change collision state');system.prepareWorld();assert.equal(loot.attributes.collision,0);
  system.updateVisuals(1);assert.deepEqual(loot.model.quaternion.toArray(),at.toArray());assert.equal(unknown.model.position.y,0);
  system.reset();assert.equal(loot.model.position.y,0);assert.deepEqual(loot.model.quaternion.toArray(),new T.Quaternion().toArray());
});

test('inventory swap and drop preserve both weapons on load failure and ignore stale session completions',async()=>{
  const hero=actor();hero.weapon2Id=other.itemId;let loaded=0;
  const game=Object.assign(Object.create(MeteorGame.prototype),{hero,running:true,paused:false,sessionRequest:1,weaponItems:new Map(weapons.map(w=>[w.itemId,w])),droppedWeapons:new Map(),_emit(){},_hud(){},_prepareWeapon:async()=>{throw Error('missing');},_equip:async(f,id)=>{loaded++;f.weaponId=id;}});
  const prior=console.warn;console.warn=()=>{};try{await game.switchWeapon();await game.dropWeapon();}finally{console.warn=prior;}
  assert.equal(hero.weaponId,weapon.itemId);assert.equal(hero.weapon2Id,other.itemId);assert.equal(loaded,0);
  let finish;game._prepareWeapon=()=>new Promise(resolve=>finish=resolve);const switching=game.switchWeapon();game.sessionRequest++;finish([]);await switching;
  assert.equal(hero.weaponId,weapon.itemId);assert.equal(hero.weapon2Id,other.itemId);assert.equal(hero.switchingWeapon,false);
  game._prepareWeapon=async()=>[];await game.switchWeapon();assert.equal(hero.weaponId,other.itemId);assert.equal(hero.weapon2Id,weapon.itemId);
});

test('drop produces a real cached weapon scene instance, frees only the secondary slot and clears on reset',async()=>{
  const hero=actor();hero.weapon2Id=other.itemId;const template=new T.Group();template.add(new T.Mesh(new T.BoxGeometry(),new T.MeshBasicMaterial()));
  const game=Object.assign(Object.create(MeteorGame.prototype),{hero,running:true,paused:false,sessionRequest:1,scene:new T.Scene(),weaponItems:new Map(weapons.map(w=>[w.itemId,w])),droppedWeapons:new Map(),lootSerial:0,_prepareWeapon:async()=>[template],_ground:()=>null,_emit(){},_hud(){}});
  await game.dropWeapon();assert.equal(hero.weaponId,weapon.itemId);assert.equal(hero.weapon2Id,null);const drop=[...game.droppedWeapons.values()][0];
  assert.equal(drop.weaponId,other.itemId);assert.equal(drop.dropOwner,hero);assert.equal(drop.model.children[0].children[0].geometry,template.children[0].geometry);
  assert.equal(game._lootSnapshot().drops.length,1);game._clearDroppedWeapons();assert.equal(game.scene.children.length,0);
});

test('adding the drop binding preserves customized older layouts even when G is occupied',()=>{
  const previous=defaultBindings();delete previous.drop;previous.attack=['KeyG'];previous.forward=['KeyI'];
  const updated=loadBindings({getItem:()=>JSON.stringify(previous)});assert.deepEqual(updated.attack,['KeyG']);assert.deepEqual(updated.forward,['KeyI']);assert.notEqual(updated.drop[0],'KeyG');
});

test('room transports retry-safe inventory actions and host-only bounded loot snapshots',()=>{
  const rooms=new NetworkRooms(),a=rooms.create('房主'),b=rooms.join(a.room.code,'客人');
  const call=(p,op,data={})=>rooms.request(a.room.code,p.token,op,{round:1,...data});call(a,'ready',{ready:true});call(b,'ready',{ready:true});call(a,'start');call(a,'loaded');call(b,'loaded');
  const input=['switch','drop','pickup'].map((action,i)=>({action,active:true,angle:0,sequence:i+1}));call(b,'sync',{input});call(b,'sync',{input});assert.equal(call(a,'sync').input.length,3);
  const frame={sequence:1,time:1,loot:{consumed:['D_item'],drops:[{name:'web-drop-1',weaponId:other.itemId,position:[0,0,0]}]},players:[a,b].map(p=>({id:p.playerId,position:[0,0,0],angle:0,hp:1000,maxHp:1000,rage:0,pose:6,source:0,frame:0,serial:1,effectTime:0,weaponId:weapon.itemId,weapon2Id:null,pickupSerial:1}))};
  call(a,'sync',{frame});assert.deepEqual(call(b,'sync').frame.loot,frame.loot);assert.throws(()=>call(b,'sync',{frame}),/房主/);
  assert.throws(()=>call(a,'sync',{frame:{...frame,sequence:2,loot:{...frame.loot,drops:[{...frame.loot.drops[0],position:[NaN,0,0]}]}}}),/无效/);
  assert.equal(call(b,'sync').frame.sequence,1);
});

test('replica drop loader cannot resurrect a drop consumed while its model was loading',async()=>{
  let finish;const game=Object.assign(Object.create(MeteorGame.prototype),{lootReplica:true,sessionRequest:1,currentMap:{},droppedWeapons:new Map(),_prepareWeapon:()=>new Promise(resolve=>finish=resolve),_spawnDroppedWeapon(){assert.fail('consumed drop resurrected');}});
  game._applyLootState({consumed:[],drops:[{name:'web-drop-1',weaponId:other.itemId,position:[0,0,0]}]});game._applyLootState({consumed:[],drops:[]});finish([]);await new Promise(resolve=>setImmediate(resolve));assert.equal(game.droppedWeapons.size,0);
});

test('guest applies the host inventory, consumed props and pickup feedback once without running pickup simulation',async()=>{
  const poses=parsePos(await readFile(new URL('../dist/assets/original/characters/p0/p0.pos',import.meta.url),'utf8'));
  function fighter(id){const f=actor();f.networkId=id;f.combat=new NativeCombatController({poses,actions:new Map()},{weapon:'sword'});f.combat.play(6,{force:true});f.character={frame:0,source:0,setPoseFrame(source,frame){this.source=source;this.frame=frame;}};return f;}
  const hero=fighter('guest'),peer=fighter('host');let effects=0,loot;
  const game={hero,enemies:[peer],weaponItems:new Map(weapons.map(w=>[w.itemId,w])),pause(){},_hud(){},_applyLootState(state){loot=state;},_equip:async(f,id)=>{f.weaponId=id;},rageVfx:{playItem(){effects++;},sample(){}}};
  const session=new NetworkGame(game,{host:false,playerId:'guest',send(){}},{players:[{id:'host'},{id:'guest'}]});session.active=true;hero.pickupSerial=peer.pickupSerial=0;
  const frame={sequence:1,time:1,loot:{consumed:['D_Wpn01'],drops:[]},players:[hero,peer].map(f=>({id:f.networkId,position:[0,0,0],angle:0,hp:800,maxHp:1000,rage:0,dead:false,grounded:true,guard:false,weaponId:other.itemId,weapon2Id:weapon.itemId,pickupSerial:1,pose:6,source:0,frame:poses.get(6).start,serial:1,kills:0,deaths:0}))};
  frame.players[0].statuses=[{id:3,name:'铜皮',statKey:4,remaining:89,value:20,period:0}];
  session.apply(frame);assert.equal(hero.weaponId,other.itemId);assert.equal(hero.weapon2Id,weapon.itemId);assert.equal(hero.hp,800);assert.deepEqual(loot,frame.loot);assert.equal(game.lootReplica,true);assert.equal(effects,2);assert.deepEqual(hero.networkItemStatuses,frame.players[0].statuses);
  session.apply(frame);session.apply({...frame,sequence:2});assert.equal(effects,2,'snapshots and retries cannot replay pickup effects');session.dispose();assert.equal(game.lootReplica,undefined);
});

test('a real RES defense buff serializes its nonperiodic status into a valid host snapshot',()=>{
  const hero=actor(),peer=actor();hero.networkId='host';peer.networkId='guest';hero.character=peer.character={source:0,frame:0};
  const {system}=fixture([item('buff','Item03')]);assert.equal(system.tryPickup(hero).ok,true);assert.equal(hero.scriptItems[0].period,null);
  const game={hero,enemies:[peer],matchElapsed:1,pause(){},_lootSnapshot:()=>({consumed:['buff'],drops:[]})};
  const session=new NetworkGame(game,{host:true,playerId:'host',send(){}},{players:[{id:'host'},{id:'guest'}]});session.active=true;
  const state=session.snapshot();assert.equal(state.players[0].statuses[0].period,0);assert.equal(state.players[0].statuses[0].remaining,90);assert.doesNotThrow(()=>JSON.stringify(state));session.dispose();
});

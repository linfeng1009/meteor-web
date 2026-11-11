import test, { after } from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { loadNativeCombat, NativeCombatController, NativePoseTimeline, createNativeDamageResolver, nativeReactionParameters, nativeHitAngle, nativeHitSelection, nativeGuardPose, NATIVE_GUARD_REACTIONS, NATIVE_DEFAULT_BLEND_TIME } from '../dist/native-combat.js';
import { NativeImpactFeedback } from '../dist/native-impact-feedback.js';
import { NativeBloodFeedback } from '../dist/native-blood-feedback.js';
import { NetworkGame } from '../dist/network-game.js';
import {bindLocalPlayerControl} from '../dist/player-control.js';
import {NetworkClient} from '../dist/network-client.js';
import {NetworkRooms} from '../network-server.mjs';

// Real POS, RES, SKC/BNC/AMB and native weapons on a plain CPU test floor.
// Textures, browser rendering/audio and NPC retaliation are intentionally absent;
// these tests prove the hit/reaction chain, not original AI or manual victory.
const dist = new URL('../dist/', import.meta.url), v = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
const priorFetch = globalThis.fetch, priorTextureLoad = THREE.TextureLoader.prototype.load;
globalThis.fetch = async input => { try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); } catch { return new Response('', { status: 404 }); } };
THREE.TextureLoader.prototype.load = function(url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
const data = await loadNativeCombat(), weapons = JSON.parse(await readFile(new URL('assets/original/weapon-models/manifest.json', dist), 'utf8'));
const fixtures = [];

test('native Move/Value packing preserves their separate motion/time meanings and original float32 wire rounding', () => {
  assert.deepEqual(nativeReactionParameters(data.poses.get(315).attacks[0]), { motionScale: 10, duration: .5 });
  assert.deepEqual(nativeReactionParameters(data.poses.get(262).attacks[0]), { motionScale: 5, duration: 0.09999999403953552 });
  assert.deepEqual(nativeReactionParameters(data.poses.get(297).attacks[0], { guarded: true }), { motionScale: 8, duration: 0.5999999642372131 });
});

test('one-frame airborne source loops hold exactly one transform and cannot sample another pose or generate endless vertical velocity', () => {
  const pose = data.poses.get(339), sampled = [];
  const timeline = new NativePoseTimeline(pose, { loop: true, sampleRoot: (_source, frame) => { sampled.push(frame); return { x: 0, y: 0, z: frame }; } });
  for (let frame = 0; frame < 180; frame++) {
    const state = timeline.advance(1 / 60); assert.equal(state.frame, pose.loopStart); assert.equal(state.rootDelta.z, 0); assert.equal(state.finished, false);
  }
  assert.ok(sampled.every(frame => frame === pose.loopStart));
});

test('source reaction selection uses native signed angles, exact sector boundaries and append-time fallback', () => {
  const attack = data.poses.get(262).attacks[0];
  for (const [position, direction, poseId] of [[v(0, 0, 2), 0, 93], [v(2, 0, 0), 2, 94], [v(-2, 0, 0), 1, 91], [v(0, 0, -2), 3, 92]]) {
    const result = nativeHitSelection(attack, nativeHitAngle(position, v()));
    assert.equal(result.direction, direction); assert.equal(result.poseId, poseId);
    const rotated = v(position.z, 0, -position.x);
    assert.equal(nativeHitSelection(attack, nativeHitAngle(rotated, v(), Math.PI / 2)).poseId, poseId, 'rotate actor and attacker together');
  }
  for (const [angle, direction] of [[.7853975 - 1e-9, 0], [.7853975, 2], [-.7853975 + 1e-9, 0], [-.7853975, 1], [2.3561924999999997, 3], [-2.3561924999999997, 3]]) {
    assert.equal(nativeHitSelection(attack, angle).direction, direction);
  }
  assert.equal(nativeHitSelection({ targetpose: 103, targetposeleft: -1 }, Math.PI / 2).poseId, 103);
  assert.equal(nativeHitSelection(attack, nativeHitAngle(v(), v())).direction, 0);
});

test('source guard selection retains each weapon-state list, all four front variants and its fixed side/back entries', () => {
  const expected = { dart: [40, 41, 42, 43, 77, 78, 79], dual: [52, 53, 54, 55, 77, 78, 79], dagger: [56, 57, 58, 59, 83, 84, 85],
    sword: [60, 61, 62, 63, 80, 81, 82], spear: [64, 65, 66, 67, 86, 87, 88], blade: [68, 69, 70, 71, 80, 81, 82], hammer: [72, 73, 74, 75, 77, 78, 79] };
  for (const [weapon, poses] of Object.entries(expected)) {
    assert.deepEqual(NATIVE_GUARD_REACTIONS[weapon], poses);
    for (let n = 0; n < 4; n++) assert.equal(nativeGuardPose(weapon, 0, () => n / 4), poses[n]);
    for (let direction = 1; direction < 4; direction++) assert.equal(nativeGuardPose(weapon, direction), poses[direction + 3]);
    assert.ok(poses.every(id => data.poses.get(id)?.valid && Number.isFinite(data.poses.get(id).loopStart)));
  }
});

test('front guard follows the original CRT53-bit draw distribution, including the maximum draw selecting slot4', () => {
  const counts = new Map();
  for (let draw = 0; draw <= 32767; draw++) {
    const pose = nativeGuardPose('sword', 0, () => draw / 32768);
    counts.set(pose, (counts.get(pose) || 0) + 1);
  }
  assert.deepEqual([...counts], [[60, 8192], [61, 8192], [62, 8192], [63, 8191], [80, 1]]);
  assert.equal(nativeGuardPose('sword', 0, () => 32767 / 32768), 80);
});
after(() => {
  for (const { game, floor } of fixtures) {
    game.projectiles?.dispose(); game.impactFeedback?.dispose(); game.bloodFeedback?.dispose(); for (const actor of [game.hero, ...game.enemies]) actor.character.dispose();
    for (const promise of game.weaponCache.values()) promise.then(model => model.traverse(node => {
      node.geometry?.dispose(); for (const material of Array.isArray(node.material) ? node.material : [node.material]) material?.dispose();
    }));
    floor.geometry.dispose(); floor.material.dispose();
  }
  globalThis.fetch = priorFetch; THREE.TextureLoader.prototype.load = priorTextureLoad;
});

async function fixture() {
  const game = Object.create(MeteorGame.prototype), events = [], sounds = [];
  const floor = new THREE.Mesh(new THREE.PlaneGeometry(200, 200), new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }));
  floor.rotation.x = -Math.PI / 2; floor.updateMatrixWorld(true);
  Object.assign(game, { combatData: data, weaponManifest: weapons,
    weaponItems: new Map(weapons.items.map(item => [Number(item.itemId), item])),
    weaponModels: new Map(weapons.models.map(model => [model.modelId.toLowerCase(), model])), weaponCache: new Map(),
    effectDefinitions: new Map(), waveFiles: new Map(), effects: [], scene: new THREE.Scene(), camera: new THREE.PerspectiveCamera(), raycaster: new THREE.Raycaster(),
    hostPhysics: { speed: 8, gravity: 34, jumpVelocity: 12, radius: .4, step: .55 },
    currentMap: { colliders: [floor], bounds: new THREE.Box3(v(-100, -1, -100), v(100, 30, 100)), metadata: {}, spawns: [{ position: v(0, .015, 0) }] },
    weapon: 'sword', actorSerial: 0, enemies: [], keys: new Set(), directionBuffer: [], cameraAngle: 0,
    running: true, paused: false, mode: 'training', elapsed: 0, matchElapsed: 0, kills: 0, deaths: 0, totalDamage: 0, contactHits: 0,
    onEvent: event => events.push(event), onUpdate() {}, _emit(text, type, amount, point, extra) { events.push({ text, type, amount, ...extra }); },
    _nameplate() {}, _unlockAudio() {}, _soundDefinition: name => sounds.push(name), _hud() {} });
  game.damageResolver = createNativeDamageResolver(data); game._initializeProjectiles();
  game.hero = await game._createFighter(0, '孟星魂', true); game.scene.add(game.hero.root);
  game._placeFighter(game.hero, { position: v(0, .015, 0) }); await game._equip(game.hero, 'sword');
  const target = await game._createFighter(8, '原版对练角色'); game.scene.add(target.root); game.enemies.push(target);
  game._placeFighter(target, { position: v(0, .015, 1.1) }); await game._equip(target, 'spear');
  target.maxHp = target.hp = 10000; target.team = target.teamMask = 2; game.hero.team = game.hero.teamMask = 1;
  target.scriptControlled = true; target.scriptControl = { paused: true }; game.locked = target;
  const result = { game, hero: game.hero, target, floor, events, sounds }; fixtures.push(result); return result;
}
function hit(game, attacker, target, poseId, attack = data.poses.get(poseId).attacks[0]) {
  return game._applyNativeHit(attacker, target, { poseId, pose: data.poses.get(poseId) }, attack, target.root.position.clone().add(v(0, 1.35, 0)));
}
function tick(game, dt = 1 / 60) {
  game.elapsed += dt; game.matchElapsed += dt;
  game._updateFighter(game.hero, dt); for (const actor of game.enemies) game._updateFighter(actor, dt);
  game.projectiles.update(dt);
}

test('real native HP loss emits blood and a guard emits only sparks, including host event and replica deduplication',async()=>{
  const {game,hero,target}=await fixture();game.bloodFeedback=new NativeBloodFeedback(game.scene);game.impactFeedback=new NativeImpactFeedback(game.scene);
  hero.networkId='host';target.networkId='guest';const before=target.hp;hit(game,hero,target,262);
  assert.ok(target.hp<before);assert.ok(game.bloodFeedback.mesh.visible);assert.equal(game.combatFeedbackEvents.at(-1).blood,true);
  assert.equal(game.combatFeedbackEvents.at(-1).attackerId,'host');assert.equal(game.combatFeedbackEvents.at(-1).targetId,'guest');
  game.bloodFeedback.clear();target.guard=true;hit(game,hero,target,262);assert.equal(game.bloodFeedback.mesh.visible,false);assert.equal(game.combatFeedbackEvents.at(-1).guarded,true);assert.equal(game.combatFeedbackEvents.at(-1).blood,false);
  const events=game._combatFeedbackSnapshot(),played=[];
  const session=new NetworkGame(game,{host:false,playerId:'guest',send(){}},{players:[{id:'host'},{id:'guest'}]});session.active=true;
  const original=game._playCombatFeedback;game._playCombatFeedback=(event,local)=>played.push({id:event.id,local});
  const frame={sequence:1,time:game.matchElapsed,players:[],impacts:events};session.apply(frame);session.apply(frame);session.apply({...frame,sequence:2});assert.equal(played.length,events.length);assert.ok(played.every(e=>e.local));
  session.apply({...frame,sequence:3,time:5,impacts:[{...events[0],id:100,time:0}]});assert.equal(played.length,events.length,'expired feedback cannot replay after a stall');
  game._playCombatFeedback=original;session.dispose();
});

test('listen-host remote inputs use native movement and hit the actual host, then replicas use the same HP snapshot',async()=>{
  const {game,hero,target}=await fixture();await game._equip(target,'sword');target.scriptControlled=false;target.networkId='guest';hero.networkId='host';target.root.rotation.y=Math.PI;
  const room={players:[{id:'host'},{id:'guest'}]},client={host:true,playerId:'host',send(){}};
  const session=new NetworkGame(game,client,room);session.play();
  try{
    game.pause(true);assert.equal(game.paused,false,'network menu must not stop the shared simulation');game.pause(false);
    session.inputs([{playerId:'guest',action:'attack',active:true,angle:0}]);assert.equal(target.combat.timeline.pose.id,262);
    for(let i=0;i<90;i++)tick(game);assert.ok(hero.hp<hero.maxHp,'remote sword must damage host through the original contact path');
    const frame=session.snapshot();assert.equal(frame.players.find(p=>p.id==='host').hp,hero.hp);assert.equal(frame.players.find(p=>p.id==='guest').id,'guest');
    const before=target.root.position.x;session.inputs([{playerId:'guest',action:'right',active:true,angle:0}]);for(let i=0;i<30;i++)tick(game);assert.ok(target.root.position.x>before+1);
    session.inputs([{playerId:'guest',action:'clear',active:false,angle:0}]);assert.equal(session.remote.keys.size,0);
    assert.equal(game.hero,hero);assert.equal(game.enemies[0],target,'temporary actor context must restore host references');
    target.spawnIndex=1;game.currentMap.spawns.push({position:v(0,.015,6)});target.hp=1;hit(game,hero,target,262);assert.equal(target.dead,true);assert.equal(session.scores.get('host').kills,1);
    for(let i=0;i<200;i++)tick(game);assert.equal(target.dead,false);assert.ok(target.root.position.z>5,'remote respawns at its own source spawn rather than the host spawn');
    const replica=await fixture();replica.hero.networkId='guest';replica.target.networkId='host';const guestSession=new NetworkGame(replica.game,{host:false,playerId:'guest',send(){}},room);guestSession.play();
    try{guestSession.apply(session.snapshot());assert.equal(replica.hero.hp,target.hp);assert.equal(replica.target.hp,hero.hp);assert.deepEqual(replica.hero.root.position.toArray(),target.root.position.toArray());const position=replica.hero.root.position.clone();tick(replica.game);assert.deepEqual(replica.hero.root.position.toArray(),position.toArray(),'guest must not independently simulate authoritative movement');replica.target.root.position.copy(replica.hero.root.position).add(v(.1,0,0));replica.game._separateCharacters(.1);assert.deepEqual(replica.hero.root.position.toArray(),position.toArray(),'guest must not independently separate authoritative bodies');}
    finally{guestSession.dispose();}
    game._placeFighter(hero,{position:v(0,.015,0)});game._placeFighter(target,{position:v(.1,.015,0)});game._separateCharacters(.1);
    assert.ok(Math.abs(Math.abs(hero.root.position.x)-Math.abs(target.root.position.x-.1))<1e-8,'body separation must not give the host the old player-vs-NPC weight advantage');
  }finally{session.dispose();}
});

test('reliable transport applies the real remote sword attack once despite lost delivery and acknowledgement',async()=>{
  const {game,hero,target}=await fixture(),rooms=new NetworkRooms(),a=rooms.create('房主'),b=rooms.join(a.room.code,'客人');
  const request=(player,op,data={})=>rooms.request(a.room.code,player.token,op,{round:1,...data});
  request(a,'ready',{ready:true});request(b,'ready',{ready:true});request(a,'start');request(a,'loaded');request(b,'loaded');
  hero.networkId=a.playerId;target.networkId=b.playerId;await game._equip(target,'sword');target.root.rotation.y=Math.PI;
  let session,attackCalls=0;const host=new NetworkClient({onInput:batch=>{attackCalls+=batch.filter(x=>x.action==='attack').length;session.inputs(batch);},getFrame:()=>session.snapshot()}),guest=new NetworkClient();
  for(const [client,player] of [[host,a],[guest,b]]){Object.assign(client,{room:request(player,'sync').room,code:a.room.code,playerId:player.playerId});client.api=async(path,data)=>request(player,'sync',data);}
  session=new NetworkGame(game,host,host.room);session.play();const api=host.api;let calls=0;
  host.api=async(path,data)=>{calls++;if(calls===3)throw Error('确认未送达');const result=await api(path,data);if(calls===1)throw Error('投递响应丢失');return result;};
  try{
    guest.send('attack');await guest.sync();await host.sync();assert.equal(attackCalls,0);await host.sync();assert.equal(attackCalls,1);
    for(let i=0;i<90;i++)tick(game);const hp=hero.hp;assert.ok(hp<hero.maxHp,'delivered remote input must really damage the host');
    await host.sync();await host.sync();await host.sync();assert.equal(attackCalls,1);assert.equal(hero.hp,hp);assert.equal(rooms.rooms.get(a.room.code).players[1].input.length,0);
  }finally{session.dispose();}
});

test('guest lock toggles only on key down; focus loss clears input and menus reject new actions without stopping the world',async()=>{
  const {game,hero,target}=await fixture();hero.networkId='guest';target.networkId='host';const sent=[];
  const client={host:false,playerId:'guest',send:(action,active)=>sent.push({action,active})},room={players:[{id:'host'},{id:'guest'}]};
  const session=new NetworkGame(game,client,room);session.play();game.locked=null;sent.length=0;
  try{
    game.action('lock',true);assert.equal(game.locked,target);game.action('lock',false);assert.equal(game.locked,target,'key release must not undo the local lock');
    game.action('lock',true);game.action('lock',false);assert.equal(game.locked,null);
    game.action('forward');game.directionBuffer=[{direction:'up'}];game.recoveryAttack={actor:hero};game.traversalTap={direction:'forward'};hero.guard=true;
    game.releaseInput();assert.equal(sent.at(-1).action,'clear');assert.equal(game.keys.size,0);assert.equal(game.directionBuffer.length,0);assert.equal(game.recoveryAttack,null);assert.equal(game.traversalTap,null);assert.equal(hero.guard,false);
    const count=sent.length;for(const action of ['attack','jump','forward','guard','lock'])game.action(action,true);assert.equal(sent.length,count);assert.equal(game.locked,null);
    game.pause(true);assert.equal(game.paused,false,'menu must not freeze network world');game.pause(false);const resumed=sent.length;
    game.action('forward');assert.equal(sent.length,resumed+1);assert.equal(sent.at(-1).action,'forward');
  }finally{session.dispose();}
});

test('host input suspension releases held defense and movement while remote input remains active',async()=>{
  const {game,hero,target}=await fixture();bindLocalPlayerControl(game);target.networkId='guest';hero.networkId='host';target.root.position.z=10;
  const session=new NetworkGame(game,{host:true,playerId:'host',send(){}},{players:[{id:'host'},{id:'guest'}]});session.play();
  try{
    game.action('guard');game.action('right');session.inputs([{playerId:'guest',action:'forward',active:true,angle:Math.PI}]);
    game.pause(true);assert.equal(hero.guard,false);assert.equal(game.keys.size,0);assert.ok(session.remote.keys.has('forward'));
    const serial=hero.combat.serial;game.action('attack');game.action('guard');game.action('right');assert.equal(hero.combat.serial,serial);assert.equal(hero.guard,false);assert.equal(game.keys.size,0);
    const z=target.root.position.z;for(let i=0;i<20;i++)tick(game);assert.ok(target.root.position.z>z+.5,'remote keeps moving while host menu is open');
    game.pause(false);game.action('guard');assert.equal(hero.guard,true);
  }finally{session.dispose();}
});

test('reliable focus-release clear reaches the host after a lost response and removes held controls',async()=>{
  const {game,hero,target}=await fixture(),rooms=new NetworkRooms(),a=rooms.create('房主'),b=rooms.join(a.room.code,'客人');
  const request=(player,op,data={})=>rooms.request(a.room.code,player.token,op,{round:1,...data});
  request(a,'ready',{ready:true});request(b,'ready',{ready:true});request(a,'start');request(a,'loaded');request(b,'loaded');
  hero.networkId=a.playerId;target.networkId=b.playerId;let session;const host=new NetworkClient({onInput:batch=>session.inputs(batch)}),guest=new NetworkClient();
  for(const [client,player] of [[host,a],[guest,b]]){Object.assign(client,{room:request(player,'sync').room,code:a.room.code,playerId:player.playerId});client.api=async(path,data)=>request(player,'sync',data);}
  session=new NetworkGame(game,host,host.room);session.play();
  try{
    guest.send('forward');guest.send('guard');await guest.sync();await host.sync();assert.ok(session.remote.keys.has('forward'));assert.ok(session.remote.keys.has('guard'));
    const api=guest.api;let dropped=false;guest.api=async(path,data)=>{const result=await api(path,data);if(!dropped){dropped=true;throw Error('释放响应丢失');}return result;};
    guest.send('clear',false);await guest.sync();await guest.sync();await host.sync();assert.equal(session.remote.keys.size,0);assert.equal(target.guard,false);assert.equal(guest.held.size,0);
    await host.sync();assert.equal(session.remote.keys.size,0,'acknowledgement retry must not restore old held controls');
  }finally{session.dispose();}
});

test('standing double tap preserves the sword down-up-up attack and works through remote player controls',async()=>{
  const {game,hero,target}=await fixture();hero.networkId='host';target.networkId='guest';await game._equip(target,'sword');
  const session=new NetworkGame(game,{host:true,playerId:'host',send(){}},{players:[{id:'host'},{id:'guest'}]});session.play();
  try{
    game.action('back');game.action('back',false);game.elapsed+=.1;game.action('forward');game.action('forward',false);game.elapsed+=.1;game.action('forward');game.action('forward',false);
    assert.equal(hero.combat.timeline.pose.id,165);game.action('attack');assert.equal(hero.combat.currentMove.poseId,277);assert.equal(hero.combat.currentMove.name,'忌冬雨');assert.equal(hero.rage,0);
    const localBuffer=game.directionBuffer;
    session.inputs([{playerId:'guest',action:'right',active:true,angle:Math.PI},{playerId:'guest',action:'right',active:false,angle:Math.PI}]);game.elapsed+=.1;
    session.inputs([{playerId:'guest',action:'right',active:true,angle:Math.PI}]);assert.equal(target.combat.timeline.pose.id,168);assert.equal(target.combat.currentMove.kind,'dash');assert.equal(game.directionBuffer,localBuffer);
    session.inputs([{playerId:'guest',action:'clear',active:false,angle:0}]);assert.equal(session.remote.keys.size,0);assert.equal(target.combat.currentMove.kind,'dash','release does not invent a forced motion cancel');
  }finally{session.dispose();}
});

test('one delivered batch preserves rapid remote dash/roll/command timing without advancing host time',async()=>{
  const {game,hero,target}=await fixture();hero.networkId='host';target.networkId='guest';await game._equip(target,'sword');
  const session=new NetworkGame(game,{host:true,playerId:'host',send(){}},{players:[{id:'host'},{id:'guest'}]});session.play();
  const send=(action,active,time)=>({playerId:'guest',action,active,time,angle:Math.PI});
  try{
    const elapsed=game.elapsed,position=target.root.position.clone();
    session.inputs([send('forward',true,100),send('forward',false,100.03),send('forward',true,100.12)]);
    assert.equal(target.combat.timeline.pose.id,165);assert.equal(game.elapsed,elapsed);assert.deepEqual(target.root.position.toArray(),position.toArray(),'recognizing input must not simulate client elapsed movement');
    target.combat.play(6,{force:true});session.inputs([send('clear',false,101),send('crouch',true,101.01),send('right',true,101.02),send('right',false,101.03),send('right',true,101.15)]);
    assert.equal(target.combat.timeline.pose.id,177);
    target.combat.play(6,{force:true});session.inputs([send('clear',false,102),send('back',true,102.01),send('back',false,102.02),send('forward',true,102.08),send('forward',false,102.09),send('forward',true,102.16),send('forward',false,102.17),send('attack',true,102.2)]);
    assert.equal(target.combat.currentMove.poseId,277);assert.equal(game.elapsed,elapsed);assert.equal(hero.combat.busy,false);
    target.combat.react(90);session.inputs([send('attack',true,103)]);assert.equal(session.remote.recoveryAttack.time,103);assert.ok(session.remote.recoveryAttack.expires<=elapsed+.301,'recovery expiration must use the host clock');
    game.elapsed+=.4;game._updateFighter(target,1/60);assert.equal(session.remote.recoveryAttack,null,'expired recovery cannot wait for the unrelated client clock');
  }finally{session.dispose();}
});

test('two players keep movement, keys and camera independent without swapping game references',async()=>{
  const {game,hero,target}=await fixture();bindLocalPlayerControl(game);target.networkId='guest';hero.networkId='host';target.root.position.z=10;
  const session=new NetworkGame(game,{host:true,playerId:'host',send(){}},{players:[{id:'host'},{id:'guest'}]});session.play();
  const peers=game.enemies,spawns=game.currentMap.spawns,events=game.onEvent;
  // Reject even a temporary swap, including one restored in a finally block.
  for(const [object,key] of [[game,'hero'],[game,'enemies'],[game,'onEvent'],[game.currentMap,'spawns']]){
    const value=object[key];Object.defineProperty(object,key,{configurable:true,get:()=>value,set(){throw Error('global reference swap: '+key);}});
  }
  try{
    game.cameraAngle=0;game.action('right');
    session.inputs([{playerId:'guest',action:'right',active:true,angle:Math.PI}]);
    const beforeHost=hero.root.position.x,beforeGuest=target.root.position.x;
    for(let i=0;i<30;i++)tick(game);
    assert.ok(hero.root.position.x>beforeHost+1);assert.ok(target.root.position.x<beforeGuest-1);
    assert.equal(game.cameraAngle,0);assert.equal(session.remote.cameraAngle,Math.PI);assert.notEqual(game.localControl.keys,session.remote.keys);
    session.inputs([{playerId:'guest',action:'clear',active:false,angle:0}]);assert.equal(session.remote.keys.size,0);assert.ok(game.keys.has('right'));
    game.action('right',false);game.action('guard');session.inputs([{playerId:'guest',action:'guard',active:true,angle:Math.PI}]);
    game.action('guard',false);assert.equal(hero.guard,false);assert.equal(target.guard,true);assert.ok(session.remote.keys.has('guard'));
    assert.equal(game.hero,hero);assert.equal(game.enemies,peers);assert.equal(game.currentMap.spawns,spawns);assert.equal(game.onEvent,events);
  }finally{session.dispose();for(const [object,key,value] of [[game,'hero',hero],[game,'enemies',peers],[game,'onEvent',events],[game.currentMap,'spawns',spawns]])Object.defineProperty(object,key,{value,writable:true,configurable:true});}
  assert.equal(target.playerControl,undefined);assert.equal(game._controlFor(target),null,'leaving removes remote player control');
});

test('remote crouch double tap rolls using its own angle and does not consume local direction history',async()=>{
  const {game,hero,target}=await fixture();bindLocalPlayerControl(game);target.networkId='guest';hero.networkId='host';
  const session=new NetworkGame(game,{host:true,playerId:'host',send(){}},{players:[{id:'host'},{id:'guest'}]});session.play();
  try{
    game.action('left');game.action('left',false);const localBuffer=game.directionBuffer;
    session.inputs([{playerId:'guest',action:'crouch',active:true,angle:1},{playerId:'guest',action:'forward',active:true,angle:1},{playerId:'guest',action:'forward',active:false,angle:1}]);
    game.elapsed+=.1;session.inputs([{playerId:'guest',action:'forward',active:true,angle:1}]);
    assert.equal(target.combat.timeline.pose.id,176);assert.equal(target.root.rotation.y,1+Math.PI);assert.equal(hero.combat.busy,false);
    assert.equal(game.directionBuffer,localBuffer);assert.ok(localBuffer.length>0);assert.equal(session.remote.directionBuffer.length,0);
  }finally{session.dispose();}
});

test('hits, death and respawn clear only the affected player commands and release locks',async()=>{
  const {game,hero,target}=await fixture();bindLocalPlayerControl(game);target.networkId='guest';hero.networkId='host';target.spawnIndex=1;game.currentMap.spawns.push({position:v(0,.015,6)});
  const session=new NetworkGame(game,{host:true,playerId:'host',send(){}},{players:[{id:'host'},{id:'guest'}]});session.play();
  try{
    game.action('left');game.action('left',false);const local=game.directionBuffer;
    session.inputs([{playerId:'guest',action:'back',active:true,angle:Math.PI},{playerId:'guest',action:'back',active:false,angle:Math.PI}]);assert.ok(session.remote.directionBuffer.length);
    hit(game,hero,target,262);assert.equal(session.remote.directionBuffer.length,0);assert.equal(game.directionBuffer,local);
    session.inputs([{playerId:'guest',action:'attack',active:true,angle:Math.PI}]);assert.equal(session.remote.recoveryAttack.actor,target);assert.equal(game.recoveryAttack,null);
    session.remote.locked=hero;game.locked=target;target.hp=1;hit(game,hero,target,262);
    assert.equal(target.dead,true);assert.equal(game.locked,null);assert.equal(session.remote.recoveryAttack,null);assert.equal(game.directionBuffer,local);
    for(let i=0;i<200;i++)tick(game);assert.equal(target.dead,false);assert.ok(target.root.position.z>5);assert.equal(session.remote.traversalTap,null);
    session.remote.locked=hero;const remoteHistory=[{direction:'down',time:game.elapsed,air:false}];session.remote.directionBuffer=remoteHistory;
    hero.hp=1;hit(game,target,hero,262);assert.equal(session.remote.locked,null,'local death must release remote combat lock too');assert.equal(game.directionBuffer.length,0);assert.equal(session.remote.directionBuffer,remoteHistory,'a remote hit must not clear the attacker command history');
  }finally{session.dispose();}
});

test('fixed world replay preserves sword hits, death, respawn and movement across render rates and stalls',async()=>{
  const results=[];
  for(const deltas of [Array(180).fill(1/30),Array(360).fill(1/60),Array(864).fill(1/144),Array(60).fill(.1)]){
    const {game,hero,target}=await fixture();game.updateAccum=0;target.hp=1;
    let tickIndex=0;const frames=[],step=game._stepWorld.bind(game);
    game._stepWorld=dt=>{
      if(tickIndex===0)game.action('attack');
      if(tickIndex===210)game.action('right');
      if(tickIndex===240){game.action('right',false);game.action('jump');}
      if(tickIndex===300)game.action('guard');
      if(tickIndex===330)game.action('guard',false);
      step(dt);tickIndex++;
      frames.push([hero.root.position.toArray(),hero.hp,hero.rage,hero.combat.timeline.pose.id,hero.character.frame,hero.grounded,hero.guard,target.hp,target.dead,target.root.position.toArray(),game.kills,game.matchElapsed]);
    };
    for(const delta of deltas)game._advanceWorld(delta);
    assert.equal(tickIndex,360);assert.ok(frames.some(f=>f[8]),'actual sword hit must kill the wounded target');
    assert.equal(target.dead,false,'the original respawn path must run during fixed ticks');
    assert.equal(game.kills,1);assert.ok(frames.some(f=>!f[5]),'jump input must reach airborne state');assert.ok(hero.root.position.x>1,'movement must run');
    results.push(frames);
  }
  for(const frames of results.slice(1))assert.deepEqual(frames,results[0]);
});

test('fixed world replay preserves all sword combo contacts at 30/60/144Hz and 100ms stalls',async()=>{
  const results=[];
  for(const deltas of [Array(90).fill(1/30),Array(180).fill(1/60),Array(432).fill(1/144),Array(30).fill(.1)]){
    const {game,hero,target,events}=await fixture();game.updateAccum=0;let index=0;const step=game._stepWorld.bind(game),states=[];
    game._stepWorld=dt=>{
      if(index%6===0&&game.contactHits<3)game.action('attack');
      step(dt);index++;states.push([hero.combat.timeline.pose.id,hero.character.frame,target.hp,target.rage,target.combat.timeline.pose.id,target.root.position.toArray()]);
    };
    for(const dt of deltas)game._advanceWorld(dt);
    assert.deepEqual(events.filter(e=>e.type==='hit').map(e=>e.poseId),[262,263,264]);results.push(states);
  }
  for(const states of results.slice(1))assert.deepEqual(states,results[0]);
});

test('real hit events, original animation and impact sound all use the selected front/back/side source pose', async () => {
  for (const [offset, expected] of [[v(0, 0, 1.1), 93], [v(1.1, 0, 0), 94], [v(-1.1, 0, 0), 91], [v(0, 0, -1.1), 92]]) {
    const { game, hero, target, events, sounds } = await fixture();
    game._placeFighter(hero, { position: target.root.position.clone().add(offset) });
    hit(game, hero, target, 262);
    assert.equal(target.combat.timeline.pose.id, expected);
    assert.equal(events.find(event => event.type === 'hit').raw.selectedTargetPose, expected);
    assert.ok(sounds.includes(`W00BL${String(expected).padStart(3, '0')}`)); assert.ok(target.hp < target.maxHp);
    game._updateFighter(target, .2);
    const source = target.character.combatPoses.get(expected);
    assert.equal(target.character.source, source.source);
    assert.ok(target.character.frame >= source.start && target.character.frame <= source.end);
  }
});

test('an interrupted native hit blend starts from the actual displayed bones and weapon attachments without a pose pop', async () => {
  const { game, hero, target } = await fixture(); game._updateFighter(target, 1 / 60);
  const positions = () => ['bau_Head', 'bau_R_Hand', 'd_wpnR'].map(name => target.character.getAttachment(name).getWorldPosition(v()));
  const before = positions(); hit(game, hero, target, 262);
  assert.ok(positions().every((point, i) => point.distanceTo(before[i]) < 1e-6), 'contact starts at weight zero');
  assert.equal(target.combat.poseBlend.duration, NATIVE_DEFAULT_BLEND_TIME);
  game._updateFighter(target, .045);
  const partial = positions(), firstSnapshot = target.combat.poseBlend.from.snapshot.id;
  assert.ok(partial.some((point, i) => point.distanceTo(before[i]) > .001), 'native skeleton visibly enters the hit pose');
  hit(game, hero, target, 263);
  assert.ok(target.combat.poseBlend.from.snapshot.id > firstSnapshot);
  assert.ok(positions().every((point, i) => point.distanceTo(partial[i]) < 1e-6), 'second contact preserves the interrupted displayed blend');
  assert.equal(target.combat.poseBlend.weight, 0);
  game._updateFighter(target, .03);
  assert.ok(Math.abs(target.combat.poseBlend.weight - .03 / NATIVE_DEFAULT_BLEND_TIME) < 1e-6);
  assert.equal(target.combat.timeline.frame, target.combat.timeline.pose.start, 'blend does not skip hit animation time');
});

test('a blocked rear blow plays the defender sword guard pose, moves by native DefenseMove, holds DefenseValue and returns to guard', async () => {
  const { game, hero, target } = await fixture(); await game._equip(hero, 'blade'); await game._equip(target, 'sword');
  target.scriptControl.guard = true; target.guard = true;
  const start = target.root.position.clone(); hit(game, hero, target, 297);
  assert.equal(target.hp, 10000); assert.equal(game.totalDamage, 0);
  assert.equal(target.combat.timeline.pose.id, 82); assert.equal(target.combat.reactionPhase, 'guard');
  assert.equal(target.combat.poseBlend.duration, Math.fround(.01));
  const pose = target.combat.timeline.pose, a = target.character.sampleSceneMotion(pose.source, pose.start), b = target.character.sampleSceneMotion(pose.source, pose.end);
  let elapsed = 0;
  while (target.combat.reacting && elapsed < 2) { game._updateFighter(target, 1 / 60); elapsed += 1 / 60; assert.equal(target.guard, true); }
  assert.ok(elapsed >= .61 && elapsed < .7, `native .01 blend followed by .6 hold: ${elapsed}`);
  assert.ok(Math.abs(target.root.position.x - start.x - (b.x - a.x) * .08 * 8) < 1e-5);
  assert.ok(Math.abs(target.root.position.z - start.z + (b.y - a.y) * .08 * 8) < 1e-5);
  assert.ok(target.root.position.distanceTo(start) > .1, 'authored block recoil must move the collision root');
  game._updateFighter(target, 1 / 60);
  assert.equal(target.combat.timeline.pose.id, 16); assert.equal(target.guard, true);
});

test('public held guard can be released and pressed during block stun, repeated blocks preserve HP and a source break-guard hit interrupts it', async () => {
  const { game, hero, target } = await fixture();
  game.action('guard'); hit(game, target, hero, 262);
  assert.equal(hero.combat.reactionPhase, 'guard'); assert.equal(hero.guard, true);
  game.action('guard', false); assert.equal(hero.guard, false);
  game.action('guard'); assert.equal(hero.guard, true);
  game.action('attack'); game.action('jump'); assert.equal(hero.combat.queuedMove, null); assert.equal(hero.grounded, true);
  const hp = hero.hp; game._updateFighter(hero, .06); hit(game, target, hero, 262);
  assert.equal(hero.hp, hp); assert.equal(hero.combat.reactionPhase, 'guard');
  hit(game, target, hero, 298);
  assert.ok(hero.hp < hp); assert.equal(hero.guard, false); assert.equal(hero.combat.reactionPhase, 'hit');
});

test('a native light-hit reaction discards queued offense and cannot be canceled by normal attack or locomotion input', () => {
  const combat = new NativeCombatController(data, { weapon: 'sword' }); let paid = 0;
  combat.attack({ poseId: 262 }); combat.attack({ poseId: 263, onStart: () => paid++ });
  assert.equal(combat.queued, 263); assert.equal(combat.react(93), true);
  assert.equal(combat.timeline.pose.id, 93); assert.equal(combat.reacting, true); assert.equal(combat.busy, true);
  assert.equal(combat.currentMove, null); assert.equal(combat.queuedMove, null);
  for (let frame = 0; frame < 8; frame++) {
    assert.equal(combat.attack(), false); assert.equal(combat.play(140), false);
    combat.update(1 / 60, { grounded: true }); assert.equal(combat.timeline.pose.id, 93);
  }
  combat.update(1, { grounded: true });
  assert.equal(combat.reacting, false); assert.equal(combat.busy, false); assert.equal(paid, 0);
  assert.equal(combat.attack(), true); assert.equal(combat.timeline.pose.id, 262);
});

test('native knockdowns keep their POS down links and recover through original animation rather than instantly standing', () => {
  for (const [id, down, recover] of [[95, 113, 120], [98, 112, 119], [103, 112, 119]]) {
    const combat = new NativeCombatController(data, { weapon: 'sword' }), seen = new Set(); let downFrames = 0;
    assert.equal(combat.react(id), true);
    for (let frame = 0; frame < 300 && combat.reacting; frame++) {
      for (const state of combat.update(1 / 60, { grounded: true }).segments) seen.add(state.poseId);
      if (combat.reactionPhase === 'down') { downFrames++; assert.equal(combat.attack(), false); }
    }
    assert.ok(seen.has(id) && seen.has(down) && seen.has(recover), `${id}: missing native chain ${[...seen]}`);
    assert.ok(downFrames > 1, `${id}: authored prone frame needs a visible hold`);
    assert.equal(combat.reacting, false); assert.equal(combat.busy, false);
  }
});

test('airborne prone reactions wait for floor contact and repeated light hits do not snap a prone actor upright', () => {
  const combat = new NativeCombatController(data); combat.react(98);
  for (let frame = 0; frame < 180; frame++) combat.update(1 / 60, { grounded: false });
  assert.equal(combat.timeline.pose.id, 112); assert.equal(combat.reactionPhase, 'down');
  assert.equal(combat.react(90), false); assert.equal(combat.timeline.pose.id, 112);
  for (let frame = 0; frame < 180 && combat.reacting; frame++) combat.update(1 / 60, { grounded: true });
  assert.equal(combat.reacting, false); assert.equal(combat.timeline.pose.id, 119);
});

test('a real native sword hit visibly plays its authored target pose and locks ordinary AI movement and offense', async () => {
  const { game, hero, target } = await fixture(), beforeFacing = target.root.rotation.y;
  target.scriptControl = { paused: false, canAttack: true, attackTarget: hero, moveTarget: hero.root.position, attackRequested: true };
  target.aiTimer = 0;
  assert.equal(hit(game, hero, target, 262), true); assert.equal(target.hp, 10000 - game.totalDamage);
  assert.equal(target.combat.timeline.pose.id, 92, 'rear sword262 hit selects original TargetPoseBack'); assert.equal(target.combat.reacting, true);
  game._updateFighter(target, 1 / 60);
  assert.equal(target.combat.timeline.pose.id, 92, 'AI must not replace the hit animation with an attack or run');
  const pose = data.poses.get(92);
  assert.equal(target.character.source, pose.source); assert.ok(target.character.frame >= pose.start && target.character.frame <= pose.end);
  assert.equal(target.velocity.lengthSq(), 0, 'ordinary chase velocity must stop; source animation recoil may still move the actor');
  assert.equal(target.root.rotation.y, beforeFacing, 'AI must not turn toward its chase target during the hit animation');
  assert.ok(target.character.getAttachment('bau_Spine1'), 'the displayed frame uses the actual native skeleton');
});

test('three ordinary public attack inputs can hit and knock down a real native opponent on the source sword third strike', async () => {
  const { game, hero, target, events } = await fixture();
  game.action('attack');
  for (let frame = 0; frame < 180 && game.contactHits < 1; frame++) tick(game);
  assert.equal(game.contactHits, 1); game.action('attack');
  for (let frame = 0; frame < 180 && game.contactHits < 2; frame++) tick(game);
  assert.equal(game.contactHits, 2); assert.equal(hero.combat.timeline.pose.id, 263); game.action('attack');
  for (let frame = 0; frame < 240 && game.contactHits < 3; frame++) tick(game);
  const hits = events.filter(event => event.type === 'hit');
  assert.deepEqual(hits.map(event => event.poseId), [262, 263, 264]);
  assert.equal(hits[2].knockdown, true); assert.equal(target.combat.timeline.pose.id, hits[2].raw.selectedTargetPose);
  const down = target.combat.timeline.pose.link; assert.ok([112, 113].includes(down)); const recovery = down === 112 ? 119 : 120;
  assert.equal(target.combat.reacting, true); assert.equal(target.dead, false);
  assert.ok(target.hp > 0 && target.hp < target.maxHp, 'knockdown is not death');
  const seen = new Set(), downHeadHeights = [], recoveryHeadHeights = [];
  for (let frame = 0; frame < 240; frame++) {
    tick(game); const id = target.combat.timeline.pose.id; seen.add(id);
    const headHeight = target.character.getAttachment('bau_Head').getWorldPosition(v()).y - target.root.position.y;
    if (id === down) downHeadHeights.push(headHeight);
    if (id === recovery) recoveryHeadHeights.push(headHeight);
  }
  assert.ok(seen.has(down) && seen.has(recovery)); assert.equal(target.combat.reacting, false); assert.equal(target.combat.timeline.pose.id, 7);
  assert.ok(downHeadHeights.length > 1 && Math.max(...downHeadHeights) < .35, 'native head bone must visibly lie close to the ground during the prone hold');
  assert.ok(Math.max(...recoveryHeadHeights) - Math.min(...recoveryHeadHeights) > .8, 'original recovery frames must raise the body rather than snapping straight to stance');
  assert.ok(target.character.getAttachment('bau_Head').getWorldPosition(v()).y - target.root.position.y > 1.5, 'the actual native skeleton stands again after recovery');
  assert.equal(game.contactHits, 3, 'each source attack window damages once despite many render updates');
});

test('rapid public attack presses retain all three original sword strike windows before the third hit knocks down', async () => {
  const { game, target, events } = await fixture();
  for (let frame = 0; frame < 360 && game.contactHits < 3; frame++) {
    if (frame % 6 === 0) game.action('attack'); // normal J presses every 100 ms
    tick(game);
  }
  const hits = events.filter(event => event.type === 'hit');
  assert.deepEqual(hits.map(event => event.poseId), [262, 263, 264], 'early queued clicks must not discard the first two authored contacts');
  assert.equal(game.contactHits, 3); assert.equal(target.contacts, 3);
  assert.equal(hits[2].knockdown, true); assert.equal(target.combat.timeline.pose.id, hits[2].raw.selectedTargetPose); assert.equal(target.dead, false);
  assert.equal(target.maxHp - target.hp, hits.reduce((total, event) => total + event.amount, 0));
});

test('guarded contact does not turn a blocked blow into knockdown, while a lethal blow keeps death priority', async () => {
  const { game, hero, target } = await fixture();
  target.guard = true; hit(game, hero, target, 264);
  assert.equal(target.hp, 10000); assert.notEqual(target.combat.timeline.pose.id, 98);
  target.guard = false; target.hp = 1; hit(game, hero, target, 264);
  assert.equal(target.hp, 0); assert.equal(target.dead, true); assert.equal(target.combat.timeline.pose.id, 117);
  assert.equal(target.combat.reacting, false);
  assert.equal(hit(game, hero, target, 262), false); assert.equal(target.combat.timeline.pose.id, 117);
  assert.equal(game.kills, 1);
  game._placeFighter(target, { position: v(0, .015, 1.1) });
  assert.equal(target.dead, false); assert.equal(target.combat.reacting, false); assert.equal(target.combat.busy, false);
  assert.equal(target.combat.timeline.pose.id, 7); assert.equal(target.combat.attack(), true);
});

test('native hitstun cannot be cancelled by jumping; held defense engages on recovery without another input event', async () => {
  const { game, hero, target } = await fixture();
  hit(game, target, hero, 264);
  assert.equal(hero.combat.timeline.pose.id, 98);
  game.action('forward'); game.action('attack'); game.action('jump'); game.action('guard');
  game._updateFighter(hero, 1 / 60);
  assert.equal(hero.combat.timeline.pose.id, 98); assert.equal(hero.combat.queuedMove, null); assert.equal(hero.grounded, true);
  assert.equal(hero.velocity.lengthSq(), 0, 'held movement cannot cancel authored recoil'); assert.equal(hero.guard, false);
  game.action('forward', false);
  for (let frame = 0; frame < 240; frame++) { game.elapsed += 1 / 60; game._updateFighter(hero, 1 / 60); }
  assert.equal(hero.combat.reacting, false); assert.equal(hero.combat.timeline.pose.id, 16); assert.equal(hero.guard, true);
  game.action('guard', false); game._updateFighter(hero, 1 / 60); assert.equal(hero.combat.timeline.pose.id, 6);
  game.action('jump'); assert.equal(hero.grounded, false); assert.equal(hero.combat.timeline.pose.id, 151);
});

test('real impact feedback freezes only the contacting actors and consumes only its pause portion of the next update', async () => {
  const { game, hero, target } = await fixture(); game.impactFeedback = new NativeImpactFeedback(game.scene);
  const third = await game._createFighter(8, '无关对练角色'); game.enemies.push(third); game.scene.add(third.root);
  game._placeFighter(third, { position: v(20, .015, 0) }); third.scriptControlled = true; third.scriptControl = { paused: true };
  game.action('attack'); game._updateFighter(hero, .01); game._updateFighter(third, .01);
  hit(game, hero, target, 262);
  const stop = target.hitstop, attackerFrame = hero.combat.timeline.frame, victimFrame = target.combat.timeline.frame, thirdFrame = third.combat.timeline.frame;
  assert.ok(stop > 0 && stop <= .06); assert.equal(hero.hitstop, stop); assert.equal(game.impactFeedback.active.length, 1);
  const victimDisplayed = target.character.frame;
  game._updateFighter(hero, stop / 2); game._updateFighter(target, stop / 2); game._updateFighter(third, stop / 2);
  assert.equal(hero.combat.timeline.frame, attackerFrame); assert.equal(target.combat.timeline.frame, victimFrame);
  assert.equal(target.character.frame, victimDisplayed, 'the original first hit frame remains visible during the contact freeze');
  assert.ok(third.combat.timeline.frame > thirdFrame, 'a nearby unrelated actor must continue animating');
  assert.equal(game.running, true); assert.equal(game.paused, false);
  const remainingPause = target.hitstop;
  game._updateFighter(hero, remainingPause + .01); game._updateFighter(target, remainingPause + .01);
  assert.equal(hero.hitstop, 0); assert.equal(target.hitstop, 0);
  assert.ok(Math.abs(hero.combat.timeline.frame - attackerFrame - .3) < 1e-6);
  assert.equal(target.combat.timeline.frame, victimFrame, 'native hit timeline stays at Start during the .12s blend');
  assert.ok(Math.abs(target.combat.poseBlend.weight - .01 / NATIVE_DEFAULT_BLEND_TIME) < 1e-6, 'only the remaining 10ms advances the blend');
});

test('one defense press during hitstun survives repeated ordinary incoming hits after recovery and release still works', async () => {
  const { game, hero, target } = await fixture();
  hit(game, target, hero, 262); const hp = hero.hp;
  game.action('guard'); assert.equal(hero.guard, false);
  for (let frame=0; frame<120 && hero.combat.reacting; frame++) { game.elapsed += 1/60; game._updateFighter(hero,1/60); }
  assert.equal(hero.guard, true);
  for (let strike=0; strike<6; strike++) {
    hit(game, target, hero, 262);
    for (let frame=0; frame<25; frame++) { game.elapsed += 1/60; game._updateFighter(hero,1/60); }
    assert.equal(hero.hp,hp,'held guard must work without key-repeat after every block reaction');
  }
  game.action('guard',false); assert.equal(hero.guard,false);
  hit(game,target,hero,262); assert.ok(hero.hp<hp,'release restores normal incoming damage');
});

test('a near-recovery attack input starts only after hitstun and expires instead of replaying after a long knockdown', async () => {
  const { game, hero, target } = await fixture();
  hit(game,target,hero,262);
  for(let frame=0;frame<8;frame++){game.elapsed+=1/60;game._updateFighter(hero,1/60);}
  assert.equal(hero.combat.reacting,true); game.action('attack');
  assert.ok(game.recoveryAttack); assert.equal(hero.combat.timeline.pose.id,93);
  for(let frame=0;frame<90 && hero.combat.currentMove?.poseId!==262;frame++){game.elapsed+=1/60;game._updateFighter(hero,1/60);}
  assert.equal(hero.combat.currentMove?.poseId,262); assert.equal(game.recoveryAttack,null);
  hit(game,target,hero,264); game.action('attack');
  for(let frame=0;frame<240;frame++){game.elapsed+=1/60;game._updateFighter(hero,1/60);}
  assert.equal(game.recoveryAttack,null); assert.equal(hero.combat.currentMove,null); assert.equal(hero.combat.busy,false);
});

test('misses produce no contact freeze, guarded impact keeps HP and death interrupts an existing freeze immediately', async () => {
  const { game, hero, target } = await fixture(); game.impactFeedback = new NativeImpactFeedback(game.scene);
  game._placeFighter(target, { position: v(0, .015, 50) }); target.maxHp = target.hp = 10000;
  game.action('attack'); for (let frame = 0; frame < 120; frame++) tick(game);
  assert.equal(game.contactHits, 0); assert.equal(game.impactFeedback.active.length, 0); assert.equal(hero.hitstop || 0, 0); assert.equal(target.hitstop || 0, 0);
  game._placeFighter(target, { position: v(0, .015, 1.1) }); target.maxHp = target.hp = 10000; target.guard = true;
  hit(game, hero, target, 264);
  assert.equal(target.hp, 10000); assert.equal(target.combat.reactionPhase, 'guard'); assert.notEqual(target.combat.timeline.pose.id, 98);
  assert.ok(target.hitstop > 0 && target.hitstop <= .06);
  target.guard = false; target.hp = 1; hit(game, hero, target, 264);
  assert.equal(target.dead, true); assert.equal(target.hp, 0); assert.equal(target.hitstop, 0);
  assert.equal(target.combat.timeline.pose.id, 117); const deathFrame = target.combat.timeline.frame;
  game._updateFighter(target, .01);
  assert.ok(target.combat.timeline.frame > deathFrame, 'death must advance immediately rather than waiting for an obsolete contact freeze');
  assert.equal(target.combat.timeline.pose.id, 117);
});

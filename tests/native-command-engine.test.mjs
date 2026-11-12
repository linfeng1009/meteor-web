import {NATIVE_AIR_PHYSICS} from '../dist/native-traversal.js';
import test, { after } from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame, getNativeAttackAttachment } from '../dist/engine.js';
import { loadNativeCombat, createNativeDamageResolver, NATIVE_WEAPONS } from '../dist/native-combat.js';
import { NATIVE_MOVE_CATALOG } from '../dist/native-move-catalog.js';
import { NATIVE_WEAPON_MENU } from '../dist/native-weapon-menu.js';
import { createHash } from 'node:crypto';
import { loadNativeRageVfx } from '../dist/native-rage-vfx.js';
import {NetworkGame} from '../dist/network-game.js';
import {NetworkProjectileMotion} from '../dist/network-projectiles.js';

// Exercise production action(), native SKC/BNC/AMB, original GMC weapons,
// POS attack windows and recovered RES/EXE damage math. Only textures/audio,
// rendering and NPC retaliation are omitted. A plain test floor isolates the
// input/combat work from task navigation and is not claimed as original COB.
const dist = new URL('../dist/', import.meta.url);
const priorFetch = globalThis.fetch, priorTextureLoad = THREE.TextureLoader.prototype.load;
globalThis.fetch = async input => {
  try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); }
  catch { return new Response('', { status: 404 }); }
};
THREE.TextureLoader.prototype.load = function (url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
const combat = await loadNativeCombat();
const wm = JSON.parse(await readFile(new URL('assets/original/weapon-models/manifest.json', dist), 'utf8'));
const gripManifest = JSON.parse(await readFile(new URL('assets/original/rage-vfx/manifest.json', dist), 'utf8'));
const v = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
const fixtures = [];

after(() => {
  globalThis.fetch = priorFetch; THREE.TextureLoader.prototype.load = priorTextureLoad;
  for (const { game, floor } of fixtures) {
    game.rageVfx?.dispose(); game.projectiles?.dispose(); game.muskets?.dispose(); game.wheels?.dispose();
    for (const actor of [game.hero, ...game.enemies]) actor.character.dispose();
    for (const promise of game.weaponCache.values()) promise.then(model => model.traverse(node => {
      node.geometry?.dispose(); for (const material of Array.isArray(node.material) ? node.material : [node.material]) material?.dispose();
    }));
    floor.geometry.dispose(); floor.material.dispose();
  }
});

async function fixture(weapon = 'sword') {
  const game = Object.create(MeteorGame.prototype), events = [];
  const floor = new THREE.Mesh(new THREE.PlaneGeometry(200, 200), new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }));
  floor.rotation.x = -Math.PI / 2; floor.updateMatrixWorld(true);
  Object.assign(game, {
    combatData: combat, weaponManifest: wm,
    weaponItems: new Map(wm.items.map(item => [Number(item.itemId), item])),
    weaponModels: new Map(wm.models.map(model => [model.modelId.toLowerCase(), model])), weaponCache: new Map(),
    effectDefinitions: new Map(), waveFiles: new Map(), effects: [],
    scene: new THREE.Scene(), camera: new THREE.PerspectiveCamera(), raycaster: new THREE.Raycaster(),
    hostPhysics: { speed: 8, gravity: NATIVE_AIR_PHYSICS.gravity, jumpVelocity: NATIVE_AIR_PHYSICS.jumpVelocity, radius: .4, step: .55 },
    currentMap: { colliders: [floor], bounds: new THREE.Box3(v(-100, -1, -100), v(100, 30, 100)), metadata: {}, spawns: [{ position: v(0, .015, 0) }] },
    weapon, actorSerial: 0, enemies: [], keys: new Set(), directionBuffer: [], cameraAngle: 0,
    running: true, paused: false, mode: 'training', elapsed: 0, matchElapsed: 0,
    kills: 0, deaths: 0, totalDamage: 0, contactHits: 0,
    onEvent: event => events.push(event), onUpdate() {}, _nameplate() {}, _unlockAudio() {}, _soundDefinition() {}, _hud() {}
  });
  game.damageResolver = createNativeDamageResolver(combat); game._initializeProjectiles();
  game.hero = await game._createFighter(0, '孟星魂', true); game.scene.add(game.hero.root);
  game._placeFighter(game.hero, { position: v(0, .015, 0) }); await game._equip(game.hero, weapon);
  const target = await game._createFighter(8, '原版对练角色'); game.scene.add(target.root); game.enemies.push(target);
  game._placeFighter(target, { position: v(0, .015, 1.1) }); await game._equip(target, 'spear');
  target.maxHp = target.hp = 10000; target.team = 2; target.teamMask = 2; game.hero.team = 1; game.hero.teamMask = 1;
  game.locked = target;
  const result = { game, hero: game.hero, target, floor, events }; fixtures.push(result); return result;
}

function command(game, directions) {
  if(game.hero.weapon==='musket'&&game.hero.musketAim&&game.hero.combat.timeline?.pose.id===212&&!game.hero.combat.timeline.finished)for(let i=0;i<70;i++)tick(game);
  if(game.hero.weapon==='musket'&&!game.hero.musketAim){game.action('attack');for(let i=0;i<70;i++)tick(game);game.directionBuffer=[];}
  for (const direction of directions) {
    const key = { up: 'forward', down: 'back', left: 'left', right: 'right' }[direction];
    game.action(key, true); game.action(key, false); game.elapsed += .08;
  }
  game.action('attack', true); game.action('attack', false);
}
function tick(game, dt = 1 / 60) {
  game.elapsed += dt; game.matchElapsed += dt;
  game._updateFighter(game.hero, dt); game.projectiles.update(dt); game.wheels?.update(dt);
}

test('all twelve visible weapon choices equip their preserved original models without using E as a catalogue cycle', async () => {
  const html = await readFile(new URL('index.html',dist),'utf8');
  const choices = [...html.matchAll(/data-weapon="([^"]+)"/g)].map(m=>m[1]);
  assert.equal(choices.length,12); assert.equal(new Set(choices).size,12);
  assert.deepEqual(choices.sort(),Object.keys(NATIVE_WEAPONS).sort());
  assert.deepEqual(Object.keys(NATIVE_WEAPON_MENU).sort(),choices);
  const { game,hero } = await fixture(); const seen = new Set();
  for(let i=0;i<12;i++) {
    await game.setWeapon(Object.keys(NATIVE_WEAPONS)[i]);
    const profile=NATIVE_WEAPONS[hero.weapon]; seen.add(hero.weapon);
    assert.equal(hero.weaponId,profile.weaponId); assert.equal(hero.combat.timeline.pose.id,hero.combat.stance);
    const item=wm.items.find(item=>item.itemId===profile.weaponId);
    assert.equal(hero.weaponModels.length,item.modelIds.length);
    assert.ok(hero.weaponModels.every(model=>model.parent && model.getObjectByProperty('isMesh',true)));
  }
  assert.equal(seen.size,12); const equipped=hero.weapon;await game.switchWeapon();assert.equal(hero.weapon,equipped,'E cannot invent a secondary weapon');
});

test('qiankun public inputs switch all three source stances and retain distinct A attacks and automatic recovery', async () => {
  const {game,hero,target,events}=await fixture('qiankun');
  const settle=()=>{for(let f=0;f<600&&hero.combat.busy;f++)tick(game);game.directionBuffer=[];game.elapsed+=2;tick(game);};
  command(game,[]); assert.equal(hero.combat.timeline.pose.id,432); settle();
  command(game,['left']); assert.equal(hero.combat.weaponMode,'spear'); settle(); assert.equal(hero.combat.timeline.pose.id,402);
  command(game,[]); assert.equal(hero.combat.timeline.pose.id,442); settle();
  command(game,['down','down']); assert.equal(hero.combat.weaponMode,'sheath'); settle(); assert.equal(hero.combat.timeline.pose.id,403);
  command(game,[]); assert.equal(hero.combat.timeline.pose.id,520);
  while(!hero.combat.timeline.canCancel&&!hero.combat.timeline.finished)tick(game);
  command(game,[]);
  const seen=new Set();for(let f=0;f<600&&hero.combat.busy;f++){tick(game);seen.add(hero.combat.timeline.pose.id);}
  assert.ok(seen.has(521)&&seen.has(522)&&seen.has(524),'original sheath follow-up must play its attack and recovery links');
  settle(); command(game,['right']); assert.equal(hero.combat.weaponMode,'blade'); settle(); assert.equal(hero.combat.timeline.pose.id,401);
  assert.ok(target.hp<10000); assert.ok(events.some(e=>e.type==='hit'&&[432,442,520,522].includes(e.poseId)));
  assert.equal(hero.weaponId,47); assert.equal(hero.weaponModels.length,2);
});

function weaponPoint(model, nativePoint) {
  return v(...nativePoint).applyAxisAngle(v(1,0,0),-Math.PI/2).applyMatrix4(model.matrixWorld);
}
function checkSeatedBlade(hero) {
  const blade=hero.weaponModels.find(m=>/r$/i.test(m.name)),sheath=hero.weaponModels.find(m=>/l$/i.test(m.name));
  const bladeSockets=gripManifest.weaponAttachments[blade.name.toLowerCase()],sheathSockets=gripManifest.weaponAttachments[sheath.name.toLowerCase()];
  const tip=weaponPoint(blade,bladeSockets.d_wpnre.position),end=weaponPoint(sheath,sheathSockets.d_wpnls.position);
  const tube=sheath.children.find(c=>c.isMesh&&c.visible),box=new THREE.Box3().setFromObject(tube);
  assert.ok(tip.distanceTo(end)<1e-5,'the blade tip must finish at the original sheath tip');
  assert.ok(box.distanceToPoint(tip)<.02,'the blade tip must be inside visible sheath geometry');
  assert.ok(box.distanceToPoint(weaponPoint(blade,bladeSockets.d_wpnrs.position))<.02,'the blade edge must enter the sheath mouth');
  const mesh=blade.children.find(c=>c.isMesh&&c.visible),positions=mesh.geometry.attributes.position;
  let handle=0;for(let i=1;i<positions.count;i++)if(positions.getZ(i)<positions.getZ(handle))handle=i;
  const hilt=v().fromBufferAttribute(positions,handle).applyMatrix4(mesh.matrixWorld);
  assert.ok(box.distanceToPoint(hilt)>.15,'the handle stays outside the sheath');
  assert.ok(blade.visible&&mesh.visible,'seating must not be faked by hiding the whole knife');
}

test('客人飞镖飞轮复用对应原GMC变体，正确缩放并在退出时保留共享几何',async()=>{
 const {game,hero}=await fixture('dart');hero.networkId='guest';const motion=new NetworkProjectileMotion(game,new Map([['guest',hero]]));
 try{
  motion.receive([{kind:'dart',id:1,ownerId:'guest',weaponId:10,position:[1,2,3],quaternion:[0,0,0,1],spin:.5,phase:'outbound'},
   {kind:'wheel',id:1,ownerId:'guest',weaponId:11,position:[2,3,4],quaternion:[0,0,0,1],spin:1,phase:'return'}]);
  await Promise.all([...motion.samples.values()].map(s=>s.ready));
  for(const [key,name] of [['dart:1','w3_1'],['wheel:1','w6_1']]){
   const sample=motion.samples.get(key);assert.ok(sample.visual);assert.equal(sample.visual.name,name);assert.equal(sample.visual.scale.x,.08);
   const mesh=sample.visual.getObjectByProperty('isMesh',true);assert.ok(mesh.geometry.attributes.position.count>0);const template=(await game._prepareWeapon(sample.weaponId))[0].getObjectByProperty('isMesh',true);assert.equal(mesh.geometry,template.geometry);
  }
 }finally{motion.dispose();}
});

test('客人乾坤在通用跑步片段按权威形态收刀入鞘，切回刀枪形态时恢复持法',async()=>{
 const {game,hero,target}=await fixture('qiankun');hero.networkId='guest';target.networkId='host';
 const session=new NetworkGame(game,{host:false,playerId:'guest',send(){}},{players:[{id:'host'},{id:'guest'}]});session.active=true;
 try{
  const pose=combat.poses.get(144);let sequence=0;
  for(const mode of ['sheath','blade','spear','sheath']){
   const serial=++sequence;session.apply({sequence,time:sequence/15,players:[{id:'guest',position:[0,.015,0],angle:0,hp:1000,maxHp:1000,rage:0,grounded:true,dead:false,weaponId:hero.weaponId,weaponMode:mode,pose:144,source:pose.source,frame:pose.start+sequence,serial,effectTime:0}]});
   assert.equal(hero.combat.weaponMode,mode);assert.equal(hero.qiankunSheathWeight,mode==='sheath'?1:0);
   if(mode==='sheath')checkSeatedBlade(hero);
   assert.equal(hero.combat.timeline.pose.id,144);
  }
 }finally{session.dispose();}
});

test('首次火铳快照的瞄准标志不被装备初始化清除，异步模型加载不覆盖后续开火动作',async()=>{
 const {game,hero,target}=await fixture('sword');hero.networkId='guest';target.networkId='host';
 const session=new NetworkGame(game,{host:false,playerId:'guest',send(){}},{players:[{id:'host'},{id:'guest'}]});session.active=true;
 const equip=game._equip;let pending,count=0;game._equip=function(...args){count++;pending=equip.apply(this,args);return pending;};
 try{
  const ready=combat.poses.get(212),shot=combat.poses.get(206),packet={id:'guest',position:[0,.015,0],angle:.7,hp:1000,maxHp:1000,rage:0,grounded:true,dead:false,weaponId:3,weaponMode:'blade',musketAim:true,aimPitch:.3,pose:212,source:ready.source,frame:ready.end,serial:20,effectTime:0};
  session.apply({sequence:1,time:1,players:[packet]});assert.equal(hero.weapon,'musket');assert.equal(hero.musketAim,true);assert.equal(hero.combat.timeline.pose.id,212);assert.equal(game.cameraAngle,.7-Math.PI);
  session.apply({sequence:2,time:1.1,players:[{...packet,pose:206,source:shot.source,frame:shot.start+1,serial:21,context:{poseId:206}}]});
  assert.equal(hero.combat.timeline.pose.id,206);assert.equal(hero.musketAim,true);await pending;
  assert.equal(count,1);assert.equal(hero.combat.timeline.pose.id,206);assert.equal(hero.musketAim,true);assert.ok(hero.weaponModel);
 }finally{await pending;session.dispose();}
});

  test('qiankun keeps the raised grip and seats the visible blade inside all four original sheaths', async () => {
  const { game, hero } = await fixture('qiankun');
  const checkGrip = () => {
    for (const model of hero.weaponModels) {
      const hand = /l$/i.test(model.name) ? 'L' : 'R', palm = hero.character.getAttachment(`bau_${hand}_Hand`);
      const point = palm.getWorldPosition(v());
      assert.ok(model.visible && model.children.some(child => child.isMesh && child.visible && child.geometry.index.count > 0));
      const visible = model.children.find(child => child.isMesh && child.visible);
      if(hand==='L'||hero.qiankunSheathWeight<1e-6){
        assert.ok(model.getWorldPosition(v()).distanceTo(point)<.2,`${model.name}: drawn grip must follow the palm`);
        assert.ok(new THREE.Box3().setFromObject(visible).distanceToPoint(point)<.3,`${model.name}: held geometry must reach the hand`);
      }
    }
    if(hero.qiankunSheathWeight>1-1e-6)checkSeatedBlade(hero);
  };
  tick(game); checkGrip();
  const hand = hero.character.getAttachment('bau_R_Hand').getWorldPosition(v()), sourceControl = hero.character.getAttachment('d_wpnR').getWorldPosition(v());
  assert.ok(hand.y > 3, 'exercise the reported overhead stance');
  assert.ok(sourceControl.distanceTo(hand) > 1, 'the source waist/part control remains intact, separate from the visible grip');
  for (const keys of [['left'], ['down','down'], ['right']]) {
    command(game, keys);
    for (let frame = 0; frame < 600 && hero.combat.busy; frame++) { tick(game); checkGrip(); }
    tick(game); checkGrip();
  }
  assert.equal(hero.combat.weaponMode, 'blade');
  for (const itemId of [47,48,49,50]) {
    await game._equip(hero,itemId);tick(game);checkGrip();command(game,['down','down']);
    for(let n=0;n<600&&hero.combat.busy;n++){tick(game);checkGrip();}
    tick(game);assert.equal(hero.combat.timeline.pose.id,403);checkSeatedBlade(hero);
  }
  await game._equip(hero,'sword'); tick(game);
  assert.equal(hero.weaponModel.parent.name,'d_wpnR', 'ordinary weapon bindings keep their source behavior');
});

test('public down-down-A slides into the sheath from either stance, then a real draw attack returns it', async () => {
  for(const fromSpear of [false,true]){
    const {game,hero,events}=await fixture('qiankun');
    const finish=()=>{for(let n=0;n<600&&hero.combat.busy;n++)tick(game);for(let n=0;n<4;n++)tick(game);};
    if(fromSpear){command(game,['left']);finish();assert.equal(hero.combat.weaponMode,'spear');}
    command(game,['down','down']);assert.equal(hero.combat.currentMove.poseId,fromSpear?441:431);
    const weights=[],poses=new Set();
    for(let n=0;n<600&&hero.combat.busy;n++){tick(game);weights.push(hero.qiankunSheathWeight);poses.add(hero.combat.timeline.pose.id);}
    finish();assert.ok(weights.some(w=>w>0&&w<1),'the blade must visibly travel instead of snapping or vanishing');
    assert.ok(poses.has(485)&&poses.has(486));assert.equal(hero.combat.timeline.pose.id,403);checkSeatedBlade(hero);
    const blade=hero.weaponModels.find(m=>/r$/i.test(m.name)),oldBlade=blade;
    command(game,['down','up']);let drawn=false;
    for(let n=0;n<600&&hero.combat.busy;n++){tick(game);drawn ||= hero.qiankunSheathWeight<.01;}
    finish();assert.ok(drawn,'the next draw command must pull the blade out');
    assert.ok(events.some(e=>e.type==='move'&&e.poseId===449));checkSeatedBlade(hero);
    await game._equip(hero,'sword');const saved=oldBlade.matrix.clone();
    hero.character.setPoseFrame(0,combat.poses.get(401).start);assert.deepEqual(oldBlade.matrix.elements,saved.elements,'switching weapons unsubscribes the old pose binding');
  }
});

test('ninja ordinary foot and blade inputs cause real source contact, including its second A branch', async () => {
  const {game,hero,target,events}=await fixture('ninja');
  command(game,[]); assert.equal(hero.combat.timeline.pose.id,461);
  for(let f=0;f<180&&!hero.combat.timeline.canCancel;f++)tick(game);
  command(game,[]);
  for(let f=0;f<300&&hero.combat.busy;f++)tick(game);
  assert.ok(events.some(e=>e.type==='hit'&&e.poseId===461));
  assert.ok(events.some(e=>e.type==='move'&&e.poseId===462)); assert.ok(target.hp<10000);
});

test('wheel uses an original model in flight, hits through its release window, returns, and permits a second throw', async () => {
  const {game,hero,target,events}=await fixture('wheel'); command(game,[]);
  for(let f=0;f<90&&!game.wheels.size;f++)tick(game);
  assert.equal(game.wheels.size,1); assert.equal(hero.weaponModel.visible,false);
  const flight=game.wheels.active[0];assert.ok(flight.visual.getObjectByProperty('isMesh',true));
  for(let f=0;f<600&&(game.wheels.size||hero.combat.busy);f++)tick(game);
  tick(game);assert.equal(game.wheels.size,0);assert.equal(hero.weaponModel.visible,true);assert.equal(hero.combat.timeline.pose.id,3);
  const hits=events.filter(e=>e.type==='hit'&&e.poseId===218);assert.equal(hits.length,1);assert.ok(target.hp<10000);
  command(game,[]);for(let f=0;f<90&&!game.wheels.size;f++)tick(game);assert.equal(game.wheels.size,1);
});

test('actual musket input produces its source shot damage and cannot be replaced by a melee contact', async () => {
  const {game,hero,target,events}=await fixture('musket'); command(game,[]);
  for(let f=0;f<90&&hero.combat.busy;f++)tick(game);
  const hits=events.filter(e=>e.type==='hit'); assert.equal(hits.length,1);assert.equal(hits[0].poseId,206);assert.ok(hits[0].musketId);
  assert.equal(target.hp,9963);assert.equal(game.projectiles.size,0);
});

test('an unlocked free attack keeps its chosen facing even with a nearby opponent behind the player', async () => {
  const {game,hero,target}=await fixture('sword');
  hero.root.rotation.y=Math.PI; game.locked=null;
  command(game,[]); assert.equal(hero.combat.timeline.pose.id,262); assert.equal(hero.root.rotation.y,Math.PI);
  for(let f=0;f<120&&hero.combat.busy;f++)tick(game);
  assert.equal(target.hp,10000,'attacks aimed away must not silently turn and hit a rear opponent');
  game.locked=target;command(game,[]);assert.ok(Math.abs(hero.root.rotation.y)<1e-6,'explicit lock still aims at the selected target');
});

test('expansion weapon audio is registered as original byte copies, not merely unresolved EF names', async () => {
  const manifest=JSON.parse(await readFile(new URL('assets/original/manifest.json',dist),'utf8'));
  for(const prefix of ['w09','w10','w11'])for(const type of ['fir','grd','hit'])for(const n of ['01','02','03']) {
    const id=prefix+type+n,record=manifest.sounds.effects.find(r=>r.id===id);assert.ok(record,id);
    const bytes=await readFile(new URL('assets/original/'+record.url,dist));assert.equal(bytes.toString('ascii',0,4),'RIFF');
    const hash=createHash('sha256').update(bytes).digest('hex');assert.equal(hash,record.sha256);assert.equal(hash,record.source.sha256);
    assert.ok(manifest.assets.some(a=>a.url===record.url&&a.sha256===hash));
  }
});

test('ordinary directional key actions select each requested original skill without pose shortcuts', async () => {
  for (const [weapon, keys, pose] of [
    ['blade', ['left', 'right'], 374], ['sword', ['down', 'up', 'up'], 277],
    ['spear', ['left', 'right'], 290], ['spear', ['left', 'right', 'up'], 292]
  ]) {
    const { game, hero, events } = await fixture(weapon);
    command(game, keys);
    assert.equal(hero.combat.timeline.pose.id, pose, `${weapon} ${keys.join(' ')}`);
    assert.equal(hero.rage, 0, 'requested normal skills do not consume rage');
    assert.ok(events.some(event => event.type === 'move' && event.poseId === pose));
    assert.equal(game.directionBuffer.length, 0, 'accepted input is consumed');
    assert.ok(hero.weaponModel && hero.character.getAttachment('d_wpnR'), 'actual original weapon/hand attachment required');
  }
});

test('blade spin executes its original 374 to 375 automatic finish before returning to stance', async () => {
  const { game, hero } = await fixture('blade');
  command(game, ['left', 'right']);
  const seen = new Set();
  for (let frame = 0; frame < 480; frame++) {
    seen.add(hero.combat.timeline.pose.id); tick(game);
  }
  assert.ok(seen.has(374) && seen.has(375), `spin chain was interrupted: ${[...seen]}`);
  assert.equal(hero.combat.busy, false);
  assert.equal(hero.combat.timeline.pose.id, 8);
  assert.ok(game.totalDamage > 0, 'native spinning bones/weapon must remove real target HP');
});

test('sword multi-thrust resolves five original bone attack windows and actual damage', async () => {
  const damageByRate = [];
  for (const dt of [1 / 60, 1 / 10]) {
    const { game, hero, target, events } = await fixture('sword');
    command(game, ['down', 'up', 'up']);
    for (let time = 0; time < 6; time += dt) tick(game, dt);
    const hits = events.filter(event => event.type === 'hit' && event.poseId === 277);
    assert.equal(hits.length, 5, `five independent native windows expected at dt=${dt}; HP=${target.hp}, hit=${hits.length}, hero=${hero.root.position.toArray()}`);
    assert.ok(hits.every(event => event.amount > 0));
    assert.equal(target.maxHp - target.hp, hits.reduce((sum, event) => sum + event.amount, 0));
    assert.equal(game.contactHits, 5);
    assert.equal(game.totalDamage, target.maxHp - target.hp);
    damageByRate.push(game.totalDamage);
  }
  assert.equal(damageByRate[0], damageByRate[1], 'lower render rate must retain all authored thrusts');
});

test('jump then down-A selects native down attacks, with sword wind-up held through 342 descent and landing', async () => {
  for (const [weapon, pose] of [['dagger', 252], ['sword', 265], ['spear', 282], ['blade', 298]]) {
    const { game, hero, target, events } = await fixture(weapon);
    // No caller-supplied position/pose override: jump is the same public action
    // used by the keyboard, followed by ordinary back-key down/up and attack.
    game.action('jump');game.action('jump',false);
    // Enter on the ordinary descent, within reach of the standing target.
    // The native takeoff rises higher than the old fixed2.1m Web arc.
    for (let i = 0; i < 120 && !hero.grounded && (hero.vy >= 0 || hero.root.position.y > 3); i++) tick(game);
    assert.equal(hero.grounded, false);
    command(game, ['down']);
    assert.equal(hero.combat.timeline.pose.id, pose, `${weapon}: air down-A selected wrong move`);
    if (weapon === 'sword') {
      // The attackless wind-up already carries native downward movement.
      // It must move the collision root before the linked stab begins.
      let sawAuthoredDescent = false;
      for (let frame = 0; frame < 30 && hero.combat.timeline.pose.id === 265; frame++) {
        const timeline = hero.combat.timeline, before = hero.root.position.y;
        const a = hero.character.sampleSceneMotion(timeline.pose.source, timeline.frame);
        tick(game);
        if (hero.combat.timeline.pose.id !== 265) break;
        const b = hero.character.sampleSceneMotion(timeline.pose.source, timeline.frame);
        if (b.z - a.z < -1e-4) {
          assert.ok(hero.grounded?Math.abs(hero.root.position.y-.015)<1e-5:Math.abs(hero.root.position.y-before-(b.z-a.z)*.08)<1e-5);
          sawAuthoredDescent = true; break;
        }
      }
      assert.ok(sawAuthoredDescent, 'attackless sword wind-up must use its original downward track');
    }
    const seen = new Set(), busy = [];
    for (let frame = 0; frame < 240; frame++) {
      seen.add(hero.combat.timeline.pose.id); busy.push(hero.combat.busy); tick(game);
    }
    assert.ok(seen.has(pose));
    if (weapon === 'sword') {
      assert.ok(seen.has(342), `265 was interrupted before native descent: ${[...seen]}`);
      assert.equal(busy[0], true, 'wind-up without an attack block still owns the attack chain');
    }
    assert.equal(hero.grounded, true);
    assert.ok(Math.abs(hero.root.position.y - .015) < 1e-5);
    assert.equal(hero.combat.busy, false);
    const damagePose = weapon === 'sword' ? 342 : pose;
    const hits = events.filter(event => event.type === 'hit' && event.poseId === damagePose);
    assert.equal(hits.length, 1, `${weapon}: source down attack must actually contact the fixed target`);
    assert.ok(hits[0].amount > 0, `${weapon}: actual native damage required`);
    assert.equal(target.maxHp - target.hp, hits[0].amount);
    assert.equal(game.totalDamage, hits[0].amount);
    if (weapon === 'sword') assert.equal(events.some(event => event.type === 'hit' && event.poseId === 265), false,
      'the native wind-up has no attack; damage must come from the linked 342 stab');
  }
});

test('every listed ready command has a public-input route from the ground or a natural jump, while pending specials stay blocked', async () => {
  const byWeapon = new Map();
  for (const weapon of Object.keys(NATIVE_WEAPONS)) byWeapon.set(weapon, await fixture(weapon));
  const execute = (game, move) => {
    if (move.continuationOf?.length) {
      const from = NATIVE_MOVE_CATALOG.find(candidate => candidate.weapon === move.weapon && candidate.poseId === move.continuationOf[0]);
      assert.ok(from, `${move.id}: source command for prerequisite`);
      if (from.pending) { execute(game, from); return from; }
      execute(game, from);
      for (let frame = 0; frame < 180 && !game.hero.combat.timeline.canCancel && !game.hero.combat.timeline.finished; frame++) tick(game);
    }
    command(game, move.input.slice(0, -1));
    if (!move.pending && game.hero.combat.queuedMove?.poseId === move.poseId) {
      // A continuation can be accepted before its predecessor's first contact.
      // Wait for its real start before requesting a further prerequisite link.
      // This also checks that quick input no longer discards the authored hit.
      const predecessor = game.hero.combat.timeline.pose, firstStrike = predecessor.attacks[0];
      let sawSourceWindow = !firstStrike;
      for (let frame = 0; frame < 180 && game.hero.combat.timeline.pose.id !== move.poseId && game.hero.combat.queuedMove?.poseId === move.poseId; frame++) {
        sawSourceWindow ||= game.hero.combat.timeline.frame >= firstStrike.start && game.hero.combat.timeline.frame < firstStrike.end + 1;
        tick(game);
      }
      assert.ok(sawSourceWindow, `${move.id}: queued continuation must preserve its predecessor's original first strike`);
      assert.equal(game.hero.combat.timeline.pose.id, move.poseId, `${move.id}: accepted queue must actually start within 180 frames`);
    }
  };
  let ready = 0, pending = 0;
  for (const move of NATIVE_MOVE_CATALOG) {
    const { game, hero, target, events } = byWeapon.get(move.weapon);
    game.keys.clear(); game.directionBuffer = []; game.elapsed += 2; events.length = 0;
    game._placeFighter(hero, { position: v(0, .015, 0) });
    game._placeFighter(target, { position: v(0, .015, 1.1) }); target.maxHp = target.hp = 10000;
    hero.rage = 100;
    if (move.weapon === 'qiankun') {
      const desired = move.weaponMode || 'blade';
      if (hero.combat.weaponMode !== desired) {
        command(game, desired === 'blade' ? ['right'] : desired === 'spear' ? ['left'] : ['down', 'down']);
        for (let frame = 0; frame < 600 && hero.combat.busy; frame++) tick(game);
        assert.equal(hero.combat.weaponMode, desired); assert.equal(hero.combat.busy, false);
        game.directionBuffer = []; game.elapsed += 2;
      }
    }
    if (move.stance === 'air') {
      game.action('jump');game.action('jump',false); for (let frame = 0; frame < 12; frame++) tick(game);
    }
    const beforePose = hero.combat.timeline.pose.id;
    const blockedBy = execute(game, move);
    if (move.pending) {
      pending++; if(hero.combat.timeline.pose.id!==beforePose)assert.equal(hero.combat.currentMove?.kind,'dash',`${move.id}: directional input may start a standing dash, never a fallback attack`);
      assert.equal(hero.combat._attackChain,false,`${move.id}: blocked special cannot silently become a basic attack`);
      assert.equal(hero.rage, 100); assert.ok(events.some(event => event.text === (blockedBy?.pending || move.pending)));
    } else {
      ready++; assert.equal(hero.combat.currentMove?.poseId, move.poseId, `${move.id}: public direction inputs selected wrong source pose`);
      assert.equal(hero.combat.timeline.pose.id, move.poseId, `${move.id}: source animation must actually start`);
      assert.equal(hero.rage, 100 - move.rage - (move.continuationOf?.length ? NATIVE_MOVE_CATALOG.find(candidate=>candidate.weapon===move.weapon&&candidate.poseId===move.continuationOf[0]).rage : 0), `${move.id}: consume each prerequisite and command rage once on actual start`);
    }
  }
  assert.equal(ready, 197); assert.equal(pending, 0);
});

test('POS attack bone names resolve the actual original BNC bones without renaming the skeleton or inventing effect attachments', async () => {
  const { hero } = await fixture('spear');
  for (const [sourceName, originalName] of [['bad R Foot', 'bad_R_Foot'], ['bau Spine1', 'bau_Spine1'], ['bau R UpperArm', 'bau_R_UpperArm']]) {
    const bone = hero.character.getAttachment(originalName);
    assert.ok(bone, `missing original BNC bone ${originalName}`);
    assert.equal(getNativeAttackAttachment(hero.character, sourceName), bone);
    assert.equal(bone.name, originalName, 'normalization must not mutate original skeleton/bind names');
    assert.equal(getNativeAttackAttachment(hero.character, originalName), bone, 'exact lookups retain priority');
  }
  assert.equal(getNativeAttackAttachment(hero.character, 'd_wpnR'), hero.character.getAttachment('d_wpnR'));
  assert.ok(!getNativeAttackAttachment(hero.character, 'effect'), 'unrestored EF effects cannot be replaced by a skeleton bone');
});

test('the requested spear left-right-up-A body attack and airborne A kick remove actual HP through original bones', async () => {
  {
    const { game, hero, target, events } = await fixture('spear');
    command(game, ['left', 'right', 'up']);
    assert.equal(hero.combat.timeline.pose.id, 292);
    for (let frame = 0; frame < 240; frame++) tick(game);
    assert.equal(target.hp, 9923, 'native 292 body attack must inflict recovered 77 damage against the source defense-15 spear');
    assert.equal(game.totalDamage, 77);
    assert.ok(events.some(event => event.type === 'hit' && event.poseId === 292));
  }
  for (const weapon of ['spear', 'blade']) {
    const { game, hero, target, events } = await fixture(weapon);
    game.action('jump');game.action('jump',false);
    // Attack near landing on the ordinary descent, within reach of the target.
    // No hero/target position, authored pose or attachment is overridden.
    for (let frame = 0; frame < 120 && !hero.grounded && (hero.vy >= 0 || hero.root.position.y > .6); frame++) tick(game);
    assert.equal(hero.grounded, false);
    command(game, []); assert.equal(hero.combat.timeline.pose.id, 338);
    const samples = [];
    for (let frame = 0; frame < 120; frame++) {
      tick(game);
      if (hero.combat.timeline.pose.id === 338 && hero.combat.timeline.frame >= 9687 && hero.combat.timeline.frame <= 9689) {
        samples.push({ frame: hero.combat.timeline.frame, root: hero.root.position.toArray(), foot: hero.character.getAttachment('bad_R_Foot').getWorldPosition(v()).toArray(), target: target.root.position.toArray() });
      }
    }
    assert.ok(target.hp < 10000, `${weapon}: original airborne foot kick must damage the fixed target; ${JSON.stringify(samples)}`);
    assert.ok(events.some(event => event.type === 'hit' && event.poseId === 338));
    assert.equal(hero.grounded, true);
  }
});

test('native thrusts move the collision root using d_base, retaining the actual authored distance rather than pelvis sway', async () => {
  for (const dt of [1 / 60, 1 / 10]) {
    const { game, hero } = await fixture('sword'); game.enemies = []; game.locked = null; game.cameraAngle=Math.PI; // Match the actor's +Z forward facing before the double tap.
    const pose = hero.character.combatPoses.get(277), a = hero.character.sampleSceneMotion(pose.source, pose.start), b = hero.character.sampleSceneMotion(pose.source, pose.end);
    const start = hero.root.position.clone(); command(game, ['down', 'up', 'up']);
    for (let seconds = 0; seconds < 6; seconds += dt) tick(game, dt);
    assert.ok(Math.abs(hero.root.position.x - start.x - (b.x - a.x) * .08) < 1e-5);
    assert.ok(Math.abs(hero.root.position.z - start.z + (b.y - a.y) * .08) < 1e-5);
    assert.ok(hero.root.position.z - start.z > 5.9, 'original thrust advances almost 6 world units');
    assert.ok(Math.abs(hero.root.position.y - .015) < 1e-5);
    assert.ok(hero.character.getAttachment('d_base').getWorldPosition(v()).distanceTo(hero.root.position) < .01);
  }
});

test('authored thrust movement stops at the ordinary collision wall at both render rates', async () => {
  for (const dt of [1 / 60, 1 / 10]) {
    const { game, hero } = await fixture('sword'); game.enemies = []; game.locked = null; game.cameraAngle=Math.PI;
    const wall = new THREE.Mesh(new THREE.BoxGeometry(10, 4, .2), new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }));
    wall.position.set(0, 2, 3); wall.updateMatrixWorld(true); game.currentMap.colliders.push(wall);
    try {
      command(game, ['down', 'up', 'up']);
      for (let seconds = 0; seconds < 6; seconds += dt) tick(game, dt);
      assert.ok(hero.root.position.z > 1, 'native thrust should advance up to the obstruction');
      assert.ok(hero.root.position.z <= 2.5 + 1e-5, `dt=${dt}: authored movement must respect wall and actor radius`);
      assert.ok(Math.abs(hero.root.position.y - .015) < 1e-5);
      assert.equal(hero.combat.busy, false, 'collision must not leave the source attack stuck');
    } finally { wall.geometry.dispose(); wall.material.dispose(); }
  }
});

test('actual heavy-hit TargetMove scales the original recoil and TargetValue holds its authored final frame', async () => {
  const { game, hero, target } = await fixture('hammer');
  target.scriptControlled = true; target.scriptControl = { paused: true };
  const start = target.root.position.clone(), attackPose = hero.character.combatPoses.get(315), attack = attackPose.attacks[0];
  game._applyNativeHit(hero, target, { poseId: 315, pose: attackPose }, attack, target.root.position.clone());
  assert.equal(target.combat.timeline.pose.id, 94, 'attacker is behind the defender: original hammer315 TargetPoseBack');
  const hitPose = target.combat.timeline.pose, a = target.character.sampleSceneMotion(hitPose.source, hitPose.start), b = target.character.sampleSceneMotion(hitPose.source, hitPose.end);
  let elapsed = 0;
  while (target.combat.reacting && elapsed < 2) { game._updateFighter(target, 1 / 60); elapsed += 1 / 60; }
  assert.ok(elapsed >= .62 && elapsed < .7, `source .12 blend precedes TargetValue .5 hold, got ${elapsed}`);
  assert.ok(Math.abs(target.root.position.x - start.x - (b.x - a.x) * .08 * 10) < 1e-5);
  assert.ok(Math.abs(target.root.position.z - start.z + (b.y - a.y) * .08 * 10) < 1e-5);
  assert.ok(target.root.position.distanceTo(start) > 3.99);
});

test('a natural dagger jump can reach all three original air strikes through ordinary attack inputs without altitude overrides', async () => {
  const { game, hero } = await fixture('dagger'); game.enemies = []; game.locked = null;
  game.action('jump');game.action('jump',false); for (let frame = 0; frame < 12; frame++) tick(game);
  for (const id of [245, 246, 247]) {
    assert.equal(hero.grounded, false, `landed before requesting air ${id}`); game.action('attack');
    for (let frame = 0; frame < 180 && hero.combat.timeline.pose.id !== id; frame++) tick(game);
    assert.equal(hero.combat.timeline.pose.id, id, `air ${id} must really start`);
    const first = hero.combat.timeline.pose.attacks[0];
    for (let frame = 0; frame < 180 && hero.combat.timeline.pose.id === id && hero.combat.timeline.frame < first.end + 1; frame++) tick(game);
  }
});


test('paid spear rage commands emit original EF visuals through the real engine animation loop', async () => {
  for (const [keys, expected] of [[['up', 'up', 'up'], ['pos571']], [['left', 'right', 'down'], ['pos562', 'pos563']]]) {
    const { game, hero, events } = await fixture('spear');
    game.rageVfx = await loadNativeRageVfx(game.scene); hero.rage = 60;
    command(game, keys); const visible = new Set();
    for (let i = 0; i < 240; i++) {
      tick(game); game.rageVfx.update(1 / 60, game.camera);
      for (const effect of game.rageVfx.active) if (effect.nodes.some(node => node.mesh?.visible)) visible.add(effect.id);
    }
    for (const id of expected) assert.ok(visible.has(id), `real animation must render ${id}`);
    assert.equal(hero.rage, 0); assert.equal(events.filter(event => event.type === 'move' && event.rageCost === 60).length, 1);
    await game.setWeapon('sword'); assert.equal(game.rageVfx.active.length, 0);
  }
});

test('infinite rage supports repeated rage commands across weapons without filling NPC rage', async () => {
  for (const [weapon, keys, poseId] of [
    ['spear', ['up', 'up', 'up'], 571], ['sword', ['left', 'right'], 561],
    ['blade', ['down', 'down', 'up'], 565], ['hammer', ['left', 'right', 'up'], 566]
  ]) {
    const { game, hero, target, events } = await fixture(weapon);
    game.locked = null; target.root.position.set(0, .015, 80); target.rage = 23;
    game.setInfiniteRage(true);
    assert.equal(hero.rage, 100); assert.equal(target.rage, 23, 'debug rage is player-only');
    for (let cast = 0; cast < 2; cast++) {
      command(game, keys);
      assert.equal(hero.combat.currentMove?.poseId, poseId);
      assert.equal(hero.rage, 100, `${weapon}: starting a rage command must retain a full bar`);
      for (let frame = 0; frame < 1200 && hero.combat.busy; frame++) tick(game);
      assert.equal(hero.combat.busy, false, `${weapon}: original skill must finish before the next cast`);
      assert.equal(hero.rage, 100);
    }
    assert.equal(events.filter(event => event.type === 'move' && event.poseId === poseId).length, 2);
    assert.equal(target.rage, 23);
  }
});

test('infinite rage survives weapon changes and respawns, then disabling restores normal spending and resource gates', async () => {
  const { game, hero, target, events } = await fixture('spear');
  game.locked = null; target.root.position.set(0, .015, 80);
  game.setInfiniteRage(true);
  await game.setWeapon('sword'); assert.equal(hero.rage, 100);
  hero.rage = 0; game._placeFighter(hero, { position: v(0, .015, 0) });
  assert.equal(hero.rage, 100, 'a respawn or new match must start full while debug is enabled');
  game._placeFighter(target, { position: v(0, .015, 80) }); assert.equal(target.rage, 0);
  game.setInfiniteRage(false);
  command(game, ['left', 'right']); assert.equal(hero.combat.currentMove?.poseId, 561); assert.equal(hero.rage, 40);
  for (let frame = 0; frame < 1200 && hero.combat.busy; frame++) tick(game);
  command(game, ['left', 'right']);
  assert.ok(events.some(event => event.text?.includes('怒气不足'))); assert.equal(hero.rage, 40);
  game._placeFighter(hero, { position: v(0, .015, 0) }); assert.equal(hero.rage, 0);
});

test('Raiden sword skin preserves native melee damage and reuses its cached template after weapon changes', async () => {
  const { game, hero, target } = await fixture('sword');
  const template = game.raidenSwordTemplate; assert.ok(template && hero.raidenSword);
  const sourceModel = hero.weaponModel, damages = [];
  for (const style of ['original', 'raiden']) {
    game._placeFighter(hero, { position: v(0, .015, 0) });
    game._placeFighter(target, { position: v(0, .015, 1.1) }); target.maxHp = target.hp = 10000;
    game.setSwordStyle(style); game.action('attack');
    const serial = hero.combat.serial;
    for (let i = 0; i < 120; i++) tick(game);
    damages.push(target.maxHp - target.hp);
    assert.equal(hero.weaponModel, sourceModel); assert.equal(hero.combat.serial >= serial, true);
    assert.equal(hero.raidenSword.visible, style === 'raiden');
  }
  assert.ok(damages[0] > 0); assert.equal(damages[0], damages[1]);
  await game.setWeapon('spear'); assert.equal(hero.raidenSword, null);
  await game.setWeapon('sword'); assert.equal(game.raidenSwordTemplate, template);
  assert.equal(hero.raidenSword.children[0].geometry, template.children[0].geometry);
  assert.equal(hero.raidenSword.visible, true);
});

test('四种常用兵器的实际方向连招在连续点攻后仍按缓冲起手并产生原版攻击窗',async()=>{
 for(const weapon of ['sword','spear','blade','dagger']){
   const {game,hero,events}=await fixture(weapon),from=NATIVE_MOVE_CATALOG.find(m=>m.weapon===weapon&&m.input.length===1&&m.stance==='ground'&&!m.continuationOf);
   const directed=NATIVE_MOVE_CATALOG.find(m=>m.weapon===weapon&&!m.pending&&!m.rage&&m.stance==='ground'&&m.input.length>1&&!m.continuationOf&&combat.actions.resolveTransition(from.poseId,m.poseId)!=null);
   assert.ok(directed);command(game,[]);assert.equal(hero.combat.currentMove.poseId,from.poseId);command(game,directed.input.filter(k=>k!=='attack'));assert.equal(hero.combat.queuedMove?.id,directed.id);
   for(let i=0;i<5;i++)command(game,[]);assert.equal(hero.combat.queuedMove?.id,directed.id);
   const predecessorSerial=hero.combat.serial;for(let i=0;i<180&&hero.combat.serial===predecessorSerial;i++)tick(game);assert.equal(hero.combat.currentMove?.id,directed.id);assert.ok(events.some(e=>e.type==='move'&&e.moveId===directed.id));
   let windows=0;for(let i=0;i<180&&hero.combat.busy;i++){const state=hero.combat.update(1/120,{grounded:true});windows+=(state?.segments||[]).reduce((n,s)=>n+s.attacks.length,0);}assert.ok(windows>0,weapon+' retained original attack windows');
 }
});

test('实际连招换向时上一招命中采样保持旧朝向，结束后恢复新招朝向',async()=>{
 const {game,hero,target}=await fixture('sword');command(game,[]);command(game,[]);assert.ok(hero.combat.queuedMove);const serial=hero.combat.serial,queued=hero.combat._queuedRequest,start=queued.onStart;
 queued.onStart=context=>{target.root.position.set(3,.015,0);return start(context);};
 const samples=[],resolve=game._resolveContacts;game._resolveContacts=function(actor,state){samples.push({serial:state.serial,facing:state.facing,actual:actor.root.rotation.y});assert.ok(Math.abs(actor.root.rotation.y-state.facing)<1e-9);return resolve.call(this,actor,state);};
 for(let i=0;i<12&&!samples.some(s=>s.serial!==serial);i++)tick(game,.25);
 assert.ok(samples.some(s=>s.serial===serial),'previous strike is still sampled');assert.ok(samples.some(s=>s.serial!==serial),'next strike is also sampled');assert.ok(Math.abs(hero.root.rotation.y)>1,'final render keeps the new facing');
});

import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { NativeItemSystem, nativeMeatbunEffect, NATIVE_ITEM_PICKUP_PROFILE, nativeWorldItemEffect, updateNativeScriptItems, nativeMovementScale } from '../dist/native-items.js';
import { nativeEffectiveStat } from '../dist/native-combat.js';
import { MeteorGame } from '../dist/engine.js';
import { NativeMissionHost } from '../dist/native-mission-host.js';

const original = new URL('../dist/assets/original/', import.meta.url);
const res = JSON.parse(await readFile(new URL('characters/meteor-res-data.json', original), 'utf8'));
const itemRecords = new Map(res.allRecords.filter(record => record.type === 2).map(record => [record.id, record]));
const actor = (hp = 1000) => ({ hp, maxHp: 1500, root: new THREE.Group() });
function item(name = 'actual-item', model = '"Item01"') {
  return { name, source: { properties: { model } }, root: new THREE.Group(), attributes: { active: 1, interactive: 1, collision: 1 },
    setActive(value) { this.attributes.active = Number(value); this.root.visible = value; }, setCollision(value) { this.attributes.collision = Number(value); } };
}
function fixture(instances = [item()]) {
  const events = [], system = new NativeItemSystem({ itemRecords, getInstances: () => instances, onPickup: event => events.push(event) });
  return { system, instances, events };
}

test('only original type2 Item01 resolves the exact RES current-HP +300 record', () => {
  const effect = nativeMeatbunEffect(itemRecords.get(1));
  assert.equal(effect.name, '肉包'); assert.equal(effect.heal, 300); assert.equal(effect.valueOffset, 53204);
  for (const record of itemRecords.values()) if (record.id !== 1) assert.equal(nativeMeatbunEffect(record), null);
  assert.equal(nativeMeatbunEffect({ ...itemRecords.get(1), type: 1 }), null);
  assert.equal(nativeMeatbunEffect({ ...itemRecords.get(1), effects: [] }), null);
});

test('native HP gain clamps to max HP and the same scene instance cannot be consumed twice', () => {
  const { system, instances, events } = fixture(), hero = actor(1400);
  const result = system.tryPickup(hero); assert.equal(result.healed, 100); assert.equal(hero.hp, 1500); assert.equal(result.effectValue, 300);
  assert.deepEqual(instances[0].attributes, { active: 0, interactive: 0, collision: 0 }); assert.equal(instances[0].root.visible, false);
  hero.hp = 500; instances[0].attributes.active = instances[0].attributes.interactive = 1;
  assert.equal(system.tryPickup(hero).ok, false); assert.equal(hero.hp, 500); assert.equal(events.length, 1);
});

test('full HP keeps the meatbun with an explicit adapter policy; a subsequent wound can use it', () => {
  const { system, instances } = fixture(), hero = actor(1500);
  assert.equal(system.peek(hero).full, true); assert.equal(system.tryPickup(hero).reason, 'full-hp'); assert.equal(instances[0].attributes.active, 1);
  assert.match(NATIVE_ITEM_PICKUP_PROFILE.provenance.fullHp, /Browser adapter/);
  hero.hp = 1000; assert.equal(system.tryPickup(hero).healed, 300); assert.equal(hero.hp, 1300);
});

test('hidden, noninteractive, distant, vertically separate, blocked and dead-player pickups are rejected', () => {
  const { system, instances } = fixture(), hero = actor(), instance = instances[0];
  instance.attributes.active = 0; assert.equal(system.peek(hero), null);
  instance.attributes.active = 1; instance.attributes.interactive = 0; assert.equal(system.peek(hero), null);
  instance.attributes.interactive = 1; instance.root.position.x = 10; assert.equal(system.peek(hero), null);
  instance.root.position.set(0, 10, 0); assert.equal(system.peek(hero), null);
  instance.root.position.set(0, 0, 0); system.canReach = () => false; assert.equal(system.peek(hero), null);
  system.canReach = () => true; hero.dead = true; assert.equal(system.tryPickup(hero).ok, false);
  hero.dead = false; hero.hp = 0; assert.equal(system.peek(hero), null);
});

test('source model identity controls effects; names and arbitrary health-item models cannot grant meatbun healing', () => {
  const seven=item('肉包','"Item07"');seven.root.position.x=1;
  const { system } = fixture([item('Item01', '"Item02"'), seven, item('Item01', '')]);
  const hero=actor(),result=system.tryPickup(hero);assert.equal(result.ok,true);assert.equal(result.itemId,2);assert.equal(result.healed,0);assert.equal(hero.hp,1000);assert.equal(hero.maxHp,2000);
  const stealth=system.tryPickup(hero);assert.equal(stealth.ok,true);assert.equal(stealth.itemId,7);assert.equal(stealth.healed,0);assert.equal(hero.hp,1000);assert.equal(hero.scriptItems.at(-1).statKey,10);
});

test('ground pickups apply native attack, defense and movement modifiers even at full HP and expire',()=>{
  for(const [id,stat,value] of [[3,4,20],[4,3,25],[5,5,150]]){
    const {system}=fixture([item('world',itemRecords.get(id).model)]),hero=actor(1500),effect=nativeWorldItemEffect(itemRecords.get(id));
    const result=system.tryPickup(hero);assert.equal(result.ok,true);assert.equal(hero.hp,1500);assert.equal(result.healed,0);
    if(stat===5)assert.equal(nativeMovementScale(hero),1.49);else assert.equal(nativeEffectiveStat(stat,100,hero.activeItems),100+value);
    updateNativeScriptItems(hero,effect.duration+.2);assert.equal(hero.activeItems.length,0);
  }
});
test('rage and small/large meatbuns use their own values, clamp and preserve full-resource pickups',()=>{
  for(const [id,value] of [[16,500],[17,100]]){const {system}=fixture([item('bun',itemRecords.get(id).model)]),hero=actor(1400);assert.equal(system.tryPickup(hero).healed,Math.min(value,100));}
  const {system,instances}=fixture([item('rage','Item08')]),hero=actor(1500);hero.rage=100;
  assert.equal(system.tryPickup(hero).reason,'full-rage');assert.equal(instances[0].attributes.active,1);hero.rage=80;
  assert.equal(system.tryPickup(hero).rageGained,20);assert.equal(hero.rage,100);
});
test('world buff duplicate refreshes without stacking and source poison buns actually tick',()=>{
  const {system,instances}=fixture([item('first','Item04'),item('second','Item04')]),hero=actor();system.tryPickup(hero);updateNativeScriptItems(hero,10);
  assert.equal(system.tryPickup(hero).refreshed,true);assert.equal(hero.activeItems.length,1);assert.equal(hero.scriptItems[0].remaining,60);assert.ok(instances.every(x=>x.attributes.active===0));
  const poison=fixture([item('poison','Item0103')]);assert.equal(poison.system.tryPickup(hero).itemId,18);updateNativeScriptItems(hero,5.2);assert.equal(hero.hp,990);
});
test('unsupported effects stay unconsumed and full HP buns do not block a nearby usable buff',()=>{
  for(const id of [6,9,32,33,39])assert.equal(nativeWorldItemEffect(itemRecords.get(id)),null);
  const {system,instances}=fixture([item('bun','Item01'),item('buff','Item03')]),hero=actor(1500);instances[1].root.position.x=1;
  assert.equal(system.tryPickup(hero).itemId,3);assert.equal(instances[0].attributes.active,1);
  const changed=structuredClone(itemRecords.get(3));changed.effects[0].words[6]=999;assert.equal(nativeWorldItemEffect(changed),null);
});

test('nearest reachable original meatbun is selected, reset permits a source-reinitialized instance, disposal stops pickups', () => {
  const first = item('farther'), second = item('closer'); first.root.position.x = 1.4; second.root.position.x = .8;
  const { system } = fixture([first, second]), hero = actor(500);
  assert.equal(system.tryPickup(hero).objectName, 'closer'); assert.equal(hero.hp, 800);
  assert.equal(system.tryPickup(hero).objectName, 'farther'); assert.equal(hero.hp, 1100);
  second.attributes.active = second.attributes.interactive = 1; second.root.visible = true; system.reset();
  assert.equal(system.tryPickup(hero).objectName, 'closer'); assert.equal(hero.hp, 1400);
  system.dispose(); first.attributes.active = first.attributes.interactive = 1; assert.equal(system.peek(hero), null);
});

test('engine pickup reach ignores its own collider, rejects an intervening wall or another scene object, and restores ray distance', () => {
  const game = Object.create(MeteorGame.prototype), hero = actor(), meatbun = item();
  meatbun.root.position.x = 1.2;
  const material = new THREE.MeshBasicMaterial({ side: THREE.DoubleSide });
  const own = new THREE.Mesh(new THREE.BoxGeometry(.5, 1, .5), material); own.position.set(1.2, .5, 0); own.userData.nativeSceneInstance = meatbun; own.updateMatrixWorld(true);
  const blocker = new THREE.Mesh(new THREE.BoxGeometry(.1, 3, 3), material); blocker.position.set(.6, 1, 0); blocker.updateMatrixWorld(true);
  let dynamic = [own];
  Object.assign(game, { raycaster: new THREE.Raycaster(), currentMap: { colliders: [], props: { getCollidersNear: () => dynamic } } });
  try {
    assert.equal(game._canReachItem(hero, meatbun), true, 'the target meatbun geometry is not an intervening wall');
    game.currentMap.colliders.push(blocker); assert.equal(game._canReachItem(hero, meatbun), false);
    game.currentMap.colliders.length = 0; blocker.userData.nativeSceneInstance = item('other-object'); dynamic = [own, blocker];
    assert.equal(game._canReachItem(hero, meatbun), false, 'a different native scene instance must still block the reach ray');
    assert.equal(game.raycaster.far, Infinity);
  } finally { own.geometry.dispose(); blocker.geometry.dispose(); material.dispose(); }
});

test('engine-initialized pickup respects pause and works in training as well as story, with serializable HUD', async () => {
  const priorFetch = globalThis.fetch, dist = new URL('../dist/', import.meta.url);
  globalThis.fetch = async input => { try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); } catch { return new Response('', { status: 404 }); } };
  const hero = actor(1400), meatbun = item('D_itSt22'), events = [], updates = [], game = Object.create(MeteorGame.prototype);
  Object.assign(hero, { combat: { attacking: false }, character: { source: 0, frame: 0 }, rage: 0, weapon: 'dagger' });
  meatbun.root.position.x = 1;
  const map = { colliders: [], spawns: [{ position: new THREE.Vector3() }], props: { instances: new Map([[meatbun.name, meatbun]]), getCollidersNear: () => [] } };
  Object.assign(game, { scene: new THREE.Scene(), camera: new THREE.PerspectiveCamera(), cameraTarget: new THREE.Vector3(), raycaster: new THREE.Raycaster(),
    enemies: [], keys: new Set(), directionBuffer: [], mode: 'story', weapon: 'dagger', running: true, paused: false, kills: 0, deaths: 0, totalDamage: 0, contactHits: 0, matchElapsed: 0,
    onEvent: event => events.push(event), onUpdate: state => updates.push(state),
    _createFighter: async () => hero, _loadMap: async () => { game.currentMap = map; }, _placeFighter() {}, _equip: async () => {}, _tickCamera() {}, _unlockAudio() {} });
  try {
    // Keep the production initializer so the real item onPickup callback and
    // native-item construction are tested; omit unrelated render/actor setup.
    await game._initialize();
    const nearby = updates.at(-1).pickup; assert.equal(nearby.name, '肉包'); assert.equal(nearby.heal, 300); assert.equal(nearby.objectName, 'D_itSt22');
    assert.equal('instance' in nearby, false); assert.doesNotThrow(() => JSON.stringify(updates.at(-1)));
    game.paused = true; game.action('pickup'); assert.equal(hero.hp, 1400); assert.equal(meatbun.attributes.active, 1);
    game.paused = false; game.mode = 'training'; game.action('pickup'); assert.equal(hero.hp, 1500);
    game.mode = 'story'; game.action('pickup'); assert.equal(hero.hp, 1500); assert.equal(meatbun.attributes.active, 0);
    assert.equal(events.filter(event => event.type === 'pickup').length, 1); assert.match(events.find(event => event.type === 'pickup').text, /气血 \+100$/);
    assert.equal(updates.at(-1).pickup, null); assert.equal(updates.at(-1).hp, 1500); assert.doesNotThrow(() => JSON.stringify(updates.at(-1)));
    game.action('pickup'); assert.equal(events.filter(event => event.type === 'pickup').length, 1);
  } finally { game.items?.dispose(); globalThis.fetch = priorFetch; }
});

test('actual cave stone PST releases the actual DES Item01, heals once, and source init plus reset restores its hidden state', async () => {
  const priorFetch = globalThis.fetch, priorTexture = THREE.TextureLoader.prototype.load;
  globalThis.fetch = async input => { try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, new URL('../dist/', import.meta.url))), { status: 200 }); } catch { return new Response('', { status: 404 }); } };
  THREE.TextureLoader.prototype.load = function (url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
  let game, system;
  try {
    game = Object.create(MeteorGame.prototype);
    Object.assign(game, { manifest: JSON.parse(await readFile(new URL('manifest.json', original), 'utf8')), collisionMaterial: new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }), raycaster: new THREE.Raycaster(), onEvent() {}, _soundDefinition() {} });
    game.currentMap = await game._readMap('sn01'); game.missionHost = await NativeMissionHost.create(game);
    const host = game.missionHost; host.call(host.sceneVm, 'Scene_OnLoad'); host.call(host.sceneVm, 'Scene_OnInit');
    const meatbun = game.getSceneObject('D_itSt22'), hero = actor(1000); hero.root.position.copy(meatbun.root.position);
    system = new NativeItemSystem({ itemRecords, getInstances: () => game.currentMap.props.instances.values() });
    assert.equal(system.peek(hero), null); assert.equal(meatbun.source.properties.model, '"item01"');
    host.sceneItemAttack('D_St22', 0, 500);
    assert.equal(system.peek(hero).objectName, 'D_itSt22'); assert.equal(system.tryPickup(hero).healed, 300); assert.equal(hero.hp, 1300);
    assert.equal(system.tryPickup(hero).ok, false); assert.equal(host.getSceneItem('D_itSt22', 'attribute', 'active'), 0);
    host.call(host.sceneVm, 'Scene_OnInit'); system.reset(); assert.equal(system.peek(hero), null);
    assert.equal(host.sceneVm.getGlobal('g_iStoneHP')[21], 500); assert.equal(host.diagnostics.length, 0);
    host.sceneItemAttack('D_St22', 0, 500); assert.equal(system.tryPickup(hero).healed, 200); assert.equal(hero.hp, 1500);
    const huatuo=game.getSceneObject('D_itSt20');hero.root.position.copy(huatuo.root.position);host.sceneItemAttack('D_St20',0,500);
    assert.equal(huatuo.source.properties.model,'"item02"');const buff=system.tryPickup(hero);assert.equal(buff.itemId,2);assert.equal(hero.maxHp,2000);assert.equal(hero.hp,1500);assert.equal(buff.duration,600);
  } finally {
    system?.dispose(); game?.missionHost?.dispose(); if (game?.currentMap) game._disposeMap(game.currentMap);
    globalThis.fetch = priorFetch; THREE.TextureLoader.prototype.load = priorTexture;
  }
});

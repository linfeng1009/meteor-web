import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { NativeMissionHost } from '../dist/native-mission-host.js';
import { MeteorGame } from '../dist/engine.js';

const root = new URL('../dist/assets/original/', import.meta.url);
const manifest = JSON.parse(await readFile(new URL('manifest.json', root), 'utf8'));
const metadata = JSON.parse(await readFile(new URL('maps/sn01/metadata.json', root), 'utf8'));
const weaponManifest = JSON.parse(await readFile(new URL('weapon-models/manifest.json', root), 'utf8'));
const sources = new Map();
for (const script of manifest.scripts.filter(s => /\.(pst|h)$/i.test(s.source.path))) sources.set(script.source.path.toLowerCase(), await readFile(new URL(script.utf8, root), 'utf8'));
const world = p => new THREE.Vector3(p[0] * .08, p[2] * .08, -p[1] * .08);

test('航点连接避开隔墙近点，无法连通时不回退为穿墙直走',()=>{
  const wall=new THREE.Mesh(new THREE.BoxGeometry(.2,5,10),new THREE.MeshBasicMaterial({side:THREE.DoubleSide}));
  wall.position.set(0,2.5,0);wall.updateMatrixWorld(true);
  const host=Object.assign(Object.create(NativeMissionHost.prototype),{game:{},map:{colliders:[wall]},raycaster:new THREE.Raycaster()});
  const point=(id,x,z,links=[])=>({id,navigationPosition:new THREE.Vector3(x,0,z),size:10,links});
  const blocked=point(1,1,0),entry=point(2,-4,0,[{target:3,distance:3}]),goal=point(3,-4,3);
  host.points=new Map([[1,blocked],[2,entry],[3,goal]]);
  const actor={root:{position:new THREE.Vector3(-1,0,0)}};
  try{
    assert.equal(host.closestWaypoint(actor.root.position).id,1);
    assert.equal(host.closestWaypoint(actor.root.position,{visible:true}).id,2);
    assert.equal(host.moveViaWaypoint(actor,3),entry.navigationPosition);assert.deepEqual(actor.scriptPath.ids,[2,3]);
    actor.scriptPath={goal:3,ids:[3],cursor:1};actor.root.position.set(1,0,0);
    assert.equal(host.moveViaWaypoint(actor,3),null,'击退到隔墙区域后重新选路，不能复用已完成路径');
    assert.equal(host.closestWaypoint(actor.root.position,{visible:true}).id,1);
    actor.scriptPath=null;host.points=new Map([[2,entry],[3,goal]]);
    assert.equal(host.closestWaypoint(actor.root.position,{visible:true}),null);
    assert.equal(host.moveViaWaypoint(actor,3),null);
  }finally{wall.geometry.dispose();wall.material.dispose();}
});

test('航点连接缓存限制失败重搜，移动墙体仍立即失效已缓存的可见连接',()=>{
  const wall=new THREE.Mesh(new THREE.BoxGeometry(.2,5,10),new THREE.MeshBasicMaterial({side:THREE.DoubleSide}));
  wall.position.set(0,2.5,0);wall.updateMatrixWorld(true);
  const host=Object.assign(Object.create(NativeMissionHost.prototype),{game:{},map:{colliders:[wall]},raycaster:new THREE.Raycaster(),clock:0});
  const near={id:1,navigationPosition:new THREE.Vector3(1,0,0)},far={id:2,navigationPosition:new THREE.Vector3(-4,0,0)};
  host.points=new Map([[1,near],[2,far]]);const position=new THREE.Vector3(-1,0,0);
  const original=host.lineOfSight.bind(host);let calls=0;host.lineOfSight=(...args)=>{calls++;return original(...args);};
  try{
    assert.equal(host.closestWaypoint(position,{visible:true}),far);calls=0;
    assert.equal(host.closestWaypoint(position,{visible:true}),far);assert.equal(calls,1,'缓存命中只重查已选连接');
    wall.position.x=-2;wall.updateMatrixWorld(true);calls=0;
    assert.equal(host.closestWaypoint(position,{visible:true}),near);assert.ok(calls>=2,'新墙体遮住旧连接后立刻重新选点');
    host.points=new Map([[2,far]]);host.clock=.21;
    assert.equal(host.closestWaypoint(position,{visible:true}),null);calls=0;
    for(let i=0;i<60;i++)assert.equal(host.closestWaypoint(position,{visible:true}),null);
    assert.equal(calls,0,'固定位置的无解连接不逐帧重复扫描');
    host.clock=.42;host.closestWaypoint(position,{visible:true});assert.ok(calls>0);
  }finally{wall.geometry.dispose();wall.material.dispose();}
});

async function mission(options = {}) {
  const events = [], configurations = [], sceneObjects = new Map();
  const des = metadata.files.find(f => f.parsed?.format === 'DES').parsed;
  for (const object of des.objects) sceneObjects.set(object.name.toLowerCase(), {
    name: object.name, pose: 0, state: 3, attributes: { active: 1, collision: 1, interactive: 1 }
  });
  const hero = { id: 500, name: '孟星魂', root: new THREE.Group(), hp: 1000, maxHp: 1000, dead: false, team: 1 };
  const visibility = new Set();
  const game = {
    manifest, hero, enemies: [], paused: false,
    currentMap: { id: 'sn01', metadata, colliders: [], sceneObjects,
      points: metadata.waypoints.points.map(p => ({ ...p, native: p.position, position: world(p.position) })) },
    onEvent: event => events.push(event),
    getSceneObject: name => sceneObjects.get(String(name).toLowerCase()),
    playScenePose: (name, pose) => { const object = sceneObjects.get(name.toLowerCase()); if (object) { object.pose = pose; object.state = 3; } },
    setSceneActive: (name, active) => { sceneObjects.get(name.toLowerCase()).attributes.active = Number(active); },
    setSceneCollision: (name, enabled) => { sceneObjects.get(name.toLowerCase()).attributes.collision = Number(enabled); },
    // Only actor perception is mocked; this fixture has no map occluders,
    // so point-to-waypoint navigation connections remain clear.
    hasScriptLineOfSight: (actor,target) => actor.scriptId==null||target.scriptId==null||visibility.has(actor.scriptId),
    placeScriptPlayer: config => { game.playerConfig = config; hero.root.position.copy(config.spawn.position); },
    createScriptActor: async config => {
      if(options.beforeActor)await options.beforeActor(config);
      configurations.push(config);
      const actor = { id: 500 + config.scriptId, scriptId: config.scriptId, modelId: config.modelId,
        root: new THREE.Group(), hp: config.hp, maxHp: config.hp, team: config.team, dead: false,
        character: { dispose() {} } };
      actor.root.position.copy(config.spawn.position); game.enemies.push(actor); return actor;
    },
    _face: (actor, target) => { actor.lastFaceTarget = target.clone(); },
    _soundDefinition() {}, finishStory: result => { game.result = result; }
  };
  if (options.realEngine) {
    Object.setPrototypeOf(game, MeteorGame.prototype);
    delete game.createScriptActor; delete game.placeScriptPlayer;
    let actorSerial = 500;
    const actor = (modelId, name, hero = false) => {
      const root = new THREE.Group(), hand = new THREE.Group(); root.add(hand);
      return { id: ++actorSerial, modelId, name, hero, root, weapon: 'sword', velocity: new THREE.Vector3(),
        hp: 1000, maxHp: 1000, rage: 0, dead: false, attackHits: new Set(),
        character: { dispose() {}, getAttachment: () => hand, setPoseFrame() {} },
        combat: { play() {}, setWeapon() {}, update() { return null; } } };
    };
    Object.assign(game, { hero: actor(0, '孟星魂', true), mode: 'story', running: true,
      scene: new THREE.Scene(), weapon: 'sword', kills: 0, deaths: 0,
      _ground: (x, z) => {
        if (!options.waypointFloorOffset) return null;
        const nearest = game.currentMap.points.reduce((a, b) => Math.hypot(a.position.x - x, a.position.z - z) < Math.hypot(b.position.x - x, b.position.z - z) ? a : b);
        return { point: new THREE.Vector3(x, nearest.position.y - options.waypointFloorOffset, z) };
      },
      weaponCache: new Map(), combatData: { weaponRecords: new Map() },
      weaponItems: new Map(weaponManifest.items.map(item => [Number(item.itemId), item])),
      _createFighter: async (...args) => actor(...args), _disposeNameplate() {},
      _readWeapon: async modelId => { const model = new THREE.Group(); model.name = modelId; return model; }
    });
  }
  const host = await NativeMissionHost.create(game, { sources, ...options });
  if (options.autoStart !== false) await host.start();
  return { game, host, events, configurations, sceneObjects, visibility };
}

test('模型加载耗时不会重排原脚本的角色创建及初始化顺序',async()=>{
  const started=[];
  const {game,host,events}=await mission({beforeActor:async config=>{started.push(config.scriptId);if(config.scriptId===1)await new Promise(resolve=>setTimeout(resolve,25));}});
  assert.deepEqual(started,[1,2,3]);assert.deepEqual(game.enemies.map(actor=>actor.scriptId),[1,2,3]);
  assert.deepEqual(events.filter(event=>event.type==='mission-npc').map(event=>event.scriptId),[1,2,3]);
  assert.deepEqual([...host.npcVms.keys()],[1,2,3]);assert.equal(host.pending.size,0);
});

test('一个角色加载失败后，后续原脚本创建请求仍可执行',async()=>{
  const {game,host}=await mission(),create=game.createScriptActor;
  const source=host.npcScripts.get(1).replace(/^level\//,'').replace(/\.pst$/,'');
  game.createScriptActor=async config=>{if(config.scriptId===4)throw new Error('测试模型加载失败');return create(config);};
  assert.equal(host.addNpc(source),4);assert.equal(host.addNpc(source),5);
  const results=await Promise.allSettled([...host.pending]);await host.flushPending();
  assert.equal(results[0].status,'rejected');assert.equal(results[1].status,'fulfilled');
  assert.equal(host.actor(4),null);assert.ok(host.actor(5));assert.equal(host.pending.size,0);
  assert.ok(host.diagnostics.some(item=>item.code==='NPC_LOAD_FAILED'));
});

test('the real cave mission creates three distinct runtime NPCs with their original source configuration and waypoints', async () => {
  const { game, host, configurations, events } = await mission();
  assert.deepEqual(configurations.map(c => [c.scriptId, c.modelId, c.weaponId, c.spawnIndex, c.hp]), [
    [1, 8, 7, 53, 1000], [2, 8, 7, 80, 1000], [3, 8, 16, 32, 2000]
  ]);
  assert.deepEqual(configurations.map(c => c.name), ['铁枪哨兵﹒甲', '铁枪哨兵﹒乙', '军枪哨兵长']);
  for (const config of configurations) {
    assert.deepEqual(host.actor(config.scriptId).root.position.toArray(), world(metadata.waypoints.points[config.spawnIndex].position).toArray());
    assert.equal(host.npcVms.get(config.scriptId).getGlobal('g_self'), config.scriptId);
  }
  assert.equal(game.playerConfig.PlayerSpawn, 9);
  assert.equal(game.playerConfig.weaponId, 5);
  assert.equal(game.playerConfig.weapon2Id, 1);
  assert.equal(game.hero.hp, 1500);
  assert.deepEqual(game.hero.root.position.toArray(), world(metadata.waypoints.points[9].position).toArray());
  assert.equal(host.natives().GetChar('军枪哨兵长'), 3);
  assert.equal(host.levelVm.getGlobal('trg0'), 1);
  assert.ok(events.some(e => e.type === 'dialogue' && e.speaker === '军枪哨兵长' && e.text.startsWith('你们都听到萧老大说的了')));
  assert.ok(host.compatibilityUsed.some(c => c.from === 'Perofrm' && c.to === 'Perform'));
  assert.equal(host.diagnostics.length, 0);
});

test('source loading preserves the native browser fetch receiver', async () => {
  let requests = 0;
  const fetcher = async function (url) {
    assert.equal(this, globalThis, 'native Window.fetch must not receive a mission host as this');
    requests++;
    const text = await readFile(url, 'utf8');
    return { ok: true, text: async () => text };
  };
  const { host } = await mission({ sources: null, fetcher });
  assert.ok(requests >= 9, 'load the level, scene, includes and NPC source files');
  assert.equal(host.actors.size, 4);
  assert.equal(host.diagnostics.length, 0);
});

test('the real engine mission bridges preserve source HP, distinct actor IDs and original weapon variants', async () => {
  const { game, host } = await mission({ realEngine: true });
  assert.deepEqual(game.enemies.map(actor => [actor.scriptId, actor.modelId, actor.weaponId, actor.hp]), [
    [1, 8, 7, 1000], [2, 8, 7, 1000], [3, 8, 16, 2000]
  ]);
  assert.equal(new Set(game.enemies.map(actor => actor.id)).size, 3);
  assert.equal(game.enemies.every(actor => actor.id !== actor.modelId), true);
  assert.deepEqual(game.enemies.map(actor => actor.weaponModel.name), ['w7_0', 'w7_0', 'w7_1']);
  assert.equal(game.hero.weaponModel.name, 'w1_0');
  assert.equal(game.hero.weapon2Id, 1);
  assert.equal(game.hero.root.rotation.y, Math.PI / 2);
  for (const actor of game.enemies) {
    assert.deepEqual(actor.root.position.toArray(), host.points.get(actor.spawnIndex).position.toArray());
    assert.equal(actor.root.parent, game.scene);
  }
  const victim = host.actor(1); victim.hp = 0; game._kill(victim);
  game._updateFighter(victim, 120);
  assert.equal(victim.dead, true, 'story NPCs must not return as training respawns');
  assert.equal(victim.hp, 0);
  assert.equal(victim.respawn, Infinity);
});

test('the patrol routes and generated movement targets come from the original WP graph', async () => {
  const { host } = await mission();
  assert.deepEqual(host.actor(1).scriptIntent.waypointIds, [0, 1, 4, 2, 3]);
  assert.deepEqual(host.actor(2).scriptIntent.waypointIds, [18, 19, 75, 55, 79, 38, 77, 78, 14, 20]);
  assert.equal(host.actor(3).scriptIntent.mode, 'wait');
  assert.ok([...host.points.values()].some(point => point.position === host.actor(1).scriptControl.moveTarget));
  const route = host.route(53, 0);
  assert.equal(route[0], 53); assert.equal(route.at(-1), 0);
  for (let i = 1; i < route.length; i++) assert.ok(host.points.get(route[i - 1]).links.some(link => link.target === route[i]));
});

test('source waypoints above the collision floor do not trap foot-positioned engine actors', async () => {
  const { host } = await mission({ realEngine: true, waypointFloorOffset: 2.8 });
  const guard = host.actor(1), spawn = host.points.get(53);
  assert.equal(spawn.position.y, metadata.waypoints.points[53].position[2] * .08, 'retain the exact original WP53 coordinate');
  assert.ok(Math.abs(spawn.navigationPosition.y - .015) < 1e-10, 'movement uses the collision floor');
  assert.deepEqual(guard.root.position.toArray(), spawn.navigationPosition.toArray());
  host.moveViaWaypoint(guard, 0);
  assert.ok(guard.scriptPath.cursor > 0, 'advance past a waypoint already reached at foot height');
  guard.root.position.copy(host.points.get(0).navigationPosition);
  host.updateControls();
  assert.equal(guard.scriptIntent.cursor, 1, 'the original patrol advances when the floor target is reached');
});

test('script perception respects original View distance and collision visibility', async () => {
  const { game, host, visibility } = await mission();
  const guard = host.actor(1);
  guard.root.rotation.y = Math.PI / 2;
  visibility.add(1);
  game.hero.root.position.copy(guard.root.position).add(new THREE.Vector3(31.9, 0, 0));
  assert.equal(host.visibleEnemy(guard), game.hero);
  game.hero.root.position.copy(guard.root.position).add(new THREE.Vector3(32.1, 0, 0));
  assert.equal(host.visibleEnemy(guard), null);
  game.hero.root.position.copy(guard.root.position).add(new THREE.Vector3(1, 0, 0));
  visibility.clear(); assert.equal(host.visibleEnemy(guard), null);
});

test('native wait begins pursuit only after discovery, while idle and behavior reset keep their source meaning', async () => {
  const { game, host, visibility } = await mission(), guard = host.actor(1);
  host.changeBehavior(1, 'wait'); guard.root.rotation.y = Math.PI / 2;
  game.hero.root.position.copy(guard.root.position).add(new THREE.Vector3(20, 0, 0));
  host.updateControls(); assert.equal(guard.scriptControl.moveTarget, null); assert.equal(guard.scriptControl.canAttack, false);
  visibility.add(1); host.updateControls();
  assert.equal(guard.scriptControl.moveTarget, game.hero.root.position); assert.equal(guard.scriptControl.attackTarget, game.hero);
  assert.equal(guard.scriptControl.canAttack, true); assert.equal(guard.awarenessTarget, game.hero);
  host.changeBehavior(1, 'idle'); assert.equal(guard.awarenessTarget, null);
  host.updateControls(); assert.equal(guard.scriptControl.moveTarget, null); assert.equal(guard.scriptControl.canAttack, false);
  visibility.clear(); host.changeBehavior(1, 'wait'); host.updateControls();
  assert.equal(guard.scriptControl.moveTarget, null); assert.equal(guard.scriptControl.attackTarget, null);
});

test('the original guard discovery, loss, retreat and report dialogue execute through PST state transitions', async () => {
  const { game, host, events, visibility } = await mission();
  const guard = host.actor(1), leader = host.actor(3);
  game.hero.root.position.copy(guard.root.position).add(new THREE.Vector3(1, 0, 0)); visibility.add(1);
  host.update(.06);
  assert.equal(host.levelVm.getGlobal('trg1'), 1);
  assert.equal(guard.scriptPerform.action, 'guard');
  host.update(3.01);
  assert.ok(events.some(e => e.type === 'dialogue' && e.text.includes('竟敢擅自闯入禁地')));
  visibility.clear(); game.hero.root.position.copy(guard.root.position).add(new THREE.Vector3(17, 0, 0)); host.update(.06);
  assert.equal(host.levelVm.getGlobal('trg1'), 2);
  assert.ok(events.some(e => e.type === 'dialogue' && e.text === '奇怪？人跑到那了？？？'));
  // Both sentries must be outside the source Report() threshold. The initial
  // source spawns are close enough to let the same OnUpdate report immediately.
  const distantWaypoint = [...host.points.values()].find(point => point.position.distanceTo(leader.root.position) > 12);
  guard.root.position.copy(distantWaypoint.position);
  host.actor(2).root.position.copy(distantWaypoint.position);
  game.hero.root.position.copy(guard.root.position).add(new THREE.Vector3(1, 0, 0));
  visibility.add(1); host.update(.06);
  assert.equal(host.levelVm.getGlobal('trg3'), 1);
  assert.equal(guard.scriptIntent.mode, 'attacktarget');
  guard.root.position.copy(leader.root.position).add(new THREE.Vector3(1, 0, 0));
  host.update(.06);
  assert.equal(host.levelVm.getGlobal('trg3'), 2);
  assert.equal(leader.scriptIntent.mode, 'follow');
  assert.equal(leader.scriptIntent.targetId, 0);
  host.update(4.01);
  assert.ok(events.some(e => e.type === 'dialogue' && e.text === '报告哨兵长！发现入侵者！！'));
  assert.ok(events.some(e => e.type === 'dialogue' && e.text === '在那？所有人跟我来！'));
  assert.equal(host.diagnostics.length, 0);
});

test('original scene item damage callbacks change real registered object collision and item activation', async () => {
  const { host, sceneObjects } = await mission();
  assert.equal(host.sceneVm.getGlobal('g_iStoneHP')[0], 500);
  // This actual DES contains items for stones 20..32; it has no D_itSt01.
  assert.equal(sceneObjects.has('d_itst01'), false);
  assert.equal(host.sceneItemAttack('D_St20', 0, 500), true);
  assert.equal(host.sceneVm.getGlobal('g_iStoneHP')[19], 0);
  assert.equal(sceneObjects.get('d_st20').attributes.collision, 0);
  assert.equal(sceneObjects.get('d_itst20').attributes.active, 1);
  host.sceneItemIdle('D_St20');
  assert.equal(host.sceneVm.getGlobal('g_bStoneAlive')[19], 0);
});

test('mission completion uses all original hostile NPCs and retains its explicit Rule-10 inference', async () => {
  const { game, host } = await mission({ completionDelay: .1 });
  host.actor(1).hp = 0; host.actor(1).dead = true; host.update(.06);
  assert.equal(game.result, undefined);
  for (const id of [2, 3]) { host.actor(id).hp = 0; host.actor(id).dead = true; }
  host.update(.06); host.update(.11);
  assert.equal(game.result.win, true);
  assert.match(game.result.provenance, /inference/);
  assert.equal(game.result.reason, 'hostile-npcs-defeated');
});

test('the source HP thresholds trigger a sentry retreat and the original leader death line', async () => {
  const { host, events } = await mission();
  const leader = host.actor(3), guard = host.actor(1);
  const distantWaypoint = [...host.points.values()].find(point => point.position.distanceTo(leader.root.position) > 12);
  for (const id of [1, 2]) host.actor(id).root.position.copy(distantWaypoint.position);
  guard.hp = guard.maxHp / 4; host.update(.06);
  assert.equal(host.levelVm.getGlobal('trg4'), 1);
  assert.equal(guard.scriptIntent.mode, 'attacktarget');
  assert.ok(events.some(event => event.type === 'dialogue' && event.text === '可恶！你给我等着！'));
  leader.hp = leader.maxHp / 2 - 1; host.update(.06);
  assert.equal(host.levelVm.getGlobal('trg6'), 1);
  leader.hp = 0; leader.dead = true; host.update(.06);
  assert.equal(host.levelVm.getGlobal('trg6'), 2);
  assert.ok(events.some(event => event.type === 'dialogue' && event.text.startsWith('呜﹒﹒﹒你别以为')));
  assert.equal(host.diagnostics.length, 0);
});

test('unsupported host APIs are explicit and a disposed host stops script execution', async () => {
  const { host, game } = await mission();
  assert.throws(() => host.natives().Misc('unsupported'), error => error.code === 'UNKNOWN_NATIVE');
  const before = host.clock; host.dispose(); host.update(1);
  assert.equal(host.clock, before);
  assert.equal(game.enemies.some(actor => actor.scriptControlled), false);
});

test('leaving while player equipment loads does not start an abandoned source mission', async () => {
  const { host, game, configurations } = await mission({ autoStart: false });
  let finishLoad;
  game.placeScriptPlayer = () => new Promise(resolve => { finishLoad = resolve; });
  const starting = host.start(); host.dispose(); finishLoad(); await starting;
  assert.equal(host.started, false);
  assert.equal(configurations.length, 0);
  assert.equal(game.enemies.length, 0);
});

test('late original NPC loads are removed after the source mission is disposed', async () => {
  const { host, game, events } = await mission({ autoStart: false });
  const originalCreate = game.createScriptActor, loaded = [];
  let finishLoad, allEntered;
  const gate = new Promise(resolve => { finishLoad = resolve; });
  const entered = new Promise(resolve => { allEntered = resolve; });
  game.createScriptActor = async config => {
    const actor = await originalCreate(config); loaded.push(actor);
    if (loaded.length === 1) allEntered();
    await gate; return actor;
  };
  const starting = host.start(); await entered; host.dispose(); finishLoad(); await starting;
  assert.equal(game.enemies.length, 0);
  assert.equal(loaded.length,1,'未开始的排队加载在离开剧情后取消');
  assert.equal(loaded.every(actor => actor.disposed), true);
  assert.equal(events.some(event => event.type === 'mission-npc'), false);
});

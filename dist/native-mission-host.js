import * as THREE from './vendor/three.module.js';
import { NativeScriptVM, NativeScriptError, parsePst, normalizePstPath, createPstIncludeResolver } from './native-script.js';
import { getNativeMission } from './native-missions.js';
import { clearNativeScriptItems, NATIVE_SCRIPT_ITEM_PROVENANCE } from './native-items.js';
import { validNativeWeatherSetting, NATIVE_WEATHER_PROVENANCE } from './native-weather.js';
import { findNativeEnemy, NATIVE_AWARENESS } from './native-awareness.js';
import { NATIVE_NPC_COMBAT_PROVENANCE } from './native-npc-combat.js';

const ORIGINAL_ROOT = new URL('./assets/original/', import.meta.url);
const SCALE = .08;
const position = point => new THREE.Vector3(point[0] * SCALE, point[2] * SCALE, -point[1] * SCALE);
const plain = value => typeof value === 'string' ? value.replace(/^"|"$/g, '') : value;
const alive = actor => !!actor && !actor.dead && !actor.disposed && !actor.scriptRemoved && actor.hp > 0;

// This bridges original PST callbacks to the browser engine. Script order, NPC
// configuration, dialogue, waypoints and object callbacks come from source files.
// Adapter timing, perception and the Rule-10 completion fallback are identified
// in provenance; unsupported API commands never silently claim success.
export class NativeMissionHost {
  static async create(game, options = {}) {
    const host = new NativeMissionHost(game, options); await host.initialize(); return host;
  }
  constructor(game, { mapId = game.currentMap?.id, sources = null, fetcher = globalThis.fetch,
    compatibility = true, onEvent = null, scriptCadence = .05, completionDelay = 1.2, random = Math.random } = {}) {
    this.game = game; this.mapId = mapId; this.manifest = game.manifest;
    // Window.fetch requires Window as its receiver in some browsers. Keep that
    // receiver when storing the native function on this host (or injecting it).
    this.fetcher = (...args) => Reflect.apply(fetcher, globalThis, args);
    this.onEvent = onEvent || (event => game.onEvent?.(event)); this.compatibility = compatibility;
    this.sourceCache = new Map(sources instanceof Map ? [...sources].map(([f, s]) => [normalizePstPath(f), s]) : Object.entries(sources || {}).map(([f, s]) => [normalizePstPath(f), s]));
    this.sourceIndex = new Map((this.manifest.scripts || []).map(record => [normalizePstPath(record.source.path), record]));
    this.sourcePromises = new Map(); this.programCache = new Map(); this.actors = new Map(); this.npcVms = new Map();
    this.sceneItems = new Map(); this.sceneNames = new Map(); this.targets = new Map(); this.pending = new Set();
    this.nextScriptId = 1; this.clock = 0; this.accumulator = 0; this.idleAccumulator = 0;
    this.random = random; this.randomSeries = new Map();
    this.vipName = mapId === 'sn15' ? '萧安' : null;
    this.mission = getNativeMission(mapId);
    this.scriptCadence = scriptCadence; this.completionDelay = completionDelay; this.started = false; this.disposed = false;
    this.disabledCallbacks = new Set(); this.diagnosticKeys = new Set(); this.diagnostics = []; this.stdout = []; this.dialogues = [];
    this.compatibilityUsed = []; this.nativeCallCount = 0; this.npcScripts = new Map(); this.completionAt = null;
    this.raycaster = new THREE.Raycaster();
    this.provenance = {
      scripts: 'Original Level/*.pst, scene PST and PScriptLib includes; source bytes preserved.',
      configuration: 'NPC Model/Weapon/Team/View/Spawn/HP and player Spawn/HP/Weapon read from original globals.',
      navigation: 'Original Level/*.wp positions and links; browser Dijkstra projects waypoints onto collision floors, and requests original takeoff when a nearby goal is elevated and NPC Jump>0. Original navigation/decision timing remains unverified.',
      perception: `${NATIVE_AWARENESS.provenance} Native units×0.08; eye points, collision rays and nearest selection are Web adapters. Full AI decisions/timing remain unverified.`,
      timing: 'PST pause/guard numeric durations are treated as seconds; dialogue display duration is a browser reading aid.',
      performAttack: 'NPC Perform attack is a browser single-attack intent, kept until the normal engine target/range/line-of-sight checks accept an attack. Original exact Perform timing remains unverified; PlayerPerform attack remains unsupported.',
      rule10: 'All hostile mission NPCs defeated => success is a Rule-10 adapter inference; no GameOver call exists in sn01_.pst or sn14_.pst.',
      sceneClock: 'Misc gettime is integer milliseconds from the host clock, matching sn09 Def.h step1000; native exact clock scheduling remains unverified.',
      randomSeries: 'Original sn09 four inclusive floor rings are shuffled without repetition using Web Fisher-Yates; original PRNG sequence remains unverified.',
      vip: 'sn15 vip symbol resolves to source named 萧安. Defeating him completes Rule4 after the host delay; this is an explicit objective adapter, not a recovered EXE Rule4 implementation.',
      timeout: 'Story RoundTime minutes impose a host timeout fallback; native exact timeout event ordering remains unverified.'
    };
    this.provenance.scriptItems = NATIVE_SCRIPT_ITEM_PROVENANCE;
    this.provenance.combatDecisions = NATIVE_NPC_COMBAT_PROVENANCE;
    this.provenance.weather = NATIVE_WEATHER_PROVENANCE;
    this.sceneSettings = {};
  }
  emit(event) { this.onEvent(event); }
  diagnostic(code, message, detail = {}) {
    const key = `${code}:${detail.file || ''}:${detail.api || ''}:${message}`;
    if (this.diagnosticKeys.has(key)) return;
    this.diagnosticKeys.add(key); const event = { type: 'mission-diagnostic', code, text: message, ...detail };
    this.diagnostics.push(event); this.emit(event); this.publishState();
  }
  unsupported(api, args, context) {
    this.diagnostic('UNSUPPORTED_NATIVE', `原脚本 API 尚未接入：${api}`, { api, arguments: args, file: context?.location?.file });
    throw new NativeScriptError(`Mission host does not implement ${api}`, context?.location, 'UNKNOWN_NATIVE');
  }
  async readSource(file) {
    file = normalizePstPath(file);
    if (this.sourceCache.has(file)) return this.sourceCache.get(file);
    if (!this.sourcePromises.has(file)) this.sourcePromises.set(file, (async () => {
      const record = this.sourceIndex.get(file);
      if (!record) throw new Error(`Original PST source ${file} is not in the imported manifest`);
      const response = await this.fetcher(new URL(record.utf8, ORIGINAL_ROOT));
      if (!response.ok) throw new Error(`Original PST ${file}: ${response.status}`);
      const source = await response.text(); this.sourceCache.set(file, source); return source;
    })());
    return this.sourcePromises.get(file);
  }
  async prepare(file, ancestry = []) {
    file = normalizePstPath(file);
    if (ancestry.includes(file)) throw new Error(`PST include cycle ${[...ancestry, file].join(' -> ')}`);
    if (this.programCache.has(file)) return this.programCache.get(file);
    const program = parsePst(await this.readSource(file), { file });
    for (const node of program.body) if (node.type === 'Include') await this.prepare(normalizePstPath(node.name, file), [...ancestry, file]);
    this.programCache.set(file, program); return program;
  }
  async makeVm(file, actorId = null) {
    file = normalizePstPath(file); const program = await this.prepare(file);
    const vm = new NativeScriptVM({ natives: this.natives(), onEvent: event => {
      if (event.type === 'native-call') this.nativeCallCount++;
      else if (event.type === 'unknown-native') this.diagnostic('UNKNOWN_NATIVE', `原脚本调用未实现的 ${event.name}`, { api: event.name, file: event.location?.file, location: event.location });
    } }).load(program, { file, resolveInclude: createPstIncludeResolver(this.sourceCache) });
    vm.contextFile = file; vm.contextActorId = actorId; return vm;
  }
  call(vm, name, args = [], fatal = false) {
    if (!vm?.hasFunction(name)) return undefined;
    const key = `${vm.contextFile}:${name}`; if (this.disabledCallbacks.has(key)) return undefined;
    try { return vm.call(name, args); }
    catch (error) {
      this.diagnostic(error.code || 'SCRIPT_ERROR', error.message, { file: vm.contextFile, callback: name });
      this.disabledCallbacks.add(key); if (fatal) throw error; return undefined;
    }
  }
  async initialize() {
    const map = this.game.currentMap;
    if (!map || map.id !== this.mapId) throw new Error('Mission host requires its actual original map to be loaded first');
    this.map = map; this.points = new Map((map.points || map.metadata.waypoints?.points || []).map(point => [point.id, {
      ...point, position: point.position?.isVector3 ? point.position.clone() : position(point.position)
    }]));
    for (const point of this.points.values()) {
      const floor = this.game._ground?.(point.position.x, point.position.z, point.position.y + 3);
      point.navigationPosition = floor ? new THREE.Vector3(point.position.x, floor.point.y + .015, point.position.z) : point.position;
    }
    const des = map.metadata.files.find(file => file.parsed?.format === 'DES')?.parsed;
    for (const [index, object] of (des?.objects || []).entries()) {
      const instance = this.game.getSceneObject?.(object.name) || map.sceneObjects?.get(object.name.toLowerCase()) || null;
      const record = { id: index + 1, name: object.name, source: object, instance, pose: instance?.pose ?? 0, state: instance?.state ?? 0,
        attributes: instance?.attributes || { active: 1, collision: object.properties.blockplayer === 'no' ? 0 : 1, interactive: 0 },
        scriptClass: plain(object.properties.name || ''), position: position(object.position || [0, 0, 0]) };
      this.sceneItems.set(record.id, record); this.sceneNames.set(object.name.toLowerCase(), record);
    }
    this.levelVm = await this.makeVm(`level/${this.mapId}_.pst`);
    this.sceneVm = await this.makeVm(`${this.mapId}/${this.mapId}.pst`);
    this.level = this.levelVm.snapshot(); this.rule = this.level.Rule; this.roundTime = this.level.RoundTime;
    return this;
  }
  async start() {
    if (this.started || this.disposed) return this;
    const hero = this.game.hero;
    if (!hero) throw new Error('Mission player is absent');
    hero.scriptId = 0; hero.scriptControlled = false; hero.team = this.level.PlayerTeam ?? 1;
    hero.maxHp = hero.hp = this.level.PlayerHP ?? 1000; hero.hpSourceVerified = true;
    hero.scriptConfig = { ...this.level, sourceFile: `Level/${this.mapId}_.pst`, scriptId: 0 };
    hero.weaponId = this.level.PlayerWeapon; hero.weapon2Id = this.level.PlayerWeapon2;
    const playerSpawn = this.points.get(this.level.PlayerSpawn);
    if (!playerSpawn) throw new Error(`Original player waypoint ${this.level.PlayerSpawn} is absent`);
    if (this.game.placeScriptPlayer) await this.game.placeScriptPlayer({ ...hero.scriptConfig, spawn: playerSpawn, hp: hero.maxHp, weaponId: hero.weaponId, weapon2Id: hero.weapon2Id });
    else {
      this.game._placeFighter?.(hero, { name: `WP${playerSpawn.id}`, position: playerSpawn.position });
      hero.maxHp = hero.hp = this.level.PlayerHP ?? 1000;
    }
    if (this.disposed) return this;
    this.actors.set(0, hero); this.started = true;
    this.call(this.sceneVm, 'Scene_OnLoad', [], true); this.call(this.sceneVm, 'Scene_OnInit', [], true);
    this.call(this.levelVm, 'OnInit', [0], true); this.call(this.levelVm, 'OnStart', [], true);
    await this.flushPending();
    if (this.disposed) return this;
    this.call(this.levelVm, 'OnUpdate'); this.processPerformances(0); this.updateControls(); this.publishState();
    return this;
  }
  async flushPending() { while (this.pending.size) await Promise.all([...this.pending]); }
  addNpc(script) {
    const file = normalizePstPath(`level/${String(script).replace(/\.pst$/i, '')}.pst`), scriptId = this.nextScriptId++;
    const task = this.instantiateNpc(file, scriptId).catch(error => {
      if (!this.disposed) this.diagnostic('NPC_LOAD_FAILED', `原角色载入失败：${script}`, { file, message: error.message });
      throw error;
    }); this.pending.add(task);
    task.finally(() => this.pending.delete(task)).catch(() => {}); return scriptId;
  }
  async instantiateNpc(file, scriptId) {
    const vm = await this.makeVm(file, scriptId); if (this.disposed) return;
    const raw = vm.snapshot(), spawn = this.points.get(raw.Spawn);
    if (!spawn) throw new Error(`${file}: original NPC Spawn waypoint ${raw.Spawn} is absent`);
    const config = { scriptId, sourceFile: file, name: raw.Name, modelId: raw.Model, weaponId: raw.Weapon,
      weapon2Id: raw.Weapon2, team: raw.Team, hp: raw.HP, spawn, spawnIndex: raw.Spawn,
      nativeGlobals: raw, view: raw.View, think: raw.Think };
    if (typeof this.game.createScriptActor !== 'function') throw new Error('Engine createScriptActor bridge is absent');
    let actor;
    try { actor = await this.game.createScriptActor(config); }
    catch (error) { if (this.disposed) return; throw error; }
    if (this.disposed) {
      if (this.game.removeScriptActor) this.game.removeScriptActor(actor);
      else {
        actor.disposed = true; this.game._disposeNameplate?.(actor); actor.character?.dispose(); actor.root?.removeFromParent();
        this.game.enemies = this.game.enemies?.filter(existing => existing !== actor) || [];
      }
      return;
    }
    Object.assign(actor, { scriptId, name: raw.Name, modelId: raw.Model, weaponId: raw.Weapon, weapon2Id: raw.Weapon2,
      team: raw.Team, hp: raw.HP, maxHp: raw.HP, hpSourceVerified: true, scriptControlled: true, scriptConfig: raw,
      scriptIntent: { mode: 'wait', waypointIds: [], cursor: 0, targetId: null, source: file },
      scriptQueue: [], scriptPerform: null, scriptAttackRequested: false, missionVm: vm });
    this.actors.set(scriptId, actor); this.npcVms.set(scriptId, vm); this.npcScripts.set(scriptId, file);
    if (Array.isArray(this.game.enemies) && !this.game.enemies.includes(actor)) this.game.enemies.push(actor);
    this.call(vm, 'OnInit', [scriptId], true); this.call(vm, 'OnStart', [], true);
    this.emit({ type: 'mission-npc', scriptId, name: raw.Name, config, source: file }); return actor;
  }
  actor(id, includeDead = true) { const actor = this.actors.get(Number(id)); return actor && !actor.scriptRemoved && !actor.disposed && (includeDead || alive(actor)) ? actor : null; }
  findActor(name, includeDead = false) {
    if (name === 'vip' && this.vipName) name = this.vipName;
    if (name === 'player') return includeDead || alive(this.actors.get(0)) ? this.actors.get(0) : null;
    return [...this.actors.values()].find(actor => actor.name === name && !actor.scriptRemoved && !actor.disposed && (includeDead || alive(actor))) || null;
  }
  sceneItem(id) { return typeof id === 'string' ? this.sceneNames.get(id.toLowerCase()) || null : this.sceneItems.get(Number(id)) || null; }
  getSceneItem(id, field, ...args) {
    const item = this.sceneItem(id); if (!item) return -1;
    const instance = this.game.getSceneObject?.(item.name) || item.instance;
    if (field === 'index') return item.id;
    if (field === 'pose') return instance?.pose ?? item.pose;
    if (field === 'state') return instance?.state ?? item.state;
    if (field === 'attribute') return (instance?.attributes || item.attributes)[args[0]] ?? 0;
    if (field === 'name') return item.scriptClass;
    return this.unsupported(`GetSceneItem:${field}`, [id, ...args]);
  }
  setSceneItem(id, field, ...args) {
    const item = this.sceneItem(id); if (!item) return 0;
    const instance = this.game.getSceneObject?.(item.name) || item.instance;
    if (field === 'name') { item.scriptClass = args[0]; return 1; }
    if (field === 'pose') {
      item.pose = Number(args[0]); if (instance) instance.pose = item.pose;
      this.game.playScenePose?.(item.name, item.pose, !!args[1]); return 1;
    }
    if (field === 'attribute') {
      const [attribute, value] = args; item.attributes[attribute] = value;
      if (instance) instance.attributes = Object.assign(instance.attributes || {}, { [attribute]: value });
      if (attribute === 'active') this.game.setSceneActive?.(item.name, !!value);
      else if (attribute === 'collision') this.game.setSceneCollision?.(item.name, !!value);
      this.emit({ type: 'scene-property', objectName: item.name, attribute, value }); return 1;
    }
    return this.unsupported(`SetSceneItem:${field}`, [id, ...args]);
  }
  sceneItemAttack(id, attackerId, damage) {
    const item = this.sceneItem(id); if (!item) return false;
    if (!Number.isFinite(damage) || damage < 0) throw new Error('Scene damage must be supplied by the engine damage resolver');
    const callback = `${item.name}_OnAttack`; if (!this.sceneVm.hasFunction(callback)) return false;
    this.call(this.sceneVm, callback, [item.id, attackerId, Math.trunc(damage)]); return true;
  }
  sceneItemIdle(id) {
    const item = this.sceneItem(id); if (!item) return false;
    const callback = `${item.name}_OnIdle`; if (!this.sceneVm.hasFunction(callback)) return false;
    this.call(this.sceneVm, callback, [item.id]); return true;
  }
  visibleEnemy(actor) {
    return findNativeEnemy(actor, [...this.actors.values()], (observer, target) => this.lineOfSight(observer, target));
  }
  lineOfSight(actor, target) {
    if (this.game.hasScriptLineOfSight) return this.game.hasScriptLineOfSight(actor, target);
    const from = actor.root.position.clone().add(new THREE.Vector3(0, 1.35, 0));
    const to = target.root.position.clone().add(new THREE.Vector3(0, 1.35, 0)), ray = to.sub(from), distance = ray.length();
    if (distance < .5) return true;
    this.raycaster.set(from, ray.normalize()); this.raycaster.far = Math.max(0, distance - .35);
    return !this.raycaster.intersectObjects(this.map.colliders || [], false).some(hit => hit.distance > .25);
  }
  changeBehavior(id, mode, ...args) {
    const actor = this.actor(id, false); if (!actor) return 0;
    if (!['idle', 'wait', 'patrol', 'follow', 'attacktarget', 'aggress', 'run', 'kill'].includes(mode)) return this.unsupported(`ChangeBehavior:${mode}`, [id, ...args]);
    const ref = args[0], symbolic = typeof ref === 'string' && !/^[-+]?\d+$/.test(ref);
    actor.scriptIntent = { mode, waypointIds: mode === 'patrol' ? args.map(Number) : [], cursor: 0,
      targetId: ['follow', 'kill'].includes(mode) ? symbolic ? this.findActor(ref)?.scriptId ?? -1 : Number(ref) : null,
      targetRef: ['follow', 'kill'].includes(mode) ? args[0] : null,
      targetSlot: mode === 'attacktarget' ? Number(args[0]) : null,
      target: mode === 'attacktarget' && this.targets.has(Number(args[0])) ? { ...this.targets.get(Number(args[0])) } : null,
      source: this.npcScripts.get(actor.scriptId) };
    actor.awarenessTarget = null; actor.npcCombat?.reset(); actor.scriptPath = null; return 1;
  }
  enqueue(id, action, ...args) {
    const actor = this.actor(id, false); if (!actor) return 0;
    actor.scriptQueue ||= []; actor.scriptQueue.push({ action: String(action).trim(), args }); return 1;
  }
  dialogue(id, text) {
    const actor = this.actor(id), content = String(text), duration = Math.max(2.4, Math.min(8, content.length * .13));
    const event = { type: 'dialogue', scriptId: Number(id), speaker: actor?.name || (Number(id) === 0 ? '孟星魂' : '原角色'), text: content, duration,
      source: this.npcScripts.get(Number(id)) || this.levelVm.contextFile };
    this.dialogues.push(event); if (this.dialogues.length > 1000) this.dialogues.shift(); this.emit(event); return 1;
  }
  processPerformances(dt) {
    for (const actor of this.actors.values()) {
      if (!alive(actor)) { actor.scriptQueue = []; actor.scriptPerform = null; actor.scriptAttackRequested = false; continue; }
      if (actor.scriptPerform) {
        actor.scriptPerform.remaining -= dt;
        if (actor.scriptPerform.remaining > 0) continue;
        actor.scriptPerform = null; actor.guard = false;
      }
      let count = 0;
      while (actor.scriptQueue?.length && count++ < 64) {
        const { action, args } = actor.scriptQueue.shift();
        if (action === 'say') this.dialogue(actor.scriptId, args[0]);
        else if (action === 'faceto') { const target = this.actor(args[0]); if (target) this.game._face?.(actor, target.root.position, 1); }
        else if (action === 'pause' || action === 'guard') {
          actor.scriptPerform = { action, mode: action, remaining: Math.max(0, Number(args[0]) || 0) }; actor.guard = action === 'guard';
          if (actor.scriptPerform.remaining > 0) break; actor.scriptPerform = null;
        } else if (action === 'aggress') { actor.scriptAggressive = true; }
        else if (action === 'attack' && actor.scriptId !== 0) { actor.scriptAggressive = true; actor.scriptAttackRequested = true; }
        else if (action === 'crouch') { actor.scriptCrouched = Number(args[0]) === 0; }
        else if (action === 'use') {
          const itemId = Number(args[0]);
          const applied = this.game.useScriptItem?.(actor, itemId);
          if (!applied) this.diagnostic('UNSUPPORTED_ITEM_EFFECT', `原物品效果尚未接入：${itemId}`, { api: 'Perform:use', itemId, scriptId: actor.scriptId });
        }
        else if (action === 'block' && actor.scriptId === 0) { actor.scriptInputBlocked = Number(args[0]) === 0; }
        else if (this.compatibility && this.mapId === 'sn15' && args.length === 0 && ['﹒﹒﹒无名﹒﹒﹒', '﹒﹒﹒﹒﹒﹒'].includes(action)) {
          // Two original sn15 ally lines omit the "say" argument. Keep the
          // source intact and record this narrow, visible compatibility map.
          if (!this.compatibilityUsed.some(entry => entry.from === 'Perform:missing-say')) {
            const entry = { from: 'Perform:missing-say', to: 'Perform:say', file: this.levelVm.contextFile };
            this.compatibilityUsed.push(entry); this.emit({ type: 'mission-compatibility', text: '原脚本对白兼容：补齐两处缺失的 say', ...entry });
          }
          this.dialogue(actor.scriptId, action);
        }
        else {
          this.diagnostic('UNSUPPORTED_PERFORM', `原角色动作尚未接入：${action}`, { api: 'Perform', arguments: args, scriptId: actor.scriptId });
        }
      }
    }
  }
  closestWaypoint(point) {
    let nearest = null, distance = Infinity;
    for (const waypoint of this.points.values()) { const current = waypoint.navigationPosition.distanceToSquared(point); if (current < distance) { nearest = waypoint; distance = current; } }
    return nearest;
  }
  route(fromId, toId) {
    if (!this.points.has(fromId) || !this.points.has(toId)) return [];
    const distances = new Map([[fromId, 0]]), previous = new Map(), open = new Set([fromId]);
    while (open.size) {
      const current = [...open].reduce((a, b) => distances.get(a) < distances.get(b) ? a : b); open.delete(current);
      if (current === toId) break;
      for (const link of this.points.get(current).links || []) {
        if (!this.points.has(link.target)) continue;
        const candidate = distances.get(current) + link.distance;
        if (candidate < (distances.get(link.target) ?? Infinity)) { distances.set(link.target, candidate); previous.set(link.target, current); open.add(link.target); }
      }
    }
    if (!distances.has(toId)) return [];
    const result = [toId]; while (result[0] !== fromId) result.unshift(previous.get(result[0])); return result;
  }
  moveViaWaypoint(actor, goalId) {
    const goal = this.points.get(goalId); if (!goal) return null;
    if (!actor.scriptPath || actor.scriptPath.goal !== goalId) actor.scriptPath = {
      goal: goalId, ids: this.route(this.closestWaypoint(actor.root.position)?.id, goalId), cursor: 0
    };
    const path = actor.scriptPath;
    while (path.cursor < path.ids.length) {
      const point = this.points.get(path.ids[path.cursor]);
      if (actor.root.position.distanceTo(point.navigationPosition) > Math.max(.65, (point.size || 40) * SCALE * .25)) return point.navigationPosition;
      path.cursor++;
    }
    return goal.navigationPosition;
  }
  targetPosition(target) {
    if (target?.kind === 'char') return this.actor(target.id)?.root.position || null;
    if (target?.kind === 'waypoint') return this.points.get(target.id)?.navigationPosition || null;
    if (target?.kind === 'sceneitem') return this.sceneItem(target.id)?.position || null;
    return null;
  }
  updateControls() {
    for (const actor of this.actors.values()) {
      if (actor.scriptId === 0 || !alive(actor)) continue;
      const intent = actor.scriptIntent || { mode: 'wait' }, enemy = this.visibleEnemy(actor);
      let moveTarget = null, attackTarget = enemy, canAttack = !!enemy;
      if (intent.mode === 'idle') { attackTarget = null; canAttack = false; }
      // 00503970(wait)→004fdf00→00503e00 enters enemy pursuit after
      // discovery. Waiting is not a permanent ban on moving toward an enemy.
      else if (intent.mode === 'wait') moveTarget = enemy?.root.position || null;
      else if (intent.mode === 'patrol') {
        if (enemy) moveTarget = enemy.root.position;
        else if (intent.waypointIds.length) {
          const goalId = intent.waypointIds[intent.cursor % intent.waypointIds.length], goal = this.points.get(goalId);
          if (goal && actor.root.position.distanceTo(goal.navigationPosition) < Math.max(.75, goal.size * SCALE * .25)) { intent.cursor = (intent.cursor + 1) % intent.waypointIds.length; actor.scriptPath = null; }
          moveTarget = this.moveViaWaypoint(actor, intent.waypointIds[intent.cursor % intent.waypointIds.length]);
        }
      } else if (intent.mode === 'follow' || intent.mode === 'kill') {
        const ref = intent.targetRef ?? intent.targetId;
        const target = typeof ref === 'string' && !/^[-+]?\d+$/.test(ref) ? this.findActor(ref) : this.actor(ref, false);
        if (target) {
          if (target.team !== actor.team) { attackTarget = target; canAttack = true; }
          const nearest = this.closestWaypoint(target.root.position);
          moveTarget = this.lineOfSight(actor, target) ? target.root.position : this.moveViaWaypoint(actor, nearest?.id);
        }
      } else if (intent.mode === 'attacktarget') {
        // SetTarget slots are also reused for Distance queries. Capture the
        // target when ChangeBehavior executes: sn15 phase7 immediately reuses
        // slot0 for the VIP himself, which must not cancel his run to WP116.
        const target = intent.target || this.targets.get(intent.targetSlot), point = this.targetPosition(target);
        moveTarget = point ? this.moveViaWaypoint(actor, this.closestWaypoint(point)?.id) : null;
        attackTarget = null; canAttack = false;
      } else if (intent.mode === 'aggress' || intent.mode === 'run' || actor.scriptAggressive) moveTarget = enemy?.root.position || null;
      const paused = !!actor.scriptPerform, guard = actor.scriptPerform?.action === 'guard';
      actor.scriptControl = { mode: intent.mode, moveTarget: paused ? null : moveTarget, attackTarget,
        canAttack: !paused && canAttack, attackRequested: !!actor.scriptAttackRequested, paused, guard, speedScale: 1, enemyId: enemy?.scriptId ?? -1 };
      if (guard) actor.guard = true;
    }
  }
  update(dt) {
    if (!this.started || this.disposed || this.completed || this.game.paused) return;
    this.clock += Math.max(0, dt); this.accumulator += dt; this.idleAccumulator += dt;
    this.processPerformances(dt);
    if (this.accumulator >= this.scriptCadence) {
      this.accumulator %= this.scriptCadence;
      this.call(this.levelVm, 'OnUpdate');
      for (const [id, vm] of this.npcVms) if (alive(this.actor(id))) this.call(vm, 'OnUpdate');
      this.call(this.sceneVm, 'Scene_OnUpdate');
      this.call(this.sceneVm, 'Scene_OnIdle');
    }
    if (this.idleAccumulator >= .1) {
      this.idleAccumulator %= .1;
      for (const item of this.sceneItems.values()) this.sceneItemIdle(item.id);
    }
    this.processPerformances(0); this.updateControls(); this.checkCompletion(); this.publishState();
  }
  checkCompletion() {
    if (this.completed) return;
    // sn09 deliberately fails when either combatant dies. Its source keeps
    // dead player identity through GetAnyChar and calls GameOver after2s;
    // allow that explicit source result to run before a host fallback.
    if (!alive(this.actor(0)) && this.mapId !== 'sn09') { this.finish(false, 'player-death', 'PlayerHP reaches zero; mission failure adapter.'); return; }
    if (['sn04', 'sn09', 'sn15'].includes(this.mapId) && this.roundTime > 0 && this.clock >= this.roundTime * 60) {
      this.finish(false, 'round-timeout', this.provenance.timeout); return;
    }
    if (this.mapId === 'sn15') {
      const vip = this.findActor(this.vipName, true);
      if (vip && !alive(vip) && !vip.scriptRemoved && !this.pending.size) {
        if (this.completionAt == null) this.completionAt = this.clock + this.completionDelay;
        if (this.clock >= this.completionAt) this.finish(true, 'vip-defeated', this.provenance.vip);
      } else this.completionAt = null;
      return;
    }
    const hostile = [...this.actors.values()].filter(actor => actor.scriptId !== 0 && actor.team !== this.actor(0).team && !actor.scriptRemoved);
    if (this.rule === 10 && hostile.length && hostile.every(actor => !alive(actor)) && !this.pending.size) {
      if (this.completionAt == null) this.completionAt = this.clock + this.completionDelay;
      if (this.clock >= this.completionAt) this.finish(true, 'hostile-npcs-defeated', this.provenance.rule10);
    }
  }
  finish(win, reason, provenance) {
    if (this.completed) return;
    this.completed = { win, reason, provenance }; this.publishState();
    this.emit({ type: 'mission-complete', win, reason, provenance, mapId: this.mapId });
    if (this.game.finishStory) this.game.finishStory(this.completed);
    else this.game._finish?.(win);
  }
  publishState() {
    const targetName = this.mission?.protectName || this.mission?.vipName;
    const target = targetName ? [...this.actors.values()].find(actor => actor.name === targetName) : null;
    const gate = this.mission?.targetObject ? this.sceneItem(this.mission.targetObject) : null;
    const objective = this.mission ? { type: this.mission.objectiveType, text: this.mission.objective,
      targetName: target?.name || (gate ? '敌方城门' : null),
      targetHp: target?.hp ?? (gate ? Math.max(0, this.sceneVm.getGlobal('g_iBPdoorHP')) : null),
      targetMaxHp: target?.maxHp ?? (gate ? this.sceneVm.getGlobal('g_iPdoorMaxHP') : null),
      position: target ? { x: target.root.position.x, z: target.root.position.z } : gate ? { x: gate.position.x, z: gate.position.z } : null,
      escaped: !!target?.scriptRemoved } : null;
    this.game.missionState = { mapId: this.mapId, mode: 'story', rule: this.rule, roundTime: this.roundTime,
      elapsed: this.clock, remaining: this.roundTime > 0 ? Math.max(0, this.roundTime * 60 - this.clock) : null,
      phase: this.completed ? 'complete' : this.started ? 'running' : 'loading', result: this.completed || null,
      npcCount: Math.max(0, this.actors.size - 1), diagnostics: this.diagnostics.length,
      nativeCalls: this.nativeCallCount, compatibilityUsed: this.compatibilityUsed, provenance: this.provenance, objective };
  }
  natives() {
    const host = this;
    const api = {
      AddNPC: name => host.addNpc(name),
      GetChar: name => host.findActor(name)?.scriptId ?? -1,
      GetAnyChar: name => host.findActor(name, true)?.scriptId ?? -1,
      GetSelf: address => host.actor(address)?.scriptId ?? -1,
      GetHP: id => host.actor(id)?.hp ?? 0,
      GetMaxHP: id => host.actor(id)?.maxHp ?? 0,
      GetTeam: id => host.actor(id)?.team ?? -1,
      GetEnemy: id => host.visibleEnemy(host.actor(id))?.scriptId ?? -1,
      GetGameTime: () => Math.floor(host.clock),
      ChangeBehavior: (...args) => host.changeBehavior(...args),
      Perform: (...args) => host.enqueue(...args),
      PlayerPerform: (...args) => host.enqueue(0, ...args),
      Say: (...args) => host.dialogue(...args),
      IsPerforming: id => Number(!!host.actor(id)?.scriptPerform || !!host.actor(id)?.scriptQueue?.length),
      StopPerform: id => { const actor = host.actor(id); if (actor) { actor.scriptQueue = []; actor.scriptPerform = null; actor.scriptAttackRequested = false; actor.guard = false; } return Number(!!actor); },
      SetTarget: (slot, kind, id) => { host.targets.set(Number(slot), { kind, id: Number(id) }); return 1; },
      Distance: (a, b) => { const first = host.targetPosition(host.targets.get(Number(a))), second = host.targetPosition(host.targets.get(Number(b))); return first && second ? Math.trunc(first.distanceTo(second) / SCALE) : -1; },
      MakeString: function (unused, prefix, number) { this.setArg(0, String(prefix) + String(number).padStart(2, '0')); },
      GetSceneItem: (...args) => host.getSceneItem(...args),
      SetSceneItem: (...args) => host.setSceneItem(...args),
      CreateEffect: (target, effect) => {
        const item = host.sceneItem(target); host.game._soundDefinition?.(String(effect));
        if (host.game.playNativeEffect) host.game.playNativeEffect(item?.name || target, effect);
        else host.emit({ type: 'native-effect', target: item?.name || target, effect, visualPending: true });
        return 1;
      },
      NetEvent: enabled => { host.netEventEnabled = !!enabled; return 1; },
      Output: (...args) => { host.stdout.push(args); if (host.stdout.length > 1000) host.stdout.shift(); host.emit({ type: 'script-output', arguments: args }); },
      Print: (...args) => api.Output(...args),
      GameOver: result => { host.finish(Number(result) > 0, 'script-GameOver', 'Original PST calls GameOver.'); return 1; },
      GameCallBack: (command, team) => {
        if (host.mapId !== 'sn04' || command !== 'end' || ![1, 2].includes(Number(team))) return host.unsupported('GameCallBack', [command, team]);
        host.finish(Number(team) === host.actor(0)?.team, 'script-gate-destroyed', 'Original sn04 scene gate destruction calls end(winning team); Web maps that team to the player result.'); return 1;
      },
      SetScene: (name, ...values) => {
        if (!validNativeWeatherSetting(name, values)) return host.unsupported('SetScene', [name, ...values]);
        host.sceneSettings[name] = [...values]; host.game.setNativeScene?.(name, ...values); return 1;
      },
      Misc: (command, ...args) => {
        if (command === 'gettime') return Math.floor(host.clock * 1000);
        if (command === 'randomseries') {
          const [slot, first, last] = args.map(Number);
          if (![slot, first, last].every(Number.isInteger) || last < first || last - first > 10000) return host.unsupported('Misc:randomseries', args);
          const series = Array.from({ length: last - first + 1 }, (_, index) => first + index);
          for (let index = series.length - 1; index > 0; index--) {
            const chosen = Math.min(index, Math.max(0, Math.floor(host.random() * (index + 1))));
            [series[index], series[chosen]] = [series[chosen], series[index]];
          }
          host.randomSeries.set(slot, series); return 1;
        }
        if (command === 'getseries') {
          const [slot, index] = args.map(Number), value = host.randomSeries.get(slot)?.[index];
          return Number.isInteger(value) ? value : host.unsupported('Misc:getseries', args);
        }
        return host.unsupported(`Misc:${command}`, args);
      },
      UpdateAIAttrib: (id, name, value) => { const actor = host.actor(id); if (!actor) return 0; actor.scriptConfig[name] = value; return 1; },
      RemoveNPC: id => {
        const actor = host.actor(id); if (!actor || actor.scriptId === 0) return 0;
        actor.scriptRemoved = true; actor.scriptQueue = []; actor.scriptPerform = null; actor.scriptAttackRequested = false;
        if (host.game.removeScriptActor) host.game.removeScriptActor(actor);
        else { actor.root?.removeFromParent(); actor.character?.dispose(); actor.disposed = true; }
        return 1;
      }
    };
    if (this.compatibility) for (const [from, to] of [['Perofrm', 'Perform'], ['Distanve', 'Distance'], ['InitBBoxs', 'InitBBoxes']]) {
      api[from] = function (...args) {
        if (!host.compatibilityUsed.some(entry => entry.from === from)) {
          const entry = { from, to, location: this.location }; host.compatibilityUsed.push(entry);
          host.emit({ type: 'mission-compatibility', text: `原脚本兼容映射 ${from} → ${to}`, ...entry });
        }
        return to === 'InitBBoxes' ? this.vm.call(to, args) : api[to](...args);
      };
    }
    for (const name of ['rand', 'Rand', 'GetLeader']) api[name] = function (...args) { return host.unsupported(name, args, this); };
    return api;
  }
  dispose() {
    this.game.clearNativeScene?.(); this.sceneSettings = {};
    this.disposed = true; this.started = false;
    for (const actor of this.actors.values()) { clearNativeScriptItems(actor); actor.awarenessTarget = null; actor.scriptControlled = false; actor.scriptControl = null; actor.scriptIntent = null; actor.scriptPerform = null; actor.scriptQueue = []; actor.scriptAttackRequested = false; actor.scriptCrouched = false; }
    this.actors.clear(); this.npcVms.clear(); this.targets.clear(); this.randomSeries.clear(); this.sourceCache.clear(); this.programCache.clear();
  }
}

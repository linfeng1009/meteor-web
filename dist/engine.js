import * as THREE from './vendor/three.module.js';
import { loadGmb, loadGmc } from './gmc-loader.js';
import { loadNativeCharacter, NATIVE_CHARACTERS } from './native-character.js';
import { loadNativeCombat, NativeCombatController, NATIVE_WEAPONS, NATIVE_LOCOMOTION, NATIVE_DIRECTIONAL, createNativeDamageResolver, createNativeSceneDamageResolver } from './native-combat.js';
import { loadOriginalSceneModels } from './native-scene-models.js';
import { NativeMissionHost } from './native-mission-host.js';
import { NativeItemSystem } from './native-items.js';
import { NativeProjectileSystem, NATIVE_DART_PROFILE } from './native-projectiles.js';

const SCALE = .08;
const MAP_IDS = { sifang: 'sn06', cave: 'sn01', forge: 'sn10' };
const clamp = THREE.MathUtils.clamp;
const v3 = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
const nativePosition = p => v3(p[0] * SCALE, p[2] * SCALE, -p[1] * SCALE);
const surfaceY = hit => hit.face ? hit.face.normal.clone().transformDirection(hit.object.matrixWorld).y : 0;
const flatDistance = (a, b) => Math.hypot(a.x - b.x, a.z - b.z);
const originalRoot = new URL('./assets/original/', import.meta.url);

// The browser host consumes original model, animation and PST data. Damage math
// follows the recovered PE functions; contact volumes, physics and perception
// are explicit browser adapters pending complete native reconstruction.
export class MeteorGame {
  constructor(canvas, { onUpdate = () => {}, onEvent = () => {}, onEnd = () => {}, damageResolver = null, sceneDamageResolver = null } = {}) {
    this.canvas = canvas; this.onUpdate = onUpdate; this.onEvent = onEvent; this.onEnd = onEnd; this.damageResolver = damageResolver; this.sceneDamageResolver = sceneDamageResolver;
    this.scene = new THREE.Scene(); this.scene.background = new THREE.Color(0x101718);
    this.camera = new THREE.PerspectiveCamera(48, 1, .1, 2500);
    this.renderer = new THREE.WebGLRenderer({ canvas, antialias: true, powerPreference: 'high-performance' });
    this.renderer.setPixelRatio(Math.min(window.devicePixelRatio || 1, 1.75)); this.renderer.outputColorSpace = THREE.SRGBColorSpace;
    this.renderer.toneMapping = THREE.NoToneMapping; this.renderer.shadowMap.enabled = false;
    this.scene.add(new THREE.HemisphereLight(0xffffff, 0x596675, 2.7));
    const key = new THREE.DirectionalLight(0xffffff, 1.6); key.position.set(-20, 50, 30); this.scene.add(key);
    this.clock = new THREE.Clock(); this.elapsed = 0; this.updateAccum = 0; this.running = false; this.paused = false;
    this.map = 'sifang'; this.weapon = 'sword'; this.characterId = 0; this.actorSerial = 0; this.mode = 'training'; this.enemies = []; this.keys = new Set();
    this.cameraManualUntil = 0; this.cameraAngle = .4; this.cameraPitch = .45; this.cameraDistance = 8; this.cameraTarget = v3(); this.locked = null;
    this.raycaster = new THREE.Raycaster(); this.collisionMaterial = new THREE.MeshBasicMaterial({ side: THREE.DoubleSide });
    this.mapCache = new Map(); this.mapData = new Map(); this.pendingMaps = new Set(); this.weaponCache = new Map(); this.soundCache = new Map(); this.effects = []; this._listeners = []; this.mapRequest = 0; this.characterRequest = 0; this.sessionRequest = 0; this.directionBuffer = [];
    this.kills = 0; this.deaths = 0; this.totalDamage = 0; this.contactHits = 0; this.time = 0; this.matchElapsed = 0;
    // Adapter constants are explicit and provisional until recovered from Meteor.exe.
    this.hostPhysics = { speed: 100 * SCALE, gravity: 34, jumpVelocity: 12, radius: .4, step: .55, projectile: NATIVE_DART_PROFILE };
    this._initializeProjectiles();
    this._bind(); this.resize(); this._frame = this._frame.bind(this); this.raf = requestAnimationFrame(this._frame);
    this.ready = this._initialize();
    window.__game = this;
  }
  _initializeProjectiles() {
    this.projectiles = new NativeProjectileSystem({ scene: this.scene, bodyRadius: this.hostPhysics.radius,
      getTargets: () => [this.hero, ...this.enemies].filter(Boolean),
      getColliders: (from, to, radius) => { const center = from.clone().add(to).multiplyScalar(.5); return this.currentMap ? this._collisionCandidates(center.x, center.z, from.distanceTo(to) / 2 + radius + 1) : []; },
      onActorHit: (shot, target, point) => this._applyNativeHit(shot.context.attacker, target, shot.context.state, shot.context.attack, point, { projectileId: shot.id }),
      onWorldHit: (shot, hit) => this._projectileWorldHit(shot, hit)
    });
  }
  _launchNativeProjectiles(f, state) {
    if (f.weapon !== 'dart' || !NATIVE_DART_PROFILE.poseIds.includes(state.poseId) || !f.weaponModel) return;
    for (const attack of state.attacks) {
      const key = `release:${state.serial}:${attack.index}`; if (f.attackHits.has(key)) continue; f.attackHits.add(key);
      const origin = f.character.getAttachment('d_wpnR').getWorldPosition(v3());
      const target = f.hero ? this.locked || this._nearest(8) : f.scriptControl?.attackTarget || this.hero;
      const direction = target && !target.dead ? target.root.position.clone().add(v3(0, 1.35, 0)).sub(origin).normalize() : v3(Math.sin(f.root.rotation.y), 0, Math.cos(f.root.rotation.y));
      const visual = f.weaponModel.clone(true); visual.rotation.set(0, 0, 0); visual.position.set(0, 0, 0); visual.scale.setScalar(SCALE);
      // A hand attachment is native Z-up and had an inverse-X rotation; a free
      // world projectile instead keeps the loader's converted Y-up geometry.
      const center = new THREE.Box3().setFromObject(visual).getCenter(v3()); visual.position.sub(center);
      const attacker = { id: f.id, hero: f.hero, scriptId: f.scriptId, root: f.root, name: f.name, weapon: f.weapon, weaponId: f.weaponId,
        weaponRecord: f.weaponRecord, nativeStats: { ...f.nativeStats }, activeItems: [...(f.activeItems || [])], team: f.team, teamMask: f.teamMask };
      this.projectiles.spawn({ owner: f, position: origin, direction, visual, sourcePosition: f.root.position.clone().add(v3(0, 1.35, 0)),
        context: { attacker, state: { poseId: state.poseId, pose: state.pose, source: state.source, serial: state.serial }, attack: { ...attack }, model: 'w3_0', weaponId: f.weaponId } });
      this._soundDefinition(state.pose.raw.fields.effectid);
    }
  }
  _projectileWorldHit(shot, hit) {
    const object = hit.object?.userData.nativeSceneInstance;
    if (!object || !this.missionHost?.sceneVm.hasFunction(`${object.name}_OnAttack`)) return;
    const context = { ...shot.context, object, point: hit.point.clone(), projectileId: shot.id };
    const damage = this.sceneDamageResolver?.(context);
    if (Number.isFinite(damage) && damage >= 0) this.missionHost.sceneItemAttack(object.name, shot.context.attacker.scriptId, damage);
    else this.onEvent({ type: 'scene-contact', objectName: object.name, attackerId: shot.context.attacker.scriptId, poseId: shot.context.state.poseId, projectileId: shot.id, damagePending: true });
  }
  _loadStatus(text) { this.onEvent({ text, type: 'load' }); }
  async _initialize() {
    this._loadStatus('正在读取本地原版资源与动作表…');
    const [manifest, combat, weaponManifest] = await Promise.all([fetch(new URL('manifest.json', originalRoot)).then(r => { if (!r.ok) throw new Error('Original asset manifest unavailable'); return r.json(); }), loadNativeCombat(), fetch(new URL('weapon-models/manifest.json', originalRoot)).then(r => { if (!r.ok) throw new Error('Original weapon manifest unavailable'); return r.json(); })]);
    this.manifest = manifest; this.combatData = combat; this.weaponManifest = weaponManifest;
    this.weaponItems = new Map(weaponManifest.items.map(item => [Number(item.itemId), item])); this.weaponModels = new Map(weaponManifest.models.map(model => [model.modelId.toLowerCase(), model]));
    if (!this.damageResolver) this.damageResolver = createNativeDamageResolver(combat);
    if (!this.sceneDamageResolver) this.sceneDamageResolver = createNativeSceneDamageResolver(combat);
    this.items = new NativeItemSystem({ itemRecords: combat.itemRecords,
      getInstances: () => this.currentMap?.props?.instances.values() || [],
      canReach: (actor, item) => this._canReachItem(actor, item),
      onPickup: result => {
        const callback = `${result.objectName}_OnPickUp`;
        if (this.missionHost?.sceneVm.hasFunction(callback)) this.missionHost.call(this.missionHost.sceneVm, callback, []);
        this._emit(`${result.name} · 气血 +${result.healed}`, 'pickup');
      }
    });
    this.effectDefinitions = new Map((manifest.sounds?.effectDefinitions || []).map(e => [e.id.toLowerCase(), e]));
    this.waveFiles = new Map((manifest.sounds?.effects || []).map(e => [e.id.toLowerCase(), e]));
    const [hero] = await Promise.all([this._createFighter(0, '孟星魂', true), this._loadMap('sifang')]);
    this.hero = hero; this.scene.add(hero.root); this._placeFighter(hero, this.currentMap.spawns[0]); await this._equip(hero, this.weapon);
    this.cameraTarget.copy(hero.root.position).add(v3(0, 1.6, 0)); this._tickCamera(1);
    this._loadStatus('原版地图、人物、兵器与动作数据已就绪'); this._hud(); return this;
  }
  async _loadMap(name) {
    this.projectiles?.clear('map-change');
    this.items?.reset();
    name = MAP_IDS[name] || /^sn\d+$/.test(name) ? name : 'sifang'; const request = ++this.mapRequest, id = MAP_IDS[name] || name;
    const label = this.manifest.maps.find(m => m.id === id)?.name || id; this._loadStatus(`正在读取原版${label}…`);
    if (!this.mapCache.has(id)) {
      this.pendingMaps.add(id);
      this.mapCache.set(id, this._readMap(id).then(result => { this.pendingMaps.delete(id); if (this.disposed) this._disposeMap(result); else this.mapData.set(id, result); return result; }).catch(error => { this.pendingMaps.delete(id); this.mapCache.delete(id); throw error; }));
    } else { const cached = this.mapCache.get(id); this.mapCache.delete(id); this.mapCache.set(id, cached); }
    const result = await this.mapCache.get(id);
    if (request !== this.mapRequest || this.disposed) { this._trimMapCache(); return result; }
    if (this.currentMap?.model) this.currentMap.model.visible = false;
    this.currentMap = result; this.map = name; result.model.visible = true; if (!result.model.parent) this.scene.add(result.model);
    this.scene.background.setHex(name === 'cave' ? 0x080c0e : name === 'forge' ? 0x24120c : 0x263038);
    this.camera.far = Math.max(1500, result.bounds.getSize(v3()).length() * 4); this.camera.updateProjectionMatrix();
    if (this.hero && !this.running) this._placeFighter(this.hero, result.spawns[0]);
    this._trimMapCache();
    return result;
  }
  _disposeMap(data) {
    const geometries = new Set(), materials = new Set(), textures = new Set();
    data.model.traverse(object => {
      if (object.geometry) geometries.add(object.geometry);
      for (const material of object.material ? Array.isArray(object.material) ? object.material : [object.material] : []) {
        materials.add(material); for (const value of Object.values(material)) if (value?.isTexture) textures.add(value);
      }
    });
    data.model.removeFromParent(); geometries.forEach(g => g.dispose()); textures.forEach(t => t.dispose()); materials.forEach(m => m.dispose());
  }
  _trimMapCache() {
    for (const id of this.mapCache.keys()) {
      if (this.mapCache.size <= 2) break;
      if (id === this.currentMap?.id || this.pendingMaps.has(id) || !this.mapData.has(id)) continue;
      this._disposeMap(this.mapData.get(id)); this.mapData.delete(id); this.mapCache.delete(id);
    }
  }
  async _readMap(id) {
    const entry = this.manifest.maps.find(m => m.id === id); if (!entry || entry.available === false) throw new Error(entry?.unavailableReason || `Original map ${id} absent`);
    const metadata = await fetch(new URL(entry.metadata, originalRoot)).then(r => r.json());
    const desText = await fetch(new URL(entry.description, originalRoot)).then(r => r.text());
    const textureMap = {}, textureAlphaMap = {};
    for (const t of entry.textures) { const url = t.url || t.frames?.[0]?.url; if (url) textureMap[t.reference.toLowerCase()] = new URL(url, originalRoot).href; if (t.alphaMask) textureAlphaMap[t.reference.toLowerCase()] = new URL(t.alphaMask, originalRoot).href; }
    const modelURL = new URL(entry.model, originalRoot);
    const model = await loadGmb(modelURL.href, { scale: SCALE, groundZ: 0, texturePath: new URL('textures/', modelURL).href, textureMap, textureAlphaMap, desText, unlit: true, name: entry.name || entry.id, source: `local:${entry.id}` });
    model.updateMatrixWorld(true); model.visible = false;
    const colliders = [], bounds = new THREE.Box3();
    for (const mesh of model.children.filter(m => m.userData.collidable)) {
      const collider = new THREE.Mesh(mesh.geometry, this.collisionMaterial); collider.name = mesh.name; collider.matrixWorld.copy(mesh.matrixWorld); collider.matrixAutoUpdate = false; colliders.push(collider);
      mesh.geometry.computeBoundingBox(); bounds.union(mesh.geometry.boundingBox.clone().applyMatrix4(mesh.matrixWorld));
    }
    const des = metadata.files.find(f => f.parsed?.format === 'DES')?.parsed;
    const props = await loadOriginalSceneModels(des?.objects || [], { scale: SCALE, collisionMaterial: this.collisionMaterial }); model.add(props.group); model.updateMatrixWorld(true);
    const userSpawns = (des?.objects || []).filter(o => /^D_user\d+$/i.test(o.name)).sort((a, b) => a.name.localeCompare(b.name, undefined, { numeric: true })).map(o => ({ name: o.name, position: nativePosition(o.position), rotation: o.quaternion }));
    const points = (metadata.waypoints?.points || []).map(p => ({ ...p, native: p.position, position: nativePosition(p.position) }));
    const spawnIndex = metadata.level?.integers.PlayerSpawn;
    const selectedPoint = points.find(p => p.id === spawnIndex) || points[0];
    const canStand = spawn => {
      this.raycaster.set(spawn.position.clone().add(v3(0, 3, 0)), v3(0, -1, 0));
      return this.raycaster.intersectObjects([...colliders, ...props.getCollidersNear(spawn.position.x, spawn.position.z)], false).some(hit => surfaceY(hit) > .38);
    };
    const spawns = userSpawns.filter(canStand), skippedSpawns = userSpawns.filter(s => !spawns.includes(s)).map(s => s.name);
    if (spawns.length < 4) for (const point of [selectedPoint, ...points.filter(p => p !== selectedPoint)].filter(Boolean)) {
      const candidate = { name: `WP${point.id}`, position: point.position.clone() };
      if (canStand(candidate) && spawns.every(s => flatDistance(s.position, candidate.position) > 2)) spawns.push(candidate);
      if (spawns.length >= 8) break;
    }
    if (!spawns.length || bounds.isEmpty()) throw new Error(`Map ${id} has no usable original spawn/collision data`);
    return { id, entry, metadata, model, colliders, props, sceneObjects: props.instances, bounds, points, spawns, skippedSpawns };
  }
  async _createFighter(characterId, name, hero = false) {
    const character = await loadNativeCharacter(characterId, { scale: SCALE, inPlace: true });
    const f = { character, root: character.group, id: ++this.actorSerial, modelId: characterId, name: name || NATIVE_CHARACTERS.find(c => c.id === characterId)?.name || `角色 ${characterId}`, hero, hp: 1000, maxHp: 1000, rage: 0, weapon: this.weapon, velocity: v3(), vy: 0, grounded: true, guard: false, dead: false, respawn: 0, attackHits: new Set(), lastSerial: 0, contacts: 0, aiTimer: 1, heldPose: null };
    f.combat = new NativeCombatController(this.combatData, { weapon: this.weapon, sampleRoot: character.sampleRoot, scale: SCALE });
    f.combat.play(NATIVE_WEAPONS[this.weapon].stance, { loop: true, force: true });
    if (!hero) this._nameplate(f); return f;
  }
  _placeFighter(f, spawn) {
    const p = spawn?.position || this.currentMap.spawns[0].position; f.root.position.copy(p);
    const ground = this._ground(p.x, p.z, p.y + 3);
    if (ground) f.root.position.y = ground.point.y + .015;
    f.maxHp = f.scriptConfig?.HP ?? f.scriptConfig?.PlayerHP ?? this.currentMap.metadata.level?.integers.PlayerHP ?? 1000; f.hpSourceVerified = true;
    f.velocity.set(0, 0, 0); f.vy = 0; f.grounded = true; f.guard = false; f.dead = false; f.root.visible = true; f.hp = f.maxHp; f.rage = 0; f.contacts = 0; f.previousPosition?.copy(f.root.position);
    f.heldPose = null; f.attackHits.clear(); f.combat.play(NATIVE_WEAPONS[f.weapon].stance, { loop: true, force: true });
  }
  async _readWeapon(modelId) {
    const entry = this.weaponModels.get(modelId.toLowerCase()); if (!entry) throw new Error(`Original weapon ${modelId} not extracted`);
    const base = new URL('weapon-models/', originalRoot), textureMap = {}, textureAlphaMap = {};
    for (const t of entry.textures) { const url = t.url || t.frames?.[0]?.url; if (url) textureMap[t.reference.toLowerCase()] = new URL(url, base).href; if (t.alphaMask) textureAlphaMap[t.reference.toLowerCase()] = new URL(t.alphaMask, base).href; }
    const modelURL = new URL(entry.modelUrl, base), loader = entry.format === 'GMB' ? loadGmb : loadGmc;
    return loader(modelURL.href, { scale: 1, groundZ: 0, textureMap, textureAlphaMap, texturePath: new URL('textures/', modelURL).href, unlit: true, name: modelId, source: `local:cmodel/${modelId}` });
  }
  async _equip(f, selection) {
    const request = f.equipRequest = (f.equipRequest || 0) + 1;
    const item = this.weaponItems.get(typeof selection === 'number' ? selection : NATIVE_WEAPONS[selection]?.weaponId);
    if (!item || !item.available) throw new Error(`Original weapon item ${selection} unavailable`);
    const prefix = item.modelId.toLowerCase().split('_')[0], name = Object.keys(NATIVE_WEAPONS).find(key => NATIVE_WEAPONS[key].model.split('_')[0] === prefix);
    if (!name) throw new Error(`Original weapon action family ${item.modelId} has not been ported`);
    f.weapon = name; f.weaponId = Number(item.itemId); f.weaponName = item.name; f.weaponRecord = this.combatData.weaponRecords.get(item.modelId.toLowerCase());
    f.combat.setWeapon(name); f.combat.play(NATIVE_WEAPONS[name].stance, { loop: true, force: true }); f.heldPose = NATIVE_WEAPONS[name].stance;
    for (const model of f.weaponModels || (f.weaponModel ? [f.weaponModel] : [])) model.removeFromParent(); f.weaponModels = []; f.weaponModel = null;
    const ids = item.modelIds.map(id => id.toLowerCase());
    for (const id of ids) if (!this.weaponCache.has(id)) this.weaponCache.set(id, this._readWeapon(id).catch(error => { this.weaponCache.delete(id); throw error; }));
    try {
      const models = (await Promise.all(ids.map(id => this.weaponCache.get(id)))).map(model => model.clone(true));
      if (this.disposed || f.disposed || request !== f.equipRequest) return;
      // GMC is converted Z-up→Y-up by the loader; attachments still use native
      // coordinates inside the character's scaled Z-up skeleton, so undo that.
      for (let i = 0; i < models.length; i++) { const model = models[i]; model.rotation.x = Math.PI / 2; f.character.getAttachment(/l$/i.test(ids[i]) ? 'd_wpnL' : 'd_wpnR').add(model); }
      f.weaponModels = models; f.weaponModel = models[0]; f.weaponReach = clamp(new THREE.Box3().setFromObject(models[0]).getSize(v3()).length() * .65, 1.8, 4.8);
    } catch (error) { this._emit(`原版兵器读取失败：${name}`, 'info'); console.error(error); }
  }
  _ground(x, z, ceiling) {
    if (!this.currentMap) return null;
    this.raycaster.set(v3(x, ceiling, z), v3(0, -1, 0));
    return this.raycaster.intersectObjects(this._collisionCandidates(x, z), false).find(hit => surfaceY(hit) > .38) || null;
  }
  _collisionCandidates(x, z, radius = 1) { return [...this.currentMap.colliders, ...(this.currentMap.props?.getCollidersNear(x, z, radius) || [])]; }
  get sceneObjects() { return this.currentMap?.sceneObjects || new Map(); }
  getSceneObject(name) { return typeof name === 'number' ? [...this.sceneObjects.values()].find(o => o.id === name || o.runtimeId === name) : this.sceneObjects.get(String(name).toLowerCase()); }
  playScenePose(name, pose, loop = false) { return this.getSceneObject(name)?.playPose(pose, { loop: !!loop }) || false; }
  setSceneActive(name, active) { const object = this.getSceneObject(name); if (object) object.setActive(!!active); return !!object; }
  setSceneCollision(name, active) { const object = this.getSceneObject(name); if (object) object.setCollision(!!active); return !!object; }
  _horizontalBlocked(position, dx, dz) {
    const distance = Math.hypot(dx, dz); if (!distance) return false;
    const direction = v3(dx / distance, 0, dz / distance);
    for (const height of [.62, 1.4, 2.2]) {
      this.raycaster.set(position.clone().add(v3(0, height, 0)), direction);
      this.raycaster.far = distance + this.hostPhysics.radius;
      const hit = this.raycaster.intersectObjects(this._collisionCandidates(position.x, position.z, distance + 1), false).find(h => Math.abs(surfaceY(h)) < .65);
      this.raycaster.far = Infinity; if (hit) return true;
    }
    return false;
  }
  _move(f, direction, speed, dt) {
    const desired = direction.clone().multiplyScalar(speed); f.velocity.lerp(desired, 1 - Math.exp(-dt * 14));
    let dx = f.velocity.x * dt, dz = f.velocity.z * dt, p = f.root.position;
    if (!this._horizontalBlocked(p, dx, 0)) p.x += dx;
    if (!this._horizontalBlocked(p, 0, dz)) p.z += dz;
    const ground = this._ground(p.x, p.z, p.y + this.hostPhysics.step);
    if (f.grounded && ground && p.y - ground.point.y < .8) p.y = ground.point.y + .015;
    else {
      f.grounded = false; f.vy -= this.hostPhysics.gravity * dt; p.y += f.vy * dt;
      const landing = this._ground(p.x, p.z, p.y + Math.max(.7, -f.vy * dt + .15));
      if (landing && p.y <= landing.point.y + .04 && f.vy <= 0) { p.y = landing.point.y + .015; f.vy = 0; f.grounded = true; }
    }
    if (p.y < this.currentMap.bounds.min.y - 20 || Math.abs(p.x) > 3000 || Math.abs(p.z) > 3000) { if (this.mode === 'story') { f.hp = 0; this._kill(f); } else this._placeFighter(f, this.currentMap.spawns[f.hero ? 0 : (f.spawnIndex || 1) % this.currentMap.spawns.length]); }
  }
  _moveDirection() {
    const x = Number(this.keys.has('right')) - Number(this.keys.has('left')), z = Number(this.keys.has('forward')) - Number(this.keys.has('back')), a = this.cameraAngle;
    return v3(Math.cos(a) * x - Math.sin(a) * z, 0, -Math.sin(a) * x - Math.cos(a) * z).normalize();
  }
  _face(f, target, dt = 1) {
    const desired = Math.atan2(target.x - f.root.position.x, target.z - f.root.position.z), current = f.root.rotation.y;
    f.root.rotation.y += Math.atan2(Math.sin(desired - current), Math.cos(desired - current)) * Math.min(1, dt * 12);
  }
  async createScriptActor(config) {
    const actor = await this._createFighter(Number(config.modelId), config.name);
    if (this.disposed || this.mode !== 'story') { actor.disposed = true; this._disposeNameplate(actor); actor.character.dispose(); throw new Error('Story actor load cancelled'); }
    Object.assign(actor, { scriptId: config.scriptId, scriptConfig: config.nativeGlobals || config, scriptControlled: true,
      team: Number(config.team), teamMask: Number(config.team), spawnIndex: config.spawnIndex, weapon2Id: config.weapon2Id });
    this._placeFighter(actor, config.spawn); actor.maxHp = actor.hp = config.hp ?? 1000;
    if (Number.isFinite(config.facing)) actor.root.rotation.y = config.facing * Math.PI / 180;
    this.scene.add(actor.root); this.enemies.push(actor);
    await this._equip(actor, Number(config.weaponId)); return actor;
  }
  async placeScriptPlayer(config) {
    const actor = this.hero; actor.scriptConfig = config; actor.scriptId = 0;
    actor.team = actor.teamMask = Number(config.PlayerTeam ?? config.team ?? 1);
    actor.weapon2Id = Number(config.weapon2Id); actor.scriptInputBlocked = false;
    this._placeFighter(actor, config.spawn); actor.maxHp = actor.hp = config.hp ?? config.PlayerHP ?? 1000;
    actor.root.rotation.y = Number(config.PlayerSpawnDir ?? config.facing ?? 0) * Math.PI / 180;
    await this._equip(actor, Number(config.weaponId)); this.weapon = actor.weapon;
  }
  removeScriptActor(actor) {
    actor.scriptRemoved = true; actor.disposed = true; this._disposeNameplate(actor); actor.character.dispose(); actor.root.removeFromParent();
    this.enemies = this.enemies.filter(f => f !== actor); if (this.locked === actor) this.locked = null;
  }
  hasScriptLineOfSight(actor, target) {
    const from = actor.root.position.clone().add(v3(0, 1.35, 0)), ray = target.root.position.clone().add(v3(0, 1.35, 0)).sub(from), distance = ray.length();
    if (distance < .5) return true;
    this.raycaster.set(from, ray.normalize()); this.raycaster.far = Math.max(0, distance - .35);
    const blocked = this.raycaster.intersectObjects(this._collisionCandidates(from.x, from.z, distance), false).some(hit => hit.distance > .25);
    this.raycaster.far = Infinity; return !blocked;
  }
  finishStory(result) { this.storyResult = result; this._finish(!!result.win); }
  async start({ map = 'sifang', weapon = 'sword', difficulty = 'normal', character = 0, mode = 'training' } = {}) {
    const request = ++this.sessionRequest;
    await this.ready; if (request !== this.sessionRequest || this.disposed) return;
    this.projectiles?.clear('restart'); this.projectiles?.pause(false); this.items?.reset(); this.missionHost?.dispose(); this.missionHost = null; this.missionState = null; this.storyResult = null;
    this.pointer = null; this.keys.clear(); this.directionBuffer = []; this.running = false; this.paused = false; this.mode = mode === 'story' ? 'story' : 'training';
    if (map !== this.map) await this._loadMap(map);
    if (request !== this.sessionRequest || this.disposed) return;
    if (this.mode === 'story') character = 0;
    if (Number(character) !== this.characterId) await this.setCharacter(character);
    if (request !== this.sessionRequest || this.disposed) return;
    this.difficulty = difficulty;
    for (const f of this.enemies) { f.disposed = true; this._disposeNameplate(f); f.character.dispose(); f.root.removeFromParent(); } this.enemies = [];
    this.hero.scriptConfig = null; this.hero.scriptControl = null; this.hero.scriptInputBlocked = false; this.hero.team = this.hero.teamMask = 1;
    this.kills = 0; this.deaths = 0; this.totalDamage = 0; this.contactHits = 0; this.matchElapsed = 0; this.time = 0; this.locked = null;
    if (this.mode === 'story') {
      this._loadStatus('正在执行原版关卡脚本与载入原 NPC…');
      const host = await NativeMissionHost.create(this, { mapId: this.currentMap.id });
      if (request !== this.sessionRequest || this.disposed) { host.dispose(); return; }
      this.missionHost = host; await host.start();
      if (request !== this.sessionRequest || this.disposed) { host.dispose(); return; }
    } else {
      this.weapon = NATIVE_WEAPONS[weapon] ? weapon : 'sword'; await this._equip(this.hero, this.weapon); this._placeFighter(this.hero, this.currentMap.spawns[0]);
      const actors = await Promise.all([1, 2, 5].map(id => this._createFighter(id, NATIVE_CHARACTERS.find(c => c.id === id)?.name)));
      if (request !== this.sessionRequest || this.disposed) { for (const f of actors) { f.disposed = true; this._disposeNameplate(f); f.character.dispose(); } return; }
      const heroPos = this.hero.root.position;
      const ordered = this.currentMap.spawns.map((spawn, i) => ({ ...spawn, index: i })).filter(spawn => flatDistance(spawn.position, heroPos) > 4).sort((a, b) => flatDistance(a.position, heroPos) - flatDistance(b.position, heroPos));
      await Promise.all(actors.map(async (f, i) => {
        const spawn = ordered[i] || this.currentMap.spawns[(i + 1) % this.currentMap.spawns.length];
        f.spawnIndex = spawn.index ?? i + 1; f.slot = i; f.team = f.teamMask = 2; this._placeFighter(f, spawn); this.scene.add(f.root); this.enemies.push(f); await this._equip(f, ['sword', 'blade', 'spear'][i]);
      }));
    }
    if (request !== this.sessionRequest || this.disposed) return;
    this.running = true; this.cameraManualUntil = 0; this.cameraAngle = this.currentMap.id === 'sn01' ? Math.PI / 2 : 0; this.cameraPitch = .4; this.cameraDistance = 8;
    this.cameraTarget.copy(this.hero.root.position).add(v3(0, 1.5, 0)); this._tickCamera(1); this._unlockAudio();
    this._emit(this.mode === 'story' ? `原版${this.currentMap.entry.name || this.currentMap.id}` : '原版动作演练开始', 'info'); this._hud();
  }
  async menu(map = this.map) {
    ++this.sessionRequest; this.projectiles?.clear('menu'); this.projectiles?.pause(false); this.items?.reset(); this.missionHost?.dispose(); this.missionHost = null; this.missionState = null; this.mode = 'training';
    this.running = false; this.paused = false; this.keys.clear(); this.pointer = null; this.locked = null; this.directionBuffer = [];
    await this.ready; if (this.disposed) return;
    if (map !== this.map) await this._loadMap(map);
    for (const f of this.enemies) { f.disposed = true; this._disposeNameplate(f); f.character.dispose(); } this.enemies = [];
    this.hero.guard = false; this.hero.scriptConfig = null; this.hero.scriptInputBlocked = false; this._placeFighter(this.hero, this.currentMap.spawns[0]); this.hero.root.rotation.y = -.3; this._hud();
  }
  pause(value = true) { this.paused = !!value; this.projectiles?.pause(this.paused); this.keys.clear(); this.pointer = null; this.directionBuffer = []; if (this.hero) this.hero.guard = false; if (this.master) this.master.gain.value = this.paused || this.muted ? 0 : .25; this._hud(); }
  async setCharacter(id = 0) {
    const request = ++this.characterRequest; await this.ready; id = Number(id); if (id === this.characterId || request !== this.characterRequest) return;
    const actor = await this._createFighter(id, NATIVE_CHARACTERS.find(c => c.id === id)?.name, true); if (this.disposed || request !== this.characterRequest) { actor.disposed = true; actor.character.dispose(); return; }
    if (this.hero) { this.hero.disposed = true; this.hero.character.dispose(); } this.hero = actor; this.characterId = id; this.scene.add(actor.root); this._placeFighter(actor, this.currentMap.spawns[0]); await this._equip(actor, this.weapon); this._hud();
  }
  async setWeapon(name) { if (!NATIVE_WEAPONS[name] || this.mode === 'story') return; this.weapon = name; if (this.hero) await this._equip(this.hero, name); this._hud(); }
  async switchWeapon() {
    if (this.mode === 'story') {
      if (this.hero.switchingWeapon) return; const next = this.hero.weapon2Id; if (!this.weaponItems.has(next)) return;
      this.hero.switchingWeapon = true; const previous = this.hero.weaponId;
      try { await this._equip(this.hero, next); this.hero.weapon2Id = previous; this.weapon = this.hero.weapon; this._hud(); } finally { this.hero.switchingWeapon = false; }
    }
    else { const families = ['sword', 'spear', 'blade', 'dagger', 'dart']; await this.setWeapon(families[(families.indexOf(this.weapon) + 1) % families.length]); }
  }
  setMuted(value) { this.muted = !!value; if (this.master) this.master.gain.value = value ? 0 : .25; }
  setQuality(value) { this.quality = value; this.renderer.setPixelRatio(Math.min(window.devicePixelRatio || 1, value === 'low' ? 1 : 1.75)); this.resize(); }
  setDamageResolver(resolver) { if (resolver !== null && typeof resolver !== 'function') throw new Error('Damage resolver must be a function or null'); this.damageResolver = resolver; }
  action(name, active = true) {
    if (active && this.hero?.scriptInputBlocked) return;
    if (name === 'crouch') { if (active && this.running && !this.paused) this.keys.add('crouch'); else this.keys.delete('crouch'); return; }
    if (['forward', 'back', 'left', 'right'].includes(name)) { if (active && this.running && !this.paused) { if (!this.keys.has(name)) { this.directionBuffer.push({ direction: { forward: 'up', back: 'down', left: 'left', right: 'right' }[name], time: this.elapsed }); this.directionBuffer = this.directionBuffer.slice(-4); } this.keys.add(name); } else this.keys.delete(name); return; }
    if (name === 'guard') { if (this.hero) this.hero.guard = active && this.running && !this.paused && !this.hero.combat.attacking; return; }
    if (!active || !this.running || this.paused || !this.hero || this.hero.dead) return;
    this._unlockAudio();
    if (name === 'attack') this._beginAttack(this.hero);
    else if (name === 'jump' && this.hero.grounded && !this.hero.combat.attacking) { this.hero.grounded = false; this.hero.vy = this.hostPhysics.jumpVelocity; this.hero.combat.play(NATIVE_LOCOMOTION.jumpStart, { force: true }); this.hero.heldPose = 'jump'; }
    else if (name === 'lock') { this.locked = this.locked ? null : this._nearest(); this.cameraManualUntil = 0; this._hud(); }
    else if (name === 'switch') this.switchWeapon();
    else if (name === 'pickup' && this.mode === 'story') {
      const result = this.items?.tryPickup(this.hero);
      if (result?.reason === 'full-hp') this._emit('气血已满，肉包留在原处', 'info');
      this._hud();
    }
    else if (name === 'fury' || name === 'dodge') this._emit('该动作的原版指令与条件正在逆向，当前不使用替代招式', 'info');
    else if (/^pose:\d+$/.test(name)) this.hero.combat.play(Number(name.slice(5)));
    else if (['weapon1', 'weapon2', 'weapon3', 'weapon4', 'weapon5'].includes(name)) this.setWeapon(['sword', 'blade', 'spear', 'dagger', 'dart'][Number(name.slice(-1)) - 1]);
  }
  _beginAttack(f) {
    const target = f.hero ? this.locked || this._nearest(8) : f.scriptControl?.attackTarget || this.hero;
    if (target) this._face(f, target.root.position);
    let poseId = null;
    if (f.hero && f.grounded) {
      const recent = this.directionBuffer.filter(d => this.elapsed - d.time < .65), mapping = NATIVE_DIRECTIONAL[f.weapon] || {};
      poseId = mapping[recent.slice(-2).map(d => d.direction).join(',')] ?? mapping[recent.at(-1)?.direction] ?? null;
      if (poseId == null) for (const [key, direction] of [['forward', 'up'], ['back', 'down'], ['left', 'left'], ['right', 'right']]) if (this.keys.has(key)) { poseId = mapping[direction] ?? null; break; }
    }
    if (f.combat.attack({ air: !f.grounded, poseId })) { f.guard = false; f.heldPose = 'attack'; }
  }
  _nearest(range = Infinity) { let best = null; for (const f of this.enemies) { const d = flatDistance(f.root.position, this.hero.root.position); if (!f.dead && !f.disposed && !f.scriptRemoved && f.team !== this.hero.team && d < range) { range = d; best = f; } } return best; }
  _updateFighter(f, dt) {
    if (f.disposed || f.scriptRemoved) return;
    (f.previousPosition ||= v3()).copy(f.root.position);
    if (f.dead) { const state = f.combat.update(dt); if (state) f.character.setPoseFrame(state.source, state.frame); f.respawn -= dt; if (f.respawn <= 0) this._placeFighter(f, this.currentMap.spawns[f.hero ? 0 : f.spawnIndex % this.currentMap.spawns.length]); return; }
    let direction = v3(), speed = this.hostPhysics.speed;
    if (f.hero) {
      if (f.scriptInputBlocked) f.guard = false;
      direction = f.scriptInputBlocked ? v3() : this._moveDirection(); if (this.locked && !this.locked.dead) this._face(f, this.locked.root.position, dt); else if (direction.lengthSq() > 0 && !f.combat.attacking) this._face(f, f.root.position.clone().add(direction), dt);
    } else if (f.scriptControlled) {
      const control = f.scriptControl;
      f.guard = !!control?.guard && !f.combat.attacking; speed *= Number(control?.speedScale ?? 1) * .68;
      if (control && !control.paused) {
        const target = control.attackTarget, targetAlive = target && !target.dead && !target.disposed;
        const moveTarget = control.moveTarget, reach = f.weaponReach || (f.weapon === 'spear' ? 3.8 : 2.3);
        const distance = targetAlive ? flatDistance(target.root.position, f.root.position) : Infinity;
        if (moveTarget && (moveTarget !== target?.root.position || distance > reach + .2)) { direction.copy(moveTarget).sub(f.root.position); direction.y = 0; if (direction.length() > .45) direction.normalize(); else direction.set(0, 0, 0); }
        if (targetAlive && control.canAttack) {
          this._face(f, target.root.position, dt);
          if (distance < reach - .5) { direction.copy(f.root.position).sub(target.root.position); direction.y = 0; direction.normalize(); speed *= .35; }
          f.aiTimer -= dt; if (distance <= reach + .6 && f.aiTimer <= 0 && !f.combat.attacking && this.hasScriptLineOfSight(f, target)) { this._beginAttack(f); f.aiTimer = 1.2 + Math.random() * .9; }
        } else if (direction.lengthSq() > 0) this._face(f, f.root.position.clone().add(direction), dt);
      }
    } else if (this.running && !this.hero.dead) {
      const delta = this.hero.root.position.clone().sub(f.root.position); delta.y = 0; const distance = delta.length();
      this._face(f, this.hero.root.position, dt); speed *= this.difficulty === 'hard' ? .9 : .68;
      const reach = f.weaponReach || (f.weapon === 'spear' ? 3.8 : 2.3);
      if (distance > reach + .2) direction.copy(delta).normalize();
      else if (distance < reach - .45) { direction.copy(delta).normalize().negate(); speed *= .4; }
      if (distance < reach + 3 && !f.combat.attacking) {
        const angle = (f.slot || 0) * Math.PI * 2 / 3 + this.elapsed * .035;
        const slot = this.hero.root.position.clone().add(v3(Math.sin(angle) * reach, 0, Math.cos(angle) * reach)).sub(f.root.position); slot.y = 0;
        if (slot.length() > .7) direction.lerp(slot.normalize(), .55).normalize();
      }
      f.aiTimer -= dt; if (distance < reach + .7 && f.aiTimer <= 0 && !f.combat.attacking) { this._beginAttack(f); f.aiTimer = 1.2 + Math.random() * .9; }
    }
    if (f.guard) speed *= .3;
    if (f.combat.attacking) speed = 0;
    this._move(f, direction, speed, dt);
    if (!f.combat.attacking) {
      let pose = f.guard ? NATIVE_WEAPONS[f.weapon].guard : !f.grounded ? NATIVE_LOCOMOTION.jumpAir : f.velocity.lengthSq() > .2 ? NATIVE_LOCOMOTION.run : NATIVE_WEAPONS[f.weapon].stance;
      const startingJump = f.heldPose === 'jump' && f.combat.timeline?.pose.id === NATIVE_LOCOMOTION.jumpStart && !f.combat.timeline.finished;
      if (startingJump) pose = NATIVE_LOCOMOTION.jumpStart;
      const crouching = f.hero && this.keys.has('crouch') && f.grounded; if (crouching) pose = 10;
      if (f.heldPose !== pose && !startingJump) { f.combat.play(pose, { loop: true, force: true }); f.heldPose = pose; }
    }
    const state = f.combat.update(dt); if (!state) return;
    if (state.pose.attacks.length) {
      const a = f.root.rotation.y, localX = state.rootDelta.x, localZ = -state.rootDelta.y;
      const dx = Math.cos(a) * localX + Math.sin(a) * localZ, dz = -Math.sin(a) * localX + Math.cos(a) * localZ;
      if (!this._horizontalBlocked(f.root.position, dx, 0)) f.root.position.x += dx;
      if (!this._horizontalBlocked(f.root.position, 0, dz)) f.root.position.z += dz;
    }
    f.character.setPoseFrame(state.source, state.frame);
    if (state.serial !== f.lastSerial) { f.attackHits.clear(); f.lastSerial = state.serial; if (state.pose.attacks.length && !(f.weapon === 'dart' && NATIVE_DART_PROFILE.poseIds.includes(state.poseId))) this._soundDefinition(state.pose.raw.fields.effectid); }
    if (state.attacks.length) { this._launchNativeProjectiles(f, state); this._resolveContacts(f, state); }
    if (f.nameplate) { f.nameplate.quaternion.copy(f.root.quaternion).invert().multiply(this.camera.quaternion); }
  }
  _resolveContacts(attacker, state) {
    if (!this.running) return;
    const targets = attacker.hero ? this.enemies : this.mode === 'story' ? [this.hero, ...this.enemies].filter(f => f !== attacker && f.team !== attacker.team) : [this.hero];
    for (const attack of state.attacks) this._resolveSceneContacts(attacker, state, attack);
    for (const attack of state.attacks) for (const target of targets) {
      const key = `${attack.index}:${target.id}`; if (!this.running || target.dead || target.disposed || target.scriptRemoved || attacker.attackHits.has(key)) continue;
      const points = [];
      for (const name of attack.bones) {
        if (name === 'weapon' && attacker.weaponModel) { const box = new THREE.Box3().setFromObject(attacker.weaponModel); points.push(box.getCenter(v3()), box.min.clone(), box.max.clone()); }
        else { const bone = attacker.character.getAttachment(name); if (bone) points.push(bone.getWorldPosition(v3())); }
      }
      if (!points.length) continue;
      const center = target.root.position.clone().add(v3(0, 1.35, 0));
      const contact = points.find(p => Math.hypot(p.x - center.x, p.z - center.z) < .9 && Math.abs(p.y - center.y) < 1.45);
      if (!contact) continue;
      attacker.attackHits.add(key); this._applyNativeHit(attacker, target, state, attack, contact);
    }
  }
  _applyNativeHit(attacker, target, state, attack, contact, extra = {}) {
    if (!this.running || target.dead || target.disposed || target.scriptRemoved) return false;
    target.contacts = (target.contacts || 0) + 1; if (attacker.hero) this.contactHits++;
    const raw = { targetValue: attack.targetvalue, targetMove: attack.targetmove, defenseValue: attack.defensevalue, defenseMove: attack.defensemove, attackType: attack.attacktype, targetPose: attack.targetpose, moveRecord: this.combatData.moveRecords.get(state.poseId), weaponRecord: attacker.weaponRecord || this.combatData.weaponRecords.get(NATIVE_WEAPONS[attacker.weapon]?.model) };
    const damageContext = { attack, raw, attacker, target, weapon: attacker.weapon, guarded: target.guard, poseId: state.poseId };
    const damage = this.damageResolver?.(damageContext);
    if (Number.isFinite(damage) && damage >= 0) {
      const hpBefore = target.hp; target.hp = Math.max(0, target.hp - damage); if (attacker.hero) this.totalDamage += hpBefore - target.hp;
      const nativeResult = damageContext.nativeResult;
      if (nativeResult) target.rage = clamp((target.rage || 0) + (nativeResult.guarded ? nativeResult.victimRage : Math.floor(14 * (hpBefore - target.hp) / 100)), 0, 100);
      this._emit(String(Math.round(damage)), 'hit', damage, contact, { poseId: state.poseId, raw, ...extra });
      if (target.hp <= 0) this._kill(target);
    } else { const name = raw.moveRecord?.name || state.pose.label || '兵刃交锋'; this._emit(attacker.hero ? `${name} · 命中` : `${name} · 对手命中`, 'hit', undefined, contact, { poseId: state.poseId, raw, damagePending: true, ...extra }); }
    const prefix = { sword: 'W00', blade: 'W05', spear: 'W07', dagger: 'W01', dart: 'W03' }[attacker.weapon];
    this._soundDefinition(`${prefix}${target.guard ? 'GD' : 'BL'}${String(attack.targetpose || 90).padStart(3, '0')}`); this._hud(); return true;
  }
  _resolveSceneContacts(attacker, state, attack) {
    if (!this.missionHost || !this.running || !this.currentMap.props) return;
    const objects = this.currentMap.props.getInstancesNear(attacker.root.position.x, attacker.root.position.z, 7);
    if (!objects.length) return;
    // Cast through actual original collision triangles toward source attack
    // bones. Contact generation is a host adapter; the scene damage argument
    // follows the independently recovered 004af570 -> OnAttack numeric path.
    const origin = attacker.root.position.clone().add(v3(0, 1.3, 0)), points = [];
    for (const name of attack.bones) {
      if (name === 'weapon' && attacker.weaponModel) {
        const box = new THREE.Box3().setFromObject(attacker.weaponModel); points.push(box.min.clone(), box.max.clone(), box.getCenter(v3()));
      } else { const bone = attacker.character.getAttachment(name); if (bone) points.push(bone.getWorldPosition(v3())); }
    }
    for (const point of points) {
      const direction = point.clone().sub(origin), length = direction.length(); if (length < .01) continue;
      this.raycaster.set(origin, direction.normalize()); this.raycaster.far = length + .12;
      const hit = this.raycaster.intersectObjects(objects.flatMap(o => o.colliders.map(c => c.collider)), false)[0]; this.raycaster.far = Infinity;
      const object = hit?.object.userData.nativeSceneInstance; if (!object) continue;
      const key = `${attack.index}:scene:${object.name}`; if (attacker.attackHits.has(key)) continue;
      if (!this.missionHost.sceneVm.hasFunction(`${object.name}_OnAttack`)) continue;
      attacker.attackHits.add(key);
      const context = { attacker, object, state, attack, point: hit.point.clone() };
      const damage = this.sceneDamageResolver?.(context);
      if (Number.isFinite(damage) && damage >= 0) this.missionHost.sceneItemAttack(object.name, attacker.scriptId, damage);
      else this.onEvent({ type: 'scene-contact', objectName: object.name, attackerId: attacker.scriptId, poseId: state.poseId, damagePending: true });
    }
  }
  _kill(target) {
    if (target.dead) return; target.dead = true; target.respawn = this.mode === 'story' ? Infinity : 3; target.combat.play(NATIVE_LOCOMOTION.dead, { force: true });
    if (target.hero) this.deaths++; else this.kills++;
    if (this.locked === target) this.locked = null;
  }
  _separateCharacters(dt) {
    const fighters = [this.hero, ...this.enemies].filter(f => !f.dead && !f.disposed && !f.scriptRemoved), diameter = this.hostPhysics.radius * 2 + .25;
    for (let i = 0; i < fighters.length; i++) for (let j = i + 1; j < fighters.length; j++) {
      const a = fighters[i], b = fighters[j]; if (Math.abs(a.root.position.y - b.root.position.y) > 2) continue;
      let dx = b.root.position.x - a.root.position.x, dz = b.root.position.z - a.root.position.z, distance = Math.hypot(dx, dz);
      if (distance >= diameter) continue;
      if (distance < .001) { const angle = j * 2.4; dx = Math.sin(angle); dz = Math.cos(angle); distance = 1; } else { dx /= distance; dz /= distance; }
      const correction = Math.min(diameter - Math.min(distance, diameter), dt * 5), aWeight = a.hero ? .08 : b.hero ? .92 : .5, bWeight = 1 - aWeight;
      for (const [f, amount] of [[a, -correction * aWeight], [b, correction * bWeight]]) {
        if (!this._horizontalBlocked(f.root.position, dx * amount, 0)) f.root.position.x += dx * amount;
        if (!this._horizontalBlocked(f.root.position, 0, dz * amount)) f.root.position.z += dz * amount;
      }
    }
  }
  _finish(win) { if (!this.running) return; this.running = false; this.projectiles?.clear('match-end'); this.keys.clear(); this.onEnd({ win, kills: this.kills, deaths: this.deaths, damage: this.totalDamage, time: Math.round(this.matchElapsed), nativeData: true, damageVerified: !!this.damageResolver, mode: this.mode, mission: this.missionState, reason: this.storyResult?.reason }); }
  _nameplate(f) {
    const c = document.createElement('canvas'); c.width = 256; c.height = 64; const ctx = c.getContext('2d'); ctx.font = '28px serif'; ctx.fillStyle = '#eee7cf'; ctx.textAlign = 'center'; ctx.fillText(f.name, 128, 43);
    const g = new THREE.Group(); const label = new THREE.Mesh(new THREE.PlaneGeometry(1.7, .425), new THREE.MeshBasicMaterial({ map: new THREE.CanvasTexture(c), transparent: true, depthWrite: false })); g.add(label); g.position.y = 3.1; f.root.add(g); f.nameplate = g;
  }
  _disposeNameplate(f) { if (!f.nameplate) return; f.nameplate.traverse(o => { o.geometry?.dispose(); o.material?.map?.dispose(); o.material?.dispose(); }); f.nameplate.removeFromParent(); }
  _safeCameraPosition(target, desired) {
    const ray = desired.clone().sub(target), distance = ray.length(); if (distance < 1e-6) return desired.clone();
    ray.multiplyScalar(1 / distance); this.raycaster.set(target, ray); this.raycaster.far = distance;
    const hit = this.raycaster.intersectObjects(this._collisionCandidates(target.x, target.z, distance), false).find(h => h.distance > .001); this.raycaster.far = Infinity;
    // A hard 1.8m floor pushed the camera through walls closer than 1.8m.
    // Keep the ray on this side of the actual surface, including tight corners.
    if (!hit) return desired.clone();
    const safe = Math.max(Math.min(.3, hit.distance * .5), hit.distance - .35);
    return target.clone().addScaledVector(ray, safe);
  }
  _canReachItem(actor, item) {
    const from = actor.root.position.clone().add(v3(0, 1, 0)), to = item.root.position.clone().add(v3(0, .4, 0));
    const direction = to.sub(from), distance = direction.length(); if (distance < .05) return true;
    this.raycaster.set(from, direction.multiplyScalar(1 / distance)); this.raycaster.far = distance;
    const blocked = this.raycaster.intersectObjects(this._collisionCandidates(from.x, from.z, distance + .2), false)
      .some(hit => hit.distance > .05 && hit.distance < distance - .1 && hit.object.userData.nativeSceneInstance !== item);
    this.raycaster.far = Infinity; return !blocked;
  }
  _tickCamera(dt) {
    if (!this.hero || !this.currentMap) return;
    const p = this.hero.root.position, eye = p.clone().add(v3(0, 1.65, 0)), target = eye.clone(); let desired;
    // Carry the camera rig with physical ascent/descent before smoothing its
    // framing. Two independent lerps otherwise lag a fast jump by several
    // body lengths, especially with a short camera distance.
    const verticalStep = Number.isFinite(this.cameraFollowY) ? p.y - this.cameraFollowY : 0;
    this.cameraFollowY = p.y;
    if (this.running || this.paused) { this.camera.position.y += verticalStep; this.cameraTarget.y += verticalStep; }
    if (!this.running && !this.paused) {
      target.add(v3(-2.8, .1, 0)); desired = p.clone().add(v3(5.2 + Math.sin(this.elapsed * .04) * .25, 3.5, 8.5));
    } else {
      const opponent = this.locked;
      // Lock-on and near-wall rendering are browser interaction adapters. They
      // do not alter the original actor pose, hit resolution or scene geometry.
      if (opponent && !opponent.dead && !opponent.disposed && (this.elapsed || 0) >= (this.cameraManualUntil || 0)) {
        const toEnemy = opponent.root.position.clone().sub(p), desiredAngle = Math.atan2(-toEnemy.x, -toEnemy.z);
        if (!this.paused) this.cameraAngle += Math.atan2(Math.sin(desiredAngle - this.cameraAngle), Math.cos(desiredAngle - this.cameraAngle)) * (1 - Math.exp(-dt * 3));
        const focus = opponent.root.position.clone().add(v3(0, 1.35, 0)).sub(eye).multiplyScalar(.25);
        if (focus.length() > 3) focus.setLength(3);
        target.copy(this._safeCameraPosition(eye, eye.clone().add(focus)));
      }
      desired = target.clone().add(v3(Math.sin(this.cameraAngle) * this.cameraDistance, Math.sin(this.cameraPitch) * this.cameraDistance + 1, Math.cos(this.cameraAngle) * this.cameraDistance));
    }
    this.cameraTarget.lerp(target, 1 - Math.exp(-dt * 8));
    const safe = this._safeCameraPosition(this.cameraTarget, desired);
    this.camera.position.lerp(safe, 1 - Math.exp(-dt * 10));
    // Recheck the interpolated point too: smoothing must not cross a wall while
    // the player or locked target moves around a corner.
    this.camera.position.copy(this._safeCameraPosition(this.cameraTarget, this.camera.position)); this.camera.lookAt(this.cameraTarget);
    this.hero.root.visible = !this.running || this.camera.position.distanceTo(eye) >= 2.1;
  }
  _hud() {
    if (!this.hero) return; const f = this.hero, target = this.locked || (this.running ? this._nearest(18) : null), b = this.currentMap?.bounds;
    let enemy = null;
    if (target) {
      const delta = target.root.position.clone().sub(f.root.position), view = this.camera.getWorldDirection(v3()); view.y = 0; view.normalize();
      const right = v3(-view.z, 0, view.x);
      enemy = { name: target.name, hp: target.hp, maxHp: target.maxHp, distance: delta.length(), bearing: Math.atan2(delta.dot(right), delta.dot(view)) };
    }
    const item = this.running && this.mode === 'story' ? this.items?.peek(f) : null;
    const pickup = item ? { name: item.name, heal: item.heal, full: item.full, distance: item.distance, objectName: item.objectName } : null;
    this.onUpdate({ pickup, hp: f.hp, maxHp: f.maxHp, rage: f.rage, hits: this.contactHits, kills: this.kills, deaths: this.deaths, time: this.matchElapsed, enemy, combo: f.combat.attacking ? f.combat.combo : 0, locked: !!this.locked, position: { x: f.root.position.x, z: f.root.position.z }, enemies: this.enemies.filter(e => !e.dead).map(e => ({ x: e.root.position.x, z: e.root.position.z })), weapon: f.weapon, weaponId: f.weaponId, weaponName: f.weaponName, mission: this.missionState, paused: this.paused, mapBounds: b ? { minX: b.min.x, maxX: b.max.x, minZ: b.min.z, maxZ: b.max.z } : null, native: { pose: f.combat.timeline?.pose.id, source: f.character.source, frame: f.character.frame, contacts: this.contactHits, damagePending: !this.damageResolver, hpSourcePending: !f.hpSourceVerified, physicsPending: true, sceneDamagePending: this.mode === 'story' && !this.sceneDamageResolver, projectilePending: false, projectileSpecialsPending: true, projectilePhysics: NATIVE_DART_PROFILE.provenance.flight, projectiles: this.projectiles?.size || 0, missionVmPending: this.mode === 'story' ? !this.missionHost?.started : false } });
  }
  _emit(text, type = 'info', amount, point, extra = {}) { const p = point?.clone().project(this.camera); this.onEvent({ text, type, amount, x: p ? (p.x + 1) / 2 : undefined, y: p ? (1 - p.y) / 2 : undefined, ...extra }); }
  _frame() {
    if (this.disposed) return; this.raf = requestAnimationFrame(this._frame); const dt = Math.min(.05, this.clock.getDelta()); this.elapsed += dt;
    if (this.hero && !this.paused) {
      if (this.running) this.missionHost?.update(dt); this.currentMap.props?.update(dt);
      if (this.running) { this.matchElapsed += dt; this._updateFighter(this.hero, dt); for (const f of this.enemies) { if (!this.running) break; this._updateFighter(f, dt); } this._separateCharacters(dt); if (this.running) this.projectiles?.update(dt); }
      else { const state = this.hero.combat.update(dt); if (state) this.hero.character.setPoseFrame(state.source, state.frame); }
      for (let i = this.effects.length - 1; i >= 0; i--) { const e = this.effects[i]; e.life -= dt; e.mesh.material.opacity = Math.max(0, e.life / .14); if (e.life <= 0) { e.mesh.removeFromParent(); e.mesh.geometry.dispose(); e.mesh.material.dispose(); this.effects.splice(i, 1); } }
      this.updateAccum += dt; if (this.updateAccum > .08) { this.updateAccum = 0; this._hud(); }
    }
    this._tickCamera(dt); this.renderer.render(this.scene, this.camera);
  }
  _bind() {
    const bind = (el, name, fn, options) => { el.addEventListener(name, fn, options); this._listeners.push(() => el.removeEventListener(name, fn, options)); };
    const keys = { KeyW: 'forward', ArrowUp: 'forward', KeyS: 'back', ArrowDown: 'back', KeyA: 'left', ArrowLeft: 'left', KeyD: 'right', ArrowRight: 'right', KeyJ: 'attack', KeyK: 'guard', Space: 'guard', KeyQ: 'lock', KeyE: 'switch', KeyL: 'jump', KeyF: 'pickup', KeyC: 'crouch', Digit1: 'weapon1', Digit2: 'weapon2', Digit3: 'weapon3', Digit4: 'weapon4', Digit5: 'weapon5' };
    bind(window, 'keydown', e => { if (!this.running || this.paused || document.querySelector('dialog[open]') || /INPUT|TEXTAREA|SELECT/.test(document.activeElement?.tagName)) return; const action = keys[e.code]; if (!action) return; e.preventDefault(); if (!e.repeat || ['forward', 'back', 'left', 'right', 'guard'].includes(action)) this.action(action); });
    bind(window, 'keyup', e => { if (keys[e.code]) this.action(keys[e.code], false); });
    bind(window, 'blur', () => { this.keys.clear(); this.pointer = null; if (this.hero) this.hero.guard = false; });
    bind(this.canvas, 'contextmenu', e => e.preventDefault());
    bind(this.canvas, 'pointerdown', e => { this._unlockAudio(); this.pointer = { x: e.clientX, y: e.clientY, startX: e.clientX, startY: e.clientY, button: e.button, moved: false }; this.canvas.setPointerCapture?.(e.pointerId); if (e.button === 2) this.action('jump'); });
    bind(this.canvas, 'pointermove', e => { const p = this.pointer; if (!p) return; if (Math.hypot(e.clientX - p.startX, e.clientY - p.startY) > 5) p.moved = true; if (p.moved && this.running && !this.paused) { this.cameraManualUntil = this.elapsed + 2; this.cameraAngle -= (e.clientX - p.x) * .005; this.cameraPitch = clamp(this.cameraPitch + (e.clientY - p.y) * .003, .15, .95); } p.x = e.clientX; p.y = e.clientY; });
    bind(this.canvas, 'pointerup', e => { if (this.pointer && !this.pointer.moved && this.pointer.button === 0) this.action('attack'); if (e.button === 2) this.action('guard', false); this.pointer = null; });
    for (const event of ['pointercancel', 'lostpointercapture']) bind(this.canvas, event, () => { this.pointer = null; this.action('guard', false); });
    bind(this.canvas, 'wheel', e => { if (!this.running) return; e.preventDefault(); this.cameraDistance = clamp(this.cameraDistance + e.deltaY * .008, 3.5, 18); }, { passive: false });
    bind(window, 'resize', () => this.resize());
  }
  resize() { const w = this.canvas.clientWidth || window.innerWidth, h = this.canvas.clientHeight || window.innerHeight; this.renderer.setSize(w, h, false); this.camera.aspect = w / Math.max(1, h); this.camera.updateProjectionMatrix(); }
  _unlockAudio() { if (this.muted) return; try { if (!this.audio) { this.audio = new (window.AudioContext || window.webkitAudioContext)(); this.master = this.audio.createGain(); this.master.gain.value = .25; this.master.connect(this.audio.destination); } if (this.audio.state === 'suspended') this.audio.resume(); } catch (_) {} }
  async _soundDefinition(id) {
    if (!id || this.muted || this.paused || !this.audio) return;
    const definition = this.effectDefinitions?.get(String(id).toLowerCase());
    const reference = definition?.soundReferences?.find(r => /fir/i.test(r)) || definition?.soundReferences?.[0];
    const file = reference && this.waveFiles?.get(reference.replace(/\.wav$/i, '').toLowerCase()); if (!file) return;
    try {
      if (!this.soundCache.has(file.id)) this.soundCache.set(file.id, fetch(new URL(file.url, originalRoot)).then(r => { if (!r.ok) throw new Error('Original WAV missing'); return r.arrayBuffer(); }).then(b => this.audio.decodeAudioData(b)).catch(error => { this.soundCache.delete(file.id); throw error; }));
      const buffer = await this.soundCache.get(file.id); if (this.muted || this.paused || this.disposed) return;
      const source = this.audio.createBufferSource(); source.buffer = buffer; source.connect(this.master); source.start(); source.onended = () => source.disconnect();
    } catch (error) { console.warn('Original sound could not be played:', file.id, error); }
  }
  dispose() {
    this.projectiles?.dispose(); this.items?.dispose(); this.missionHost?.dispose(); this.disposed = true; cancelAnimationFrame(this.raf); this._listeners.forEach(fn => fn()); this.hero?.character.dispose(); this.enemies.forEach(f => { this._disposeNameplate(f); f.character.dispose(); });
    for (const data of this.mapData.values()) this._disposeMap(data); this.mapData.clear(); this.mapCache.clear();
    const geometries = new Set(), materials = new Set(), textures = new Set(); this.scene.traverse(o => { if (o.geometry) geometries.add(o.geometry); for (const m of o.material ? Array.isArray(o.material) ? o.material : [o.material] : []) { materials.add(m); if (m.map) textures.add(m.map); } });
    geometries.forEach(g => g.dispose()); materials.forEach(m => m.dispose()); textures.forEach(t => t.dispose()); this.collisionMaterial.dispose(); this.renderer.dispose(); this.audio?.close();
  }
}

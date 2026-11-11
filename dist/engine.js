import { traversalTap, NATIVE_ROLL_POSES, nativeDashPose, NATIVE_CROUCH_POSES, NATIVE_JUMP_POSES, nativeTraversalDirection } from './native-traversal.js';
import { FixedStepClock } from './fixed-step.js';
import { FrameMeter, RenderScaleController, createFrameOverlay } from './frame-meter.js';
import { StaticColliderIndex } from './collision-index.js';
import { bindLocalPlayerControl, clearPlayerCommands } from './player-control.js';
import { createMouseLook, turnMouseCamera } from './mouse-look.js';
import { bindKeyboard, defaultBindings } from './keybindings.js';
import * as THREE from './vendor/three.module.js';
import { findNativeEnemy } from './native-awareness.js';
import { NativeNpcCombat, nativeNpcMove, nativeNpcInRange, nativeNpcFacing } from './native-npc-combat.js';
import { loadGmb, loadGmc } from './gmc-loader.js';
import { loadNativeCharacter, NATIVE_CHARACTERS, NATIVE_APPEARANCES } from './native-character.js';
import { loadNativeCombat, NativeCombatController, NATIVE_WEAPONS, NATIVE_LOCOMOTION, createNativeDamageResolver, createNativeSceneDamageResolver, nativeReactionParameters, nativeHitAngle, nativeHitSelection, nativeGuardPose } from './native-combat.js';
import { NATIVE_MOVE_CATALOG } from './native-move-catalog.js';
import { recordNativeDirection, selectNativeMove, NATIVE_RECOVERY_INPUT_WINDOW } from './native-input.js';
import { loadOriginalSceneModels } from './native-scene-models.js';
import { NativeMissionHost } from './native-mission-host.js';
import { getNativeMission } from './native-missions.js';
import { createNativeEnvironment } from './native-environment.js';
import { NativeWeather } from './native-weather.js';
import { NativeItemSystem, useNativeScriptItem, useNativeAttackItem, useNativeSelfItem, nativeMovementScale, nativeRageMaximum, updateNativeScriptItems, clearNativeScriptItems } from './native-items.js';
import { QIANKUN_MODE_NAMES } from './native-weapon-menu.js';
import { NativeProjectileSystem, NATIVE_DART_PROFILE, NativeMusketSystem, NATIVE_MUSKET_PROFILE, NativeWheelSystem, NATIVE_WHEEL_PROFILE } from './native-projectiles.js';
import { NativeImpactFeedback } from './native-impact-feedback.js';
import { loadNativeRageVfx } from './native-rage-vfx.js';
import { loadNativeEffectManifest } from './native-effect-transforms.js';
import { NativeEffectContacts } from './native-effect-contacts.js';
import { bindQiankunGrip } from './native-qiankun-grip.js';
import { createButterflySword, createSwordEnvironment, disposeButterflySword } from './butterfly-sword.js';
import { createPhoenixSpear, disposePhoenixSpear } from './phoenix-spear.js';
import { loadRaidenSword, disposeRaidenSword } from './raiden-sword.js';
import { ButterflySwordVfx } from './butterfly-vfx.js';
import { loadQiyunCourtyard, QIYUN_MAP } from './qiyun-courtyard.js';

const SCALE = .08;
const MAP_IDS = { sifang: 'sn06', cave: 'sn01', forge: 'sn10' };
const clamp = THREE.MathUtils.clamp;
const v3 = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
const nativePosition = p => v3(p[0] * SCALE, p[2] * SCALE, -p[1] * SCALE);
const surfaceY = hit => hit.face ? hit.face.normal.clone().transformDirection(hit.object.matrixWorld).y : 0;
const flatDistance = (a, b) => Math.hypot(a.x - b.x, a.z - b.z);
const originalRoot = new URL('./assets/original/', import.meta.url);

// Original POS names use spaces ("bad R Foot"), while the supplied BNC uses
// underscores ("bad_R_Foot"). Resolve that spelling difference at the attack
// boundary, retaining exact native names and all character/skin identities.
export function getNativeAttackAttachment(character, name) {
  return character.getAttachment(name) || character.getAttachment(name.trim().replace(/\s+/g, '_'));
}

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
    this.baseLights = this.scene.children.filter(object => object.isLight);
    this.frameMeter = new FrameMeter(); this.frameOverlay = createFrameOverlay(canvas.ownerDocument);
    this.renderScale = new RenderScaleController(this.renderer.getPixelRatio());
    this.clock = new THREE.Clock(); this.simulationClock = new FixedStepClock(); this.elapsed = 0; this.updateAccum = 0; this.running = false; this.paused = false;
    this.map = 'sifang'; this.weapon = 'sword'; this.swordStyle = 'butterfly'; this.spearStyle = 'original'; this.infiniteRage = false; this.characterId = 0; this.characterAppearance = 'original'; this.appearanceRequest = 0; this.actorSerial = 0; this.mode = 'training'; this.enemies = []; this.keys = new Set();
    this.cameraManualUntil = 0; this.cameraAngle = .4; this.cameraPitch = .45; this.cameraDistance = 8; this.cameraTarget = v3(); this.locked = null;
    this.raycaster = new THREE.Raycaster(); this.collisionMaterial = new THREE.MeshBasicMaterial({ side: THREE.DoubleSide });
    this.mapCache = new Map(); this.mapData = new Map(); this.pendingMaps = new Set(); this.weaponCache = new Map(); this.soundCache = new Map(); this.effects = []; this._listeners = []; this.mapRequest = 0; this.characterRequest = 0; this.sessionRequest = 0; this.directionBuffer = [];
    this.kills = 0; this.deaths = 0; this.totalDamage = 0; this.contactHits = 0; this.time = 0; this.matchElapsed = 0;
    bindLocalPlayerControl(this);
    // Adapter constants are explicit and provisional until recovered from Meteor.exe.
    this.hostPhysics = { speed: 100 * SCALE, gravity: 34, jumpVelocity: 12, radius: .4, step: .55, projectile: NATIVE_DART_PROFILE };
    this.impactFeedback = new NativeImpactFeedback(this.scene);
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
    this.muskets = new NativeMusketSystem({ bodyRadius: this.hostPhysics.radius,
      getTargets: () => [this.hero, ...this.enemies].filter(Boolean),
      getColliders: (from, to) => {
        if (!this.currentMap) return [];
        const center = from.clone().add(to).multiplyScalar(.5), radius = from.distanceTo(to) / 2 + 1;
        const machines = this.currentMap.props?.getInstancesNear(center.x, center.z, radius, { attack: true })
          .filter(object => this.missionHost?.sceneVm.hasFunction(`${object.name}_OnAttack`)) || [];
        return [...new Set([...this._collisionCandidates(center.x, center.z, radius), ...machines.flatMap(object => object.colliders.map(c => c.collider))])];
      },
      onActorHit: (shot, target, point) => this._applyNativeHit(shot.context.attacker, target, shot.context.state, shot.context.attack, point, { musketId: shot.id }),
      onWorldHit: (shot, hit) => this._projectileWorldHit(shot, hit)
    });
    this.wheels = new NativeWheelSystem({ scene: this.scene, bodyRadius: this.hostPhysics.radius,
      getTargets: () => [this.hero, ...this.enemies].filter(Boolean),
      getColliders: (from, to, radius) => { const center = from.clone().add(to).multiplyScalar(.5); return this.currentMap ? this._collisionCandidates(center.x, center.z, from.distanceTo(to) / 2 + radius + 1) : []; },
      onActorHit: (shot, target, point) => this._applyNativeHit(shot.context.attacker, target, shot.context.state, shot.context.attack, point, { wheelId: shot.id }),
      onWorldHit: (shot, hit) => this._projectileWorldHit(shot, hit)
    });
  }
  _initializeEffectContacts(manifest) {
    this.effectContacts?.dispose();
    this.effectContacts = new NativeEffectContacts({ manifest, bodyRadius: this.hostPhysics.radius });
  }
  _launchNativeProjectiles(f, state) {
    if (f.weapon === 'musket') { this._fireNativeMusket(f, state); return; }
    if (f.weapon === 'wheel') { this._launchNativeWheel(f, state); return; }
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
  _fireNativeMusket(f, state) {
    if (!NATIVE_MUSKET_PROFILE.poseIds.includes(state.poseId) || !f.weaponModel || !this.running) return;
    const origin = f.character.getAttachment('d_wpnR').getWorldPosition(v3());
    const target = f.hero ? this.locked || this._nearest(32) : f.scriptControl?.attackTarget;
    const direction = target && !target.dead ? target.root.position.clone().add(v3(0, 1.35, 0)).sub(origin).normalize() : v3(Math.sin(f.root.rotation.y), 0, Math.cos(f.root.rotation.y));
    const attacker = { id: f.id, hero: f.hero, scriptId: f.scriptId, root: f.root, name: f.name, weapon: f.weapon, weaponId: f.weaponId,
      weaponRecord: f.weaponRecord, nativeStats: { ...f.nativeStats }, activeItems: [...(f.activeItems || [])], team: f.team, teamMask: f.teamMask };
    // Explicit browser aim/range adapter until the original ballistic path is
    // recovered. Never use the dart's speed, lifetime or weapon mesh as a bullet.
    const shots = this.muskets?.firePose({ owner: f, state, position: origin, direction, range: 80,
      sourcePosition: f.root.position.clone().add(v3(0, 1.35, 0)), context: { attacker } });
    if (shots?.length) this._soundDefinition(state.pose.raw.fields.effectid);
  }
  _launchNativeWheel(f, state) {
    if (!NATIVE_WHEEL_PROFILE.poseIds.includes(state.poseId) || !f.weaponModel || !this.running) return;
    for (const attack of state.attacks) {
      const key = `release:${state.serial}:${attack.index}`; if (f.attackHits.has(key) || this.wheels?.hasOwner(f)) continue;
      const origin = f.character.getAttachment('d_wpnR').getWorldPosition(v3());
      const target = f.hero ? this.locked || this._nearest(24) : f.scriptControl?.attackTarget;
      const direction = target && !target.dead ? target.root.position.clone().add(v3(0, 1.35, 0)).sub(origin).normalize() : v3(Math.sin(f.root.rotation.y), 0, Math.cos(f.root.rotation.y));
      const visual = f.weaponModel.clone(true); visual.visible = true; visual.rotation.set(0,0,0); visual.position.set(0,0,0); visual.scale.setScalar(SCALE);
      visual.position.sub(new THREE.Box3().setFromObject(visual).getCenter(v3()));
      const attacker = { id:f.id, hero:f.hero, scriptId:f.scriptId, root:f.root, name:f.name, weapon:f.weapon, weaponId:f.weaponId,
        weaponRecord:f.weaponRecord, nativeStats:{...f.nativeStats}, activeItems:[...(f.activeItems||[])], team:f.team, teamMask:f.teamMask };
      const shot = this.wheels?.spawn({ owner:f, position:origin, direction, visual, sourcePosition:f.root.position.clone().add(v3(0,1.35,0)),
        context:{attacker,state:{poseId:state.poseId,pose:state.pose,source:state.source,serial:state.serial},attack:{...attack}} });
      if (shot) { f.attackHits.add(key); f.weaponModel.visible = false; this._soundDefinition(state.pose.raw.fields.effectid); }
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
  setNativeScene(name, ...values) {
    this.weather ||= new NativeWeather(this.scene);
    return this.weather.set(name, ...values);
  }
  clearNativeScene() { this.weather?.clear(); }
  async _initialize() {
    const effectContactsReady = loadNativeEffectManifest().then(manifest => {
      if (!this.disposed) this._initializeEffectContacts(manifest);
    }).catch(error => console.warn('原技能攻击范围暂未能载入：', error));
    const rageVfxReady = loadNativeRageVfx(this.scene).then(vfx => {
      if (this.disposed) vfx.dispose(); else this.rageVfx = vfx;
    }).catch(error => console.warn('怒气技能特效暂未能载入：', error));
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
        this._soundDefinition('getitem');this.rageVfx?.playItem(result.actor,'getitem');
        this._emit(`${result.name} · ${result.healed>0?'气血 +'+result.healed:result.description}${result.refreshed?'（已刷新）':''}`, 'pickup');
      }
    });
    this.effectDefinitions = new Map((manifest.sounds?.effectDefinitions || []).map(e => [e.id.toLowerCase(), e]));
    this.waveFiles = new Map((manifest.sounds?.effects || []).map(e => [e.id.toLowerCase(), e]));
    const [hero] = await Promise.all([this._createFighter(0, '孟星魂', true), this._loadMap('sifang')]);
    this.hero = hero; this.scene.add(hero.root); this._placeFighter(hero, this.currentMap.spawns[0]); await this._equip(hero, this.weapon);
    this.cameraTarget.copy(hero.root.position).add(v3(0, 1.6, 0)); this._tickCamera(1);
    await Promise.all([rageVfxReady, effectContactsReady]);
    this._loadStatus('原版地图、人物、兵器与动作数据已就绪'); this._hud(); return this;
  }
  async _loadMap(name) {
    this.rageVfx?.clear(); this.effectContacts?.clear(); this.projectiles?.clear('map-change'); this.muskets?.clear(); this.wheels?.clear();
    this.clearNativeScene();
    this.items?.reset();
    name = MAP_IDS[name] || /^sn\d+$/.test(name) || name === QIYUN_MAP.id ? name : 'sifang'; const request = ++this.mapRequest, id = MAP_IDS[name] || name;
    const label = id === QIYUN_MAP.id ? QIYUN_MAP.name : this.manifest.maps.find(m => m.id === id)?.name || id; this._loadStatus(`正在读取${label}…`);
    if (!this.mapCache.has(id)) {
      this.pendingMaps.add(id);
      this.mapCache.set(id, this._readMap(id).then(result => { this.pendingMaps.delete(id); if (this.disposed) this._disposeMap(result); else this.mapData.set(id, result); return result; }).catch(error => { this.pendingMaps.delete(id); this.mapCache.delete(id); throw error; }));
    } else { const cached = this.mapCache.get(id); this.mapCache.delete(id); this.mapCache.set(id, cached); }
    const result = await this.mapCache.get(id);
    if (request !== this.mapRequest || this.disposed) { this._trimMapCache(); return result; }
    if (this.currentMap?.model) this.currentMap.model.visible = false;
    this.currentMap = result; this.map = name; result.model.visible = true; if (!result.model.parent) this.scene.add(result.model);
    result.props?.reset?.();
    this._applyMapPresentation();
    this.camera.far = Math.max(1500, result.bounds.getSize(v3()).length() * 4); this.camera.updateProjectionMatrix();
    if (this.hero && !this.running) this._placeFighter(this.hero, result.spawns[0]);
    this._trimMapCache();
    return result;
  }
  _applyMapPresentation() {
    const data = this.currentMap; if (!data) return;
    this.scene.fog = data.fog || null;
    this.scene.background.setHex(data.background ?? (data.id === 'sn01' ? 0x080c0e : ['sn10', 'sn14'].includes(data.id) ? 0x24120c : 0x263038));
    for (const light of this.baseLights || []) light.visible = !data.enhanced;
    this.renderer.toneMapping = data.enhanced ? THREE.ACESFilmicToneMapping : THREE.NoToneMapping;
    this.renderer.toneMappingExposure = 1;
    this.renderer.shadowMap.enabled = !!data.enhanced && this.quality !== 'low';
    this.renderer.shadowMap.type = THREE.PCFSoftShadowMap;
  }
  _disposeMap(data) {
    data.onDispose?.();
    const geometries = new Set(), materials = new Set(), textures = new Set();
    data.model.traverse(object => {
      if (object.isInstancedMesh) object.dispose();
      if (object.geometry) geometries.add(object.geometry);
      for (const material of object.material ? Array.isArray(object.material) ? object.material : [object.material] : []) {
        if (material !== this.collisionMaterial) materials.add(material); for (const value of Object.values(material)) if (value?.isTexture) textures.add(value);
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
    if (id === QIYUN_MAP.id) return loadQiyunCourtyard({ collisionMaterial: this.collisionMaterial });
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
    const environment = createNativeEnvironment(des?.objects || [], model);
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
    return { id, entry, metadata, model, colliders, props, environment, sceneObjects: props.instances, bounds, points, spawns, skippedSpawns };
  }
  async _createFighter(characterId, name, hero = false, team = null) {
    const character = await loadNativeCharacter(characterId, { scale: SCALE, inPlace: true, appearance: hero ? this.characterAppearance : 'original' });
    if (hero && character.appearanceStatus.requested !== (this.characterAppearance || 'original')) await character.setAppearance(this.characterAppearance || 'original');
    const f = { character, root: character.group, id: ++this.actorSerial, modelId: characterId, name: name || NATIVE_CHARACTERS.find(c => c.id === characterId)?.name || `角色 ${characterId}`, hero, team, teamMask: team, hp: 1000, maxHp: 1000, rage: 0, weapon: this.weapon, velocity: v3(), vy: 0, grounded: true, guard: false, dead: false, respawn: 0, attackHits: new Set(), lastSerial: 0, contacts: 0, heldPose: null };
    const combatData = character.combatPoses ? { ...this.combatData, poses: character.combatPoses } : this.combatData;
    // The physics track is d_base, not the pelvis' local sway. 004ce850
    // consumes that scene-motion delta independently of skin deformation.
    f.combat = new NativeCombatController(combatData, { weapon: this.weapon, sampleRoot: character.sampleSceneMotion, scale: SCALE });
    f.combat.play(NATIVE_WEAPONS[this.weapon].stance, { loop: true, force: true });
    if (!hero) { if (this.combatData.npcAi) f.npcCombat = new NativeNpcCombat(this.combatData.npcAi); this._nameplate(f); } return f;
  }
  _placeFighter(f, spawn) {
    this.rageVfx?.clearActor(f);
    this.effectContacts?.clearActor(f);
    clearNativeScriptItems(f);
    f.nativeJump = null; f.jumpSequence = null;
    const p = spawn?.position || this.currentMap.spawns[0].position; f.root.position.copy(p);
    // D_user DES quaternions use wxyz in the native Z-up coordinates.
    // Project their facing onto the walking plane instead of facing the player.
    const rotation = spawn?.rotation;
    if (rotation?.length === 4) {
      const forward = v3(0, -1, 0).applyQuaternion(new THREE.Quaternion(rotation[1], rotation[2], rotation[3], rotation[0]).normalize());
      f.root.rotation.set(0, Math.atan2(forward.x, -forward.y), 0);
    }
    const ground = this._ground(p.x, p.z, p.y + 3);
    if (ground) f.root.position.y = ground.point.y + .015;
    f.maxHp = f.scriptConfig?.HP ?? f.scriptConfig?.PlayerHP ?? this.currentMap.metadata.level?.integers.PlayerHP ?? 1000; f.hpSourceVerified = true;
    f.velocity.set(0, 0, 0); f.vy = 0; f.grounded = true; f.guard = false; f.dead = false; f.environmentDeath = null; f.hitstop = 0; f.scriptCrouched = false; f.scriptItems = []; f.root.visible = true; f.hp = f.maxHp; f.rage = f.hero && this.infiniteRage ? 100 : 0; f.contacts = 0; f.previousPosition?.copy(f.root.position);
    clearPlayerCommands(this._controlFor(f));
    f.awarenessTarget = null; f.npcCombat?.reset();
    f.heldPose = null; f.attackHits.clear(); f.combat.play(f.combat.stance ?? NATIVE_WEAPONS[f.weapon].stance, { loop: true, force: true });
  }
  async _readWeapon(modelId) {
    const entry = this.weaponModels.get(modelId.toLowerCase()); if (!entry) throw new Error(`Original weapon ${modelId} not extracted`);
    const base = new URL('weapon-models/', originalRoot), textureMap = {}, textureAlphaMap = {};
    for (const t of entry.textures) { const url = t.url || t.frames?.[0]?.url; if (url) textureMap[t.reference.toLowerCase()] = new URL(url, base).href; if (t.alphaMask) textureAlphaMap[t.reference.toLowerCase()] = new URL(t.alphaMask, base).href; }
    const modelURL = new URL(entry.modelUrl, base), loader = entry.format === 'GMB' ? loadGmb : loadGmc;
    return loader(modelURL.href, { scale: 1, groundZ: 0, textureMap, textureAlphaMap, texturePath: new URL('textures/', modelURL).href, unlit: true, name: modelId, source: `local:cmodel/${modelId}` });
  }
  async _loadRaidenSwordTemplate() {
    if (this.raidenSwordTemplate) return this.raidenSwordTemplate;
    return this.raidenSwordLoad ||= loadRaidenSword({ environment: this.butterflyEnvironment }).then(template => {
      if (this.disposed) { disposeRaidenSword(template); return null; }
      this.raidenSwordTemplate = template; return template;
    }).catch(error => {
      this.raidenSwordLoad = null;
      console.warn('雷电影佩刀未能载入：', error);
      if (this.swordStyle === 'raiden') this._emit('雷电影佩刀载入失败，暂用原版长剑', 'info');
      return null;
    });
  }
  async _equip(f, selection) {
    this.rageVfx?.clearActor(f);
    this.effectContacts?.clearActor(f);
    const request = f.equipRequest = (f.equipRequest || 0) + 1;
    const item = this.weaponItems.get(typeof selection === 'number' ? selection : NATIVE_WEAPONS[selection]?.weaponId);
    if (!item || !item.available) throw new Error(`Original weapon item ${selection} unavailable`);
    const prefix = item.modelId.toLowerCase().split('_')[0], name = Object.keys(NATIVE_WEAPONS).find(key => NATIVE_WEAPONS[key].model.split('_')[0] === prefix);
    if (!name) throw new Error(`Original weapon action family ${item.modelId} has not been ported`);
    f.weaponPoseUnsubscribe?.(); f.weaponPoseUnsubscribe = null;
    f.weapon = name; f.weaponId = Number(item.itemId); f.weaponName = item.name; f.weaponRecord = this.combatData.weaponRecords.get(item.modelId.toLowerCase());
    f.combat.setWeapon(name); f.combat.play(NATIVE_WEAPONS[name].stance, { loop: true, force: true }); f.heldPose = NATIVE_WEAPONS[name].stance;
    if (f.hero) { this.directionBuffer = []; this.recoveryAttack = null; }
    if (f.butterflySword) { disposeButterflySword(f.butterflySword); if (f.hero) this.butterflyVfx?.bind(null); }
    f.raidenSword?.removeFromParent(); f.raidenSword = null;
    disposePhoenixSpear(f.phoenixSpear); f.phoenixSpear = null;
    for (const model of f.weaponModels || (f.weaponModel ? [f.weaponModel] : [])) model.removeFromParent(); f.weaponModels = []; f.weaponModel = null; f.butterflySword = null;
    const ids = item.modelIds.map(id => id.toLowerCase());
    for (const id of ids) if (!this.weaponCache.has(id)) this.weaponCache.set(id, this._readWeapon(id).catch(error => { this.weaponCache.delete(id); throw error; }));
    try {
      const [templates, gripManifest] = await Promise.all([Promise.all(ids.map(id => this.weaponCache.get(id))), name === 'qiankun' ? loadNativeEffectManifest() : null]);
      const models = templates.map(model => model.clone(true));
      if (this.disposed || f.disposed || request !== f.equipRequest) return;
      // GMC is converted Z-up→Y-up by the loader; attachments still use native
      // coordinates inside the character's scaled Z-up skeleton, so undo that.
      for (let i = 0; i < models.length; i++) {
        const model = models[i], hand = /l$/i.test(ids[i]) ? 'L' : 'R';
        model.rotation.x = Math.PI / 2;
        // Qiankun starts at the palm grips; its pose binding then seats the
        // blade in the sheath for closed/return phases.
        f.character.getAttachment(`d_wpn${hand}${name === 'qiankun' ? 'P' : ''}`).add(model);
        f.character.registerVisualAttachment?.(model,`d_wpn${hand}${name === 'qiankun' ? 'P' : ''}`);
      }
      f.weaponModels = models; f.weaponModel = models[0];
      if (name === 'qiankun') f.weaponPoseUnsubscribe = bindQiankunGrip(f, this.combatData, gripManifest);
      f.weaponReach = clamp(new THREE.Box3().setFromObject(models[0]).getSize(v3()).length() * .65, 1.8, 4.8);
      if (name === 'wheel') f.weaponReach = 14;
      if (name === 'musket') f.weaponReach = 18; // Web NPC firing distance, not a recovered EXE constant.
      if (f.hero && name === 'sword') {
        // 每次装备都新建一份：userData.update（飘带/呼吸光）是闭包，Object3D.clone
        // 会对 userData 做 JSON 序列化从而丢掉函数，所以这里不复用模板。
        if (!this.butterflyEnvironment) { try { this.butterflyEnvironment = createSwordEnvironment(this.renderer); } catch (error) { console.warn('月蝶剑环境贴图不可用：', error); } }
        const raidenTemplate = await this._loadRaidenSwordTemplate();
        if (this.disposed || f.disposed || request !== f.equipRequest) return;
        const variant = createButterflySword({ environment: this.butterflyEnvironment });
        variant.userData.butterflySword = true; variant.rotation.x = Math.PI / 2;
        f.character.getAttachment('d_wpnR').add(variant); f.character.registerVisualAttachment?.(variant,'d_wpnR'); f.butterflySword = variant;
        this.butterflyVfx ||= new ButterflySwordVfx(this.scene, { quality: this.quality || 'high' });
        if (raidenTemplate) {
          const raiden = raidenTemplate.clone(true); raiden.rotation.x = Math.PI / 2;
          f.character.getAttachment('d_wpnR').add(raiden); f.character.registerVisualAttachment?.(raiden,'d_wpnR'); f.raidenSword = raiden;
        }
        this.butterflyVfx.bind(variant); this._syncSwordStyle(f);
      }
      if (f.hero && name === 'spear') {
        if (!this.butterflyEnvironment) { try { this.butterflyEnvironment = createSwordEnvironment(this.renderer); } catch (error) { console.warn('兵器环境贴图不可用：', error); } }
        const variant = createPhoenixSpear({ environment: this.butterflyEnvironment });
        variant.rotation.x = Math.PI / 2;
        f.character.getAttachment('d_wpnR').add(variant); f.character.registerVisualAttachment?.(variant,'d_wpnR'); f.phoenixSpear = variant;
        this._syncSpearStyle(f);
      }
    } catch (error) { this._emit(`原版兵器读取失败：${name}`, 'info'); console.error(error); }
  }
  _ground(x, z, ceiling) {
    if (!this.currentMap) return null;
    this.raycaster.set(v3(x, ceiling, z), v3(0, -1, 0));
    return this.raycaster.intersectObjects(this._collisionCandidates(x, z), false).find(hit => surfaceY(hit) > .38) || null;
  }
  _collisionCandidates(x, z, radius = 1) {
    const map = this.currentMap;
    if (!map.collisionIndex || map.collisionIndex.objects !== map.colliders || map.collisionIndex.length !== map.colliders.length) map.collisionIndex = new StaticColliderIndex(map.colliders);
    return [...map.collisionIndex.near(x, z, radius), ...(map.props?.getCollidersNear(x, z, radius) || [])];
  }
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
  _move(f, direction, speed, dt, motion = null) {
    const desired = direction.clone().multiplyScalar(speed); f.velocity.lerp(desired, 1 - Math.exp(-dt * 14));
    let dx = f.velocity.x * dt + (motion?.x || 0), dz = f.velocity.z * dt + (motion?.z || 0), p = f.root.position;
    const from = p.clone();
    if (!this._horizontalBlocked(p, dx, 0)) p.x += dx;
    if (!this._horizontalBlocked(p, 0, dz)) p.z += dz;
    const ground = this._ground(p.x, p.z, p.y + this.hostPhysics.step);
    // Native 004ce850 overrides vertical velocity when the authored d_base
    // velocity has |trunc(native units/sec)|>=float0.1; otherwise gravity
    // continues. Retain that threshold to reject animation float noise.
    const authoredVertical = dt > 0 && Math.abs(Math.trunc((motion?.y || 0) / (SCALE * dt))) >= .1;
    if (f.grounded && ground && p.y - ground.point.y < .8 && !authoredVertical) p.y = ground.point.y + .015;
    else {
      f.grounded = false;
      if (authoredVertical) {
        f.nativeJump = null; f.vy = motion.y / dt; p.y += motion.y;
      } else if (f.nativeJump && !f.combat.busy) {
        const jump = f.nativeJump, before = jump.height;
        jump.elapsed = Math.min(jump.duration, jump.elapsed + dt);
        const frame = jump.pose.start + jump.elapsed * jump.fps;
        jump.height = (f.character.sampleSceneMotion(jump.pose.source, frame).z - jump.origin) * SCALE;
        const dy = jump.height - before; p.y += dy; f.vy = dy / dt;
        if (jump.elapsed >= jump.duration - 1e-8) f.nativeJump = null;
      } else {
        f.nativeJump = null; f.vy -= this.hostPhysics.gravity * dt; p.y += f.vy * dt;
      }
      const landing = this._ground(p.x, p.z, p.y + Math.max(.7, -f.vy * dt + .15));
      if (landing && p.y <= landing.point.y + .04 && f.vy <= 0) { p.y = landing.point.y + .015; f.vy = 0; f.grounded = true; f.nativeJump = null; f.jumpSequence = null; }
    }
    const hazard = this.currentMap.environment?.sweep(from, p);
    if (hazard && !f.dead) {
      // Original hell contact takes the direct death-state path (004ebc10),
      // not periodic damage. HP=0 is the Web/PST state mapping; the foot-point
      // sweep is a browser adapter for the original actor-bounds overlap.
      f.hp = 0; f.environmentDeath = { type: hazard.type, object: hazard.name }; this._kill(f);
      this.onEvent({ type: 'environment-death', text: f.hero ? '坠入险地' : `${f.name}坠入险地`, actorId: f.scriptId ?? f.id, objectName: hazard.name, provenance: hazard.provenance });
      return;
    }
    if (p.y < this.currentMap.bounds.min.y - 20 || Math.abs(p.x) > 3000 || Math.abs(p.z) > 3000) { if (this.mode === 'story') { f.hp = 0; this._kill(f); } else this._placeFighter(f, this.currentMap.spawns[f.hero ? 0 : (f.spawnIndex || 1) % this.currentMap.spawns.length]); }
  }
  _moveDirection(control = this) {
    const x = Number(control.keys.has('right')) - Number(control.keys.has('left')), z = Number(control.keys.has('forward')) - Number(control.keys.has('back')), a = control.cameraAngle;
    return v3(Math.cos(a) * x - Math.sin(a) * z, 0, -Math.sin(a) * x - Math.cos(a) * z).normalize();
  }
  _face(f, target, dt = 1) {
    const desired = Math.atan2(target.x - f.root.position.x, target.z - f.root.position.z), current = f.root.rotation.y;
    f.root.rotation.y += Math.atan2(Math.sin(desired - current), Math.cos(desired - current)) * Math.min(1, dt * 12);
  }
  async createScriptActor(config) {
    const actor = await this._createFighter(Number(config.modelId), config.name, false, Number(config.team));
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
  useScriptItem(actor, itemId) {
    const result = useNativeScriptItem(actor, this.combatData.itemRecords.get(Number(itemId)));
    if (!result) return false;
    this.onEvent?.({ type: 'script-item', actorId: actor.scriptId, itemId: result.id, name: result.name,
      duration: result.duration, value: result.value, refreshed: result.refreshed });
    return true;
  }
  async start({ map = 'sifang', weapon = 'sword', difficulty = 'normal', character = 0, mode = 'training' } = {}) {
    if (mode === 'story') {
      const mission = getNativeMission(map);
      if (!mission) throw new Error(`Original story mission ${map} is not available yet`);
      map = mission.mapId;
    }
    const request = ++this.sessionRequest;
    await this.ready; if (request !== this.sessionRequest || this.disposed) return;
    this.projectiles?.clear('restart'); this.projectiles?.pause(false); this.muskets?.clear(); this.wheels?.clear(); this.muskets?.pause(false); this.wheels?.pause(false); this.impactFeedback?.clear(); this.rageVfx?.clear(); this.effectContacts?.clear(); this.items?.reset(); this.missionHost?.dispose(); this.missionHost = null; this.missionState = null; this.storyResult = null;
    this.keyboard?.reset(); this.pointer = null; this.keys.clear(); this.traversalTap=null; this.directionBuffer = []; this.recoveryAttack = null; this.running = false; this.paused = false; this.mode = mode === 'story' ? 'story' : 'training';
    if (map !== this.map) await this._loadMap(map);
    if (request !== this.sessionRequest || this.disposed) return;
    this.currentMap.props?.reset?.();
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
    this._resetWorldClock(); this.running = true; this.cameraManualUntil = 0; this.cameraAngle = this.currentMap.id === 'sn01' ? Math.PI / 2 : 0; this.cameraPitch = this.currentMap.cameraPitch ?? .4; this.cameraDistance = this.currentMap.cameraDistance ?? 8;
    this.cameraTarget.copy(this.hero.root.position).add(v3(0, 1.5, 0)); this._tickCamera(1); this._unlockAudio();
    this._emit(this.mode === 'story' ? `原版${this.currentMap.entry.name || this.currentMap.id}` : '原版动作演练开始', 'info'); this._hud();
  }
  async menu(map = this.map) {
    this.mouseLook?.release();
    this.keyboard?.reset();
    ++this.sessionRequest; this.projectiles?.clear('menu'); this.projectiles?.pause(false); this.muskets?.clear(); this.wheels?.clear(); this.muskets?.pause(false); this.wheels?.pause(false); this.impactFeedback?.clear(); this.rageVfx?.clear(); this.effectContacts?.clear(); this.items?.reset(); this.missionHost?.dispose(); this.missionHost = null; this.missionState = null; this.mode = 'training';
    this.running = false; this.paused = false; this.keys.clear(); this.traversalTap=null; this.pointer = null; this.locked = null; this.directionBuffer = [];
    await this.ready; if (this.disposed) return;
    if (map !== this.map) await this._loadMap(map);
    this.currentMap.props?.reset?.();
    for (const f of this.enemies) { f.disposed = true; this._disposeNameplate(f); f.character.dispose(); } this.enemies = [];
    this.hero.guard = false; this.hero.scriptConfig = null; this.hero.scriptInputBlocked = false; this._placeFighter(this.hero, this.currentMap.spawns[0]); this.hero.root.rotation.y = -.3; this._resetWorldClock(); this._hud();
  }
  requestMouseLock() { return this.mouseLook?.request(); }
  setKeyBindings(bindings) { this.keyboard?.setBindings(bindings);this.mouseLook?.setBindings(bindings); }
  releaseInput({releaseMouse=true}={}) { this.keyboard?.reset(); if(releaseMouse)this.mouseLook?.release(); this.keys.clear(); clearPlayerCommands(this.localControl||this); this.pointer=null; if(this.hero)this.hero.guard=false; }
  pause(value = true) { this.releaseInput({releaseMouse:!!value}); if(this.paused !== !!value)this._resetWorldClock(); this.paused = !!value; this.projectiles?.pause(this.paused); this.muskets?.pause(this.paused); this.wheels?.pause(this.paused); if (this.master) this.master.gain.value = this.paused || this.muted ? 0 : .25; this._hud(); }
  async setCharacter(id = 0) {
    const request = ++this.characterRequest; await this.ready; id = Number(id); if (id === this.characterId || request !== this.characterRequest) return;
    const actor = await this._createFighter(id, NATIVE_CHARACTERS.find(c => c.id === id)?.name, true); if (this.disposed || request !== this.characterRequest) { actor.disposed = true; actor.character.dispose(); return; }
    if (this.hero) { this.rageVfx?.clearActor(this.hero); this.effectContacts?.clearActor(this.hero); disposePhoenixSpear(this.hero.phoenixSpear); this.hero.disposed = true; this.hero.character.dispose(); } this.hero = actor; this.characterId = id; this.scene.add(actor.root); this._placeFighter(actor, this.currentMap.spawns[0]); await this._equip(actor, this.weapon); this._hud();
  }
  async setCharacterAppearance(mode = 'original') {
    if (!Object.hasOwn(NATIVE_APPEARANCES, mode)) throw new Error('Unknown character appearance');
    const request = this.appearanceRequest = (this.appearanceRequest || 0) + 1; this.characterAppearance = mode;
    await this.ready; if (this.disposed || request !== this.appearanceRequest) return this.hero?.character.appearanceStatus;
    const actor = this.hero, status = await actor.character.setAppearance(mode);
    if (this.disposed || actor !== this.hero || request !== this.appearanceRequest) return status;
    if (!status.available || status.complete === false) this.characterAppearance = status.appearance || 'original';
    this.onEvent?.({ type: 'appearance', text: status.available ? `${status.label} · 已切换` : `外观保持不变：${status.reason}`, ...status }); this._hud();
    return status;
  }
  _syncSwordStyle(actor) {
    if (!actor?.weaponModel) return;
    const butterfly = this.swordStyle === 'butterfly' && !!actor.butterflySword;
    const raiden = this.swordStyle === 'raiden' && !!actor.raidenSword;
    actor.weaponModel.visible = !butterfly && !raiden;
    if (actor.butterflySword) actor.butterflySword.visible = butterfly;
    if (actor.raidenSword) actor.raidenSword.visible = raiden;
    if (actor.hero) this.butterflyVfx?.setVisible(butterfly);
  }
  setSwordStyle(style) {
    if (!['original','butterfly','raiden'].includes(style)) throw new Error('Unknown sword style');
    this.swordStyle=style; this._syncSwordStyle(this.hero);
  }
  _syncSpearStyle(actor) {
    if (!actor?.phoenixSpear || !actor.weaponModel) return;
    const enhanced = this.spearStyle === 'phoenix';
    actor.weaponModel.visible = !enhanced; actor.phoenixSpear.visible = enhanced;
  }
  setSpearStyle(style) {
    if (!['original', 'phoenix'].includes(style)) throw new Error('Unknown spear style');
    this.spearStyle = style; this._syncSpearStyle(this.hero);
  }
  async setWeapon(name) { if (!NATIVE_WEAPONS[name] || this.mode === 'story' || this.running && this.hero?.combat.reacting) return; this.weapon = name; if (this.hero) await this._equip(this.hero, name); this._hud(); }
  async switchWeapon() {
    if (this.hero?.combat.reacting || this.hero?.dead) return;
    if (this.mode === 'story') {
      if (this.hero.switchingWeapon) return; const next = this.hero.weapon2Id; if (!this.weaponItems.has(next)) return;
      this.hero.switchingWeapon = true; const previous = this.hero.weaponId;
      try { await this._equip(this.hero, next); this.hero.weapon2Id = previous; this.weapon = this.hero.weapon; this._hud(); } finally { this.hero.switchingWeapon = false; }
    }
    else { const first = ['sword', 'spear', 'blade', 'dagger', 'dart'], families = [...first, ...Object.keys(NATIVE_WEAPONS).filter(name => !first.includes(name))]; await this.setWeapon(families[(families.indexOf(this.weapon) + 1) % families.length]); }
  }
  setInfiniteRage(enabled) {
    this.infiniteRage = enabled === true;
    if (this.infiniteRage && this.hero) this.hero.rage = 100;
    this._hud();
  }
  setMuted(value) { this.muted = !!value; if (this.master) this.master.gain.value = value ? 0 : .25; }
  setQuality(value) { this.quality = value; this.butterflyVfx?.setQuality(value); this._applyMapPresentation(); this.renderScale.reset(Math.min(window.devicePixelRatio || 1, value === 'low' ? 1 : 2)); this.renderer.setPixelRatio(this.renderScale.ratio); this.resize(); }
  setDamageResolver(resolver) { if (resolver !== null && typeof resolver !== 'function') throw new Error('Damage resolver must be a function or null'); this.damageResolver = resolver; }
  _beginJump(actor) {
    if (!actor.grounded || actor.combat.busy) return false;
    const control=this._controlFor(actor),direction=nativeTraversalDirection(control?.keys)||'forward';
    const sequence=NATIVE_JUMP_POSES[direction];
    const pose = actor.combat.data.poses.get(sequence.start);
    if(!pose?.valid)return false;
    if(control&&!control.locked)actor.root.rotation.y=control.cameraAngle+Math.PI;
    actor.jumpSequence={...sequence,direction,facing:actor.root.rotation.y};
    actor.grounded = false; actor.vy = this.hostPhysics.jumpVelocity;
    if (pose?.valid && actor.character.sampleSceneMotion) {
      // 004ce850 consumes d_base movement independently of the visible skin.
      // Preserve the authored takeoff instead of a fixed-height substitute.
      // Interrupted/descending free flight still uses the Web gravity adapter.
      const fps = actor.combat.fps;
      actor.nativeJump = { pose, fps, elapsed: 0, height: 0, duration: (pose.end - pose.start) / fps,
        origin: actor.character.sampleSceneMotion(pose.source, pose.start).z };
    }
    actor.combat.play(sequence.start, { force: true }); actor.heldPose = 'jump'; return true;
  }
  _controlFor(actor) { return actor?.playerControl || (actor?.hero ? this.localControl || this : null); }
  _beginRoll(direction, poseId, actor = this.hero, control = this._controlFor(actor)) {
    if(!this.running||this.paused||!actor||actor.dead||!actor.grounded||actor.scriptInputBlocked||actor.combat.busy||!control?.keys.has('crouch')||poseId!==NATIVE_ROLL_POSES[direction])return false;
    if(!actor.combat.data.poses.get(poseId)?.valid)return false;
    if(!actor.combat.play(poseId,{motion:true,context:{kind:'roll',direction,poseId,name:({forward:'向前翻滚',back:'向后翻滚',left:'向左翻滚',right:'向右翻滚'})[direction]}}))return false;
    actor.root.rotation.y=control.cameraAngle+Math.PI;actor.velocity.set(0,0,0);actor.guard=false;actor.heldPose=null;clearPlayerCommands(control);
    return true;
  }
  _beginDash(direction,poseId,actor=this.hero,control=this._controlFor(actor)) {
    if(!this.running||this.paused||!actor||actor.dead||!actor.grounded||actor.scriptInputBlocked||actor.guard||actor.combat.busy||!control||control.keys.has('crouch')||poseId!==nativeDashPose(actor.weapon,direction))return false;
    if(!actor.combat.play(poseId,{motion:true,context:{kind:'dash',direction,poseId,name:'闪避'}}))return false;
    actor.root.rotation.y=control.cameraAngle+Math.PI;actor.velocity.set(0,0,0);actor.guard=false;actor.heldPose=null;control.recoveryAttack=null;
    return true;
  }
  _actionFighter(actor, control, name, active = true) {
    if(!actor || !control)return;
    const inputTime=control.inputTime??this.elapsed;
    if (name === 'guard') {
      const held = active && this.running && !this.paused && !actor.dead;
      if (held) control.keys.add('guard'); else control.keys.delete('guard');
      actor.guard = held && !actor.scriptInputBlocked && (!actor.combat.busy || actor.combat.reactionPhase === 'guard');
      return;
    }
    if (active && actor.scriptInputBlocked) return;
    if (name === 'crouch') { if(!active)control.traversalTap=null; if (active && this.running && !this.paused) control.keys.add('crouch'); else control.keys.delete('crouch'); return; }
    if (['forward','back','left','right'].includes(name)) {
      if(active&&this.running&&!this.paused&&!actor.dead){
        if(!control.keys.has(name)){
          const crouched=control.keys.has('crouch'),tap=traversalTap(control.traversalTap,{direction:name,time:inputTime,crouched,weapon:actor.weapon,allowed:actor.grounded&&!actor.combat.busy&&!actor.guard});control.traversalTap=tap.tap;
          const moved=tap.poseId&&(crouched?this._beginRoll(name,tap.poseId,actor,control):this._beginDash(name,tap.poseId,actor,control));
          if(!moved||!crouched)control.directionBuffer=recordNativeDirection(control.directionBuffer||[],{forward:'up',back:'down',left:'left',right:'right'}[name],inputTime,!actor.grounded);
        }
        control.keys.add(name);
      }else control.keys.delete(name);
      return;
    }
    if (!active || !this.running || this.paused || actor.dead) return;
    if(actor===this.hero)this._unlockAudio();
    if (name === 'attack') {
      if (actor.combat.reacting) control.recoveryAttack = { actor, weaponId: actor.weaponId,
        expires: this.elapsed + NATIVE_RECOVERY_INPUT_WINDOW, time: inputTime, air: !actor.grounded,
        buffer: [...control.directionBuffer], held: [...control.keys] };
      else { control.recoveryAttack = null; this._beginAttack(actor); }
    }
    else if (name === 'jump' && actor.grounded && !actor.combat.busy) {
      control.directionBuffer = []; this._beginJump(actor);
    }
    else if (name === 'lock') { control.locked = control.locked ? null : this._nearest(Infinity,actor); if(actor===this.hero){this.cameraManualUntil = 0;this._hud();} }
  }
  action(name, active = true) {
    if(['guard','crouch','forward','back','left','right','attack','jump','lock'].includes(name))return this._actionFighter(this.hero,this._controlFor(this.hero),name,active);
    if (!active || !this.running || this.paused || !this.hero || this.hero.dead || this.hero.scriptInputBlocked) return;
    this._unlockAudio();
    if (name === 'switch') this.switchWeapon();
    else if (name === 'pickup' && this.mode === 'story') {
      const result = this.items?.tryPickup(this.hero);
      if (result?.reason === 'full-rage') this._emit('怒气已满，道具留在原处','info');
      if (result?.reason === 'full-hp') this._emit('气血已满，肉包留在原处', 'info');
      this._hud();
    }
    else if (name === 'fury' || name === 'dodge') this._emit('该动作的原版指令与条件正在逆向，当前不使用替代招式', 'info');
    else if (/^pose:\d+$/.test(name)) this.hero.combat.play(Number(name.slice(5)));
    else if (['weapon1', 'weapon2', 'weapon3', 'weapon4', 'weapon5'].includes(name)) this.setWeapon(['sword', 'blade', 'spear', 'dagger', 'dart'][Number(name.slice(-1)) - 1]);
  }
  _beginAttack(f, savedInput = null) {
    const control=this._controlFor(f);
    if (f.dead || f.disposed || f.scriptRemoved || f.scriptCrouched || f.combat.reacting || control && f.scriptInputBlocked) return false;
    // Free attacks retain the player's chosen facing. An unlocked opponent
    // behind the player must not turn an intended gate/front attack around.
    const target = control ? control.locked : f.scriptControl?.attackTarget || this.hero;
    const move = control ? selectNativeMove(NATIVE_MOVE_CATALOG, { weapon: f.weapon, weaponMode: f.combat.weaponMode, includeOtherModes: true, air: !f.grounded, buffer: savedInput?.buffer ?? control.directionBuffer,
      held: (savedInput?.held ?? [...control.keys]).map(key => ({ forward: 'up', back: 'down', left: 'left', right: 'right' }[key])).filter(Boolean),
      time: savedInput?.time ?? control?.inputTime ?? this.elapsed, poseId: f.combat.timeline?.pose.id, movePoseId: f.combat.currentMove?.poseId, busy: f.combat.busy }) : savedInput?.npcMove ?? null;
    if (f.hero && this.infiniteRage) f.rage = 100;
    if (move?.weaponMode && move.weaponMode !== f.combat.weaponMode) {
      if (f.hero) this._emit(`${move.name}需要${QIANKUN_MODE_NAMES[move.weaponMode]} · 先用${move.weaponMode === 'sheath' ? '↓↓A' : move.weaponMode === 'spear' ? '←A' : '→A'}切换形态并完成收招`, 'info');
      return false;
    }
    if (move?.pending) { if (f.hero) this._emit(move.pending, 'info'); return false; }
    if (move && (f.rage || 0) < move.rage) { if (f.hero) this._emit(`怒气不足 · 需要 ${move.rage} 点`, 'info'); return false; }
    if (target && (!f.combat.busy || f.combat.currentMove?.kind==='dash') && !savedInput?.npcMove) this._face(f, target.root.position);
    const accepted = f.combat.attack({ air: !f.grounded, poseId: move?.poseId ?? null, context: move,
      // Input posture is checked when the command is accepted. An ACT-legal
      // queued continuation stays attached to that active predecessor if it
      // lands before the compiled transition frame (e.g. spear282 ->283).
      // Rage and actor lifetime are still checked again at the actual start.
      canStart: command => !f.dead && !f.disposed && !f.scriptRemoved && (!command || (f.hero && this.infiniteRage || (f.rage || 0) >= command.rage) &&
        ((command.stance === 'air') === !f.grounded || f.combat.busy && command.continuationOf?.includes(f.combat.currentMove?.poseId))),
      onStart: command => {
        if (!command) return;
        f.rage = f.hero && this.infiniteRage ? 100 : Math.max(0, (f.rage || 0) - command.rage);
        if (f.hero) this.onEvent?.({ type: 'move', text: command.name, moveId: command.id, poseId: command.poseId, command: command.command, rageCost: command.rage });
      }
    });
    if (accepted) {
      f.guard = false; f.heldPose = 'attack';
      if (control) { control.directionBuffer = []; control.recoveryAttack = null; }
    }
    return accepted;
  }
  _nearest(range = Infinity, actor = this.hero) { let best = null; for (const f of [this.hero,...this.enemies]) { if(!f||f===actor)continue; const d = flatDistance(f.root.position, actor.root.position); if (!f.dead && !f.disposed && !f.scriptRemoved && f.team !== actor.team && d < range) { range = d; best = f; } } return best; }
  _npcCombatAction(f, target, due, { requested = false, allowed = true, reach = 0 } = {}) {
    if (!target || !allowed || target.dead || target.disposed || target.scriptRemoved || !this.hasScriptLineOfSight(f, target)) return;
    if (requested) {
      if (flatDistance(f.root.position, target.root.position) <= reach && !f.combat.busy && this._beginAttack(f)) f.scriptAttackRequested = false;
      return;
    }
    if (!due || !f.npcCombat) return;
    const profile = f.npcCombat.data.profiles[f.weapon];
    if (!nativeNpcInRange(f, target, profile)) { f.npcCombat.guard = false; f.guard = false; return; }
    const choice = f.npcCombat.choose(f, { canAttack: () => nativeNpcFacing(f, target, profile) });
    if (choice.kind === 'attack' && choice.program != null) {
      const move = nativeNpcMove(f, choice.program, this.elapsed);
      const accepted = !!move && this._beginAttack(f, { npcMove: move });
      this.onEvent?.({ type: 'npc-decision', actorId: f.scriptId ?? f.id, kind: 'attack', category: choice.category,
        program: choice.program, poseId: move?.poseId, accepted });
    } else this.onEvent?.({ type: 'npc-decision', actorId: f.scriptId ?? f.id, kind: choice.kind });
    f.guard = f.npcCombat.guard && !f.combat.busy;
  }
  _updateFighter(f, dt) {
    if (f.disposed || f.scriptRemoved) return;
    const control=this._controlFor(f);
    if (f.hero && this.infiniteRage) f.rage = 100;
    if (f.weapon === 'wheel' && f.weaponModel) f.weaponModel.visible = !this.wheels?.hasOwner(f);
    (f.previousPosition ||= v3()).copy(f.root.position);
    updateNativeScriptItems(f, dt, result => this.onEvent?.({ type: 'item-tick', actorId: f.scriptId ?? f.id, ...result }), { time: this.elapsed });
    // 004affd0 handles periodic-stat death without an attacker/kill award.
    if (!f.dead && f.hp <= 0) this._kill(f, { awardKill: false });
    if (f.dead) { const state = f.combat.update(dt); if (state) f.character.setPoseFrame(state.source, state.frame); f.respawn -= dt; if (f.respawn <= 0) this._placeFighter(f, this.currentMap.spawns[f.hero ? 0 : f.spawnIndex % this.currentMap.spawns.length]); return; }
    const npcDue = !control && f.npcCombat?.advance(dt, f.scriptConfig, {
      hasTarget: !!(f.scriptControl?.attackTarget || f.awarenessTarget), paused: !!f.scriptControl?.paused });
    // Only the two contacting actors pause; mission time, projectiles and
    // other fighters keep running. These short durations are Web feedback.
    if (f.hitstop > 0) { const pause = Math.min(dt, f.hitstop); f.hitstop -= pause; dt -= pause; if (dt <= 1e-7) return; }
    let direction = v3(), speed = this.hostPhysics.speed * nativeMovementScale(f);
    if (control && control.recoveryAttack) {
      const input = control.recoveryAttack;
      if (input.actor !== f || input.weaponId !== f.weaponId || this.elapsed > input.expires || input.air !== !f.grounded || f.scriptInputBlocked) control.recoveryAttack = null;
      else if (!f.combat.reacting) { control.recoveryAttack = null; this._beginAttack(f, input); }
    }
    if (control) f.guard = control.keys.has('guard') && !f.scriptInputBlocked && (!f.combat.busy || f.combat.reactionPhase === 'guard');
    if (f.combat.reacting || f.scriptCrouched || f.combat.busy && ['roll','dash'].includes(f.combat.currentMove?.kind)) {
      if (f.combat.reactionPhase !== 'guard') f.guard = false;
    } else if (control) {
      if (f.scriptInputBlocked) f.guard = false;
      direction = f.scriptInputBlocked ? v3() : this._moveDirection(control);
      if(!f.grounded&&f.jumpSequence&&!f.combat.busy)f.root.rotation.y=f.jumpSequence.facing;
      else if (control.locked && !control.locked.dead) this._face(f, control.locked.root.position, dt);
      else if (!f.combat.busy && (control.keys.has('crouch') || control.lookLocked || control.mouseLook?.locked)) this._face(f, f.root.position.clone().add(v3(-Math.sin(control.cameraAngle),0,-Math.cos(control.cameraAngle))),dt);
      else if (direction.lengthSq() > 0 && !f.combat.busy) this._face(f, f.root.position.clone().add(direction), dt);
    } else if (f.scriptControlled) {
      const control = f.scriptControl;
      f.guard = !!(control?.guard || !control?.paused && f.npcCombat?.guard) && !f.combat.busy; speed *= Number(control?.speedScale ?? 1) * .68;
      if (control && !control.paused) {
        const target = control.attackTarget, targetAlive = target && !target.dead && !target.disposed;
        const moveTarget = control.moveTarget, reach = f.weaponReach || (f.weapon === 'spear' ? 3.8 : 2.3);
        // Dijkstra/waypoint navigation is a Web adapter. Elevated source links
        // (e.g. sn09 WP7→0) need the same original takeoff as the player; a
        // walking-only follower would fall when the source floors disappear.
        if (moveTarget && Number(f.scriptConfig?.Jump) > 0 && moveTarget.y - f.root.position.y > this.hostPhysics.step + .3 && flatDistance(moveTarget, f.root.position) < 8) this._beginJump(f);
        const distance = targetAlive ? flatDistance(target.root.position, f.root.position) : Infinity;
        if (moveTarget && (moveTarget !== target?.root.position || distance > reach + .2)) { direction.copy(moveTarget).sub(f.root.position); direction.y = 0; if (direction.length() > .45) direction.normalize(); else direction.set(0, 0, 0); }
        if (targetAlive && control.canAttack) {
          this._face(f, target.root.position, dt);
          if (distance < reach - .5) { direction.copy(f.root.position).sub(target.root.position); direction.y = 0; direction.normalize(); speed *= .35; }
          this._npcCombatAction(f, target, npcDue, { requested: control.attackRequested, reach: reach + .6 });
        } else if (direction.lengthSq() > 0) this._face(f, f.root.position.clone().add(direction), dt);
      }
    } else if (this.running && !this.hero.dead) {
      const target = findNativeEnemy(f, [this.hero], (observer, enemy) => this.hasScriptLineOfSight(observer, enemy));
      if (target) {
        f.guard = !!f.npcCombat?.guard && !f.combat.busy;
        const delta = target.root.position.clone().sub(f.root.position); delta.y = 0; const distance = delta.length();
        this._face(f, target.root.position, dt); speed *= this.difficulty === 'hard' ? .9 : .68;
        const reach = f.weaponReach || (f.weapon === 'spear' ? 3.8 : 2.3);
        if (distance > reach + .2) direction.copy(delta).normalize();
        else if (distance < reach - .45) { direction.copy(delta).normalize().negate(); speed *= .4; }
        if (distance < reach + 3 && !f.combat.busy) {
          const angle = (f.slot || 0) * Math.PI * 2 / 3 + this.elapsed * .035;
          const slot = target.root.position.clone().add(v3(Math.sin(angle) * reach, 0, Math.cos(angle) * reach)).sub(f.root.position); slot.y = 0;
          if (slot.length() > .7) direction.lerp(slot.normalize(), .55).normalize();
        }
        this._npcCombatAction(f, target, npcDue, { reach: reach + .7 });
      }
    }
    if (f.guard) speed *= .3;
    if (f.combat.busy) speed = 0;
    if (!f.combat.busy) {
      const jumpStart=f.jumpSequence?.start??NATIVE_LOCOMOTION.jumpStart,jumpAir=f.jumpSequence?.air??NATIVE_LOCOMOTION.jumpAir;
      let pose = f.guard ? NATIVE_WEAPONS[f.weapon].guard : !f.grounded ? jumpAir : f.velocity.lengthSq() > .2 ? NATIVE_LOCOMOTION.run : f.combat.stance ?? NATIVE_WEAPONS[f.weapon].stance;
      const startingJump = f.heldPose === 'jump' && f.combat.timeline?.pose.id === jumpStart && !f.combat.timeline.finished;
      if (startingJump) pose = jumpStart;
      const crouching = (f.scriptCrouched || control && control.keys.has('crouch')) && f.grounded;
      if (crouching) {
        const walking=direction.lengthSq()>0||f.velocity.lengthSq()>.2,requested=nativeTraversalDirection(control?.keys);
        const movingPose=NATIVE_CROUCH_POSES[requested]??(f.heldPose>=145&&f.heldPose<=148?f.heldPose:NATIVE_CROUCH_POSES.forward);
        pose=walking?movingPose:NATIVE_CROUCH_POSES.idle;
      }
      if (f.heldPose !== pose && !startingJump) { f.combat.play(pose, { loop: true, force: true }); f.heldPose = pose; }
    }
    const state = f.combat.update(dt, { grounded: f.grounded, projectileReady: !this.wheels?.hasOwner(f) }); if (!state) return;
    // A held defense is sampled continuously, including the exact frame a
    // hit/attack recovery ends. It must not depend on OS key-repeat or a new
    // touch press while several opponents are attacking.
    if (control && !f.combat.busy && !f.scriptInputBlocked && control.keys.has('guard')) f.guard = true;
    const motion = v3();
    for (const segment of state.segments || [state]) if (segment.authoredMotionScale != null) {
      const a = f.root.rotation.y, scale = segment.authoredMotionScale;
      const localX = segment.rootDelta.x * scale, localZ = -segment.rootDelta.y * scale;
      motion.x += Math.cos(a) * localX + Math.sin(a) * localZ;
      motion.z += -Math.sin(a) * localX + Math.cos(a) * localZ;
      motion.y += segment.rootDelta.z * scale;
    }
    // Native animation advances before the actor's motion update (004cc130).
    // All authored recoil/lunges now share floor, wall and hazard checks.
    this._move(f, direction, speed, dt, motion);
    if (f.dead) return;
    for (const segment of state.segments || [state]) {
      if (!segment.blend && segment.serial !== f.lastSerial) {
        f.attackHits.clear(); f.lastSerial = segment.serial;
        const basicEmitter = { dart: NATIVE_DART_PROFILE, musket: NATIVE_MUSKET_PROFILE, wheel: NATIVE_WHEEL_PROFILE }[f.weapon];
        if (segment.pose.attacks.length && !basicEmitter?.poseIds.includes(segment.pose.id)) this._soundDefinition(segment.pose.raw.fields.effectid);
      }
      // Source parameter18 is a deferred self item, independent of landing a
      // hit. Commit once on casting completion; interruption discards the cast.
      if (!segment.blend && segment.finished && !['roll','dash'].includes(segment.context?.kind) && segment.context?.poseId === segment.pose.id && f.selfItemSerial !== segment.serial) {
        f.selfItemSerial = segment.serial;
        const item = useNativeSelfItem(f, this.combatData.moveRecords.get(segment.pose.id), this.combatData.itemRecords);
        if (item) this.onEvent?.({ type: 'self-item', actorId: f.scriptId ?? f.id, poseId: segment.pose.id, itemId: item.id, name: item.name, duration: item.duration, refreshed: item.refreshed });
      }
      // A rendered frame can cross several narrow original attack windows.
      // Sample each window's authored frame, keeping its original index and
      // serial so multi-thrusts hit once per window, never once per render.
      for (const attack of segment.attacks) {
        const frame = clamp(segment.frame, attack.start, attack.end);
        f.character.setPoseFrame(segment.source, frame);
        const contactState = { ...segment, frame, attacks: [attack] };
        this._launchNativeProjectiles(f, contactState); this._resolveContacts(f, contactState);
      }
    }
    if (state.blend && f.character.setPoseBlend) f.character.setPoseBlend(state.blend.from, state.blend.to, state.blend.weight);
    else f.character.setPoseFrame(state.source, state.frame);
    this.rageVfx?.sample(f, state, f.combat.fps);
    if (f.nameplate) { f.nameplate.quaternion.copy(f.root.quaternion).invert().multiply(this.camera.quaternion); }
  }
  _resolveContacts(attacker, state) {
    if (!this.running) return;
    const targets = attacker.playerControl ? [this.hero,...this.enemies].filter(f=>f!==attacker&&f.team!==attacker.team) : attacker.hero ? this.enemies : this.mode === 'story' ? [this.hero, ...this.enemies].filter(f => f !== attacker && f.team !== attacker.team) : [this.hero];
    for (const attack of state.attacks) this._resolveSceneContacts(attacker, state, attack);
    for (const attack of state.attacks) {
      const points = [];
      for (const name of attack.bones) {
        if (name === 'weapon' && attacker.weaponModel) { for (const model of attacker.weaponModels?.length ? attacker.weaponModels : [attacker.weaponModel]) { const box = new THREE.Box3().setFromObject(model); points.push(box.getCenter(v3()), box.min.clone(), box.max.clone()); } }
        else { const bone = getNativeAttackAttachment(attacker.character, name); if (bone) points.push(bone.getWorldPosition(v3())); }
      }
      const effectVolumes = this.effectContacts?.sample(attacker, state, attack, attacker.combat.fps) || [];
      for (const target of targets) {
        const key = `${attack.index}:${target.id}`; if (!this.running || target.dead || target.disposed || target.scriptRemoved || attacker.attackHits.has(key)) continue;
        const center = target.root.position.clone().add(v3(0, 1.35, 0));
        let contact = points.find(p => Math.hypot(p.x - center.x, p.z - center.z) < .9 && Math.abs(p.y - center.y) < 1.45), extra = {};
        if (!contact) {
          const effect = this.effectContacts?.contact(effectVolumes, target);
          if (effect) { const { point, ...info } = effect; contact = point; extra = info; }
        }
        if (!contact) continue;
        // Body/weapon/effect are alternative checks in one POS Attack record.
        // Keep its existing per-target identity rather than doubling damage.
        attacker.attackHits.add(key); this._applyNativeHit(attacker, target, state, attack, contact, extra);
      }
    }
  }
  _applyNativeHit(attacker, target, state, attack, contact, extra = {}) {
    if (!this.running || target.dead || target.disposed || target.scriptRemoved) return false;
    target.contacts = (target.contacts || 0) + 1; if (attacker.hero) this.contactHits++;
    const raw = { targetValue: attack.targetvalue, targetMove: attack.targetmove, defenseValue: attack.defensevalue, defenseMove: attack.defensemove, attackType: attack.attacktype, targetPose: attack.targetpose, moveRecord: this.combatData.moveRecords.get(state.poseId), weaponRecord: attacker.weaponRecord || this.combatData.weaponRecords.get(NATIVE_WEAPONS[attacker.weapon]?.model) };
    // Original POS parser rule 0x30 stores AttackType at record+0x30;
    // 004f3380 packs its six bits, and 004af630 applies the guard branch only
    // when that field is zero. A native nonzero type must bypass guard HP
    // protection. The native branch also protects a held guard from behind;
    // direction chooses its source reaction, not an invented guard cone.
    const guarded = !!target.guard && ((attack.attacktype ?? 0) & 0x3f) === 0;
    const guardBypassed = !!target.guard && !guarded;
    const selection = nativeHitSelection(attack, nativeHitAngle(attacker.root.position, target.root.position, target.root.rotation.y));
    const reactionPose = selection.poseId;
    Object.assign(raw, { selectedTargetPose: reactionPose, hitDirection: selection.direction, hitAngle: selection.angle });
    const knockdown = !guarded && [112, 113].includes(this.combatData.poses?.get(reactionPose)?.link);
    const damageContext = { attack, raw, attacker, target, weapon: attacker.weapon, guarded, poseId: state.poseId };
    const damage = this.damageResolver?.(damageContext);
    if (Number.isFinite(damage) && damage >= 0) {
      const hpBefore = target.hp; target.hp = Math.max(0, target.hp - damage); if (attacker.hero) this.totalDamage += hpBefore - target.hp;
      const nativeResult = damageContext.nativeResult;
      if (nativeResult) target.rage = clamp((target.rage || 0) + (nativeResult.guarded ? nativeResult.victimRage : Math.floor(14 * (hpBefore - target.hp) / 100)), 0, nativeRageMaximum(target));
      // 004af630: guard returns before parameter16; a lethal hit takes the
      // death path. Surviving ordinary hits gain rage before their item effect.
      const attackItem = !guarded && target.hp > 0 ? useNativeAttackItem(target, raw.moveRecord, this.combatData.itemRecords) : null;
      if (attackItem) {
        raw.attackItem = { id: attackItem.id, name: attackItem.name, refreshed: attackItem.refreshed,
          duration: attackItem.duration, period: attackItem.period, rageBefore: attackItem.rageBefore, rageAfter: attackItem.rageAfter };
        this.onEvent?.({ type: 'attack-item', actorId: target.scriptId ?? target.id, attackerId: attacker.scriptId ?? attacker.id,
          poseId: state.poseId, itemId: attackItem.id, name: attackItem.name, refreshed: attackItem.refreshed });
      }
      if (target.hp <= 0) this._kill(target);
      this._emit(guarded ? '格挡' : String(Math.round(damage)), 'hit', damage, contact, { poseId: state.poseId, raw, guarded, guardBypassed, knockdown: knockdown && !target.dead, attackerHero: !!attacker.hero, targetHero: !!target.hero, targetName: target.name, ...extra });
    } else { const name = raw.moveRecord?.name || state.pose.label || '兵刃交锋'; this._emit(attacker.hero ? `${name} · 命中` : `${name} · 对手命中`, 'hit', undefined, contact, { poseId: state.poseId, raw, guarded, guardBypassed, damagePending: true, ...extra }); }
    const displayedReaction = guarded ? nativeGuardPose(target.weapon, selection.direction) : reactionPose;
    if (!target.dead && displayedReaction != null && target.combat?.react(displayedReaction, {
      ...nativeReactionParameters(attack, { guarded }), guarded, fromPose: target.character?.capturePose?.()
    })) {
      if (!guarded) target.guard = false;
      this.effectContacts?.clearActor(target);
      target.heldPose = 'reaction'; target.velocity?.set(0, 0, 0);
      // Native forced hits blend from the currently displayed transforms.
      // Capture also retains an interrupted partial blend without a bone pop.
      const timeline = target.combat.timeline;
      const blend = target.combat.poseBlend;
      if (blend && target.character?.setPoseBlend) target.character.setPoseBlend(blend.from, blend.to, blend.weight);
      else target.character?.setPoseFrame(timeline.pose.source, timeline.frame);
      const control=this._controlFor(target);if(control)control.directionBuffer=[];
    }
    const feedback = this.impactFeedback?.emit({ point: contact, direction: target.root.position.clone().sub(attacker.root.position), guarded, knockdown, local: !!(attacker.hero || target.hero) });
    if (attacker.hero && this.swordStyle === 'butterfly') this.butterflyVfx?.burst(contact, { guarded, knockdown, camera: this.camera });
    if (feedback) {
      if (attacker.combat && !attacker.dead) attacker.hitstop = Math.max(attacker.hitstop || 0, feedback.hitstop);
      if (!target.dead) target.hitstop = Math.max(target.hitstop || 0, feedback.hitstop);
    }
    const prefix = { sword: 'W00', blade: 'W05', spear: 'W07', dagger: 'W01', dart: 'W03', musket: 'W02', wheel: 'W06', qiankun: 'W09', ninja: 'W11', dual: 'W08', hammer: 'W04', knuckle: 'W10' }[attacker.weapon];
    this._soundDefinition(`${prefix}${guarded ? 'GD' : 'BL'}${String(reactionPose).padStart(3, '0')}`); this._hud(); return true;
  }
  _resolveSceneContacts(attacker, state, attack) {
    if (!this.missionHost || !this.running || !this.currentMap.props) return;
    const objects = this.currentMap.props.getInstancesNear(attacker.root.position.x, attacker.root.position.z, 7, { attack: true })
      .filter(object => this.missionHost.sceneVm.hasFunction(`${object.name}_OnAttack`));
    if (!objects.length) return;
    // Cast through actual original collision triangles toward source attack
    // bones. Contact generation is a host adapter; the scene damage argument
    // follows the independently recovered 004af570 -> OnAttack numeric path.
    const origin = attacker.root.position.clone().add(v3(0, 1.3, 0)), points = [];
    for (const name of attack.bones) {
      if (name === 'weapon' && attacker.weaponModel) {
        for (const model of attacker.weaponModels?.length ? attacker.weaponModels : [attacker.weaponModel]) { const box = new THREE.Box3().setFromObject(model); points.push(box.min.clone(), box.max.clone(), box.getCenter(v3())); }
      } else { const bone = getNativeAttackAttachment(attacker.character, name); if (bone) points.push(bone.getWorldPosition(v3())); }
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
  _kill(target, { awardKill = true } = {}) {
    if (target.dead) return; target.dead = true; target.guard = false; target.hitstop = 0; target.respawn = this.mode === 'story' ? Infinity : 3; target.combat.play(NATIVE_LOCOMOTION.dead, { force: true });
    clearPlayerCommands(this._controlFor(target));
    if (target.hero) this.deaths++; else if (awardKill) this.kills++;
    for(const actor of [this.hero,...this.enemies]){const control=this._controlFor(actor);if(control?.locked===target)control.locked=null;}
  }
  _separateCharacters(dt) {
    const fighters = [this.hero, ...this.enemies].filter(f => !f.dead && !f.disposed && !f.scriptRemoved), diameter = this.hostPhysics.radius * 2 + .25;
    for (let i = 0; i < fighters.length; i++) for (let j = i + 1; j < fighters.length; j++) {
      const a = fighters[i], b = fighters[j]; if (Math.abs(a.root.position.y - b.root.position.y) > 2) continue;
      let dx = b.root.position.x - a.root.position.x, dz = b.root.position.z - a.root.position.z, distance = Math.hypot(dx, dz);
      if (distance >= diameter) continue;
      if (distance < .001) { const angle = j * 2.4; dx = Math.sin(angle); dz = Math.cos(angle); distance = 1; } else { dx /= distance; dz /= distance; }
      const bothPlayers=!!this._controlFor(a)&&!!this._controlFor(b);
      const correction = Math.min(diameter - Math.min(distance, diameter), dt * 5), aWeight = bothPlayers ? .5 : a.hero ? .08 : b.hero ? .92 : .5, bWeight = 1 - aWeight;
      for (const [f, amount] of [[a, -correction * aWeight], [b, correction * bWeight]]) {
        if (!this._horizontalBlocked(f.root.position, dx * amount, 0)) f.root.position.x += dx * amount;
        if (!this._horizontalBlocked(f.root.position, 0, dz * amount)) f.root.position.z += dz * amount;
      }
    }
  }
  _finish(win) { if (!this.running) return; this.running = false; this.projectiles?.clear('match-end'); this.muskets?.clear(); this.wheels?.clear(); this.keys.clear(); this.traversalTap=null; this.onEnd({ win, kills: this.kills, deaths: this.deaths, damage: this.totalDamage, time: Math.round(this.matchElapsed), nativeData: true, damageVerified: !!this.damageResolver, mode: this.mode, mission: this.missionState, reason: this.storyResult?.reason }); }
  _nameplate(f) {
    const c = document.createElement('canvas'); c.width = 256; c.height = 64; const ctx = c.getContext('2d'); ctx.font = '28px serif'; ctx.fillStyle = '#eee7cf'; ctx.textAlign = 'center'; ctx.fillText(`${f.team === this.hero?.team ? '同伴' : f.team === 0 ? '剧情' : '对手'} · ${f.name}`, 128, 43, 240);
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
  _tickCamera(dt, { directLook: directLookRequested = false } = {}) {
    if (!this.hero || !this.currentMap) return;
    const p = this.hero.root.position, eye = p.clone().add(v3(0, 1.65, 0)), target = eye.clone(); let desired;
    // Carry the camera rig with physical ascent/descent before smoothing its
    // framing. Two independent lerps otherwise lag a fast jump by several
    // body lengths, especially with a short camera distance.
    const verticalStep = Number.isFinite(this.cameraFollowY) ? p.y - this.cameraFollowY : 0;
    this.cameraFollowY = p.y;
    if (this.running || this.paused) { this.camera.position.y += verticalStep; this.cameraTarget.y += verticalStep; }
    if (!this.running && !this.paused) {
      if (this.currentMap.menuCamera) {
        target.fromArray(this.currentMap.menuCamera.target); desired = v3().fromArray(this.currentMap.menuCamera.position);
        desired.x += Math.sin(this.elapsed * .04) * .5;
      } else { target.add(v3(-2.8, .1, 0)); desired = p.clone().add(v3(5.2 + Math.sin(this.elapsed * .04) * .25, 3.5, 8.5)); }
    } else {
      const opponent = this.locked;
      // Lock-on and near-wall rendering are browser interaction adapters. They
      // do not alter the original actor pose, hit resolution or scene geometry.
      if (opponent && !opponent.dead && !opponent.disposed ) {
        const toEnemy = opponent.root.position.clone().sub(p), desiredAngle = Math.atan2(-toEnemy.x, -toEnemy.z);
        if (!this.paused) this.cameraAngle += Math.atan2(Math.sin(desiredAngle - this.cameraAngle), Math.cos(desiredAngle - this.cameraAngle)) * (1 - Math.exp(-dt * 3));
        const focus = opponent.root.position.clone().add(v3(0, 1.35, 0)).sub(eye).multiplyScalar(.25);
        if (focus.length() > 3) focus.setLength(3);
        target.copy(this._safeCameraPosition(eye, eye.clone().add(focus)));
      }
      desired = target.clone().add(v3(Math.sin(this.cameraAngle) * this.cameraDistance, Math.sin(this.cameraPitch) * this.cameraDistance + 1, Math.cos(this.cameraAngle) * this.cameraDistance));
    }
    this.cameraTarget.lerp(target, 1 - Math.exp(-dt * 8));
    const hasLiveLock = this.locked && !this.locked.dead && !this.locked.disposed;
    const directLook = this.running && !this.paused && !hasLiveLock && (directLookRequested || this.mouseLook?.locked || this.pointer?.moved);
    if (directLook) {
      // Follow translation smoothly, but apply the sampled mouse orbit in this
      // render frame. Position lerp here added ~100ms of angular chase/drag.
      desired = this.cameraTarget.clone().add(v3(Math.sin(this.cameraAngle) * this.cameraDistance, Math.sin(this.cameraPitch) * this.cameraDistance + 1, Math.cos(this.cameraAngle) * this.cameraDistance));
    }
    const safe = this._safeCameraPosition(this.cameraTarget, desired);
    if (directLook) this.camera.position.copy(safe);
    else this.camera.position.lerp(safe, 1 - Math.exp(-dt * 10));
    // Recheck the interpolated point too: smoothing must not cross a wall while
    // the player or locked target moves around a corner.
    if (!directLook) this.camera.position.copy(this._safeCameraPosition(this.cameraTarget, this.camera.position)); this.camera.lookAt(this.cameraTarget);
    this.hero.root.visible = !this.running || this.camera.position.distanceTo(eye) >= 2.1;
  }
  _hud() {
    if (!this.hero) return; const f = this.hero, target = this.locked || (this.running ? this._nearest(18) : null), b = this.currentMap?.bounds;
    let enemy = null;
    if (target) {
      const delta = target.root.position.clone().sub(f.root.position), view = this.camera.getWorldDirection(v3()); view.y = 0; view.normalize();
      const right = v3(-view.z, 0, view.x);
      enemy = { name: target.name, hp: target.hp, maxHp: target.maxHp, reaction: target.combat?.reactionPhase ?? null, distance: delta.length(), bearing: Math.atan2(delta.dot(right), delta.dot(view)) };
    }
    const item = this.running && this.mode === 'story' ? this.items?.peek(f) : null;
    const pickup = item ? { name: item.name, heal: item.heal, description:item.description, fullReason:item.fullReason, full: item.full, distance: item.distance, objectName: item.objectName } : null;
    const statuses = (f.scriptItems || []).map(item => ({ id: item.id, name: item.name, statKey: item.statKey, remaining: item.remaining, value: item.value, period: item.period }));
    this.onUpdate({ infiniteRage: !!this.infiniteRage, characterAppearance: f.character.appearanceStatus, pickup, statuses, inputBlocked: !!f.scriptInputBlocked, hp: f.hp, maxHp: f.maxHp, playerReaction: f.combat.reactionPhase, rage: f.rage, hits: this.contactHits, kills: this.kills, deaths: this.deaths, time: this.matchElapsed, enemy, combo: f.combat.attacking ? f.combat.combo : 0, moveName: f.combat.busy ? f.combat.currentMove?.name : null, moveCommand: f.combat.busy ? f.combat.currentMove?.command : null, queuedMoveName: f.combat.queuedMove?.name || null, locked: !!this.locked, position: { x: f.root.position.x, z: f.root.position.z }, enemies: this.enemies.filter(e => !e.dead && !e.scriptRemoved && e.team !== f.team && e.team !== 0).map(e => ({ x: e.root.position.x, z: e.root.position.z })), allies: this.enemies.filter(e => !e.dead && !e.scriptRemoved && e.team === f.team).map(e => ({ x: e.root.position.x, z: e.root.position.z })), weapon: f.weapon, weaponId: f.weaponId, weaponName: f.weaponName, weaponMode: f.combat.weaponMode, mission: this.missionState, paused: this.paused, mapBounds: b ? { minX: b.min.x, maxX: b.max.x, minZ: b.min.z, maxZ: b.max.z } : null, native: { pose: f.combat.timeline?.pose.id, source: f.character.source, frame: f.character.frame, contacts: this.contactHits, damagePending: !this.damageResolver, hpSourcePending: !f.hpSourceVerified, physicsPending: true, sceneDamagePending: this.mode === 'story' && !this.sceneDamageResolver, projectilePending: false, projectileSpecialsPending: true, projectilePhysics: NATIVE_DART_PROFILE.provenance.flight, projectiles: this.projectiles?.size || 0, missionVmPending: this.mode === 'story' ? !this.missionHost?.started : false } });
  }
  _emit(text, type = 'info', amount, point, extra = {}) { const p = point?.clone().project(this.camera); this.onEvent({ text, type, amount, x: p ? (p.x + 1) / 2 : undefined, y: p ? (1 - p.y) / 2 : undefined, ...extra }); }
  _resetWorldClock() { this.simulationClock?.reset(); this.clock?.getDelta(); this.frameMeter?.reset(); }
  _advanceWorld(seconds) {
    this.simulationClock ||= new FixedStepClock();
    if (!this.hero || this.paused || this.disposed) { this.simulationClock.reset(); return; }
    this.simulationClock.advance(seconds, dt => {
      if (!this.hero || this.paused || this.disposed) return false;
      this._stepWorld(dt);
      return !this.paused && !this.disposed;
    });
  }
  _stepWorld(dt) {
    this.elapsed += dt;
    if (this.running) this.missionHost?.update(dt); this.currentMap.props?.update(dt); this.currentMap.update?.(dt);
    if (this.running) { this.matchElapsed += dt; this._updateFighter(this.hero, dt); for (const f of this.enemies) { if (!this.running) break; this._updateFighter(f, dt); } this._separateCharacters(dt); if (this.running) { this.projectiles?.update(dt); this.wheels?.update(dt); } }
    else { const state = this.hero.combat.update(dt); if (state) this.hero.character.setPoseFrame(state.source, state.frame); }
    this.updateAccum += dt; if (this.updateAccum > .08) { this.updateAccum = 0; this._hud(); }
  }
  _updatePresentation(dt) {
      this.weather?.update(dt, this.hero?.root.position);
      // Run cosmetic springs once, after final body motion and separation.
      for (const actor of [this.hero,...this.enemies]) if(actor?.root.visible&&!actor.disposed)actor.character.updateSecondaryMotion?.(dt,{groundY:actor.grounded?actor.root.position.y:undefined});
      for (let i = this.effects.length - 1; i >= 0; i--) { const e = this.effects[i]; e.life -= dt; e.mesh.material.opacity = Math.max(0, e.life / .14); if (e.life <= 0) { e.mesh.removeFromParent(); e.mesh.geometry.dispose(); e.mesh.material.dispose(); this.effects.splice(i, 1); } }
      this.impactFeedback?.update(dt);
      this.rageVfx?.update(dt, this.camera);
      this.butterflyVfx?.update(dt, { attacking: !!this.hero?.combat?.attacking, camera: this.camera });
      if (this.hero?.phoenixSpear?.visible) this.hero.phoenixSpear.userData.update(this.elapsed);
  }
  _frame(timestamp) {
    if (this.disposed) return; this.raf = requestAnimationFrame(this._frame);
    const started = performance.now();
    const seconds = this.clock.getDelta(), dt = Number.isFinite(seconds) ? Math.max(0, Math.min(.05, seconds)) : 0;
    this._advanceWorld(seconds);
    if (this.hero && !this.paused) this._updatePresentation(dt);
    const worldEnd = performance.now();
    this._tickCamera(dt);
    const cameraEnd = performance.now();
    const offset = this.impactFeedback?.cameraOffset;
    if (offset) this.camera.position.add(offset);
    this.renderer.render(this.scene, this.camera);
    if (offset) this.camera.position.sub(offset);
    const ended = performance.now();
    const stats = this.frameMeter?.sample(Number.isFinite(timestamp) ? timestamp : started, { cpu: ended - started, world: worldEnd - started, camera: cameraEnd - worldEnd, render: ended - cameraEnd });
    if (stats) {
      this.frameOverlay?.update(stats, this.renderer);
      const ratio = this.renderScale?.update(stats, this.running && !this.paused && !document.hidden);
      if (ratio && Math.abs(ratio - this.renderer.getPixelRatio()) > .001) { this.renderer.setPixelRatio(ratio); this.resize(); }
    }
  }
  _bind() {
    const bind = (el, name, fn, options) => { el.addEventListener(name, fn, options); this._listeners.push(() => el.removeEventListener(name, fn, options)); };
    bind(document, 'visibilitychange', () => { this.frameMeter.reset(); this.clock.getDelta(); this.simulationClock.reset(); });
    this.keyboard = bindKeyboard(window, { bindings: defaultBindings(), enabled: () => this.running && !this.paused && !document.querySelector('dialog[open]') && !/INPUT|TEXTAREA|SELECT/.test(document.activeElement?.tagName), action: (name, down) => this.action(name, down) });
    this._listeners.push(() => this.keyboard.dispose());
    this.mouseLook = createMouseLook(this.canvas, { active: () => this.running && !this.paused && !document.querySelector('dialog[open]'), move: (dx, dy) => turnMouseCamera(this, dx, dy), action: (name, down) => this.action(name, down), onUnlock: () => this.onEvent({ type: 'pointer-unlock' }), onError: () => this.onEvent({ type: 'pointer-error', text: '鼠标锁定未成功，请点击游戏画面重试；也可继续使用键盘操作。' }) });
    this._listeners.push(() => this.mouseLook.dispose());
    bind(window, 'blur', () => this.releaseInput());
    bind(this.canvas, 'contextmenu', e => e.preventDefault());
    bind(this.canvas, 'pointerdown', e => { this._unlockAudio(); if(this.mouseLook.pointerDown(e))return; this.pointer = { x: e.clientX, y: e.clientY, startX: e.clientX, startY: e.clientY, button: e.button, moved: false }; this.canvas.setPointerCapture?.(e.pointerId); if (e.button === 2) this.action('jump'); });
    bind(this.canvas, 'pointermove', e => { if(this.mouseLook.locked || this.locked&&!this.locked.dead&&!this.locked.disposed)return; const p = this.pointer; if (!p) return; if (Math.hypot(e.clientX - p.startX, e.clientY - p.startY) > 5) p.moved = true; if (p.moved && this.running && !this.paused) { this.cameraManualUntil = this.elapsed + 2; this.cameraAngle -= (e.clientX - p.x) * .005; this.cameraPitch = clamp(this.cameraPitch + (e.clientY - p.y) * .003, .15, .95); } p.x = e.clientX; p.y = e.clientY; });
    bind(this.canvas, 'pointerup', e => { this.mouseLook.pointerUp(e); if (this.pointer && !this.pointer.moved && this.pointer.button === 0) this.action('attack'); this.pointer = null; });
    for (const event of ['pointercancel', 'lostpointercapture']) bind(this.canvas, event, () => { this.pointer = null; this.action('guard', false); });
    bind(this.canvas, 'wheel', e => { if (!this.running || this.locked&&!this.locked.dead&&!this.locked.disposed) return; e.preventDefault(); this.cameraDistance = clamp(this.cameraDistance + e.deltaY * .008, 3.5, 18); }, { passive: false });
    bind(window, 'resize', () => this.resize());
  }
  resize() { const w = this.canvas.clientWidth || window.innerWidth, h = this.canvas.clientHeight || window.innerHeight; this.renderer.setSize(w, h, false); this.camera.aspect = w / Math.max(1, h); this.camera.updateProjectionMatrix(); }
  _unlockAudio() { if (this.muted) return; try { if (!this.audio) { this.audio = new (window.AudioContext || window.webkitAudioContext)(); this.master = this.audio.createGain(); this.master.gain.value = .25; this.master.connect(this.audio.destination); this._prewarmCombatAudio(); } if (this.audio.state === 'suspended') this.audio.resume(); } catch (_) {} }
  _loadSoundBuffer(file) {
    if (!this.soundCache.has(file.id)) this.soundCache.set(file.id, fetch(new URL(file.url, originalRoot)).then(r => { if (!r.ok) throw new Error('Original WAV missing'); return r.arrayBuffer(); }).then(b => this.audio.decodeAudioData(b)).catch(error => { this.soundCache.delete(file.id); throw error; }));
    return this.soundCache.get(file.id);
  }
  _prewarmCombatAudio() {
    if (!this.audio || !this.effectDefinitions || !this.waveFiles) return;
    // Decode the small native weapon WAV set ahead of contact. First-hit
    // feedback should not wait for a network request or audio decoding.
    const files = new Map();
    for (const [name, definition] of this.effectDefinitions) if (/^w(?:00|01|02|03|04|05|06|07|08|09|10|11)/i.test(name)) {
      for (const reference of definition.soundReferences || []) {
        const file = this.waveFiles.get(reference.replace(/\.wav$/i, '').toLowerCase());
        if (file) files.set(file.id, file);
      }
    }
    for (const file of files.values()) this._loadSoundBuffer(file).catch(() => {});
  }
  async _soundDefinition(id) {
    if (!id || this.muted || this.paused || !this.audio) return;
    const definition = this.effectDefinitions?.get(String(id).toLowerCase());
    const reference = definition?.soundReferences?.find(r => /fir/i.test(r)) || definition?.soundReferences?.[0];
    const file = reference && this.waveFiles?.get(reference.replace(/\.wav$/i, '').toLowerCase()); if (!file) return;
    try {
      const buffer = await this._loadSoundBuffer(file); if (this.muted || this.paused || this.disposed) return;
      const source = this.audio.createBufferSource(); source.buffer = buffer; source.connect(this.master); source.start(); source.onended = () => source.disconnect();
    } catch (error) { console.warn('Original sound could not be played:', file.id, error); }
  }
  dispose() {
    this.frameOverlay?.dispose();
    this.weather?.dispose();
    this.rageVfx?.dispose(); this.effectContacts?.dispose(); this.projectiles?.dispose(); this.muskets?.dispose(); this.wheels?.dispose(); this.impactFeedback?.dispose(); this.items?.dispose(); this.missionHost?.dispose(); this.disposed = true; cancelAnimationFrame(this.raf); this._listeners.forEach(fn => fn()); this.hero?.character.dispose(); this.enemies.forEach(f => { this._disposeNameplate(f); f.character.dispose(); });
    for (const data of this.mapData.values()) this._disposeMap(data); this.mapData.clear(); this.mapCache.clear();
    const geometries = new Set(), materials = new Set(), textures = new Set(); this.scene.traverse(o => { if (o.geometry) geometries.add(o.geometry); for (const m of o.material ? Array.isArray(o.material) ? o.material : [o.material] : []) { materials.add(m); if (m.map) textures.add(m.map); } });
    this.butterflyVfx?.dispose(); this.butterflyVfx = null;
    disposePhoenixSpear(this.hero?.phoenixSpear);
    disposeButterflySword(this.hero?.butterflySword); disposeButterflySword(this.butterflySwordTemplate); this.butterflySwordTemplate = null;
    disposeRaidenSword(this.raidenSwordTemplate); this.raidenSwordTemplate = null;
    this.butterflyEnvironment?.dispose(); this.butterflyEnvironment = null;
    geometries.forEach(g => g.dispose()); materials.forEach(m => m.dispose()); textures.forEach(t => t.dispose()); this.collisionMaterial.dispose(); this.renderer.dispose(); this.audio?.close();
  }
}

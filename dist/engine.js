import {NativeStealthFeedback} from './native-stealth-feedback.js';
import {validCombatTarget,acquireCombatTarget} from './combat-targeting.js';
import {nativeSameTeam} from './native-teams.js';
import {nativeStrideSpeed} from './native-movement-profile.js';
import { traversalTap, NATIVE_AIR_PHYSICS, NATIVE_ACTION_MOTION, nativeActionMomentum, NATIVE_JUMP_HOLD_SECONDS, nativeAirPose, stepNativeAirMotion, NATIVE_ROLL_POSES, nativeDashPose, NATIVE_CROUCH_POSES, NATIVE_GROUND_MOVE_POSES, NATIVE_JUMP_POSES, nativeTraversalDirection } from './native-traversal.js';
import { FixedStepClock } from './fixed-step.js';
import { NATIVE_WALL_POSES, NATIVE_WALL_PHYSICS, NATIVE_AIR_WALL_PHYSICS, nativeWallVerticalVelocity, nativeWallJumpVelocity, nativeAirWallJumpVelocity, WALL_TRAVERSAL_ADAPTER as WALL } from './native-wall-traversal.js';
import { FrameMeter, RenderScaleController, createFrameOverlay } from './frame-meter.js';
import { StaticColliderIndex } from './collision-index.js';
import { bindLocalPlayerControl, clearPlayerCommands, applyPlayerLook, usesPlayerLook, updatePlayerTurn } from './player-control.js';
import { createMouseLook, turnMouseCamera } from './mouse-look.js';
import { bindKeyboard, defaultBindings } from './keybindings.js';
import * as THREE from './vendor/three.module.js';
import { findNativeEnemy } from './native-awareness.js';
import { NativeNpcCombat, nativeNpcMove, nativeNpcInRange, nativeNpcFacing } from './native-npc-combat.js';
import { loadGmb, loadGmc } from './gmc-loader.js';
import { DEFAULT_CHARACTER_APPEARANCE, loadNativeCharacter, NATIVE_APPEARANCES } from './native-character.js';
import { appearanceCharacterName, FEATURED_APPEARANCES } from './character-appearances.js';
import { loadNativeCombat, NativeCombatController, NATIVE_WEAPONS, NATIVE_LOCOMOTION, createNativeDamageResolver, createNativeSceneDamageResolver, nativeReactionParameters, nativeHitAngle, nativeHitSelection, nativeGuardPose, nativeAttackFrames } from './native-combat.js';
import { NATIVE_MOVE_CATALOG } from './native-move-catalog.js';
import { recordNativeDirection, selectNativeMove, NATIVE_RECOVERY_INPUT_WINDOW } from './native-input.js';
import { loadOriginalSceneModels } from './native-scene-models.js';
import { NativeMissionHost } from './native-mission-host.js';
import { getNativeMission } from './native-missions.js';
import { createNativeEnvironment } from './native-environment.js';
import { NativeWeather } from './native-weather.js';
import { NativeItemSystem, useNativeScriptItem, useNativeAttackItem, useNativeSelfItem, nativeMovementScale, nativeAirMovementScale, nativeRageMaximum, nativeIsInvisible, updateNativeScriptItems, clearNativeScriptItems } from './native-items.js';
import { QIANKUN_MODE_NAMES } from './native-weapon-menu.js';
import { sweepActorCapsule, NativeProjectileSystem, NATIVE_DART_PROFILE, NativeMusketSystem, NATIVE_MUSKET_PROFILE, NativeWheelSystem, NATIVE_WHEEL_PROFILE } from './native-projectiles.js';
import { NativeImpactFeedback } from './native-impact-feedback.js';
import { NativeBloodFeedback, bloodStyleForHit } from './native-blood-feedback.js';
import { loadNativePoisonFeedback } from './native-poison-feedback.js';
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
const wallSurfaceNormal = hit => hit.face.normal.clone().applyNormalMatrix(new THREE.Matrix3().getNormalMatrix(hit.object.matrixWorld));
const ceilingProbeOffsets = [[0,0],...Array.from({length:8},(_,i)=>[Math.cos(i*Math.PI/4),Math.sin(i*Math.PI/4)])];
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
  constructor(canvas, { onUpdate = () => {}, onEvent = () => {}, onEnd = () => {}, damageResolver = null, sceneDamageResolver = null, combatRandom = Math.random } = {}) {
    this.canvas = canvas; this.onUpdate = onUpdate; this.onEvent = onEvent; this.onEnd = onEnd; this.damageResolver = damageResolver; this.sceneDamageResolver = sceneDamageResolver;
    this.combatRandom=combatRandom;
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
    this.map = 'sifang'; this.weapon = 'sword'; this.swordStyle = 'butterfly'; this.spearStyle = 'original'; this.infiniteRage = false; this.characterId = 0; this.characterAppearance = DEFAULT_CHARACTER_APPEARANCE; this.appearanceRequest = 0; this.actorSerial = 0; this.mode = 'training'; this.enemies = []; this.keys = new Set();
    this.cameraManualUntil = 0; this.cameraAngle = .4; this.cameraPitch = .45; this.cameraDistance = 8; this.cameraTarget = v3(); this.locked = null;
    this.raycaster = new THREE.Raycaster(); this.collisionMaterial = new THREE.MeshBasicMaterial({ side: THREE.DoubleSide });
    this.mapCache = new Map(); this.mapData = new Map(); this.pendingMaps = new Set(); this.weaponCache = new Map(); this.soundCache = new Map(); this.effects = []; this._listeners = []; this.mapRequest = 0; this.characterRequest = 0; this.sessionRequest = 0; this.directionBuffer = [];
    this.kills = 0; this.deaths = 0; this.totalDamage = 0; this.contactHits = 0; this.time = 0; this.matchElapsed = 0;
    bindLocalPlayerControl(this);
    // Adapter constants are explicit and provisional until recovered from Meteor.exe.
    this.hostPhysics = { speed: 100 * SCALE, gravity: NATIVE_AIR_PHYSICS.gravity, jumpVelocity: NATIVE_AIR_PHYSICS.jumpVelocity, radius: .4, step: .55, projectile: NATIVE_DART_PROFILE };
    this.impactFeedback = new NativeImpactFeedback(this.scene);
    this.bloodFeedback = new NativeBloodFeedback(this.scene);
    this.stealthFeedback = new NativeStealthFeedback();
    this._initializeProjectiles();
    this._bind(); this.resize(); this._frame = this._frame.bind(this); this.raf = requestAnimationFrame(this._frame);
    this.ready = this._initialize();
    window.__game = this;
  }
  _initializeProjectiles() {
    this.projectiles = new NativeProjectileSystem({ scene: this.scene, bodyRadius: this.hostPhysics.radius,
      canHit:(owner,target)=>!this.networkCombat||!nativeSameTeam(owner,target),
      getTargets: () => [this.hero, ...this.enemies].filter(Boolean),
      getColliders: (from, to, radius) => { const center = from.clone().add(to).multiplyScalar(.5); return this.currentMap ? this._collisionCandidates(center.x, center.z, from.distanceTo(to) / 2 + radius + 1) : []; },
      onActorHit: (shot, target, point) => this._applyNativeHit(shot.context.attacker, target, shot.context.state, shot.context.attack, point, { projectileId: shot.id }),
      onWorldHit: (shot, hit) => this._projectileWorldHit(shot, hit)
    });
    this.muskets = new NativeMusketSystem({ bodyRadius: this.hostPhysics.radius,
      canHit:(owner,target)=>!this.networkCombat||!nativeSameTeam(owner,target),
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
      canHit:(owner,target)=>!this.networkCombat||!nativeSameTeam(owner,target),
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
      const control=this._controlFor(f);
      const target = control ? control.locked || this._nearest(8,f) : f.scriptControl?.attackTarget || this.hero;
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
    const control=this._controlFor(f),target=control?null:f.scriptControl?.attackTarget;
    let direction=target&&!target.dead?target.root.position.clone().add(v3(0,1.35,0)).sub(origin).normalize():v3(Math.sin(f.root.rotation.y),0,Math.cos(f.root.rotation.y));
    if(control&&f.musketAim){
      direction=v3(-Math.sin(control.cameraAngle)*Math.cos(control.aimPitch||0),Math.sin(control.aimPitch||0),-Math.cos(control.cameraAngle)*Math.cos(control.aimPitch||0));
      // Reticle determines the world aim point; the muzzle-to-point ray still
      // checks nearby walls, so aiming around cover cannot shoot through it.
      const eye=f.root.position.clone().add(v3(0,1.65,0));this.raycaster.set(eye,direction);this.raycaster.far=80;
      const hit=this.raycaster.intersectObjects(this.currentMap.colliders||[],false)[0];this.raycaster.far=Infinity;
      let distance=hit?.distance??80;const end=eye.clone().addScaledVector(direction,80);
      for(const actor of [this.hero,...(this.enemies||[])])if(actor&&actor!==f&&!actor.dead&&!actor.disposed&&!actor.scriptRemoved){const t=sweepActorCapsule(eye,end,actor,0,this.hostPhysics.radius);if(t!=null)distance=Math.min(distance,t*80);}
      direction=eye.addScaledVector(direction,distance).sub(origin).normalize();
    }
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
      const control=this._controlFor(f);
      const target = control ? control.locked || this._nearest(24,f) : f.scriptControl?.attackTarget;
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
    const poisonReady = loadNativePoisonFeedback(this.scene).then(vfx => { if(this.disposed)vfx.dispose();else this.poisonFeedback=vfx; }).catch(error => console.warn('中毒持续特效暂未能载入：',error));
    const slowReady = loadNativePoisonFeedback(this.scene,'attrslow').then(vfx => { if(this.disposed)vfx.dispose();else this.slowFeedback=vfx; }).catch(error => console.warn('减速持续特效暂未能载入：',error));
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
    this.droppedWeapons=new Map();this.lootSerial=0;
    this.items = new NativeItemSystem({ itemRecords: combat.itemRecords,weaponItems:this.weaponItems,
      getInstances: () => [...(this.currentMap?.props?.instances.values() || []),...(this.droppedWeapons?.values()||[])],
      canReach: (actor, item) => this._canReachItem(actor, item),
      onPickup: result => {
        if(result.kind==='weapon')this._prepareWeapon(result.actor.weapon2Id).catch(()=>{});
        result.actor.pickupSerial=(result.actor.pickupSerial||0)+1;
        if(this.droppedWeapons.has(result.objectName)){result.instance.root.removeFromParent();this.droppedWeapons.delete(result.objectName);this.items.visuals.delete(result.instance);}
        const callback = `${result.objectName}_OnPickUp`;
        if (this.missionHost?.sceneVm.hasFunction(callback)) this.missionHost.call(this.missionHost.sceneVm, callback, []);
        this._soundDefinition('getitem');this.rageVfx?.playItem(result.actor,'getitem');
        this._emit(`${result.name} · ${result.healed>0?'气血 +'+result.healed:result.description}${result.refreshed?'（已刷新）':''}`, 'pickup');
      }
    });
    this.effectDefinitions = new Map((manifest.sounds?.effectDefinitions || []).map(e => [e.id.toLowerCase(), e]));
    this.waveFiles = new Map((manifest.sounds?.effects || []).map(e => [e.id.toLowerCase(), e]));
    const [hero] = await Promise.all([this._createFighter(0, null, true), this._loadMap('sifang')]);
    this.hero = hero; this.scene.add(hero.root); this._placeFighter(hero, this.currentMap.spawns[0]); await this._equip(hero, this.weapon);
    this.cameraTarget.copy(hero.root.position).add(v3(0, 1.6, 0)); this._tickCamera(1);
    await Promise.all([rageVfxReady, effectContactsReady, poisonReady, slowReady]);
    this._loadStatus('原版地图、人物、兵器与动作数据已就绪'); this._hud(); return this;
  }
  async _loadMap(name) {
    this.rageVfx?.clear(); this.stealthFeedback?.clear(); this.effectContacts?.clear(); this.projectiles?.clear('map-change'); this.muskets?.clear(); this.wheels?.clear();
    this.clearNativeScene();
    this.items?.reset(); this._clearDroppedWeapons();
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
  async _createFighter(characterId, name, hero = false, team = null, appearance = hero ? this.characterAppearance ?? 'original' : 'original') {
    const character = await loadNativeCharacter(characterId, { scale: SCALE, inPlace: true, appearance });
    if (character.appearance !== appearance) {
      const reason = character.appearanceStatus.reason;
      character.dispose();
      throw new Error(reason || '人物外观未能载入');
    }
    const f = { character, root: character.group, id: ++this.actorSerial, modelId: characterId, name: name || appearanceCharacterName(characterId, appearance), hero, team, teamMask: team, hp: 1000, maxHp: 1000, rage: 0, weapon: this.weapon, velocity: v3(), vy: 0, grounded: true, guard: false, dead: false, respawn: 0, attackHits: new Set(), lastSerial: 0, contacts: 0, heldPose: null };
    const combatData = character.combatPoses ? { ...this.combatData, poses: character.combatPoses } : this.combatData;
    // The physics track is d_base, not the pelvis' local sway. 004ce850
    // consumes that scene-motion delta independently of skin deformation.
    f.combat = new NativeCombatController(combatData, { weapon: this.weapon, sampleRoot: character.sampleSceneMotion, scale: SCALE });
    f.combat.play(NATIVE_WEAPONS[this.weapon].stance, { loop: true, force: true });
    if (!hero) { if (this.combatData.npcAi) f.npcCombat = new NativeNpcCombat(this.combatData.npcAi,{random:this.combatRandom||Math.random}); this._nameplate(f); } return f;
  }
  _placeFighter(f, spawn) {
    f.weapon2Id=f.scriptConfig?Number(f.scriptConfig.weapon2Id??f.weapon2Id)||0:0;
    this.rageVfx?.clearActor(f);
    this.effectContacts?.clearActor(f);
    clearNativeScriptItems(f);
    f.musketAim=false; f.nativeJump = null; f.jumpSequence = null; f.wallRun = null; f.wallKick = null; f.wallEntries = 0;
    f.actionMomentum=null;f.motionVelocity?.set(0,0,0);
    f.wallJumpReady=false;f.wallJumpAge=0;
    f.standingTurn=null;f.nativeAirGroundContact=false;
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
    this.stealthFeedback?.clearActor(f);
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
  async _equip(f, selection, { preserveCombat = false } = {}) {
    this.rageVfx?.clearActor(f);
    this.effectContacts?.clearActor(f);
    const request = f.equipRequest = (f.equipRequest || 0) + 1;
    const item = this.weaponItems.get(typeof selection === 'number' ? selection : NATIVE_WEAPONS[selection]?.weaponId);
    if (!item || !item.available) throw new Error(`Original weapon item ${selection} unavailable`);
    const prefix = item.modelId.toLowerCase().split('_')[0], name = Object.keys(NATIVE_WEAPONS).find(key => NATIVE_WEAPONS[key].model.split('_')[0] === prefix);
    if (!name) throw new Error(`Original weapon action family ${item.modelId} has not been ported`);
    const retained=preserveCombat?{weapon:f.weapon,weaponId:f.weaponId,weaponName:f.weaponName,weaponRecord:f.weaponRecord,weaponReach:f.weaponReach,
      mode:f.combat.weaponMode,models:(f.weaponModels||[]).map(model=>({model,parent:model.parent}))}:null;
    this.stealthFeedback?.clearActor(f);
    f.weaponPoseUnsubscribe?.(); f.weaponPoseUnsubscribe = null;
    f.weapon = name; f.weaponId = Number(item.itemId); f.weaponName = item.name; f.weaponRecord = this.combatData.weaponRecords.get(item.modelId.toLowerCase());
    if(name==='knuckle'&&this.weaponItems.get(f.weapon2Id)?.available)this._prepareWeapon(f.weapon2Id).catch(()=>{});
    f.musketAim=false;
    if(preserveCombat){f.combat.weapon=name;f.combat.weaponMode='blade';}
    else{f.combat.setWeapon(name);f.combat.play(NATIVE_WEAPONS[name].stance,{loop:true,force:true});f.heldPose=NATIVE_WEAPONS[name].stance;}
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
    } catch (error) {
      if(retained&&!this.disposed&&!f.disposed&&request===f.equipRequest){
        Object.assign(f,{weapon:retained.weapon,weaponId:retained.weaponId,weaponName:retained.weaponName,weaponRecord:retained.weaponRecord,weaponReach:retained.weaponReach});
        f.weaponModels=retained.models.map(entry=>entry.model);f.weaponModel=f.weaponModels[0];
        for(const {model,parent} of retained.models)parent?.add(model);
        if(f.combat.currentMove?.weapon!==retained.weapon&&!f.combat.currentMove?.switchesWeapon){f.combat.setWeapon(retained.weapon);f.combat.play(f.combat.stance,{force:true,loop:true});}
        else{f.combat.weapon=retained.weapon;f.combat.weaponMode=retained.mode;}
      }
      this._emit(`原版兵器读取失败：${name}`, 'info'); console.error(error);return false;
    }
    return true;
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
  _wallContact(actor,side,facing=actor.root.rotation.y,probe=null) {
    const forward=v3(Math.sin(facing),0,Math.cos(facing)),right=v3(-Math.cos(facing),0,Math.sin(facing));
    const toward=probe?.direction??(side==='front'?forward:side==='right'?right:right.negate());
    const reach=probe?.reach??this.hostPhysics.radius+WALL.reach,hits=[];
    for(const height of WALL.heights){
      this.raycaster.set(actor.root.position.clone().add(v3(0,height,0)),toward);this.raycaster.far=reach;
      const hit=this.raycaster.intersectObjects(this._collisionCandidates(actor.root.position.x,actor.root.position.z,reach+1),false).find(hit=>hit.face&&hit.distance>=.001);
      this.raycaster.far=Infinity;if(!hit)return null;
      const normal=wallSurfaceNormal(hit);if(Math.abs(normal.y)>WALL.maxNormalY)return null;
      if(normal.dot(toward)>0)normal.negate();const planeNormal=normal.clone();normal.y=0;normal.normalize();
      hits.push({normal,planeNormal,point:hit.point.clone()});
    }
    if(hits[0].planeNormal.dot(hits[1].planeNormal)<.95||Math.abs(hits[0].planeNormal.dot(hits[1].point.clone().sub(hits[0].point)))>.1)return null;
    return {...hits[0],side,forward};
  }
  _endWallTraversal(actor) {
    const wall=actor.wallRun,air=NATIVE_JUMP_POSES.forward.air;
    actor.wallRun=null;actor.nativeJump=null;
    // 004cc120 state2→0 keeps velocity;004cf7c0 maps a wall pose to152
    // once ordinary descent reaches the native<-40 speed threshold.
    // Reactions retain their own pose and must not be overwritten here.
    actor.jumpSequence=wall&&!actor.dead&&!actor.combat.busy?{start:air,air,direction:'forward',facing:wall.facing,ballistic:true}:null;
  }
  _updateWallTraversal(actor,direction,dt) {
    if(this.paused)return;
    if(actor.wallJumpReady&&!actor.grounded)actor.wallJumpAge=(actor.wallJumpAge||0)+dt;
    const control=this._controlFor(actor),forwardHeld=control?.keys.has('forward')&&!control.keys.has('back');
    const allowed=this.running&&forwardHeld&&!actor.grounded&&!actor.dead&&!actor.scriptInputBlocked&&!actor.guard&&!actor.combat.busy;
    if(actor.wallRun){
      const wall=actor.wallRun,hit=allowed&&direction.lengthSq()>0?this._wallContact(actor,wall.side,wall.facing):null;
      if(!hit||wall.elapsed+dt>NATIVE_WALL_PHYSICS.duration||hit.planeNormal.dot(wall.planeNormal)<.95||Math.abs(wall.planeNormal.dot(hit.point.clone().sub(wall.point)))>.15||direction.dot(wall.forward)<.25){this._endWallTraversal(actor);return;}
      wall.elapsed+=dt;return;
    }
    // 004ccca0: forward>0, jump permission+e4=1, vy>=0, jump age>=.1.
    if(!allowed||!actor.wallJumpReady||actor.vy<0||(actor.wallJumpAge||0)+1e-9<NATIVE_WALL_PHYSICS.entryDelay||direction.lengthSq()===0)return;
    for(const side of ['front','right','left']){
      const hit=this._wallContact(actor,side);if(!hit||direction.dot(hit.forward)<.25)continue;
      if(side==='front'?direction.dot(hit.normal)>-.25:Math.abs(direction.dot(hit.normal))>.75)continue;
      const pose=NATIVE_WALL_POSES[side].pose;if(!actor.combat.data.poses.get(pose)?.valid)continue;
      const tangent=hit.forward.clone().addScaledVector(hit.normal,-hit.forward.dot(hit.normal)).normalize();
      actor.wallRun={...hit,pose,facing:actor.root.rotation.y,elapsed:dt,velocity:side==='front'?v3():tangent.multiplyScalar(WALL.sideSpeed)};
      actor.wallEntries=(actor.wallEntries||0)+1;actor.nativeJump=null;actor.jumpSequence=null;actor.wallKick=null;actor.velocity.set(0,0,0);
      actor.wallJumpReady=false;
      return;
    }
  }
  _beginWallJump(actor,{large=false}={}) {
    const wall=actor.wallRun;if(!wall||!this.running||this.paused||actor.dead||actor.scriptInputBlocked||actor.guard||actor.combat.busy)return false;
    const hit=this._wallContact(actor,wall.side,wall.facing);
    if(!hit||hit.planeNormal.dot(wall.planeNormal)<.95||Math.abs(wall.planeNormal.dot(hit.point.clone().sub(wall.point)))>.15){this._endWallTraversal(actor);return false;}
    return this._startWallKick(actor,wall,{large});
  }
  _beginAirWallJump(actor,{large=false}={}){
    if(!this.running||this.paused||!this.currentMap||!this.raycaster||actor.grounded||actor.wallRun||actor.dead||actor.scriptInputBlocked||actor.guard||actor.combat.busy)return false;
    const facing=actor.root.rotation.y,forward=v3(Math.sin(facing),0,Math.cos(facing)),right=v3(-Math.cos(facing),0,Math.sin(facing));
    // Body-height coverage and facing-based probe basis remain Web geometry
    // adapters; the native contact range, result poses and impulse are kept.
    for(const [side,direction] of [['front',forward],['right',forward.clone().add(right).normalize()],['left',forward.clone().sub(right).normalize()]]){
      const hit=this._wallContact(actor,side,facing,{direction,reach:NATIVE_AIR_WALL_PHYSICS.reach});
      if(hit&&this._startWallKick(actor,{...hit,facing},{large,air:true}))return true;
    }
    return false;
  }
  _startWallKick(actor,wall,{large=false,air=false}={}){
    const id=NATIVE_WALL_POSES[wall.side].exit,pose=actor.combat.data.poses.get(id);
    if(!pose?.valid||!Number.isFinite(pose.link))return false;
    const incoming=actor.motionVelocity||actor.velocity;
    const velocity=air?nativeAirWallJumpVelocity({x:incoming.x,y:actor.vy,z:incoming.z},wall.planeNormal,{large}):nativeWallJumpVelocity(wall.planeNormal,{large});if(!velocity)return false;
    actor.wallRun=null;actor.grounded=false;actor.vy=velocity.y;
    actor.jumpSequence={start:id,air:pose.link,direction:wall.side,facing:wall.facing,ballistic:true};
    actor.nativeJump=null;
    // The native impulse enters ordinary state0 physics immediately; no
    // Web timer freezes horizontal input after kicking away from a wall.
    actor.wallKick=null;actor.nativeAirGroundContact=false;actor.velocity.set(velocity.x,0,velocity.z);
    actor.motionVelocity??=v3();actor.motionVelocity.copy(actor.velocity);
    actor.wallJumpReady=true;actor.wallJumpAge=0;
    actor.combat.play(id,{force:true});actor.heldPose='jump';return true;
  }
  _ceilingBlocked(position,rise) {
    if(!(rise>0)||!this.raycaster||!this.currentMap)return false;
    // Sample the collision body's perimeter too: a central ray misses eaves
    // over a shoulder. Distance zero is a valid flush ceiling contact.
    const radius=this.hostPhysics.radius,candidates=this._collisionCandidates(position.x,position.z,radius+1);
    for(const [x,z] of ceilingProbeOffsets){
      this.raycaster.set(v3(position.x+x*radius,position.y+WALL.bodyHeight,position.z+z*radius),v3(0,1,0));this.raycaster.far=rise+.05;
      const blocked=this.raycaster.intersectObjects(candidates,false).some(hit=>hit.face&&Math.abs(wallSurfaceNormal(hit).y)>.4);
      if(blocked){this.raycaster.far=Infinity;return true;}
    }
    this.raycaster.far=Infinity;return false;
  }
  _move(f, direction, speed, dt, motion = null, actionMotion=f.combat.busy) {
    if(f.combat.reacting)f.wallKick=null;
    const drifting=!f.grounded&&!actionMotion&&!f.wallRun;
    // 004ce840 writes current velocity from d_base plus copied momentum;
    // old locomotion must not remain as a second NPC velocity channel.
    if(actionMotion)f.velocity.set(0,0,0);
    else if(drifting){
      const control=this._controlFor(f),a=f.root.rotation.y;
      let inputX=direction.x,inputZ=direction.z,forwardRunning=direction.x*Math.sin(a)+direction.z*Math.cos(a)>0;
      if(control){
        const forward=f.scriptInputBlocked?0:Number(control.keys.has('forward'))-Number(control.keys.has('back'));
        const right=f.scriptInputBlocked?0:Number(control.keys.has('right'))-Number(control.keys.has('left'));
        forwardRunning=forward>0&&!control.keys.has('crouch');const side=forwardRunning?Math.fround(.2):1;
        inputX=Math.sin(a)*forward-Math.cos(a)*right*side;inputZ=Math.cos(a)*forward+Math.sin(a)*right*side;
      }
      f.vy=stepNativeAirMotion(f.velocity,f.vy,inputX,inputZ,forwardRunning,dt,nativeAirMovementScale(f),this.hostPhysics.gravity,f.nativeAirGroundContact===true);
      f.nativeAirGroundContact=false;
    }
    else{const desired=f.wallRun?f.wallRun.velocity:direction.clone().multiplyScalar(speed);if(this._controlFor(f))f.velocity.copy(desired);else f.velocity.lerp(desired,1-Math.exp(-dt*14));}
    let dx = f.velocity.x * dt + (motion?.x || 0), dz = f.velocity.z * dt + (motion?.z || 0), p = f.root.position;
    const momentum=actionMotion&&f.actionMomentum;
    if(momentum){
      momentum.x=nativeActionMomentum(momentum.x,dt,f.grounded);momentum.z=nativeActionMomentum(momentum.z,dt,f.grounded);
      dx+=momentum.x*dt;dz+=momentum.z*dt;
    }else f.actionMomentum=null;
    const from = p.clone();
    if (!this._horizontalBlocked(p, dx, 0)) p.x += dx;else{if(momentum)momentum.x=0;if(drifting)f.velocity.x=0;}
    if (!this._horizontalBlocked(p, 0, dz)) p.z += dz;else{if(momentum)momentum.z=0;if(drifting)f.velocity.z=0;}
    const ground = this._ground(p.x, p.z, p.y + this.hostPhysics.step);
    // Native 004ce850 overrides vertical velocity when the authored d_base
    // velocity has |trunc(native units/sec)|>=float0.1; otherwise gravity
    // continues. Retain that threshold to reject animation float noise.
    const authoredVertical = dt > 0 && Math.abs(Math.trunc((motion?.y || 0) / (SCALE * dt))) >= .1;
    if (f.grounded && ground && p.y - ground.point.y < .8 && !authoredVertical) p.y = ground.point.y + .015;
    else {
      f.grounded = false;
      const beforeY=p.y;
      if(f.wallRun){f.nativeJump=null;f.vy=nativeWallVerticalVelocity(f.vy,dt,this.hostPhysics.gravity);p.y+=f.vy*dt;}
      else if (authoredVertical) {
        f.nativeJump = null; f.vy = motion.y / dt; p.y += motion.y;
      } else {
        f.nativeJump = null;
        if(!drifting)f.vy-=this.hostPhysics.gravity*dt;
        p.y += f.vy * dt;
      }
      if(p.y>beforeY&&this._ceilingBlocked(v3(p.x,beforeY,p.z),p.y-beforeY)){p.y=beforeY;f.vy=0;f.nativeJump=null;f.jumpSequence=null;if(f.wallRun)this._endWallTraversal(f);}
      const landing = this._ground(p.x, p.z, p.y + Math.max(.7, -f.vy * dt + .15));
      if (landing && p.y <= landing.point.y + .04 && f.vy <= 0) { p.y = landing.point.y + .015; f.vy = 0; f.grounded = true; f.musketAim=false; f.nativeJump = null; f.jumpSequence = null; f.wallRun=null;f.wallKick=null;f.wallEntries=0;f.wallJumpReady=false;f.wallJumpAge=0; }
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
    f.motionVelocity??=v3();if(dt>0)f.motionVelocity.set((p.x-from.x)/dt,0,(p.z-from.z)/dt);
    // A pose may finish during combat.update before this motion step.
    // Its final authored segment still uses action physics; state0/1 keeps
    // the resulting current velocity rather than restoring old locomotion.
    if(actionMotion&&!f.combat.busy){f.velocity.copy(f.motionVelocity);f.actionMomentum=null;f.nativeAirGroundContact=false;}
    if (p.y < this.currentMap.bounds.min.y - 20 || Math.abs(p.x) > 3000 || Math.abs(p.z) > 3000) { if (this.mode === 'story'||this.networkCombat) { f.hp = 0; this._kill(f,{awardKill:false}); } else this._placeFighter(f, this.currentMap.spawns[f.hero ? 0 : (f.spawnIndex || 1) % this.currentMap.spawns.length]); }
  }
  _captureActionMomentum(actor,{ninja=false}={}){
    actor.standingTurn=null;
    const velocity=actor.motionVelocity||actor.velocity,scale=ninja?NATIVE_ACTION_MOTION.ninjaScale:1;
    actor.actionMomentum??=v3();actor.actionMomentum.set(Math.fround((velocity?.x||0)/SCALE*scale)*SCALE,0,Math.fround((velocity?.z||0)/SCALE*scale)*SCALE);
    actor.wallKick=null;
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
  async start({ map = 'sifang', weapon = 'sword', difficulty = 'normal', character = 0, characterAppearance = Number(character) === 0 ? DEFAULT_CHARACTER_APPEARANCE : 'original', mode = 'training' } = {}) {
    if (mode === 'story') {
      const mission = getNativeMission(map);
      if (!mission) throw new Error(`Original story mission ${map} is not available yet`);
      map = mission.mapId;
    }
    const request = ++this.sessionRequest;
    await this.ready; if (request !== this.sessionRequest || this.disposed) return;
    this.projectiles?.clear('restart'); this.projectiles?.pause(false); this.muskets?.clear(); this.wheels?.clear(); this.muskets?.pause(false); this.wheels?.pause(false); this.impactFeedback?.clear(); this.rageVfx?.clear(); this.stealthFeedback?.clear(); this.effectContacts?.clear(); this.items?.reset(); this._clearDroppedWeapons(); this.missionHost?.dispose(); this.missionHost = null; this.missionState = null; this.storyResult = null;
    this.keyboard?.reset(); this.pointer = null; this.keys.clear(); this.traversalTap=null; this.directionBuffer = []; this.recoveryAttack = null; this.running = false; this.paused = false; this.mode = mode === 'story' ? 'story' : 'training';
    if (map !== this.map) await this._loadMap(map);
    if (request !== this.sessionRequest || this.disposed) return;
    this.currentMap.props?.reset?.();
    if (this.mode === 'story') { character = 0; characterAppearance = 'original'; }
    await this.setCharacter(character, characterAppearance);
    if (request !== this.sessionRequest || this.disposed) return;
    this.difficulty = difficulty;
    for (const f of this.enemies) { f.disposed = true; this._disposeNameplate(f); f.character.dispose(); f.root.removeFromParent(); } this.enemies = [];
    this.hero.scriptConfig = null; this.hero.scriptControl = null; this.hero.scriptInputBlocked = false; this.hero.team = this.hero.teamMask = 1;
    this.kills = 0; this.deaths = 0; this.totalDamage = 0; this.contactHits = 0; this.matchElapsed = 0; this.time = 0; this.locked = null;if(this.localControl)this.localControl.autoLockEnabled=true;
    if (this.mode === 'story') {
      this._loadStatus('正在执行原版关卡脚本与载入原 NPC…');
      const host = await NativeMissionHost.create(this, { mapId: this.currentMap.id });
      if (request !== this.sessionRequest || this.disposed) { host.dispose(); return; }
      this.missionHost = host; await host.start();
      if (request !== this.sessionRequest || this.disposed) { host.dispose(); return; }
    } else {
      this.weapon = NATIVE_WEAPONS[weapon] ? weapon : 'sword'; await this._equip(this.hero, this.weapon); this._placeFighter(this.hero, this.currentMap.spawns[0]);
      if (mode !== 'network') {
        await this._spawnTrainingOpponents(request);
      }
    }
    if (request !== this.sessionRequest || this.disposed) return;
    this._resetWorldClock(); this.running = true; this.cameraManualUntil = 0; this.cameraAngle = this.currentMap.id === 'sn01' ? Math.PI / 2 : 0; this.cameraPitch = this.currentMap.cameraPitch ?? .4; this.cameraDistance = this.currentMap.cameraDistance ?? 8;
    this.cameraTarget.copy(this.hero.root.position).add(v3(0, 1.5, 0)); this._tickCamera(1); this._unlockAudio();
    this._emit(this.mode === 'story' ? `原版${this.currentMap.entry.name || this.currentMap.id}` : '原版动作演练开始', 'info'); this._hud();
  }
  async _spawnTrainingOpponents(request) {
    const appearances = FEATURED_APPEARANCES.filter(id => id !== this.hero.character.appearance).slice(0, 3);
    const results = await Promise.allSettled(appearances.map(id => this._createFighter(NATIVE_APPEARANCES[id].characterId, null, false, 2, id)));
    const actors = results.filter(result => result.status === 'fulfilled').map(result => result.value);
    const failure = results.find(result => result.status === 'rejected');
    if (failure || request !== this.sessionRequest || this.disposed) {
      for (const actor of actors) { actor.disposed = true; this._disposeNameplate(actor); actor.character.dispose(); }
      if (failure && request === this.sessionRequest && !this.disposed) throw failure.reason;
      return;
    }
    const heroPos = this.hero.root.position;
    const spawns = this.currentMap.spawns;
    const ordered = spawns.map((spawn, i) => ({ ...spawn, index: i })).filter(spawn => flatDistance(spawn.position, heroPos) > 4).sort((a, b) => flatDistance(a.position, heroPos) - flatDistance(b.position, heroPos));
    await Promise.all(actors.map(async (actor, i) => {
      const spawn = ordered[i] || spawns[(i + 1) % spawns.length];
      actor.spawnIndex = spawn.index ?? i + 1;
      actor.slot = i;
      this._placeFighter(actor, spawn);
      this.scene.add(actor.root);
      this.enemies.push(actor);
      await this._equip(actor, ['sword', 'blade', 'spear'][i]);
    }));
  }
  async menu(map = this.map, selection) {
    this.mouseLook?.release();
    this.keyboard?.reset();
    const request = ++this.sessionRequest;
    this.projectiles?.clear('menu'); this.projectiles?.pause(false); this.muskets?.clear(); this.wheels?.clear(); this.muskets?.pause(false); this.wheels?.pause(false); this.impactFeedback?.clear(); this.rageVfx?.clear(); this.stealthFeedback?.clear(); this.effectContacts?.clear(); this.items?.reset(); this._clearDroppedWeapons(); this.missionHost?.dispose(); this.missionHost = null; this.missionState = null; this.mode = 'training';
    this.running = false; this.paused = false; this.keys.clear(); this.traversalTap=null; this.pointer = null; this.locked = null; this.directionBuffer = [];
    await this.ready; if (this.disposed || request !== this.sessionRequest) return;
    if (map !== this.map) await this._loadMap(map);
    if (this.disposed || request !== this.sessionRequest) return;
    this.currentMap.props?.reset?.();
    for (const f of this.enemies) { f.disposed = true; this._disposeNameplate(f); f.character.dispose(); } this.enemies = [];
    if (selection) await this.setCharacter(selection.character, selection.characterAppearance);
    if (this.disposed || request !== this.sessionRequest) return;
    this.hero.guard = false; this.hero.scriptConfig = null; this.hero.scriptInputBlocked = false; this._placeFighter(this.hero, this.currentMap.spawns[0]); this.hero.root.rotation.y = -.3; this._resetWorldClock(); this._hud();
  }
  requestMouseLock() { return this.mouseLook?.request(); }
  setKeyBindings(bindings) { this.keyboard?.setBindings(bindings);this.mouseLook?.setBindings(bindings); }
  releaseInput({releaseMouse=true}={}) { clearPlayerCommands(this.localControl||this); this.keyboard?.reset(); if(releaseMouse)this.mouseLook?.release(); this.keys.clear(); this.pointer=null; if(this.hero)this.hero.guard=false; }
  pause(value = true) { this.releaseInput({releaseMouse:!!value}); if(this.paused !== !!value)this._resetWorldClock(); this.paused = !!value; this.projectiles?.pause(this.paused); this.muskets?.pause(this.paused); this.wheels?.pause(this.paused); if (this.master) this.master.gain.value = this.paused || this.muted ? 0 : .25; this._hud(); }
  async setCharacter(id = 0, appearance = Number(id) === 0 ? DEFAULT_CHARACTER_APPEARANCE : 'original') {
    const request = ++this.characterRequest;
    await this.ready;
    if (this.disposed || request !== this.characterRequest) return;
    id = Number(id);
    if (id === this.characterId) {
      if (this.hero.character.appearance !== appearance || this.characterAppearance !== undefined && this.characterAppearance !== appearance) {
        const status = await this.setCharacterAppearance(appearance);
        if (request === this.characterRequest && (!status?.available || status.appearance !== appearance)) {
          throw new Error(status?.reason || '人物外观未能载入');
        }
      }
      if (request === this.characterRequest) this.hero.name = appearanceCharacterName(id, appearance);
      return;
    }
    const actor = await this._createFighter(id, null, true, null, appearance);
    if (this.disposed || request !== this.characterRequest) { actor.disposed = true; actor.character.dispose(); return; }
    this.characterAppearance = appearance;
    if (this.hero) { this.stealthFeedback?.clearActor(this.hero); this.rageVfx?.clearActor(this.hero); this.effectContacts?.clearActor(this.hero); disposePhoenixSpear(this.hero.phoenixSpear); this.hero.disposed = true; this.hero.character.dispose(); } this.hero = actor; this.characterId = id; this.scene.add(actor.root); this._placeFighter(actor, this.currentMap.spawns[0]); await this._equip(actor, this.weapon); this._hud();
  }
  async setCharacterAppearance(mode = 'original') {
    if (!Object.hasOwn(NATIVE_APPEARANCES, mode)) throw new Error('Unknown character appearance');
    const request = this.appearanceRequest = (this.appearanceRequest || 0) + 1; this.characterAppearance = mode;
    await this.ready; if (this.disposed || request !== this.appearanceRequest) return this.hero?.character.appearanceStatus;
    const actor = this.hero; this.stealthFeedback?.clearActor(actor);
    const status = await actor.character.setAppearance(mode);
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
    return this._switchInventoryWeapon(this.hero);
  }
  async _prepareWeapon(id){
    const item=this.weaponItems.get(id);if(!item?.available)throw Error('兵器资源不可用');
    for(const name of item.modelIds.map(id=>id.toLowerCase()))if(!this.weaponCache.has(name))this.weaponCache.set(name,this._readWeapon(name).catch(error=>{this.weaponCache.delete(name);throw error;}));
    return Promise.all(item.modelIds.map(name=>this.weaponCache.get(name.toLowerCase())));
  }
  async _switchInventoryWeapon(actor){
    if(!actor||!this.running||this.paused||actor.dead||actor.scriptInputBlocked||actor.combat.busy||actor.switchingWeapon)return;
    const next=actor.weapon2Id;if(!this.weaponItems.has(next))return;
    const session=this.sessionRequest,previous=actor.weaponId;actor.switchingWeapon=true;
    try{await this._prepareWeapon(next);if(this.disposed||session!==this.sessionRequest||actor.disposed||actor.dead||actor.weapon2Id!==next||!this.running||this.paused||actor.scriptInputBlocked||actor.combat.busy)return;
      await this._equip(actor,next);actor.weapon2Id=previous;if(actor===this.hero)this.weapon=actor.weapon;this._hud();
    }catch(error){this._emit('兵器载入失败，保留原装备','info');console.warn(error);}finally{actor.switchingWeapon=false;}
  }
  _switchWeaponForMove(actor){
    const item=this.weaponItems.get(actor.weapon2Id);
    if(actor.weapon!=='knuckle'||!item?.available)return;
    // 004e3d20 emits actor command0x2c for groups110/111 (412/413).
    // Keep the authored side-step/cancel graph while changing the inventory.
    const previous=actor.weaponId,next=actor.weapon2Id;
    actor.weapon2Id=previous;
    const loading=this._equip(actor,next,{preserveCombat:true}).then(ok=>{
      if(ok===false&&actor.weaponId===previous){actor.weapon2Id=next;if(actor===this.hero)this.weapon=actor.weapon;}
    }).catch(error=>{console.warn('换兵招式的兵器未能载入',error);});
    if(actor===this.hero)this.weapon=actor.weapon;
    return loading;
  }
  _clearDroppedWeapons(){for(const drop of this.droppedWeapons?.values()||[])drop.root.removeFromParent();this.droppedWeapons?.clear();this.replicaLootDesired=new Map();this.combatFeedbackEvents=[];this.bloodFeedback?.clear();this.poisonFeedback?.clear();this.slowFeedback?.clear();}
  _lootSnapshot(){return {consumed:[...(this.items?.consumedNames||[])],drops:[...(this.droppedWeapons?.values()||[])].filter(drop=>drop.attributes.active).map(drop=>({name:drop.name,weaponId:drop.weaponId,position:drop.root.position.toArray()}))};}
  _combatFeedbackSnapshot(){return (this.combatFeedbackEvents||[]).filter(event=>(this.matchElapsed||0)-event.time<=.6);}
  _playCombatFeedback(event,local=false){
    const point=v3(...event.point),direction=v3(...event.direction);
    this.impactFeedback?.emit({point,direction,guarded:event.guarded,knockdown:event.knockdown,local});
    this.bloodFeedback?.emit({point,direction,guarded:event.guarded,damage:event.blood?1:0,style:event.bloodStyle});
    if(event.sound)this._soundDefinition(event.sound);
  }
  _applyLootState(state){
    if(!state)return;this.droppedWeapons ||= new Map();const consumed=new Set(state.consumed);for(const instance of this.currentMap.props?.instances.values()||[])if(consumed.has(instance.name)){instance.setActive(false);instance.setCollision(false);}
    this.replicaLootDesired=new Map(state.drops.map(drop=>[drop.name,drop]));
    for(const [name,drop] of this.droppedWeapons)if(!this.replicaLootDesired.has(name)){drop.root.removeFromParent();this.droppedWeapons.delete(name);this.items?.visuals.delete(drop);}
    this.pendingLootLoads ||= new Set();
    for(const drop of state.drops){if(this.droppedWeapons.has(drop.name)||this.pendingLootLoads.has(drop.name))continue;this.pendingLootLoads.add(drop.name);const session=this.sessionRequest;
      this._prepareWeapon(drop.weaponId).then(models=>{const latest=this.replicaLootDesired.get(drop.name);if(this.lootReplica&&!this.disposed&&session===this.sessionRequest&&latest?.weaponId===drop.weaponId)this._spawnDroppedWeapon(drop.weaponId,v3(...latest.position),drop.name,models);}).catch(()=>{}).finally(()=>this.pendingLootLoads.delete(drop.name));
    }
  }
  _spawnDroppedWeapon(id,position,name,templates,owner=null){
    const item=this.weaponItems.get(id);if(!item)return null;
    const root=new THREE.Group(),model=new THREE.Group();root.name=name;root.position.copy(position);root.scale.setScalar(SCALE);root.add(model);
    for(const template of templates)model.add(template.clone(true));this.scene.add(root);
    const drop={name,root,model,source:{properties:{model:item.modelId}},attributes:{active:1,interactive:1,collision:0},dropOwner:owner,weaponId:id,
      setActive(value){this.attributes.active=Number(value);root.visible=!!value;},setCollision(){}};
    this.droppedWeapons.set(name,drop);return drop;
  }
  async dropWeapon(actor=this.hero){
    if(!actor||!this.running||this.paused||actor.dead||actor.scriptInputBlocked||actor.combat.busy||actor.switchingWeapon||!this.weaponItems.has(actor.weapon2Id)||this.droppedWeapons.size>=64)return;
    const id=actor.weapon2Id,session=this.sessionRequest;actor.switchingWeapon=true;
    try{const templates=await this._prepareWeapon(id);if(this.disposed||session!==this.sessionRequest||actor.dead||actor.disposed||actor.weapon2Id!==id||!this.running||this.paused||actor.scriptInputBlocked||actor.combat.busy)return;
      const position=actor.root.position.clone();const floor=this._ground(position.x,position.z,position.y+1);if(floor)position.y=floor.point.y+.12;
      this._spawnDroppedWeapon(id,position,`web-drop-${++this.lootSerial}`,templates,actor);actor.weapon2Id=null;this._emit(`丢下${this.weaponItems.get(id).name}`,'info');this._hud();
    }catch(error){this._emit('兵器载入失败，未丢弃装备','info');console.warn(error);}finally{actor.switchingWeapon=false;}
  }
  setInfiniteRage(enabled) {
    this.infiniteRage = enabled === true;
    if (this.infiniteRage && this.hero) this.hero.rage = 100;
    this._hud();
  }
  setMuted(value) { this.muted = !!value; if (this.master) this.master.gain.value = value ? 0 : .25; }
  setQuality(value) { this.quality = value; this.butterflyVfx?.setQuality(value); this._applyMapPresentation(); this.renderScale.reset(Math.min(window.devicePixelRatio || 1, value === 'low' ? 1 : 2)); this.renderer.setPixelRatio(this.renderScale.ratio); this.resize(); }
  setDamageResolver(resolver) { if (resolver !== null && typeof resolver !== 'function') throw new Error('Damage resolver must be a function or null'); this.damageResolver = resolver; }
  _beginJump(actor,{large=false}={}) {
    if (!actor.grounded || actor.combat.busy) return false;
    const control=this._controlFor(actor),direction=nativeTraversalDirection(control?.keys)||'forward';
    const sequence=NATIVE_JUMP_POSES[direction];
    const pose = actor.combat.data.poses.get(sequence.start);
    if(!pose?.valid)return false;
    // 004cf760 chooses a directional pose;004cf5a0 changes vertical speed
    // and state without reorienting the model. Consume actual look input,
    // but do not snap a keyboard-only jump toward an unrelated camera.
    if(usesPlayerLook(control))applyPlayerLook(actor,control);
    actor.jumpSequence={...sequence,direction,facing:actor.root.rotation.y,ballistic:true};actor.wallEntries=0;actor.wallRun=null;actor.wallKick=null;
    actor.wallJumpReady=true;actor.wallJumpAge=0;
    // 004cf5a0 changes state0 without clearing the previous floor-contact
    // flag+35c; the first free-flight step can retain ground acceleration.
    actor.nativeAirGroundContact=actor.grounded;
    actor.musketAim=false; actor.grounded = false; actor.vy = large?NATIVE_AIR_PHYSICS.largeJumpVelocity:this.hostPhysics.jumpVelocity;
    // 004cf5a0 enters state0 with physical vertical speed; ordinary jump
    // animation must not add its d_base elevation on top of that flight.
    actor.nativeJump=null;
    actor.combat.play(sequence.start, { force: true }); actor.heldPose = 'jump'; return true;
  }
  _finishJumpCharge(actor,control){
    const charge=control?.jumpCharge;if(!charge)return false;control.jumpCharge=null;
    if(charge.actor!==actor||!this.running||this.paused||actor.dead||actor.disposed||actor.scriptInputBlocked||actor.combat.busy||actor.guard)return false;
    if(usesPlayerLook(control))applyPlayerLook(actor,control);
    const duration=actor.playerControl?Math.max(0,(control.inputTime??charge.time)-charge.time):Math.max(charge.elapsed,(this.elapsed??charge.time)-charge.time);
    control.directionBuffer=[];
    const options={large:duration+1e-9>=NATIVE_JUMP_HOLD_SECONDS};
    return actor.grounded?this._beginJump(actor,options):actor.wallRun?this._beginWallJump(actor,options):this._beginAirWallJump(actor,options);
  }
  _updateJumpCharge(actor,control,dt){
    const charge=control?.jumpCharge;if(!charge)return;
    if(actor.dead||actor.disposed||actor.scriptInputBlocked||actor.guard){control.jumpCharge=null;return;}
    charge.elapsed+=dt;
    // Remote hold duration follows the client's ordered event clock. Host
    // polling delay alone must not turn a short tap into a large jump.
    const elapsed=actor.playerControl?Math.max(0,(control.inputTime??charge.time)-charge.time):charge.elapsed;
    if(elapsed>NATIVE_JUMP_HOLD_SECONDS+1e-9&&!actor.combat.busy)this._finishJumpCharge(actor,control);
  }
  _controlFor(actor) { return actor?.playerControl || (actor?.hero ? this.localControl || this : null); }
  _beginRoll(direction, poseId, actor = this.hero, control = this._controlFor(actor)) {
    if(!this.running||this.paused||!actor||actor.dead||!actor.grounded||actor.scriptInputBlocked||actor.combat.busy||!control?.keys.has('crouch')||poseId!==NATIVE_ROLL_POSES[direction])return false;
    if(!actor.combat.data.poses.get(poseId)?.valid)return false;
    if(!actor.combat.play(poseId,{motion:true,context:{kind:'roll',direction,poseId,name:({forward:'向前翻滚',back:'向后翻滚',left:'向左翻滚',right:'向右翻滚'})[direction]}}))return false;
    this._captureActionMomentum(actor);
    actor.root.rotation.y=control.cameraAngle+Math.PI;actor.velocity.set(0,0,0);actor.guard=false;actor.heldPose=null;clearPlayerCommands(control,{preserveJump:true});
    return true;
  }
  _beginDash(direction,poseId,actor=this.hero,control=this._controlFor(actor)) {
    if(!this.running||this.paused||!actor||actor.dead||!actor.grounded||actor.scriptInputBlocked||actor.guard||actor.combat.busy||!control||control.keys.has('crouch')||poseId!==nativeDashPose(actor.weapon,direction))return false;
    if(!actor.combat.play(poseId,{motion:true,context:{kind:'dash',direction,poseId,name:'闪避'}}))return false;
    this._captureActionMomentum(actor);
    actor.root.rotation.y=control.cameraAngle+Math.PI;actor.velocity.set(0,0,0);actor.guard=false;actor.heldPose=null;control.recoveryAttack=null;
    return true;
  }
  _actionFighter(actor, control, name, active = true) {
    if(!actor || !control)return;
    if(['switch','drop','pickup'].includes(name)){if(active){if(name==='switch')return this._switchInventoryWeapon(actor);if(name==='drop')return this.dropWeapon(actor);return this._tryPickupActor(actor);}return;}
    const inputTime=control.inputTime??this.elapsed;
    if(name==='clear'){control.keys.clear();clearPlayerCommands(control);actor.guard=false;actor.musketAim=false;return;}
    if(name==='jump'){
      if(!active){this._finishJumpCharge(actor,control);return;}
      if(!this.running||this.paused||actor.dead||actor.disposed||actor.scriptInputBlocked||actor.combat.busy||actor.guard)return;
      if(!control.jumpCharge){if(actor===this.hero)this._unlockAudio();control.jumpCharge={actor,time:inputTime,elapsed:0};}
      return;
    }
    if (name === 'guard') {
      const held = active && this.running && !this.paused && !actor.dead;
      if(held&&usesPlayerLook(control))applyPlayerLook(actor,control);
      if (held) control.keys.add('guard'); else control.keys.delete('guard');
      if(held)actor.musketAim=false;
      actor.guard = held && !actor.scriptInputBlocked && !actor.wallRun && (actor.grounded||actor.combat.reactionPhase==='guard') && (!actor.combat.busy || actor.combat.reactionPhase === 'guard');
      return;
    }
    if (active && actor.scriptInputBlocked) return;
    if (name === 'crouch') { if(!active)control.traversalTap=null; if (active && this.running && !this.paused) control.keys.add('crouch'); else control.keys.delete('crouch'); return; }
    if (['forward','back','left','right'].includes(name)) {
      if(active&&this.running&&!this.paused&&!actor.dead){
        if(!control.keys.has(name)){
          const crouched=control.keys.has('crouch'),tap=traversalTap(control.traversalTap,{direction:name,time:inputTime,crouched,weapon:actor.weapon,allowed:actor.grounded&&!actor.combat.busy&&!actor.guard&&!actor.musketAim});control.traversalTap=tap.tap;
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
    else if (name === 'lock' && !actor.musketAim) { this._toggleCombatLock(actor,control); if(actor===this.hero){this.cameraManualUntil = 0;this._hud();} }
  }
  action(name, active = true) {
    if(['switch','drop','pickup'].includes(name)){if(active){if(name==='switch')return this.switchWeapon();if(name==='drop')return this.dropWeapon();this._tryPickupActor(this.hero);this._hud();}return;}
    if(['clear','guard','crouch','forward','back','left','right','attack','jump','lock'].includes(name))return this._actionFighter(this.hero,this._controlFor(this.hero),name,active);
    if (!active || !this.running || this.paused || !this.hero || this.hero.dead || this.hero.scriptInputBlocked) return;
    this._unlockAudio();
    if (name === 'fury' || name === 'dodge') this._emit('该动作的原版指令与条件正在逆向，当前不使用替代招式', 'info');
    else if (/^pose:\d+$/.test(name)) this.hero.combat.play(Number(name.slice(5)));

  }
  _beginAttack(f, savedInput = null) {
    const control=this._controlFor(f);
    // 004cff30 accepts actor states0/1/3/6, excluding wall state2.
    if (f.dead || f.disposed || f.scriptRemoved || f.scriptCrouched || f.wallRun || f.combat.reacting || control && f.scriptInputBlocked) return false;
    if(usesPlayerLook(control))applyPlayerLook(f,control);
    // Native musket state 004deca0: first ground attack enters ready pose212;
    // crouch/aim blocks movement (004ded10). Subsequent attacks use POS/ACT.
    if(control&&f.weapon==='musket'&&!f.musketAim){
      if(!f.grounded||f.guard||control.keys.has('crouch')||f.combat.busy)return false;
      f.musketAim=true;control.aimPitch=0;control.cameraAngle=f.root.rotation.y-Math.PI;control.locked=null;f.velocity.set(0,0,0);
      f.root.rotation.y=control.cameraAngle+Math.PI;f.combat.play(212,{force:true});f.heldPose=212;control.directionBuffer=[];return true;
    }
    if(control&&f.musketAim&&f.combat.timeline?.pose.id===212&&!f.combat.timeline.finished)return false;
    // Free attacks retain the player's chosen facing. An unlocked opponent
    // behind the player must not turn an intended gate/front attack around.
    const target = control ? this._attackTarget(f,control) : f.scriptControl?.attackTarget || this.hero;
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
    const outgoingSelfCast=f.combat.busy&&f.combat.timeline?.canCancel&&!f.combat.poseBlend
      ?{pose:f.combat.timeline.pose,source:f.combat.timeline.pose.source,frame:f.combat.timeline.frame,serial:f.combat.serial,context:f.combat.currentMove,effectTime:f.combat._effectElapsed}:null;
    const accepted = f.combat.attack({ air: !f.grounded, poseId: move?.poseId ?? null, context: move,
      // Input posture is checked when the command is accepted. An ACT-legal
      // queued continuation stays attached to that active predecessor if it
      // lands before the compiled transition frame (e.g. spear282 ->283).
      // Rage and actor lifetime are still checked again at the actual start.
      canStart: command => !f.dead && !f.disposed && !f.scriptRemoved && (!command || (f.hero && this.infiniteRage || (f.rage || 0) >= command.rage) &&
        ((command.stance === 'air') === !f.grounded || f.combat.busy && command.continuationOf?.includes(f.combat.currentMove?.poseId))),
      onAccept:()=>this._captureActionMomentum(f,{ninja:f.weapon==='ninja'}),
      onStart: command => {
        // Queued ACT transitions start later than the click: use the target's
        // current position at the actual start, rather than a captured position.
        if(control&&!f.musketAim){const current=this._attackTarget(f,control);if(current)this._face(f,current.root.position);}
        if (!command) return;
        if(command.switchesWeapon)this._switchWeaponForMove(f);
        f.rage = f.hero && this.infiniteRage ? 100 : Math.max(0, (f.rage || 0) - command.rage);
        if (f.hero) this.onEvent?.({ type: 'move', text: command.name, moveId: command.id, poseId: command.poseId, command: command.command, rageCost: command.rage });
      }
    });
    if (accepted) {
      // 004cff30 flushes pending parameter18 when an ACT request is accepted
      // into native state2. Early Web buffering alone must not grant the item.
      if(outgoingSelfCast)this._commitNativeSelfItem(f,outgoingSelfCast);
      f.guard = false; f.heldPose = 'attack';
      if (control) { control.directionBuffer = []; control.recoveryAttack = null; }
    }
    return accepted;
  }
  _toggleCombatLock(actor,control){
    if(control.locked){control.locked=null;control.autoLockEnabled=false;}
    else{control.autoLockEnabled=true;control.locked=acquireCombatTarget(actor,[this.hero,...this.enemies],{angle:control.cameraAngle+Math.PI,range:24,minDot:-1,lineOfSight:(a,b)=>this.hasScriptLineOfSight(a,b)});}
    if(actor===this.hero)this._emit(control.locked?'锁定 · '+control.locked.name:control.autoLockEnabled?'自动锁定已开启 · 攻击前方对手':'自由攻击 · Q 重新锁定','info');
  }
  _attackTarget(actor,control){
    if(control.locked&&!validCombatTarget(actor,control.locked))control.locked=null;
    if(!control.locked&&control.autoLockEnabled!==false&&!actor.musketAim&&!['musket','dart','wheel'].includes(actor.weapon))control.locked=acquireCombatTarget(actor,[this.hero,...this.enemies],{angle:control.cameraAngle+Math.PI,lineOfSight:(a,b)=>this.hasScriptLineOfSight(a,b)});
    return control.locked;
  }
  _nearest(range = Infinity, actor = this.hero) { let best = null; for (const f of [this.hero,...this.enemies]) { if(!f||f===actor)continue; const d = flatDistance(f.root.position, actor.root.position); if (!f.dead && !f.disposed && !f.scriptRemoved && !nativeIsInvisible(f) && !nativeSameTeam(f,actor) && d < range) { range = d; best = f; } } return best; }
  _npcCombatAction(f, target, due, { requested = false, allowed = true, reach = 0 } = {}) {
    if (!target || !allowed || target.dead || target.disposed || target.scriptRemoved || !this.hasScriptLineOfSight(f, target)) return;
    if (requested) {
      if (flatDistance(f.root.position, target.root.position) <= reach && !f.combat.busy && this._beginAttack(f)) f.scriptAttackRequested = false;
      return;
    }
    if (!due || !f.npcCombat) return;
    const profile = f.npcCombat.data.profiles[f.weapon];
    if (!nativeNpcInRange(f, target, profile)) { f.npcCombat.guard = false; f.npcCombat.crouch = false; f.guard = false; return; }
    const choice = f.npcCombat.choose(f, { canAttack: () => nativeNpcFacing(f, target, profile) });
    if (choice.kind === 'attack' && choice.program != null) {
      const move = nativeNpcMove(f, choice.program, this.elapsed);
      const accepted = !!move && this._beginAttack(f, { npcMove: move });
      this.onEvent?.({ type: 'npc-decision', actorId: f.scriptId ?? f.id, kind: 'attack', category: choice.category,
        program: choice.program, poseId: move?.poseId, accepted });
    } else this.onEvent?.({ type: 'npc-decision', actorId: f.scriptId ?? f.id, kind: choice.kind, defense: choice.defense });
    f.guard = f.npcCombat.guard && f.grounded && !f.wallRun && !f.combat.busy;
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
    if (f.dead) { const state = f.combat.update(dt); if (state) f.character.setPoseFrame(state.source, state.frame); f.respawn -= dt; if (f.respawn <= 0) this._placeFighter(f, this.currentMap.spawns[(f.spawnIndex||0)%this.currentMap.spawns.length]); return; }
    const npcDue = !control && f.npcCombat?.advance(dt, f.scriptConfig, {
      hasTarget: !!(f.scriptControl?.attackTarget || f.awarenessTarget), paused: !!f.scriptControl?.paused });
    // Only the two contacting actors pause; mission time, projectiles and
    // other fighters keep running. These short durations are Web feedback.
    if (f.hitstop > 0) { const pause = Math.min(dt, f.hitstop); f.hitstop -= pause; dt -= pause; if (dt <= 1e-7) return; }
    updatePlayerTurn(f,control,dt);
    this._updateJumpCharge(f,control,dt);
    let direction = v3(), speed = this.hostPhysics.speed * nativeMovementScale(f);
    if (control && control.recoveryAttack) {
      const input = control.recoveryAttack;
      if (input.actor !== f || input.weaponId !== f.weaponId || this.elapsed > input.expires || input.air !== !f.grounded || f.scriptInputBlocked) control.recoveryAttack = null;
      else if (!f.combat.reacting) { control.recoveryAttack = null; this._beginAttack(f, input); }
    }
    if (control) f.guard = control.keys.has('guard') && !f.scriptInputBlocked && !f.wallRun && (f.grounded||f.combat.reactionPhase==='guard') && (!f.combat.busy || f.combat.reactionPhase === 'guard');
    if (f.combat.reacting || f.scriptCrouched || f.combat.busy && ['roll','dash'].includes(f.combat.currentMove?.kind)) {
      if (f.combat.reactionPhase !== 'guard') f.guard = false;
    } else if (control) {
      if (f.scriptInputBlocked) f.guard = false;
      direction = f.scriptInputBlocked ? v3() : this._moveDirection(control);
      if(f.wallRun&&!f.combat.busy)f.root.rotation.y=f.wallRun.facing;
      else if (control.locked && validCombatTarget(f,control.locked)) this._face(f, control.locked.root.position, dt);
      else if(!f.grounded&&f.jumpSequence&&!f.combat.busy&&!f.guard){if(usesPlayerLook(control))applyPlayerLook(f,control);}
      else if (!f.combat.busy && !f.guard && (control.keys.has('crouch') || usesPlayerLook(control))) {
        if(usesPlayerLook(control))applyPlayerLook(f,control);
        else this._face(f, f.root.position.clone().add(v3(-Math.sin(control.cameraAngle),0,-Math.cos(control.cameraAngle))),dt);
      }
      else if (direction.lengthSq() > 0 && !f.combat.busy && !f.guard) this._face(f, f.root.position.clone().add(direction), dt);
    } else if (f.scriptControlled) {
      const control = f.scriptControl;
      f.guard = !!(control?.guard || !control?.paused && f.npcCombat?.guard) && f.grounded && !f.wallRun && !f.combat.busy; speed *= Number(control?.speedScale ?? 1) * .68;
      if (control && !control.paused) {
        const target = control.attackTarget, targetAlive = target && !target.dead && !target.disposed;
        const moveTarget = control.moveTarget, reach = f.weaponReach || (f.weapon === 'spear' ? 3.8 : 2.3);
        // Dijkstra/waypoint navigation is a Web adapter. Elevated source links
        // (e.g. sn09 WP7→0) need the same original takeoff as the player; a
        // walking-only follower would fall when the source floors disappear.
        if (moveTarget && Number(f.scriptConfig?.Jump) > 0 && moveTarget.y - f.root.position.y > this.hostPhysics.step + .3 && flatDistance(moveTarget, f.root.position) < 8) this._beginJump(f,{large:moveTarget.y-f.root.position.y>3.3});
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
        f.guard = !!f.npcCombat?.guard && f.grounded && !f.wallRun && !f.combat.busy;
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
    if(f.musketAim&&(f.weapon!=='musket'||f.combat.reacting||!f.grounded||f.scriptInputBlocked))f.musketAim=false;
    if(f.musketAim){direction.set(0,0,0);f.root.rotation.y=(control?.cameraAngle??f.root.rotation.y-Math.PI)+Math.PI;}
    if(f.guard)speed*=control?0:.3;
    if(f.musketAim)speed=0;
    if (f.combat.busy) speed = 0;
    this._updateWallTraversal(f,direction,dt);
    if (!f.combat.busy) {
      const current=f.combat.timeline?.pose.id,sequence=f.jumpSequence;
      const startingJump=!f.grounded&&!!sequence&&sequence.start===current&&!f.combat.timeline.finished;
      if(f.wallRun){
        if(current!==f.wallRun.pose)f.combat.play(f.wallRun.pose,{loop:true,force:true});
        f.heldPose=f.wallRun.pose;
      }else if(!f.grounded&&(!f.guard||startingJump)){
        // Native free-flight keeps the current clip until descent<-40
        // native units/s, then initializes directional air. Existing air
        // clips keep their POS clock/link; a ledge is not immediately180.
        const pose=nativeAirPose(current,f.vy);
        if(current!==pose)f.combat.play(pose,{loop:false,force:true});
        else if([152,154,156,158,180].includes(pose))f.combat.timeline.loop=pose===NATIVE_LOCOMOTION.fall;
        f.heldPose=pose;
      }else{
        const moving=direction.lengthSq()>0;
        const facingMove=control&&(control.lookLocked||control.mouseLook?.locked||control.locked&&!control.locked.dead&&!control.locked.disposed);
        const groundMove=facingMove?(NATIVE_GROUND_MOVE_POSES[nativeTraversalDirection(control.keys)]??(f.heldPose>=141&&f.heldPose<=143?f.heldPose:NATIVE_LOCOMOTION.run)):NATIVE_LOCOMOTION.run;
        let pose=f.musketAim?212:f.guard?NATIVE_WEAPONS[f.weapon].guard:moving?groundMove:f.combat.stance??NATIVE_WEAPONS[f.weapon].stance;
        const crouching=(f.scriptCrouched||f.npcCombat?.crouch||control&&control.keys.has('crouch'))&&f.grounded&&!f.musketAim&&!f.guard;
        if(crouching){
          const walking=direction.lengthSq()>0,requested=nativeTraversalDirection(control?.keys);
          const movingPose=NATIVE_CROUCH_POSES[requested]??(f.heldPose>=145&&f.heldPose<=148?f.heldPose:NATIVE_CROUCH_POSES.forward);
          pose=walking?movingPose:NATIVE_CROUCH_POSES.idle;
        }
        if(!moving&&!f.guard&&!f.musketAim&&f.standingTurn)pose=f.standingTurn.poseId;
        if(f.heldPose!==pose){f.combat.play(pose,{loop:true,force:true});if(f.musketAim&&pose===212){f.combat.timeline.frame=f.combat.timeline.pose.end;f.combat.timeline.finished=true;}f.heldPose=pose;}
      }
    }
    const locomotion=f.combat.timeline?.pose.id;
    if(f.grounded&&!f.combat.busy&&!f.guard&&!f.musketAim){
      const stride=nativeStrideSpeed(f.character.nativeCharacterId??0,locomotion);
      if(stride>0){const rate=speed/this.hostPhysics.speed;if(control||locomotion>=145&&locomotion<=148)speed=nativeStrideSpeed(0,locomotion)*rate;f.combat.timeline.playbackRate=speed/stride;}
    }
    const queuedRequest=f.combat._queuedRequest;
    const queuedCastSerial=queuedRequest&&queuedRequest.canStart?.(queuedRequest.context)!==false?f.combat.serial:null;
    const state = f.combat.update(dt, { grounded: f.grounded, projectileReady: !this.wheels?.hasOwner(f), getFacing:()=>f.root.rotation.y }); if (!state) return;
    this.effectContacts?.beginStep(f,state);
    // A held defense is sampled continuously, including the exact frame a
    // hit/attack recovery ends. It must not depend on OS key-repeat or a new
    // touch press while several opponents are attacking.
    if (control && f.grounded && !f.wallRun && !f.combat.busy && !f.scriptInputBlocked && control.keys.has('guard')) f.guard = true;
    const motion = v3();let actionMotion=false;
    for (const segment of state.segments || [state]) {
      if(f.jumpSequence&&!f.jumpSequence.ballistic&&[f.jumpSequence.start,f.jumpSequence.air].includes(segment.poseId)&&f.character.sampleSceneMotion){
        // Consume BOTH takeoff and linked air d_base tracks, at actual POS time.
        // The former host stopped at takeoff, then injected an extra ballistic arc.
        f.nativeJump=null;
        for(const range of segment.frameIntervals||[]){const a=f.character.sampleSceneMotion(segment.source,range.from),b=f.character.sampleSceneMotion(segment.source,range.to);motion.y+=(b.z-a.z)*SCALE;}
      }
      if(segment.authoredMotionScale==null)continue;
      if(segment.consumed>0)actionMotion=true;
      const a = Number.isFinite(segment.facing)?segment.facing:f.root.rotation.y, scale = segment.authoredMotionScale;
      const localX = segment.rootDelta.x * scale, localZ = -segment.rootDelta.y * scale;
      motion.x += Math.cos(a) * localX + Math.sin(a) * localZ;
      motion.z += -Math.sin(a) * localX + Math.cos(a) * localZ;
      motion.y += segment.rootDelta.z * scale;
    }
    // Native animation advances before the actor's motion update (004cc130).
    // All authored recoil/lunges now share floor, wall and hazard checks.
    this._move(f, direction, speed, dt, motion,actionMotion||f.combat.busy);
    if (f.dead) return;
    // A queued move may turn toward its target during combat.update(). Old
    // attack windows in that same tick still belong to their earlier facing.
    const finalFacing=f.root.rotation.y;
    try{for (const segment of state.segments || [state]) {
      if(Number.isFinite(segment.facing))f.root.rotation.y=segment.facing;
      if (!segment.blend && segment.serial !== f.lastSerial) {
        f.attackHits.clear(); f.lastSerial = segment.serial;
        const basicEmitter = { dart: NATIVE_DART_PROFILE, musket: NATIVE_MUSKET_PROFILE, wheel: NATIVE_WHEEL_PROFILE }[f.weapon];
        if (segment.pose.attacks.length && !basicEmitter?.poseIds.includes(segment.pose.id)) this._soundDefinition(segment.pose.raw.fields.effectid);
      }
      // A rendered frame can cross several narrow original attack windows.
      // Sample each window's authored frame, keeping its original index and
      // serial so multi-thrusts hit once per window, never once per render.
      for (const attack of segment.attacks)this._resolveAttackWindow(f,segment,attack);
      // 004ce410 pushes2 to004dc8c0: End-floor(frame)<2. Parameter18
      // applies near the final two source frames, independently of contact.
      // Resolve this host step's attack before committing lethal self damage.
      const armedQueue=segment.serial===queuedCastSerial&&segment.pose.cancels.some(window=>segment.frameIntervals?.some(range=>range.from<=window.end&&range.to>=window.start));
      if(!segment.blend&&(segment.frame>=segment.pose.end-1||armedQueue))this._commitNativeSelfItem(f,segment);
      if(f.dead)break;
    }
    }finally{f.root.rotation.y=finalFacing;}
    if(f.dead){const pose=f.combat.timeline.pose;f.character.setPoseFrame(pose.source,f.combat.timeline.frame);return;}
    if (state.blend && f.character.setPoseBlend) f.character.setPoseBlend(state.blend.from, state.blend.to, state.blend.weight);
    else f.character.setPoseFrame(state.source, state.frame);
    this.rageVfx?.sample(f, state, f.combat.fps);
    if (f.nameplate) { f.nameplate.quaternion.copy(f.root.quaternion).invert().multiply(this.camera.quaternion); }
  }
  _commitNativeSelfItem(actor,state){
    if(['roll','dash'].includes(state.context?.kind)||state.context?.poseId!==state.pose.id||actor.selfItemSerial===state.serial)return null;
    actor.selfItemSerial=state.serial;
    const item=useNativeSelfItem(actor,this.combatData?.moveRecords?.get(state.pose.id),this.combatData?.itemRecords);
    if(item)this.onEvent?.({type:'self-item',actorId:actor.scriptId??actor.id,poseId:state.pose.id,itemId:item.id,name:item.name,duration:item.duration,refreshed:item.refreshed});
    if(item&&actor.hp<=0){this.rageVfx?.detachOnDeath(actor,state,actor.combat.fps);this._kill(actor,{awardKill:false,deathPose:state.pose.link,deathContext:{...state.context,deathEffectTime:state.effectTime,deathEffectAt:this.matchElapsed}});}
    return item;
  }
  _resolveAttackWindow(actor,segment,attack){
    // Projectile release and independent EF clocks retain their existing path.
    const melee=!['dart','musket','wheel'].includes(actor.weapon)&&attack.bones.some(bone=>bone!=='effect');
    const frames=melee?nativeAttackFrames(segment,attack):[clamp(segment.frame,attack.start,attack.end)];
    // Mixed bone/effect windows need crossed bone frames too. Their separate
    // EF clock is queried once, rather than once per bone sample.
    const effectVolumes=melee&&attack.bones.includes('effect')&&frames.length
      ?this.effectContacts?.sample(actor,segment,attack,actor.combat?.fps)||[]:undefined;
    for(const frame of frames){actor.character.setPoseFrame(segment.source,frame);const state={...segment,frame,attacks:[attack]};this._launchNativeProjectiles(actor,state);this._resolveContacts(actor,state,effectVolumes);}
  }
  _resolveContacts(attacker, state, sampledEffectVolumes) {
    if (!this.running) return;
    const targets = attacker.playerControl ? [this.hero,...this.enemies].filter(f=>f!==attacker&&!nativeSameTeam(f,attacker)) : attacker.hero ? this.enemies.filter(f=>!this.networkCombat||!nativeSameTeam(f,attacker)) : this.mode === 'story' ? [this.hero, ...this.enemies].filter(f => f !== attacker && !nativeSameTeam(f,attacker)) : [this.hero];
    for (const attack of state.attacks) this._resolveSceneContacts(attacker, state, attack);
    for (const attack of state.attacks) {
      const points = [];
      for (const name of attack.bones) {
        if (name === 'weapon' && attacker.weaponModel) { for (const model of attacker.weaponModels?.length ? attacker.weaponModels : [attacker.weaponModel]) { const box = new THREE.Box3().setFromObject(model); points.push(box.getCenter(v3()), box.min.clone(), box.max.clone()); } }
        else { const bone = getNativeAttackAttachment(attacker.character, name); if (bone) points.push(bone.getWorldPosition(v3())); }
      }
      const effectVolumes = sampledEffectVolumes ?? (this.effectContacts?.sample(attacker, state, attack, attacker.combat.fps) || []);
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
    if (!this.running || target.dead || target.disposed || target.scriptRemoved || this.networkCombat&&nativeSameTeam(target,attacker)) return false;
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
    const damage = this.damageResolver?.(damageContext);let confirmedDamage=0;
    if (Number.isFinite(damage) && damage >= 0) {
      const hpBefore = target.hp; target.hp = Math.max(0, target.hp - damage);confirmedDamage=hpBefore-target.hp; if (attacker.hero) this.totalDamage += hpBefore - target.hp;
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
      if (target.hp <= 0) this._kill(target,{attacker});
      this._emit(guarded ? '格挡' : String(Math.round(damage)), 'hit', damage, contact, { poseId: state.poseId, raw, guarded, guardBypassed, knockdown: knockdown && !target.dead, attackerHero: !!attacker.hero, targetHero: !!target.hero, targetName: target.name, ...extra });
    } else { const name = raw.moveRecord?.name || state.pose.label || '兵刃交锋'; this._emit(attacker.hero ? `${name} · 命中` : `${name} · 对手命中`, 'hit', undefined, contact, { poseId: state.poseId, raw, guarded, guardBypassed, damagePending: true, ...extra }); }
    target.musketAim=false;
    const displayedReaction = guarded ? nativeGuardPose(target.weapon, selection.direction,this.combatRandom||Math.random) : reactionPose;
    if (!target.dead && displayedReaction != null && target.combat?.react(displayedReaction, {
      ...nativeReactionParameters(attack, { guarded }), guarded, fromPose: target.character?.capturePose?.()
    })) {
      if (!guarded) target.guard = false;
      this._captureActionMomentum(target);
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
    const direction=target.root.position.clone().sub(attacker.root.position);
    const prefix = { sword: 'W00', blade: 'W05', spear: 'W07', dagger: 'W01', dart: 'W03', musket: 'W02', wheel: 'W06', qiankun: 'W09', ninja: 'W11', dual: 'W08', hammer: 'W04', knuckle: 'W10' }[attacker.weapon];
    let lift=0;
    const reaction=this.combatData.poses?.get(reactionPose),sample=target.character?.sampleSceneMotion;
    if(reaction?.valid&&sample){
      const key=`${target.character.nativeCharacterId??0}:${reactionPose}`,cache=this.bloodLiftCache||=new Map();
      if(!cache.has(key)){const origin=sample(reaction.source,reaction.start).z;let peak=0;for(let i=1;i<=8;i++){const z=sample(reaction.source,reaction.start+(reaction.end-reaction.start)*i/8).z-origin;if(Number.isFinite(z))peak=Math.max(peak,z);}cache.set(key,peak*.08);}
      lift=cache.get(key)*Math.max(0,Number(attack.targetmove)||0);
    }
    const bloodStyle=bloodStyleForHit({damage,force:attack.targetmove,weapon:attacker.weapon,knockdown,lift,reactionPose});
    this.bloodFeedback?.emit({point:contact,direction,guarded,damage:confirmedDamage,style:bloodStyle});
    this.combatFeedbackSerial=(this.combatFeedbackSerial||0)+1;
    const actors=[this.hero,...(this.enemies||[])];
    (this.combatFeedbackEvents||=[]).push({id:this.combatFeedbackSerial,time:this.matchElapsed||0,point:contact.toArray(),direction:direction.normalize().toArray(),guarded,knockdown,blood:!guarded&&confirmedDamage>0,bloodStyle:!guarded&&confirmedDamage>0?bloodStyle:undefined,
      attackerId:actors.find(actor=>actor?.root===attacker.root)?.networkId,targetId:target.networkId,projectile:Number.isInteger(extra.projectileId)?{kind:'dart',id:extra.projectileId}:Number.isInteger(extra.wheelId)?{kind:'wheel',id:extra.wheelId}:undefined,sound:prefix&&Number.isInteger(reactionPose)?`${prefix}${guarded?'GD':'BL'}${String(reactionPose).padStart(3,'0')}`:null});
    if(this.combatFeedbackEvents.length>32)this.combatFeedbackEvents.shift();
    if (attacker.hero && this.swordStyle === 'butterfly') this.butterflyVfx?.burst(contact, { guarded, knockdown, camera: this.camera });
    if (feedback) {
      if (attacker.combat && !attacker.dead) attacker.hitstop = Math.max(attacker.hitstop || 0, feedback.hitstop);
      if (!target.dead) target.hitstop = Math.max(target.hitstop || 0, feedback.hitstop);
    }
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
  _kill(target, { awardKill = true, deathPose = NATIVE_LOCOMOTION.dead, deathContext = null } = {}) {
    if(!target.dead&&this.droppedWeapons?.size<64){const id=target.weaponId,item=this.weaponItems?.get(id),templates=item?.modelIds.map(id=>this.weaponCache.get(id.toLowerCase()));
      if(templates?.every(Boolean)){const session=this.sessionRequest,position=target.root.position.clone();Promise.all(templates).then(models=>{if(!this.disposed&&session===this.sessionRequest&&this.droppedWeapons.size<64)this._spawnDroppedWeapon(id,position,`web-drop-${++this.lootSerial}`,models);}).catch(()=>{});}}
    target.wallRun=null;target.wallKick=null;
    if (target.dead) return; this.stealthFeedback?.clearActor(target); target.dead = true; target.guard = false; target.musketAim=false; target.hitstop = 0; target.respawn = this.mode === 'story' ? Infinity : 3; target.combat.play(this.combatData?.poses?.has(deathPose)?deathPose:NATIVE_LOCOMOTION.dead, { force: true,context:deathContext });
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
    const c = document.createElement('canvas'); c.width = 256; c.height = 64; const ctx = c.getContext('2d'); ctx.font = '28px serif'; ctx.fillStyle = '#eee7cf'; ctx.textAlign = 'center'; ctx.fillText(`${nativeSameTeam(f,this.hero) ? '同伴' : f.team === 0 ? '剧情' : '对手'} · ${f.name}`, 128, 43, 240);
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
    if(this.hero.musketAim&&!this.hero.dead&&(this.running||this.paused)){
      const control=this._controlFor(this.hero),eye=this.hero.root.position.clone().add(v3(0,1.65,0)),pitch=control?.aimPitch||0;
      const direction=v3(-Math.sin(this.cameraAngle)*Math.cos(pitch),Math.sin(pitch),-Math.cos(this.cameraAngle)*Math.cos(pitch));
      this.camera.position.copy(eye);this.cameraTarget.copy(eye).add(direction);this.camera.lookAt(this.cameraTarget);this.hero.root.visible=false;this.cameraFollowY=this.hero.root.position.y;return;
    }
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
    if (!this.hero) return; const f = this.hero, target = this.locked&&!nativeIsInvisible(this.locked) ? this.locked : (this.running ? this._nearest(18) : null), b = this.currentMap?.bounds;
    let enemy = null;
    if (target) {
      const delta = target.root.position.clone().sub(f.root.position), view = this.camera.getWorldDirection(v3()); view.y = 0; view.normalize();
      const right = v3(-view.z, 0, view.x);
      enemy = { name: target.name, hp: target.hp, maxHp: target.maxHp, reaction: target.combat?.reactionPhase ?? null, distance: delta.length(), bearing: Math.atan2(delta.dot(right), delta.dot(view)) };
    }
    const item = this.running ? this.items?.peek(f) : null;
    const pickup = item ? { name: item.name, heal: item.heal, description:item.description, fullReason:item.fullReason, full: item.full, distance: item.distance, objectName: item.objectName } : null;
    const statuses = (f.networkItemStatuses || f.scriptItems || []).map(item => ({ id: item.id, name: item.name, statKey: item.statKey, remaining: item.remaining, value: item.value, period: item.period }));
    this.onUpdate({ musketAim:!!f.musketAim, infiniteRage: !!this.infiniteRage, characterAppearance: f.character.appearanceStatus, pickup, statuses, inputBlocked: !!f.scriptInputBlocked, hp: f.hp, maxHp: f.maxHp, playerReaction: f.networkReactionPhase??f.combat.reactionPhase, rage: f.rage, hits: this.contactHits, kills: this.kills, deaths: this.deaths, time: this.matchElapsed, enemy, combo: f.combat.attacking ? f.combat.combo : 0, moveName: f.combat.busy ? f.combat.currentMove?.name : null, moveCommand: f.combat.busy ? f.combat.currentMove?.command : null, queuedMoveName: this.networkCombat&&this.lootReplica?f.networkQueuedMoveName??null:f.combat.queuedMove?.name||null, locked: !!this.locked, position: { x: f.root.position.x, z: f.root.position.z }, enemies: this.enemies.filter(e => !e.dead && !e.scriptRemoved && !nativeSameTeam(e,f) && e.team !== 0 && !nativeIsInvisible(e)).map(e => ({ x: e.root.position.x, z: e.root.position.z })), allies: this.enemies.filter(e => !e.dead && !e.scriptRemoved && nativeSameTeam(e,f)).map(e => ({ x: e.root.position.x, z: e.root.position.z })), weapon: f.weapon, weaponId: f.weaponId, weaponName: f.weaponName, weapon2Name:this.weaponItems?.get(f.weapon2Id)?.name||null, weaponMode: f.combat.weaponMode, mission: this.missionState, paused: this.paused, mapBounds: b ? { minX: b.min.x, maxX: b.max.x, minZ: b.min.z, maxZ: b.max.z } : null, native: { pose: f.combat.timeline?.pose.id, source: f.character.source, frame: f.character.frame, contacts: this.contactHits, damagePending: !this.damageResolver, hpSourcePending: !f.hpSourceVerified, physicsPending: true, sceneDamagePending: this.mode === 'story' && !this.sceneDamageResolver, projectilePending: false, projectileSpecialsPending: true, projectilePhysics: NATIVE_DART_PROFILE.provenance.flight, projectiles: this.projectiles?.size || 0, missionVmPending: this.mode === 'story' ? !this.missionHost?.started : false } });
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
    this.items?.prepareWorld?.();
    if (this.running) this.missionHost?.update(dt); this.currentMap.props?.update(dt); this.currentMap.update?.(dt);
    if (this.running) { this.matchElapsed += dt; this._updateFighter(this.hero, dt); for (const f of this.enemies) { if (!this.running) break; this._updateFighter(f, dt); } this._separateCharacters(dt); if (this.running) { this.projectiles?.update(dt); this.wheels?.update(dt); } }
    else { const state = this.hero.combat.update(dt); if (state) this.hero.character.setPoseFrame(state.source, state.frame); }
    this._updateLoot();
    this.updateAccum += dt; if (this.updateAccum > .08) { this.updateAccum = 0; this._hud(); }
  }
  _updatePresentation(dt) {
      this.stealthFeedback?.update([this.hero,...this.enemies],this.hero);
      this.items?.updateVisuals(this.elapsed);
      this.weather?.update(dt, this.hero?.root.position);
      // Run cosmetic springs once, after final body motion and separation.
      for (const actor of [this.hero,...this.enemies]) if(actor?.root.visible&&!actor.disposed)actor.character.updateSecondaryMotion?.(dt,{groundY:actor.grounded?actor.root.position.y:undefined});
      for (let i = this.effects.length - 1; i >= 0; i--) { const e = this.effects[i]; e.life -= dt; e.mesh.material.opacity = Math.max(0, e.life / .14); if (e.life <= 0) { e.mesh.removeFromParent(); e.mesh.geometry.dispose(); e.mesh.material.dispose(); this.effects.splice(i, 1); } }
      const feedbackStep=this.paused?0:dt;
      this.impactFeedback?.update(feedbackStep,this.camera);
      this.bloodFeedback?.update(feedbackStep,this.camera,this.renderer?.domElement?.height||900);
      this.poisonFeedback?.update(feedbackStep,[this.hero,...this.enemies]);
      this.slowFeedback?.update(feedbackStep,[this.hero,...this.enemies]);
      this.rageVfx?.update(feedbackStep, this.camera);
      this.butterflyVfx?.update(dt, { attacking: !!this.hero?.combat?.attacking, camera: this.camera });
      if (this.hero?.phoenixSpear?.visible) this.hero.phoenixSpear.userData.update(this.elapsed);
  }
  _tryPickupActor(actor){if(this.running&&!this.paused&&!this.lootReplica&&actor&&actor.grounded!==false&&!actor.dead&&!actor.combat.busy&&!actor.guard)return this.items?.tryPickup(actor);}
  _updateLoot(){if(this.running&&!this.paused&&!this.lootReplica)for(const actor of [this.hero,...this.enemies])if(actor&&this._controlFor(actor)&&actor.grounded)this._tryPickupActor(actor);}
  _frame(timestamp) {
    if (this.disposed) return; this.raf = requestAnimationFrame(this._frame);
    // Static menu shell needs no world updates or WebGL submissions. Reset the
    // clocks so returning to combat never accumulates menu time as catch-up work.
    if (this.menuIdle) { this.clock.getDelta(); this.simulationClock.reset(); return; }
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
    this.keyboard = bindKeyboard(window, { bindings: defaultBindings(), enabled: () => this.running && !this.paused && !document.querySelector('dialog[open]') && !/INPUT|TEXTAREA|SELECT/.test(document.activeElement?.tagName), action: (name, down) => this.action(name, down),onReset:()=>this.action('clear',false) });
    this._listeners.push(() => this.keyboard.dispose());
    this.mouseLook = createMouseLook(this.canvas, { active: () => this.running && !this.paused && !document.querySelector('dialog[open]'), move: (dx, dy) => turnMouseCamera(this, dx, dy), action: (name, down) => this.action(name, down),onReset:()=>this.action('clear',false), onUnlock: () => this.onEvent({ type: 'pointer-unlock' }), onError: () => this.onEvent({ type: 'pointer-error', text: '鼠标锁定未成功，请点击游戏画面重试；也可继续使用键盘操作。' }) });
    this._listeners.push(() => this.mouseLook.dispose());
    bind(window, 'blur', () => this.releaseInput());
    bind(this.canvas, 'contextmenu', e => e.preventDefault());
    bind(this.canvas, 'pointerdown', e => { this._unlockAudio(); if(this.mouseLook.pointerDown(e))return; this.pointer = { x: e.clientX, y: e.clientY, startX: e.clientX, startY: e.clientY, button: e.button, moved: false }; this.canvas.setPointerCapture?.(e.pointerId); if (e.button === 2) this.action('jump'); });
    bind(this.canvas, 'pointermove', e => { if(this.mouseLook.locked || this.locked&&!this.locked.dead&&!this.locked.disposed)return; const p = this.pointer; if (!p) return; if (Math.hypot(e.clientX - p.startX, e.clientY - p.startY) > 5) p.moved = true; if (p.moved && this.running && !this.paused) { this.cameraManualUntil = this.elapsed + 2; this.cameraAngle -= (e.clientX - p.x) * .005; this.cameraPitch = clamp(this.cameraPitch + (e.clientY - p.y) * .003, .15, .95); } p.x = e.clientX; p.y = e.clientY; });
    bind(this.canvas, 'pointerup', e => { this.mouseLook.pointerUp(e); if (this.pointer && !this.pointer.moved && this.pointer.button === 0) this.action('attack'); if(this.pointer?.button===2)this.action('jump',false); this.pointer = null; });
    for (const event of ['pointercancel', 'lostpointercapture']) bind(this.canvas, event, () => { if(this.pointer?.button===2)this.action('clear',false);this.pointer = null; this.action('guard', false); });
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
    this.rageVfx?.dispose(); this.effectContacts?.dispose(); this.projectiles?.dispose(); this.muskets?.dispose(); this.wheels?.dispose(); this.stealthFeedback?.dispose(); this.impactFeedback?.dispose(); this.bloodFeedback?.dispose(); this.poisonFeedback?.dispose(); this.slowFeedback?.dispose(); this.items?.dispose(); this._clearDroppedWeapons(); this.missionHost?.dispose(); this.disposed = true; cancelAnimationFrame(this.raf); this._listeners.forEach(fn => fn()); this.hero?.character.dispose(); this.enemies.forEach(f => { this._disposeNameplate(f); f.character.dispose(); });
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

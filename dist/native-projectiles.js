import * as THREE from './vendor/three.module.js';

// Original source anchors are retained separately from the browser's flight
// adapter. POS determines release, never flight lifetime. EF trajectory data is
// not claimed recovered until independently verified against the executable.
export const NATIVE_DART_PROFILE = Object.freeze({
  weaponItem: 1, model: 'w3_0', poseIds: Object.freeze([200, 202, 209, 210]), scale: .08,
  speed: 50, radius: .12, lifetime: 3, gravity: 0, spin: 28, maxActive: 64,
  provenance: Object.freeze({
    model: 'Original cmodel/W3_0.GMC, item 1 七星; native geometry converted once at scale 0.08.',
    release: 'Original P0.POS 200: 3517–3519; 202: 12276–12279; 209: 3550–3553; 210: 3593–3596; one release per original attack window.',
    damage: 'Original Meteor.res item1 attack75; pose200/202 modifier65 (34 versus defense15), pose209/210 modifier50 (23 versus defense15), recovered EXE arithmetic.',
    sound: 'Original Pos200/Pos202.ef references W03FIR01.wav; Pos209.ef W03FIR02.wav; Pos210.ef W03FIR03.wav.',
    flight: 'Browser adapter: speed50 world/s, radius0.12, lifetime3s, gravity0, spin28rad/s. Not recovered EXE flight constants.',
    collision: 'Continuous segment versus actor vertical capsules and original map/dynamic triangles; nearest impact wins; wall wins ties.',
    aim: 'Browser adapter: original d_wpnR release position; locked/nearby target chest or actor forward; no homing.'
  })
});

// Original musket poses have no melee bones. This profile preserves their
// source identity; instantaneous ray contact is an explicit Web host adapter.
// No original bullet speed, range, spread or tracer has been recovered.
export const NATIVE_MUSKET_PROFILE = Object.freeze({
  weaponItem: 3, model: 'w2_0', poseIds: Object.freeze([206, 207, 208]), scale: .08,
  contactMode: 'web-hitscan-adapter',
  provenance: Object.freeze({
    weapon: 'Original Meteor.res item3 怒火/W2_0, native class2, attack80, defense15; variants12/21/30/39 keep their own RES records.',
    release: 'Original P0.POS:206 Attack3738–3742;207 Attack9629–9633;208 Attack3769–3773; all have no melee Bone. One shot per POS window is a Web adapter.',
    damage: 'Original pose206/207/208 attack modifiers65/75/80; recovered EXE arithmetic gives37/45/49 rawHP against defense15 with default item3.',
    sound: 'Original Pos206/207/208.ef references W02FIR01/02/03.wav respectively.',
    collision: 'Web adapter: immediate segment versus actor vertical capsules and original map triangles; nearest contact wins, walls win ties. Range must be supplied by the host.',
    pending: 'Native bullet/ray mode, range, spread, ammunition and full EF are unverified. Aim entry uses native212 state; camera projection and ray convergence remain Web adapters. Special215 and216→217 remain unsupported here.'
  })
});

function worldSegmentContact(system, from, to, radius) {
  const delta = to.clone().sub(from), length = delta.length(); if (length < 1e-9) return null;
  const direction = delta.multiplyScalar(1 / length), right = new THREE.Vector3().crossVectors(direction, new THREE.Vector3(0, 1, 0));
  if (right.lengthSq() < 1e-8) right.set(1, 0, 0); else right.normalize();
  const up = new THREE.Vector3().crossVectors(right, direction).normalize();
  const offsets = radius > 0 ? [new THREE.Vector3(), right.clone().multiplyScalar(radius), right.clone().multiplyScalar(-radius), up.clone().multiplyScalar(radius), up.clone().multiplyScalar(-radius)] : [new THREE.Vector3()];
  const colliders = system.getColliders(from, to, radius) || []; let nearest = null;
  system.raycaster.near = .001; system.raycaster.far = length;
  for (const offset of offsets) {
    system.raycaster.set(from.clone().add(offset), direction);
    const hit = system.raycaster.intersectObjects(colliders, false)[0];
    if (hit && (!nearest || hit.distance < nearest.distance)) nearest = { ...hit, t: hit.distance / length, center: from.clone().addScaledVector(direction, hit.distance) };
  }
  return nearest;
}

// Earliest segment contact against a vertical capsule, including initial overlap.
// The cylinder and both spherical caps are intersected analytically, so a shot
// cannot tunnel through an actor between two rendered frames.
export function sweepActorCapsule(from, to, actor, projectileRadius = .12, bodyRadius = .4) {
  const p = actor.root.position, low = p.y + bodyRadius, high = p.y + 2.2, radius = bodyRadius + projectileRadius;
  const dx = to.x - from.x, dy = to.y - from.y, dz = to.z - from.z;
  const px = from.x - p.x, pz = from.z - p.z;
  const nearestY = THREE.MathUtils.clamp(from.y, low, high);
  if (px * px + pz * pz + (from.y - nearestY) ** 2 <= radius * radius) return 0;
  let best = Infinity;
  const a = dx * dx + dz * dz, b = 2 * (px * dx + pz * dz), c = px * px + pz * pz - radius * radius;
  const disc = b * b - 4 * a * c;
  if (a > 1e-12 && disc >= 0) {
    const root = Math.sqrt(disc);
    for (const t of [(-b - root) / (2 * a), (-b + root) / (2 * a)]) if (t >= 0 && t <= 1 && from.y + dy * t >= low && from.y + dy * t <= high) best = Math.min(best, t);
  }
  const magnitude = dx * dx + dy * dy + dz * dz;
  if (magnitude > 1e-12) for (const y of [low, high]) {
    const py = from.y - y, sb = 2 * (px * dx + py * dy + pz * dz), sc = px * px + py * py + pz * pz - radius * radius, sd = sb * sb - 4 * magnitude * sc;
    if (sd < 0) continue;
    const t = (-sb - Math.sqrt(sd)) / (2 * magnitude); if (t >= 0 && t <= 1) best = Math.min(best, t);
  }
  return Number.isFinite(best) ? best : null;
}

export class NativeProjectileSystem {
  constructor({ scene, getTargets = () => [], canHit = () => true, getColliders = () => [], onActorHit = () => {}, onWorldHit = () => {}, profile = NATIVE_DART_PROFILE, bodyRadius = .4 } = {}) {
    this.scene = scene; this.getTargets = getTargets; this.getColliders = getColliders; this.onActorHit = onActorHit; this.onWorldHit = onWorldHit;
    this.profile = profile; this.bodyRadius = bodyRadius; this.active = []; this.serial = 0; this.paused = false; this.disposed = false;
    this.canHit=canHit;
    this.group = new THREE.Group(); this.group.name = '原版七星投射物'; scene?.add(this.group); this.raycaster = new THREE.Raycaster();
  }
  get size() { return this.active.length; }
  pause(value = true) { this.paused = !!value; }
  worldContact(from, to, radius) {
    return worldSegmentContact(this, from, to, radius);
  }
  spawn({ owner, position, direction, visual = null, context = {}, sourcePosition = null, profile = this.profile } = {}) {
    if (this.disposed || !owner || !position || !direction || direction.lengthSq() < 1e-12) return null;
    const root = new THREE.Group(); root.name = `七星-${++this.serial}`; root.position.copy(position); root.quaternion.setFromUnitVectors(new THREE.Vector3(0, 0, 1), direction.clone().normalize()); if (visual) root.add(visual);
    const shot = { id: this.serial, owner, root, visual, position: position.clone(), previous: position.clone(), velocity: direction.clone().normalize().multiplyScalar(profile.speed), age: 0, profile, context, removed: false };
    // Prevent a hand which clips through a wall from spawning beyond that wall.
    const blocked = sourcePosition && this.worldContact(sourcePosition, position, profile.radius);
    if (blocked) { shot.position.copy(blocked.center); shot.removed = true; this.onWorldHit(shot, blocked); return null; }
    while (this.active.length >= profile.maxActive) this.remove(this.active[0], 'capacity');
    this.group.add(root); this.active.push(shot); return shot;
  }
  remove(shot, reason = 'removed') {
    if (!shot || shot.removed) return; shot.removed = true; shot.removalReason = reason; shot.root.removeFromParent();
    const index = this.active.indexOf(shot); if (index >= 0) this.active.splice(index, 1);
    // Original model geometry/material/textures are shared with the weapon cache.
    // Ownership remains there; deleting a shot must never dispose those assets.
  }
  update(dt) {
    if (this.disposed || this.paused || !Number.isFinite(dt) || dt <= 0) return;
    for (const shot of [...this.active]) {
      if (shot.removed) continue;
      const remaining = shot.profile.lifetime - shot.age, step = Math.min(dt, Math.max(0, remaining));
      if (step <= 0) { this.remove(shot, 'expired'); continue; }
      shot.previous.copy(shot.position); const to = shot.position.clone().addScaledVector(shot.velocity, step); to.y -= .5 * shot.profile.gravity * step * step;
      const world = this.worldContact(shot.position, to, shot.profile.radius); let actor = null, actorT = Infinity;
      for (const target of this.getTargets(shot) || []) {
        if (!target || target === shot.owner || target.id === shot.owner.id || target.dead || target.disposed || target.scriptRemoved || target.hp <= 0 || !this.canHit(shot.owner,target)) continue;
        // Relative-motion sweep also catches an actor crossing the flight line.
        const relativeFrom = target.previousPosition ? shot.position.clone().add(target.root.position).sub(target.previousPosition) : shot.position;
        const t = sweepActorCapsule(relativeFrom, to, target, shot.profile.radius, this.bodyRadius);
        if (t != null && t < actorT) { actor = target; actorT = t; }
      }
      shot.age += step;
      if (world && world.t <= actorT + 1e-7) {
        shot.position.copy(world.center); this.remove(shot, 'world'); this.onWorldHit(shot, world);
      } else if (actor) {
        shot.position.lerp(to, actorT); const point = shot.position.clone(); this.remove(shot, 'actor'); this.onActorHit(shot, actor, point);
      } else {
        shot.position.copy(to); shot.velocity.y -= shot.profile.gravity * step; shot.root.position.copy(to); if (shot.visual) shot.visual.rotation.y += shot.profile.spin * step;
        if (shot.age >= shot.profile.lifetime) this.remove(shot, 'expired');
      }
    }
  }
  clear(reason = 'clear') { for (const shot of [...this.active]) this.remove(shot, reason); }
  dispose() { this.clear('dispose'); this.disposed = true; this.group.removeFromParent(); }
}

export class NativeMusketSystem {
  constructor({ getTargets = () => [], canHit = () => true, getColliders = () => [], onActorHit = () => {}, onWorldHit = () => {}, bodyRadius = .4 } = {}) {
    this.getTargets = getTargets; this.getColliders = getColliders; this.onActorHit = onActorHit; this.onWorldHit = onWorldHit; this.bodyRadius = bodyRadius;
    this.raycaster = new THREE.Raycaster(); this.serial = 0; this.paused = false; this.disposed = false; this.releases = new WeakMap();
    this.canHit=canHit;
  }
  get size() { return 0; }
  pause(value = true) { this.paused = !!value; }
  // The host explicitly chooses range and aim. No dart geometry, travel speed,
  // lifetime, homing or invented native ballistic constant enters this path.
  fire({ owner, position, direction, range, sourcePosition = null, context = {} } = {}) {
    if (this.disposed || this.paused || !owner || !position || !direction || !Number.isFinite(range) || range <= 0 || direction.lengthSq() < 1e-12) return null;
    const shot = { id: ++this.serial, owner, position: position.clone(), context, profile: NATIVE_MUSKET_PROFILE, removed: true, removalReason: 'miss' };
    const blocked = sourcePosition && worldSegmentContact(this, sourcePosition, position, 0);
    if (blocked) { shot.position.copy(blocked.center); shot.removalReason = 'world'; this.onWorldHit(shot, blocked); return shot; }
    const to = position.clone().addScaledVector(direction.clone().normalize(), range), world = worldSegmentContact(this, position, to, 0);
    let actor = null, actorT = Infinity;
    for (const target of this.getTargets(shot) || []) {
      if (!target || target === owner || target.id === owner.id || target.dead || target.disposed || target.scriptRemoved || target.hp <= 0 || !this.canHit(owner,target)) continue;
      const t = sweepActorCapsule(position, to, target, 0, this.bodyRadius);
      if (t != null && t < actorT) { actor = target; actorT = t; }
    }
    if (world && world.t <= actorT + 1e-7) {
      shot.position.copy(world.center); shot.removalReason = 'world'; this.onWorldHit(shot, world);
    } else if (actor) {
      shot.position.lerp(to, actorT); shot.removalReason = 'actor'; this.onActorHit(shot, actor, shot.position.clone());
    } else shot.position.copy(to);
    return shot;
  }
  firePose({ owner, state, context = {}, ...aim } = {}) {
    if (!owner || !state || !Number.isFinite(state.serial) || !NATIVE_MUSKET_PROFILE.poseIds.includes(state.poseId) || this.paused || this.disposed) return [];
    let record = this.releases.get(owner);
    if (record && state.serial < record.serial) return [];
    if (!record || record.serial !== state.serial) { record = { serial: state.serial, windows: new Set() }; this.releases.set(owner, record); }
    const shots = [];
    for (const attack of state.attacks || []) {
      if (record.windows.has(attack.index)) continue;
      const shot = this.fire({ owner, ...aim, context: { ...context,
        state: { poseId: state.poseId, pose: state.pose, source: state.source, serial: state.serial }, attack: { ...attack } } });
      if (shot) { record.windows.add(attack.index); shots.push(shot); }
    }
    return shots;
  }
  // Immediate shots leave no active flight object. Clear only resets release
  // identities when the host restarts a match or changes maps.
  clear() { this.releases = new WeakMap(); }
  dispose() { this.clear(); this.disposed = true; }
}

// Source item/model/windows and RES damage are native. Travel/return/catch are
// explicitly Web physics until the original class6 projectile is recovered.
export const NATIVE_WHEEL_PROFILE = Object.freeze({
  model: 'w6_0', weaponItem: 2, poseIds: Object.freeze([218, 220, 222]),
  speed: 30, distance: 24, returnSpeed: 38, radius: .24, lifetime: 5, spin: 24,
  provenance: 'Original W6 models, POS218/220/222 release windows and RES pose damage; Web outbound/return trajectory, one damaging contact per throw, range/catch/timing are provisional.'
});
export class NativeWheelSystem {
  constructor({ scene, getTargets = () => [], canHit = () => true, getColliders = () => [], onActorHit = () => {}, onWorldHit = () => {}, bodyRadius = .4 } = {}) {
    Object.assign(this, { scene, getTargets, canHit, getColliders, onActorHit, onWorldHit, bodyRadius });
    this.active = []; this.serial = 0; this.raycaster = new THREE.Raycaster(); this.paused = false; this.disposed = false;
  }
  get size() { return this.active.length; }
  hasOwner(owner) { return this.active.some(shot => shot.owner === owner); }
  pause(value = true) { this.paused = !!value; }
  spawn({ owner, position, direction, visual, sourcePosition, context = {} } = {}) {
    if (this.disposed || this.paused || !owner || !position || !direction || !direction.lengthSq() || this.hasOwner(owner)) return null;
    const root = new THREE.Group(); root.position.copy(position); if (visual) root.add(visual);
    const shot = { id: ++this.serial, owner, root, visual, context, position: position.clone(), direction: direction.clone().normalize(),
      phase: 'outbound', age: 0, travelled: 0, removed: false, profile: NATIVE_WHEEL_PROFILE };
    const wall = sourcePosition && worldSegmentContact(this, sourcePosition, position, shot.profile.radius);
    if (wall) { shot.position.copy(wall.center); root.position.copy(shot.position); shot.phase = 'return'; this.onWorldHit(shot, wall); }
    this.active.push(shot); this.scene?.add(root); return shot;
  }
  update(dt) {
    if (this.disposed || this.paused || !(dt > 0) || !Number.isFinite(dt)) return;
    for (const shot of [...this.active]) {
      const { owner, profile } = shot; shot.age += dt;
      if (owner.dead || owner.disposed || owner.scriptRemoved || shot.age >= profile.lifetime) { this.remove(shot); continue; }
      const destination = shot.phase === 'return' ? owner.root.position.clone().add(new THREE.Vector3(0, 1.35, 0)) : null;
      if (destination && destination.distanceTo(shot.position) <= profile.returnSpeed * dt + .35) { this.remove(shot); continue; }
      const direction = destination ? destination.sub(shot.position).normalize() : shot.direction;
      const distance = Math.min((destination ? profile.returnSpeed : profile.speed) * dt, destination ? Infinity : profile.distance - shot.travelled);
      const to = shot.position.clone().addScaledVector(direction, distance);
      if (shot.phase === 'outbound') {
        const world = worldSegmentContact(this, shot.position, to, profile.radius); let target = null, targetT = Infinity;
        for (const actor of this.getTargets(shot) || []) {
          if (!actor || actor === owner || actor.id === owner.id || actor.dead || actor.disposed || actor.scriptRemoved || actor.hp <= 0 || !this.canHit(owner,actor)) continue;
          const t = sweepActorCapsule(shot.position, to, actor, profile.radius, this.bodyRadius);
          if (t != null && t < targetT) { target = actor; targetT = t; }
        }
        if (world && world.t <= targetT + 1e-7) { shot.position.copy(world.center); shot.phase = 'return'; this.onWorldHit(shot, world); }
        else if (target) { shot.position.lerp(to, targetT); shot.phase = 'return'; this.onActorHit(shot, target, shot.position.clone()); }
        else { shot.position.copy(to); shot.travelled += distance; if (shot.travelled >= profile.distance - 1e-7) shot.phase = 'return'; }
      } else shot.position.copy(to);
      shot.root.position.copy(shot.position); if (shot.visual) shot.visual.rotation.y += profile.spin * dt;
    }
  }
  remove(shot) { shot.removed = true; shot.root.removeFromParent(); const i = this.active.indexOf(shot); if (i >= 0) this.active.splice(i, 1); if (shot.owner.weapon === 'wheel' && shot.owner.weaponModel) shot.owner.weaponModel.visible = true; }
  clear() { for (const shot of [...this.active]) this.remove(shot); }
  dispose() { this.clear(); this.disposed = true; }
}

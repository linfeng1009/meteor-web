import * as THREE from './vendor/three.module.js';

// Original source anchors are retained separately from the browser's flight
// adapter. POS determines release, never flight lifetime. EF trajectory data is
// not claimed recovered until independently verified against the executable.
export const NATIVE_DART_PROFILE = Object.freeze({
  weaponItem: 1, model: 'w3_0', poseIds: Object.freeze([200, 202]), scale: .08,
  speed: 50, radius: .12, lifetime: 3, gravity: 0, spin: 28, maxActive: 64,
  provenance: Object.freeze({
    model: 'Original cmodel/W3_0.GMC, item 1 七星; native geometry converted once at scale 0.08.',
    release: 'Original P0.POS 200: 3517–3519; 202: 12276–12279; one release per original attack window.',
    damage: 'Original Meteor.res item1 attack75; pose200/202 modifier65, recovered EXE arithmetic (34 versus defense15).',
    sound: 'Original Pos200/Pos202.ef references W03FIR01.wav.',
    flight: 'Browser adapter: speed50 world/s, radius0.12, lifetime3s, gravity0, spin28rad/s. Not recovered EXE flight constants.',
    collision: 'Continuous segment versus actor vertical capsules and original map/dynamic triangles; nearest impact wins; wall wins ties.',
    aim: 'Browser adapter: original d_wpnR release position; locked/nearby target chest or actor forward; no homing.'
  })
});

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
  constructor({ scene, getTargets = () => [], getColliders = () => [], onActorHit = () => {}, onWorldHit = () => {}, profile = NATIVE_DART_PROFILE, bodyRadius = .4 } = {}) {
    this.scene = scene; this.getTargets = getTargets; this.getColliders = getColliders; this.onActorHit = onActorHit; this.onWorldHit = onWorldHit;
    this.profile = profile; this.bodyRadius = bodyRadius; this.active = []; this.serial = 0; this.paused = false; this.disposed = false;
    this.group = new THREE.Group(); this.group.name = '原版七星投射物'; scene?.add(this.group); this.raycaster = new THREE.Raycaster();
  }
  get size() { return this.active.length; }
  pause(value = true) { this.paused = !!value; }
  worldContact(from, to, radius) {
    const delta = to.clone().sub(from), length = delta.length(); if (length < 1e-9) return null;
    const direction = delta.multiplyScalar(1 / length), right = new THREE.Vector3().crossVectors(direction, new THREE.Vector3(0, 1, 0));
    if (right.lengthSq() < 1e-8) right.set(1, 0, 0); else right.normalize();
    const up = new THREE.Vector3().crossVectors(right, direction).normalize();
    const offsets = [new THREE.Vector3(), right.clone().multiplyScalar(radius), right.clone().multiplyScalar(-radius), up.clone().multiplyScalar(radius), up.clone().multiplyScalar(-radius)];
    const colliders = this.getColliders(from, to, radius) || []; let nearest = null;
    this.raycaster.near = .001; this.raycaster.far = length;
    for (const offset of offsets) {
      this.raycaster.set(from.clone().add(offset), direction);
      const hit = this.raycaster.intersectObjects(colliders, false)[0];
      if (hit && (!nearest || hit.distance < nearest.distance)) nearest = { ...hit, t: hit.distance / length, center: from.clone().addScaledVector(direction, hit.distance) };
    }
    return nearest;
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
        if (!target || target === shot.owner || target.id === shot.owner.id || target.dead || target.disposed || target.scriptRemoved || target.hp <= 0) continue;
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

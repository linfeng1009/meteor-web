import * as THREE from './vendor/three.module.js';
import {nativeSameTeam} from './native-teams.js';

// Original source anchors are retained separately from the browser's flight
// adapter. POS determines release, never flight lifetime. EF trajectory data is
// not claimed recovered until independently verified against the executable.
export const NATIVE_DART_PROFILE = Object.freeze({
  weaponItem: 1, model: 'w3_0', poseIds: Object.freeze([200, 202, 209, 210]), scale: .08,
  speed: 600 * .08, upwardVelocity: Math.fround(.13) * 600 * .08, radius: .12, lifetime: 3, gravity: 50 * .08, spin: 8, maxActive: 64,
  provenance: Object.freeze({
    model: 'Original cmodel/W3_0.GMC, item 1 七星; native geometry converted once at scale 0.08.',
    release: 'Original P0.POS 200: 3517–3519; 202: 12276–12279; 209: 3550–3553; 210: 3593–3596; one release per original attack window.',
    damage: 'Original Meteor.res item1 attack75; pose200/202 modifier65 (34 versus defense15), pose209/210 modifier50 (23 versus defense15), recovered EXE arithmetic.',
    sound: 'Original Pos200/Pos202.ef references W03FIR01.wav; Pos209.ef W03FIR02.wav; Pos210.ef W03FIR03.wav.',
    flight: '004df4e0 -> controller+c0/004d0530 ->004e4f60/004e5120: forward*600 plus nativeZ(.13*600), gravity50, spin8; units converted at .08, explicit Euler. Radius.12, lifetime3 and capacity64 remain Web adapters.',
    collision: 'Continuous segment versus actor vertical capsules and original map/dynamic triangles; nearest impact wins; wall wins ties.',
    aim: 'Browser adapter: d_wpnR position and ballistic target-chest assistance, or a forward point10 world units away; no homing. Native physicalActor+6c source transform and aim vector remain unresolved.'
  })
});

// 004dedc0 -> message10 -> 004efb00 -> 004f3ab0/004f3d30:
// one instantaneous, scene-clipped segment; all eligible actor boxes are tested.
export const NATIVE_MUSKET_PROFILE = Object.freeze({
  weaponItem: 3, model: 'w2_0', poseIds: Object.freeze([206, 207, 208]), scale: .08,
  contactMode: 'native-scene-clipped-ray', range: 1000 * .08, originHeight: 30 * .08,
  bodyHalfWidth: 7 * .08, bodyHeight: 36 * .08,
  provenance: Object.freeze({
    weapon: 'Original Meteor.res item3 怒火/W2_0, native class2, attack80, defense15; variants12/21/30/39 keep their own RES records.',
    release: '004ded90 arms controller+370;004dedc0 fires once when0055ddd0 reports an attack window and clears the flag. Original P0.POS206/207/208 windows have no melee Bone.',
    damage: 'Original pose206/207/208 attack modifiers65/75/80; recovered EXE arithmetic gives37/45/49 rawHP against defense15 with default item3.',
    sound: 'Original Pos206/207/208.ef references W02FIR01/02/03.wav respectively.',
    collision: '004f3d30 starts at actor position+nativeZ30, extends1000 along actor forward and clips against scene;004f3ab0 tests every eligible actor.00497f40 uses axis-aligned nativeXY±7, nativeZ0..36. Browser map triangles, feedback entry points, eligibility policy and camera projection remain host adapters.',
    pending: 'Native ammunition/special-shot branching and full EF remain unverified here. Special215 and216→217 use the separate effect-contact path, not this ordinary ray.'
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

// Web lock assist compensates the recovered ballistic flight. This solver is
// an adapter, not a claim about the native targeting implementation.
export function aimNativeDart(origin, target, profile = NATIVE_DART_PROFILE) {
  const delta = target.clone().sub(origin), horizontal = Math.hypot(delta.x, delta.z);
  if (horizontal < 1e-6) return delta.normalize();
  const error = angle => {
    const time = horizontal / (profile.speed * Math.cos(angle));
    return (profile.speed * Math.sin(angle) + (profile.upwardVelocity || 0)) * time
      - .5 * profile.gravity * time * time - delta.y;
  };
  let low = -1.4, high = .7;
  if (error(low) > 0 || error(high) < 0) return delta.normalize();
  for (let i = 0; i < 32; i++) { const mid = (low + high) / 2; if (error(mid) > 0) high = mid; else low = mid; }
  const angle = (low + high) / 2, scale = Math.cos(angle) / horizontal;
  return new THREE.Vector3(delta.x * scale, Math.sin(angle), delta.z * scale);
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
    shot.velocity.y += profile.upwardVelocity || 0;
    // Prevent a hand which clips through a wall from spawning beyond that wall.
    const blocked = sourcePosition && this.worldContact(sourcePosition, position, profile.radius);
    if (blocked) { shot.position.copy(blocked.center); shot.removed = true; this.onWorldHit(shot, blocked); return null; }
    while (this.active.length >= profile.maxActive) this.remove(this.active[0], 'capacity');
    this.group.add(root); this.active.push(shot);this.onFlightSample?.(shot,'spawn'); return shot;
  }
  remove(shot, reason = 'removed') {
    if (!shot || shot.removed) return;this.onFlightSample?.(shot,reason); shot.removed = true; shot.removalReason = reason; shot.root.removeFromParent();
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
      shot.previous.copy(shot.position); const to = shot.position.clone().addScaledVector(shot.velocity, step);
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
        shot.position.copy(to); shot.velocity.y -= shot.profile.gravity * step; shot.root.position.copy(to); if (shot.visual) shot.visual.rotation.z -= shot.profile.spin * step;
        if (shot.age >= shot.profile.lifetime) this.remove(shot, 'expired');
      }
      if(!shot.removed)this.onFlightSample?.(shot,'update');
    }
  }
  clear(reason = 'clear') { for (const shot of [...this.active]) this.remove(shot, reason); }
  dispose() { this.clear('dispose'); this.disposed = true; this.group.removeFromParent(); }
}

// Native00497f40 ->00570600/005702d0: finite segment vs actor AABB.
export function sweepNativeMusketBody(from, to, actor) {
  return sweepNativeActorBox(from,to,actor,NATIVE_MUSKET_PROFILE.bodyHalfWidth,NATIVE_MUSKET_PROFILE.bodyHeight);
}

export function sweepNativeActorBox(from,to,actor,width,height) {
  const p = actor.root.position;
  let enter = 0, exit = 1;
  for (const axis of ['x', 'y', 'z']) {
    const low = p[axis] - (axis === 'y' ? 0 : width);
    const high = p[axis] + (axis === 'y' ? height : width);
    const delta = to[axis] - from[axis];
    if (Math.abs(delta) < 1e-12) { if (from[axis] < low || from[axis] > high) return null; continue; }
    const a = (low - from[axis]) / delta, b = (high - from[axis]) / delta;
    enter = Math.max(enter, Math.min(a, b)); exit = Math.min(exit, Math.max(a, b));
    if (enter > exit) return null;
  }
  return enter;
}

export class NativeMusketSystem {
  constructor({ getTargets = () => [], canHit = () => true, getColliders = () => [], onActorHit = () => {}, onWorldHit = () => {}, bodyRadius = .4 } = {}) {
    this.getTargets = getTargets; this.getColliders = getColliders; this.onActorHit = onActorHit; this.onWorldHit = onWorldHit; this.bodyRadius = bodyRadius;
    this.raycaster = new THREE.Raycaster(); this.serial = 0; this.paused = false; this.disposed = false; this.releases = new WeakMap();
    this.canHit=canHit;
  }
  get size() { return 0; }
  pause(value = true) { this.paused = !!value; }
  // A caller may shorten the query, but never extend the original maximum.
  fire({ owner, position, direction, range = NATIVE_MUSKET_PROFILE.range, sourcePosition = null, context = {} } = {}) {
    if (this.disposed || this.paused || !owner || !position || !direction || !Number.isFinite(range) || range <= 0 || direction.lengthSq() < 1e-12) return null;
    const shot = { id: ++this.serial, owner, position: position.clone(), context, profile: NATIVE_MUSKET_PROFILE, removed: true, removalReason: 'miss' };
    const blocked = sourcePosition && worldSegmentContact(this, sourcePosition, position, 0);
    if (blocked) { shot.position.copy(blocked.center); shot.removalReason = 'world'; this.onWorldHit(shot, blocked); return shot; }
    range = Math.min(range, NATIVE_MUSKET_PROFILE.range);
    const to = position.clone().addScaledVector(direction.clone().normalize(), range), world = worldSegmentContact(this, position, to, 0);
    if (world) to.copy(world.center);
    shot.position.copy(to);
    // The native loop does not shorten the ray after hitting a fighter.
    // Keep the provider's stable actor order; callbacks may remove targets.
    const contacts = [], seen = new Set();
    for (const target of this.getTargets(shot) || []) {
      if (!target || target === owner || target.id === owner.id || target.dead || target.disposed || target.scriptRemoved || target.hp <= 0 || !this.canHit(owner,target)) continue;
      const key = target.id ?? target;
      if (seen.has(key)) continue; seen.add(key);
      const t = sweepNativeMusketBody(position, to, target);
      if (t != null) contacts.push({ target, point: position.clone().lerp(to, t) });
    }
    if (world) { shot.removalReason = 'world'; this.onWorldHit(shot, world); }
    if (contacts.length) shot.removalReason = 'actor';
    for (const { target, point } of contacts) this.onActorHit(shot, target, point);
    return shot;
  }
  firePose({ owner, state, context = {}, ...aim } = {}) {
    if (!owner || !state || !Number.isFinite(state.serial) || !NATIVE_MUSKET_PROFILE.poseIds.includes(state.poseId) || this.paused || this.disposed) return [];
    let record = this.releases.get(owner);
    if (record && state.serial < record.serial) return [];
    if (!record || record.serial !== state.serial) { record = { serial: state.serial, fired: false }; this.releases.set(owner, record); }
    const shots = [];
    for (const attack of state.attacks || []) {
      if (record.fired) break;
      record.fired = true;
      const shot = this.fire({ owner, ...aim, context: { ...context,
        state: { poseId: state.poseId, pose: state.pose, source: state.source, serial: state.serial }, attack: { ...attack } } });
      if (shot) shots.push(shot); else record.fired = false;
    }
    return shots;
  }
  // Immediate shots leave no active flight object. Clear only resets release
  // identities when the host restarts a match or changes maps.
  clear() { this.releases = new WeakMap(); }
  dispose() { this.clear(); this.disposed = true; }
}

// 004f0230 builds [target?, launch-position]; 004f0ee0 owns collisions,
// 004e5760 advances the queue. Native coordinates are converted at .08.
export const NATIVE_WHEEL_PROFILE = Object.freeze({
  model: 'w6_0', weaponItem: 2, originHeight: 20 * .08, poseIds: Object.freeze([218, 220, 222]),
  speed: 600 * .08, targetRange: 600 * .08, acceleration: 8000 * .08,
  steeringDelay: .09, arrivalRadius: 26 * .08, lifetime: 5, spin: 16,
  predictionPeriod: 1 / 30, predictionSeconds: .2, hitCooldown: .4,
  bodyHalfWidth: Math.fround(2.6) * 7 * .08, bodyHeight: 36 * .08,
  collisionReturnScale: Math.fround(1.2), tumble: 16,
  provenance: '004f0230: target+20 then launch-position+20.004f2e70/004f3e70: nearest-to-forward enemy within600, no wall query.004f0ee0:30Hz target prediction+.2*velocity, per-victim timer>.4, first eligible box hit without changing path; scene collision rolls back, zeroes velocity, skips a waypoint or enables collision-free +7c return.004e5760: Euler translation, age>.09 steering8000, speed600 (+7c*float32(1.2)), arrival<26; empty queue completes next tick; age>5 expires. Web fixed-step timing, actor eligibility and scene triangle query are host adapters.'
});

function liveWheelActor(actor) {
  return actor?.root?.position && !actor.dead && !actor.disposed && !actor.scriptRemoved && !(actor.hp <= 0);
}

// The native selector maximizes horizontal forward dot, rather than choosing
// the closest actor or allowing a lock behind the thrower to redirect release.
export function selectNativeWheelTarget(owner, candidates, direction) {
  let best = null, bestDot = 0;
  const forward = direction.clone(); forward.y = 0; forward.normalize();
  for (const target of candidates || []) {
    if (!liveWheelActor(target) || target === owner || (owner.id != null && target.id === owner.id) || nativeSameTeam(owner,target)) continue;
    const delta = target.root.position.clone().sub(owner.root.position), horizontal = Math.hypot(delta.x,delta.z);
    if (delta.length() > NATIVE_WHEEL_PROFILE.targetRange || horizontal < .001 * .08) continue;
    const dot = (delta.x * forward.x + delta.z * forward.z) / horizontal;
    if (dot > bestDot) { best = target; bestDot = dot; }
  }
  return best;
}

export class NativeWheelSystem {
  constructor({ scene, getTargets = () => [], canHit = () => true, getColliders = () => [], onActorHit = () => {}, onWorldHit = () => {}, bodyRadius = .4 } = {}) {
    Object.assign(this, { scene, getTargets, canHit, getColliders, onActorHit, onWorldHit, bodyRadius });
    this.active = []; this.serial = 0; this.raycaster = new THREE.Raycaster(); this.paused = false; this.disposed = false;
    this.time = 0; this.contacts = new WeakMap();
  }
  get size() { return this.active.length; }
  hasOwner(owner) { return this.active.some(shot => shot.owner === owner); }
  pause(value = true) { this.paused = !!value; }
  noteActorContact(target) { this.contacts.set(target,this.time); }
  spawn({ owner, position, direction, visual, context = {}, target } = {}) {
    if (this.disposed || this.paused || !liveWheelActor(owner) || !position || !direction || !direction.lengthSq() || this.hasOwner(owner)) return null;
    const profile = NATIVE_WHEEL_PROFILE, root = new THREE.Group(); root.position.copy(position); if (visual) root.add(visual);
    const shot = { id: ++this.serial, owner, root, visual, context, position: position.clone(), previous: position.clone(),
      phase: 'outbound', age: 0, removed: false, profile, velocity: direction.clone().normalize().multiplyScalar(profile.speed),
      waypoints: [], collisionReturn: false, nextPrediction: profile.predictionPeriod, spin: 0, tumble: 0 };
    // An explicit null means no target; undefined asks the native selector.
    shot.target = target === undefined ? selectNativeWheelTarget(owner,this.getTargets(shot),direction) : target;
    if (liveWheelActor(shot.target)) shot.waypoints.push({ kind:'target', position:shot.target.root.position.clone().add(new THREE.Vector3(0,profile.originHeight,0)) });
    else shot.target = null;
    shot.waypoints.push({ kind:'return', position:owner.root.position.clone().add(new THREE.Vector3(0,profile.originHeight,0)) });
    this._phase(shot); this.active.push(shot); this.scene?.add(root); this.onFlightSample?.(shot,'spawn'); return shot;
  }
  _phase(shot) { shot.phase = shot.waypoints[0]?.kind === 'target' ? 'outbound' : 'return'; }
  update(dt) {
    if (this.disposed || this.paused || !(dt > 0) || !Number.isFinite(dt)) return;
    this.time += dt;
    for (const shot of [...this.active]) {
      if (shot.removed) continue;
      const {owner,profile} = shot; shot.age += dt;
      if (owner.disposed || owner.scriptRemoved) { this.remove(shot,'departure'); continue; }
      // Native removal is strictly >5; ordinary owner death does not cancel an
      // already released wheel. End-of-match cleanup still clears all shots.
      if (shot.age > profile.lifetime) { this.remove(shot,'expired'); continue; }
      if (!shot.waypoints.length) { this.remove(shot,'caught'); continue; }
      if (shot.age + 1e-10 >= shot.nextPrediction) {
        shot.nextPrediction = (Math.floor((shot.age + 1e-10) / profile.predictionPeriod) + 1) * profile.predictionPeriod;
        if (shot.waypoints.length > 1 && shot.target?.root && !shot.target.disposed && !shot.target.scriptRemoved) {
          const point = shot.waypoints[0].position;
          point.copy(shot.target.root.position).y += profile.originHeight;
          if (shot.target.velocity) point.addScaledVector(shot.target.velocity,profile.predictionSeconds);
          // Host fighters store native vertical velocity separately from x/z.
          if (Number.isFinite(shot.target.vy)) point.y += (shot.target.vy - (shot.target.velocity?.y || 0)) * profile.predictionSeconds;
        }
      }
      shot.previous.copy(shot.position); shot.position.addScaledVector(shot.velocity,dt);
      shot.spin += profile.spin * dt;
      if (shot.collisionReturn) shot.tumble += profile.tumble * dt;
      if (shot.visual) { shot.visual.rotation.y = shot.spin; shot.visual.rotation.x = shot.tumble; }
      if (shot.age > profile.steeringDelay) {
        const delta = shot.waypoints[0].position.clone().sub(shot.position);
        if (delta.length() < profile.arrivalRadius) { shot.waypoints.shift(); this._phase(shot); }
        else {
          shot.velocity.addScaledVector(delta.normalize(),profile.acceleration * dt);
          shot.velocity.clampLength(0,profile.speed * (shot.collisionReturn ? profile.collisionReturnScale : 1));
        }
      }
      // +7c skips both scene and actor collisions. A normal return remains
      // damaging and still tests walls until this special state is entered.
      if (!shot.collisionReturn) {
        const world = worldSegmentContact(this,shot.previous,shot.position,0);
        if (world) {
          shot.position.copy(shot.previous); shot.velocity.set(0,0,0);
          if (!shot.waypoints.length) { shot.root.position.copy(shot.position); this.remove(shot,'world'); this.onWorldHit(shot,world); continue; }
          if (shot.waypoints.length > 1) shot.waypoints.shift(); else shot.collisionReturn = true;
          this._phase(shot); this.onWorldHit(shot,world);
        } else {
          // Native actor-map order chooses the first valid box contact in a
          // tick, not the nearest contact; damage never consumes the wheel.
          for (const actor of this.getTargets(shot) || []) {
            if (!liveWheelActor(actor) || actor === owner || (owner.id != null && actor.id === owner.id) || !this.canHit(owner,actor)) continue;
            if (this.time - (this.contacts.get(actor) ?? -Infinity) <= profile.hitCooldown + 1e-10) continue;
            const t = sweepNativeActorBox(shot.previous,shot.position,actor,profile.bodyHalfWidth,profile.bodyHeight);
            if (t == null) continue;
            this.noteActorContact(actor); this.onActorHit(shot,actor,shot.previous.clone().lerp(shot.position,t)); break;
          }
        }
      }
      if (shot.removed) continue;
      shot.root.position.copy(shot.position); this.onFlightSample?.(shot,'update');
    }
  }
  remove(shot,reason='removed') {
    if (!shot || shot.removed) return;
    // Mark before callbacks, so cleanup/reentrant damage cannot release twice.
    shot.removed = true; shot.removalReason = reason; shot.root.position.copy(shot.position);
    this.onFlightSample?.(shot,reason); shot.root.removeFromParent();
    const i = this.active.indexOf(shot); if (i >= 0) this.active.splice(i,1);
    if (shot.owner.weapon === 'wheel' && shot.owner.weaponModel) shot.owner.weaponModel.visible = true;
  }
  clear(reason='clear') { for (const shot of [...this.active]) this.remove(shot,reason); this.contacts = new WeakMap(); }
  dispose() { this.clear('dispose'); this.disposed = true; }
}

// Original NPC perception:004fc0b0 first accepts nearby actors or a positive
// forward dot(004fc610), then requires View and an unobstructed sight ray
// (004fc980→004fc8a0). 004fdf00 can retain a known target within200 units.
// Actor eye points, collision rays and nearest-target selection remain Web
// adapters; the complete original AI decisions and PRNG are not implemented.
const SCALE = .08;
export const NATIVE_AWARENESS = Object.freeze({
  defaultView: 400, nearby: 80 * SCALE, retainDistance: 200 * SCALE,
  provenance: 'Meteor.exe005012f0/004fe1a0 View field/default400;004fc0b0 nearby distance²6400;004fc610 forward dot>0;004fc8a0 View×multiplier with004fda00 default1;004fdf00 cached enemy distance²<40000.'
});

const alive = actor => !!actor?.root?.position && !actor.dead && !actor.disposed && !actor.scriptRemoved && actor.hp > 0;
export function nativeEnemies(actor, target) {
  return actor !== target && alive(actor) && alive(target) && !(target.team > 0 && target.team === actor.team);
}

export function nativeCanDiscover(actor, target, lineOfSight) {
  if (!nativeEnemies(actor, target)) return false;
  const distanceSquared = actor.root.position.distanceToSquared(target.root.position);
  const view = Number(actor.scriptConfig?.View ?? NATIVE_AWARENESS.defaultView) * SCALE;
  if (!Number.isFinite(view) || view < 0 || distanceSquared > view * view) return false;
  const delta = target.root.position.clone().sub(actor.root.position), yaw = actor.root.rotation.y;
  if (distanceSquared > NATIVE_AWARENESS.nearby ** 2 && Math.sin(yaw) * delta.x + Math.cos(yaw) * delta.z <= 0) return false;
  return !!lineOfSight(actor, target);
}

export function findNativeEnemy(actor, candidates, lineOfSight) {
  if (!alive(actor)) { if (actor) actor.awarenessTarget = null; return null; }
  const previous = actor.awarenessTarget;
  const visible = [...candidates].filter(target => nativeCanDiscover(actor, target, lineOfSight))
    .sort((a, b) => actor.root.position.distanceToSquared(a.root.position) - actor.root.position.distanceToSquared(b.root.position))[0];
  if (visible) return actor.awarenessTarget = visible;
  if (candidates.includes(previous) && nativeEnemies(actor, previous) &&
      actor.root.position.distanceToSquared(previous.root.position) < NATIVE_AWARENESS.retainDistance ** 2) return previous;
  actor.awarenessTarget = null; return null;
}

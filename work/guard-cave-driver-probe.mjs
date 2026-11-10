import { nativeFiles, nativeMission, tick } from '../tests/helpers/native-mission-fixture.mjs';

// CPU-only reproducible investigation. Original HP, NPC logic, collision,
// positions, damage and results are not assigned by this input driver.
const restore = nativeFiles();
const snapshot = game => ({ time: game.matchElapsed, hp: game.hero.hp, player: game.hero.root.position.toArray(),
  enemies: game.enemies.map(actor => ({ id: actor.scriptId, position: actor.root.position.toArray(), intent: actor.scriptIntent?.mode,
    paused: actor.scriptControl?.paused, canAttack: actor.scriptControl?.canAttack,
    distance: actor.root.position.distanceTo(game.hero.root.position), lineOfSight: game.hasScriptLineOfSight(actor, game.hero),
    moveTarget: actor.scriptControl?.moveTarget?.toArray(), pose: actor.combat.timeline?.pose.id })) });

try {
  for (const seed of [1, 2, 3, 4]) {
    let state = seed;
    Math.random = () => { state = (Math.imul(state, 214013) + 2531011) >>> 0; return ((state >>> 16) & 32767) / 32768; };
    const fixture = await nativeMission('sn01'), { game, host } = fixture;
    try {
      for (const id of host.route(9, 53)) {
        const goal = host.points.get(id).navigationPosition;
        for (let frame = 0; frame < 600 && game.running; frame++) {
          const delta = goal.clone().sub(game.hero.root.position);
          if (Math.hypot(delta.x, delta.z) < .7) break;
          game.cameraAngle = Math.atan2(-delta.x, -delta.z); game.action('forward'); tick(game, 1 / 30);
        }
      }
      let lastHp = game.hero.hp, lastHitAt = game.matchElapsed;
      for (let frame = 0; frame < 3600 && game.running; frame++) {
        const enemy = game._nearest(); if (!enemy) break;
        const delta = enemy.root.position.clone().sub(game.hero.root.position);
        game.action('forward', false);
        if (Math.hypot(delta.x, delta.z) > 1.1) {
          game.cameraAngle = Math.atan2(-delta.x, -delta.z); game.action('forward');
        }
        tick(game, 1 / 30);
        if (game.hero.hp !== lastHp) { lastHp = game.hero.hp; lastHitAt = game.matchElapsed; }
        if (game.matchElapsed - lastHitAt > 20) break;
      }
      console.log(JSON.stringify({ seed, dead: game.hero.dead, ...snapshot(game) }));
    } finally { fixture.dispose(); }
  }
} finally { restore(); }

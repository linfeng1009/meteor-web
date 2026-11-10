import { writeFile, readFile } from 'node:fs/promises';
import { createHash } from 'node:crypto';
import { nativeFiles, nativeMission, tick } from '../../tests/helpers/native-mission-fixture.mjs';

// Read-only gameplay investigation: original source startup followed by camera
// yaw and public forward/jump inputs only. No HP, position or AI-state assignment.
const root = new URL('../../', import.meta.url), out = new URL('./', import.meta.url);
const baseline = {};
for (const name of ['dist/engine.js', 'dist/native-combat.js', 'dist/native-character.js', 'dist/native-mission-host.js', 'tests/helpers/native-mission-fixture.mjs']) {
  baseline[name] = createHash('sha256').update(await readFile(new URL(name, root))).digest('hex');
}
await writeFile(new URL('source-hashes.json', out), JSON.stringify(baseline, null, 2) + '\n');
const restore = nativeFiles(), normalFetch = globalThis.fetch;
const scenarios = ['123', '321', '213', '231', '312', '132'];
const snapshot = game => ({ time: game.matchElapsed, hp: game.hero.hp, player: game.hero.root.position.toArray(),
  playerPose: game.hero.combat.timeline?.pose.id, playerFrame: game.hero.combat.timeline?.frame,
  playerGrounded: game.hero.grounded, playerVelocity: game.hero.velocity.toArray(), keys: [...game.keys],
  floor: game._ground(game.hero.root.position.x, game.hero.root.position.z, game.hero.root.position.y + .8)?.object?.name,
  enemies: game.enemies.map(actor => ({ id: actor.scriptId, position: actor.root.position.toArray(), yaw: actor.root.rotation.y,
    intent: actor.scriptIntent?.mode, intentTarget: actor.scriptIntent?.targetRef, nav: actor.scriptPath,
    paused: actor.scriptControl?.paused, canAttack: actor.scriptControl?.canAttack,
    distance: actor.root.position.distanceTo(game.hero.root.position), lineOfSight: game.hasScriptLineOfSight(actor, game.hero),
    moveTarget: actor.scriptControl?.moveTarget?.toArray(), pose: actor.combat.timeline?.pose.id,
    frame: actor.combat.timeline?.frame, timer: actor.aiTimer })) });
try {
  for (const order of scenarios) {
    const seed = 5;
    globalThis.fetch = async input => {
      const text = input instanceof Request ? input.url : String(input), match = text.match(/npc01_0([123])\.pst/);
      if (match) await new Promise(resolve => setTimeout(resolve, order.indexOf(match[1]) * 35));
      return normalFetch(input);
    };
    let state = seed, draws = 0;
    Math.random = () => { draws++; state = (Math.imul(state, 214013) + 2531011) >>> 0; return ((state >>> 16) & 32767) / 32768; };
    const fixture = await nativeMission('sn01'), { game, host, events } = fixture, trace = [], initialActorOrder = game.enemies.map(a => a.scriptId);
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
        if (Math.hypot(delta.x, delta.z) > 1.1) { game.cameraAngle = Math.atan2(-delta.x, -delta.z); game.action('forward'); }
        tick(game, 1 / 30);
        if (game.hero.hp !== lastHp) { lastHp = game.hero.hp; lastHitAt = game.matchElapsed; }
        if (frame % 150 === 0) trace.push(snapshot(game));
        if (game.matchElapsed - lastHitAt > 20) break;
      }
      const result = { seed, order, initialActorOrder, draws, dead: game.hero.dead, timeSinceHit: game.matchElapsed - lastHitAt, ...snapshot(game),
        trace, hits: events.filter(event => event.type === 'hit' && event.targetHero) };
      await writeFile(new URL(`order-${order}-seed-${seed}.json`, out), JSON.stringify(result, null, 2) + '\n');
      console.log(JSON.stringify({ seed, order, initialActorOrder, dead: result.dead, time: result.time, hp: result.hp, draws, secondsSinceHit: result.timeSinceHit }));
      if (!game.hero.dead) break;
    } finally { fixture.dispose(); }
  }
} finally { restore(); }

import test, { after } from 'node:test';
import assert from 'node:assert/strict';
import { nativeFiles, nativeMission, tick, attackWhenReady, v } from './helpers/native-mission-fixture.mjs';

// Real original maps, FMC floors, waypoints, actors, weapons, bones, POS/ACT,
// RES arithmetic and PST. Image decode/audio/labels/render loop are omitted.
const restore = nativeFiles(), fixtures = [];
async function mission(id) { const f = await nativeMission(id); fixtures.push(f); return f; }
after(() => { for (const f of fixtures) f.dispose(); restore(); });
function waitIntro(game) { for (let frame = 0; frame < 340; frame++) tick(game, .1, { enemies: false }); }
function near(game, actor) { game._placeFighter(game.hero, { position: actor.root.position.clone().add(v(0, 0, -1.1)) }); game.locked = actor; }
function damageVip(game, vip, threshold = 0) {
  // Controlled combat acceptance: only the player's combat is advanced;
  // retaliation and VIP movement are frozen while source damage is applied.
  // No target HP/dead/position is assigned, and the source PST keeps running.
  near(game, vip);
  for (let frame = 0; frame < 30000 && vip.hp > threshold && game.running; frame++) {
    if (!game.hero.combat.busy) near(game, vip);
    attackWhenReady(game); tick(game, 1 / 30, { enemies: false });
  }
  assert.ok(vip.hp <= threshold, `ordinary source dual attacks did not reach HP${threshold}: ${vip.hp}`);
}

test('both new missions load real source geometry, original equipment and exact NPC HP/team/spawns', async () => {
  for (const id of ['sn09', 'sn15']) {
    const { game, host } = await mission(id);
    assert.equal(game.hero.character.appearance, 'original');
    assert.ok(game.enemies.every(actor => actor.character.appearance === 'original'));
    assert.equal(game.currentMap.props.warnings.length, 0); assert.equal(host.diagnostics.length, 0);
    assert.equal(game.hero.hp, id === 'sn09' ? 3000 : 2500);
    assert.equal(game.hero.weaponId, id === 'sn09' ? 5 : 13);
    assert.equal(game.hero.weapon2Id, id === 'sn09' ? 1 : 10);
    for (const actor of [game.hero, ...game.enemies]) {
      const floor = game._ground(actor.root.position.x, actor.root.position.z, actor.root.position.y + .1);
      assert.ok(floor, actor.name); assert.ok(Math.abs(actor.root.position.y - floor.point.y - .015) < 1e-4);
      assert.ok(actor.weaponModels.length); assert.ok(actor.weaponModels.every(model => model.parent));
    }
    if (id === 'sn09') {
      assert.deepEqual([...host.actors.values()].filter(a => !a.hero).sort((a,b) => a.scriptConfig.Spawn-b.scriptConfig.Spawn)
        .map(a => [a.name,a.modelId,a.weaponId,a.team,a.hp,a.scriptConfig.Spawn]), [['屠城',15,36,0,9990,0],['冷燕',1,33,2,3000,7]]);
      assert.equal([...game.currentMap.props.instances.values()].filter(i => /^D_sn09f\d+$/i.test(i.name)).length, 100);
    } else {
      assert.equal(game.enemies.length, 7); assert.equal(game.enemies.reduce((sum,a) => sum+a.hp, 0), 27500);
      assert.equal(host.findActor('无名'), null); assert.equal(host.findActor('vip'), host.findActor('萧安'));
      assert.equal(host.findActor('右护法').weapon, 'hammer'); assert.equal(host.findActor('右护法').hp, 5000);
      assert.equal(host.findActor('萧安').hp, 7500); assert.equal(host.findActor('萧安').scriptConfig.Spawn, 73);
    }
  }
});

test('sn09 normal movement/jump/guard from the source spawn survives all100 falling floors with living ColdYan and reaches original GameOver', async t => {
  const { game, host, events, endings } = await mission('sn09'), cold = host.findActor('冷燕'), goal = host.points.get(4).navigationPosition;
  // Live source AI and scene mechanisms remain active throughout. Inputs use
  // a waypoint-directed driver; no actor placement, HP or result override.
  for (let frame = 0; frame < 1200 && game.running; frame++) {
    const delta = goal.clone().sub(game.hero.root.position), distance = Math.hypot(delta.x, delta.z);
    if (distance < .7 && game.hero.root.position.y > 4) break;
    game.cameraAngle = Math.atan2(-delta.x, -delta.z); game.action('forward');
    if (!game.hero.scriptInputBlocked && game.hero.grounded && distance < 11) game.action('jump');
    tick(game, 1 / 30);
  }
  game.action('forward', false); assert.ok(game.hero.root.position.y > 4, 'authored takeoff must reach the actual4.68m platform');
  let crouched = false;
  for (let frame = 0; frame < 6300 && game.running; frame++) {
    const delta = goal.clone().sub(game.hero.root.position), move = Math.hypot(delta.x, delta.z) > .6;
    if (move) game.cameraAngle = Math.atan2(-delta.x, -delta.z);
    // Recover the platform center at normal movement speed after authored recoil;
    // hold defense once there. Permanently holding guard slows movement and
    // cannot counter the now-source-driven NPC combo's repeated pushback.
    game.action('forward', move); game.action('guard', !move);
    if (game.hero.grounded && game.hero.root.position.y < 4 && move) game.action('jump');
    tick(game, 1 / 30); crouched ||= cold.scriptCrouched;
  }
  assert.equal(endings.length, 1); assert.equal(endings[0].win, true); assert.equal(host.completed.reason, 'script-GameOver');
  assert.ok(host.clock >= 199 && host.clock < 200); assert.ok(game.hero.hp > 0 && cold.hp > 0 && !cold.dead);
  assert.equal(game.deaths, 0); assert.equal(game.kills, 0); assert.equal(game.totalDamage, 0); assert.ok(crouched);
  const floors = [...game.currentMap.props.instances.values()].filter(i => /^D_sn09f\d+$/i.test(i.name));
  assert.ok(floors.every(i => i.pose === 1 && i.state === 3));
  assert.equal(host.sceneVm.getGlobal('g_iActiveCount'), 101);
  const order = host.stdout.filter(args => args[0] === 'Active').map(args => Number(args[1].slice(-2)) || 100);
  assert.equal(order.length, 100); assert.equal(new Set(order).size, 100);
  for (const [start,end] of [[0,36],[36,64],[64,84],[84,100]]) assert.ok(order.slice(start,end).every(id => id > start && id <= end), 'source floor rings must keep their order');
  assert.ok(events.some(e => e.type === 'script-item' && e.actorId === 0 && e.itemId === 14));
  assert.ok(events.some(e => e.type === 'script-item' && e.actorId === cold.scriptId && e.itemId === 14));
  assert.equal(host.diagnostics.length, 0); assert.equal(host.disabledCallbacks.size, 0);
  assert.ok(events.some(e => e.type === 'dialogue' && e.text.includes('你先服下它吧')));
  t.diagnostic(`Live original-scene survival ${host.clock.toFixed(2)}s; playerHP${game.hero.hp}, ColdYanHP${cold.hp}; no HP/dead/result assignment.`);
  const oldActors = [...game.enemies]; await game.start({ map:'sn09', mode:'story' });
  assert.ok(host.disposed); assert.ok(oldActors.every(a => a.disposed)); assert.equal(game.hero.hp, 3000);
  assert.equal(game.hero.scriptItems.length, 0); assert.equal(game.hero.activeItems.length, 0); assert.equal(game.hero.nativeJump, null);
  assert.equal(game.missionHost.clock, 0); assert.equal(game.missionHost.completed, undefined);
  assert.ok(floors.every(i => i.pose === 0 && i.root.visible && i.attributes.collision === 1));
});

test('sn09 falling from the source spawn produces original delayed failure instead of a false survival victory', async () => {
  const { game, host, endings } = await mission('sn09');
  // Freeze NPC retaliation to isolate real FMC disappearance, gravity, death
  // and the source2-second failure. The player is never placed after spawn.
  for (let frame = 0; frame < 6000 && game.running; frame++) tick(game, 1 / 30, { enemies:false });
  assert.ok(game.hero.dead); assert.equal(game.hero.hp, 0); assert.equal(game.deaths, 1);
  assert.equal(host.completed.win, false); assert.equal(host.completed.reason, 'script-GameOver');
  assert.equal(endings.length, 1); assert.equal(host.levelVm.getGlobal('gameover'), 2); assert.equal(host.diagnostics.length, 0);
});

test('sn09 protected death overrides a pending positive story result in the original PST', async () => {
  const { game, host } = await mission('sn09');
  // VM boundary test only: freeze physics and directly supply protected HP0
  // after the source has scheduled success. This is not combat acceptance.
  for (let frame = 0; frame < 1820; frame++) host.update(.1);
  assert.equal(host.levelVm.getGlobal('gameover'), 1);
  host.findActor('冷燕').hp = 0;
  for (let frame = 0; frame < 50 && !host.completed; frame++) host.update(.1);
  assert.equal(host.completed.win, false); assert.equal(game.storyResult.reason, 'script-GameOver');
});

test('sn15 actual dual attacks defeat only the7500HP VIP, win with six other enemies alive, and restart restores source state', async () => {
  const { game, host, endings } = await mission('sn15'); waitIntro(game);
  const vip = host.findActor('萧安'); damageVip(game, vip);
  for (let frame = 0; frame < 60 && game.running; frame++) tick(game, 1 / 30, { enemies:false });
  assert.equal(game.totalDamage, 7500); assert.equal(game.kills, 1); assert.equal(game.enemies.filter(a => !a.dead).length, 6);
  assert.equal(endings.length, 1); assert.equal(host.completed.win, true); assert.equal(host.completed.reason, 'vip-defeated');
  assert.match(host.completed.provenance, /adapter/); assert.equal(host.diagnostics.length, 0);
  const oldActors = [...game.enemies]; await game.start({ map:'sn15', mode:'story' });
  assert.ok(oldActors.every(a => a.disposed)); assert.equal(game.enemies.length, 7); assert.equal(game.hero.hp, 2500);
  assert.equal(game.hero.weaponId, 13); assert.equal(game.hero.weapon2Id, 10); assert.equal(game.totalDamage, 0);
  assert.equal(game.missionState.objective.targetHp, 7500); assert.equal(game.missionState.objective.escaped, false);
});

test('sn15 injured VIP physically follows all escape stages to WP116 and original RemoveNPC/GameOver fails the mission', async t => {
  const { game, host, endings } = await mission('sn15'); waitIntro(game);
  const vip = host.findActor('萧安'), playerSpawn = game.hero.root.position.clone(); damageVip(game, vip, 1800);
  // Preparation above freezes NPC motion; now advance the living VIP's real
  // navigation/physics with other NPCs frozen, and leave the player at spawn.
  // VIP HP/dead/position and script globals are never assigned.
  game._placeFighter(game.hero, { position:playerSpawn }); game.locked = null;
  const stages = new Set();
  for (let frame = 0; frame < 6000 && game.running; frame++) {
    tick(game, 1 / 30, { enemies:false }); if (game.running) game._updateFighter(vip, 1 / 30);
    stages.add(host.levelVm.getGlobal('trg7'));
  }
  for (const phase of [3,4,5,6,7,8]) assert.ok(stages.has(phase), `missing original escape phase${phase}`);
  assert.ok(vip.hp > 0 && !vip.dead && vip.scriptRemoved && vip.disposed); assert.equal(game.kills, 0);
  assert.equal(endings.length, 1); assert.equal(host.completed.win, false); assert.equal(host.completed.reason, 'script-GameOver');
  assert.equal(game.missionState.objective.escaped, true); assert.equal(host.diagnostics.length, 0);
  t.diagnostic(`Actual VIP escape failed the mission at${host.clock.toFixed(2)}s, HP${vip.hp}.`);
});

test('sn15 real guard damage triggers the conditional friendly ally, source嗜战, and a friendly HUD marker exactly once', async () => {
  const { game, host, events } = await mission('sn15'); waitIntro(game);
  const guard = host.findActor('左护法'); near(game, guard); game.locked = null;
  // Contact-only incoming-damage fixture. Only the original left guard acts;
  // Keep contact range between recoveries as movement/weapon speeds change;
  // no player HP, result or source trigger/global is assigned.
  for (let frame = 0; frame < 6000 && game.running && !host.levelVm.getGlobal('trg8'); frame++) {
    if(!game.hero.combat.busy)game.hero.root.position.copy(guard.root.position).add(v(0,0,-1.1));
    tick(game, 1 / 30, { enemies:false }); game._updateFighter(guard, 1 / 30);
  }
  assert.ok(game.hero.hp > 0 && game.hero.hp < 2500/3); await host.flushPending(); host.update(.1);
  const ally = host.findActor('无名'); assert.ok(ally); assert.equal(ally.modelId, 10); assert.equal(ally.team, 1);
  assert.equal(ally.hp, 9999); assert.equal(ally.weaponId, 23); assert.equal(ally.scriptIntent.targetRef, 'vip');
  // Recoil can bring the player within the source dialogue radius. In that
  // branch use4 is queued behind the original3-second pause, not immediate.
  for (let frame=0; frame<400 && !ally.activeItems.some(item=>item.id===4); frame++) host.update(1/30);
  assert.ok(ally.activeItems.some(item => item.id === 4)); assert.ok(events.some(e => e.type === 'script-item' && e.actorId === ally.scriptId && e.itemId === 4));
  for (let frame = 0; frame < 20; frame++) host.update(.1); await host.flushPending();
  assert.equal([...host.actors.values()].filter(a => a.name === '无名').length, 1);
  let hud; game.onUpdate = state => { hud = state; }; game._hud();
  assert.equal(hud.enemies.length, 7); assert.equal(hud.allies.length, 1); assert.doesNotThrow(() => JSON.stringify(hud));
  assert.equal(host.diagnostics.length, 0);
});

test('pause freezes mission, floor and item clocks, and leaving clears script effects before another session', async () => {
  const { game, host } = await mission('sn09');
  for (let frame = 0; frame < 850; frame++) tick(game, 1 / 30, { enemies:false });
  assert.ok(game.hero.scriptItems.some(item => item.id === 14));
  const before = [host.clock, game.hero.hp, game.hero.scriptItems[0].remaining, host.sceneVm.getGlobal('g_iActiveCount')];
  game.pause(true); for (let frame = 0; frame < 600; frame++) tick(game, 1 / 30);
  assert.deepEqual([host.clock, game.hero.hp, game.hero.scriptItems[0].remaining, host.sceneVm.getGlobal('g_iActiveCount')], before);
  host.dispose(); assert.deepEqual(game.hero.scriptItems, []); assert.deepEqual(game.hero.activeItems, []);
});

import {NATIVE_AIR_PHYSICS} from '../dist/native-traversal.js';
import test, { after } from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { loadNativeCombat, createNativeDamageResolver, createNativeSceneDamageResolver } from '../dist/native-combat.js';

// Real original map, actors, bones, animation, weapons, arithmetic and PST on
// the CPU. Only image decode, audio, labels and the browser render loop are absent.
const dist = new URL('../dist/', import.meta.url), original = new URL('assets/original/', dist);
const previousFetch = globalThis.fetch, previousLoad = THREE.TextureLoader.prototype.load, previousRandom = Math.random;
// Fix only the browser adapter's AI cooldown jitter for reproducible acceptance.
Math.random = () => .5;
globalThis.fetch = async input => {
  try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); }
  catch { return new Response('', { status: 404 }); }
};
THREE.TextureLoader.prototype.load = function (url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
const manifest = JSON.parse(await readFile(new URL('manifest.json', original), 'utf8'));
const weapons = JSON.parse(await readFile(new URL('weapon-models/manifest.json', original), 'utf8'));
const combat = await loadNativeCombat(), games = [], v = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
async function island() {
  const game = Object.create(MeteorGame.prototype), events = [], endings = [];
  Object.assign(game, {
    manifest, combatData: combat, weaponManifest: weapons,
    weaponItems: new Map(weapons.items.map(item => [Number(item.itemId), item])),
    weaponModels: new Map(weapons.models.map(model => [model.modelId.toLowerCase(), model])),
    weaponCache: new Map(), effectDefinitions: new Map(), waveFiles: new Map(), effects: [],
    scene: new THREE.Scene(), camera: new THREE.PerspectiveCamera(), cameraTarget: v(),
    raycaster: new THREE.Raycaster(), collisionMaterial: new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }),
    hostPhysics: { speed: 8, gravity: NATIVE_AIR_PHYSICS.gravity, jumpVelocity: NATIVE_AIR_PHYSICS.jumpVelocity, radius: .4, step: .55 },
    map: 'sn14', mode: 'training', weapon: 'sword', characterId: 0, characterAppearance: 'original', appearanceRequest: 0,
    actorSerial: 0, enemies: [], keys: new Set(), directionBuffer: [], sessionRequest: 0, characterRequest: 0,
    mapRequest: 0, running: false, paused: false, elapsed: 0, difficulty: 'normal',
    kills: 0, deaths: 0, totalDamage: 0, contactHits: 0, matchElapsed: 0, time: 0,
    cameraAngle: 0, cameraPitch: .4, cameraDistance: 8,
    onUpdate() {}, onEvent: event => events.push(event), onEnd: result => endings.push(result),
    _nameplate() {}, _unlockAudio() {}, _soundDefinition() {}
  });
  game._initializeProjectiles(); game.damageResolver = createNativeDamageResolver(combat); game.sceneDamageResolver = createNativeSceneDamageResolver(combat);
  game.currentMap = await game._readMap('sn14'); game.scene.add(game.currentMap.model);
  game.hero = await game._createFighter(0, '孟星魂', true); game.scene.add(game.hero.root); game.ready = Promise.resolve();
  await game.start({ map: 'sn14', mode: 'story' }); games.push(game); return { game, host: game.missionHost, events, endings };
}
function tick(game, dt = 1 / 60, { enemies = true, player = true } = {}) {
  if (!game.running || game.paused) return;
  game.elapsed += dt; game.matchElapsed += dt; game.missionHost.update(dt); game.currentMap.props.update(dt);
  if (!game.running) return;
  if (player) game._updateFighter(game.hero, dt);
  if (enemies) for (const actor of game.enemies) { if (!game.running) break; game._updateFighter(actor, dt); }
  if (player && enemies) game._separateCharacters(dt);
  if (game.running) game.projectiles.update(dt);
}
function placeNear(game, actor, distance = 1.1) {
  const candidates = [v(0, 0, -distance), v(0, 0, distance), v(distance, 0, 0), v(-distance, 0, 0)];
  for (const offset of candidates) {
    game._placeFighter(game.hero, { position: actor.root.position.clone().add(offset) });
    if (game.hasScriptLineOfSight(actor, game.hero)) return;
  }
  assert.fail(`actual source ${actor.name} spawn needs a clear near contact position`);
}
after(() => {
  for (const game of games) {
    game.projectiles.dispose(); game.missionHost?.dispose();
    for (const actor of [game.hero, ...game.enemies]) actor.character.dispose(); game._disposeMap(game.currentMap);
  }
  globalThis.fetch = previousFetch; THREE.TextureLoader.prototype.load = previousLoad; Math.random = previousRandom;
});

test('island mission loads the two original NPCs, source player configuration, dialogue and patrol routes on real floors', async () => {
  const { game, host, events } = await island();
  assert.equal(host.mapId, 'sn14'); assert.equal(host.rule, 10); assert.equal(host.roundTime, 10);
  assert.equal(game.hero.hp, 1000); assert.equal(game.hero.weaponId, 6); assert.equal(game.hero.weapon2Id, 0);
  assert.deepEqual([...game.enemies].sort((a, b) => a.scriptId - b.scriptId).map(a => [a.name, a.modelId, a.weaponId, a.weapon2Id, a.scriptConfig.Spawn, a.hp]), [
    ['大刀哨兵', 2, 8, 2, 0, 1000], ['铁枪哨兵', 8, 7, 2, 33, 1000]
  ]);
  assert.deepEqual(host.actor(1).scriptIntent.waypointIds, [0]); assert.deepEqual(host.actor(2).scriptIntent.waypointIds, [16, 18, 19, 20, 21]);
  for (const actor of [game.hero, ...game.enemies]) {
    const p = actor.root.position, floor = game._ground(p.x, p.z, p.y + .1);
    assert.ok(floor); assert.ok(Math.abs(p.y - floor.point.y - .015) < 1e-4, actor.name);
  }
  assert.ok(events.some(e => e.type === 'dialogue' && e.text.startsWith('好呗，我也懒得听你的冷笑话')));
  assert.ok(events.some(e => e.type === 'dialogue' && e.text === '企企企！'));
  assert.deepEqual(host.route(34, 0), [34, 4, 31, 0]); assert.deepEqual(host.route(34, 33), [34, 4, 31, 33]);
  assert.equal(host.diagnostics.length, 0);
});

test('ordinary walking follows original island waypoint links from the source player spawn to both source guard spawns', async () => {
  const { game, host } = await island(), start = game.hero.root.position.clone();
  const path = [...host.route(34, 0), ...host.route(0, 33).slice(1)]; game.action('forward');
  // Navigation-only acceptance: keep the other actors and their retaliation
  // frozen. Do not place/teleport the player after the original source spawn.
  for (const id of path) {
    const goal = host.points.get(id).navigationPosition; let frame = 0;
    while (frame++ < 600 && (Math.hypot(goal.x - game.hero.root.position.x, goal.z - game.hero.root.position.z) > .65 || Math.abs(goal.y - game.hero.root.position.y) > .7)) {
      const delta = goal.clone().sub(game.hero.root.position); game.cameraAngle = Math.atan2(-delta.x, -delta.z);
      game._updateFighter(game.hero, 1 / 60);
    }
    assert.ok(game.hero.root.position.distanceTo(goal) < 1, `ordinary source path got stuck before WP${id}: ${game.hero.root.position.toArray()}`);
  }
  game.action('forward', false);
  assert.ok(game.hero.root.position.distanceTo(start) > 40); assert.equal(game.hero.dead, false); assert.equal(game.hero.grounded, true);
});

test('original reacquisition Perform attack becomes a single valid combat request without changing source patrol intent', async () => {
  const { game, host } = await island(), guard = host.actor(2), native = host.natives();
  placeNear(game, guard); host.update(.1);
  assert.equal(host.levelVm.getGlobal('trg2'), 1, 'source first sighting branch must run');
  game._placeFighter(game.hero, host.points.get(34));
  for (let frame = 0; frame < 360; frame++) host.update(1 / 60);
  assert.equal(host.levelVm.getGlobal('trg2'), 2, 'source target-lost branch must run');
  placeNear(game, guard); guard.aiTimer = 1000; host.update(.1);
  assert.equal(host.levelVm.getGlobal('trg2'), 3, 'source reacquisition branch must execute Perform attack');
  assert.equal(guard.scriptAttackRequested, true); assert.equal(guard.scriptControl.attackRequested, true);
  assert.equal(guard.scriptIntent.mode, 'patrol');
  game._updateFighter(guard, 1 / 60);
  assert.equal(guard.combat.attacking, true); assert.equal(guard.scriptAttackRequested, false);
  for (const mode of ['follow', 'kill']) {
    native.ChangeBehavior(guard.scriptId, mode, 0); native.Perform(guard.scriptId, 'attack'); host.processPerformances(0); host.updateControls();
    assert.equal(guard.scriptIntent.mode, mode, 'attack intent must preserve the original source follow/kill behavior');
    assert.equal(guard.scriptControl.attackRequested, true); native.StopPerform(guard.scriptId);
  }
  native.Perform(guard.scriptId, 'attack'); host.processPerformances(0); host.updateControls();
  assert.equal(guard.scriptAttackRequested, true); native.StopPerform(guard.scriptId); host.updateControls();
  assert.equal(guard.scriptAttackRequested, false); assert.equal(guard.scriptControl.attackRequested, false);
  native.Perform(guard.scriptId, 'attack'); host.processPerformances(0); guard.dead = true; host.processPerformances(0);
  assert.equal(guard.scriptAttackRequested, false, 'death cancels a pending script request');
  guard.dead = false; native.Perform(guard.scriptId, 'attack'); host.processPerformances(0); host.dispose();
  assert.equal(guard.scriptAttackRequested, false, 'leaving the mission cancels a pending request');
  assert.equal(host.diagnostics.some(e => e.code === 'UNSUPPORTED_PERFORM'), false);
});

test('a script attack request cannot bypass native scene line-of-sight or normal weapon reach', async () => {
  const { game, host } = await island(), guard = host.actor(2);
  host.natives().StopPerform(guard.scriptId); guard.aiTimer = 1000; guard.scriptAttackRequested = true;
  guard.scriptControl = { attackTarget: game.hero, canAttack: true, paused: false, guard: false, attackRequested: true };
  game._updateFighter(guard, 1 / 60);
  assert.equal(guard.combat.attacking, false, 'WP34 player is far outside source spear reach'); assert.equal(guard.scriptAttackRequested, true);
  placeNear(game, guard);
  const origin = guard.root.position.clone().add(v(0, 1.35, 0)), target = game.hero.root.position.clone().add(v(0, 1.35, 0));
  const wall = new THREE.Mesh(new THREE.PlaneGeometry(10, 10), new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }));
  wall.position.copy(origin).add(target).multiplyScalar(.5); wall.lookAt(target); wall.updateMatrixWorld(true); game.currentMap.colliders.push(wall);
  try {
    assert.equal(game.hasScriptLineOfSight(guard, game.hero), false); game._updateFighter(guard, 1 / 60);
    assert.equal(guard.combat.attacking, false); assert.equal(guard.scriptAttackRequested, true);
  } finally { game.currentMap.colliders.pop(); wall.geometry.dispose(); wall.material.dispose(); }
  game._updateFighter(guard, 1 / 60);
  assert.equal(guard.combat.attacking, true); assert.equal(guard.scriptAttackRequested, false);
});

test('island native sword combat consumes the source 2000 HP and executes both death lines before a single inferred victory and restart', async () => {
  const { game, host, events, endings } = await island();
  // Isolate the victory lifecycle from enemy retaliation. Source actors stay
  // at their real spawns; the player is positioned near them. No HP is assigned.
  for (const victim of game.enemies) {
    let attempts = 0;
    while (!victim.dead && attempts++ < 100) {
      placeNear(game, victim); game.locked = victim; game.action('attack');
      for (let frame = 0; frame < 100 && !victim.dead; frame++) tick(game, 1 / 60, { enemies: false });
    }
    assert.equal(victim.dead, true, `source sword did not defeat ${victim.name}`);
  }
  for (let frame = 0; frame < 180 && game.running; frame++) tick(game, 1 / 60, { enemies: false });
  assert.equal(game.totalDamage, 2000); assert.equal(game.kills, 2); assert.equal(endings.length, 1); assert.equal(endings[0].win, true);
  assert.equal(host.completed.reason, 'hostile-npcs-defeated'); assert.match(host.completed.provenance, /inference/);
  assert.ok(events.some(e => e.type === 'dialogue' && e.speaker === '大刀哨兵' && e.text.includes('两三下功夫')));
  assert.ok(events.some(e => e.type === 'dialogue' && e.speaker === '铁枪哨兵' && e.text.startsWith('大胡子﹒﹒﹒帮')));
  assert.equal(host.diagnostics.length, 0);
  await game.start({ map: 'sn14', mode: 'story' });
  assert.equal(game.hero.hp, 1000); assert.equal(game.hero.weaponId, 6); assert.equal(game.kills, 0); assert.equal(game.totalDamage, 0);
  assert.equal(game.missionHost.completed, undefined); assert.equal(game.enemies.length, 2);
  assert.ok(game.enemies.every(a => a.hp === 1000 && !a.dead && !a.scriptAttackRequested));
});

test('ordinary movement into living island guards causes natural failure and restart restores source HP and pending intents', async t => {
  const { game, host, endings } = await island(), guard = host.actor(2);
  // Contact failure acceptance, not a proof of a walk route from WP34.
  placeNear(game, guard); game.hero.scriptInputBlocked = false;
  for (let frame = 0; frame < 30 * 120 && game.running; frame++) {
    // Original recoil now moves the player. Reapproach with ordinary input
    // instead of assuming an idle target remains within NPC sight forever.
    const delta=guard.root.position.clone().sub(game.hero.root.position);
    const move=Math.hypot(delta.x,delta.z)>1.1;
    if(move)game.cameraAngle=Math.atan2(-delta.x,-delta.z);
    game.action('forward',move);tick(game,1/30);
  }
  assert.equal(game.hero.hp, 0); assert.equal(game.deaths, 1); assert.equal(endings.length, 1); assert.equal(endings[0].win, false);
  assert.equal(host.completed.reason, 'player-death'); assert.equal(host.diagnostics.length, 0);
  t.diagnostic(`Actual source guards caused failure after ${game.matchElapsed.toFixed(2)} simulated seconds; no HP/dead assignment.`);
  await game.start({ map: 'sn14', mode: 'story' });
  assert.equal(game.hero.hp, 1000); assert.equal(game.hero.dead, false); assert.equal(game.hero.rage, 0); assert.equal(game.contactHits, 0);
  assert.ok(game.enemies.every(a => !a.scriptAttackRequested && a.hp === a.maxHp));
});

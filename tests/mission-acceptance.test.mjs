import test, { after } from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { loadNativeCombat, createNativeDamageResolver } from '../dist/native-combat.js';

// Run the real game/mission/character/geometry code on the CPU. Only image
// decoding, audio, labels and the browser render loop are omitted. No damage,
// collision, animation, PST callback or native API is replaced by a formula.
const dist = new URL('../dist/', import.meta.url);
const previousFetch = globalThis.fetch, previousTextureLoad = THREE.TextureLoader.prototype.load;
globalThis.fetch = async input => {
  try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); }
  catch { return new Response('', { status: 404 }); }
};
THREE.TextureLoader.prototype.load = function (url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
after(() => { globalThis.fetch = previousFetch; THREE.TextureLoader.prototype.load = previousTextureLoad; });

const original = new URL('assets/original/', dist);
const manifest = JSON.parse(await readFile(new URL('manifest.json', original), 'utf8'));
const weaponManifest = JSON.parse(await readFile(new URL('weapon-models/manifest.json', original), 'utf8'));
const combat = await loadNativeCombat();
const vector = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
const games = [];

async function cave() {
  const game = Object.create(MeteorGame.prototype), events = [], endings = [];
  Object.assign(game, {
    manifest, combatData: combat, weaponManifest,
    weaponItems: new Map(weaponManifest.items.map(item => [Number(item.itemId), item])),
    weaponModels: new Map(weaponManifest.models.map(model => [model.modelId.toLowerCase(), model])),
    weaponCache: new Map(), effectDefinitions: new Map(), waveFiles: new Map(), effects: [],
    scene: new THREE.Scene(), camera: new THREE.PerspectiveCamera(), cameraTarget: vector(),
    raycaster: new THREE.Raycaster(), collisionMaterial: new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }),
    hostPhysics: { speed: 8, gravity: 34, jumpVelocity: 12, radius: .4, step: .55 },
    map: 'sn01', mode: 'training', weapon: 'sword', characterId: 0, actorSerial: 0,
    enemies: [], keys: new Set(), directionBuffer: [], sessionRequest: 0, characterRequest: 0,
    mapRequest: 0, running: false, paused: false, elapsed: 0, difficulty: 'normal',
    kills: 0, deaths: 0, totalDamage: 0, contactHits: 0, matchElapsed: 0, time: 0,
    cameraAngle: 0, cameraPitch: .4, cameraDistance: 8,
    onUpdate() {}, onEvent: event => events.push(event), onEnd: result => endings.push(result),
    _nameplate() {}, _unlockAudio() {}, _soundDefinition() {}
  });
  game._initializeProjectiles();
  game.damageResolver = createNativeDamageResolver(combat);
  game.currentMap = await game._readMap('sn01'); game.scene.add(game.currentMap.model);
  game.hero = await game._createFighter(0, '孟星魂', true); game.scene.add(game.hero.root);
  game.ready = Promise.resolve(); await game.start({ map: 'sn01', mode: 'story' });
  games.push(game); return { game, events, endings };
}

function tick(game, dt = 1 / 60, { enemies = true, player = true } = {}) {
  if (game.paused || !game.running) return;
  game.elapsed += dt; game.matchElapsed += dt;
  game.missionHost.update(dt); game.currentMap.props.update(dt);
  if (!game.running) return;
  if (player) game._updateFighter(game.hero, dt);
  if (enemies) for (const enemy of game.enemies) { if (!game.running) break; game._updateFighter(enemy, dt); }
  if (player && enemies) game._separateCharacters(dt);
  if (game.running) game.projectiles.update(dt);
}

after(() => {
  for (const game of games) {
    game.projectiles?.dispose();
    game.missionHost?.dispose();
    for (const actor of [game.hero, ...game.enemies]) actor.character.dispose();
    game._disposeMap(game.currentMap);
  }
});

test('the actual source mission starts on real floors with the original distinct NPC configuration', async () => {
  const { game, events } = await cave();
  assert.equal(game.hero.hp, 1500); assert.equal(game.hero.weaponId, 5); assert.equal(game.hero.weapon2Id, 1);
  assert.deepEqual(game.enemies.map(actor => [actor.scriptId, actor.modelId, actor.weaponId, actor.hp]).sort((a, b) => a[0] - b[0]), [[1, 8, 7, 1000], [2, 8, 7, 1000], [3, 8, 16, 2000]]);
  for (const actor of [game.hero, ...game.enemies]) {
    const p = actor.root.position, floor = game._ground(p.x, p.z, p.y + .1);
    assert.ok(floor, `${actor.name} requires actual source collision below the spawn`);
    assert.ok(Math.abs(p.y - floor.point.y - .015) < 1e-5);
  }
  assert.ok(events.some(event => event.type === 'dialogue' && event.text.startsWith('你们都听到萧老大说的了')));
  assert.equal(game.missionHost.diagnostics.length, 0);
});

test('a player dagger attack uses actual native pose, bones, weapon geometry and RES math to remove NPC HP', async () => {
  const { game } = await cave();
  const victim = game.missionHost.actor(1);
  // Isolate contact resolution at the actual NPC spawn; no NPC AI or synthetic
  // attachment coordinates are used in this combat acceptance fixture.
  game._placeFighter(game.hero, { position: victim.root.position.clone().add(vector(0, 0, -1.1)) });
  game.locked = victim; game.action('attack');
  for (let frame = 0; frame < 100 && victim.hp === victim.maxHp; frame++) game._updateFighter(game.hero, 1 / 60);
  assert.ok(victim.hp < victim.maxHp, `original dagger did not damage ${victim.name}; HP=${victim.hp}`);
  assert.ok(game.totalDamage > 0); assert.ok(game.contactHits > 0);
});

test('switching to the source secondary dart releases from the real hand and damages an original NPC only after flight', async () => {
  const { game, events } = await cave(), victim = game.missionHost.actor(1);
  game._placeFighter(game.hero, { position: victim.root.position.clone().add(vector(0, 0, -6)) });
  game.locked = victim; await game.switchWeapon();
  assert.equal(game.hero.weaponId, 1); assert.equal(game.hero.weapon2Id, 5); assert.equal(game.hero.weapon, 'dart');
  game.action('attack');
  // Run the actual AMB/SKC/POS release, then advance the flight separately to
  // show that changing HP is a projectile collision rather than a melee reach.
  for (let frame = 0; frame < 120 && game.projectiles.size === 0; frame++) game._updateFighter(game.hero, 1 / 60);
  assert.equal(game.projectiles.size, 1, 'the original hand/attack window must release one dart');
  assert.equal(victim.hp, victim.maxHp, 'a distant original NPC cannot take launch-time contact damage');
  const projectile = game.projectiles.active[0];
  assert.equal(projectile.context.state.poseId, 200); assert.equal(projectile.context.weaponId, 1);
  for (let frame = 0; frame < 120 && victim.hp === victim.maxHp; frame++) game.projectiles.update(1 / 60);
  assert.ok(victim.hp < victim.maxHp, `original hand-released dart did not damage ${victim.name}`);
  assert.equal(projectile.removalReason, 'actor'); assert.equal(game.contactHits, 1);
  assert.ok(events.some(event => event.type === 'hit' && event.projectileId === projectile.id));
});

test('all original mission NPC spawns are reachable from the player through WP edges and real collision geometry', async () => {
  const { game } = await cave(), host = game.missionHost;
  const route = [...host.route(9, 53), ...host.route(53, 80).slice(1), ...host.route(80, 32).slice(1)];
  assert.ok(route.length > 1);
  // Navigation acceptance only: freeze the other actors and combat, while the
  // real player movement, floor/step tests and original scene collisions run.
  game.running = false; game.keys.add('forward');
  for (const id of route) {
    const goal = host.points.get(id).navigationPosition;
    let reached = false;
    for (let frame = 0; frame < 600; frame++) {
      const delta = goal.clone().sub(game.hero.root.position);
      if (Math.hypot(delta.x, delta.z) < .7 && Math.abs(delta.y) < 1.1) { reached = true; break; }
      game.cameraAngle = Math.atan2(-delta.x, -delta.z);
      game._updateFighter(game.hero, 1 / 60);
    }
    assert.ok(reached, `blocked at WP${id} on ${route.join('→')}; player=${game.hero.root.position.toArray()} goal=${goal.toArray()}`);
  }
  game.keys.clear();
});

test('source patrol AI can reach and damage a player who enters the original guard area', async () => {
  const { game } = await cave();
  // WP67 is an actual connected point on the first-guard side of the cave.
  // The original player spawn is above the patrol floor and need not trigger
  // native sight; this fixture represents walking into the encounter area.
  game._placeFighter(game.hero, { position: game.missionHost.points.get(67).position });
  const minimumDistance = new Map(game.enemies.map(actor => [actor.scriptId, Infinity]));
  for (let frame = 0; frame < 900 && game.hero.hp === game.hero.maxHp && game.running; frame++) {
    tick(game, 1 / 30);
    for (const actor of game.enemies) minimumDistance.set(actor.scriptId, Math.min(minimumDistance.get(actor.scriptId), actor.root.position.distanceTo(game.hero.root.position)));
  }
  const details = game.enemies.map(actor => ({ scriptId: actor.scriptId, position: actor.root.position.toArray(), target: actor.scriptControl?.moveTarget?.toArray(), path: actor.scriptPath, minDistance: minimumDistance.get(actor.scriptId) }));
  assert.ok(game.hero.hp < 1500, `original patrol never engaged the idle player: ${JSON.stringify(details)}`);
});

test('real native attacks defeat source NPC HP and produce one story win, then restart resets the mission', async () => {
  const { game, events, endings } = await cave();
  const oldHost = game.missionHost, oldActors = [...game.enemies];
  // Freeze retaliation to isolate the complete player attack→HP→death→source
  // callbacks→Rule10 adapter→onEnd chain. No actor HP or dead flag is assigned.
  for (const victim of [...game.enemies]) {
    game._placeFighter(game.hero, { position: victim.root.position.clone().add(vector(0, 0, -1.1)) });
    game.locked = victim;
    for (let frame = 0; frame < 6000 && !victim.dead && game.running; frame++) {
      // Plain dagger input is the source 248→249 chain; 250/251 need ↑A.
      // Time the second click after the first actual hit window instead of
      // clicking every rendered frame and cancelling the first strike before
      // it can contact. The real original cancel graph still controls linking.
      const combat = game.hero.combat, timeline = combat.timeline;
      // Keep the controlled contact fixture near the stationary victim after
      // each complete combo; native entry-frame/root motion can carry the
      // attacker past them. This is not movement or live-AI acceptance.
      if (!combat.busy) game._placeFighter(game.hero, { position: victim.root.position.clone().add(vector(0, 0, -1.1)) });
      const lastHit = Math.max(...(timeline?.pose.attacks.map(attack => attack.end) || []));
      if (!combat.busy || combat.queued == null && timeline.canCancel && timeline.frame > lastHit) game.action('attack');
      tick(game, 1 / 60, { enemies: false });
    }
    assert.equal(victim.dead, true, `normal dagger attacks did not defeat ${victim.name} (HP=${victim.hp})`);
    assert.equal(victim.respawn, Infinity);
  }
  for (let frame = 0; frame < 100 && game.running; frame++) tick(game, 1 / 60, { enemies: false, player: false });
  assert.equal(game.running, false); assert.equal(endings.length, 1); assert.equal(endings[0].win, true);
  assert.equal(game.kills, 3); assert.equal(game.totalDamage, 4000, 'all source NPC HP must be removed by resolved attacks');
  assert.equal(game.storyResult.reason, 'hostile-npcs-defeated');
  assert.match(game.storyResult.provenance, /inference/);
  assert.ok(events.some(event => event.type === 'dialogue' && event.text.startsWith('呜﹒﹒﹒你别以为')), 'the original leader death callback must execute');
  const hp = game.enemies.map(actor => actor.hp);
  tick(game, 1); assert.deepEqual(game.enemies.map(actor => actor.hp), hp); assert.equal(endings.length, 1);
  await game.start({ map: 'sn01', mode: 'story' });
  assert.equal(oldHost.disposed, true);
  assert.ok(oldActors.every(actor => actor.disposed && actor.root.parent === null));
  assert.equal(game.running, true); assert.equal(game.hero.hp, 1500); assert.equal(game.hero.dead, false);
  assert.equal(game.hero.weaponId, 5); assert.equal(game.enemies.length, 3);
  assert.deepEqual(game.enemies.map(actor => actor.hp).sort((a, b) => a - b), [1000, 1000, 2000]);
  assert.equal(game.kills, 0); assert.equal(game.deaths, 0); assert.equal(game.storyResult, null);
});

for (const seed of [1, 2, 3, 4]) test(`walking normally into the source enemies causes player death and one failure, and restart resets accumulated state (jitter seed ${seed})`, async t => {
  // Control browser AI cooldown jitter so failures can be replayed. This is
  // test input, not recovery of the original process-wide random sequence.
  const priorRandom = Math.random; let randomState = seed;
  Math.random = () => { randomState = (Math.imul(randomState, 214013) + 2531011) >>> 0; return ((randomState >>> 16) & 32767) / 32768; };
  t.after(() => { Math.random = priorRandom; });
  const { game, endings, events } = await cave();
  const host = game.missionHost;
  const recent = [];
  for (const id of host.route(9, 53)) {
    const goal = host.points.get(id).navigationPosition;
    for (let frame = 0; frame < 600 && game.running; frame++) {
      const delta = goal.clone().sub(game.hero.root.position);
      if (Math.hypot(delta.x, delta.z) < .7) break;
      game.cameraAngle = Math.atan2(-delta.x, -delta.z); game.action('forward'); tick(game, 1 / 30);
    }
    assert.ok(Math.hypot(goal.x - game.hero.root.position.x, goal.z - game.hero.root.position.z) < .7, `the live player could not walk to WP${id}`);
  }
  // The original leader can wait after receiving the guards' report. An idle
  // player need not be chased forever, so use ordinary movement to approach
  // the living enemies rather than overriding that original script intent.
  for (let frame = 0; frame < 3600 && game.running; frame++) {
    const enemy = game._nearest(), delta = enemy.root.position.clone().sub(game.hero.root.position);
    if (frame % 300 === 0) recent.push({ time: game.matchElapsed, hp: game.hero.hp, position: game.hero.root.position.toArray(),
      enemies: game.enemies.map(actor => ({ id: actor.scriptId, position: actor.root.position.toArray(), intent: actor.scriptIntent?.mode,
        paused: actor.scriptControl?.paused, canAttack: actor.scriptControl?.canAttack, distance: actor.root.position.distanceTo(game.hero.root.position),
        lineOfSight: game.hasScriptLineOfSight(actor, game.hero), pose: actor.combat.timeline?.pose.id })) });
    game.action('forward', false);
    if (Math.hypot(delta.x, delta.z) > 1.1) {
      game.cameraAngle = Math.atan2(-delta.x, -delta.z); game.action('forward');
    }
    tick(game, 1 / 30);
  }
  if (!game.hero.dead) t.diagnostic(`Natural source-enemy failure trace: ${JSON.stringify(recent)}`);
  else t.diagnostic(`Jitter seed ${seed}: source enemies caused natural failure after ${game.matchElapsed.toFixed(2)} seconds; no HP/dead assignment.`);
  assert.equal(game.hero.dead, true, `source enemies failed to defeat an approaching player; HP=${game.hero.hp}; ${JSON.stringify(recent.at(-1))}`);
  assert.equal(game.hero.hp, 0); assert.equal(game.hero.respawn, Infinity);
  assert.equal(game.running, false); assert.equal(endings.length, 1); assert.equal(endings[0].win, false);
  assert.equal(game.deaths, 1);
  // Original102–106/111 reactions include body attack windows. Walking into
  // enemies can therefore cause passive impact damage after a knockback.
  // The acceptance contract forbids player attack input, not source body hits.
  assert.equal(events.filter(event => event.type === 'move').length, 0);
  const passiveHits = events.filter(event => event.type === 'hit' && event.attackerHero);
  const reactionBodies = new Set([...combat.poses.values()].filter(pose => pose.id >= 90 && pose.id <= 120 &&
    pose.attacks.some(attack => attack.bones.length && attack.bones.every(bone => !['weapon','effect'].includes(bone)))).map(pose => pose.id));
  assert.ok(passiveHits.every(hit => reactionBodies.has(hit.poseId)), 'damage without attack input must come from a source reaction body window');
  assert.equal(game.totalDamage, passiveHits.reduce((sum, hit) => sum + hit.amount, 0));
  assert.equal(game.storyResult.reason, 'player-death');
  assert.ok(game.hero.rage > 0, 'actual prior hits accumulated native victim rage');
  const oldActors = [...game.enemies];
  await game.start({ map: 'sn01', mode: 'story' });
  assert.equal(game.running, true); assert.equal(game.hero.hp, 1500); assert.equal(game.hero.dead, false);
  assert.equal(game.hero.rage, 0, 'new story runs must not inherit anger from the failed run');
  assert.equal(game.hero.contacts, 0, 'new story runs must not inherit contacts from the failed run');
  assert.ok(oldActors.every(actor => actor.disposed));
  assert.equal(game.enemies.length, 3); assert.equal(game.kills, 0); assert.equal(game.deaths, 0);
});

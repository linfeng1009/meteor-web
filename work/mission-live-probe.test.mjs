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

if (process.env.METEOR_MISSION_PROBE) test('probe live source mission from the player spawn', async () => {
  const { game, events, endings } = await cave(), host = game.missionHost;
  const report = () => JSON.stringify({ time: game.matchElapsed, hp: game.hero.hp, position: game.hero.root.position.toArray(), enemies: game.enemies.map(e => ({ id: e.scriptId, hp: e.hp, position: e.root.position.toArray(), intent: e.scriptIntent?.mode, target: e.scriptControl?.moveTarget?.toArray() })), hits: game.contactHits, kills: game.kills, end: endings });
  const walk = goal => { const delta = goal.clone().sub(game.hero.root.position); game.cameraAngle = Math.atan2(-delta.x, -delta.z); game.action('forward'); };
  for (const id of host.route(9, 53)) {
    const goal = host.points.get(id).navigationPosition;
    for (let i = 0; i < 600 && game.running && goal.clone().sub(game.hero.root.position).setY(0).length() > .7; i++) { walk(goal); tick(game); }
  }
  game.action('forward', false); console.log('AT GUARD', report());
  if (process.env.METEOR_MISSION_PROBE !== 'dagger') await game.switchWeapon();
  let nextReport = 10, retreating = false;
  for (let i = 0; i < 18000 && game.running; i++) {
    const victim = game.locked && !game.locked.dead ? game.locked : game._nearest(); if (!victim) { tick(game); continue; }
    if (game.locked !== victim) { if (game.locked) game.action('lock'); game.action('lock'); }
    const delta = victim.root.position.clone().sub(game.hero.root.position), distance = Math.hypot(delta.x, delta.z), visible = game.hasScriptLineOfSight(game.hero, victim);
    game.action('forward', false); game.action('back', false);
    const dagger = game.hero.weapon === 'dagger';
    if (distance < 10) retreating = true; if (distance > 17) retreating = false;
    if (distance > (dagger ? 1.15 : 19) || !visible) {
      const from = host.closestWaypoint(game.hero.root.position), to = host.closestWaypoint(victim.root.position), path = host.route(from.id, to.id);
      const next = path.find(id => host.points.get(id).navigationPosition.clone().sub(game.hero.root.position).setY(0).length() > .7);
      walk(visible ? victim.root.position : host.points.get(next ?? to.id).navigationPosition);
    } else if (!dagger && retreating) {
      const away = Math.atan2(-delta.x, -delta.z), p = game.hero.root.position;
      const directions = [0, .5, -.5, 1, -1, 1.57, -1.57].map(angle => vector(Math.sin(away + angle), 0, Math.cos(away + angle)));
      const direction = directions.find(d => !game._horizontalBlocked(p, d.x, 0) && !game._horizontalBlocked(p, 0, d.z) && game._ground(p.x + d.x, p.z + d.z, p.y + .6));
      if (direction) walk(p.clone().add(direction)); else game.action('attack');
    } else game.action('attack');
    tick(game);
    if (game.matchElapsed >= nextReport) { console.log('LIVE', report()); nextReport += 20; }
  }
  console.log('FINAL', report());
  assert.equal(endings[0]?.win, true);
});


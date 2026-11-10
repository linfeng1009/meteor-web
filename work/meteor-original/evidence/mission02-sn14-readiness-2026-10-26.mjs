// Offline preparation audit; original files are read, never executed/modified.
// Image decoding/audio/canvas labels are omitted; native geometry, animation,
// combat arithmetic, scene instances, waypoint navigation and PST are real.
import { readFile } from 'node:fs/promises';
import assert from 'node:assert/strict';
import * as THREE from '../../../dist/vendor/three.module.js';
import { MeteorGame } from '../../../dist/engine.js';
import { loadNativeCombat, createNativeDamageResolver, createNativeSceneDamageResolver } from '../../../dist/native-combat.js';

const dist = new URL('../../../dist/', import.meta.url), original = new URL('assets/original/', dist);
globalThis.fetch = async input => {
  try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); }
  catch { return new Response('', { status: 404 }); }
};
THREE.TextureLoader.prototype.load = function (url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
const manifest = JSON.parse(await readFile(new URL('manifest.json', original), 'utf8'));
const weaponManifest = JSON.parse(await readFile(new URL('weapon-models/manifest.json', original), 'utf8'));
const combat = await loadNativeCombat(), events = [], endings = [], game = Object.create(MeteorGame.prototype);
const v = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
Object.assign(game, {
  manifest, combatData: combat, weaponManifest,
  weaponItems: new Map(weaponManifest.items.map(item => [Number(item.itemId), item])),
  weaponModels: new Map(weaponManifest.models.map(model => [model.modelId.toLowerCase(), model])),
  weaponCache: new Map(), effectDefinitions: new Map(), waveFiles: new Map(), effects: [],
  scene: new THREE.Scene(), camera: new THREE.PerspectiveCamera(), cameraTarget: v(),
  raycaster: new THREE.Raycaster(), collisionMaterial: new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }),
  hostPhysics: { speed: 8, gravity: 34, jumpVelocity: 12, radius: .4, step: .55 },
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
await game.start({ map: 'sn14', mode: 'story' });
const host = game.missionHost;
function snapshot() {
  return { player: { hp: game.hero.hp, maxHp: game.hero.maxHp, weaponId: game.hero.weaponId, weapon2Id: game.hero.weapon2Id, position: game.hero.root.position.toArray() },
    npc: [...game.enemies].sort((a, b) => a.scriptId - b.scriptId).map(actor => ({ scriptId: actor.scriptId, name: actor.name, modelId: actor.modelId, weaponId: actor.weaponId, weapon2Id: actor.weapon2Id,
      hp: actor.hp, spawn: actor.scriptConfig.Spawn, position: actor.root.position.toArray(), intent: actor.scriptIntent?.mode, patrol: actor.scriptIntent?.waypointIds })),
    globals: host.levelVm.snapshot(), diagnostics: host.diagnostics.map(e => ({ code: e.code, api: e.api, callback: e.callback, text: e.text })) };
}
const initial = snapshot();
assert.equal(game.hero.maxHp, 1000); assert.equal(game.hero.weaponId, 6); assert.equal(game.hero.weapon2Id, 0);
assert.deepEqual(initial.npc.map(a => [a.name, a.modelId, a.weaponId, a.spawn, a.hp]), [['大刀哨兵', 2, 8, 0, 1000], ['铁枪哨兵', 8, 7, 33, 1000]]);
const floorChecks = [game.hero, ...game.enemies].map(actor => { const p = actor.root.position, floor = game._ground(p.x, p.z, p.y + .1); return { name: actor.name, floor: !!floor, offset: floor ? p.y - floor.point.y : null }; });
assert.ok(floorChecks.every(record => record.floor && Math.abs(record.offset - .015) < 1e-4));
for (let i = 0; i < 300; i++) { game.elapsed += 1 / 60; host.update(1 / 60); game.currentMap.props.update(1 / 60); }
const startup = snapshot();
const routes = game.enemies.map(actor => ({ from: 34, to: actor.scriptConfig.Spawn, route: host.route(34, actor.scriptConfig.Spawn) }));
const walkedRoute = [], walkPath = [...host.route(34, 0), ...host.route(0, 33).slice(1)];
for (const id of walkPath) {
  const goal = host.points.get(id).navigationPosition; let frame = 0;
  while (frame++ < 1200 && (Math.hypot(goal.x - game.hero.root.position.x, goal.z - game.hero.root.position.z) > .65 || Math.abs(goal.y - game.hero.root.position.y) > .7)) {
    const delta = goal.clone().sub(game.hero.root.position); game.cameraAngle = Math.atan2(-delta.x, -delta.z); game.keys.add('forward');
    game._updateFighter(game.hero, 1 / 60);
  }
  const remaining = game.hero.root.position.distanceTo(goal), reached = remaining < 1;
  walkedRoute.push({ waypoint: id, frames: frame, reached, remaining, actorPosition: game.hero.root.position.toArray(), goal: goal.toArray() });
  if (!reached) break;
}
game.keys.clear(); game._placeFighter(game.hero, host.points.get(34));
// Trigger the genuine loss-of-friend branch using isolated normal melee damage;
// NPC physical retaliation is frozen and the player is placed at source spawns.
// This is lifecycle acceptance, not a full live-AI victory from the player spawn.
const killed = [];
for (const victim of game.enemies) {
  let attacks = 0;
  while (!victim.dead && attacks++ < 100) {
    const p = victim.root.position;
    game._placeFighter(game.hero, { position: p.clone().add(v(0, 0, -1.1)) });
    game.locked = victim; game.action('attack');
    for (let frame = 0; frame < 100 && !victim.dead; frame++) {
      game.elapsed += 1 / 60; game._updateFighter(game.hero, 1 / 60); host.update(1 / 60); game.currentMap.props.update(1 / 60);
    }
  }
  assert.equal(victim.dead, true, `real sword contact must kill ${victim.name}`);
  killed.push({ name: victim.name, attacks, hp: victim.hp });
}
for (let frame = 0; frame < 180 && game.running; frame++) host.update(1 / 60);
assert.equal(game.totalDamage, 2000); assert.equal(game.kills, 2); assert.equal(endings.length, 1); assert.equal(endings[0].win, true);
const result = {
  date: '2026-10-26', mapId: 'sn14', mapName: '炎硫岛', readyForNamedMission: true,
  campaignOrder: { established: false, localMenu: 'menu.res lists map IDs/names only', save: 'singlerec.ini contains ten level14 entries and is not authoritative campaign-order evidence', note: 'Do not label this second campaign mission without independent order evidence.' },
  sn02: { mapName: '秦皇陵', rule: 5, npcScripts: 0, callbacks: 0, note: 'Not an original second-story mission; level config only.' },
  initial, startup, floorChecks, routes, walkedRoute, killed, totalDamage: game.totalDamage, kills: game.kills,
  result: host.completed, deathLines: events.filter(e => e.type === 'dialogue' && /两三下|报.*仇|偿命|死定了/.test(e.text)).map(e => ({ speaker: e.speaker, text: e.text })),
  diagnostics: host.diagnostics, missingPerform: events.filter(e => e.type === 'mission-diagnostic' && e.code === 'UNSUPPORTED_PERFORM'),
  limits: ['NPC retaliation frozen during kill acceptance; player placed at source NPC positions', 'Rule10 win remains host inference, no explicit GameOver in source sn14_.pst', 'No full manual/live-AI win or exact native AI/physics asserted', 'NPC Perform attack is an explicit browser single-attack intent; exact EXE Perform timing is not recovered']
};
console.log(JSON.stringify(result, null, 2));
game.projectiles.dispose(); host.dispose(); for (const actor of [game.hero, ...game.enemies]) actor.character.dispose(); game._disposeMap(game.currentMap);

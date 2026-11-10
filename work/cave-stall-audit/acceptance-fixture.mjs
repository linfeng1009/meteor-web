// Isolated audit fixture: same source setup, intentionally mirrors acceptance cave()
// which omits the optional sceneDamageResolver. Actor damage remains original.
import { readFile } from 'node:fs/promises';
import * as THREE from '../../dist/vendor/three.module.js';
import { MeteorGame } from '../../dist/engine.js';
import { loadNativeCombat, createNativeDamageResolver, createNativeSceneDamageResolver } from '../../dist/native-combat.js';

const dist = new URL('../../dist/', import.meta.url), original = new URL('assets/original/', dist);
export const v = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
export function nativeFiles() {
  const previousFetch = globalThis.fetch, previousLoad = THREE.TextureLoader.prototype.load, previousRandom = Math.random;
  // Fixed browser PRNG/cooldown jitter; not a claim about the original PRNG.
  Math.random = () => .5;
  globalThis.fetch = async input => {
    try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); }
    catch { return new Response('', { status: 404 }); }
  };
  THREE.TextureLoader.prototype.load = function (url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
  return () => { globalThis.fetch = previousFetch; THREE.TextureLoader.prototype.load = previousLoad; Math.random = previousRandom; };
}
let data;
export async function nativeMission(mapId) {
  data ||= Promise.all([readFile(new URL('manifest.json', original), 'utf8').then(JSON.parse),
    readFile(new URL('weapon-models/manifest.json', original), 'utf8').then(JSON.parse), loadNativeCombat()]);
  const [manifest, weapons, combat] = await data, game = Object.create(MeteorGame.prototype), events = [], endings = [];
  Object.assign(game, {
    manifest, combatData: combat, weaponManifest: weapons,
    weaponItems: new Map(weapons.items.map(item => [Number(item.itemId), item])),
    weaponModels: new Map(weapons.models.map(model => [model.modelId.toLowerCase(), model])),
    weaponCache: new Map(), effectDefinitions: new Map(), waveFiles: new Map(), effects: [],
    scene: new THREE.Scene(), camera: new THREE.PerspectiveCamera(), cameraTarget: v(),
    raycaster: new THREE.Raycaster(), collisionMaterial: new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }),
    hostPhysics: { speed: 8, gravity: 34, jumpVelocity: 12, radius: .4, step: .55 },
    map: mapId, mode: 'training', weapon: 'sword', characterId: 0, characterAppearance: 'original', appearanceRequest: 0,
    actorSerial: 0, enemies: [], keys: new Set(), directionBuffer: [], sessionRequest: 0, characterRequest: 0, mapRequest: 0,
    running: false, paused: false, elapsed: 0, difficulty: 'normal', kills: 0, deaths: 0, totalDamage: 0, contactHits: 0,
    matchElapsed: 0, time: 0, cameraAngle: 0, cameraPitch: .4, cameraDistance: 8,
    onUpdate() {}, onEvent: event => events.push(event), onEnd: result => endings.push(result),
    _nameplate() {}, _unlockAudio() {}, _soundDefinition() {}
  });
  game._initializeProjectiles(); game.damageResolver = createNativeDamageResolver(combat); 
  game.currentMap = await game._readMap(mapId); game.scene.add(game.currentMap.model);
  game.hero = await game._createFighter(0, '孟星魂', true); game.scene.add(game.hero.root); game.ready = Promise.resolve();
  await game.start({ map: mapId, mode: 'story' });
  return { game, host: game.missionHost, events, endings, dispose() {
    game.projectiles.dispose(); game.missionHost?.dispose();
    for (const actor of [game.hero, ...game.enemies]) actor.character.dispose();
    game._disposeMap(game.currentMap); game.collisionMaterial.dispose();
  } };
}
export function tick(game, dt = 1 / 60, { player = true, enemies = true, separation = true } = {}) {
  if (!game.running || game.paused) return;
  game.elapsed += dt; game.matchElapsed += dt; game.missionHost.update(dt); game.currentMap.props.update(dt);
  if (!game.running) return;
  if (player) game._updateFighter(game.hero, dt);
  if (enemies) for (const actor of game.enemies) { if (!game.running) break; game._updateFighter(actor, dt); }
  if (player && enemies && separation) game._separateCharacters(dt);
  if (game.running) game.projectiles.update(dt);
}
export function attackWhenReady(game) {
  const combat = game.hero.combat, timeline = combat.timeline;
  const lastStrike = Math.max(...(timeline?.pose.attacks.map(attack => attack.end) || []));
  if (!combat.busy || combat.queued == null && timeline.canCancel && timeline.frame > lastStrike) game.action('attack');
}

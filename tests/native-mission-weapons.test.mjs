import test, { after } from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { loadNativeCombat, createNativeDamageResolver, NATIVE_WEAPONS } from '../dist/native-combat.js';

// Real source models, skeletons, AMB, POS/ACT and RES arithmetic. The plain
// floor isolates mission-required weapon behavior from map navigation; image
// decoding, rendering/audio and NPC retaliation are deliberately absent.
const dist = new URL('../dist/', import.meta.url), v = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
const previousFetch = globalThis.fetch, previousLoad = THREE.TextureLoader.prototype.load;
globalThis.fetch = async input => { try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); } catch { return new Response('', { status: 404 }); } };
THREE.TextureLoader.prototype.load = function (url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
const combat = await loadNativeCombat(), weapons = JSON.parse(await readFile(new URL('assets/original/weapon-models/manifest.json', dist), 'utf8'));
const games = [];
after(() => {
  for (const game of games) {
    game.projectiles?.dispose(); for (const actor of [game.hero, ...game.enemies]) actor.character.dispose();
    for (const promise of game.weaponCache.values()) promise.then(model => model.traverse(node => { node.geometry?.dispose(); for (const material of Array.isArray(node.material) ? node.material : [node.material]) material?.dispose(); }));
    for (const mesh of game.currentMap.colliders) { mesh.geometry.dispose(); mesh.material.dispose(); }
  }
  globalThis.fetch = previousFetch; THREE.TextureLoader.prototype.load = previousLoad;
});
async function fixture(itemId = 13, distance = 1.1) {
  const game = Object.create(MeteorGame.prototype), events = [], sounds = [];
  const floor = new THREE.Mesh(new THREE.PlaneGeometry(200, 200), new THREE.MeshBasicMaterial({ side: THREE.DoubleSide })); floor.rotation.x = -Math.PI / 2; floor.updateMatrixWorld(true);
  Object.assign(game, { combatData: combat, weaponManifest: weapons,
    weaponItems: new Map(weapons.items.map(item => [Number(item.itemId), item])), weaponModels: new Map(weapons.models.map(model => [model.modelId.toLowerCase(), model])), weaponCache: new Map(),
    scene: new THREE.Scene(), camera: new THREE.PerspectiveCamera(), raycaster: new THREE.Raycaster(), hostPhysics: { speed: 8, gravity: 34, jumpVelocity: 12, radius: .4, step: .55 },
    currentMap: { colliders: [floor], bounds: new THREE.Box3(v(-100, -1, -100), v(100, 30, 100)), metadata: {}, spawns: [{ position: v(0, .015, 0) }] },
    weapon: 'sword', actorSerial: 0, enemies: [], keys: new Set(), directionBuffer: [], cameraAngle: 0, running: true, paused: false, mode: 'training', elapsed: 0, matchElapsed: 0,
    kills: 0, deaths: 0, totalDamage: 0, contactHits: 0, onEvent: event => events.push(event), onUpdate() {}, _nameplate() {}, _unlockAudio() {}, _soundDefinition: name => sounds.push(name), _hud() {},
    _emit(text, type, amount, point, extra) { events.push({ text, type, amount, ...extra }); }
  });
  game.damageResolver = createNativeDamageResolver(combat); game._initializeProjectiles();
  game.hero = await game._createFighter(0, '孟星魂', true); game.scene.add(game.hero.root); game._placeFighter(game.hero, { position: v(0, .015, 0) }); await game._equip(game.hero, itemId);
  const target = await game._createFighter(8, '原版对练角色'); game.scene.add(target.root); game.enemies.push(target); game._placeFighter(target, { position: v(0, .015, distance) }); await game._equip(target, 'spear');
  target.maxHp = target.hp = 10000; target.team = target.teamMask = 2; game.hero.team = game.hero.teamMask = 1; game.locked = target;
  games.push(game); return { game, hero: game.hero, target, events, sounds };
}
function tick(game, dt = 1 / 60) { game.elapsed += dt; game.matchElapsed += dt; game._updateFighter(game.hero, dt); game.projectiles.update(dt); }

test('source items retain their actual models, handedness and original stance', async () => {
  for (const [item, family, modelNames] of [[13, 'dual', ['w8_1r', 'w8_1l']], [18, 'hammer', ['w4_1']], [36, 'hammer', ['w4_3']],
    [51, 'knuckle', ['w10_0r', 'w10_0l']], [52, 'knuckle', ['w10_1r', 'w10_1l']], [53, 'knuckle', ['w10_2r', 'w10_2l']], [54, 'knuckle', ['w10_3r', 'w10_3l']]]) {
    const { game, hero } = await fixture(item);
    assert.equal(hero.weaponId, item); assert.equal(hero.weapon, family);
    assert.deepEqual(hero.weaponModels.map(model => model.name), modelNames);
    assert.equal(hero.combat.timeline.pose.id, NATIVE_WEAPONS[family].stance);
    for (const model of hero.weaponModels) assert.equal(model.parent, hero.character.getAttachment(model.name.endsWith('l') ? 'd_wpnL' : 'd_wpnR'));
    assert.equal(hero.weaponRecord.model.toLowerCase(), modelNames[0]);
    assert.ok(hero.weaponModels.every(model => model.getObjectByProperty('isMesh', true)));
    game.action('guard'); tick(game); assert.equal(hero.combat.timeline.pose.id, NATIVE_WEAPONS[family].guard);
    assert.equal(hero.character.frame >= combat.poses.get(NATIVE_WEAPONS[family].guard).start, true);
    game.action('guard', false); tick(game); assert.equal(hero.combat.timeline.pose.id, NATIVE_WEAPONS[family].stance);
  }
});

for (const [item, family, poses, damages] of [[13, 'dual', [230, 231, 232], [31, 42, 52]], [18, 'hammer', [315], [88]], [51, 'knuckle', [407, 408, 409], [33, 38, 46]]]) {
  test(`${family} ordinary attack inputs traverse actual native bones and each source window once`, async () => {
    const { game, hero, target, events } = await fixture(item);
    for (let index = 0; index < poses.length; index++) {
      game.action('attack');
      for (let frame = 0; frame < 240 && game.contactHits <= index; frame++) tick(game);
      assert.equal(game.contactHits, index + 1, `${family} pose${poses[index]} did not contact through native geometry`);
      assert.equal(hero.combat.timeline.pose.id, poses[index]);
    }
    const hits = events.filter(event => event.type === 'hit');
    assert.deepEqual(hits.map(event => event.poseId), poses); assert.deepEqual(hits.map(event => event.amount), damages);
    assert.equal(target.hp, 10000 - damages.reduce((a, b) => a + b, 0)); assert.equal(game.projectiles.size, 0, 'source melee cannot invent a ranged projectile');
    for (let frame = 0; frame < 240; frame++) tick(game);
    assert.equal(game.contactHits, poses.length, 'repeated source-frame samples do not repeat one attack window');
    assert.equal(hero.combat.timeline.pose.id, NATIVE_WEAPONS[family].stance);
  });
}

for (const [item, family, prefix] of [[13, 'dual', 'W08'], [18, 'hammer', 'W04'], [51, 'knuckle', 'W10']]) {
  test(`${family} actual blocked first strike preserves HP and selects its source guard sound family`, async () => {
    const { game, target, events, sounds } = await fixture(item); target.guard = true;
    game.action('attack'); for (let frame = 0; frame < 240 && game.contactHits < 1; frame++) tick(game);
    assert.equal(game.contactHits, 1); assert.equal(target.hp, 10000); assert.equal(game.totalDamage, 0);
    assert.equal(events.find(event => event.type === 'hit').guarded, true); assert.equal(target.combat.reactionPhase, 'guard');
    const sound = sounds.find(name => name?.startsWith(`${prefix}GD`)); assert.ok(sound);
    const ef = await readFile(new URL(`assets/original/sounds/definitions/${sound.toLowerCase()}.ef`, dist));
    assert.ok(ef.includes(Buffer.from(`${prefix}GRD01.wav`)), 'sound family must resolve through the actual original EF');
  });
}

test('mission weapon profiles keep plain-A separate from the authored directional branches', () => {
  assert.deepEqual(NATIVE_WEAPONS.dual.basic, [230, 231, 232]); assert.deepEqual(NATIVE_WEAPONS.dual.air, [226, 227]);
  assert.deepEqual(NATIVE_WEAPONS.hammer.basic, [315]); assert.deepEqual(NATIVE_WEAPONS.hammer.air, [338]);
  for (const family of ['dual', 'hammer']) {
    const profile = NATIVE_WEAPONS[family]; assert.ok(combat.poses.get(profile.guard).valid);
    for (const id of profile.air) { const pose = combat.poses.get(id); assert.ok(pose.valid && pose.attacks.length); assert.ok(pose.label.includes('空')); }
    for (let i = 1; i < profile.basic.length; i++) assert.equal(combat.actions.canLink(profile.basic[i - 1], profile.basic[i]), true);
  }
});

test('ordinary jump and attack inputs render the original dual, hammer and knuckle air poses and return to their source stances', async () => {
  for (const [item, family, first] of [[13, 'dual', 226], [18, 'hammer', 338], [51, 'knuckle', 405]]) {
    const { game, hero } = await fixture(item);
    game.action('jump'); game.action('attack'); assert.equal(hero.combat.timeline.pose.id, first);
    let displayed = false;
    for (let frame = 0; frame < 360; frame++) {
      tick(game);
      if (hero.combat.timeline.pose.id === first) {
        const pose = combat.poses.get(first); displayed ||= hero.character.source === pose.source && hero.character.frame >= pose.start && hero.character.frame <= pose.end;
      }
    }
    assert.ok(displayed, `${family}: actual source air animation must reach the character`);
    assert.equal(hero.grounded, true); assert.equal(hero.combat.timeline.pose.id, NATIVE_WEAPONS[family].stance);
    assert.equal(game.projectiles.size, 0);
  }
});

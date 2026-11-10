import test, { after } from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { loadNativeCombat, NativeCombatController, NativePoseTimeline, createNativeDamageResolver, nativeReactionParameters, nativeHitAngle, nativeHitSelection, nativeGuardPose, NATIVE_GUARD_REACTIONS, NATIVE_DEFAULT_BLEND_TIME } from '../dist/native-combat.js';
import { NativeImpactFeedback } from '../dist/native-impact-feedback.js';

// Real POS, RES, SKC/BNC/AMB and native weapons on a plain CPU test floor.
// Textures, browser rendering/audio and NPC retaliation are intentionally absent;
// these tests prove the hit/reaction chain, not original AI or manual victory.
const dist = new URL('../dist/', import.meta.url), v = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
const priorFetch = globalThis.fetch, priorTextureLoad = THREE.TextureLoader.prototype.load;
globalThis.fetch = async input => { try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); } catch { return new Response('', { status: 404 }); } };
THREE.TextureLoader.prototype.load = function(url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
const data = await loadNativeCombat(), weapons = JSON.parse(await readFile(new URL('assets/original/weapon-models/manifest.json', dist), 'utf8'));
const fixtures = [];

test('native Move/Value packing preserves their separate motion/time meanings and original float32 wire rounding', () => {
  assert.deepEqual(nativeReactionParameters(data.poses.get(315).attacks[0]), { motionScale: 10, duration: .5 });
  assert.deepEqual(nativeReactionParameters(data.poses.get(262).attacks[0]), { motionScale: 5, duration: 0.09999999403953552 });
  assert.deepEqual(nativeReactionParameters(data.poses.get(297).attacks[0], { guarded: true }), { motionScale: 8, duration: 0.5999999642372131 });
});

test('one-frame airborne source loops hold exactly one transform and cannot sample another pose or generate endless vertical velocity', () => {
  const pose = data.poses.get(339), sampled = [];
  const timeline = new NativePoseTimeline(pose, { loop: true, sampleRoot: (_source, frame) => { sampled.push(frame); return { x: 0, y: 0, z: frame }; } });
  for (let frame = 0; frame < 180; frame++) {
    const state = timeline.advance(1 / 60); assert.equal(state.frame, pose.loopStart); assert.equal(state.rootDelta.z, 0); assert.equal(state.finished, false);
  }
  assert.ok(sampled.every(frame => frame === pose.loopStart));
});

test('source reaction selection uses native signed angles, exact sector boundaries and append-time fallback', () => {
  const attack = data.poses.get(262).attacks[0];
  for (const [position, direction, poseId] of [[v(0, 0, 2), 0, 93], [v(2, 0, 0), 2, 94], [v(-2, 0, 0), 1, 91], [v(0, 0, -2), 3, 92]]) {
    const result = nativeHitSelection(attack, nativeHitAngle(position, v()));
    assert.equal(result.direction, direction); assert.equal(result.poseId, poseId);
    const rotated = v(position.z, 0, -position.x);
    assert.equal(nativeHitSelection(attack, nativeHitAngle(rotated, v(), Math.PI / 2)).poseId, poseId, 'rotate actor and attacker together');
  }
  for (const [angle, direction] of [[.7853975 - 1e-9, 0], [.7853975, 2], [-.7853975 + 1e-9, 0], [-.7853975, 1], [2.3561924999999997, 3], [-2.3561924999999997, 3]]) {
    assert.equal(nativeHitSelection(attack, angle).direction, direction);
  }
  assert.equal(nativeHitSelection({ targetpose: 103, targetposeleft: -1 }, Math.PI / 2).poseId, 103);
  assert.equal(nativeHitSelection(attack, nativeHitAngle(v(), v())).direction, 0);
});

test('source guard selection retains each weapon-state list, all four front variants and its fixed side/back entries', () => {
  const expected = { dart: [40, 41, 42, 43, 77, 78, 79], dual: [52, 53, 54, 55, 77, 78, 79], dagger: [56, 57, 58, 59, 83, 84, 85],
    sword: [60, 61, 62, 63, 80, 81, 82], spear: [64, 65, 66, 67, 86, 87, 88], blade: [68, 69, 70, 71, 80, 81, 82], hammer: [72, 73, 74, 75, 77, 78, 79] };
  for (const [weapon, poses] of Object.entries(expected)) {
    assert.deepEqual(NATIVE_GUARD_REACTIONS[weapon], poses);
    for (let n = 0; n < 4; n++) assert.equal(nativeGuardPose(weapon, 0, () => n / 4), poses[n]);
    for (let direction = 1; direction < 4; direction++) assert.equal(nativeGuardPose(weapon, direction), poses[direction + 3]);
    assert.ok(poses.every(id => data.poses.get(id)?.valid && Number.isFinite(data.poses.get(id).loopStart)));
  }
});

test('front guard follows the original CRT53-bit draw distribution, including the maximum draw selecting slot4', () => {
  const counts = new Map();
  for (let draw = 0; draw <= 32767; draw++) {
    const pose = nativeGuardPose('sword', 0, () => draw / 32768);
    counts.set(pose, (counts.get(pose) || 0) + 1);
  }
  assert.deepEqual([...counts], [[60, 8192], [61, 8192], [62, 8192], [63, 8191], [80, 1]]);
  assert.equal(nativeGuardPose('sword', 0, () => 32767 / 32768), 80);
});
after(() => {
  for (const { game, floor } of fixtures) {
    game.projectiles?.dispose(); game.impactFeedback?.dispose(); for (const actor of [game.hero, ...game.enemies]) actor.character.dispose();
    for (const promise of game.weaponCache.values()) promise.then(model => model.traverse(node => {
      node.geometry?.dispose(); for (const material of Array.isArray(node.material) ? node.material : [node.material]) material?.dispose();
    }));
    floor.geometry.dispose(); floor.material.dispose();
  }
  globalThis.fetch = priorFetch; THREE.TextureLoader.prototype.load = priorTextureLoad;
});

async function fixture() {
  const game = Object.create(MeteorGame.prototype), events = [], sounds = [];
  const floor = new THREE.Mesh(new THREE.PlaneGeometry(200, 200), new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }));
  floor.rotation.x = -Math.PI / 2; floor.updateMatrixWorld(true);
  Object.assign(game, { combatData: data, weaponManifest: weapons,
    weaponItems: new Map(weapons.items.map(item => [Number(item.itemId), item])),
    weaponModels: new Map(weapons.models.map(model => [model.modelId.toLowerCase(), model])), weaponCache: new Map(),
    effectDefinitions: new Map(), waveFiles: new Map(), effects: [], scene: new THREE.Scene(), camera: new THREE.PerspectiveCamera(), raycaster: new THREE.Raycaster(),
    hostPhysics: { speed: 8, gravity: 34, jumpVelocity: 12, radius: .4, step: .55 },
    currentMap: { colliders: [floor], bounds: new THREE.Box3(v(-100, -1, -100), v(100, 30, 100)), metadata: {}, spawns: [{ position: v(0, .015, 0) }] },
    weapon: 'sword', actorSerial: 0, enemies: [], keys: new Set(), directionBuffer: [], cameraAngle: 0,
    running: true, paused: false, mode: 'training', elapsed: 0, matchElapsed: 0, kills: 0, deaths: 0, totalDamage: 0, contactHits: 0,
    onEvent: event => events.push(event), onUpdate() {}, _emit(text, type, amount, point, extra) { events.push({ text, type, amount, ...extra }); },
    _nameplate() {}, _unlockAudio() {}, _soundDefinition: name => sounds.push(name), _hud() {} });
  game.damageResolver = createNativeDamageResolver(data); game._initializeProjectiles();
  game.hero = await game._createFighter(0, '孟星魂', true); game.scene.add(game.hero.root);
  game._placeFighter(game.hero, { position: v(0, .015, 0) }); await game._equip(game.hero, 'sword');
  const target = await game._createFighter(8, '原版对练角色'); game.scene.add(target.root); game.enemies.push(target);
  game._placeFighter(target, { position: v(0, .015, 1.1) }); await game._equip(target, 'spear');
  target.maxHp = target.hp = 10000; target.team = target.teamMask = 2; game.hero.team = game.hero.teamMask = 1;
  target.scriptControlled = true; target.scriptControl = { paused: true }; game.locked = target;
  const result = { game, hero: game.hero, target, floor, events, sounds }; fixtures.push(result); return result;
}
function hit(game, attacker, target, poseId, attack = data.poses.get(poseId).attacks[0]) {
  return game._applyNativeHit(attacker, target, { poseId, pose: data.poses.get(poseId) }, attack, target.root.position.clone().add(v(0, 1.35, 0)));
}
function tick(game, dt = 1 / 60) {
  game.elapsed += dt; game.matchElapsed += dt;
  game._updateFighter(game.hero, dt); for (const actor of game.enemies) game._updateFighter(actor, dt);
  game.projectiles.update(dt);
}

test('real hit events, original animation and impact sound all use the selected front/back/side source pose', async () => {
  for (const [offset, expected] of [[v(0, 0, 1.1), 93], [v(1.1, 0, 0), 94], [v(-1.1, 0, 0), 91], [v(0, 0, -1.1), 92]]) {
    const { game, hero, target, events, sounds } = await fixture();
    game._placeFighter(hero, { position: target.root.position.clone().add(offset) });
    hit(game, hero, target, 262);
    assert.equal(target.combat.timeline.pose.id, expected);
    assert.equal(events.find(event => event.type === 'hit').raw.selectedTargetPose, expected);
    assert.ok(sounds.includes(`W00BL${String(expected).padStart(3, '0')}`)); assert.ok(target.hp < target.maxHp);
    game._updateFighter(target, .2);
    const source = target.character.combatPoses.get(expected);
    assert.equal(target.character.source, source.source);
    assert.ok(target.character.frame >= source.start && target.character.frame <= source.end);
  }
});

test('an interrupted native hit blend starts from the actual displayed bones and weapon attachments without a pose pop', async () => {
  const { game, hero, target } = await fixture(); game._updateFighter(target, 1 / 60);
  const positions = () => ['bau_Head', 'bau_R_Hand', 'd_wpnR'].map(name => target.character.getAttachment(name).getWorldPosition(v()));
  const before = positions(); hit(game, hero, target, 262);
  assert.ok(positions().every((point, i) => point.distanceTo(before[i]) < 1e-6), 'contact starts at weight zero');
  assert.equal(target.combat.poseBlend.duration, NATIVE_DEFAULT_BLEND_TIME);
  game._updateFighter(target, .045);
  const partial = positions(), firstSnapshot = target.combat.poseBlend.from.snapshot.id;
  assert.ok(partial.some((point, i) => point.distanceTo(before[i]) > .001), 'native skeleton visibly enters the hit pose');
  hit(game, hero, target, 263);
  assert.ok(target.combat.poseBlend.from.snapshot.id > firstSnapshot);
  assert.ok(positions().every((point, i) => point.distanceTo(partial[i]) < 1e-6), 'second contact preserves the interrupted displayed blend');
  assert.equal(target.combat.poseBlend.weight, 0);
  game._updateFighter(target, .03);
  assert.ok(Math.abs(target.combat.poseBlend.weight - .03 / NATIVE_DEFAULT_BLEND_TIME) < 1e-6);
  assert.equal(target.combat.timeline.frame, target.combat.timeline.pose.start, 'blend does not skip hit animation time');
});

test('a blocked rear blow plays the defender sword guard pose, moves by native DefenseMove, holds DefenseValue and returns to guard', async () => {
  const { game, hero, target } = await fixture(); await game._equip(hero, 'blade'); await game._equip(target, 'sword');
  target.scriptControl.guard = true; target.guard = true;
  const start = target.root.position.clone(); hit(game, hero, target, 297);
  assert.equal(target.hp, 10000); assert.equal(game.totalDamage, 0);
  assert.equal(target.combat.timeline.pose.id, 82); assert.equal(target.combat.reactionPhase, 'guard');
  assert.equal(target.combat.poseBlend.duration, Math.fround(.01));
  const pose = target.combat.timeline.pose, a = target.character.sampleSceneMotion(pose.source, pose.start), b = target.character.sampleSceneMotion(pose.source, pose.end);
  let elapsed = 0;
  while (target.combat.reacting && elapsed < 2) { game._updateFighter(target, 1 / 60); elapsed += 1 / 60; assert.equal(target.guard, true); }
  assert.ok(elapsed >= .61 && elapsed < .7, `native .01 blend followed by .6 hold: ${elapsed}`);
  assert.ok(Math.abs(target.root.position.x - start.x - (b.x - a.x) * .08 * 8) < 1e-5);
  assert.ok(Math.abs(target.root.position.z - start.z + (b.y - a.y) * .08 * 8) < 1e-5);
  assert.ok(target.root.position.distanceTo(start) > .1, 'authored block recoil must move the collision root');
  game._updateFighter(target, 1 / 60);
  assert.equal(target.combat.timeline.pose.id, 16); assert.equal(target.guard, true);
});

test('public held guard can be released and pressed during block stun, repeated blocks preserve HP and a source break-guard hit interrupts it', async () => {
  const { game, hero, target } = await fixture();
  game.action('guard'); hit(game, target, hero, 262);
  assert.equal(hero.combat.reactionPhase, 'guard'); assert.equal(hero.guard, true);
  game.action('guard', false); assert.equal(hero.guard, false);
  game.action('guard'); assert.equal(hero.guard, true);
  game.action('attack'); game.action('jump'); assert.equal(hero.combat.queuedMove, null); assert.equal(hero.grounded, true);
  const hp = hero.hp; game._updateFighter(hero, .06); hit(game, target, hero, 262);
  assert.equal(hero.hp, hp); assert.equal(hero.combat.reactionPhase, 'guard');
  hit(game, target, hero, 298);
  assert.ok(hero.hp < hp); assert.equal(hero.guard, false); assert.equal(hero.combat.reactionPhase, 'hit');
});

test('a native light-hit reaction discards queued offense and cannot be canceled by normal attack or locomotion input', () => {
  const combat = new NativeCombatController(data, { weapon: 'sword' }); let paid = 0;
  combat.attack({ poseId: 262 }); combat.attack({ poseId: 263, onStart: () => paid++ });
  assert.equal(combat.queued, 263); assert.equal(combat.react(93), true);
  assert.equal(combat.timeline.pose.id, 93); assert.equal(combat.reacting, true); assert.equal(combat.busy, true);
  assert.equal(combat.currentMove, null); assert.equal(combat.queuedMove, null);
  for (let frame = 0; frame < 8; frame++) {
    assert.equal(combat.attack(), false); assert.equal(combat.play(140), false);
    combat.update(1 / 60, { grounded: true }); assert.equal(combat.timeline.pose.id, 93);
  }
  combat.update(1, { grounded: true });
  assert.equal(combat.reacting, false); assert.equal(combat.busy, false); assert.equal(paid, 0);
  assert.equal(combat.attack(), true); assert.equal(combat.timeline.pose.id, 262);
});

test('native knockdowns keep their POS down links and recover through original animation rather than instantly standing', () => {
  for (const [id, down, recover] of [[95, 113, 120], [98, 112, 119], [103, 112, 119]]) {
    const combat = new NativeCombatController(data, { weapon: 'sword' }), seen = new Set(); let downFrames = 0;
    assert.equal(combat.react(id), true);
    for (let frame = 0; frame < 300 && combat.reacting; frame++) {
      for (const state of combat.update(1 / 60, { grounded: true }).segments) seen.add(state.poseId);
      if (combat.reactionPhase === 'down') { downFrames++; assert.equal(combat.attack(), false); }
    }
    assert.ok(seen.has(id) && seen.has(down) && seen.has(recover), `${id}: missing native chain ${[...seen]}`);
    assert.ok(downFrames > 1, `${id}: authored prone frame needs a visible hold`);
    assert.equal(combat.reacting, false); assert.equal(combat.busy, false);
  }
});

test('airborne prone reactions wait for floor contact and repeated light hits do not snap a prone actor upright', () => {
  const combat = new NativeCombatController(data); combat.react(98);
  for (let frame = 0; frame < 180; frame++) combat.update(1 / 60, { grounded: false });
  assert.equal(combat.timeline.pose.id, 112); assert.equal(combat.reactionPhase, 'down');
  assert.equal(combat.react(90), false); assert.equal(combat.timeline.pose.id, 112);
  for (let frame = 0; frame < 180 && combat.reacting; frame++) combat.update(1 / 60, { grounded: true });
  assert.equal(combat.reacting, false); assert.equal(combat.timeline.pose.id, 119);
});

test('a real native sword hit visibly plays its authored target pose and locks ordinary AI movement and offense', async () => {
  const { game, hero, target } = await fixture(), beforeFacing = target.root.rotation.y;
  target.scriptControl = { paused: false, canAttack: true, attackTarget: hero, moveTarget: hero.root.position, attackRequested: true };
  target.aiTimer = 0;
  assert.equal(hit(game, hero, target, 262), true); assert.equal(target.hp, 10000 - game.totalDamage);
  assert.equal(target.combat.timeline.pose.id, 92, 'rear sword262 hit selects original TargetPoseBack'); assert.equal(target.combat.reacting, true);
  game._updateFighter(target, 1 / 60);
  assert.equal(target.combat.timeline.pose.id, 92, 'AI must not replace the hit animation with an attack or run');
  const pose = data.poses.get(92);
  assert.equal(target.character.source, pose.source); assert.ok(target.character.frame >= pose.start && target.character.frame <= pose.end);
  assert.equal(target.velocity.lengthSq(), 0, 'ordinary chase velocity must stop; source animation recoil may still move the actor');
  assert.equal(target.root.rotation.y, beforeFacing, 'AI must not turn toward its chase target during the hit animation');
  assert.ok(target.character.getAttachment('bau_Spine1'), 'the displayed frame uses the actual native skeleton');
});

test('three ordinary public attack inputs can hit and knock down a real native opponent on the source sword third strike', async () => {
  const { game, hero, target, events } = await fixture();
  game.action('attack');
  for (let frame = 0; frame < 180 && game.contactHits < 1; frame++) tick(game);
  assert.equal(game.contactHits, 1); game.action('attack');
  for (let frame = 0; frame < 180 && game.contactHits < 2; frame++) tick(game);
  assert.equal(game.contactHits, 2); assert.equal(hero.combat.timeline.pose.id, 263); game.action('attack');
  for (let frame = 0; frame < 240 && game.contactHits < 3; frame++) tick(game);
  const hits = events.filter(event => event.type === 'hit');
  assert.deepEqual(hits.map(event => event.poseId), [262, 263, 264]);
  assert.equal(hits[2].knockdown, true); assert.equal(target.combat.timeline.pose.id, hits[2].raw.selectedTargetPose);
  const down = target.combat.timeline.pose.link; assert.ok([112, 113].includes(down)); const recovery = down === 112 ? 119 : 120;
  assert.equal(target.combat.reacting, true); assert.equal(target.dead, false);
  assert.ok(target.hp > 0 && target.hp < target.maxHp, 'knockdown is not death');
  const seen = new Set(), downHeadHeights = [], recoveryHeadHeights = [];
  for (let frame = 0; frame < 240; frame++) {
    tick(game); const id = target.combat.timeline.pose.id; seen.add(id);
    const headHeight = target.character.getAttachment('bau_Head').getWorldPosition(v()).y - target.root.position.y;
    if (id === down) downHeadHeights.push(headHeight);
    if (id === recovery) recoveryHeadHeights.push(headHeight);
  }
  assert.ok(seen.has(down) && seen.has(recovery)); assert.equal(target.combat.reacting, false); assert.equal(target.combat.timeline.pose.id, 7);
  assert.ok(downHeadHeights.length > 1 && Math.max(...downHeadHeights) < .35, 'native head bone must visibly lie close to the ground during the prone hold');
  assert.ok(Math.max(...recoveryHeadHeights) - Math.min(...recoveryHeadHeights) > .8, 'original recovery frames must raise the body rather than snapping straight to stance');
  assert.ok(target.character.getAttachment('bau_Head').getWorldPosition(v()).y - target.root.position.y > 1.5, 'the actual native skeleton stands again after recovery');
  assert.equal(game.contactHits, 3, 'each source attack window damages once despite many render updates');
});

test('rapid public attack presses retain all three original sword strike windows before the third hit knocks down', async () => {
  const { game, target, events } = await fixture();
  for (let frame = 0; frame < 360 && game.contactHits < 3; frame++) {
    if (frame % 6 === 0) game.action('attack'); // normal J presses every 100 ms
    tick(game);
  }
  const hits = events.filter(event => event.type === 'hit');
  assert.deepEqual(hits.map(event => event.poseId), [262, 263, 264], 'early queued clicks must not discard the first two authored contacts');
  assert.equal(game.contactHits, 3); assert.equal(target.contacts, 3);
  assert.equal(hits[2].knockdown, true); assert.equal(target.combat.timeline.pose.id, hits[2].raw.selectedTargetPose); assert.equal(target.dead, false);
  assert.equal(target.maxHp - target.hp, hits.reduce((total, event) => total + event.amount, 0));
});

test('guarded contact does not turn a blocked blow into knockdown, while a lethal blow keeps death priority', async () => {
  const { game, hero, target } = await fixture();
  target.guard = true; hit(game, hero, target, 264);
  assert.equal(target.hp, 10000); assert.notEqual(target.combat.timeline.pose.id, 98);
  target.guard = false; target.hp = 1; hit(game, hero, target, 264);
  assert.equal(target.hp, 0); assert.equal(target.dead, true); assert.equal(target.combat.timeline.pose.id, 117);
  assert.equal(target.combat.reacting, false);
  assert.equal(hit(game, hero, target, 262), false); assert.equal(target.combat.timeline.pose.id, 117);
  assert.equal(game.kills, 1);
  game._placeFighter(target, { position: v(0, .015, 1.1) });
  assert.equal(target.dead, false); assert.equal(target.combat.reacting, false); assert.equal(target.combat.busy, false);
  assert.equal(target.combat.timeline.pose.id, 7); assert.equal(target.combat.attack(), true);
});

test('native hitstun cannot be cancelled by jumping; held defense engages on recovery without another input event', async () => {
  const { game, hero, target } = await fixture();
  hit(game, target, hero, 264);
  assert.equal(hero.combat.timeline.pose.id, 98);
  game.action('forward'); game.action('attack'); game.action('jump'); game.action('guard');
  game._updateFighter(hero, 1 / 60);
  assert.equal(hero.combat.timeline.pose.id, 98); assert.equal(hero.combat.queuedMove, null); assert.equal(hero.grounded, true);
  assert.equal(hero.velocity.lengthSq(), 0, 'held movement cannot cancel authored recoil'); assert.equal(hero.guard, false);
  game.action('forward', false);
  for (let frame = 0; frame < 240; frame++) { game.elapsed += 1 / 60; game._updateFighter(hero, 1 / 60); }
  assert.equal(hero.combat.reacting, false); assert.equal(hero.combat.timeline.pose.id, 16); assert.equal(hero.guard, true);
  game.action('guard', false); game._updateFighter(hero, 1 / 60); assert.equal(hero.combat.timeline.pose.id, 6);
  game.action('jump'); assert.equal(hero.grounded, false); assert.equal(hero.combat.timeline.pose.id, 151);
});

test('real impact feedback freezes only the contacting actors and consumes only its pause portion of the next update', async () => {
  const { game, hero, target } = await fixture(); game.impactFeedback = new NativeImpactFeedback(game.scene);
  const third = await game._createFighter(8, '无关对练角色'); game.enemies.push(third); game.scene.add(third.root);
  game._placeFighter(third, { position: v(20, .015, 0) }); third.scriptControlled = true; third.scriptControl = { paused: true };
  game.action('attack'); game._updateFighter(hero, .01); game._updateFighter(third, .01);
  hit(game, hero, target, 262);
  const stop = target.hitstop, attackerFrame = hero.combat.timeline.frame, victimFrame = target.combat.timeline.frame, thirdFrame = third.combat.timeline.frame;
  assert.ok(stop > 0 && stop <= .06); assert.equal(hero.hitstop, stop); assert.equal(game.impactFeedback.active.length, 1);
  const victimDisplayed = target.character.frame;
  game._updateFighter(hero, stop / 2); game._updateFighter(target, stop / 2); game._updateFighter(third, stop / 2);
  assert.equal(hero.combat.timeline.frame, attackerFrame); assert.equal(target.combat.timeline.frame, victimFrame);
  assert.equal(target.character.frame, victimDisplayed, 'the original first hit frame remains visible during the contact freeze');
  assert.ok(third.combat.timeline.frame > thirdFrame, 'a nearby unrelated actor must continue animating');
  assert.equal(game.running, true); assert.equal(game.paused, false);
  const remainingPause = target.hitstop;
  game._updateFighter(hero, remainingPause + .01); game._updateFighter(target, remainingPause + .01);
  assert.equal(hero.hitstop, 0); assert.equal(target.hitstop, 0);
  assert.ok(Math.abs(hero.combat.timeline.frame - attackerFrame - .3) < 1e-6);
  assert.equal(target.combat.timeline.frame, victimFrame, 'native hit timeline stays at Start during the .12s blend');
  assert.ok(Math.abs(target.combat.poseBlend.weight - .01 / NATIVE_DEFAULT_BLEND_TIME) < 1e-6, 'only the remaining 10ms advances the blend');
});

test('one defense press during hitstun survives repeated ordinary incoming hits after recovery and release still works', async () => {
  const { game, hero, target } = await fixture();
  hit(game, target, hero, 262); const hp = hero.hp;
  game.action('guard'); assert.equal(hero.guard, false);
  for (let frame=0; frame<120 && hero.combat.reacting; frame++) { game.elapsed += 1/60; game._updateFighter(hero,1/60); }
  assert.equal(hero.guard, true);
  for (let strike=0; strike<6; strike++) {
    hit(game, target, hero, 262);
    for (let frame=0; frame<25; frame++) { game.elapsed += 1/60; game._updateFighter(hero,1/60); }
    assert.equal(hero.hp,hp,'held guard must work without key-repeat after every block reaction');
  }
  game.action('guard',false); assert.equal(hero.guard,false);
  hit(game,target,hero,262); assert.ok(hero.hp<hp,'release restores normal incoming damage');
});

test('a near-recovery attack input starts only after hitstun and expires instead of replaying after a long knockdown', async () => {
  const { game, hero, target } = await fixture();
  hit(game,target,hero,262);
  for(let frame=0;frame<8;frame++){game.elapsed+=1/60;game._updateFighter(hero,1/60);}
  assert.equal(hero.combat.reacting,true); game.action('attack');
  assert.ok(game.recoveryAttack); assert.equal(hero.combat.timeline.pose.id,93);
  for(let frame=0;frame<90 && hero.combat.currentMove?.poseId!==262;frame++){game.elapsed+=1/60;game._updateFighter(hero,1/60);}
  assert.equal(hero.combat.currentMove?.poseId,262); assert.equal(game.recoveryAttack,null);
  hit(game,target,hero,264); game.action('attack');
  for(let frame=0;frame<240;frame++){game.elapsed+=1/60;game._updateFighter(hero,1/60);}
  assert.equal(game.recoveryAttack,null); assert.equal(hero.combat.currentMove,null); assert.equal(hero.combat.busy,false);
});

test('misses produce no contact freeze, guarded impact keeps HP and death interrupts an existing freeze immediately', async () => {
  const { game, hero, target } = await fixture(); game.impactFeedback = new NativeImpactFeedback(game.scene);
  game._placeFighter(target, { position: v(0, .015, 50) }); target.maxHp = target.hp = 10000;
  game.action('attack'); for (let frame = 0; frame < 120; frame++) tick(game);
  assert.equal(game.contactHits, 0); assert.equal(game.impactFeedback.active.length, 0); assert.equal(hero.hitstop || 0, 0); assert.equal(target.hitstop || 0, 0);
  game._placeFighter(target, { position: v(0, .015, 1.1) }); target.maxHp = target.hp = 10000; target.guard = true;
  hit(game, hero, target, 264);
  assert.equal(target.hp, 10000); assert.equal(target.combat.reactionPhase, 'guard'); assert.notEqual(target.combat.timeline.pose.id, 98);
  assert.ok(target.hitstop > 0 && target.hitstop <= .06);
  target.guard = false; target.hp = 1; hit(game, hero, target, 264);
  assert.equal(target.dead, true); assert.equal(target.hp, 0); assert.equal(target.hitstop, 0);
  assert.equal(target.combat.timeline.pose.id, 117); const deathFrame = target.combat.timeline.frame;
  game._updateFighter(target, .01);
  assert.ok(target.combat.timeline.frame > deathFrame, 'death must advance immediately rather than waiting for an obsolete contact freeze');
  assert.equal(target.combat.timeline.pose.id, 117);
});

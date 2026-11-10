import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { NativeCombatController, decodeNativeText, parsePos, parseAct } from '../dist/native-combat.js';
import { createNativeCharacter, parseNativeSkin, parseNativeBones, parseNativeAnimation, parseNativePoses } from '../dist/native-character.js';

// Use the supplied native skin, skeleton and every original jump frame. A
// synthetic floor/wall isolates the browser physics/camera adapter from map
// occlusion; no skeleton coordinates, animation windows or jump poses are faked.
const assets = new URL('../dist/assets/original/characters/', import.meta.url);
const text = file => readFile(new URL(file, assets), 'utf8');
const arrayBuffer = async file => { const b = await readFile(new URL(file, assets)); return b.buffer.slice(b.byteOffset, b.byteOffset + b.byteLength); };
const [skin, bones, personal, common, poses, act] = await Promise.all([
  text('p0/p0.skc'), text('p0/p0.bnc'), arrayBuffer('p0/p0.amb'), arrayBuffer('common/character.amb'), text('p0/p0.pos'),
  readFile(new URL('../dist/assets/native/combat/character.act', import.meta.url))
]);
const data = { id: 0, skin: parseNativeSkin(skin), skeleton: parseNativeBones(bones), animations: [parseNativeAnimation(common), parseNativeAnimation(personal)], poses: parseNativePoses(poses) };
const combatData = { poses: parsePos(poses), actions: parseAct(decodeNativeText(act)) };
const v = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);

function fixture({ locked = false, wall = false } = {}) {
  const game = Object.create(MeteorGame.prototype), character = createNativeCharacter(data, { inPlace: true, loadTextures: false });
  const floor = new THREE.Mesh(new THREE.PlaneGeometry(200, 200), new THREE.MeshBasicMaterial({ side: THREE.DoubleSide })); floor.rotation.x = -Math.PI / 2; floor.updateMatrixWorld(true);
  const colliders = [floor];
  if (wall) { const mesh = new THREE.Mesh(new THREE.PlaneGeometry(30, 20), new THREE.MeshBasicMaterial({ side: THREE.DoubleSide })); mesh.position.set(0, 5, 4); mesh.updateMatrixWorld(true); colliders.push(mesh); }
  const hero = { character, root: character.group, hero: true, id: 0, name: '孟星魂', weapon: 'dagger', velocity: v(), vy: 0, grounded: true, guard: false, dead: false, disposed: false, attackHits: new Set(), lastSerial: 0, heldPose: null };
  hero.root.position.y = .015; hero.combat = new NativeCombatController(combatData, { weapon: 'dagger', sampleRoot: character.sampleRoot });
  hero.combat.play(9, { force: true, loop: true });
  const opponent = { root: new THREE.Group(), dead: false, disposed: false }; opponent.root.position.set(0, .015, -8);
  Object.assign(game, { hero, locked: locked ? opponent : null, enemies: [opponent], keys: new Set(), directionBuffer: [], elapsed: 10, running: true, paused: false, mode: 'training',
    currentMap: { bounds: new THREE.Box3(v(-100, -1, -100), v(100, 20, 100)), colliders }, hostPhysics: { speed: 8, gravity: 34, jumpVelocity: 12, radius: .4, step: .55 },
    camera: new THREE.PerspectiveCamera(48, 16 / 9, .1, 1000), cameraTarget: v(0, 1.665, 0), cameraAngle: 0, cameraPitch: .4, cameraDistance: 8,
    cameraManualUntil: 0, raycaster: new THREE.Raycaster(), _unlockAudio() {} });
  game.camera.position.set(0, 5, 8);
  for (let i = 0; i < 90; i++) { game._updateFighter(hero, 1 / 60); game._tickCamera(1 / 60); }
  return { game, hero, colliders, dispose() { character.dispose(); for (const mesh of colliders) { mesh.geometry.dispose(); mesh.material.dispose(); } } };
}

function visualBounds(hero) {
  hero.root.updateMatrixWorld(true); hero.character.skeleton.update(); hero.character.mesh.computeBoundingBox();
  return hero.character.mesh.boundingBox.clone().applyMatrix4(hero.character.mesh.matrixWorld);
}
function projection(game, box) {
  game.camera.updateMatrixWorld(true);
  return box.getCenter(v()).project(game.camera);
}
function jump(fixture, visit) {
  const { game, hero } = fixture; game.action('jump'); assert.equal(hero.grounded, false);
  const frames = [];
  for (let i = 0; i < 120; i++) {
    game.elapsed += 1 / 60; game._updateFighter(hero, 1 / 60); game._tickCamera(1 / 60);
    const bounds = visualBounds(hero), screen = projection(game, bounds), base = hero.character.getAttachment('d_base').getWorldPosition(v());
    const frame = { i, bounds, screen, base, root: hero.root.position.clone(), camera: game.camera.position.clone(), pose: hero.combat.timeline.pose.id, grounded: hero.grounded };
    frames.push(frame); visit?.(frame);
  }
  return frames;
}

test('native in-place jump removes scene translation from d_base while preserving the authored skeleton pose', () => {
  const character = createNativeCharacter(data, { inPlace: true, loadTextures: false });
  const base = character.getAttachment('d_base'), originalParent = character.bones[0].parent;
  try {
    for (const id of [151, 152, 180]) for (let frame = data.poses[id].start; frame <= data.poses[id].end; frame++) {
      character.setPoseFrame(0, frame); const position = base.getWorldPosition(v());
      assert.ok(position.length() < .01, `pose ${id} frame ${frame}: scene dummy escaped the physics root by ${position.length().toFixed(3)}m`);
      assert.equal(character.bones[0].parent, originalParent);
      assert.ok(Math.abs(character.bones[0].position.z - character.sampleRoot(0, frame).z) < 1e-6, 'pelvis local height must remain authored');
    }
  } finally { character.dispose(); }
});

test('authored non-in-place jump remains available with its original d_base displacement', () => {
  const character = createNativeCharacter(data, { inPlace: false, loadTextures: false });
  try {
    character.setPoseFrame(0, 663);
    assert.ok(Math.abs(character.getAttachment('d_base').position.z - 72.97940063476562) < 1e-5);
    assert.ok(character.getAttachment('d_base').getWorldPosition(v()).y > 5.8);
  } finally { character.dispose(); }
});

test('normal L takeoff moves the collision root by the original d_base curve without adding it twice to the skin', () => {
  const state = fixture();
  try {
    const { game, hero } = state, pose = hero.combat.data.poses.get(151), start = hero.root.position.y;
    const origin = hero.character.sampleSceneMotion(pose.source, pose.start).z;
    game.action('jump');
    for (let index = 1; index <= 27; index++) {
      game._updateFighter(hero, 1/60);
      const expected = (hero.character.sampleSceneMotion(pose.source, pose.start + index/2).z - origin)*.08;
      assert.ok(Math.abs(hero.root.position.y - start - expected) < 1e-5);
      assert.ok(Math.abs(hero.character.getAttachment('d_base').getWorldPosition(v()).y - hero.root.position.y) < .01);
    }
    assert.ok(hero.root.position.y > 5.5, 'authored elevation must permit the sn09 central platform');
  } finally { state.dispose(); }
});

for (const locked of [false, true]) test(`the real L jump stays in view ${locked ? 'with an enemy locked' : 'on open ground'} and lands with the collider`, () => {
  const state = fixture({ locked });
  try {
    const frames = jump(state), airborne = frames.filter(f => !f.grounded), last = frames.at(-1);
    assert.ok(airborne.some(f => f.pose === 151) && airborne.some(f => f.pose === 152), 'exercise both original takeoff and airborne poses');
    assert.ok(Math.max(...airborne.map(f => f.root.y)) > 1.8, 'the collision root must really jump');
    for (const f of frames) {
      assert.ok(Math.abs(f.base.y - f.root.y) < .01, `frame ${f.i}: visual scene translation diverged from collider by ${(f.base.y - f.root.y).toFixed(3)}m`);
      assert.ok(f.screen.z > -1 && f.screen.z < 1 && Math.abs(f.screen.x) < .95 && Math.abs(f.screen.y) < .95, `frame ${f.i} pose ${f.pose}: rendered body center left view: ${f.screen.toArray()}`);
    }
    assert.equal(last.grounded, true); assert.ok(Math.abs(last.root.y - .015) < 1e-5); assert.equal(state.hero.vy, 0);
    assert.ok(last.bounds.min.y > -.15 && last.bounds.min.y < .2, 'landed native feet must meet the collision floor');
  } finally { state.dispose(); }
});

test('jump camera follows the native body without crossing a nearby wall', () => {
  const state = fixture({ wall: true });
  try {
    const frames = jump(state);
    for (const f of frames) {
      assert.ok(f.camera.z < 4, 'camera must stay on the player side of the wall');
      assert.ok(Math.abs(f.base.y - f.root.y) < .01, 'wall collision cannot be bypassed by moving only the camera to the displaced skin');
      assert.ok(Math.abs(f.screen.y) < 1, `frame ${f.i}: body escaped the clipped camera view: ${f.screen.toArray()}`);
    }
  } finally { state.dispose(); }
});


test('in-place correction keeps native dart hand attachments aligned with the same skin pose', () => {
  const inPlace = createNativeCharacter(data, { inPlace: true, loadTextures: false }), authored = createNativeCharacter(data, { inPlace: false, loadTextures: false });
  try {
    for (const id of [200, 202]) for (let frame = data.poses[id].start; frame <= data.poses[id].end; frame++) {
      inPlace.setPoseFrame(0, frame); authored.setPoseFrame(0, frame);
      const inPelvis = inPlace.bones[0].getWorldPosition(v()), authoredPelvis = authored.bones[0].getWorldPosition(v());
      for (const name of ['d_wpnR', 'd_wpnL']) {
        const fixedHand = inPlace.getAttachment(name).getWorldPosition(v()), rawHand = authored.getAttachment(name).getWorldPosition(v());
        assert.ok(fixedHand.sub(inPelvis).distanceTo(rawHand.sub(authoredPelvis)) < 1e-6, `pose ${id} frame ${frame}: scene correction changed ${name} relative to skin`);
      }
      assert.ok(inPlace.getAttachment('d_base').getWorldPosition(v()).length() < .01);
    }
  } finally { inPlace.dispose(); authored.dispose(); }
});

test('native attack 259 cannot leave the skin behind its collision root and raw per-frame override remains usable', () => {
  const character = createNativeCharacter(data, { inPlace: true, loadTextures: false });
  try {
    const pose = data.poses[259];
    for (let frame = pose.start; frame <= pose.end; frame++) {
      character.setPoseFrame(pose.source, frame);
      assert.ok(character.getAttachment('d_base').getWorldPosition(v()).length() < .01, `attack frame ${frame}: inherited scene displacement bypasses root collision`);
    }
    character.setPoseFrame(pose.source, pose.end, { rootMotion: true });
    assert.ok(Math.abs(character.getAttachment('d_base').position.y + 91.01268768310547) < 1e-5, 'raw authoring preview retains the original scene trajectory');
    character.setPoseFrame(pose.source, pose.end, { rootMotion: false });
    assert.ok(character.getAttachment('d_base').position.length() < .01, 'a frame override can explicitly return to collision-aligned playback');
  } finally { character.dispose(); }
});

test('vertical camera follow preserves its settled height over the collision root throughout a real jump', () => {
  const state = fixture();
  try {
    const targetOffset = state.game.cameraTarget.y - state.hero.root.position.y;
    const cameraOffset = state.game.camera.position.y - state.hero.root.position.y;
    jump(state, frame => {
      assert.ok(Math.abs(state.game.cameraTarget.y - frame.root.y - targetOffset) < .001, `frame ${frame.i}: look target lagged behind the jump root`);
      assert.ok(Math.abs(frame.camera.y - frame.root.y - cameraOffset) < .001, `frame ${frame.i}: vertical camera smoothing detached from the jumping player`);
    });
  } finally { state.dispose(); }
});

test('moving forward during the native jump keeps the rendered body on screen and lands while moving', () => {
  const state = fixture();
  try {
    const start = state.hero.root.position.clone(); state.game.action('forward');
    const frames = jump(state), last = frames.at(-1);
    assert.ok(last.root.distanceTo(start) > 10, 'the original actor must actually travel while airborne and after landing');
    for (const f of frames) assert.ok(Math.abs(f.screen.x) < .95 && Math.abs(f.screen.y) < .95 && f.screen.z < 1, `moving frame ${f.i}: body escaped view: ${f.screen.toArray()}`);
    assert.equal(last.grounded, true); assert.ok(Math.abs(last.root.y - .015) < 1e-5);
  } finally { state.dispose(); }
});

test('all twenty supplied characters share the scene dummy hierarchy used by the in-place adapter', async () => {
  for (let id = 0; id < 20; id++) {
    const skeleton = parseNativeBones(await text(`p${id}/p${id}.bnc`));
    const base = skeleton.dummies.filter(entry => entry.name === 'd_base');
    assert.equal(base.length, 1, `p${id} needs one unambiguous scene dummy`);
    assert.equal(base[0].parent, 'NULL', `p${id}: scene dummy must be top level`);
    assert.deepEqual(base[0].position, id === 19 ? [.308, -.265, 0] : [0, 0, 0], `p${id}: preserve the actual BNC scene origin, including p19's nonzero pivot`);
    assert.equal(skeleton.bones[0].parent, 'd_base', `p${id}: skin root must descend from scene dummy`);
  }
});

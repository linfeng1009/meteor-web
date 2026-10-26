import test from 'node:test';
import assert from 'node:assert/strict';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
const v = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
function fixture(colliders = []) {
  const game = Object.create(MeteorGame.prototype), root = new THREE.Group(), targetRoot = new THREE.Group(); targetRoot.position.z = 10;
  const hero = { root, hp: 1500, maxHp: 1500, rage: 0, weapon: 'dart', weaponId: 1, weaponName: '七星', hpSourceVerified: true, character: { source: 0, frame: 1 }, combat: { attacking: false, timeline: { pose: { id: 1 } }, combo: 0 } };
  const opponent = { root: targetRoot, name: '军枪哨兵长', hp: 2000, maxHp: 2000 };
  Object.assign(game, { hero, locked: opponent, enemies: [opponent], currentMap: { bounds: new THREE.Box3(v(-20, 0, -20), v(20, 10, 20)) },
    camera: new THREE.PerspectiveCamera(48, 1.5, .1, 1000), cameraTarget: v(0, 1.65, 0), cameraAngle: 0, cameraPitch: .4, cameraDistance: 8,
    cameraManualUntil: 0, elapsed: 10, running: true, paused: false, raycaster: new THREE.Raycaster(), _collisionCandidates: () => colliders,
    contactHits: 0, kills: 0, deaths: 0, matchElapsed: 0, mode: 'story', damageResolver: () => 34, onUpdate: state => { game.hudState = state; } });
  game.camera.position.set(0, 5, 8); return { game, hero, opponent };
}
function wall(z) { const mesh = new THREE.Mesh(new THREE.PlaneGeometry(20, 20), new THREE.MeshBasicMaterial({ side: THREE.DoubleSide })); mesh.position.set(0, 2, z); mesh.updateMatrixWorld(true); return mesh; }

test('lock-on turns the camera behind the player to keep the actual enemy in view', () => {
  const { game, hero, opponent } = fixture(), playerPosition = hero.root.position.clone();
  for (let frame = 0; frame < 60; frame++) game._tickCamera(.05);
  assert.ok(Math.cos(game.cameraAngle) < -.99); game.camera.updateMatrixWorld(true);
  const screen = opponent.root.position.clone().add(v(0, 1.35, 0)).project(game.camera);
  assert.ok(Math.abs(screen.x) < .02 && Math.abs(screen.y) < 1 && screen.z < 1, `locked enemy outside view: ${screen.toArray()}`);
  assert.deepEqual(hero.root.position.toArray(), playerPosition.toArray());
});

test('manual camera override holds the user angle temporarily and then smoothly follows the lock again', () => {
  const { game } = fixture(); game.cameraAngle = .7; game.cameraManualUntil = 12;
  game._tickCamera(.1); assert.equal(game.cameraAngle, .7);
  game.elapsed = 13; game._tickCamera(.1); assert.notEqual(game.cameraAngle, .7);
  game.paused = true; const angle = game.cameraAngle; game._tickCamera(.1); assert.equal(game.cameraAngle, angle);
});

test('near-wall camera stays in front of the actual triangle and hides only the close player rendering', () => {
  const colliders = [wall(1)], { game, hero } = fixture(colliders); game.locked = null;
  game._tickCamera(.05); assert.ok(game.camera.position.z < 1 && game.camera.position.z > 0); assert.equal(hero.root.visible, false);
  assert.deepEqual(hero.root.position.toArray(), [0, 0, 0]);
  colliders.length = 0; for (let frame = 0; frame < 60; frame++) game._tickCamera(.05);
  assert.equal(hero.root.visible, true); assert.ok(game.camera.position.z > 7);
  const close = fixture([wall(.15)]).game; const safe = close._safeCameraPosition(v(0, 1.65, 0), v(0, 4, 8)); assert.ok(safe.z > 0 && safe.z < .15, 'a minimum zoom must not push through a closer wall');
});

test('enemy HUD reports world distance and signed bearing from the actual camera direction', () => {
  const { game, opponent } = fixture(); opponent.root.position.set(3, 4, 0);
  game.camera.position.set(0, 1.65, 8); game.camera.lookAt(v(0, 1.65, 0)); game._hud();
  assert.equal(game.hudState.enemy.distance, 5); assert.ok(Math.abs(game.hudState.enemy.bearing - Math.PI / 2) < 1e-8);
  opponent.root.position.x = -3; game._hud(); assert.ok(game.hudState.enemy.bearing < 0);
});

import {NATIVE_AIR_PHYSICS} from '../dist/native-traversal.js';
import test, { after } from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { createNativeEnvironment } from '../dist/native-environment.js';
import { loadNativeCombat, NativeCombatController, NATIVE_LOCOMOTION } from '../dist/native-combat.js';
import { NativeMissionHost } from '../dist/native-mission-host.js';
const dist = new URL('../dist/', import.meta.url), original = new URL('assets/original/', dist), v = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
const priorFetch = globalThis.fetch, priorTextureLoad = THREE.TextureLoader.prototype.load;
globalThis.fetch = async input => { try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); } catch { return new Response('', { status: 404 }); } };
THREE.TextureLoader.prototype.load = function(url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
const game = Object.create(MeteorGame.prototype);
Object.assign(game, { manifest: JSON.parse(await readFile(new URL('manifest.json', original), 'utf8')),
  collisionMaterial: new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }), raycaster: new THREE.Raycaster(), onEvent() {} });
game.currentMap = await game._readMap('sn14');
const des = game.currentMap.metadata.files.find(file => file.parsed?.format === 'DES').parsed;
const native = createNativeEnvironment(des.objects, game.currentMap.model);
const combat = await loadNativeCombat();
const resources = [];
after(() => { game._disposeMap(game.currentMap); for (const mesh of resources) { mesh.geometry.dispose(); mesh.material.dispose(); } globalThis.fetch = priorFetch; THREE.TextureLoader.prototype.load = priorTextureLoad; });

function box(name = 'SourceBox') {
  const geometry = new THREE.BufferGeometry(); geometry.setAttribute('position', new THREE.Float32BufferAttribute([
    -1,-1,-1, 1,-1,-1, 1,1,-1, -1,1,-1, -1,-1,1, 1,-1,1, 1,1,1, -1,1,1
  ], 3));
  geometry.setIndex([0,2,1,0,3,2, 4,5,6,4,6,7, 0,4,7,0,7,3, 1,2,6,1,6,5, 0,1,5,0,5,4, 3,7,6,3,6,2]);
  const mesh = new THREE.Mesh(geometry, new THREE.MeshBasicMaterial()); mesh.name = name; resources.push(mesh); return mesh;
}
function source(name = 'SourceBox', props = {}) { return { name, properties: { name: '"hell"', ...props } }; }
function fixture(records = [source()], mesh = box()) { const model = new THREE.Group(); if (mesh) model.add(mesh); return { mesh, model, environment: createNativeEnvironment(records, model) }; }

test('actual sn14 hidden Plane23 is inside the exact original hell volume and a falling-foot sweep detects it', () => {
  assert.equal(native.pending.length, 0); assert.equal(native.triggers.length, 1);
  const trigger = native.triggers[0]; assert.equal(trigger.name, 'HBox'); assert.equal(trigger.source.properties.name, '"hell"');
  const plane = game.currentMap.model.getObjectByName('Plane23'), hell = game.currentMap.model.getObjectByName('HBox');
  assert.equal(plane.visible, false); assert.equal(plane.userData.collidable, true); assert.equal(hell.userData.collidable, false);
  const floor = game._ground(-96, 64, 10); assert.equal(floor.object.name, 'Plane23');
  const landing = floor.point.clone().add(v(0, .015, 0)); assert.ok(trigger.bounds.containsPoint(landing));
  const hit = native.sweep(v(-96, 10, 64), landing);
  assert.equal(hit.name, 'HBox'); assert.ok(hit.t > 0 && hit.t < 1); assert.ok(Math.abs(hit.point.y - trigger.bounds.max.y) < 1e-8);
  assert.equal(native.sweep(landing, landing).t, 0);
  assert.equal(plane.userData.collidable, true, 'a trigger detector must preserve the source hidden support plane');
});

test('the original sn14 player spawn remains outside hell while standing on its actual source floor', () => {
  const spawn = game.currentMap.points.find(point => point.id === game.currentMap.metadata.level.integers.PlayerSpawn);
  assert.ok(spawn); const floor = game._ground(spawn.position.x, spawn.position.z, spawn.position.y + 3); assert.ok(floor);
  const feet = floor.point.clone().add(v(0, .015, 0));
  assert.equal(native.sweep(feet, feet), null); assert.ok(feet.y > native.triggers[0].bounds.max.y);
});

test('continuous world-foot contact catches fast falls and complete crossings even when both endpoints are outside', () => {
  const { environment } = fixture();
  const fall = environment.sweep(v(0, 10, 0), v(0, -10, 0)); assert.equal(fall.t, .45); assert.deepEqual(fall.point.toArray(), [0, 1, 0]);
  const crossing = environment.sweep(v(-10, 0, 0), v(10, 0, 0)); assert.equal(crossing.t, .45); assert.deepEqual(crossing.point.toArray(), [-1, 0, 0]);
  assert.equal(environment.sweep(v(-10, 2, 0), v(10, 2, 0)), null);
  assert.equal(environment.sweep(v(0, 0, 0), v(5, 0, 0)).t, 0); assert.equal(environment.sweep(v(3, 3, 3)), null);
  assert.equal(environment.sweep(v(NaN, 0, 0), v()), null);
});

test('the exact source class and explicit activation decide eligibility, without guessing from a mesh name or appearance', () => {
  for (const klass of ['lava', 'hellfire', 'Hell', '', undefined]) {
    const { environment } = fixture([{ name: 'SourceBox', properties: { name: klass } }]); assert.equal(environment.triggers.length, 0); assert.equal(environment.pending.length, 0);
  }
  for (const props of [{ active: 0 }, { active: '"0"' }, { interactive: '0' }, { interactive: false }]) {
    const { environment } = fixture([source('SourceBox', props)]); assert.equal(environment.sweep(v()), null); assert.equal(environment.pending.length, 0);
  }
  const { environment } = fixture([source('SourceBox', { visible: '0', blockplayer: 'no' })]);
  assert.equal(environment.sweep(v()).name, 'SourceBox', 'hidden non-collidable source volumes still define hazards');
});

test('missing meshes, planes, rotated volumes and malformed boxes remain pending rather than using their broad AABB', () => {
  const noMesh = fixture([source('Missing')]); assert.equal(noMesh.environment.triggers.length, 0); assert.equal(noMesh.environment.pending[0].name, 'Missing');
  const plane = new THREE.Mesh(new THREE.PlaneGeometry(2, 2), new THREE.MeshBasicMaterial()); plane.name = 'SourceBox'; resources.push(plane);
  const notBox = fixture([source()], plane).environment; assert.equal(notBox.sweep(v()), null); assert.equal(notBox.pending.length, 1);
  const rotated = box(); rotated.rotation.y = Math.PI / 4;
  const turned = fixture([source()], rotated).environment; assert.equal(turned.sweep(v()), null); assert.equal(turned.pending.length, 1);
  const broken = box(); broken.geometry.index.setX(1, 1);
  const malformed = fixture([source()], broken).environment; assert.equal(malformed.sweep(v()), null); assert.equal(malformed.pending.length, 1);
});

test('source world placement is retained and multiple valid volumes return the earliest intersection', () => {
  const model = new THREE.Group(), near = box('Near'), far = box('Far'); near.position.x = 4; far.position.x = 8; model.add(near, far); model.position.z = 5;
  const environment = createNativeEnvironment([source('Far'), source('Near')], model);
  assert.equal(environment.pending.length, 0); assert.equal(environment.triggers.length, 2);
  const hit = environment.sweep(v(0, 0, 5), v(12, 0, 5)); assert.equal(hit.name, 'Near'); assert.equal(hit.t, .25); assert.deepEqual(hit.point.toArray(), [3, 0, 5]);
  assert.equal(environment.sweep(v(0, 0, 0), v(12, 0, 0)), null);
  assert.equal(near.position.x, 4); assert.equal(near.geometry.attributes.position.count, 8);
});

function fallingActor(mode = 'story') {
  const events = [], endings = [], engine = Object.create(MeteorGame.prototype), frames = [];
  const actor = { id: 1, scriptId: 0, name: '孟星魂', hero: true, root: new THREE.Group(), velocity: v(),
    hp: 1000, maxHp: 1000, rage: 0, weapon: 'sword', grounded: false, vy: 0, dead: false,
    attackHits: new Set(), contacts: 0, heldPose: null, character: { setPoseFrame(source, frame) { frames.push({ source, frame }); } },
    combat: new NativeCombatController(combat, { weapon: 'sword' }) };
  actor.root.position.set(-96, 10, 64); actor.combat.play(152, { loop: true, force: true });
  Object.assign(engine, { currentMap: game.currentMap, hero: actor, enemies: [], manifest: game.manifest,
    collisionMaterial: game.collisionMaterial, raycaster: new THREE.Raycaster(), keys: new Set(), directionBuffer: [],
    hostPhysics: { speed: 8, gravity: NATIVE_AIR_PHYSICS.gravity, jumpVelocity: NATIVE_AIR_PHYSICS.jumpVelocity, radius: .4, step: .55 }, cameraAngle: 0,
    mode, running: true, paused: false, kills: 0, deaths: 0, matchElapsed: 0, totalDamage: 0,
    onEvent: event => events.push(event), onEnd: result => endings.push(result) });
  return { engine, actor, events, endings, frames };
}

test('real engine falling onto native Plane23 dies at HBox before the hidden floor can keep the actor alive', () => {
  const { engine, actor, events } = fallingActor();
  for (let frame = 0; frame < 180 && !actor.dead; frame++) engine._updateFighter(actor, 1 / 60);
  assert.equal(actor.dead, true); assert.equal(actor.hp, 0, 'HP zero is the explicit Web/PST death mapping');
  assert.deepEqual(actor.environmentDeath, { type: 'hell', object: 'HBox' });
  assert.equal(actor.combat.timeline.pose.id, NATIVE_LOCOMOTION.dead, 'the same update must not replace death with locomotion');
  assert.equal(actor.respawn, Infinity); assert.equal(engine.deaths, 1);
  assert.equal(events.filter(event => event.type === 'environment-death').length, 1);
  for (let frame = 0; frame < 180; frame++) engine._updateFighter(actor, 1 / 60);
  assert.equal(actor.dead, true); assert.equal(engine.deaths, 1);
  assert.equal(events.filter(event => event.type === 'environment-death').length, 1);
});

test('environment death produces one mission failure and source foot placement clears the death reason for restart', () => {
  const { engine, actor, events, endings } = fallingActor();
  const host = new NativeMissionHost(engine, { mapId: 'sn14' }); host.actors.set(0, actor);
  for (let frame = 0; frame < 180 && !actor.dead; frame++) engine._updateFighter(actor, 1 / 60);
  host.checkCompletion(); host.checkCompletion();
  assert.equal(endings.length, 1); assert.equal(endings[0].win, false); assert.equal(endings[0].reason, 'player-death');
  assert.equal(events.filter(event => event.type === 'mission-complete').length, 1);
  const spawn = game.currentMap.points.find(point => point.id === game.currentMap.metadata.level.integers.PlayerSpawn);
  engine._placeFighter(actor, spawn);
  assert.equal(actor.dead, false); assert.equal(actor.hp, 1000); assert.equal(actor.environmentDeath, null);
  assert.equal(actor.grounded, true); assert.equal(native.sweep(actor.root.position), null);
  assert.equal(actor.combat.timeline.pose.id, 6); host.dispose();
});

test('training hazard death uses the existing respawn interval and restores the actual safe source spawn', () => {
  const { engine, actor, events } = fallingActor('training');
  for (let frame = 0; frame < 180 && !actor.dead; frame++) engine._updateFighter(actor, 1 / 60);
  assert.equal(actor.dead, true); assert.equal(actor.respawn, 3);
  engine._updateFighter(actor, 3.01);
  assert.equal(actor.dead, false); assert.equal(actor.hp, 1000); assert.equal(actor.environmentDeath, null);
  assert.equal(native.sweep(actor.root.position), null); assert.equal(engine.deaths, 1);
  assert.equal(events.filter(event => event.type === 'environment-death').length, 1);
});

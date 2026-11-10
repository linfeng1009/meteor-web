// Actual native geometry + the production browser movement adapter, no renderer,
// source EXE execution, character animation or ordinary player route asserted.
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../../../dist/vendor/three.module.js';
import { MeteorGame } from '../../../dist/engine.js';
import { readGmb } from '../../../dist/gmc-loader.js';
const dist = new URL('../../../dist/', import.meta.url), root = new URL('assets/original/', dist);
globalThis.fetch = async input => { try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); } catch { return new Response('', { status: 404 }); } };
THREE.TextureLoader.prototype.load = function(url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
const manifest = JSON.parse(await readFile(new URL('manifest.json', root), 'utf8'));
const mapEntry = manifest.maps.find(m => m.id === 'sn14');
const metadata = JSON.parse(await readFile(new URL(mapEntry.metadata, root), 'utf8'));
const des = metadata.files.find(f => f.parsed?.format === 'DES').parsed;
const hellSource = des.objects.find(o => o.name === 'HBox');
assert.equal(hellSource.properties.name, '"hell"'); assert.equal(hellSource.properties.blockplayer, 'no'); assert.equal(hellSource.properties.visible, '0');
const game = Object.create(MeteorGame.prototype);
Object.assign(game, { manifest, collisionMaterial: new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }), raycaster: new THREE.Raycaster(),
  hostPhysics: { radius: .4, step: .55, gravity: 34 }, mode: 'story', kills: 0, deaths: 0, onEvent() {} });
game.currentMap = await game._readMap('sn14');
const volume = game.currentMap.model.getObjectByName('HBox'), safetyPlane = game.currentMap.model.getObjectByName('Plane23');
assert.ok(volume && !volume.visible && !volume.userData.collidable); assert.ok(safetyPlane && !safetyPlane.visible && safetyPlane.userData.collidable);
const hellBounds = volume.geometry.boundingBox.clone().applyMatrix4(volume.matrixWorld);
const actor = { hero: true, hp: 1000, maxHp: 1000, dead: false, combat: { play() {} }, root: new THREE.Group(), velocity: new THREE.Vector3(), vy: 0, grounded: false };
actor.root.position.set(-1200 * .08, 10, 800 * .08);
const initial = actor.root.position.clone();
let frames = 0;
for (; frames < 180 && !actor.dead; frames++) game._move(actor, new THREE.Vector3(), 0, 1 / 60);
const floor = game._ground(actor.root.position.x, actor.root.position.z, actor.root.position.y + .1);
assert.equal(floor.object.name, 'Plane23');
if (game.currentMap.environment?.triggers.length) { assert.equal(actor.hp, 0); assert.equal(actor.dead, true); } else { assert.ok(actor.grounded); assert.equal(actor.hp, 1000); assert.equal(actor.dead, false); }
assert.ok(hellBounds.containsPoint(actor.root.position));
const bytes = await readFile(new URL(mapEntry.model, root)), data = readGmb(bytes.buffer.slice(bytes.byteOffset, bytes.byteOffset + bytes.byteLength));
const box = data.objects.find(o => o.name === 'HBox');
const sceneText = await readFile(new URL(mapEntry.sceneScript, root), 'utf8');
const result = { date: '2026-10-26', kind: 'sn14-original-environment-geometry-audit',
  finding: actor.dead ? 'The original source hell volume now intercepts the falling actor before it can settle safely on Plane23; host HP0/death follows the source trigger contact.' : 'The original name=hell volume is not a browser collision surface, but no trigger handling runs; an actor settles safely on the hidden Plane23 inside it without losing HP.',
  sourceHell: { name: hellSource.name, properties: hellSource.properties, vertexCount: box.vertices.length, triangleCount: box.faces.length,
    uniqueCoordinateCounts: [0, 1, 2].map(axis => new Set(box.vertices.map(v => v.position[axis])).size),
    worldBounds: { min: hellBounds.min.toArray(), max: hellBounds.max.toArray() }, collidable: volume.userData.collidable, visible: volume.visible },
  hiddenGround: { name: safetyPlane.name, collidable: safetyPlane.userData.collidable, visible: safetyPlane.visible, worldBounds: { min: safetyPlane.geometry.boundingBox.min.toArray(), max: safetyPlane.geometry.boundingBox.max.toArray() } },
  movementProbe: { placedAt: initial.toArray(), frames, dt: 1 / 60, grounded: actor.grounded, finalPosition: actor.root.position.toArray(), floor: floor.object.name,
    hpBefore: 1000, hpAfter: actor.hp, dead: actor.dead, feetInsideHellAabb: hellBounds.containsPoint(actor.root.position), chestInsideHellAabb: hellBounds.containsPoint(actor.root.position.clone().add(new THREE.Vector3(0, 1.35, 0))) },
  existingFallOutThreshold: game.currentMap.bounds.min.y - 20,
  sceneScript: { file: mapEntry.sceneScript, functions: ['Scene_OnInit'], initCalls: ['InitBoxes', 'InitBBoxes', 'InitChairs', 'InitDeskes', 'InitJugs'], referencesHellOrLava: /\b(?:hell|lava)\b/i.test(sceneText),
    note: 'The scene main script contains no hell/lava trigger or environmental damage value. Included breakable-prop libraries have object OnAttack damage callbacks; they are not evidence for a lava damage rate.' },
  scope: 'CPU geometric placement inside one source trigger volume; no player route, browser behavior or original EXE damage/death semantics proved.' };
console.log(JSON.stringify(result, null, 2)); game._disposeMap(game.currentMap);

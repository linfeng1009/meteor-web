import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { createHash } from 'node:crypto';
import * as THREE from '../dist/vendor/three.module.js';
import { createRaidenSword, disposeRaidenSword, loadRaidenSword } from '../dist/raiden-sword.js';
import { MeteorGame } from '../dist/engine.js';
const root = new URL('../dist/assets/enhanced/weapons/raiden-sword/', import.meta.url);
const asset = { manifest: JSON.parse(await readFile(new URL('manifest.json', root), 'utf8')), mesh: JSON.parse(await readFile(new URL('mesh.json', root), 'utf8')) };

test('standalone PMX sword retains authored geometry, native attachment length and original 2048 color texture', async () => {
  const { manifest, mesh } = asset;
  assert.equal(manifest.stats.sourceVertices, 1566); assert.equal(manifest.stats.sourceTriangles, 1850);
  assert.equal(mesh.triangleCount, 1808); assert.equal(manifest.stats.mergedOverlayTriangles, 42);
  assert.ok(mesh.faces.every(face => face.indices.length === 3 && face.indices.every(index => index >= 0 && index < mesh.vertexCount)));
  assert.ok([...mesh.positions, ...mesh.normals, ...mesh.uvs].every(Number.isFinite));
  const sword = createRaidenSword(asset), bounds = new THREE.Box3().setFromObject(sword);
  assert.ok(Math.abs(bounds.max.z - 20.03) < .001); assert.ok(bounds.min.z < -3 && bounds.min.z > -4);
  const color = await readFile(new URL('textures/color.png', root));
  assert.equal(color.readUInt32BE(16), 2048); assert.equal(color.readUInt32BE(20), 2048);
  assert.equal(createHash('sha256').update(color).digest('hex'), manifest.sourceFiles.find(file => file.file === 'tex/刀.png').sha256);
  assert.equal(mesh.faces.filter(face => face.material === 3).length, 42, 'glow belongs to the same base faces, not a second coplanar surface');
  disposeRaidenSword(sword);
});

test('sword styles remain mutually exclusive and cannot change an active move or original attack model', () => {
  const game = Object.create(MeteorGame.prototype), original = new THREE.Group(), butterfly = new THREE.Group(), raiden = createRaidenSword(asset);
  const combat = { timeline: { frame: 9772 }, currentMove: { poseId: 262 } }, weaponModels = [original];
  const actor = game.hero = { hero: true, weapon: 'sword', weaponId: 6, weaponModel: original, weaponModels, butterflySword: butterfly, raidenSword: raiden, combat, weaponReach: 2.4, hp: 721 };
  let butterfliesVisible; game.butterflyVfx = { setVisible(value) { butterfliesVisible = value; } };
  for (const style of ['raiden', 'original', 'butterfly', 'raiden']) {
    game.setSwordStyle(style);
    assert.equal(original.visible, style === 'original'); assert.equal(butterfly.visible, style === 'butterfly'); assert.equal(raiden.visible, style === 'raiden');
    assert.equal(butterfliesVisible, style === 'butterfly');
    assert.equal(actor.weaponModels, weaponModels); assert.equal(actor.weaponModel, original); assert.equal(actor.combat, combat);
    assert.equal(combat.timeline.frame, 9772); assert.equal(actor.hp, 721); assert.equal(actor.weaponReach, 2.4);
  }
  assert.throws(() => game.setSwordStyle('missing'), /Unknown sword style/);
  disposeRaidenSword(raiden);
});

test('a missing Raiden skin falls back to the original sword with butterfly glow disabled', () => {
  const game = Object.create(MeteorGame.prototype); game.hero = { weaponModel: new THREE.Group(), butterflySword: new THREE.Group() };
  game.setSwordStyle('raiden'); assert.equal(game.hero.weaponModel.visible, true); assert.equal(game.hero.butterflySword.visible, false);
});

test('loaded templates can be cloned for equipment without disposing shared textures on a detach', () => {
  const color = new THREE.Texture(), emission = new THREE.Texture(), environment = new THREE.Texture();
  color.userData.raidenSwordOwned = emission.userData.raidenSwordOwned = true;
  const template = createRaidenSword(asset, { environment, textures: new Map([['textures/color.png', color], ['textures/emission.png', emission]]) });
  const clone = template.clone(true), parent = new THREE.Group(); parent.add(clone);
  assert.equal(clone.children[0].geometry, template.children[0].geometry); assert.ok(clone.children[0].material.every((material, i) => material === template.children[0].material[i]));
  let colorDisposals = 0, emissionDisposals = 0, environmentDisposals = 0;
  color.addEventListener('dispose', () => colorDisposals++); emission.addEventListener('dispose', () => emissionDisposals++); environment.addEventListener('dispose', () => environmentDisposals++);
  clone.removeFromParent(); assert.equal(colorDisposals, 0);
  disposeRaidenSword(template); assert.equal(colorDisposals, 1); assert.equal(emissionDisposals, 1); assert.equal(environmentDisposals, 0);
});

test('runtime loader completes both source textures and creates a display-only template', async () => {
  const originalFetch = globalThis.fetch, originalLoad = THREE.TextureLoader.prototype.load;
  globalThis.fetch = async url => new Response(await readFile(new URL(url)), { status: 200 });
  const loads = [];
  THREE.TextureLoader.prototype.load = function (url, done) { loads.push(url); const texture = new THREE.Texture(); done(texture); return texture; };
  try {
    const sword = await loadRaidenSword(); assert.equal(loads.length, 2);
    assert.equal(sword.userData.skin, 'raiden'); assert.equal(sword.children.length, 1);
    assert.ok(sword.children[0].material.every(material => material.map?.isTexture && material.emissiveIntensity <= .35));
    disposeRaidenSword(sword);
  } finally { globalThis.fetch = originalFetch; THREE.TextureLoader.prototype.load = originalLoad; }
});

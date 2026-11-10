import test from 'node:test';
import assert from 'node:assert/strict';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { createPhoenixSpear, disposePhoenixSpear, PHOENIX_SPEAR_AXIS } from '../dist/phoenix-spear.js';

function resources(root) {
  const geometries = new Set(), materials = new Set(), textures = new Set();
  root.traverse(object => {
    if (object.geometry) geometries.add(object.geometry);
    for (const material of object.material ? (Array.isArray(object.material) ? object.material : [object.material]) : []) {
      materials.add(material);
      for (const value of Object.values(material)) if (value?.isTexture && value.userData.phoenixOwned) textures.add(value);
    }
  });
  return { geometries, materials, textures };
}

test('phoenix spear covers the original spear length with finite geometry', () => {
  const spear = createPhoenixSpear();
  const bounds = new THREE.Box3().setFromObject(spear);
  assert.match(spear.name, /霜翎凤鸣/);
  assert.ok(Math.abs(bounds.max.z - PHOENIX_SPEAR_AXIS.tip) < .5, 'head follows the native spear tip');
  assert.ok(Math.abs(bounds.min.z - PHOENIX_SPEAR_AXIS.tail) < .5, 'tail keeps the native spear length');
  assert.ok([...bounds.min.toArray(), ...bounds.max.toArray()].every(Number.isFinite));
  spear.traverse(object => {
    if (object.geometry?.attributes.position) {
      assert.ok(object.geometry.attributes.position.array.every(Number.isFinite), `${object.name} has finite vertices`);
    }
  });
  disposePhoenixSpear(spear);
});

test('phoenix spear preserves visible surface texture and restrained physically based lighting', () => {
  const spear = createPhoenixSpear();
  const { materials, textures } = resources(spear);
  const physical = [...materials].filter(material => material.isMeshPhysicalMaterial || material.isMeshStandardMaterial);
  assert.ok(physical.length >= 4, 'ice, silver, gold and ornament surfaces use distinct materials');
  assert.ok(physical.every(material => Number.isFinite(material.roughness) && Number.isFinite(material.metalness)));
  assert.ok(physical.every(material => material.emissive.getHex() === 0 || material.emissiveIntensity <= .5), 'surface lighting must not wash out the texture');
  assert.ok(textures.size > 0, 'spear contains generated surface texture');
  for (const texture of textures) {
    assert.ok(texture.isDataTexture, 'surface textures work without a browser canvas');
    const red = new Set();
    for (let i = 0; i < texture.image.data.length; i += 4) red.add(texture.image.data[i]);
    assert.ok(red.size > 8, 'surface texture contains detail rather than a flat colour');
  }
  disposePhoenixSpear(spear);
});

test('phoenix ribbons animate independently while keeping their vertices finite', () => {
  const spear = createPhoenixSpear();
  const ribbons = [];
  spear.traverse(object => { if (object.name === 'phoenix-ribbon') ribbons.push(object); });
  assert.ok(ribbons.length >= 2, 'reference has layered silk strips');
  const before = ribbons.map(ribbon => Array.from(ribbon.geometry.attributes.position.array));
  spear.userData.update(1.37);
  ribbons.forEach((ribbon, index) => {
    const after = ribbon.geometry.attributes.position.array;
    assert.ok(after.every(Number.isFinite));
    assert.ok(before[index].some((value, i) => Math.abs(value - after[i]) > 1e-3), 'silk follows its own wave');
  });
  disposePhoenixSpear(spear);
});

test('switching spear skin preserves native combat state and attack reach', () => {
  const game = Object.create(MeteorGame.prototype);
  const original = new THREE.Group(), alternate = createPhoenixSpear();
  const combat = { timeline: { pose: { id: 279 }, time: .4 }, currentMove: { id: 'spear-attack' } };
  const actor = { weapon: 'spear', weaponId: 7, weaponModel: original, weaponModels: [original], phoenixSpear: alternate, combat, weaponReach: 4.1, hp: 721 };
  game.hero = actor;
  game.setSpearStyle('phoenix');
  assert.equal(original.visible, false);
  assert.equal(alternate.visible, true);
  assert.deepEqual(actor.weaponModels, [original], 'native weapon remains the collision source');
  game.setSpearStyle('original');
  assert.equal(original.visible, true);
  assert.equal(alternate.visible, false);
  assert.equal(actor.combat, combat);
  assert.equal(combat.timeline.time, .4);
  assert.equal(actor.weaponReach, 4.1);
  assert.equal(actor.weaponId, 7);
  assert.equal(actor.hp, 721);
  assert.throws(() => game.setSpearStyle('unknown'), /Unknown spear style/);
  disposePhoenixSpear(alternate);
});

test('disposing a spear releases each owned resource once and preserves the shared environment', () => {
  const environment = new THREE.Texture();
  const spear = createPhoenixSpear({ environment });
  const parent = new THREE.Group(); parent.add(spear);
  const { geometries, materials, textures } = resources(spear);
  const counts = new Map();
  for (const resource of [...geometries, ...materials, ...textures]) {
    counts.set(resource, 0);
    resource.addEventListener('dispose', () => counts.set(resource, counts.get(resource) + 1));
  }
  let environmentDisposals = 0;
  environment.addEventListener('dispose', () => environmentDisposals++);
  disposePhoenixSpear(spear);
  assert.equal(spear.parent, null);
  assert.ok([...counts.values()].every(count => count === 1), 'shared geometry, material and owned texture dispose exactly once');
  assert.equal(environmentDisposals, 0, 'game owns the shared PMREM environment');
});

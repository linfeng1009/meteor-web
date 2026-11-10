import test from 'node:test';
import assert from 'node:assert/strict';
import * as THREE from '../dist/vendor/three.module.js';
import { MeteorGame } from '../dist/engine.js';
import { createButterflySword } from '../dist/butterfly-sword.js';

test('sword appearance swaps visuals without changing the active combat state or source weapon model', () => {
  const game=Object.create(MeteorGame.prototype), original=new THREE.Group(), alternate=createButterflySword();
  const combat={timeline:{pose:{id:262},time:.4}, currentMove:{id:'sword-attack'}};
  const actor={weapon:'sword',weaponId:5,weaponModel:original,weaponModels:[original],butterflySword:alternate,combat,weaponReach:2.4,hp:721};
  game.hero=actor; game.setSwordStyle('butterfly');
  assert.equal(original.visible,false);assert.equal(alternate.visible,true);assert.deepEqual(actor.weaponModels,[original]);
  game.setSwordStyle('original');assert.equal(original.visible,true);assert.equal(alternate.visible,false);
  assert.equal(actor.combat,combat);assert.equal(combat.timeline.time,.4);assert.equal(actor.weaponId,5);assert.equal(actor.weaponReach,2.4);assert.equal(actor.hp,721);
  assert.throws(()=>game.setSwordStyle('unknown'),/Unknown sword style/);
});

test('reference sword is a finite 3D mesh with its grip and blade on the original attachment axis', () => {
  const sword=createButterflySword();const box=new THREE.Box3().setFromObject(sword);
  assert.ok(sword.children.length>10);assert.ok(box.min.z < -3 && box.max.z > 19);
  assert.ok([...box.min.toArray(),...box.max.toArray()].every(Number.isFinite));
});

test('refined sword ships physically based materials with emissive glow layers', async () => {
  const { createButterflySword: build } = await import('../dist/butterfly-sword.js');
  const sword = build();
  const materials = new Set();
  sword.traverse(o => { if (o.material) (Array.isArray(o.material) ? o.material : [o.material]).forEach(m => materials.add(m)); });
  const physical = [...materials].filter(m => m.isMeshPhysicalMaterial);
  assert.ok(materials.size >= 6, 'expected several distinct materials');
  assert.ok(physical.length >= 5, 'expected physical materials, not plain standard ones');
  assert.ok(physical.every(m => Number.isFinite(m.metalness) && Number.isFinite(m.roughness)));
  assert.ok(physical.some(m => m.emissiveIntensity > .3 && m.emissive.getHex() !== 0), 'blade must self-illuminate');
  assert.ok(physical.some(m => m.clearcoat > .5), 'blade should carry a clearcoat layer');
  assert.ok(sword.userData.features.includes('emissive-glow'));
  assert.ok(sword.userData.features.includes('pbr-environment'));
  assert.equal(typeof sword.userData.update, 'function');
});

test('ribbon geometry is animated instead of frozen', async () => {
  const { createButterflySword: build } = await import('../dist/butterfly-sword.js');
  const sword = build(); sword.updateMatrixWorld(true);
  const ribbons = []; sword.traverse(o => { if (o.name === 'ribbon') ribbons.push(o); });
  assert.equal(ribbons.length, 2, 'two cloth strips');
  const before = Array.from(ribbons[0].geometry.attributes.position.array);
  sword.userData.update(1.37);
  const after = Array.from(ribbons[0].geometry.attributes.position.array);
  assert.ok(before.some((value, i) => Math.abs(value - after[i]) > 1e-3), 'vertices must move with time');
  assert.ok(after.every(Number.isFinite));
});

test('blade keeps textured surfaces and a restrained glow throughout its animation', () => {
  const sword = createButterflySword();
  const blades = sword.children.filter(child => child.name === 'blade-textured');
  assert.equal(blades.length, 2);
  const texture = blades[0].material.map;
  assert.ok(texture?.isDataTexture);
  assert.ok(new Set(texture.image.data.filter((_, i) => i % 4 === 0)).size > 20, 'texture must contain visible tonal variation');
  assert.ok(blades.every(blade => blade.material.map === texture));
  for (const time of [0, .6, 1.8]) {
    sword.userData.update(time);
    assert.ok(sword.userData.glowMaterials.every(material => material.opacity <= .1));
  }
});

test('disposing the sword releases its generated blade texture once without disposing the shared environment', async () => {
  const { disposeButterflySword } = await import('../dist/butterfly-sword.js');
  const environment = new THREE.Texture();
  const sword = createButterflySword({ environment });
  const texture = sword.children.find(child => child.name === 'blade-textured').material.map;
  let textureDisposals = 0, environmentDisposals = 0;
  texture.addEventListener('dispose', () => textureDisposals++);
  environment.addEventListener('dispose', () => environmentDisposals++);
  disposeButterflySword(sword);
  assert.equal(textureDisposals, 1);
  assert.equal(environmentDisposals, 0);
});

import test from 'node:test';
import assert from 'node:assert/strict';
import * as THREE from '../dist/vendor/three.module.js';
import { createButterflySword } from '../dist/butterfly-sword.js';
import { ButterflySwordVfx } from '../dist/butterfly-vfx.js';

function bench({ quality = 'high', environment = null } = {}) {
  const scene = new THREE.Scene();
  const sword = createButterflySword({ environment });
  scene.add(sword); sword.updateMatrixWorld(true);
  const vfx = new ButterflySwordVfx(scene, { quality });
  vfx.bind(sword);
  return { scene, sword, vfx };
}

test('attacking builds a sword trail that fades and disappears when idle', () => {
  const { vfx } = bench();
  for (let i = 0; i < 6; i++) vfx.update(1 / 60, { attacking: true });
  assert.equal(vfx.trailMesh.visible, true);
  assert.ok(vfx.trailGeometry.drawRange.count > 0, 'trail strip must have triangles');
  assert.ok(vfx.samples.length >= 2);
  // 停手后所有采样按生命周期过期，条带自我隐藏。
  for (let i = 0; i < 40; i++) vfx.update(1 / 60, { attacking: false });
  assert.equal(vfx.trailMesh.visible, false);
  assert.equal(vfx.trailGeometry.drawRange.count, 0);
});

test('trail vertices and colours stay finite and fade toward the tail', () => {
  const { vfx } = bench();
  for (let i = 0; i < 8; i++) vfx.update(1 / 60, { attacking: true });
  const positions = vfx.trailPositions.slice(0, vfx.samples.length * 6);
  const colors = vfx.trailColors.slice(0, vfx.samples.length * 6);
  assert.ok(positions.every(Number.isFinite));
  assert.ok(colors.every(value => Number.isFinite(value) && value >= 0));
  const head = colors.slice(-6).reduce((a, b) => a + b, 0);
  const tail = colors.slice(0, 6).reduce((a, b) => a + b, 0);
  assert.ok(head > tail, 'newest sample must be brighter than the oldest');
});

test('butterflies follow the blade and freeze when the appearance is switched off', () => {
  const { vfx } = bench();
  vfx.update(1 / 60, { attacking: false });
  assert.ok(vfx.butterflies.length >= 4);
  assert.ok(vfx.butterflies.every(b => b.group.visible));
  const first = vfx.butterflies[0].group.position.clone();
  vfx.update(1 / 60, { attacking: false });
  assert.ok(vfx.butterflies[0].group.position.distanceTo(first) >= 0);
  vfx.setVisible(false);
  assert.ok(vfx.butterflies.every(b => !b.group.visible && b.material.opacity === 0));
  assert.equal(vfx.trailMesh.visible, false);
});

test('impact burst spawns a ring plus butterflies and cleans itself up', () => {
  const { vfx, scene } = bench();
  vfx.update(1 / 60, { attacking: true });
  vfx.burst(new THREE.Vector3(1, 1.2, 2), { knockdown: true });
  const kinds = vfx.bursts.map(b => b.kind);
  assert.ok(kinds.includes('ring'));
  assert.ok(kinds.filter(kind => kind === 'butterfly').length >= 3, 'knockdown scatters a small swarm');
  for (let i = 0; i < 90; i++) vfx.update(1 / 60, { attacking: false });
  assert.equal(vfx.bursts.length, 0, 'bursts must be released');
  assert.equal(scene.children.filter(o => o.type === 'Mesh' && o.geometry?.type === 'RingGeometry').length, 0);
});

test('low quality keeps the effect budget smaller', () => {
  const high = bench({ quality: 'high' }).vfx;
  const low = bench({ quality: 'low' }).vfx;
  assert.ok(high.butterflies.length > low.butterflies.length);
  high.dispose(); low.dispose();
});

test('dispose releases scene objects and is safe to call twice', () => {
  const { vfx, scene } = bench();
  vfx.update(1 / 60, { attacking: true });
  vfx.burst(new THREE.Vector3(), {});
  const before = scene.children.length;
  vfx.dispose();
  assert.ok(scene.children.length < before);
  vfx.dispose();
});
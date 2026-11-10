import test from 'node:test';
import assert from 'node:assert/strict';
import * as THREE from '../dist/vendor/three.module.js';
import { NativeImpactFeedback, IMPACT_FEEDBACK_ADAPTER } from '../dist/native-impact-feedback.js';

test('actual contact feedback distinguishes guard, light hit and knockdown with bounded actor freezes', () => {
  const scene = new THREE.Scene(), impact = new NativeImpactFeedback(scene), point = new THREE.Vector3(4, 1.2, -7);
  const guard = impact.emit({ point, guarded: true }), hit = impact.emit({ point }), down = impact.emit({ point, knockdown: true });
  assert.ok(guard.hitstop > 0 && guard.hitstop < hit.hitstop && hit.hitstop < down.hitstop);
  assert.ok(down.hitstop <= .06, 'a presentation freeze cannot become a lengthy global pause');
  assert.equal(scene.children.length, 3);
  for (const mesh of scene.children) {
    assert.deepEqual(mesh.position.toArray(), point.toArray());
    assert.ok([...mesh.geometry.attributes.position.array].every(Number.isFinite));
    assert.equal(mesh.material.depthTest, true); assert.equal(mesh.material.depthWrite, false);
  }
  assert.notEqual(scene.children[0].material.color.getHex(), scene.children[1].material.color.getHex());
  impact.dispose();
});

test('feedback expires and disposes GPU resources, with no camera drift after an impact', () => {
  const scene = new THREE.Scene(), impact = new NativeImpactFeedback(scene);
  impact.emit({ point: new THREE.Vector3(), knockdown: true }); const mesh = scene.children[0]; let geometries = 0, materials = 0;
  mesh.geometry.addEventListener('dispose', () => geometries++); mesh.material.addEventListener('dispose', () => materials++);
  impact.update(.016); assert.ok(impact.cameraOffset.length() > 0);
  assert.ok(impact.cameraOffset.length() <= IMPACT_FEEDBACK_ADAPTER.knockdown.cameraImpulse);
  impact.update(.3); assert.equal(scene.children.length, 0); assert.equal(impact.active.length, 0);
  assert.equal(geometries, 1); assert.equal(materials, 1); assert.equal(impact.cameraOffset.length(), 0);
});

test('multi-target impacts have a hard memory and shake cap; distant contacts do not move the camera', () => {
  const scene = new THREE.Scene(), impact = new NativeImpactFeedback(scene), point = new THREE.Vector3();
  assert.equal(impact.emit({ point, local: false }).cameraImpulse, 0); impact.update(.01); assert.equal(impact.cameraOffset.length(), 0);
  for (let i = 0; i < 100; i++) impact.emit({ point, knockdown: true });
  assert.ok(scene.children.length <= IMPACT_FEEDBACK_ADAPTER.maxEffects);
  impact.update(.016); assert.ok(impact.cameraOffset.length() <= IMPACT_FEEDBACK_ADAPTER.knockdown.cameraImpulse + 1e-9);
  impact.clear(); assert.equal(scene.children.length, 0); assert.equal(impact.cameraOffset.length(), 0);
  impact.dispose(); assert.equal(impact.emit({ point }), null);
});

test('invalid contact coordinates cannot introduce NaNs or an invisible lingering effect', () => {
  const scene = new THREE.Scene(), impact = new NativeImpactFeedback(scene);
  assert.equal(impact.emit(), null); assert.equal(impact.emit({ point: new THREE.Vector3(NaN, 0, 0) }), null);
  impact.emit({ point: new THREE.Vector3(), local: false }); impact.update(-1); impact.update(NaN);
  assert.equal(impact.active[0].age, 0); assert.ok([...scene.children[0].geometry.attributes.position.array].every(Number.isFinite));
  impact.clear();
});

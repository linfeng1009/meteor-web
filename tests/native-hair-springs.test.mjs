import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import * as THREE from '../dist/vendor/three.module.js';
import { validateHairRig } from '../dist/hair-springs.js';
import { createNativeCharacter, loadNativeCharacterData } from '../dist/native-character.js';

const json = async path => JSON.parse(await readFile(new URL(path, import.meta.url)));
const fileFetch = async url => {
  try { return new Response(await readFile(new URL(url))); }
  catch { return new Response('', { status: 404 }); }
};
const withFetch = async callback => {
  const before = globalThis.fetch; globalThis.fetch = fileFetch;
  try { return await callback(); } finally { globalThis.fetch = before; }
};
const data = await withFetch(() => loadNativeCharacterData(0));
const joints = actor => [...actor.bones, ...actor.dummies].map(b => b.matrixWorld.toArray());
const energy = snapshot => snapshot.reduce((sum, n) => sum + new THREE.Vector3().fromArray(n.tail).distanceToSquared(new THREE.Vector3().fromArray(n.previous)), 0);
const point = new THREE.Vector3(), other = new THREE.Vector3();
const models = ['hutao', 'raiden', 'emilia'];

for (const name of models) {
  const skin = await json(`../dist/assets/enhanced/${name}/mesh.json`), rig = skin.secondaryMotion;
  test(`${name}: hair rig keeps original geometry and every non-hair binding`, async () => {
    const baseline = await json(`../work/hair-physics-2026-11-10/baseline/${name}/mesh.json`);
    assert.equal(validateHairRig(rig), rig.bones.length);
    for (const field of ['positions', 'normals', 'uvs', 'faces']) assert.deepEqual(skin[field], baseline[field], field);
    const hairMaterials = new Set(rig.hairMaterials);
    const protectedVertices = new Set(skin.faces.filter(f => !hairMaterials.has(f.material)).flatMap(f => f.indices));
    let driven = 0, unchanged = true, valid = true;
    for (let v = 0; v < skin.vertexCount; v++) {
      const indices = skin.skinIndices.slice(v * 4, v * 4 + 4), weights = skin.skinWeights.slice(v * 4, v * 4 + 4);
      valid &&= indices.every(i => Number.isInteger(i) && i >= 0 && i < 30 + rig.bones.length) && Math.abs(weights.reduce((a,b) => a+b, 0) - 1) < .001;
      if (indices.some((i,j) => i >= 30 && weights[j] > 0)) { driven++; valid &&= !protectedVertices.has(v); }
      if (protectedVertices.has(v)) unchanged &&= indices.every((i,j) => i === baseline.skinIndices[v*4+j]) && weights.every((w,j) => w === baseline.skinWeights[v*4+j]);
    }
    assert.equal(unchanged, true, 'face, body and costume weights remain exact');
    assert.equal(valid, true, 'only hair vertices use valid extra influences'); assert.ok(driven > 100);
    assert.ok(rig.bones.every(b => b.follow >= .98 && b.globalMaxAngle <= .04), 'restrained profile is exported in the assets');
  });

  test(`${name}: continuous motion stays restrained and preserves native joints and weapon`, async () => withFetch(async () => {
    const actor = createNativeCharacter(data, { loadTextures: false }), reference = createNativeCharacter(data, { loadTextures: false });
    try {
      await actor.setAppearance(name);
      assert.equal(actor.skeleton.bones.length, 30);
      assert.equal(actor.mesh.skeleton.bones.slice(0, 30).every((b,i) => b === actor.bones[i]), true);
      const attachment = actor.getAttachment('d_wpnR'), weapon = new THREE.Group(); attachment.add(weapon);
      const inverseRestHeadQ = new THREE.Quaternion();
      actor.skeleton.boneInverses[13].clone().invert().decompose(new THREE.Vector3(), inverseRestHeadQ, new THREE.Vector3()); inverseRestHeadQ.invert();
      const axes = rig.bones.map(b => new THREE.Vector3().fromArray(b.tail).sub(new THREE.Vector3().fromArray(b.position)).normalize().applyQuaternion(inverseRestHeadQ));
      let maxAngle = 0, maxLengthError = 0, peakEnergy = 0, finite = true;
      for (let frame = 0; frame < 210; frame++) {
        const t = Math.min(frame, 89) / 60, pose = data.poses[144];
        for (const a of [actor, reference]) {
          a.group.position.set(Math.sin(t * 2) * .35, Math.max(0, Math.sin(t * 4)) * .45, 0);
          a.group.rotation.y = Math.sin(t * 3) * .65;
          a.setPoseFrame(pose.source, pose.start + (t * 30) % (pose.end - pose.start));
        }
        const before = joints(actor), weaponBefore = weapon.matrixWorld.toArray();
        actor.updateSecondaryMotion(1 / 60, { groundY: 0 });
        assert.deepEqual(joints(actor), before); assert.deepEqual(joints(actor), joints(reference));
        assert.deepEqual(weapon.matrixWorld.toArray(), weaponBefore); assert.equal(actor.getAttachment('d_wpnR'), attachment);
        const snapshot = actor.getSecondaryMotionSnapshot(), headQ = actor.bones[13].getWorldQuaternion(new THREE.Quaternion());
        for (let i = 0; i < snapshot.length; i++) {
          const n = snapshot[i]; finite &&= [...n.position, ...n.tail, ...n.previous].every(Number.isFinite);
          point.fromArray(n.tail).sub(other.fromArray(n.position));
          maxLengthError = Math.max(maxLengthError, Math.abs(point.length() - n.length));
          maxAngle = Math.max(maxAngle, point.normalize().angleTo(axes[i].clone().applyQuaternion(headQ)));
        }
        if (frame >= 90 && frame < 100) peakEnergy = Math.max(peakEnergy, energy(snapshot));
      }
      assert.equal(finite, true); assert.ok(maxAngle <= .04001, `whole-strand angle ${maxAngle}`);
      assert.ok(maxLengthError < 1e-6, `segment length error ${maxLengthError}`);
      assert.ok(peakEnergy > 1e-12, 'moving hair retains a small physical response');
      assert.ok(energy(actor.getSecondaryMotionSnapshot()) < Math.max(1e-13, peakEnergy * .002), 'motion settles after the driver stops');
    } finally { actor.dispose(); reference.dispose(); }
  }));
}

test('hair physics handles frame rates, pauses, teleports, toggles and cached appearances', async () => withFetch(async () => {
  const final = [];
  for (const fps of [30, 60, 120]) {
    const actor = createNativeCharacter(data, { loadTextures: false });
    try {
      await actor.setAppearance('raiden'); const pose = data.poses[6]; actor.setPoseFrame(pose.source, pose.start); actor.resetSecondaryMotion();
      for (let frame = 0; frame < fps * 2; frame++) {
        const t = Math.min(frame / fps, 1);
        actor.group.position.x = Math.sin(t * Math.PI) * .3; actor.group.rotation.y = t * .5;
        actor.updateSecondaryMotion(1 / fps);
      }
      final.push(actor.getSecondaryMotionSnapshot().map(n => n.tail));
      const before = actor.getSecondaryMotionSnapshot(); actor.updateSecondaryMotion(0);
      assert.deepEqual(actor.getSecondaryMotionSnapshot(), before);
      const resets = actor.secondaryMotionStatus.resets; actor.group.position.x += 8; actor.updateSecondaryMotion(1 / fps);
      assert.ok(actor.secondaryMotionStatus.resets > resets, 'teleport resets stale inertia');
      actor.setSecondaryMotionEnabled(false); const disabled = actor.getSecondaryMotionSnapshot();
      actor.updateSecondaryMotion(.1); assert.deepEqual(actor.getSecondaryMotionSnapshot(), disabled);
      for (const appearance of ['emilia', 'original', 'hutao', 'raiden']) {
        await actor.setAppearance(appearance); assert.equal(actor.secondaryMotionStatus.enabled, false);
      }
      actor.setSecondaryMotionEnabled(true); assert.equal(actor.secondaryMotionStatus.enabled, true);
      actor.updateSecondaryMotion(1); assert.ok(actor.getSecondaryMotionSnapshot().every(n => n.tail.every(Number.isFinite)));
    } finally { actor.dispose(); }
  }
  for (const tails of final.slice(1)) assert.ok(tails.every((tail, i) => new THREE.Vector3().fromArray(tail).distanceTo(new THREE.Vector3().fromArray(final[0][i])) < .01), '30/60/120 Hz converge to the same settled hair pose');
}));

test('hair rig rejects invalid constraints and forward parent references', async () => {
  const rig = (await json('../dist/assets/enhanced/emilia/mesh.json')).secondaryMotion;
  for (const mutate of [b => b.follow = Infinity, b => b.globalMaxAngle = -1, b => b.parent = 999, b => b.rotation = [0,0,0,0]]) {
    const invalid = structuredClone(rig); mutate(invalid.bones[0]); assert.throws(() => validateHairRig(invalid), /Invalid hair/);
  }
});

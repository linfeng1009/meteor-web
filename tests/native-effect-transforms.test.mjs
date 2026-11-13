import test, { after } from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { createHash } from 'node:crypto';
import * as THREE from '../dist/vendor/three.module.js';
import { loadNativeCharacter } from '../dist/native-character.js';
import { createEffectTransforms, effectNodeMatrix, setEffectTime, snapshotEffectAnchors } from '../dist/native-effect-transforms.js';

const dist = new URL('../dist/', import.meta.url), v = (x = 0, y = 0, z = 0) => new THREE.Vector3(x, y, z);
const oldFetch = globalThis.fetch, oldLoad = THREE.TextureLoader.prototype.load;
globalThis.fetch = async input => { try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); } catch { return new Response('', { status: 404 }); } };
THREE.TextureLoader.prototype.load = function (_url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
const manifest = JSON.parse(await readFile(new URL('assets/original/rage-vfx/manifest.json', dist)));
const character = await loadNativeCharacter(0, { scale: .08, inPlace: true, appearance: 'original' });
const actor = { character, root: character.group };
const worldAxes = new THREE.Matrix4().makeRotationX(-Math.PI / 2).scale(v(.08, .08, .08));
after(() => { character.dispose(); globalThis.fetch = oldFetch; THREE.TextureLoader.prototype.load = oldLoad; });
const closeVector = (a, b, message) => assert.ok(a.distanceTo(b) < 1e-8, `${message}: ${a.toArray()} versus ${b.toArray()}`);
const closeMatrix = (a, b, message) => assert.ok(a.elements.every((value, i) => Math.abs(value - b.elements[i]) < 1e-8), message);
const keyAt = (position, scale = [1, 1, 1]) => [0, ...position, 0, 0, 0, 1, ...scale, ...new Array(17).fill(0)];
function synthetic(bindings, flags = [0, 0, 0, 1], position = [10, 20, 30]) {
  return { type: 'BOX', name: 'AttackAsymmetric', dimensions: [2, 4, 6], bindings, flags, keys: [keyAt(position)] };
}
function sample(f, source, time = 0) {
  const graph = createEffectTransforms(f, { nodes: [source] }, { weaponAttachments: {} }); setEffectTime(graph, time);
  return effectNodeMatrix(graph, graph.nodes[0]);
}
function simpleActor() {
  const root = new THREE.Group(), nativeSpace = new THREE.Group(), bone = new THREE.Group();
  root.position.set(10, 1, 20); root.rotation.y = Math.PI / 2;
  nativeSpace.rotation.x = -Math.PI / 2; nativeSpace.scale.setScalar(.08); root.add(nativeSpace);
  bone.position.set(100, 200, 300); bone.rotation.x = .7; nativeSpace.add(bone);
  return { root, character: { nativeSpace, getAttachment: name => name === 'b' ? bone : null }, bone };
}

test('original203 empty rotation binding keeps native world axes while its origin follows the animated bone', async () => {
  const definition = manifest.effects.pos203, source = definition.nodes.find(node => node.name === 'AttackBall');
  assert.deepEqual(source.bindings, ['b', '']); assert.equal(source.flags[3], 1);
  assert.equal(createHash('sha256').update(await readFile(new URL(`assets/original/${definition.source}`, dist))).digest('hex'), definition.sha256);
  const time = source.keys[0][0], key = source.keys[0], matrices = [];
  for (const yaw of [0, Math.PI / 3]) {
    actor.root.position.set(7, .015, -9); actor.root.rotation.y = yaw; character.setPoseFrame(0, 3630);
    const matrix = sample(actor, source, time), bone = character.getAttachment('b'); bone.updateWorldMatrix(true, false);
    const expectedOrigin = new THREE.Vector3().setFromMatrixPosition(bone.matrixWorld).add(v(...key.slice(1, 4)).applyMatrix4(worldAxes));
    closeVector(new THREE.Vector3().setFromMatrixPosition(matrix), expectedOrigin, '203 bone origin plus native world offset');
    const expectedBasis = worldAxes.clone().multiply(new THREE.Matrix4().compose(v(), new THREE.Quaternion(...key.slice(4, 8)).normalize(), v(...key.slice(8, 11))));
    const asymmetricPoint = v(11, 17, 23), displacement = asymmetricPoint.clone().applyMatrix4(matrix).sub(expectedOrigin);
    closeVector(displacement, asymmetricPoint.clone().applyMatrix4(expectedBasis), '203 must not inherit caster yaw'); matrices.push(matrix);
  }
  const delta = matrix => v(11, 17, 23).applyMatrix4(matrix).sub(new THREE.Vector3().setFromMatrixPosition(matrix));
  closeVector(delta(matrices[0]), delta(matrices[1]), 'empty rotation stays fixed when the caster turns');
});

test('original204 split bone/Character binding uses the Character basis for key offsets', () => {
  const source = manifest.effects.pos204.nodes.find(node => node.name === 'AttackBall'), key = source.keys[0];
  assert.deepEqual(source.bindings, ['b', 'Character']); actor.root.rotation.y = Math.PI / 3; character.setPoseFrame(0, 3680);
  const matrix = sample(actor, source, key[0]), bone = character.getAttachment('b'); bone.updateWorldMatrix(true, false); character.nativeSpace.updateWorldMatrix(true, false);
  const basis = character.nativeSpace.matrixWorld.clone(), boneOrigin = new THREE.Vector3().setFromMatrixPosition(bone.matrixWorld);
  const expectedOrigin = v(...key.slice(1, 4)).transformDirection(basis).multiplyScalar(v(...key.slice(1, 4)).length() * .08).add(boneOrigin);
  closeVector(new THREE.Vector3().setFromMatrixPosition(matrix), expectedOrigin, '204 offset must follow Character axes, not the animated bone');
  const expected = basis.setPosition(boneOrigin).multiply(new THREE.Matrix4().compose(v(...key.slice(1, 4)), new THREE.Quaternion(...key.slice(4, 8)).normalize(), v(...key.slice(8, 11))));
  closeMatrix(matrix, expected, 'full original204 transform');
});

test('native relative and world position flags produce different fixed coordinates under a turned caster', () => {
  const f = simpleActor(), relative = sample(f, synthetic(['b', 'Character'])), absolute = sample(f, synthetic(['b', 'Character'], [0, 0, 0, 0]));
  closeVector(new THREE.Vector3().setFromMatrixPosition(relative), v(-7.6, 27.4, 11.2), 'relative key offset');
  closeVector(new THREE.Vector3().setFromMatrixPosition(absolute), v(-5.2, 27.4, 10.4), 'native world key offset');
  const empty = sample(f, synthetic(['b', ''])), root = sample(f, synthetic(['b', 'ROOT']));
  closeMatrix(empty, root, 'empty and ROOT share native default orientation');
  closeVector(v(1, 2, 3).applyMatrix4(empty).sub(new THREE.Vector3().setFromMatrixPosition(empty)), v(.08, .24, -.16), 'asymmetric world basis');
});

test('separate position and rotation parents preserve a sheared affine basis and never inherit position-parent rotation', () => {
  const f = simpleActor(), rotationParent = new THREE.Group(); f.character.nativeSpace.add(rotationParent);
  rotationParent.matrixAutoUpdate = false; rotationParent.matrix.set(2, .5, 0, 10, 0, 1, .25, 20, .3, 0, .75, 30, 0, 0, 0, 1);
  const getAttachment = f.character.getAttachment; f.character.getAttachment = name => name === 'rotation' ? rotationParent : getAttachment(name);
  const source = synthetic(['b', 'rotation'], [0, 0, 0, 1], [2, 5, 7]), matrix = sample(f, source);
  rotationParent.updateWorldMatrix(true, false); f.bone.updateWorldMatrix(true, false);
  const expected = rotationParent.matrixWorld.clone().setPosition(new THREE.Vector3().setFromMatrixPosition(f.bone.matrixWorld))
    .multiply(new THREE.Matrix4().makeTranslation(2, 5, 7));
  closeMatrix(matrix, expected, 'decomposing the independent rotation parent would discard shear');
  const before = matrix.clone(); f.bone.rotation.set(1.2, .9, -.4);
  closeMatrix(sample(f, source), before, 'position parent contributes its origin without its animated orientation');
});


test('original pos245/246/247 self-named billboard rotation uses the native default instead of disappearing', async () => {
  const combat = JSON.parse(await readFile(new URL('assets/original/combat-vfx.json', dist)));
  for (const id of ['pos245', 'pos246', 'pos247']) {
    const definition = combat.effects[id], source = definition.nodes.find(node => node.name === 'Board_1');
    assert.equal(createHash('sha256').update(await readFile(new URL(`assets/original/${definition.source}`, dist))).digest('hex'), definition.sha256);
    assert.deepEqual(source.bindings, ['Sphere_2', 'Board_1']);
    const f = simpleActor(), graph = createEffectTransforms(f, definition, manifest);
    setEffectTime(graph, source.keys[0][0]);
    const node = graph.nodes.find(node => node.source === source), actual = effectNodeMatrix(graph, node);
    assert.ok(actual, `${id} authored billboard must remain visible`);
    const fallback = structuredClone(definition);
    fallback.nodes.find(node => node.name === 'Board_1').bindings[1] = '';
    const expected = createEffectTransforms(f, fallback, manifest); setEffectTime(expected, source.keys[0][0]);
    closeMatrix(actual, effectNodeMatrix(expected, expected.nodes.find(node => node.source.name === 'Board_1')), `${id} native self exclusion`);
  }
});

test('bone and weapon socket references take precedence over identically named effect nodes', () => {
  const f = simpleActor(), socket = new THREE.Group(); socket.name = 'wpn'; socket.position.set(3, 4, 5); f.root.add(socket); f.weaponModels = [socket];
  const definitions = [synthetic(['b', 'Character']), { ...synthetic(['ROOT', ''], undefined, [1000, 0, 0]), name: 'b' }];
  const graph = createEffectTransforms(f, { nodes: definitions }, manifest); setEffectTime(graph, 0);
  closeMatrix(effectNodeMatrix(graph, graph.nodes[0]), sample(f, definitions[0]), 'bone must win over sibling');
  const sockets = { weaponAttachments: { wpn: { test_socket: { position: [1, 2, 3], quaternion: [1, 0, 0, 0] } } } };
  const source = synthetic(['test_socket', 'Character']);
  const withSibling = createEffectTransforms(f, { nodes: [source, { ...definitions[1], name: 'test_socket' }] }, sockets);
  const withoutSibling = createEffectTransforms(f, { nodes: [source] }, sockets);
  setEffectTime(withSibling, 0); setEffectTime(withoutSibling, 0);
  closeMatrix(effectNodeMatrix(withSibling, withSibling.nodes[0]), effectNodeMatrix(withoutSibling, withoutSibling.nodes[0]), 'socket must win over sibling');
});

test('detached tails freeze external anchors per requesting node while sibling keys continue moving', () => {
  const f = simpleActor(), self = { ...synthetic(['ROOT', 'Self'], undefined, [0, 0, 0]), name: 'Self' };
  self.keys.push([1, 100, 0, 0, ...self.keys[0].slice(4)]);
  const follower = { ...synthetic(['Self', ''], undefined, [0, 0, 0]), name: 'Follower' };
  const graph = createEffectTransforms(f, { nodes: [self, follower] }, manifest); setEffectTime(graph, 0);
  const first = effectNodeMatrix(graph, graph.nodes[1]).clone();
  graph.frozenAnchors = snapshotEffectAnchors(graph);
  f.root.position.add(v(100, 200, 300)); setEffectTime(graph, 1);
  const last = effectNodeMatrix(graph, graph.nodes[1]);
  assert.ok(last); closeVector(new THREE.Vector3().setFromMatrixPosition(last).sub(new THREE.Vector3().setFromMatrixPosition(first)), v(8, 0, 0), 'follower keeps live sibling animation without following moved caster');
});

test('true two-node binding cycles remain invalid', () => {
  const a = { ...synthetic(['B', '']), name: 'A' }, b = { ...synthetic(['A', '']), name: 'B' };
  const graph = createEffectTransforms(simpleActor(), { nodes: [a, b] }, manifest); setEffectTime(graph, 0);
  assert.equal(effectNodeMatrix(graph, graph.nodes[0]), null);
});

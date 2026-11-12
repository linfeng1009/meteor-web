import * as THREE from './vendor/three.module.js';

// Original PonEF channels and bindings, shared by drawing and attack queries.
// Interpolation and the native-to-Web transform are host implementations.
const ROOT = new URL('./assets/original/rage-vfx/', import.meta.url);
const NATIVE_TO_WEB = new THREE.Matrix4().makeRotationX(-Math.PI / 2);
const NATIVE_WORLD = NATIVE_TO_WEB.clone().scale(new THREE.Vector3().setScalar(.08));
const UNIT = new THREE.Vector3(1, 1, 1);
let manifestPromise;
export function loadNativeEffectManifest() {
  return manifestPromise ||= fetch(new URL('manifest.json', ROOT)).then(response => {
    if (!response.ok) throw new Error('Original effect manifest unavailable');
    return response.json();
  }).catch(error => { manifestPromise = null; throw error; });
}

export function sampleEffectKeys(keys, time, result = new Array(28)) {
  if (!keys?.length || !Number.isFinite(time)) return null;
  let lo = keys[0], hi = lo;
  if (time >= keys.at(-1)[0]) lo = hi = keys.at(-1);
  else for (let i = 1; i < keys.length; i++) { hi = keys[i]; if (time <= hi[0]) { lo = keys[i - 1]; break; } }
  const t = hi[0] > lo[0] ? THREE.MathUtils.clamp((time - lo[0]) / (hi[0] - lo[0]), 0, 1) : 0;
  for (let i = 0; i < 28; i++) result[i] = THREE.MathUtils.lerp(lo[i], hi[i], t);
  const a = new THREE.Quaternion(...lo.slice(4, 8)).normalize(), b = new THREE.Quaternion(...hi.slice(4, 8)).normalize();
  a.slerp(b, t); result.splice(4, 4, a.x, a.y, a.z, a.w);
  return result;
}

export function createEffectTransforms(actor, definition, manifest) {
  const graph = { actor, manifest, time: 0, nodes: [], names: new Map(), nodeMatrices: new Set() };
  for (const source of definition.nodes) {
    const node = { source, matrix: new THREE.Matrix4(), local: new THREE.Matrix4(), key: new Array(28), valid: false };
    graph.nodes.push(node); graph.nodeMatrices.add(node.matrix);
    if (source.type !== 'AUDIO' && !graph.names.has(source.name.toLowerCase())) graph.names.set(source.name.toLowerCase(), node);
  }
  return graph;
}
export function setEffectTime(graph, time) {
  graph.time = time;
  for (const node of graph.nodes) { node.updated = false; node.valid = false; }
}

function anchor(graph, name, visiting, rotation = false, owner = null) {
  const { actor, manifest } = graph, binding = String(name ?? ''), key = binding.toLowerCase();
  const candidate = key && key !== 'root' && key !== 'character' ? graph.names.get(key) : null;
  // 0056e230 searches external bones/sockets before sibling nodes and skips
  // the requesting node itself (native pos245/246/247 Board_1 rotation).
  const parent = candidate !== owner ? candidate : null;
  if (graph.frozenAnchors) return graph.frozenAnchors.get(owner)?.[Number(rotation)]
    || (parent ? effectNodeMatrix(graph, parent, visiting) : null);
  // 0056e230 returns the effect owner's default matrix for ROOT/empty names;
  // 00582120 uses an identity orientation when no rotation parent resolved.
  // Native world axes still require the Web coordinate/unit conversion.
  if (!key || key === 'root') {
    if (rotation) return NATIVE_WORLD;
    actor.root.updateWorldMatrix(true, false); return actor.root.matrixWorld;
  }
  if (key === 'character') {
    if (actor.character.nativeSpace) { actor.character.nativeSpace.updateWorldMatrix(true, false); return actor.character.nativeSpace.matrixWorld; }
    actor.root.updateWorldMatrix(true, false);
    return actor.root.matrixWorld.clone().multiply(NATIVE_TO_WEB).scale(new THREE.Vector3().setScalar(.08));
  }
  const attachment = actor.character.getAttachment?.(binding) || actor.character.getAttachment?.(binding.trim().replace(/\s+/g, '_'));
  if (attachment) { attachment.updateWorldMatrix(true, false); return attachment.matrixWorld; }
  for (const model of actor.weaponModels || (actor.weaponModel ? [actor.weaponModel] : [])) {
    const dummy = manifest.weaponAttachments?.[model.name.toLowerCase()]?.[key];
    if (!dummy) continue;
    model.updateWorldMatrix(true, false);
    const q = dummy.quaternion, local = new THREE.Matrix4().compose(new THREE.Vector3(...dummy.position), new THREE.Quaternion(q[1], q[2], q[3], q[0]).normalize(), UNIT);
    return model.matrixWorld.clone().multiply(NATIVE_TO_WEB).multiply(local);
  }
  if (parent) return effectNodeMatrix(graph, parent, visiting);
  // 0056e230 also returns the owner's default matrix when no named bone,
  // weapon socket or sibling effect resolves (e.g. original blink binding b).
  if(rotation)return NATIVE_WORLD;
  actor.root.updateWorldMatrix(true,false);return actor.root.matrixWorld;
}

// Detached visual tails keep the caster's last sampled anchors, while their
// own authored node keys continue. Attack-query graphs never use this cache.
export function snapshotEffectAnchors(graph) {
  const snapshots = new Map(), copies = new Map();
  for (const node of graph.nodes) {
    const anchors = [null, null];
    for (let role = 0; role < 2; role++) {
      const binding = String(node.source.bindings[role] ?? '');
      const matrix = anchor(graph, binding, new Set(), role === 1, node);
      if (matrix && !graph.nodeMatrices.has(matrix)) {
        if (!copies.has(matrix)) copies.set(matrix, matrix.clone());
        anchors[role] = copies.get(matrix);
      }
    }
    // A name can be this node's rejected self reference but another node's
    // live sibling reference. Freeze external anchors per requester/role.
    snapshots.set(node, anchors);
  }
  return snapshots;
}
export function effectNodeMatrix(graph, node, visiting = new Set()) {
  if (node.updated) return node.valid ? node.matrix : null;
  if (visiting.has(node)) return null;
  visiting.add(node); node.updated = true; node.valid = false;
  const source = node.source, key = sampleEffectKeys(source.keys, graph.time, node.key);
  if (!key) { visiting.delete(node); return null; }
  const positionAnchor = anchor(graph, source.bindings[0], visiting, false, node), rotationAnchor = anchor(graph, source.bindings[1], visiting, true, node);
  if (!positionAnchor || !rotationAnchor) { visiting.delete(node); return null; }
  const position = new THREE.Vector3(...key.slice(1, 4)), quaternion = new THREE.Quaternion(...key.slice(4, 8)).normalize(), scale = new THREE.Vector3(...key.slice(8, 11));
  // 00582120 takes only the position anchor's origin, then copies the full
  // rotation anchor matrix. Keep its affine basis, including inherited shear.
  const origin = new THREE.Vector3().setFromMatrixPosition(positionAnchor);
  node.matrix.copy(rotationAnchor).setPosition(origin);
  // 00582d50 reads flags[3] into +0x24. 00582210 adds a zero-mode key
  // offset in native world axes; the relative mode uses the rotation basis.
  if (source.flags?.[3] === 0) {
    origin.add(position.applyMatrix4(NATIVE_WORLD));
    node.matrix.multiply(node.local.compose(new THREE.Vector3(), quaternion, scale)).setPosition(origin);
  } else node.matrix.multiply(node.local.compose(position, quaternion, scale));
  node.valid = node.matrix.elements.every(Number.isFinite); visiting.delete(node);
  return node.valid ? node.matrix : null;
}

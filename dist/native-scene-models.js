import * as THREE from './vendor/three.module.js';
import { loadGmb, loadGmc } from './gmc-loader.js';

const rootURL = new URL('./assets/original/scene-models/', import.meta.url);
const conversion = new THREE.Quaternion().setFromAxisAngle(new THREE.Vector3(1, 0, 0), -Math.PI / 2);
const inverseConversion = conversion.clone().invert();
const unitScale = new THREE.Vector3(1, 1, 1);
const vector = p => new THREE.Vector3(p[0], p[2], -p[1]);
const quaternion = p => conversion.clone().multiply(new THREE.Quaternion(p[1], p[2], p[3], p[0]).normalize()).multiply(inverseConversion);
let manifestPromise;
export function loadSceneModelManifest() { return manifestPromise ||= fetch(new URL('manifest.json', rootURL)).then(r => { if (!r.ok) throw new Error('Original cmodel manifest unavailable'); return r.json(); }).catch(error => { manifestPromise = null; throw error; }); }

export function parseRigidAnimation(text) {
  const counts = text.match(/SceneObjects\s+(\d+)\s+Dumm?eyObjects\s+(\d+)/i), timing = text.match(/FPS\s+(\d+)\s+Frames\s+(\d+)\s+Mode:\s*(\w+)/i);
  if (!counts || !timing || timing[3].toUpperCase() !== 'RIGID') throw new Error('Unsupported native FMC format');
  const objectCount = Number(counts[1]), dummyCount = Number(counts[2]), count = objectCount + dummyCount, fps = Number(timing[1]), frameCount = Number(timing[2]);
  const frames = [];
  for (const block of text.matchAll(/frame\s+(\d+)\s*\{([^}]+)\}/gi)) {
    if (Number(block[1]) !== frames.length) throw new Error('FMC frame sequence mismatch');
    const rows = [...block[2].matchAll(/\bt\s+([-+\d.eE]+)\s+([-+\d.eE]+)\s+([-+\d.eE]+)\s+q\s+([-+\d.eE]+)\s+([-+\d.eE]+)\s+([-+\d.eE]+)\s+([-+\d.eE]+)/g)].map(m => m.slice(1).map(Number));
    if (rows.length !== count || rows.some(r => r.some(n => !Number.isFinite(n)))) throw new Error('FMC transform count/value mismatch'); frames.push(rows);
  }
  if (frames.length !== frameCount || !fps) throw new Error('FMC frame count mismatch');
  return { fps, frameCount, objectCount, dummyCount, frames };
}
export function parseRigidPoses(text) {
  return [...text.matchAll(/\bpose\s*\{([^}]+)\}/gi)].map((m, id) => {
    const start = Number(m[1].match(/\bstart\s+(\d+)/i)?.[1]), end = Number(m[1].match(/\bend\s+(\d+)/i)?.[1]);
    return { id, start, end, valid: Number.isFinite(start) && Number.isFinite(end) && end >= start };
  });
}
const matrixFor = row => new THREE.Matrix4().compose(vector(row.slice(0, 3)), quaternion(row.slice(3)), unitScale);

export async function loadOriginalSceneModels(desObjects, { scale = .08, collisionMaterial } = {}) {
  const manifest = await loadSceneModelManifest(), entries = new Map(manifest.models.map(m => [m.id, m]));
  const templates = new Map(), instances = new Map(), group = new THREE.Group(); group.name = '原版 DES cmodel 实例'; group.userData.nativeSceneModels = true;
  const warnings = [], requested = desObjects.filter(o => o.properties?.model);
  const normalize = name => String(name).replace(/"/g, '').toLowerCase();
  async function template(id) {
    if (!templates.has(id)) templates.set(id, (async () => {
      const entry = entries.get(id); if (!entry?.available) { warnings.push({ model: id, reason: entry?.unavailableReason || 'Original cmodel not extracted' }); return null; }
      if (entry.pairedModels) {
        const parts = await Promise.all(entry.pairedModels.map(template)), model = new THREE.Group(); model.name = id;
        for (const part of parts) if (part) model.add(part.model.clone(true));
        return { entry, model, animation: null, poses: [], objectNames: parts.flatMap(part => part?.objectNames || []), inverseRest: [] };
      }
      const textureMap = {}, textureAlphaMap = {};
      for (const t of entry.textures) { const url = t.url || t.frames?.[0]?.url; if (url) textureMap[normalize(t.reference)] = new URL(url, rootURL).href; if (t.alphaMask) textureAlphaMap[normalize(t.reference)] = new URL(t.alphaMask, rootURL).href; }
      const [desText, animationText, poseText] = await Promise.all([entry.description ? fetch(new URL(entry.description, rootURL)).then(r => r.text()) : '', entry.animation ? fetch(new URL(entry.animation, rootURL)).then(r => r.text()) : '', entry.poses ? fetch(new URL(entry.poses, rootURL)).then(r => r.text()) : '']);
      const modelURL = new URL(entry.model, rootURL), loader = entry.format === 'GMB' ? loadGmb : loadGmc;
      const model = await loader(modelURL.href, { scale: 1, groundZ: 0, textureMap, textureAlphaMap, texturePath: new URL('textures/', rootURL).href, skipEffects: false, unlit: true, desText, name: id, source: `local:cmodel/${id}` });
      const animation = animationText ? parseRigidAnimation(animationText) : null, poses = poseText ? parseRigidPoses(poseText) : [];
      const objectNames = entry.stats.objects.map(o => o.name), inverseRest = animation ? animation.frames[0].map(matrixFor).map(m => m.invert()) : [];
      return { entry, model, animation, poses, objectNames, inverseRest };
    })());
    return templates.get(id);
  }
  // One geometry/material copy per referenced model and map; instances share it.
  await Promise.all([...new Set(requested.map(o => normalize(o.properties.model)))].map(template));
  for (const object of requested) {
    const asset = await template(normalize(object.properties.model)); if (!asset) continue;
    const root = new THREE.Group(); root.name = object.name; root.position.copy(vector(object.position)).multiplyScalar(scale); root.quaternion.copy(quaternion(object.quaternion)); root.scale.setScalar(scale);
    const model = asset.model.clone(true); root.add(model); group.add(root);
    const attributes = { active: 1, collision: 1, interactive: 1, ...object.properties }, meshRecords = [], colliders = [];
    const instance = { name: object.name, source: object, root, model, asset, attributes, pose: 0, state: 3, frame: 0, time: 0, playing: false, loop: false, colliders, bounds: new THREE.Box3() };
    model.traverse(mesh => {
      if (!mesh.isMesh) return; const index = asset.objectNames.indexOf(mesh.name);
      mesh.matrixAutoUpdate = false; meshRecords.push({ mesh, index });
      if (mesh.userData.collidable) { const collider = new THREE.Mesh(mesh.geometry, collisionMaterial); collider.matrixAutoUpdate = false; collider.name = `${object.name}/${mesh.name}`; collider.userData.nativeSceneInstance = instance; colliders.push({ collider, mesh }); }
    });
    instance.setFrame = frame => {
      if (asset.animation) {
        const f = THREE.MathUtils.clamp(frame, 0, asset.animation.frameCount - 1), lo = Math.floor(f), hi = Math.min(lo + 1, asset.animation.frameCount - 1), t = f - lo;
        for (const { mesh, index } of meshRecords) {
          if (index < 0 || !asset.animation.frames[lo][index]) continue;
          const a = asset.animation.frames[lo][index], b = asset.animation.frames[hi][index], p = vector(a.slice(0, 3)).lerp(vector(b.slice(0, 3)), t), q = quaternion(a.slice(3)).slerp(quaternion(b.slice(3)), t);
          mesh.matrix.compose(p, q, unitScale).multiply(asset.inverseRest[index]);
        }
      }
      instance.frame = frame; root.updateMatrixWorld(true); for (const record of colliders) record.collider.matrixWorld.copy(record.mesh.matrixWorld);
    };
    instance.playPose = (id, { loop = false } = {}) => {
      const pose = asset.poses[Number(id)]; if (!pose?.valid || !asset.animation) return false;
      instance.pose = Number(id); instance.time = 0; instance.playing = pose.end > pose.start; instance.state = instance.playing ? 1 : 3; instance.loop = !!loop; instance.setFrame(pose.start); return true;
    };
    instance.setActive = active => { instance.attributes.active = Number(!!active); root.visible = !!active && !/^(0|false)$/i.test(String(instance.attributes.visible)); };
    instance.setCollision = active => { instance.attributes.collision = Number(!!active); };
    instance.playPose(0); instance.setFrame(instance.frame); instance.setActive(!/^(0|false)$/i.test(String(attributes.active))); instance.setCollision(!/^(0|false)$/i.test(String(attributes.collision)) && !/^no$/i.test(String(attributes.blockplayer)));
    instance.bounds.setFromObject(root).expandByScalar(2); instances.set(object.name.toLowerCase(), instance);
  }
  const grid = new Map(), cell = 16;
  for (const instance of instances.values()) {
    const b = instance.bounds; if (b.isEmpty()) continue;
    for (let x = Math.floor(b.min.x / cell); x <= Math.floor(b.max.x / cell); x++) for (let z = Math.floor(b.min.z / cell); z <= Math.floor(b.max.z / cell); z++) { const key = `${x},${z}`; if (!grid.has(key)) grid.set(key, []); grid.get(key).push(instance); }
  }
  return {
    group, instances, warnings, templates,
    getInstancesNear(x, z, radius = 1) {
      const found = new Set(); for (let gx = Math.floor((x - radius) / cell); gx <= Math.floor((x + radius) / cell); gx++) for (let gz = Math.floor((z - radius) / cell); gz <= Math.floor((z + radius) / cell); gz++) for (const item of grid.get(`${gx},${gz}`) || []) if (item.attributes.active !== 0 && item.attributes.collision !== 0) found.add(item);
      return [...found];
    },
    getCollidersNear(x, z, radius = 1) {
      return this.getInstancesNear(x, z, radius).flatMap(item => item.colliders.map(c => c.collider));
    },
    update(dt) {
      for (const item of instances.values()) {
        if (!item.playing || item.attributes.active === 0) continue;
        const animation = item.asset.animation, pose = item.asset.poses[item.pose]; item.time += Math.max(0, dt) * animation.fps;
        let frame = pose.start + item.time;
        if (frame > pose.end) { if (item.loop) frame = pose.start + (frame - pose.start) % (pose.end - pose.start + 1); else { frame = pose.end; item.playing = false; item.state = 3; } }
        item.setFrame(frame);
      }
    }
  };
}

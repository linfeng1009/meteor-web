import * as THREE from './vendor/three.module.js';

// Trigger identity/shape come from the original DES + GMB. This module only
// detects contact; the host decides the verified consequence of that contact.
export const NATIVE_ENVIRONMENT_PROVENANCE = Object.freeze({
  identity: 'Original DES properties.name exactly hell, matched to the same-named GMB mesh.',
  shape: 'Only verified eight-vertex, twelve-triangle closed axis-aligned boxes are enabled; other source geometry remains pending.',
  contact: 'Browser adapter: continuous world-space actor-foot segment against the original volume; no texture/color inference or invented damage constant.'
});
const axes = ['x', 'y', 'z'];
const sourceClass = value => String(value ?? '').trim().replace(/^"(.*)"$/, '$1');
const disabled = value => value === false || value === 0 || /^(0|false)$/i.test(sourceClass(value));
const finite = point => point && axes.every(axis => Number.isFinite(point[axis]));

function originalBox(mesh, epsilon) {
  const position = mesh.geometry?.getAttribute('position'), index = mesh.geometry?.index;
  if (position?.count !== 8 || index?.count !== 36) return null;
  const points = Array.from({ length: 8 }, (_, i) => new THREE.Vector3().fromBufferAttribute(position, i).applyMatrix4(mesh.matrixWorld));
  if (points.some(point => !finite(point))) return null;
  const bounds = new THREE.Box3().setFromPoints(points), size = bounds.getSize(new THREE.Vector3());
  const tolerance = Math.max(epsilon, size.length() * 1e-7);
  if (axes.some(axis => size[axis] <= tolerance)) return null;
  const corners = [];
  for (const point of points) {
    let corner = 0;
    for (let axis = 0; axis < 3; axis++) {
      const key = axes[axis];
      if (Math.abs(point[key] - bounds.min[key]) <= tolerance) continue;
      if (Math.abs(point[key] - bounds.max[key]) > tolerance) return null;
      corner |= 1 << axis;
    }
    corners.push(corner);
  }
  if (new Set(corners).size !== 8) return null;
  const sides = new Map(), edges = new Map();
  for (let offset = 0; offset < index.count; offset += 3) {
    const vertices = [0, 1, 2].map(n => index.getX(offset + n));
    if (vertices.some(i => !Number.isInteger(i) || i < 0 || i >= 8) || new Set(vertices).size !== 3) return null;
    const common = axes.map((_, axis) => axis).filter(axis => vertices.every(i => (corners[i] & (1 << axis)) === (corners[vertices[0]] & (1 << axis))));
    if (common.length !== 1) return null;
    const axis = common[0], side = axis * 2 + Number(!!(corners[vertices[0]] & (1 << axis)));
    const area = points[vertices[1]].clone().sub(points[vertices[0]]).cross(points[vertices[2]].clone().sub(points[vertices[0]])).length() / 2;
    if (area <= tolerance * tolerance) return null;
    if (!sides.has(side)) sides.set(side, []); sides.get(side).push({ vertices, area });
    for (let i = 0; i < 3; i++) { const key = [vertices[i], vertices[(i + 1) % 3]].sort((a, b) => a - b).join(':'); edges.set(key, (edges.get(key) || 0) + 1); }
  }
  if (sides.size !== 6 || [...edges.values()].some(count => count !== 2)) return null;
  for (const [side, triangles] of sides) {
    if (triangles.length !== 2 || new Set(triangles.flatMap(t => t.vertices)).size !== 4) return null;
    const other = axes.filter((_, axis) => axis !== Math.floor(side / 2)), area = size[other[0]] * size[other[1]];
    if (Math.abs(triangles.reduce((sum, t) => sum + t.area, 0) - area) > Math.max(tolerance, area * 1e-6)) return null;
  }
  return bounds;
}

function entryTime(from, to, bounds) {
  let enter = 0, leave = 1;
  for (const axis of axes) {
    const delta = to[axis] - from[axis];
    if (Math.abs(delta) < 1e-12) { if (from[axis] < bounds.min[axis] || from[axis] > bounds.max[axis]) return null; continue; }
    const first = (bounds.min[axis] - from[axis]) / delta, second = (bounds.max[axis] - from[axis]) / delta;
    enter = Math.max(enter, Math.min(first, second)); leave = Math.min(leave, Math.max(first, second));
    if (enter > leave) return null;
  }
  return enter;
}

export function createNativeEnvironment(desObjects, mapModel, { epsilon = 1e-5 } = {}) {
  const triggers = [], pending = [];
  mapModel?.updateMatrixWorld(true);
  for (const source of desObjects || []) {
    if (sourceClass(source.properties?.name) !== 'hell' || disabled(source.properties?.active) || disabled(source.properties?.interactive)) continue;
    const mesh = mapModel?.getObjectByName(source.name);
    if (!mesh?.isMesh) { pending.push({ name: source.name, type: 'hell', reason: 'Source trigger has no matching GMB mesh.' }); continue; }
    const bounds = originalBox(mesh, epsilon);
    if (!bounds) { pending.push({ name: source.name, type: 'hell', reason: 'Source trigger is not a verified eight-vertex closed axis-aligned box; no AABB fallback applied.' }); continue; }
    triggers.push({ name: source.name, type: 'hell', source, bounds, provenance: NATIVE_ENVIRONMENT_PROVENANCE });
  }
  return { triggers, pending, provenance: NATIVE_ENVIRONMENT_PROVENANCE,
    sweep(from, to = from) {
      if (!finite(from) || !finite(to)) return null;
      let earliest = null;
      for (const trigger of triggers) {
        const t = entryTime(from, to, trigger.bounds);
        if (t !== null && (!earliest || t < earliest.t)) earliest = { name: trigger.name, type: trigger.type, source: trigger.source,
          point: new THREE.Vector3(from.x, from.y, from.z).lerp(to, t), t, provenance: trigger.provenance };
      }
      return earliest;
    }
  };
}

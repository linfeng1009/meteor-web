import { Box3 } from './vendor/three.module.js';

// Only immutable map colliders belong here. Moving/disabled scene props keep
// using their existing live spatial query; exact triangle raycasts still decide hits.
export class StaticColliderIndex {
  constructor(objects, cellSize = 16) {
    this.objects = objects; this.length = objects.length; this.cellSize = cellSize;
    this.cells = new Map(); this.large = [];
    for (const object of objects) {
      const geometry = object.geometry;
      if (!geometry) { this.large.push(object); continue; }
      if (!geometry.boundingBox) geometry.computeBoundingBox();
      const box = new Box3().copy(geometry.boundingBox).applyMatrix4(object.matrixWorld);
      const x0 = Math.floor(box.min.x / cellSize), x1 = Math.floor(box.max.x / cellSize);
      const z0 = Math.floor(box.min.z / cellSize), z1 = Math.floor(box.max.z / cellSize);
      if (!Number.isFinite(x0 + x1 + z0 + z1) || (x1 - x0 + 1) * (z1 - z0 + 1) > 64) { this.large.push(object); continue; }
      for (let x = x0; x <= x1; x++) for (let z = z0; z <= z1; z++) {
        const key = `${x},${z}`; if (!this.cells.has(key)) this.cells.set(key, []);
        this.cells.get(key).push(object);
      }
    }
  }
  near(x, z, radius) {
    if (!Number.isFinite(x + z + radius) || radius < 0) return this.objects;
    const x0 = Math.floor((x - radius) / this.cellSize), x1 = Math.floor((x + radius) / this.cellSize);
    const z0 = Math.floor((z - radius) / this.cellSize), z1 = Math.floor((z + radius) / this.cellSize);
    if ((x1 - x0 + 1) * (z1 - z0 + 1) > 4096) return this.objects;
    const found = new Set(this.large);
    for (let ix = x0; ix <= x1; ix++) for (let iz = z0; iz <= z1; iz++) for (const object of this.cells.get(`${ix},${iz}`) || []) found.add(object);
    return [...found];
  }
}

import * as THREE from './vendor/three.module.js';

const ROOT = new URL('./assets/enhanced/weapons/raiden-sword/', import.meta.url);
let dataPromise;
export async function loadRaidenSwordData() {
  return dataPromise ||= Promise.all(['manifest.json', 'mesh.json'].map(async file => {
    const response = await fetch(new URL(file, ROOT));
    if (!response.ok) throw new Error(`Raiden sword asset unavailable: ${file}`);
    return response.json();
  })).then(([manifest, mesh]) => ({ manifest, mesh })).catch(error => { dataPromise = null; throw error; });
}

// A rigid visual template. Clones share owned GPU resources and contain no
// animation closures; the engine disposes the template after removing its clones.
export function createRaidenSword({ manifest, mesh }, { environment = null, textures = new Map() } = {}) {
  const group = new THREE.Group(); group.name = '雷电影佩刀';
  const geometry = new THREE.BufferGeometry();
  geometry.setAttribute('position', new THREE.Float32BufferAttribute(mesh.positions, 3));
  geometry.setAttribute('normal', new THREE.Float32BufferAttribute(mesh.normals, 3));
  geometry.setAttribute('uv', new THREE.Float32BufferAttribute(mesh.uvs, 2));
  const indices = [];
  for (let mi = 0; mi < mesh.materials.length; mi++) {
    const start = indices.length;
    for (const face of mesh.faces) if (face.material === mi) indices.push(...face.indices);
    geometry.addGroup(start, indices.length - start, mi);
  }
  geometry.setIndex(indices); geometry.computeBoundingBox(); geometry.computeBoundingSphere();
  const materials = mesh.materials.map(source => {
    const material = new THREE.MeshPhysicalMaterial({ name: source.name, color: 0xffffff,
      map: textures.get(source.texture) || null, metalness: source.metalness, roughness: source.roughness,
      emissive: source.emissive ? 0xffffff : 0x000000, emissiveMap: textures.get(source.emissive) || null,
      emissiveIntensity: source.emissiveIntensity, clearcoat: .45, clearcoatRoughness: .25,
      envMap: environment, envMapIntensity: .65, side: THREE.DoubleSide });
    return material;
  });
  const surface = new THREE.Mesh(geometry, materials); surface.name = 'raiden-sword-surface'; group.add(surface);
  group.userData = { skin: 'raiden', sourceFormat: 'PMX', sourceName: manifest.sourceName,
    vertexCount: mesh.vertexCount, triangleCount: mesh.triangleCount, attachment: manifest.attachment };
  return group;
}

export async function loadRaidenSword({ environment = null } = {}) {
  const data = await loadRaidenSwordData(), textures = new Map(), loader = new THREE.TextureLoader();
  const paths = new Set(data.mesh.materials.flatMap(material => [material.texture, material.emissive]).filter(Boolean));
  try {
    // Settle every load before cleanup, including any parallel load that fails.
    const results = await Promise.allSettled([...paths].map(async path => {
      const texture = await new Promise((resolve, reject) => loader.load(new URL(path, ROOT).href, resolve, undefined, reject));
      texture.colorSpace = THREE.SRGBColorSpace; texture.anisotropy = 4;
      texture.userData.raidenSwordOwned = true; textures.set(path, texture);
    }));
    const failed = results.find(result => result.status === 'rejected');
    if (failed) throw failed.reason;
    return createRaidenSword(data, { environment, textures });
  } catch (error) { for (const texture of textures.values()) texture.dispose(); throw error; }
}

export function disposeRaidenSword(template) {
  if (!template) return;
  const geometries = new Set(), materials = new Set(), textures = new Set();
  template.traverse(mesh => {
    if (mesh.geometry) geometries.add(mesh.geometry);
    for (const material of mesh.material ? (Array.isArray(mesh.material) ? mesh.material : [mesh.material]) : []) {
      materials.add(material);
      for (const value of Object.values(material)) if (value?.isTexture && value.userData.raidenSwordOwned) textures.add(value);
    }
  });
  template.removeFromParent();
  for (const geometry of geometries) geometry.dispose();
  for (const material of materials) material.dispose();
  for (const texture of textures) texture.dispose();
}

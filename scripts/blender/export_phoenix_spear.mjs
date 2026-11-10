// Export the runtime geometry after animating the ribbons to a reproducible pose.
import { mkdir, writeFile } from 'node:fs/promises';
import { deflateSync } from 'node:zlib';
import { createPhoenixSpear } from '../../dist/phoenix-spear.js';

const output = new URL('../../work/phoenix-spear/', import.meta.url);
await mkdir(new URL('textures/', output), { recursive: true });
const root = createPhoenixSpear();
root.userData.update(.5);
root.updateMatrixWorld(true);
const textures = [], materials = [], objects = [];
const textureIds = new Map(), materialIds = new Map();
const pending = [];
// Encode RGBA without dependencies; PNG rows start at the top, GL DataTexture
// rows at the lower-left. Preserve the source byte values exactly.
function pngRGBA(data, width, height) {
  const crc32 = bytes => {
    let crc = 0xffffffff;
    for (const byte of bytes) { crc ^= byte; for (let bit = 0; bit < 8; bit++) crc = (crc >>> 1) ^ ((crc & 1) ? 0xedb88320 : 0); }
    return (crc ^ 0xffffffff) >>> 0;
  };
  const chunk = (name, data) => {
    const type = Buffer.from(name), length = Buffer.alloc(4), checksum = Buffer.alloc(4);
    length.writeUInt32BE(data.length); checksum.writeUInt32BE(crc32(Buffer.concat([type, data])));
    return Buffer.concat([length, type, data, checksum]);
  };
  const header = Buffer.alloc(13); header.writeUInt32BE(width); header.writeUInt32BE(height, 4); header[8] = 8; header[9] = 6;
  const rows = Buffer.alloc(height * (width * 4 + 1));
  for (let row = 0; row < height; row++) rows.set(data.subarray((height - 1 - row) * width * 4, (height - row) * width * 4), row * (width * 4 + 1) + 1);
  return Buffer.concat([Buffer.from([137,80,78,71,13,10,26,10]), chunk('IHDR', header), chunk('sRGB', Buffer.from([0])), chunk('IDAT', deflateSync(rows)), chunk('IEND', Buffer.alloc(0))]);
}
function textureId(texture) {
  if (!texture?.isDataTexture) return null;
  if (textureIds.has(texture)) return textureIds.get(texture);
  const id = textures.length, image = texture.image, raw = `textures/surface-${id}.rgba`, png = `textures/surface-${id}.png`;
  textureIds.set(texture, id);
  textures.push({ id, width: image.width, height: image.height, raw, png, colorSpace: texture.colorSpace, flipY: texture.flipY, wrapS: texture.wrapS, wrapT: texture.wrapT });
  pending.push(writeFile(new URL(raw, output), image.data));
  pending.push(writeFile(new URL(png, output), pngRGBA(image.data, image.width, image.height)));
  return id;
}
function materialId(material) {
  if (materialIds.has(material)) return materialIds.get(material);
  const id = materials.length;
  materialIds.set(material, id);
  materials.push({ id, name: material.name || `Surface ${id}`, color: material.color.toArray(), metalness: material.metalness || 0, roughness: material.roughness ?? .5, clearcoat: material.clearcoat || 0, clearcoatRoughness: material.clearcoatRoughness ?? .1, opacity: material.opacity ?? 1, transparent: !!material.transparent, emissive: material.emissive?.toArray() || [0, 0, 0], emissiveIntensity: material.emissiveIntensity || 0, sheen: material.sheen || 0, sheenColor: material.sheenColor?.toArray() || [1, 1, 1], map: textureId(material.map) });
  return id;
}
root.traverse(mesh => {
  if (!mesh.isMesh || !mesh.visible) return;
  const geometry = mesh.geometry.clone();
  geometry.applyMatrix4(mesh.matrixWorld);
  const position = geometry.getAttribute('position');
  objects.push({ name: mesh.name || `Spear part ${objects.length}`, positions: Array.from(position.array), normals: geometry.getAttribute('normal') ? Array.from(geometry.getAttribute('normal').array) : null, uvs: geometry.getAttribute('uv') ? Array.from(geometry.getAttribute('uv').array) : null, indices: geometry.index ? Array.from(geometry.index.array) : Array.from({ length: position.count }, (_, i) => i), materials: (Array.isArray(mesh.material) ? mesh.material : [mesh.material]).map(materialId), groups: geometry.groups });
  geometry.dispose();
});
await Promise.all(pending);
await writeFile(new URL('mesh-parts.json', output), JSON.stringify({ name: root.name, poseTime: .5, textures, materials, objects }));
console.log(`Exported ${objects.length} mesh parts, ${materials.length} materials, ${textures.length} textures.`);

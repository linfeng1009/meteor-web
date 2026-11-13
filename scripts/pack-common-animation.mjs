import { readFile, writeFile } from 'node:fs/promises';
import { gzipSync, gunzipSync } from 'node:zlib';
import { animationPackLayout, unpackNativeAnimation } from '../dist/native-animation-pack.js';

const source = new URL('../dist/assets/original/characters/common/character.amb', import.meta.url);
const original = await readFile(source);
const { frames, stride, widths } = animationPackLayout(Uint8Array.from(original).buffer);
const packed = Buffer.alloc(original.length + 4);
packed.write('AMB1');
original.copy(packed, 4, 0, 21);
let field = 0, lane = 25;
for (const width of widths) {
  let previous = 0, lastDelta = 0;
  for (let frame = 0; frame < frames; frame++) {
    const at = 21 + frame * stride + field, index = lane + frame;
    if (width === 1) { packed[index] = original[at]; continue; }
    const value = original.readInt32LE(at);
    const delta = (value - previous) | 0, residual = (delta - lastDelta) | 0;
    const encoded = (residual << 1) ^ (residual >> 31);
    for (let byte = 0; byte < 4; byte++) packed[index + byte * frames] = encoded >>> (byte * 8);
    previous = value;
    lastDelta = delta;
  }
  field += width;
  lane += width * frames;
}
const compressed = gzipSync(packed, { level: 9 });
const decoded = unpackNativeAnimation(Uint8Array.from(gunzipSync(compressed)).buffer);
if (!original.equals(Buffer.from(decoded))) throw new Error('Packed animation differs from BANIM source');
await writeFile(new URL('character.v1.ambpack.gz', source), compressed);
console.log(`Common BANIM: ${original.length} original bytes, ${compressed.length} packed bytes, exact round trip.`);

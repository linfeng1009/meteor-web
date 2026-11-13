// Build small carousel thumbnails from the existing menu artwork.
// cwebp is only needed to regenerate these checked-in images.
import { mkdir } from 'node:fs/promises';
import { spawnSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';

const dist = new URL('../dist/', import.meta.url);
const target = new URL('assets/menu/thumbs/', dist);
await mkdir(target, { recursive: true });
for (const id of ['qiyun', 'sn06', 'sn01', 'sn10', 'sn14']) {
  const source = new URL(id === 'qiyun' ? 'assets/enhanced/maps/qiyun/preview.webp' : `assets/menu/maps/${id}.webp`, dist);
  const result = spawnSync('cwebp', ['-quiet', '-q', '65', '-resize', '144', '0', fileURLToPath(source), '-o', fileURLToPath(new URL(id + '.webp', target))], { stdio: 'inherit' });
  if (result.error) throw result.error;
  if (result.status !== 0) throw new Error('Cannot generate thumbnail for ' + id);
}

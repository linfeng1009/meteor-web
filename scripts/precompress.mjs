#!/usr/bin/env node
// Precompress deployable assets so the server never spends CPU on zlib.
// Writes "<file>.br" (brotli q11) and "<file>.gz" next to each text asset.
// Run after any asset rebuild:  node scripts/precompress.mjs
import {readdir, stat, writeFile, readFile} from 'node:fs/promises';
import {join, extname} from 'node:path';
import {fileURLToPath} from 'node:url';
import {brotliCompress, gzip, constants as C} from 'node:zlib';
import {promisify} from 'node:util';

const brotli = promisify(brotliCompress), gzipAsync = promisify(gzip);
const ROOT = fileURLToPath(new URL('../dist/', import.meta.url));

// Same policy as the server: never re-compress already-compressed formats.
const SKIP = new Set(['.png', '.jpg', '.jpeg', '.webp', '.mp3', '.wav', '.bmp', '.gif', '.zip', '.br', '.gz', '.woff2']);
const MIN_BYTES = 4096;

async function* walk(dir) {
  for (const entry of await readdir(dir, {withFileTypes: true})) {
    const path = join(dir, entry.name);
    if (entry.isDirectory()) yield* walk(path);
    else if (entry.isFile()) yield path;
  }
}

let made = 0, skipped = 0, bytesIn = 0, bytesOut = 0;
for await (const path of walk(ROOT)) {
  const ext = extname(path).toLowerCase();
  if (SKIP.has(ext)) continue;
  const info = await stat(path);
  if (info.size < MIN_BYTES) continue;
  const brPath = path + '.br', gzPath = path + '.gz';
  let fresh = false;
  try { fresh = (await stat(brPath)).mtimeMs >= info.mtimeMs; } catch {}
  if (fresh) { skipped++; continue; }
  const source = await readFile(path);
  const [br, gz] = await Promise.all([
    brotli(source, {params: {[C.BROTLI_PARAM_QUALITY]: 11, [C.BROTLI_PARAM_SIZE_HINT]: source.length}}),
    gzipAsync(source, {level: 9}),
  ]);
  await Promise.all([writeFile(brPath, br), writeFile(gzPath, gz)]);
  made++; bytesIn += source.length; bytesOut += br.length;
  if (made % 40 === 0) process.stdout.write(`  …${made} files\n`);
}
console.log(`precompress: ${made} files written, ${skipped} already fresh`);
if (made) console.log(`  ${(bytesIn / 1e6).toFixed(1)} MB -> ${(bytesOut / 1e6).toFixed(1)} MB brotli (${Math.round(100 * bytesOut / bytesIn)}%)`);
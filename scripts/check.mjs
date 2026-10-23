import { readdir } from 'node:fs/promises';
import { spawnSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
const root = new URL('../', import.meta.url);
const modules = (await readdir(new URL('dist/', root))).filter(name => name.endsWith('.js'));
const files = ['server.mjs', ...modules.map(name => `dist/${name}`)];
for (const file of files) {
  const result = spawnSync(process.execPath, ['--check', fileURLToPath(new URL(file, root))], { stdio: 'inherit' });
  if (result.status !== 0) process.exit(result.status || 1);
}
console.log(`Syntax checked ${files.length} runtime modules.`);

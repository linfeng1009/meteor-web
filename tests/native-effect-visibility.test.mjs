import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { execFileSync } from 'node:child_process';
import { createHash } from 'node:crypto';
const root = new URL('../', import.meta.url), original = new URL('../dist/assets/original/', import.meta.url);
const python = process.platform === 'win32' ? 'python' : 'python3';

test('全部原显示开关可从材质a4重新核验，不借透明度或贴图名猜测', async () => {
  const result = JSON.parse(execFileSync(python, ['-S', 'scripts/import-effect-visibility.py', '--check'], { cwd: root, encoding: 'utf8' }));
  assert.deepEqual(result, { checked: true, hiddenNodes: 339, texturedHiddenNodes: 45 });
  const unique = new Set();
  for (const name of ['combat-vfx.json', 'rage-vfx/manifest.json', 'item-vfx.json']) {
    const manifest = JSON.parse(await readFile(new URL(name, original), 'utf8'));
    for (const definition of Object.values(manifest.effects)) {
      const raw = await readFile(new URL(definition.source, original));
      assert.equal(createHash('sha256').update(raw).digest('hex'), definition.sha256);
      for (const node of definition.nodes) {
        let cursor = node.offset + 16;
        for (let i = 0; i < 4; i++) {
          const length = raw.readUInt32LE(cursor); cursor += 4 + length;
          if (i === 0) cursor += 16;
        }
        const hidden = raw.readUInt32LE(cursor + 69) !== 0;
        assert.equal(node.hidden ?? false, hidden, `${definition.id}/${node.name}`);
        if (hidden) unique.add(`${definition.sha256}:${node.offset}`);
      }
    }
  }
  assert.equal(unique.size, 339);
});

import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { execFileSync } from 'node:child_process';
import { createHash } from 'node:crypto';
const root = new URL('../', import.meta.url), original = new URL('../dist/assets/original/', import.meta.url);
const python = process.platform === 'win32' ? 'python' : 'python3';

test('原93字节材质块的滚动速度完整提取且可只用标准库复核', async () => {
  const result = JSON.parse(execFileSync(python, ['-S', 'scripts/import-effect-uv.py', '--check'], { cwd: root, encoding: 'utf8' }));
  assert.deepEqual(result, { checked: true, scrollingNodes: 145, texturedScrollingNodes: 142 });
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
        const uv = [raw.readFloatLE(cursor + 73), raw.readFloatLE(cursor + 77)];
        if (uv.some(v => v !== 0)) {
          assert.deepEqual(node.uvSpeed, uv);
          unique.add(`${definition.sha256}:${node.offset}`);
        } else assert.equal(node.uvSpeed, undefined);
      }
    }
  }
  assert.equal(unique.size, 145);
});

test('非有限原UV速度被明确拒绝', () => {
  const code = "import pathlib,runpy,struct,tempfile;parse=runpy.run_path('scripts/import-rage-vfx.py')['read_effect'];p=pathlib.Path('dist/assets/original/sounds/definitions/pos279.ef');raw=p.read_bytes();node=next(n for n in parse(p)['nodes'] if n['name']=='Cylinder_4');cursor=node['offset']+16\nfor i in range(4):\n length=struct.unpack_from('<I',raw,cursor)[0];cursor+=4+length\n if i==0:cursor+=16\nwith tempfile.TemporaryDirectory() as temp:\n target=pathlib.Path(temp)/'test.ef'\n for delta,value in [(73,float('nan')),(77,float('inf'))]:\n  data=bytearray(raw);struct.pack_into('<f',data,cursor+delta,value);target.write_bytes(data)\n  try:parse(target)\n  except ValueError as e:assert 'Nonfinite EF UV speed' in str(e)\n  else:raise AssertionError('Accepted invalid UV speed')\nprint('rejected')";
  assert.equal(execFileSync(python, ['-S', '-c', code], { cwd: root, encoding: 'utf8' }).trim(), 'rejected');
});

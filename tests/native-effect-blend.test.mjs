import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { execFileSync } from 'node:child_process';
import { createHash } from 'node:crypto';
import * as THREE from '../dist/vendor/three.module.js';
import { configureNativeEffectBlend } from '../dist/native-rage-vfx.js';
const root = new URL('../', import.meta.url), original = new URL('../dist/assets/original/', import.meta.url);
const python = process.platform === 'win32' ? 'python' : 'python3';

test('所有原混合参数可从材质90/94/98标准库重建，原EF与其他字段不变', async () => {
  const result = JSON.parse(execFileSync(python, ['-S', 'scripts/import-effect-blend.py', '--check'], { cwd: root, encoding: 'utf8' }));
  assert.deepEqual(result, { checked: true, nodes: 2412, modes: { 0: 1101, 1: 15, 2: 9, 3: 499, 4: 788 } });
  const unique = new Set();
  for (const name of ['combat-vfx.json', 'rage-vfx/manifest.json', 'item-vfx.json']) {
    const manifest = JSON.parse(await readFile(new URL(name, original), 'utf8'));
    for (const definition of Object.values(manifest.effects)) {
      const raw = await readFile(new URL(definition.source, original));
      assert.equal(createHash('sha256').update(raw).digest('hex'), definition.sha256);
      for (const node of definition.nodes) {
        let cursor = node.offset + 16;
        for (let i = 0; i < 4; i++) {
          cursor += 4 + raw.readUInt32LE(cursor); if (i === 0) cursor += 16;
        }
        assert.deepEqual(node.blend, [raw.readUInt32LE(cursor + 81), raw.readUInt32LE(cursor + 85), raw.readUInt32LE(cursor + 89)]);
        unique.add(`${definition.sha256}:${node.offset}`);
      }
    }
  }
  assert.equal(unique.size, 2412);
});

const factors = [THREE.OneFactor, THREE.ZeroFactor, THREE.SrcColorFactor, THREE.OneMinusSrcColorFactor,
  THREE.SrcAlphaFactor, THREE.OneMinusSrcAlphaFactor, THREE.DstColorFactor, THREE.OneMinusDstColorFactor, THREE.DstAlphaFactor, THREE.OneMinusDstAlphaFactor];
test('十个自定义因子遵循原文件索引，固定模式忽略未使用的因子字', () => {
  const material = new THREE.MeshBasicMaterial({ transparent: true });
  try {
    for (let a = 0; a < 10; a++) for (let b = 0; b < 10; b++) {
      configureNativeEffectBlend(material, [4, a, b]);
      assert.equal(material.blending, THREE.CustomBlending); assert.equal(material.blendEquation, THREE.AddEquation);
      assert.equal(material.blendSrc, factors[a]); assert.equal(material.blendDst, factors[b]);
      assert.equal(material.blendSrcAlpha, null); assert.equal(material.blendDstAlpha, null);
    }
    configureNativeEffectBlend(material, [1, 999, 999]);
    assert.equal(material.blendSrc, THREE.SrcColorFactor); assert.equal(material.blendDst, THREE.OneFactor);
    assert.throws(() => configureNativeEffectBlend(material, [4, 10, 0]), /Unverified/);
    assert.throws(() => configureNativeEffectBlend(material, [4, 0, -1]), /Unverified/);
    assert.throws(() => configureNativeEffectBlend(material, [5, 0, 0]), /Unverified/);
  } finally { material.dispose(); }
});

function factor(value, s, d, channel) {
  const map = new Map([[THREE.OneFactor, 1], [THREE.ZeroFactor, 0], [THREE.SrcColorFactor, s[channel]], [THREE.OneMinusSrcColorFactor, 1 - s[channel]],
    [THREE.DstColorFactor, d[channel]], [THREE.OneMinusDstColorFactor, 1 - d[channel]], [THREE.SrcAlphaFactor, s[3]], [THREE.OneMinusSrcAlphaFactor, 1 - s[3]],
    [THREE.DstAlphaFactor, d[3]], [THREE.OneMinusDstAlphaFactor, 1 - d[3]]]);
  return map.get(value);
}
test('五种原混合公式有不同RGBA结果，减暗及颜色叠加不依赖源透明度', () => {
  const source = [.2, .4, .6, .25], destination = [.7, .5, .3, .8];
  const cases = [
    [[0, 0, 1], [.2, .4, .6, .25], false],
    [[1, 4, 0], [.74, .66, .66, .8625], false],
    [[2, 1, 3], [.56, .3, .12, .6], false],
    [[3, 4, 5], [.575, .475, .375, .6625], true],
    [[4, 4, 0], [.75, .6, .45, .8625], true]
  ];
  for (const [blend, expected, alphaGate] of cases) {
    const material = new THREE.MeshBasicMaterial({ transparent: true });
    try {
      assert.equal(configureNativeEffectBlend(material, blend), alphaGate);
      const actual = material.blending === THREE.NoBlending ? source : source.map((v, i) => v * factor(material.blendSrc, source, destination, i) + destination[i] * factor(material.blendDst, source, destination, i));
      for (let i = 0; i < 4; i++) assert.ok(Math.abs(actual[i] - expected[i]) < 1e-10, `mode${blend[0]} channel${i}`);
    } finally { material.dispose(); }
  }
});

test('未知原混合模式与自定义因子被拒绝，不猜测叠加方式', () => {
  const code = "import pathlib,runpy,struct,tempfile;parse=runpy.run_path('scripts/import-rage-vfx.py')['read_effect'];p=pathlib.Path('dist/assets/original/sounds/definitions/pos279.ef');raw=p.read_bytes();cursor=parse(p)['nodes'][0]['offset']+16\nfor i in range(4):\n length=struct.unpack_from('<I',raw,cursor)[0];cursor+=4+length\n if i==0:cursor+=16\nwith tempfile.TemporaryDirectory() as temp:\n target=pathlib.Path(temp)/'test.ef'\n for blend in [(5,0,0),(4,10,0),(4,0,10)]:\n  data=bytearray(raw);struct.pack_into('<3I',data,cursor+81,*blend);target.write_bytes(data)\n  try:parse(target)\n  except ValueError as e:assert 'Unverified EF blend' in str(e)\n  else:raise AssertionError('Accepted unverified blend')\nprint('rejected')";
  assert.equal(execFileSync(python, ['-S', '-c', code], { cwd: root, encoding: 'utf8' }).trim(), 'rejected');
});

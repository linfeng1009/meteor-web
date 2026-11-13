import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile, stat, mkdtemp, rm, writeFile } from 'node:fs/promises';
import { tmpdir } from 'node:os';
import { join } from 'node:path';
import { Writable } from 'node:stream';
import { brotliCompressSync, gzipSync, gunzipSync } from 'node:zlib';
import { unpackNativeAnimation } from '../dist/native-animation-pack.js';
import { createNetworkServer } from '../network-server.mjs';
import { MeteorGame } from '../dist/engine.js';
import * as THREE from '../dist/vendor/three.module.js';

const root = new URL('../dist/', import.meta.url);

test('lobby static imports stay independent of the 3D engine and rendering library', async () => {
  const visited = new Set();
  async function visit(url) {
    if (visited.has(url.href)) return;
    visited.add(url.href);
    assert.doesNotMatch(url.pathname, /\/(engine|native-character|menu-snapshots|qiyun-courtyard|three\.module)\.js$/);
    const source = await readFile(url, 'utf8');
    for (const match of source.matchAll(/^\s*(?:import(?!\s*\()|export\s*\{[^}]*\}\s*from)\s+[^;\n]*?['"](\.[^'"]+\.js)['"]/gm)) {
      await visit(new URL(match[1], url));
    }
  }
  await visit(new URL('app.js', root));
  const html = await readFile(new URL('index.html', root), 'utf8');
  assert.match(html, /<div id="load-screen" class="hidden">/);
  assert.match(html, /id="start-low-bandwidth"/);
});

test('packed shared motion is byte-identical to the original and smaller than both existing sidecars', async () => {
  const base = new URL('assets/original/characters/common/', root);
  const [original, packed, brotli, gzip] = await Promise.all([
    readFile(new URL('character.amb', base)), readFile(new URL('character.v1.ambpack.gz', base)),
    stat(new URL('character.amb.br', base)), stat(new URL('character.amb.gz', base))
  ]);
  const expanded = gunzipSync(packed);
  const decoded = unpackNativeAnimation(Uint8Array.from(expanded).buffer);
  assert.ok(original.equals(Buffer.from(decoded)));
  assert.ok(packed.length < brotli.size && packed.length < gzip.size);
  assert.throws(() => unpackNativeAnimation(Uint8Array.from(expanded.subarray(0, -1)).buffer), /dimensions/);
});

test('static responses keep Brotli, gzip and raw caches separate and honor disabled encodings', async () => {
  const folder = await mkdtemp(join(tmpdir(), 'meteor-static-'));
  const bytes = Buffer.from('Meteor binary geometry '.repeat(250));
  await writeFile(join(folder, 'geometry.bin'), bytes);
  const br = brotliCompressSync(bytes), gz = gzipSync(bytes);
  await writeFile(join(folder, 'geometry.bin.br'), br);
  await writeFile(join(folder, 'geometry.bin.gz'), gz);
  const server = createNetworkServer({ root: folder });
  try {
    const handler = server.listeners('request')[0];
    const request = async (encoding, headers = {}, method = 'GET') => {
      const chunks = [];
      const response = new Writable({ write(chunk, _, done) { chunks.push(chunk); done(); } });
      response.writeHead = (status, headers) => {
        response.status = status;
        response.headers = Object.fromEntries(Object.entries(headers).map(([key, value]) => [key.toLowerCase(), value]));
        response.headersSent = true;
      };
      await handler({ url: '/geometry.bin', method, headers: {
        'accept-encoding': encoding, ...headers
      } }, response);
      return { status: response.status, headers: response.headers, body: Buffer.concat(chunks) };
    };
    const compressed = await request('gzip, br');
    const zipped = await request('br;q=0, gzip');
    const plain = await request('br;q=0, gzip;q=0');
    assert.equal(compressed.headers['content-encoding'], 'br');
    assert.equal(zipped.headers['content-encoding'], 'gzip');
    assert.equal(plain.headers['content-encoding'], undefined);
    assert.deepEqual(compressed.body, br);
    assert.deepEqual(zipped.body, gz);
    assert.deepEqual(plain.body, bytes);
    for (const response of [compressed, zipped, plain]) assert.equal(response.headers.vary, 'Accept-Encoding');
    const cached = await request('br', { 'if-none-match': compressed.headers.etag });
    assert.equal(cached.status, 304);
    assert.equal(cached.headers.vary, 'Accept-Encoding');
    assert.equal((await request('gzip', { 'if-none-match': compressed.headers.etag })).status, 200);
    const head = await request('br', {}, 'HEAD');
    assert.equal(Number(head.headers['content-length']), br.length);
    assert.equal(head.body.length, 0);
  } finally {
    await rm(folder, { recursive: true, force: true });
  }
});

test('cold lightweight training loads its selected map and original cast through start()', async () => {
  const originalFetch = globalThis.fetch, originalLoad = THREE.TextureLoader.prototype.load;
  const paths = new Set();
  const record = input => {
    const url = new URL(input, root);
    paths.add(url.href.slice(root.href.length));
    return url;
  };
  globalThis.fetch = async input => {
    const url = record(input);
    try { return new Response(await readFile(url)); }
    catch { return new Response(null, { status: 404 }); }
  };
  THREE.TextureLoader.prototype.load = function (url, onLoad) {
    record(url);
    const texture = new THREE.Texture();
    onLoad?.(texture);
    return texture;
  };
  const game = Object.assign(Object.create(MeteorGame.prototype), {
    scene: new THREE.Scene(), camera: new THREE.PerspectiveCamera(), cameraTarget: new THREE.Vector3(),
    raycaster: new THREE.Raycaster(), renderer: { shadowMap: {} }, baseLights: [],
    map: 'sifang', weapon: 'sword', swordStyle: 'original', characterId: 0, characterAppearance: 'original',
    eagerSwordVariants: false, keys: new Set(), enemies: [], effects: [],
    mapCache: new Map(), mapData: new Map(), pendingMaps: new Set(), weaponCache: new Map(),
    mapRequest: 0, sessionRequest: 0, characterRequest: 0, actorSerial: 0,
    hostPhysics: { speed: 8, gravity: 34, jumpVelocity: 12, radius: .4, step: .55 },
    collisionMaterial: new THREE.MeshBasicMaterial({ side: THREE.DoubleSide }),
    onUpdate() {}, onEvent() {}, _nameplate() {}, _unlockAudio() {}, _tickCamera() {}
  });
  try {
    game.scene.background = new THREE.Color();
    game._initializeProjectiles();
    game.ready = game._initialize(true);
    await game.ready;
    assert.equal(game.hero, undefined);
    assert.equal(game.currentMap, undefined);
    assert.equal([...paths].some(path => /\.(amb|gmb|gmc)$/.test(path) || path.endsWith('.ambpack.gz')), false);
    await game.start({ map: 'cave', character: 0, characterAppearance: 'liuchao', lowBandwidth: true });
    assert.equal(game.currentMap.id, 'sn01');
    assert.equal(game.hero.character.appearance, 'original');
    assert.deepEqual(game.enemies.map(actor => actor.modelId), [1, 2, 3]);
    assert.equal(game.running, true);
    assert.equal([...paths].some(path => path.includes('/sn06/') || path.startsWith('assets/enhanced/')), false);
    assert.ok(paths.has('assets/original/characters/common/character.v1.ambpack.gz'));
    assert.equal(paths.has('assets/original/characters/common/character.amb'), false);
  } finally {
    for (const actor of [game.hero, ...game.enemies]) actor?.character.dispose();
    game.rageVfx?.dispose();
    game.effectContacts?.dispose();
    game.poisonFeedback?.dispose();
    game.slowFeedback?.dispose();
    game.items?.dispose();
    for (const map of game.mapData.values()) game._disposeMap(map);
    game.collisionMaterial.dispose();
    globalThis.fetch = originalFetch;
    THREE.TextureLoader.prototype.load = originalLoad;
  }
});

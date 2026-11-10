import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { createHash } from 'node:crypto';
import { NATIVE_MISSIONS, getNativeMission } from '../dist/native-missions.js';
import { NativeScriptVM } from '../dist/native-script.js';
import { MeteorGame } from '../dist/engine.js';

const root = new URL('../dist/assets/original/', import.meta.url);
const manifest = JSON.parse(await readFile(new URL('manifest.json', root), 'utf8'));

test('available story cards match real level globals and source NPC declarations, independently of map numbering', async () => {
  for (const mission of NATIVE_MISSIONS) {
    const entry = manifest.scripts.find(s => s.source.path.toLowerCase() === mission.source.toLowerCase());
    assert.ok(entry, mission.id);
    const names = [], source = await readFile(new URL(entry.utf8, root), 'utf8');
    const vm = new NativeScriptVM({ natives: { AddNPC: name => names.push(name) } }).load(source, { file: mission.source });
    assert.equal(vm.getGlobal('PlayerHP'), mission.playerHp);
    assert.equal(vm.getGlobal('Rule'), mission.rule);
    vm.call('OnStart'); assert.equal(names.length, mission.npcCount ?? mission.enemyCount);
    assert.ok(names.every(name => manifest.scripts.some(s => s.source.path.toLowerCase() === `level/${name}.pst`)));
    assert.equal(manifest.maps.find(m => m.id === mission.mapId).name, mission.name);
  }
  const tomb = manifest.scripts.find(s => s.source.path.toLowerCase() === 'level/sn02_.pst');
  const vm = new NativeScriptVM().load(await readFile(new URL(tomb.utf8, root), 'utf8'), { file: tomb.source.path });
  assert.equal(vm.hasFunction('OnStart'), false, 'sn02 is not another source NPC mission');
  assert.equal(getNativeMission('sn02'), null);
  assert.equal(getNativeMission('cave'), getNativeMission('sn01'));
});

test('unavailable story maps fail before mutating or loading a match', async () => {
  const game = Object.create(MeteorGame.prototype); game.sessionRequest = 8;
  await assert.rejects(game.start({ mode: 'story', map: 'sn02' }), /not available/);
  assert.equal(game.sessionRequest, 8);
});

test('each available mission soundtrack is present with its original byte-copy hash', async () => {
  for (const mission of NATIVE_MISSIONS) {
    const url = `sounds/music/${mission.music}`, entry = manifest.sounds.music.find(track => track.url === url);
    assert.ok(entry, url);
    const bytes = await readFile(new URL(url, root));
    assert.equal(createHash('sha256').update(bytes).digest('hex'), entry.source.sha256);
    assert.equal(entry.source.sha256, entry.sha256); assert.equal(entry.transform, 'byte copy');
    assert.ok(manifest.assets.some(asset => asset.url === url && asset.sha256 === entry.sha256));
  }
});

import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { nativeScriptItemEffect, useNativeScriptItem, useNativeAttackItem, updateNativeScriptItems, clearNativeScriptItems } from '../dist/native-items.js';

const records = JSON.parse(await readFile(new URL('../dist/assets/original/characters/meteor-res-data.json', import.meta.url), 'utf8')).allRecords;
const items = new Map(records.filter(record => record.type === 2).map(record => [record.id, record]));
const pose = id => records.find(record => record.type === 3 && record.id === id);
const actor = () => ({ hp: 3000, maxHp: 3000, rage: 80, dead: false, scriptItems: [], activeItems: [] });

test('attack-item resolution follows original parameter16 and exact source effect data', () => {
  for (const [id, expected] of [[201, 22], [551, 22], [203, 12], [204, 12], [210, 11]]) {
    const a = actor(), effect = useNativeAttackItem(a, pose(id), items);
    assert.equal(effect.id, expected); assert.equal(effect.record, items.get(expected));
  }
  assert.equal(useNativeAttackItem(actor(), pose(200), items), null);
  assert.equal(useNativeAttackItem(actor(), pose(209), items), null, 'stat5 slow stays unsupported until its movement consumer is restored');
  assert.equal(useNativeAttackItem(actor(), { ...pose(201), type: 2 }, items), null);
  assert.equal(useNativeAttackItem(actor(), { ...pose(201), parameters: [{ words: [16, 99999, 0] }] }, items), null);
  const invalid = structuredClone(items.get(12)); invalid.effects[0].words[3] = 1;
  assert.equal(nativeScriptItemEffect(invalid), null, 'word3=2 is the poison period; word4=1 is its effect type');
});

test('气丧 immediately clamps rage to the original maximum without retaining a timed modifier', () => {
  for (const [before, expected] of [[100, 80], [20, 0], [5, 0], [0, 0]]) {
    const a = actor(); a.rage = before;
    const result = useNativeScriptItem(a, items.get(22));
    assert.equal(a.rage, expected); assert.equal(result.drained, before - expected);
    assert.deepEqual(a.scriptItems, []); assert.deepEqual(a.activeItems, []);
  }
  const a = actor(); a.nativeStats = { 7: 50 };
  useNativeScriptItem(a, items.get(22)); assert.equal(a.rage, 50, 'stat6 is bounded by effective stat7');
  a.rage = 50; useNativeScriptItem(a, items.get(22)); assert.equal(a.rage, 30, 'a later valid hit applies another immediate drain');
});

test('七星 and 蛊毒 use the source counter threshold, next native step and expiry-before-tick', () => {
  for (const [id, period, duration, count] of [[11, 3, 15, 4], [12, 2, 60, 27]]) {
    const effect = nativeScriptItemEffect(items.get(id)); assert.equal(effect.period, period); assert.equal(effect.duration, duration);
    for (const dt of [1 / 60, .1, .25]) {
      const a = actor(), ticks = []; useNativeScriptItem(a, items.get(id));
      updateNativeScriptItems(a, period - .01, event => ticks.push(event)); assert.equal(a.hp, 3000);
      updateNativeScriptItems(a, .01, event => ticks.push(event)); assert.equal(a.hp, 3000); assert.equal(ticks.length, 0);
      updateNativeScriptItems(a, .2, event => ticks.push(event)); assert.equal(a.hp, 2990); assert.equal(ticks.length, 1);
      for (let time = period + .2; time < duration - 1e-8; time += dt) updateNativeScriptItems(a, Math.min(dt, duration - time), event => ticks.push(event));
      assert.equal(a.hp, 3000 - 10 * count); assert.equal(a.scriptItems.length, 0); assert.equal(a.activeItems.length, 0);
      updateNativeScriptItems(a, 60, event => ticks.push(event)); assert.equal(ticks.length, count);
    }
  }
});

test('repeat poison hits refresh only the lifetime while preserving period progress and independent poison identities', () => {
  const a = actor(); useNativeAttackItem(a, pose(203), items); updateNativeScriptItems(a, 1.5);
  assert.equal(useNativeAttackItem(a, pose(204), items).refreshed, true);
  assert.equal(a.scriptItems[0].remaining, 60); assert.equal(a.scriptItems[0].counter, 14); assert.equal(a.activeItems.length, 1);
  updateNativeScriptItems(a, .5); assert.equal(a.hp, 3000);
  updateNativeScriptItems(a, .2); assert.equal(a.hp, 2990);
  useNativeAttackItem(a, pose(210), items); assert.equal(a.scriptItems.length, 2);
  updateNativeScriptItems(a, 3.2); assert.equal(a.hp, 2970, 'item11 and item12 each retain their own damage clock');
  clearNativeScriptItems(a); updateNativeScriptItems(a, 120); assert.equal(a.hp, 2970); assert.deepEqual(a.activeItems, []);
});

test('all actors share the game item phase and expired items cannot tick or survive reset', () => {
  const a = actor(), b = actor();
  updateNativeScriptItems(a, .1, undefined, { time: 10.1 });
  useNativeScriptItem(a, items.get(12)); useNativeScriptItem(b, items.get(12));
  updateNativeScriptItems(a, .1, undefined, { time: 10.2 }); updateNativeScriptItems(b, .1, undefined, { time: 10.2 });
  assert.equal(a.scriptItems[0].counter, 2); assert.equal(b.scriptItems[0].counter, 2);
  a.scriptItems[0].remainingTicks = 2; a.scriptItems[0].counter = 20;
  updateNativeScriptItems(a, .2, undefined, { time: 10.4 }); assert.equal(a.hp, 3000); assert.deepEqual(a.scriptItems, []);
  clearNativeScriptItems(b); useNativeScriptItem(b, items.get(12)); updateNativeScriptItems(b, .1);
  assert.equal(b.scriptItems[0].counter, 0, 'the standalone cadence remainder is cleared on restart');
});

test('source item effects reject dead, removed and disposed actors without an application', () => {
  for (const state of [{ hp: 0 }, { dead: true }, { disposed: true }, { scriptRemoved: true }]) {
    for (const id of [201, 203, 210]) {
      const a = { ...actor(), ...state }; assert.equal(useNativeAttackItem(a, pose(id), items), null);
      assert.equal(a.rage, 80); assert.deepEqual(a.scriptItems, []);
    }
  }
});

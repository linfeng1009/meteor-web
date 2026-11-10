import test from 'node:test';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { nativeScriptItemEffect, nativeMovementScale, useNativeScriptItem, updateNativeScriptItems, clearNativeScriptItems } from '../dist/native-items.js';
import { nativeEffectiveStat } from '../dist/native-combat.js';

const resources = JSON.parse(await readFile(new URL('../dist/assets/original/characters/meteor-res-data.json', import.meta.url), 'utf8'));
const item = id => resources.allRecords.find(record => record.type === 2 && record.id === id);
const actor = () => ({ hp: 3000, maxHp: 3000, dead: false, scriptItems: [], activeItems: [] });

test('story items read source lifetime, refresh mode and periodic stat effects without guessing from names', () => {
  assert.deepEqual([nativeScriptItemEffect(item(4)).value, nativeScriptItemEffect(item(4)).duration], [25, 60]);
  assert.deepEqual([nativeScriptItemEffect(item(14)).value, nativeScriptItemEffect(item(14)).period, nativeScriptItemEffect(item(14)).duration], [-10, 5, 9999.9]);
  assert.equal(nativeScriptItemEffect(item(1)), null);
  assert.equal(nativeScriptItemEffect({ ...item(14), effects: [{ ...item(14).effects[0], mode: 7 }] }), null);
});

test('嗜战 affects actual native effective attack, refreshes without stacking, and expires after60 seconds', () => {
  const a = actor(); useNativeScriptItem(a, item(4));
  assert.equal(nativeEffectiveStat(3, 110, a.activeItems), 135);
  updateNativeScriptItems(a, 40); assert.equal(useNativeScriptItem(a, item(4)).refreshed, true);
  assert.equal(a.activeItems.length, 1); assert.equal(a.scriptItems[0].remaining, 60);
  updateNativeScriptItems(a, 59.9); assert.equal(nativeEffectiveStat(3, 110, a.activeItems), 135);
  updateNativeScriptItems(a, .1); assert.equal(nativeEffectiveStat(3, 110, a.activeItems), 110); assert.equal(a.scriptItems.length, 0);
});

test('尸毒 uses the source5Hz counter-before-increment cadence across Web frame rates', () => {
  for (const dt of [1 / 60, 1 / 30, .1, .25]) {
    const a = actor(), ticks = []; useNativeScriptItem(a, item(14));
    const count = Math.round(20 / dt);
    for (let frame = 0; frame < count; frame++) { updateNativeScriptItems(a, dt, e => ticks.push(e)); if ((frame + 1) * dt < 5 - 1e-8) assert.equal(a.hp, 3000); }
    assert.equal(a.hp, 2970); assert.equal(ticks.length, 3); assert.ok(ticks.every(e => e.amount === 10));
  }
});

test('poison refresh preserves its current period and cannot underflow source HP', () => {
  const a = actor(); a.hp = 15; useNativeScriptItem(a, item(14)); updateNativeScriptItems(a, 4);
  useNativeScriptItem(a, item(14)); updateNativeScriptItems(a, 1); assert.equal(a.hp, 15, 'reaching the counter threshold does not tick in that same native step');
  updateNativeScriptItems(a, .2); assert.equal(a.hp, 5);
  updateNativeScriptItems(a, 5.2); assert.equal(a.hp, 0);
  assert.equal(useNativeScriptItem(a, item(4)), null);
});

test('restart/mission disposal clears only script-owned effects and leaves no periodic damage behind', () => {
  const a = actor(), unrelated = { type: 1, id: 999 }; a.activeItems.push(unrelated);
  useNativeScriptItem(a, item(4)); useNativeScriptItem(a, item(14)); updateNativeScriptItems(a, 4.9);
  clearNativeScriptItems(a); assert.deepEqual(a.activeItems, [unrelated]); assert.deepEqual(a.scriptItems, []);
  updateNativeScriptItems(a, 100); assert.equal(a.hp, 3000);
});

test('slow affects walking only while active and does not change any weapon family baseline speed', () => {
  const weapons = resources.allRecords.filter(record => record.type === 1);
  assert.ok(weapons.length > 12);
  for (const weaponRecord of weapons) {
    const a = { ...actor(), weaponRecord };
    assert.equal(nativeMovementScale(a), 1, weaponRecord.id);
    useNativeScriptItem(a, item(13)); assert.equal(nativeMovementScale(a), .3, weaponRecord.id);
    clearNativeScriptItems(a); assert.equal(nativeMovementScale(a), 1, weaponRecord.id);
  }
});

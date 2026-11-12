import test from 'node:test';
import assert from 'node:assert/strict';
import { NATIVE_MOVE_CATALOG, NATIVE_WEAPON_FAMILIES } from '../dist/native-move-catalog.js';
import { renderNativeMoveGuide } from '../dist/native-move-guide.js';

const guide = weapon => renderNativeMoveGuide(weapon);
function row(weapon, poseId) {
  const html = guide(weapon), id = `${weapon}-${poseId}`;
  const start = html.indexOf(`<li data-move-id="${id}"`);
  assert.ok(start >= 0, `No guide entry for ${id}`);
  return html.slice(start, html.indexOf('</li>', start) + 5);
}
const visibleText = html => html.replace(/<[^>]*>/g, '');
const command = html => visibleText(html.match(/<span class="combo-command"[^>]*><span aria-hidden="true">(.*?)<\/span><\/span>/s)?.[1] || '');

test('the actual guide renders every catalog entry exactly once and rejects unequipped families', () => {
  const ids = [];
  for (const family of NATIVE_WEAPON_FAMILIES) {
    if (!family.available) {
      assert.throws(() => guide(family.id), /No move guide/);
      continue;
    }
    const html = guide(family.id);
    ids.push(...[...html.matchAll(/<li data-move-id="([^"]+)"/g)].map(match => match[1]));
    assert.match(html, /id="guide-weapon-heading"/);
    assert.match(html, /id="combo-group-ground"/);
    if (NATIVE_MOVE_CATALOG.some(move => move.weapon === family.id && move.stance === 'air' && !move.rage)) assert.match(html, /id="combo-group-air"/);
    assert.match(html, /id="combo-group-rage"/);
  }
  assert.equal(new Set(ids).size, ids.length, 'A command must not appear in two stance groups');
  assert.deepEqual(ids.sort(), NATIVE_MOVE_CATALOG.map(move => move.id).sort());
});

test('the reported spins, multi-thrust and four melee plunges show their complete distinct commands', () => {
  for (const [weapon, poseId, expected] of [
    ['blade', 374, '←→A'], ['sword', 277, '↓↑↑A'],
    ['spear', 290, '←→A'], ['spear', 292, '←→↑A'],
    ['sword', 265, '空中 ↓A'], ['blade', 298, '空中 ↓A'],
    ['spear', 282, '空中 ↓A'], ['dagger', 252, '空中 ↓A']
  ]) assert.equal(command(row(weapon, poseId)), expected, `${weapon}/${poseId}`);
  assert.match(row('sword', 277), /连续多次突刺，可多段命中/);
  assert.match(row('blade', 374), /旋身后自动收斩/);
  assert.doesNotMatch(guide('dart'), />空中 ↓A</, 'Flying darts must not advertise a melee plunge');
});

test('rage costs and unavailable projectile specials remain visible next to their commands', () => {
  for (const move of NATIVE_MOVE_CATALOG.filter(move => move.rage)) {
    const html = row(move.weapon, move.poseId);
    assert.ok(html.includes(`怒气 ${move.rage}`), move.id);
    assert.equal(html.includes('暂不可用'), Boolean(move.pending), move.id);
    if (move.pending) assert.ok(visibleText(html).includes(move.pending), move.id);
  }
  assert.match(guide('dart'), /8 项指令/);
  assert.equal((guide('dart').match(/暂不可用/g) || []).length, 0);
  assert.match(row('dart', 209), /命中施加原钝筋：移动速度系数50%，持续15秒/);
  assert.match(row('dart', 210), /每3秒削减10气血，持续15秒/);
  assert.match(row('dart', 201), /削减敌人20怒气/);
  assert.match(row('dart', 551), /空中向四周散射/);
  assert.match(row('dart', 203), /每2秒削减10气血，持续60秒/);
  assert.match(guide('dagger'), /17 项指令/);
  assert.doesNotMatch(row('dagger', 259), /暂不可用/);
  assert.match(row('dagger', 343), /向后刺击，再接推开动作/);
  assert.equal(NATIVE_WEAPON_FAMILIES.filter(family => family.available).reduce((sum, family) => sum + (guide(family.id).match(/暂不可用/g) || []).length, 0), 4);
  assert.doesNotMatch(row('ninja',470), /暂不可用/);
  assert.match(row('hammer', 567), /增加20防御.*120秒/);
  assert.match(row('knuckle', 489), /增加40攻击.*90秒/);
  assert.match(row('qiankun', 451), /先用.*↓↓A.*拔刀式/);
  assert.match(row('sword', 560), /剑刃与两道剑气可独立命中/);
});

test('follow-up requirements are explained by move names and arrow commands are screen-reader labeled', () => {
  const followup = row('sword', 268);
  assert.equal(command(followup), '↓A↓A');
  assert.match(followup, /衔接「残泉回春」/);
  assert.match(row('spear', 283), /衔接「坠」/);
  assert.match(row('sword', 277), /aria-label="下 上 上 攻击"/);
  for (const family of NATIVE_WEAPON_FAMILIES.filter(family => family.available)) {
    assert.doesNotMatch(visibleText(guide(family.id)), /\bPOS\b|poseId|\b(?:265|342|374|375|573)\b/, family.id);
  }
});

import { getNativeMoves, NATIVE_WEAPON_FAMILIES } from './native-move-catalog.js';
import { QIANKUN_MODE_NAMES } from './native-weapon-menu.js';

const escapeText = value => String(value ?? '').replace(/[&<>"']/g, char => ({ '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;', "'": '&#39;' }[char]));
const symbols = { up: '↑', down: '↓', left: '←', right: '→', attack: 'A' };
const labels = { '↑': '上', '↓': '下', '←': '左', '→': '右', A: '攻击' };
// Explain behavior to the player without exposing source pose IDs or file syntax.
const moveHelp = {
  'dart-209': '投射命中可用，附加持续效果待补。',
  'dart-210': '命中后约每3秒削减10气血，持续15秒；再次命中刷新时长。',
  'dart-201': '向四周散射，命中削减敌人20怒气。',
  'dart-551': '空中向四周散射，命中削减敌人20怒气。',
  'dart-203': '连续施展后自动收招；命中施加蛊毒，约每2秒削减10气血，持续60秒。',
  'dagger-370': '回踢会自动衔接。',
  'dagger-257': '后续的血祭会自动衔接。',
  'dagger-258': '也可由豫让三伏自动衔接。',
  'dagger-259': '沿冲锋路径的狭窄区域命中，触发原受击动作，再自动收招。',
  'dagger-343': '向后刺击，再接推开动作；两段可独立命中。',
  'dagger-559': '近身攻击可用，远端破空弹效果待补。',
  'sword-277': '连续多次突刺，可多段命中。',
  'sword-560': '近身攻击可用，远端剑气命中待补。',
  'sword-368': '剑气可远程命中，后续招式自动衔接；起手命中削减10怒气。',
  'sword-265': '下插后自动衔接刺击。',
  'spear-562': '后续招式自动衔接。',
  'spear-293': '气罩击退周围敌人，后续冲击波自动衔接。',
  'blade-374': '旋身后自动收斩。',
  'blade-572': '旋身后自动收斩。',
  'dual-244': '连续施展后自动收招，起手命中削减10怒气。',
  'blade-310': '整套连斩自动连续施展。'
};

function commandHTML(move) {
  const text = move.command || move.input.map(key => symbols[key] || key).join('');
  const label = [...text].map(char => labels[char] || char).join(' ');
  return `<span class="combo-command" aria-label="${escapeText(label)}"><span aria-hidden="true">${[...text].map(char => labels[char] ? `<kbd>${char}</kbd>` : escapeText(char)).join('')}</span></span>`;
}

function moveHTML(move, moves) {
  const previousNames = (move.continuationOf || []).map(id => moves.find(previous => previous.poseId === id)?.name).filter(Boolean);
  const help = [move.weaponMode ? `${QIANKUN_MODE_NAMES[move.weaponMode]}下施展。` : '', previousNames.length ? `衔接「${previousNames.join('」或「')}」。` : '', move.help || moveHelp[move.id], move.pending].filter(Boolean).join(' ');
  return `<li data-move-id="${escapeText(move.id)}"${move.pending ? ' class="combo-pending"' : ''}><div class="combo-move-title"><strong>${escapeText(move.name)}</strong>${move.rage ? `<span class="combo-rage">怒气 ${move.rage}</span>` : ''}${move.pending ? '<span class="combo-status">暂不可用</span>' : ''}</div>${commandHTML(move)}${help ? `<p>${escapeText(help)}</p>` : ''}</li>`;
}

export function renderNativeMoveGuide(weapon) {
  const family = NATIVE_WEAPON_FAMILIES.find(family => family.id === weapon && family.available);
  if (!family) throw new Error(`No move guide for ${weapon}`);
  const moves = getNativeMoves(weapon), available = moves.filter(move => !move.pending).length;
  const groups = [
    ['ground', '地面招式', '按顺序连续输入', moves.filter(move => move.stance === 'ground' && !move.rage)],
    ['air', '空中招式', '先跃起，再输入', moves.filter(move => move.stance === 'air' && !move.rage)],
    ['rage', '怒气招式', '怒气满足条件后施展', moves.filter(move => move.rage > 0)]
  ];
  const count = `${moves.length} 项指令${available < moves.length ? ` · ${available} 项可用` : ''}`;
  return `<div class="combo-weapon-heading"><h3 id="guide-weapon-heading">${escapeText(family.name)}招式</h3><span>${count}</span></div>${groups.filter(([, , , entries]) => entries.length).map(([id, title, hint, entries]) => `<section class="combo-group" aria-labelledby="combo-group-${id}"><h4 id="combo-group-${id}">${title}<span>${hint}</span></h4><ul class="combo-move-list">${entries.map(move => moveHTML(move, moves)).join('')}</ul></section>`).join('')}`;
}

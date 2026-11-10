// All original action families use their own item/model/POS data. This menu
// describes player-facing controls; individual unfinished moves stay labelled
// in the move guide instead of hiding the entire weapon family.
export const NATIVE_WEAPON_MENU = Object.freeze({
  sword: { name: '长剑', glyph: '剑', motto: '剑气纵横', sourceName: '碧血剑', desc: '轻灵迅捷，攻守兼备。J 三连剑，方向接 J 施展不同剑招。' },
  blade: { name: '大刀', glyph: '刀', motto: '一刀破势', sourceName: '斩铁刀', desc: '势大力沉。J 三连斩，方向接 J 可扫、挑、劈。' },
  spear: { name: '长枪', glyph: '枪', motto: '一点寒芒', sourceName: '战戟', desc: '保持身位，以长兵制敌。J 三连刺，方向接 J 可升、打、扫。' },
  dagger: { name: '匕首', glyph: '匕', motto: '蛇吻', sourceName: '蛇吻匕首', desc: '轻巧迅疾。J 两连挥，W 接 J 开启上刺连段；钟乳洞的起始兵器。' },
  dart: { name: '飞镖', glyph: '镖', motto: '七星', sourceName: '七星飞镖', desc: 'J 投掷，Q 锁定目标。墙壁与场景物件会阻挡飞镖。' },
  dual: { name: '双刺', glyph: '刺', motto: '双手连击', sourceName: '峨嵋双刺', desc: 'J 三连击，W 接 J 上刺。飞鹏堡的起始兵器。' },
  hammer: { name: '重锤', glyph: '锤', motto: '重击', sourceName: '流星锤', desc: 'J 横扫，W 接 J 锤击，S 接 J 下击。空中 S 接 J 可重砸。' },
  musket: { name: '火铳', glyph: '铳', motto: '怒火', sourceName: '怒火铳', desc: 'J 烟声，W 接 J 焦野，S 接 J 熔铁（20 怒气）。射击会被墙壁阻挡；特殊弹道仍在补全。' },
  wheel: { name: '飞轮', glyph: '轮', motto: '旋风', sourceName: '旋风轮', desc: 'J 掷出飞轮，回收后再次出手。W 接 J 或 S 接 J 切换投掷动作；特殊轮刃仍在补全。' },
  qiankun: { name: '乾坤刀', glyph: '乾', motto: '三式变化', sourceName: '杖刀林', desc: '持刀、持枪、拔刀三式。← 接 J 转持枪，↓↓ 接 J 收刀入鞘，→ 接 J 转回持刀；收刀后进入拔刀待发姿态。' },
  knuckle: { name: '指虎', glyph: '虎', motto: '贴身短打', sourceName: '指虎林', desc: 'J 三连拳。S 接 J 扫腿，WS 接 J 靠山，SW 接 J 上勾，SWW 接 J 百烈。' },
  ninja: { name: '忍刀', glyph: '忍', motto: '刃脚并用', sourceName: '忍刀林', desc: 'J 两连踢，W 接 J 跃斩，S 接 J 横斩。空中 J 可连斩；瞬移、隐身和擒拿等特殊招仍在补全。' }
});
export const QIANKUN_MODE_NAMES = Object.freeze({ blade: '持刀式', spear: '持枪式', sheath: '拔刀式' });

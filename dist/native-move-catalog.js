// Manual commands for all twelve original weapon families.
// Directions/rage are cross-checked community reference data, NOT a recovered
// Meteor.exe recognizer. Animations, linked phases, attack windows and cancel
// permissions must still be read from the supplied P0.POS / character.act.
export const NATIVE_MOVE_SOURCES = Object.freeze([
  Object.freeze({ title: '武器招式表', url: 'https://www.lxres.com/LiuXingBiJi/1559.html', role: 'commands, follow-up prerequisites, rage requirements' }),
  Object.freeze({ title: 'Pose 动作资料表', url: 'https://www.lxres.com/LiuXingBiJi/1758.html', role: 'pose lookup, corroborated against original local POS and ACT' })
]);

export const NATIVE_WEAPON_FAMILIES = Object.freeze([
  ['dart', '飞镖', true], ['musket', '火铳', true], ['wheel', '飞轮', true],
  ['dual', '双刺', true], ['dagger', '匕首', true], ['sword', '剑', true],
  ['spear', '长枪', true], ['blade', '大刀', true], ['hammer', '重锤', true],
  ['qiankun', '乾坤刀', true], ['knuckle', '指虎', true], ['ninja', '忍刀', true]
].map(([id, name, available]) => Object.freeze({ id, name, available })));

const symbols = { up: '↑', down: '↓', left: '←', right: '→', attack: 'A' };
const directions = { U: 'up', D: 'down', L: 'left', R: 'right', A: 'attack' };
const decode = text => [...text].map(key => directions[key]);
const rows = [];
function move(weapon, poseId, keys, name, { stance = 'ground', rage = 0, continuationOf, command, alternateInputs, ...extra } = {}) {
  const input = Object.freeze(decode(keys));
  rows.push(Object.freeze({ id: `${weapon}-${poseId}`, weapon, poseId, input,
    name, stance, rage, command: command || `${stance === 'air' ? '空中 ' : ''}${input.map(key => symbols[key]).join('')}`,
    ...(continuationOf ? { continuationOf: Object.freeze(continuationOf) } : {}),
    ...(alternateInputs ? { alternateInputs: Object.freeze(alternateInputs.map(keys => Object.freeze(decode(keys)))) } : {}),
    ...extra }));
}

// 飞镖。The special EF emitters are not replaced by a fabricated melee hit.
move('dart', 200, 'A', '黑蜂针');
move('dart', 209, 'UA', '雷神锥', { help: '命中施加原钝筋：移动速度系数50%，持续15秒；可格挡，重复命中刷新。' });
move('dart', 210, 'DA', '赤练牙');
move('dart', 201, 'DUA', '八方绝', { rage: 60, notes: '原EF十二攻击球命中，存活且未格挡的目标在受击加怒后削减20怒；人物接触体与时钟为Web适配。' });
move('dart', 203, 'DUUA', '落樱雪', { rage: 100, notes: '原203→204→205→329攻击与收招；命中施加原item12蛊毒，每2秒损失10气血、持续60秒，重复命中刷新时长。计时为Web适配。' });
move('dart', 202, 'A', '黑蜂针', { stance: 'air' });
move('dart', 214, 'UA', '空踢', { stance: 'air' });
move('dart', 551, 'DUA', '八方绝', { stance: 'air', rage: 60, notes: '使用独立原EF与攻击窗，命中削减20怒并自动接211；正常起跳施展，人物接触体与时钟为Web适配。' });

// 匕首。Up+A is a separate chain, not the third/fourth plain-A hit.
move('dagger', 248, 'A', '太岁');
move('dagger', 249, 'A', '九尾', { continuationOf: [248], command: 'AA' });
move('dagger', 250, 'UA', '夜叉');
move('dagger', 251, 'UA', '旱魃', { continuationOf: [250], command: '↑A↑A', alternateInputs: ['A'] });
move('dagger', 253, 'UUA', '曹沫举顶');
move('dagger', 370, 'LA', '荆轲现匕', { notes: '原版 POS 自动衔接 371 回踢' });
move('dagger', 255, 'RA', '聂政屠犬');
move('dagger', 343, 'DA', '专诸鱼肠', { notes: '原骨骼与AttackBox共同判定第一段，第二段按独立effect窗推开；原粒子发射器仍待恢复' });
move('dagger', 257, 'DUA', '豫让三伏', { notes: '原版 POS 自动衔接 258 血祭' });
move('dagger', 558, 'DDA', '暗犽', { rage: 60 });
move('dagger', 259, 'DUUA', '阎罗', { rage: 100, notes: '原effect攻击盒命中，进入109受击；自动接349收招。粒子视觉与精确人物接触体仍待恢复。' });
move('dagger', 245, 'A', '姑获', { stance: 'air' });
move('dagger', 246, 'A', '奔云', { stance: 'air', continuationOf: [245], command: '空中 AA' });
move('dagger', 247, 'A', '鹏翼', { stance: 'air', continuationOf: [246], command: '空中 AAA' });
move('dagger', 252, 'DA', '罗刹', { stance: 'air' });
move('dagger', 256, 'UDA', '鬼弹', { stance: 'air' });
move('dagger', 559, 'DDA', '降神', { stance: 'air', rage: 60, notes: '原动作及骨骼攻击窗；破空弹远端命中仍待恢复' });

// 轻剑。277 is a free multi-thrust move; it must not be treated as a rage move.
move('sword', 262, 'A', '乱草');
move('sword', 263, 'A', '巧篆', { continuationOf: [262], command: 'AA' });
move('sword', 264, 'A', '重隶', { continuationOf: [263], command: 'AAA' });
move('sword', 266, 'UA', '残日红江');
move('sword', 267, 'DA', '残泉回春');
move('sword', 268, 'DA', '风残草尽', { continuationOf: [267], command: '↓A↓A', alternateInputs: ['A'] });
move('sword', 269, 'LA', '烛举焰残');
move('sword', 270, 'RA', '枯鹰残木');
move('sword', 271, 'DDA', '雀置喙');
move('sword', 272, 'DUA', '鹤舒翎');
move('sword', 273, 'DUA', '孤雁回', { continuationOf: [272], command: '↓↑A↓↑A' });
move('sword', 274, 'UDA', '燕双飞');
move('sword', 275, 'UUA', '忌夏日');
move('sword', 276, 'UUA', '忌秋风', { continuationOf: [275], command: '↑↑A↑↑A' });
move('sword', 277, 'DUUA', '忌冬雨', { notes: '原版狂刺的多个独立攻击窗' });
move('sword', 561, 'LRA', '凤凰雏', { rage: 60 });
move('sword', 560, 'RLA', '血残气丧', { rage: 60, notes: '原动作、骨骼与PLANE攻击窗；原平面攻击盒参与剑气命中，完整粒子仍待恢复' });
move('sword', 368, 'LRUA', '凤凰羽', { rage: 100, notes: '原368→369自动衔接，原EF剑气攻击盒可远端命中；起手命中削减10怒气。PLANE判定与完整粒子仍待恢复' });
move('sword', 260, 'A', '轻行', { stance: 'air' });
move('sword', 261, 'A', '正楷', { stance: 'air', continuationOf: [260], command: '空中 AA' });
move('sword', 265, 'DA', '刻铭', { stance: 'air', notes: '265 起手自动衔接 342 下插攻击窗' });

// 长枪。1758 incorrectly repeats ←→A for 286 and 290. The two distinct
// commands here follow 1559 and the distinct original POS labels/attack types.
move('spear', 279, 'A', '刺');
move('spear', 280, 'A', '进', { continuationOf: [279], command: 'AA' });
move('spear', 281, 'A', '挑', { continuationOf: [280], command: 'AAA' });
move('spear', 284, 'DA', '打');
move('spear', 285, 'UA', '升');
move('spear', 286, 'RLA', '河东狮吼');
move('spear', 287, 'DDA', '霸王别姬');
move('spear', 288, 'DUA', '功盖三国');
move('spear', 289, 'UUA', '力拔河山');
move('spear', 290, 'LRA', '蛟龙海覆波');
move('spear', 291, 'DDUA', '虬龙扫暴阵');
move('spear', 292, 'LRUA', '应龙空翔蹴');
move('spear', 571, 'UUUA', '狂龙穿心破', { rage: 60 });
move('spear', 562, 'LRDA', '伏龙翔天破', { rage: 60, notes: '原版 POS 自动衔接 563' });
move('spear', 293, 'DUUA', '万圣龙王破', { rage: 100, notes: '原293→294气罩与冲击体按EF攻击包围盒命中，触发原击退和倒地；人物接触体及时间采样为Web适配。' });
move('spear', 338, 'A', '空踢', { stance: 'air' });
move('spear', 282, 'DA', '坠', { stance: 'air' });
move('spear', 283, 'DA', '跋扈飞扬', { stance: 'air', continuationOf: [282], command: '空中 ↓A↓A', alternateInputs: ['A'] });

// 大刀。The free spin is 374→375; the 60-rage reverse command is 572→573.
// 1758 gives both the same input. 1559 distinguishes them unambiguously.
move('blade', 295, 'A', '蚀月斩');
move('blade', 296, 'A', '吞日斩', { continuationOf: [295], command: 'AA' });
move('blade', 297, 'A', '殒星斩', { continuationOf: [296], command: 'AAA' });
move('blade', 299, 'UA', '浪滔天');
move('blade', 300, 'DA', '断石危');
move('blade', 301, 'LA', '碎岸裂');
move('blade', 302, 'RA', '鲛鳞腾');
move('blade', 303, 'UUA', '单刀劈马');
move('blade', 304, 'UUA', '人仰马翻', { continuationOf: [303], command: '↑↑A↑↑A' });
move('blade', 305, 'DUA', '伯乐难寻');
move('blade', 306, 'DDA', '项背汗血');
move('blade', 307, 'DDA', '赤兔穷追', { continuationOf: [306], command: '↓↓A↓↓A' });
move('blade', 374, 'LRA', '旋风', { notes: '原版 POS 自动衔接 375 收斩' });
move('blade', 309, 'LRUA', '疾风');
move('blade', 572, 'RLA', '狂风', { rage: 60, notes: '原版 POS 自动衔接 573' });
move('blade', 565, 'DDUA', '雷斩', { rage: 60 });
move('blade', 310, 'LRDA', '腥风', { rage: 100, notes: '原版 POS 自动链 311→312→313→314→331' });
move('blade', 338, 'A', '空踢', { stance: 'air' });
move('blade', 298, 'DA', '落崖险', { stance: 'air' });

// Basic A chains are input branches, not all consecutive pose numbers.
move('dual', 230, 'A', '左扇手');
move('dual', 231, 'A', '右扇手', { continuationOf: [230], command: 'AA' });
move('dual', 232, 'A', '虎归山', { continuationOf: [231], command: 'AAA' });
move('dual', 233, 'UA', '进撵猴');
move('dual', 234, 'UA', '马分鬃', { continuationOf: [233], command: '↑A↑A', alternateInputs: ['A'] });
move('dual', 237, 'RA', '右揽鹊尾');
move('dual', 238, 'LA', '左揽鹊尾');
move('dual', 239, 'LRA', '双龙通臂掌');
move('dual', 240, 'DUA', '玉女穿梭');
move('dual', 241, 'DA', '七星踏');
move('dual', 242, 'DA', '跨虎步', { continuationOf: [241], command: '↓A↓A', alternateInputs: ['A'] });
move('dual', 243, 'UUA', '十字鞭', { notes: '以武器招式表的↑↑A为准；另一Pose表记载不同，原EXE方向识别仍待核实。' });
move('dual', 244, 'DLRA', '合太极', { rage: 100, notes: '原POS自动衔接350至364；命中施加原气绝，削减10怒气；完整粒子尚待恢复。' });
move('dual', 556, 'LRUA', '祥龙摆尾', { rage: 60 });
move('dual', 557, 'DDUA', '乘风', { rage: 100, help: '施展完成后移动速度系数150%，持续90秒；重复施展刷新时长。' });
move('dual', 226, 'A', '小狮戏珠', { stance: 'air' });
move('dual', 227, 'A', '右摆莲', { stance: 'air', continuationOf: [226], command: '空中 AA' });
move('dual', 228, 'UA', '穿云脚', { stance: 'air' });
move('dual', 229, 'UA', '单鞭腿', { stance: 'air', continuationOf: [228], command: '空中 ↑A↑A', alternateInputs: ['A'] });
move('dual', 235, 'DA', '湖探月', { stance: 'air' });
move('dual', 236, 'DA', '海底针', { stance: 'air', continuationOf: [235], command: '空中 ↓A↓A', alternateInputs: ['A'] });

move('hammer', 315, 'A', '金刚洞月');
move('hammer', 316, 'UA', '金刚抱拳');
move('hammer', 317, 'DA', '金刚拜塔');
move('hammer', 319, 'DUA', '下山虎');
move('hammer', 320, 'UUA', '墨云鹤游空');
move('hammer', 321, 'DDA', '奔雷炎华光');
move('hammer', 322, 'LRA', '双连金钟破');
move('hammer', 323, 'RLA', '三击铜鼓冲');
move('hammer', 372, 'LRDA', '伏虎腾翔跌', { notes: '原POS自动衔接373；远端冲击效果尚未恢复。' });
move('hammer', 566, 'LRUA', '焚雷震八方', { rage: 60 });
move('hammer', 567, 'DUUA', '金钟罩', { rage: 100, help: '施展完成后增加20防御，持续120秒；重复施展刷新时长。' });
move('hammer', 325, 'DDUA', '俯爆压头灯', { rage: 100, help: '腾空砸地后自动收招；冲击命中削减敌人5怒气。' });
move('hammer', 338, 'A', '空踢', { stance: 'air' });
move('hammer', 318, 'DA', '金刚叩首', { stance: 'air' });

move('musket', 206, 'A', '烟声');
move('musket', 207, 'UA', '焦野');
move('musket', 208, 'DA', '熔铁', { rage: 20 });
move('musket', 216, 'DUA', '炎狱', { rage: 60, help: '瞄准后自动发射火浪并收招。' });
move('musket', 215, 'DUUA', '焚雷', { rage: 100, help: '连续发射，可多段命中，结束后自动收招。' });

move('wheel', 218, 'A', '一念电转');
move('wheel', 220, 'UA', '十方俱灭');
move('wheel', 222, 'DA', '百里追魂');
move('wheel', 552, 'DUA', '千刀万刮', { rage: 60, help: '连续轮刃攻击，结束后自动收招。' });
move('wheel', 224, 'DUUA', '万劫千秋', { rage: 100, help: '轮刃命中施加错骨，移动速度降至30%，持续60秒。' });
move('wheel', 554, 'DUA', '夺命轮盘', { stance: 'air', rage: 60, help: '跳起后输入；命中后自动接落地收招。' });

move('knuckle', 407, 'A', '虎探爪');
move('knuckle', 408, 'A', '擘虎须', { continuationOf: [407], command: 'AA' });
move('knuckle', 409, 'A', '断虎牙', { continuationOf: [408], command: 'AAA' });
move('knuckle', 411, 'LRA', '虎爪旋破');
move('knuckle', 412, 'LLA', '左打虎', { switchesWeapon:true, help:'侧击时自动换出副兵器，可继续输入副兵器招式；没有副兵器时保留指虎。' });
move('knuckle', 413, 'RRA', '右打虎', { switchesWeapon:true, help:'侧击时自动换出副兵器，可继续输入副兵器招式；没有副兵器时保留指虎。' });
move('knuckle', 414, 'DA', '虎扫尾');
move('knuckle', 415, 'DDA', '奔虎箭疾');
move('knuckle', 416, 'LRUA', '虎啸波', { rage: 60, help: '向前发出气功波，命中后击退敌人。' });
move('knuckle', 417, 'DUA', '虎扬头');
move('knuckle', 418, 'UUA', '虎王崩击');
move('knuckle', 419, 'UDA', '猛虎靠山');
move('knuckle', 420, 'DUUA', '疯虎百烈');
move('knuckle', 489, 'DDUA', '饿虎嗜血', { rage: 100, help: '施展完成后增加40攻击，持续90秒；重复施展刷新时长。' });
move('knuckle', 421, 'LRDA', '虎王虐袭杀', { rage: 100, help: '整套拳脚与气功波自动衔接；命中削减敌人20怒气。' });
move('knuckle', 405, 'A', '跃虎脚', { stance: 'air' });
move('knuckle', 406, 'A', '飞虎脚', { stance: 'air', continuationOf: [405], command: '空中 AA' });
move('knuckle', 410, 'DA', '虎出栅', { stance: 'air' });

// The three source stances share one weapon item. Commands are selected in the
// current stance; mode changes are committed only when their source pose starts.
const qmove = (mode, poseId, keys, name, options = {}) => move('qiankun', poseId, keys, name, { weaponMode: mode, ...options });
qmove('blade', 430, 'LA', '持枪式', { changesMode: 'spear' });
qmove('blade', 431, 'DDA', '拔刀式', { changesMode: 'sheath', help: '收刀入鞘，进入拔刀待发姿态。' });
qmove('blade', 432, 'A', '裂颜击');
qmove('blade', 433, 'A', '断肩击', { continuationOf: [432], command: 'AA' });
qmove('blade', 434, 'A', '斩腰击', { continuationOf: [433], command: 'AAA' });
qmove('blade', 438, 'DA', '邪蛇');
qmove('blade', 439, 'DA', '土龙', { continuationOf: [438], alternateInputs: ['A'], command: '↓AA' });
qmove('blade', 568, 'UUA', '霸王落', { rage: 60, help: '脚踢后自动接扫刀。' });
qmove('spear', 440, 'RA', '持刀式', { changesMode: 'blade' });
qmove('spear', 441, 'DDA', '拔刀式', { changesMode: 'sheath', help: '收刀入鞘，进入拔刀待发姿态。' });
qmove('spear', 442, 'A', '劈');
qmove('spear', 443, 'UA', '勾');
qmove('spear', 444, 'UUA', '轮');
qmove('spear', 445, 'DA', '回');
qmove('spear', 570, 'DUA', '勾魂锁', { rage: 60, help: '先用←A切至持枪式，再输入↓↑A；投出刀鞘后自动收招。' });
qmove('sheath', 447, 'RA', '持刀式', { changesMode: 'blade' });
qmove('sheath', 448, 'LA', '持枪式', { changesMode: 'spear' });
qmove('sheath', 520, 'A', '破喉击');
qmove('sheath', 521, 'A', '贪噬', { continuationOf: [520], command: 'AA', help: '突刺后可再按攻击接弧月；未接招时自动收鞘。' });
qmove('sheath', 523, 'A', '弧月', { continuationOf: [521], command: 'AAA', help: '接贪噬的突刺后段施展，刀鞘随原动作飞出，再自动收鞘。' });
qmove('sheath', 449, 'DUA', '一闪');
qmove('sheath', 450, 'UDA', '一灭');
qmove('sheath', 451, 'DDUA', '死斗', { rage: 100, help: '先用↓↓A收刀入鞘，进入拔刀式后再输入↓↓↑A；整套连斩自动衔接，命中削减敌人20怒气。' });
move('qiankun', 458, 'A', '空踢', { stance: 'air' });
move('qiankun', 446, 'DA', '封灵之击', { stance: 'air' });

move('ninja', 461, 'A', '挂踢');
move('ninja', 462, 'A', '下踢', { continuationOf: [461], command: 'AA' });
move('ninja', 463, 'UA', '跃斩');
move('ninja', 464, 'DA', '横斩');
move('ninja', 466, 'UDA', '插地');
move('ninja', 467, 'UDA', '后拉', { continuationOf: [466], alternateInputs: ['A'], command: '↑↓A↑↓A' });
move('ninja', 470, 'DDUA', '夹头', { help: '按原攻击盒命中并摔飞对手，可破防；未命中时完整收招。' });
move('ninja', 471, 'DUA', '升龙脚');
move('ninja', 472, 'LRUA', '剪刀脚');
for (const [id, keys, name] of [[526, 'UUA', '前'], [527, 'RRA', '右'], [528, 'LLA', '左'], [529, 'DDA', '后']]) {
  move('ninja', id, keys, `瞬移·${name}`, { kind: 'movement', help: '沿原动作轨迹快速位移，受地形碰撞约束；可按原接招表衔接攻击。' });
  move('ninja', id + 4, keys, `空中瞬移·${name}`, { kind: 'movement', stance: 'air', help: '空中沿原动作轨迹快速位移，保留下落；可衔接空中攻击。' });
}
move('ninja', 468, 'LRUDA', '同归于尽', { rage: 50, help: '爆炸按原攻击盒判定，施展末段自身损失99999气血；可被打断，爆炸可格挡。' });
move('ninja', 535, 'LRDA', '忍法隐身', { rage: 50, help: '施展完成后隐身120秒，降低人物可见度并阻止敌人新发现；不会免疫攻击，重复施展刷新时长。' });
move('ninja', 540, 'LRA', '压制', { rage: 10, help: '起手击倒后自动踩踏、收刀；初踩期间再次输入←→A可接再踩，每次实际接招消耗10怒气。' });
move('ninja', 473, 'DUUA', '暴怒爆弹', { rage: 50, help: '释放爆弹，命中削减敌人5怒气；可接暴怒环杀。原粒子发射器仍在完善。' });
move('ninja', 474, 'DUUA', '暴怒环杀', { rage: 50, continuationOf: [473], command: '↓↑↑A↓↑↑A', help: '接在暴怒爆弹之后，环绕火柱按原轨迹判定；需另外消耗50怒气。' });
move('ninja', 478, 'A', '空中轻斩', { stance: 'air' });
move('ninja', 479, 'A', '空中连斩', { stance: 'air', continuationOf: [478], command: '空中 AA' });
move('ninja', 465, 'DA', '空中下踏', { stance: 'air' });

export const NATIVE_MOVE_CATALOG = Object.freeze(rows);
export function getNativeMoves(weapon) { return NATIVE_MOVE_CATALOG.filter(move => move.weapon === weapon); }

export const NATIVE_MOVE_LIMITATIONS = Object.freeze([
  '十二类兵器均可装备；特殊投射、擒拿、隐身和强化状态未完成的指令在招式表中单独标记。',
  '输入映射与怒气门槛来自社区招式表交叉核对；原 EXE 的方向识别容错和全部捷径条件尚未恢复。',
  '大锤、火铳、飞轮、指虎和乾坤刀的已恢复怒招支持原攻击盒及相关属性状态；完整粒子、原物理和所有附加条件尚未全部恢复。'
]);

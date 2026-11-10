import { NATIVE_APPEARANCES, NATIVE_CHARACTERS } from './native-character.js';

// Shared presentation for the lobby, HUD and workshop. Native story identities
// and character IDs remain in the original character data.
const details = Object.freeze({
  original: { name: '原版人物', shortLabel: '原版', title: '原版人物', kind: 'original' },
  hd: { name: '孟星魂', shortLabel: '高清试版', title: '孟星魂 · 高清试版', kind: 'hd', note: '本版为原模型基础上的几何与材质改良，脸部贴图使用 AI 辅助细化。尚属试作，面数增长不代表完成手工角色重制。' },
  hutao: { name: 'YS-胡桃', seal: '胡', shortLabel: 'YS-胡桃', title: 'YS-胡桃 · 模型适配', kind: 'pmx', note: '采用本地完整「胡桃喵1.0.pmx」及配套贴图。资料署名 miHoYo／观海，目录署名摸鱼大水怪。适配原版骨架；发尾已加入独立弹簧骨骼、惯性和基础身体碰撞；衣摆与表情尚未接入原模型物理和控制。' },
  raiden: { name: 'YS-影', seal: '影', shortLabel: 'YS-影', title: 'YS-影 · 模型适配', kind: 'pmx', note: '采用本地完整「礼服影.pmx」及配套贴图。改模：花咲十七夜；头部：miHoYo／ota／ash.k／manashiku，身体：miHoYo／观海子。适配《流星》动作；长发已加入独立弹簧骨骼、惯性和基础身体碰撞；礼服裙摆与表情尚未接入原模型物理和控制。' },
  emilia: { name: 'RE0-爱蜜莉雅', seal: '爱', shortLabel: 'RE0-爱蜜莉雅', title: 'RE0-爱蜜莉雅 · 模型适配', kind: 'pmx', note: '采用本地完整「Emilia_v1.pmx」及配套贴图，适配《流星》人物动作。长发已加入独立弹簧骨骼、惯性和基础身体碰撞；衣裙物理和面部表情尚未接入；原包署名 Skymoons／Elemental Craft／Kadokawa corp／chenxs（陈心舒），完整原说明保留在本地。' },
  doubao: { name: '豆包', seal: '豆', shortLabel: '豆包', title: '豆包 · 模型适配', kind: 'pmx', note: '使用项目内完整人物与原4K贴图，适配《流星》的身体动作和武器挂点，头发为轻微跟随。版权归属《豆包》；建模：sdn1111，绑定：鹿铃。衣物物理和面部表情尚未接入。' },
  springfield: { name: '春田', seal: '春', shortLabel: '春田', title: '春田 · 泳装P3', kind: 'pmx', note: '保留原模型身材比例、网格与贴图，沿用《流星》动作，刘海和长发轻微跟随；可查看原模型姿态。模型：Sunborn Network Technology；绑定修正：DesmondChan／摸鱼的可露凯。衣物物理与表情尚未接入。' }
});

export const WORKSHOP_APPEARANCES = Object.freeze(Object.keys(NATIVE_APPEARANCES).filter(id => NATIVE_APPEARANCES[id].assetPath));
export function appearanceDetails(id) {
  return details[id] || { name: NATIVE_APPEARANCES[id]?.label || '人物', shortLabel: NATIVE_APPEARANCES[id]?.label || '人物', title: NATIVE_APPEARANCES[id]?.label || '人物外观', kind: 'pmx', note: '本地模型与原版动作适配。' };
}
export function appearanceCharacterName(characterId, appearance) {
  const descriptor = NATIVE_APPEARANCES[appearance];
  return descriptor?.characterId === Number(characterId) ? appearanceDetails(appearance).name : NATIVE_CHARACTERS.find(character => character.id === Number(characterId))?.name || '江湖人物';
}
export function appearanceCharacterSeal(characterId, appearance) {
  const descriptor = NATIVE_APPEARANCES[appearance];
  return (descriptor?.characterId === Number(characterId) && appearanceDetails(appearance).seal) ||
    Array.from(appearanceCharacterName(characterId, appearance))[0];
}

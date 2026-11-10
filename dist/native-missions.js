// Available source-script missions, not the numeric map order. sn02 is the
// Qin Emperor's Tomb arena and contains no original single-player NPC script.
// Configurations are cross-checked against each original Level/snXX_.pst.
export const NATIVE_MISSIONS = Object.freeze([
  Object.freeze({ id: 'sn01', mapId: 'sn01', name: '钟乳洞', rule: 10, playerHp: 1500,
    weapon: '蛇吻匕首 · 七星飞镖', enemyCount: 3, music: 's1.mp3',
    description: '穿过洞窟石桥，迎战军枪哨兵长与两名铁枪哨兵。',
    objective: '击败洞窟中的三名守卫', objectiveType: 'eliminate',
    source: 'Level/sn01_.pst', completion: 'Rule 10 hostile-NPC completion is an explicit browser adapter.' }),
  Object.freeze({ id: 'sn14', mapId: 'sn14', name: '炎硫岛', rule: 10, playerHp: 1000,
    weapon: '碧血剑', enemyCount: 2, music: 's2.mp3', musicProvenance: 'Original local track; island mapping is a browser selection, not recovered EXE mapping',
    description: '踏上火山孤岛，迎战大刀哨兵与铁枪哨兵。',
    objective: '击败岛上的两名守卫', objectiveType: 'eliminate',
    source: 'Level/sn14_.pst', completion: 'Rule 10 hostile-NPC completion is an explicit browser adapter.' }),
  Object.freeze({ id: 'sn09', mapId: 'sn09', name: '决死阵', rule: 1, playerHp: 3000,
    weapon: '蛇吻匕首 · 七星飞镖', enemyCount: 1, npcCount: 2, music: 's1.mp3',
    musicProvenance: 'Original local track; browser selection, not recovered EXE mapping',
    description: '避开塌落石板，跃上中央石台。别击杀冷燕，与她一起撑过对峙。',
    objective: '与冷燕一起存活至剧情结束', objectiveType: 'survive', protectName: '冷燕',
    successText: '你与冷燕撑过了对峙，可以继续选择其他任务。',
    failureText: '你或冷燕未能撑过对峙。留意塌落地板，重新再试。',
    source: 'Level/sn09_.pst', completion: 'Original PST GameOver after survival dialogue; killing ColdYan fails.' }),
  Object.freeze({ id: 'sn04', mapId: 'sn04', name: '炽雪城', rule: 3, playerHp: 2000,
    weapon: '偃月枪 · 刃牙双刺', enemyCount: 7, music: 's2.mp3',
    musicProvenance: 'Original local track; browser selection, not recovered EXE mapping',
    description: '穿过风雪中的关卡，突破守军，击破敌方城门。',
    objective: '击破敌方城门（10000 耐久）', objectiveType: 'siege', targetObject: 'D_BPdoor',
    successText: '敌方城门已破，炽雪城关卡已突破。',
    failureText: '闯关失败。留意火铳兵，寻找机会攻击敌方城门。',
    source: 'Level/sn04_.pst', completion: 'Original scene D_BPdoor destruction and animation completion calls GameCallBack(end,1); interpreted as winning team.' }),
  Object.freeze({ id: 'sn15', mapId: 'sn15', name: '飞鹏堡', rule: 4, playerHp: 2500,
    weapon: '刃牙双刺 · 青牙飞镖', enemyCount: 7, npcCount: 7, music: 's2.mp3',
    musicProvenance: 'Original local track; browser selection, not recovered EXE mapping',
    description: '闯入飞鹏堡追击萧安，阻止他逃到出口。危急时，无名可能现身相助。',
    objective: '击败萧安，阻止他逃脱', objectiveType: 'assassinate', vipName: '萧安',
    successText: '萧安已被击败。可以继续选择其他任务。',
    failureText: '萧安逃脱或孟星魂倒下了。重整兵器，再试一次。',
    source: 'Level/sn15_.pst', completion: 'Original PST escape/failure; named-VIP death success is an explicit Rule4 browser adapter.' })
]);

export function getNativeMission(id) {
  return NATIVE_MISSIONS.find(mission => mission.id === (id === 'cave' ? 'sn01' : id)) || null;
}

#!/usr/bin/env python3
"""Preserve original x86 stat semantics with offsets and calculated examples.
No original executable is run. All numbers come from static disassembly + Meteor.res.
"""
import hashlib,json,struct
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
EXE=Path('/Users/dulinfeng/Downloads/流星86726/lxhdj_/Meteor.exe')
E=ROOT/'work/meteor-original/evidence'
res=json.loads((ROOT/'dist/assets/original/characters/meteor-res-data.json').read_text())
pct=struct.unpack('<f',struct.pack('<f',0.01))[0]
rows=[]
for weapon,attack,poses in [('sword',110,[262,263,264]),('spear',115,[279,280,281]),('blade',130,[295,296,297])]:
 for pose in poses:
  r=next(x for x in res['allRecords'] if x['type']==3 and x['id']==pose)
  effect=next(x for x in r['effects'] if x['statKey']==3)
  value=effect['value'];pose_attack=attack+int((value*pct-1)*attack)
  raw=max(0,int((pose_attack-15)*1.0))
  rows.append(dict(weapon=weapon,attack=attack,defense=15,pose=pose,coefficient=value,coefficientOffset=effect['valueOffset'],poseAttack=pose_attack,rawHPDamage=raw,rageGainedByVictim=(14*raw)//100))
doc={
 'case':'meteor-original','sample':str(EXE),'sha256':hashlib.sha256(EXE.read_bytes()).hexdigest(),
 'method':'Ghidra 12.1.4 decompilation with stat virtual-call prototypes recovered from ECX/stack/RET; original x86 disassembly cross-check. Original EXE not executed.',
 'statObject':{'actorOffset':'0x88','vtable':'0x5a9490','ids':{'1':'maxHP','2':'HP','3':'attack','4':'defense','5':'movement percent','6':'rage','7':'max rage'}},
 'functions':{
  '0x004d4a70':{'role':'initialize stats','proof':'fld float arg; fmul float[0x5a9bac]=1000; __ftol; insert (2,rawHP,0),(1,rawHP,0), (6,0,0),(7,100,0), (5,100,0),(3,0,0),(4,0,0)', 'formula':'rawHP=trunc(lifeRatio*1000)'},
  '0x004bf650':{'role':'level PST settings','proof':'this+0x588 assigned 1000 before optional PlayerHP override','formula':'PlayerHP default = 1000 raw units'},
  '0x004d5de0':{'vtableOffset':'0x30','role':'get underlying stat','formula':'entry.base + entry.delta; optional out pointer gets base'},
  '0x004d5e30':{'vtableOffset':'0x34','role':'get effective stat','formula':'max(0,underlying + selectedWeaponModifiers + activeItemModifiers)','modifierFilter':'effect.words[2]==statId && words[4]==-1 && (words[0]&2)!=0 && words[1]==0','mode0':'add words[6]','mode1':'add trunc((words[6]*float32(0.01)-1)*underlying)'},
  '0x004d61c0':{'vtableOffset':'0x40','role':'get pose attack','formula':'effectiveAttack + sum(poseModifiers)','mode0':'add RES effect value','mode1':'add trunc((RES effect value*float32(0.01)-1)*effectiveAttack)','criticalDisassembly':'004d6281 call getStat(3); 004d6284 store EAX at [esp+0x14]; 004d62ac PUSH EBP changes ESP by -4; 004d62f1 FIMUL [esp+0x18] therefore uses saved effective attack, not optional base-out value.'},
  '0x004d6190':{'vtableOffset':'0x3c','role':'damage before team scale','formula':'poseAttack - target.getStat(4)'},
  '0x004d5f70':{'vtableOffset':'0x38','role':'apply damage','formula':'damage=trunc((poseAttack-defense)*factor); if damage>0 target.addStat(2,-damage,0)','proof':'004d5f88 FMUL [esp+0x10]; __ftol; JLE skips; target virtual +0x2c stat2'},
  '0x004af630':{'role':'server hit event','factor':'1.0 normally; 0.2 when victim.teamMask & attacker.teamMask !=0','victimRage':'floor(14*(HPbefore-HPafter)/100)','guardBranchRage':'trunc(14*(poseAttack-defense)/500) to victim if damageBeforeScale>0 and different team; branch requires hitPacket.field10to15==0 and victim+0x20c==1','poseParameter16':'after surviving a hit, victim stats +0x48 resolves pose(type3,id) parameter16 -> item(type2,id), then server applies those item effects to victim; these effects are NOT attacker cast cost'},
  '0x004d4d30':{'role':'clamp stat adjustments','formula':'stats2 clamp 0..effectiveStat1; stats6 clamp 0..effectiveStat7; other stats lower bound0'},
 },
 'floatPercentConstant':{'va':'0x5a8410','hex':'0x3c23d70a','floatValue':pct},
 'examples':rows,
 'unresolved':['Exact original player input recognizer and direction-to-pose table','Full action trigger mapping for rage consumption events','End-to-end life_adjust config object field propagation; scalar percent initialization itself is proven at 0x004ac453'],
 'caveats':['Raw HP is the internal integer scale; do not divide damage by ten unless all HP and item values are likewise converted for presentation.','__ftol truncates toward zero; do not replace attack+trunc((coefficient*.01-1)*attack) with floor(attack*coefficient/100).','Ghidra omits x87 expressions around __ftol; use accompanying disassembly and annotated formulas.']
}
(E/'E-exe-combat-formulas.json').write_text(json.dumps(doc,ensure_ascii=False,indent=2)+'\n')
md='''# 原版 Meteor.exe 战斗数值证据\n\n样本 SHA-256：`%s`。本次只静态分析，没有执行客户端。\n\n原生角色 `+0x88` 的属性虚表为 `0x5a9490`；属性 1/2 是最大/当前 HP，3/4 是攻击/防御，6/7 是当前/最大怒气。\n\n## 可接入的精确计算\n\n1. `004d61c0`：先取有效攻击 A。姿态 RES 中的 mode=1 系数 c 产生增量 `trunc((c * float32(0.01) - 1) * A)`，加到 A。mode=0 直接相加。\n2. `004d6190`：姿态攻击减目标有效防御。\n3. `004d5f70`：`D=trunc((姿态攻击-防御)*factor)`；D>0 才扣目标 raw HP。`004af630` 给正常阵营 factor=1，同队 mask 相交 factor=0.2。\n4. 受击者怒气增加 `floor(14*(实际HP损失)/100)`。防御分支增加 `trunc(14*(姿态攻击-防御)/500)`，敌方且结果>0 才加；当前分支条件为包中特定位为0且目标 `+0x20c==1`。\n5. HP 和怒气调整由 `004d4d30` 限制在 0..各自最大值，初始最大怒气100。\n\n`004d61c0` 的 x87 基数尤其容易被反编译输出误导：`004d6284` 把有效攻击保存在 `[esp+0x14]`，`004d62ac` 的 `push ebp` 使栈移4字节，因此 `004d62f1 fimul [esp+0x18]` 仍指向有效攻击，不是 getStat 的 base-out 参数。\n\n## HP 单位\n\n`004bf650` 在查 PlayerHP 前写默认1000，只有字段存在才覆盖。`004d4a70` 用 `trunc(floatRatio*1000)` 同时初始化当前/最大HP；调用点 `004ac453` 先把整型配置乘0.01。`server.cfg life_adjust` 是百分比配置的读取语义已找到（`0045b0a0` 保存到对象+0x70），到游戏对象+0x23c的完整字段传播还需补齐，但基础默认1000已无歧义。\n\n## 附加效果不是出招消耗\n\n`004af630` 命中后以**受击者**属性接口+0x48调用 `004d5fc0(3,pose)`，解析姿态 parameter16 引用的 type2道具，再按受击者 ID 应用。因此 item21(-10怒气)、item22(-20)、item37(-5) 是命中附加效果，不能当作攻击者消费。\n\n## 普通武器对防御15的例子\n\n| 武器 | 姿态 | 攻击 | 系数 | 姿态攻击 | rawHP伤害 | 受击加怒 |\n|---|---:|---:|---:|---:|---:|---:|\n'''%doc['sha256']
for r in rows:md+='| %s | %d | %d | %d | %d | %d | %d |\n'%(r['weapon'],r['pose'],r['attack'],r['coefficient'],r['poseAttack'],r['rawHPDamage'],r['rageGainedByVictim'])
md+='\n完整结构化证据：[E-exe-combat-formulas.json](E-exe-combat-formulas.json)。函数伪代码与关键反汇编位于 [decompiled/](decompiled/)。原方向出招识别和怒气消耗事件仍在追踪，不用公开招式表替代 EXE 证据。\n'
(E/'F-exe-combat-formulas.md').write_text(md)
print(json.dumps({'evidence':str(E/'E-exe-combat-formulas.json'),'examples':rows},ensure_ascii=False))

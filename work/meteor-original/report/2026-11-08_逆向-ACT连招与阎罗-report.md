# ACT组连招与匕首阎罗

2026-11-08，本地v0.7.2，普通逆向与移植报告，`flavor=null`。

## 结果与范围

修复原ACT招式组未参与连招选择的问题。剑、枪、刀、双刺现在可按原允许列表接入同组的实际成员，保留根指令名称、排队时机及一次耗怒。匕首阎罗从禁用改为可用，使用原冲锋轨迹、effect攻击盒、109受击和349收招；目录现为196指令、166可执行入口、30项待补。全套315项通过，这不等于全部原招式效果或完整原版战斗已还原。

授权沿用[scope](../scope.md)：用户指定本地客户端的离线静态逆向、资源解析、Web移植和本地验证。原PE32/x86 Meteor.exe为1,945,600字节，SHA-256 `289afb0aa44a47921d167fc24d6d404c60d6d00c299ac27d45fc61e16231b498`；未运行、修改或上传。导入表和平台依赖沿用[E-imports](../evidence/E-imports.json)。

## ACT连接规则

原0055d020以group索引请求招式；首次起手使用组首成员。0055d130及非强制0055d020按当前姿态`+70`允许列表的原顺序，比较每个目标`pose+68 groupId`，首个匹配目标写入`+624`；0055d450按该实际成员的Action起手。之前Web只检查“前招能否连接指令根”，因此漏掉了这些原入口：

| 前招 | 指令根 | 实际允许成员 |
|---|---:|---:|
| 剑264 | 凤凰羽368 | 369 |
| 枪281 | 万圣龙王破293 | 294 |
| 刀299 | 腥风310 | 313 |
| 刀301 | 腥风310 | 312 |
| 双刺231 | 233 | 234 |

现在`parseAct`建立组映射，busy连接按原列表顺序解析实际成员；原literal `canLink`保留。`queued`记录实际姿态，`queuedMove/currentMove`保留根指令context，实际起手才扣怒，自动POS link不再次扣费。没有把同组成员任意互连，也没有把连招入口改成重放完整起手。低层`play(id)`在idle仍是直接姿态API；已核查的生产目录idle根均为原组首。

只读独立原ACT对照覆盖160组、191个源节点、43,357项请求，零差异；1,005个合法排队连接全部进入正确成员，其中136项实际成员不同于请求根，context及一次耗怒保持。另有生产输入检查从长枪AAA接入294并实际命中远端目标，未直接指定大招实际成员。

## 阎罗命中与动作

原259的Attack只检查effect，窗口9551–9553，AttackType0，TargetPose109、Move5、Value0；RES攻击修饰900%，没有本组飞镖的附加item引用。原AttackBox为BOX `[5,5,100]`，绑定d_base，键0.6367–1.0033秒；349原本没有EffectID和Attack，不能编造第二个效果。

P0的d_base在9551/9552/9553累积使宿主向前移动约2.427/4.854/7.281米，必须和效果盒变换一起计算。只固定人物根的方向探针会把盒包络误读成身前/身后范围，不能当作实战射程。生产输入S/W/W/J在5米处命中一次，夹具伤害794，显示原109反应，随后259→349收招并回到匕首站姿；没有用武器或身体命中替代effect。794是该角色/兵器/目标夹具结果，不是阎罗固定伤害。109没有112/113链接，因此没有强行改为通用倒地。

默认导入器现输出55份EF、240个纹理形状、49条纹理记录（45 PNG、4 IFL），manifest及45张PNG共46文件在隔离目录中逐字节复现。`--include-pose`仅用于额外原数据检查，不启用相应招式。八方绝仍缺item22的怒气削减消费者，落樱雪仍缺item12蛊毒应用与计时，继续禁用；没有造程序飞镖或空间吸引代替它们。

## Evidence、Finding与Path

E-AG01：[源证据索引](../evidence/E-act-groups-2026-11-08.json)，包含各静态导出、原数据、探针、失败和复现文件的SHA-256；源引用为0055d020/0055d130/0055d450及原ACT/POS/EF/RES。复现命令见下。索引的当前哈希以[验证快照](../evidence/E-validation-current.json)为准。

E-AG02：[完整TAP](../evidence/native-runtime-act-groups-2026-11-08.tap)，SHA-256 `975eeefd6e3c493f621918ce60b116891b25b1d7f90a89ac746350d8ab00c2c5`；`npm test`得到315通过、0失败/跳过/取消、48212.891459ms。

E-AG03：[语法日志](../evidence/native-act-groups-syntax-2026-11-08.log)，SHA-256 `44e9db1c9dc1dc9229a48b670a274d8b4de0ea16cbd46f0e0bfbf06da8c51332`；`npm run check`通过27运行模块。E-AG04：[资产复核](../evidence/E-asset-coverage-current.json)，SHA-256 `fe553443a8f3273473960f8d93a93cb1313ce9f7da2a147d4cb5383322ee73c7`；`python3 scripts/analysis/verify-recovered-assets.py`核验3885记录，原已声明缺项保留。

F-AG01：ACT组成员入口遗漏已修复。`severity=n/a_re`，`category=reverse_algo`，`status=validated`，`confidence=high`，`evidence_ids=[E-AG01,E-AG02]`；位置为`dist/native-combat.js`。影响为原来被拒绝的合法衔接能进入正确后段。复现原组测试及生产引擎测试；剩余边界为完整原方向识别器、选择器条件和全部耗怒触发链。

F-AG02：阎罗的原effect攻击路径已接入。字段同上，`evidence_ids=[E-AG01,E-AG02,E-AG04]`；位置为`native-move-catalog.js`、`native-effect-contacts.js`及原259/349。影响为正常输入可沿突进路径命中，随后原反应/收招。复现效果接触测试；剩余边界为人物接触体、粒子视觉、原精确物理和浏览器实战。

P-AG01，`path_type=callflow`，start为普通连击后输入大招，goal为原组成员的实际命中：①目录根指令映射原组（E-AG01/F-AG01）；②扫描前招原允许列表，选首个同组目标（E-AG01、E-AG02/F-AG01）；③在原队列时机实际起手并扣怒一次（E-AG02/F-AG01）；④读取实际成员的原POS/EF与伤害数据，进入原反应（E-AG01、E-AG02/F-AG02）。residual_risks为上述原输入、物理、状态及完整游戏边界。

```mermaid
flowchart LR
    A[前招之后输入技能] --> B[原指令组]
    B --> C[按前招允许列表顺序匹配]
    C --> D[原实际成员排队]
    D --> E[起手扣怒一次]
    E --> F[实际成员POS和EF]
    F --> G[真实伤害与原受击收招]
```

[图源](../diagrams/act-groups-2026-11-08.mmd)及[渲染日志](../evidence/act-groups-diagram-render-2026-11-08.log)保留，不声称已生成SVG。

```sh
node --test tests/native-act-group.test.mjs tests/native-effect-contacts.test.mjs
node work/combo-continuity-audit/integration-review-2026-11-08.mjs
npm test
npm run check
python3 scripts/analysis/verify-recovered-assets.py
```

## 验证与未完成项

新增7项组检查、1项阎罗和1项生产长枪衔接检查；其他专项数量与全套有重叠，不相加冒充新检查。75份源码/测试/导入脚本及5清单从全套开始到交付复核保持一致。保留了阎罗初次把固定根探针坐标当作突进目标的失败，以及旧catalog/guide断言；修正来自实际d_base轨迹和新的effect入口，不删除失败日志。

普通受击审计另确认state7来自死亡pose117，state9有死亡后等待入口，完整枚举名未定；这两项拒绝受击不能证明普通出招霸体，也未证明不存在其他保护。原掩码生产者、爆气和AI时序继续开放，未添加通用霸体。

本阶段CPU夹具暂停NPC反击/导航，未进行浏览器/GPU/触屏或人工通关；此前浏览器访问边界未绕过，无发布或上传。完整战斗还原目标保持active。时间线见[timeline](../timeline.md)，开放工单见[workitems](../workitems.md)。

- [x] 原授权、样本与导入表范围复核。
- [x] 源函数/数据、运行验证及Evidence→Finding→Path已记录。
- [x] 全套315项、27模块语法、3885资产记录与默认导入复现通过。
- [x] 失败、图源、项目内日志及时间线保留。
- [ ] 全部技能、完整原输入/物理/群战AI与人工实战还原。

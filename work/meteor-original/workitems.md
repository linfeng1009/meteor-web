# Work Items

更新日期：2026-10-26。本阶段“完成”仅指各行限定的交付范围；完整原版游戏重构仍未完成。旧阶段成果已私有发布；本轮 83 项本地集成、跳跃修复与肉包拾取尚未上传或部署。外部上传曾被自动审批拒绝，仍缺明确用户授权，不能用旧发布快照证明本轮已上线。资源导出、PST可解析、数值恢复和隔离胜利验收均不等同于全游戏行为一致或完整活AI通关。

| ID | title | role | targets | surface | status | evidence | notes |
|----|-------|------|---------|---------|--------|----------|-------|
| WI-001 | 建立本地离线授权与范围 | lead | case / local client | process | complete | [scope](scope.md)、[工具清单](tool-index-verified.md) | auth=granted；原样本只读；未运行原EXE |
| WI-002 | 全源清单、PAK识别与可复现资源导入 | quality_review | 本地资源、地图、UI、音效、脚本 | file formats | complete | [源清单](evidence/resource-inventory.json)、[版本差异](evidence/resource-source-report.md)、[发布资产校验](evidence/E-asset-coverage-current.json) | 2090源文件/28 PAK；全部22地图目录；21可用、sn22显式禁用；哈希保留 |
| WI-003 | 原版人物与共享动画格式接入 | resource_research | SKC/BNC/AMB/POS、20人物 | geometry / animation | complete | [人物清单](../../dist/assets/original/characters/manifest.json)、[当前覆盖](evidence/E-asset-coverage-current.json) | 原蒙皮与动画；不宣称所有动作行为已恢复 |
| WI-004 | 原场景模型与FMC姿态、真实几何碰撞桥 | resource_research / game_engine | GMB/GMC/DES/FMC、场景实例 | geometry / browser adapter | complete | [场景提取](evidence/E-scene-model-extraction.json)、[运行验证](evidence/E-scene-runtime-verification.json) | 114模型；原双持r/l组件别名；含动态平台；非原COB/物理完整实现 |
| WI-005 | 原兵器及RES物品/动作记录提取 | lead / resource_research | cmodel / Meteor.res | resources / stats | complete | [兵器清单](../../dist/assets/original/weapon-models/manifest.json)、[当前覆盖](evidence/E-asset-coverage-current.json) | 59物品/71模型；58物品模型可用；资源覆盖不等于全部武器行为 |
| WI-006 | EXE基础数值分支恢复及JS复核 | lead | Meteor.exe属性/HP/伤害/防御与受击加怒 | PE static analysis | complete | [公式](evidence/E-exe-combat-formulas.json)、[9组验证](evidence/E-formula-runtime-verification.json)、[报告](report/2026-10-23_逆向-MeteorEXE战斗数值-report.md) | x86汇编交叉核对；life_adjust完整传播、输入/耗怒映射保留未完成 |
| WI-007 | PST AST解析器、include与受限执行 | quality_review | 111 PST/H依赖与函数 | DSL interpreter | complete | [VM证据](evidence/E-pst-runtime.json)、[测试日志](evidence/native-mission-tests.tap) | 无eval/new Function；未知API显式错误；不是全API实现 |
| WI-008 | 钟乳洞第一关原脚本宿主适配与引擎联调 | quality_review / game_engine / lead | sn01 Level/scene/3 NPC/WP与对白UI | mission adapter | complete | [宿主证据](evidence/E-mission-host.json)、[首关验收](evidence/E-mission-cpu-acceptance.md)、[报告](report/2026-10-23_逆向-钟乳洞PST宿主-report.md) | 原1500HP/3 NPC/原武器/WP/对白/巡逻/报告；实际攻击、自然失败和重开已验收；Rule10仍为适配推断，完整活AI通关未证明 |
| WI-009 | 自动检查与有限本地浏览器交互验证 | lead / quality_review / game_engine / jump_regression | 当前Web运行目录 | validation | complete | [83项最终快照](evidence/E-validation-current.json)、[全套TAP](evidence/native-runtime-current.tap)、[跳跃证据](evidence/E-jump-follow-2026-10-26.md) | 2026-10-26最终83/83、26.87秒、11模块语法与diff检查通过；含10跳跃、9肉包、13投射、7首关验收。浏览器平地/锁定跳跃截图不等于完整通关或新版本上线 |
| WI-010 | 证据链、阶段报告、时间线、图与匿名经验记录 | quality_review / lead | work/meteor-original | documentation | complete | [数值报告](report/2026-10-23_逆向-MeteorEXE战斗数值-report.md)、[宿主报告及Mermaid](report/2026-10-23_逆向-钟乳洞PST宿主-report.md)、[journal](field-journal/2026-10-23_native-game-port.md)、[timeline](timeline.md) | 仅项目内存档；未写技能目录或外部记忆 |
| WI-011 | 2026-10-23旧阶段私有部署与运行目录比对 | lead | historical owner-private deployment | release | complete | [旧部署记录](evidence/E-web-deployment.json) | 仅旧版发布succeeded、3953运行文件零差异；线上只核验私有登录门。当前跳跃/拾取版本未部署，外部上传授权尚待明确 |
| WI-012 | 原七星基础地面/空中投射与命中生命周期 | game_engine / mission_acceptance / lead | item1 W3_0、POS200/202、手骨、sn01碰撞 | projectile adapter | complete | [投射证据](evidence/E-native-projectiles.md)、[当前验证](evidence/E-validation-current.json) | 13项回归；真实原手骨/模型/地图三发各34、桥T遮挡；长官防0每发49；飞行常数公开为Web适配，进阶动作仍属WI-023 |
| WI-013 | 首关原路径、实际伤害、结算与重开CPU验收 | mission_acceptance | 原WP9/53/80/32、三NPC、PST与真实战斗运行代码 | bounded acceptance | complete | [验收说明](evidence/E-mission-cpu-acceptance.md)、[7项TAP](evidence/mission-cpu-acceptance.tap) | 无直接改HP/dead；原路径真实步行、活敌自然失败、重开；隔离反击的匕首4000伤害/3kill/原死亡对白/唯一推断胜利。完整活AI实战胜利仍属WI-027 |
| WI-014 | 机关原伤害默认接入与最终集成验收 | lead / game_engine / quality_review | EXE事件0x1d到PST OnAttack、scene resolver与真实几何 | numeric bridge / validation | complete | [静态原参数](evidence/E-native-machine-damage.json)、[真实几何链](evidence/scene-machine-audit-2026-10-26.json)、[83项最终验证](evidence/E-validation-current.json) | 默认引擎已接createNativeSceneDamageResolver。实际sn01石块D_St20受11发各49伤害从500到-39，原破碎pose1结束state3、隐藏/关闭碰撞、激活D_itSt20并可源初始化复原；Item02未接拾取，探针不证明人物瞄准或步行路线 |
| WI-015 | 原人物就地跳跃与镜头跟随修复 | lead / jump_regression | SKC/BNC/AMB/POS151/152/180、camera、20人物层级 | animation / camera adapter | complete | [跳跃证据及对照](evidence/E-jump-follow-2026-10-26.md)、[最终TAP](evidence/native-runtime-current.tap) | 10项通过，旧版对照8失败；d_base场景额外高度约5.902m→0，原骨盆/武器挂点与raw轨迹保留；平地/锁定/移动/近墙跳跃与落地验证；P19非零BNC初值保留 |
| WI-016 | 钟乳洞原肉包恢复与拾取引擎接入 | lead / native_items | RES type2/id1 Item01、DES/PST、F/触屏、HP与HUD | bounded item adapter | complete | [原肉包证据](evidence/E-native-items-2026-10-26.md)、[83项最终TAP](evidence/native-runtime-current.tap)、[验证快照](evidence/E-validation-current.json) | 9项通过；原+300HP夹取、真实石块Item01掉落→拾取→重置、遮挡/暂停/剧情门与序列化HUD。仅sn01，演武禁用；范围/显式输入/满血保留/每局一次无计时重生属Web适配，其他物品仍未接 |
| WI-020 | 其余原剧情与完整原GameRule | team | 除sn01适配以外的关卡与规则 | gameplay | open | [宿主限制](evidence/E-mission-host.json) | 原脚本可解析不代表其他关卡能通关；超时/进度/跨关卡尚未核实 |
| WI-021 | 原输入识别与方向序列到动作、耗怒触发映射 | lead / game_engine | 输入selector、事件分支 | PE / gameplay | open | [公式未完成项](evidence/E-exe-combat-formulas.json) | 已有原动作数据，不以公开招式表代替原selector证据 |
| WI-022 | 原COB语义、物理、导航与AI完整行为 | game_engine | collision cells / movement / sight / tactics | engine | open | [宿主provenance](evidence/E-mission-host.json)、[原资源限制](evidence/E-asset-coverage-current.json) | 现用真实三角碰撞、WP寻路及明确Web参数；未声称原行为一致 |
| WI-023 | 完整原投射物、PonEF视觉与全部武器操作 | game_engine / resource_research | dart、ranged、effects、全部动作家族 | gameplay | open | [基础投射与剩余边界](evidence/E-native-projectiles.md) | 七星200/202基础飞行/遮挡/真实伤害已按WI-012完成；原飞行常数、八方手里剑、怒招、完整EF与全部武器语义仍待恢复 |
| WI-024 | 全物品效果、原接触语义与全部场景交互 | lead / game_engine | scene OnAttack / item effects | PE / gameplay | open | [机关原伤害](evidence/E-native-machine-damage.json)、[几何链](evidence/scene-machine-audit-2026-10-26.json)、[肉包范围](evidence/E-native-items-2026-10-26.md) | 原OnAttack参数与默认引擎接入按WI-014完成；sn01原Item01肉包按WI-016完成。原拾取条件/计时、其他道具效果、完整接触体/事件频率、爆炸及全部场景交互仍待验证 |
| WI-025 | 原联网协议、房间与同步 | team | network / multiplayer | protocol | open | [scope](scope.md)、[发布未核验项](evidence/E-web-deployment.json) | 本阶段未做联网协议恢复或多人同步 |
| WI-026 | 缺失/损坏源素材处理 | resource_research | sn22、w6_5及3处纹理 | resource recovery | open | [缺项研究](evidence/E-missing-models-research.json)、[覆盖清单](evidence/E-asset-coverage-current.json) | 不用原创替代品冒充原素材；sn22非有限顶点禁用 |
| WI-027 | 完整游戏移植、人工通关及原版行为对照 | team | end-to-end parity / all missions | acceptance | open | [首关CPU边界](evidence/E-mission-cpu-acceptance.md)、[本地/线上验证边界](evidence/E-web-deployment.json) | 总体目标仍未完成；首关隔离胜利不等于完整活AI通关；尚无完整人工胜利，包含登录后的线上游戏验证 |

## Coverage

- [x] 已完成源文件全量清单与当前发布资源逐条校验；缺失/损坏项明示。
- [ ] 完成所有in_scope代码与所有原游戏行为的分析（未完成，见WI-020..027）。
- [x] Critical/High候选分流：本项目为纯逆向与移植，无安全漏洞交付；不虚构漏洞等级。
- [x] 已验证发现挂接Evidence，公式静态证据与Web运行测试区分。
- [x] 原始数值与任务调用Path已在两份报告中记录。
- [x] 主要阶段与职责、复现命令、验证边界已补入timeline。
- [x] docs-generator阶段报告已生成。
- [x] 报告包含可编辑Mermaid，并注明只提供源码、未导出渲染图。
- [x] 匿名field journal已写入本项目，未写外部技能库/记忆。
- [ ] 完整游戏、所有关卡、联网及人工通关验收（未完成）。

## Refs
- skills/ops/timeline-workitem.md
- skills/ops/evidence-finding-path.md

## 2026-11-05 恢复后的阶段补录

初始化脚本曾覆盖本文件；上方恢复 Git 已存版本。本段根据仍保留的报告和验证文件重建增量，未完成项目继续开放。

| ID | 内容 | 状态 | 依据与边界 |
|---|---|---|---|
| WI-028 | 炎硫岛原任务与环境 | 阶段已验证 | evidence/E-native-island-2026-10-26.md；Rule10 为明确的 Web 完成适配 |
| WI-029 | 手搓招式、防御与进阶七星投射 | 阶段已验证 | 2026-10-29 报告与验证；完整12兵器及原 selector 仍未完成 |
| WI-030 | 受击、击倒、起身及局部打击反馈 | 阶段已验证 | 2026-10-30 报告；Web停顿与震屏不冒充原版常数 |
| WI-031 | 决死阵、飞鹏堡 | 进行中 | 11月4日有原脚本审计和部分接线；尚待真实关卡验收 |
| WI-032 | 原生动作混合与个人 POS | 进行中 | 11月5日 EXE 静态导出及代码草稿；尚未完整回归 |

## 2026-11-06 关卡阶段更新

| ID | 内容 | 状态 | 证据与边界 |
|---|---|---|---|
| WI-031 | 决死阵、飞鹏堡本地任务接入 | 阶段完成 | E-new-missions-2026-11-06.json；8项真实资产集成检查；决死阵完整CPU活AI存活，飞鹏堡胜利/逃脱/援军分别隔离验证；浏览器和完整活AI追击胜利未验收 |
| WI-032 | 原动作/个人POS/起跳运动与完整战斗还原 | 继续进行 | 原AMB起跳进入碰撞根并通过跳跃/镜头回归；骨骼过渡和个人POS草稿随全套通过。原精确物理、完整输入、全部招式效果仍未完成 |

WI-020、WI-022、WI-023、WI-024、WI-027保持开放；上述阶段完成只指本轮明确范围。UI/浏览器试玩受访问批准限制，未声称线上发布。

## 2026-11-06 战斗运动阶段更新

| ID | 内容 | 状态 | 证据与边界 |
|---|---|---|---|
| WI-033 | 原d_base轨迹、TargetMove/Value及播放边界 | 阶段已验证 | E-combat-motion-source-2026-11-06.json、234项最终TAP；原百分位消息、倍率/最低时长、墙体接线、无攻击窗运动、单帧空中保持。完整producer/旋转/原物理仍开放 |
| WI-032 | 原动作/个人POS/起跳运动与完整战斗还原 | 继续进行 | 111条可用指令自然起跳/地面输入遍历；移除额外高度。ACT续招跨落地是Web策略；方向受击/护架运动/强制受击混合/全部EF/剩余兵器与原selector继续开放 |

WI-020、WI-021、WI-022、WI-023、WI-024、WI-027保持open。已有四任务的全套回归通过，不代表其余剧情或完整还原验收完成。

## 2026-11-06 十二兵器与群战输入阶段更新

| ID | 内容 | 状态 | 证据与边界 |
|---|---|---|---|
| WI-034 | 围攻下恢复操作与十二兵器选择 | 阶段已验证 | E-twelve-weapons-2026-11-06.json；持续防御、0.3秒恢复攻击输入、自由面向与Q锁定；十二类UI/实际装备。原霸体、爆气及群战AI时序仍待核实 |
| WI-035 | 乾坤刀三架式、火铳和飞轮入口 | 阶段已验证 | 293项全套；196指令/165入口/31禁用；原POS/ACT、状态表、释放窗和伤害已接。射线及飞轮往返为Web适配，完整技能与原投射语义仍开放 |
| WI-036 | 炽雪城原城门与天气 | 阶段已验证 | 原七NPC/双兵器、10000门耐久、各阶段到pose8/state3的唯一原回调结算；127.50秒隔离接触验收，不是出生点活AI实战通关 |
| WI-024 | 全道具及场景交互 | 继续进行 | 补RES道具15/19/20及原门非阻挡交互查询；道具7/stat10消费者、完整接触和其余效果仍未恢复，炼铁狱未开放 |
| WI-020 | 其余剧情与GameRule/VIP | 继续进行 | 五项任务进入回归，四项源剧情未开放；原vip/enemyvip同队/敌队区别已发现，sn15固定萧安适配尚未完整更换 |
| WI-032 | 原动作与完整战斗还原 | 继续进行 | 十二家族、方向受击/防御过渡和部分原EF视觉通过回归；未恢复完整物理、输入识别、霸体/爆气与全部效果 |

本阶段68份代码/测试/导入脚本和5清单通过全套前后哈希复核；293/293测试、25模块语法及3885资产记录核验通过。WI-020、WI-021、WI-022、WI-023、WI-024、WI-027仍保持open，完整移植目标未完成。原未播种钟乳洞停滞未解释；无新浏览器/人工通关/线上发布。

## 2026-11-07 原EF效果命中更新

| ID | 内容 | 状态 | 证据与边界 |
|---|---|---|---|
| WI-037 | 长枪气罩、冲击波与原EF攻击包围盒 | 阶段已验证 | E-effect-contacts-2026-11-07.json；11项新增、306项最终全套。原球/柱/盒A/a节点、POS effect窗口、方向反应与AMB击退/倒地/起身接通；共享变换与去重、EF秒时钟、底端柱体、粗时间步和生命周期通过。Web人物接触体/插值/采样仍有边界 |
| WI-023 | 全部投射物与EF | 继续进行 | 普通视觉节点不制造伤害；当前支持原包围盒分支，不等同完整粒子/模型/路径/其他形状。效果对场景机关、原穿墙和全局时序仍未恢复 |
| WI-032 | 原动作与完整战斗还原 | 继续进行 | 气罩能驱动实际原受击轨迹；原霸体/爆气、完整输入、附加状态及群战AI仍开放。暂停按用户要求执行，恢复后继续原目标 |

同期工作区的无限怒气调试开关、UI和测试已保留并重新全套验证；关闭后原门槛和扣怒继续通过。最终全套后的单处源码注释修正有源副本及精确非执行内容比对。WI-020、WI-021、WI-022、WI-023、WI-024、WI-027仍open；无新浏览器、完整人工实战或线上结论。

## 2026-11-08 ACT组与阎罗阶段更新

| ID | 内容 | 状态 | 证据与边界 |
|---|---|---|---|
| WI-038 | 原ACT组到实际衔接成员 | 阶段已验证 | E-act-groups-2026-11-08.json；160组/191前招/43357原数据比对零差异，1005合法目录排队连接通过。按前招允许列表原顺序选首个同组成员，保留根context、一次扣怒及原自动链接；不开放组内任意互连 |
| WI-039 | 匕首阎罗原效果攻击入口 | 阶段已验证 | 259原AttackBox、d_base突进、109受击及349自动收招；S/W/W/J生产输入下5米目标命中一次，夹具伤害794、100怒支付一次。CPU平面暂停NPC反击/导航；不是固定伤害、通用击倒或人工实战验收 |
| WI-023 | 全部投射物与EF | 继续进行 | 196入口中166可执行、30待补；默认55EF/240纹理形状/49纹理记录（45PNG、4IFL），46生成文件复现一致。八方绝item22怒气削减及落樱雪item12蛊毒消费者仍未恢复，继续禁用 |
| WI-021 | 原输入识别与耗怒映射 | 继续进行 | 组请求语义及实际成员已接；低层idle play仍为直接pose接口，生产可用入口已核为原组首项。完整原selector、方向识别和其他触发链未恢复 |
| WI-032 | 原动作与完整战斗还原 | 继续进行 | 原state7死亡及state9死亡后入口已溯源，未据拒绝受击条件制造通用霸体。保护掩码、爆气、原精确物理、群战AI与全部技能继续开放 |

v0.7.2全套315/315、27模块语法及3885资产记录核验通过；75代码/测试/导入脚本和5清单在全套前后保持一致。WI-020、WI-021、WI-022、WI-023、WI-024、WI-027、WI-032继续开放。没有新增浏览器/GPU/人工通关或线上结论，完整目标保持active。

## 2026-11-08 敌人发现与七星状态更新

| ID | 内容 | 状态 | 证据与边界 |
|---|---|---|---|
| WI-040 | 发现门槛、已知目标与wait追击 | 阶段已验证 | E-awareness-2026-11-08.json；演武/单机共用原View、近处80单位、远处前方点积、视线及旧目标200单位保留。原sn06正常开局活AI仅一人发现，旧引擎三个生产检查失败；wait发现后追击，idle/剧情命令/报告/增援保持各自行为。完整环顾/决策/战术未恢复 |
| WI-041 | 八方绝、落樱雪、赤练牙附加道具 | 阶段已验证 | 原参数16应用、damage→victim-rage→item顺序，格挡/致死拒绝，零伤害/动态stat7、原5Hz计数/到期/刷新和无攻击者周期死亡通过。196入口现169可执行/27待补；技能CPU夹具暂停NPC反击/导航，状态视觉及其他效果仍缺 |
| WI-042 | 效果独立绑定与位置模式 | 阶段已验证 | 原00582120/00582210位置父原点、旋转父完整仿射基、空旋转世界轴与flags3；4新检查当前通过/隔离旧模块全失败。61EF/286纹理形状/50纹理记录（46PNG、4IFL），47生成文件默认导入复现一致；完整粒子仍开放 |
| WI-022 | 原物理、导航与完整AI | 继续进行 | 已修演武全图自动锁定与wait分支，当前眼点/射线、最近目标和部分时序仍为Web适配；原AI权重、环顾、战术与精确物理未完整恢复 |
| WI-023 | 全部兵器与效果 | 继续进行 | 新增三条可执行七星入口；209减速的stat5消费者、其他附加状态和剩余27条入口、完整EF/投射物理继续开放 |

最后338/338、28模块语法和3885资产记录核验通过；79代码/测试/导入脚本和5清单全套前后不变。WI-020、WI-021、WI-022、WI-023、WI-024、WI-027、WI-032保持open；总体目标active。无新浏览器/GPU/人工通关、上传或部署；已明确区分原图活AI开局与冻结NPC的技能检查。


## 2026-11-09 怒招与握持修复

| ID | 内容 | 状态 | 证据与边界 |
|---|---|---|---|
| WI-RG01 | 用户报告的五类怒招拦截 | 本轮已验证 | 10入口解禁，实际伤害/状态、一次扣怒、原收招与再次攻击；完整原技能效果仍开放 |
| WI-RG02 | 乾坤刀举刀无刀 | 本轮已验证 | 生产可见模型挂原RP/LP手部点，三式/四款原模型与浏览器对照；原dummy补偿仍未全恢复 |
| WI-023 | 全部投射物与EF | 继续进行 | 179可执行/17待补；76EF/53纹理记录，PLANE/粒子/MODEL等未全部接入 |
| WI-032 | 原动作与完整战斗 | 继续进行 | 全套369/369通过不等同原护体、完整物理/网络/全部AI和剧情完成 |


## 2026-11-09 收刀回归补正

| ID | 内容 | 状态 | 证据与边界 |
|---|---|---|---|
| WI-RG02 | 乾坤刀握持与收刀 | 本轮补正已验证 | 原DES端点与POS阶段驱动可见刀身入鞘；四款模型、公开收/拔刀及换兵器清理；旧全部跟手断言已改为实际几何验收 |
| WI-032 | 完整战斗还原 | 继续进行 | 全套370/370；受击身体攻击窗口的验收修正不代表全部原物理与原渲染器已恢复 |

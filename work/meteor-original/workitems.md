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

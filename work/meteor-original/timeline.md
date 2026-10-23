# Timeline (append-only)

## 2026-10-22T16:55:08+08:00 | lead | init
- action: case-init
- command_or_ref: skills/scripts/case-init.sh
- result_summary: case directory created; scope ready_for_act=true
- artifacts: [scope.md, workitems.md]
- evidence_ids: []
- decision_delta: [case_initialized]
- carry_forward_refs: [scope.md]
- next: open PRIMARY SKILL.md and ACT within scope

## 补录说明

以下记录在2026-10-23收尾时根据保留文件、命令结果与代理交接补录。精度仅到日期/阶段，不伪造先前未记录的执行时刻；各JSON中的observedAt为对应实际快照时间。阶段交付完成不表示完整游戏已完成。

## 2026-10-22 | lead | 原版路线与静态工具就绪（补录）
- action: 确认用户要求从本地原客户端移植，归档此前近似玩法原型；确认PE身份和导入表，建立Ghidra工程。
- command_or_ref: notes/decisions.md；tool-index.md；tool-index-verified.md；evidence/E-imports.json。
- result_summary: 原样本保持只读，未执行原EXE；无IDA，使用已验证路径的Ghidra与rabin2，保留8532函数主项目分析结果。
- artifacts: [notes/decisions.md, tool-index-verified.md, ghidra-project, evidence/E-imports.json]
- evidence_ids: [E-301, E-302]
- linked_workitems: [WI-001, WI-006]
- decision_delta: [original-data-required, prototype-archived, offline-static-analysis]
- next: 按资源格式、人物动画、战斗语义和验证分工推进。

## 2026-10-22—2026-10-23 | quality_review | 全量资源清单与可复现导入（补录）
- action: 识别全部ZIP格式PAK、逐文件SHA256；按真实menu/PST映射地图名称，扩展全部22地图目录；导出UI/音效/脚本与include。
- command_or_ref: scripts/import-original.py --source {sample_dir} --output dist/assets/original --maps all；scripts/analysis/verify-recovered-assets.py。
- result_summary: 完整源清单2090文件/28 PAK；发布主清单3036资产；21地图可用，sn22因非有限顶点标记不可用；loose与PAK的DES差异分别记录，无臆造地图名。
- artifacts: [evidence/resource-inventory.json, evidence/resource-source-report.md, evidence/E-asset-coverage-current.json]
- evidence_ids: [E-305, E-306]
- linked_workitems: [WI-002]
- decision_delta: [all-map-resources-preserved, invalid-model-explicit, source-bytes-preserved]
- next: 真实人物、武器和场景实例接入，不以资源存在证明行为完整。

## 2026-10-22—2026-10-23 | resource_research / lead / game_engine | 人物、兵器、场景与动作接入（补录）
- action: 解析原SKC/BNC/AMB/POS、GMB/GMC/DES/FMC及RES记录；处理蒙皮UV、原武器变体、双持r/l别名、隐藏碰撞平台及原FMC姿态。
- command_or_ref: dist/assets/original/characters/manifest.json；dist/assets/original/weapon-models/manifest.json；scripts/verify-native-scenes.mjs。
- result_summary: 20套原人物、59物品/71武器模型、114场景模型清单；sn01/02/09/10/18真实几何与FMC测试保全。w6_5、三处纹理与sn22问题保留；运行碰撞/物理仍属Web桥。
- artifacts: [evidence/E-scene-model-extraction.json, evidence/E-scene-runtime-verification.json, evidence/E-missing-models-research.json]
- evidence_ids: [E-native-combat, E-scene-runtime-verification, E-missing-models-research, E-305]
- linked_workitems: [WI-003, WI-004, WI-005, WI-022, WI-026]
- decision_delta: [native-characters-replaced-procedural, source-weapon-variants, source-geometry-collision]
- next: 核实原EXE数值和任务生命周期；未完成的原AI/投射物/联网单列。

## 2026-10-22—2026-10-23 | lead | x86公式与RES交叉核实（补录）
- action: 导出属性/命中等关键函数，结合x87反汇编核对百分比修正、向零截断、HP默认值、队伍倍率及受击/防御加怒。
- command_or_ref: scripts/analysis/document-combat-formulas.py；scripts/analysis/verify-exe-formulas.mjs。
- result_summary: JS当前数值匹配9/9独立原始样例；parameter16确认为受击者附加物品效果，不冒充攻击者耗怒；原方向输入selector及消耗事件映射未完成。
- artifacts: [evidence/E-exe-decompilation-index.json, evidence/E-exe-combat-formulas.json, evidence/E-formula-runtime-verification.json, report/2026-10-23_逆向-MeteorEXE战斗数值-report.md]
- evidence_ids: [E-302, E-303, E-304]
- linked_workitems: [WI-006, WI-021]
- decision_delta: [x87-truncation-retained, victim-effects-not-cast-cost, unresolved-input-explicit]
- next: 数值恢复不外推为完整战斗条件；机器伤害与物理保留证据边界。

## 2026-10-22—2026-10-23 | quality_review | PST解释器与第一关宿主（补录）
- action: 构建无eval的PST解析/解释器；加载111个真实PST/H及includes；接入sn01关卡、场景和三个NPC的独立VM。
- command_or_ref: node --test tests/native-script.test.mjs；node --test tests/native-mission-host.test.mjs。
- result_summary: 原PlayerSpawn9/HP1500/武器5+1、NPC WP53/80/32与HP1000/1000/2000、原巡逻/发现/报告/撤退/死亡对白执行；源码拼写兼容显式记录，未知API显式错误。
- artifacts: [evidence/E-pst-runtime.json, evidence/E-mission-host.json, report/2026-10-23_逆向-钟乳洞PST宿主-report.md]
- evidence_ids: [E-pst-runtime, E-mission-host]
- linked_workitems: [WI-007, WI-008, WI-020]
- decision_delta: [actual-source-story, independent-script-identity, rule10-completion-labelled-inference]
- next: 引擎联调生命周期与异步加载；其他关卡不因语法可解析而宣称通关。

## 2026-10-23 | game_engine / quality_review / lead | 联调与有限浏览器验收（补录）
- action: 接通createScriptActor/placeScriptPlayer/scriptControl、场景姿态与碰撞及对白UI；修复Window.fetch接收者、异步退出残留、WP原高度与人物脚底抵达不一致。
- command_or_ref: npm test；npm run check；evidence/E-mission-host.json；evidence/E-web-deployment.json。
- result_summary: 38/38测试、9运行模块语法检查通过。本地浏览器确认原sn01/人物/箱子、1500HP、对白、E换原匕首/七星、走桥、Q锁定，以及375px触控切换。未人工通关。机器OnAttack传参公式未证实，默认只发damagePending。
- artifacts: [evidence/native-mission-tests.tap, evidence/E-mission-host.json, evidence/E-scene-runtime-verification.json]
- evidence_ids: [E-mission-host, E-scene-runtime-verification, E-web-deployment]
- linked_workitems: [WI-008, WI-009, WI-024, WI-027]
- decision_delta: [runtime-frozen, gameplay-validation-bounded, no-invented-machine-damage]
- next: 仅发布当前阶段；完整GameRule、原AI/物理、投射物、其他任务和联网均保留未完成。

## 2026-10-23 | lead | 当前阶段私有发布（补录）
- action: 保存并部署当前Web运行目录，核对发布包与源运行文件。
- command_or_ref: evidence/E-web-deployment.json；sourceCommit=ce1c35f2bf126589d6e05af8a7eb3d113e784452。
- result_summary: status=succeeded、audience=owner-private；3953运行文件比较0差异。线上浏览器仅验证私有登录门正常，未登录、未验证登录后实际游戏；不把本地验收当作线上登录后验收。
- artifacts: [evidence/E-web-deployment.json]
- evidence_ids: [E-web-deployment]
- linked_workitems: [WI-011, WI-027]
- decision_delta: [private-stage-published, hosted-game-after-login-not-verified]
- next: owner可从发布链接登录检查；余下完整移植内容按open工单继续。

## 2026-10-23 | quality_review | 文档与匿名经验收尾
- action: 按证据补齐阶段职责、工单状态和时间线；在宿主报告加入Mermaid调用图，并写项目内匿名field journal。
- command_or_ref: workitems.md；report/2026-10-23_逆向-钟乳洞PST宿主-report.md；field-journal/2026-10-23_native-game-port.md。
- result_summary: 阶段已完成项与全游戏未完成项分开；原样本和runtime未改；未写外部技能目录或记忆。Mermaid保留可编辑源码；本机无mmdc，未声称已生成渲染图。
- artifacts: [workitems.md, diagrams/native-mission-flow.mmd, field-journal/2026-10-23_native-game-port.md, report/2026-10-23_逆向-钟乳洞PST宿主-report.md]
- evidence_ids: [E-mission-host, E-web-deployment, E-303, E-304, E-305, E-306]
- linked_workitems: [WI-010]
- decision_delta: [stage-closure-documented, full-game-remains-open, journal-project-local]
- next: 按workitems中open项目推进，不把私有阶段发布标作完整游戏完成。

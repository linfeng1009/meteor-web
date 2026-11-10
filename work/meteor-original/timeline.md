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

## 2026-10-23 | game_engine / mission_acceptance / lead | 七星基础投射与首关CPU验收
- action: 从原POS200/202攻击窗、d_wpnR手骨和W3_0接入实际飞行、连续扫掠与原伤害；补齐原路径、实际近战/投射伤害、自然失败、隔离胜利和重开验收。
- command_or_ref: npm test；npm run check；node --test tests/mission-acceptance.test.mjs；node --test tests/native-projectiles.test.mjs。
- result_summary: 本条历史快照为58/58、10模块语法检查通过（当前已由2026-10-26的83项快照更新）；13项投射与7项首关CPU验收通过。实际WP67→WP53三发各34，桥mesh T遮挡；原长官防0每发49。普通移动从原WP9走到WP53后由活敌实际击杀并唯一失败，重开清空怒气/接触计数。冻结NPC物理反击的独立夹具以正常匕首累计4000伤害、3kill、原长官死亡台词及唯一Rule10推断胜利；没有直接改NPC HP/dead。
- artifacts: [evidence/E-native-projectiles.md, evidence/E-mission-cpu-acceptance.md, evidence/mission-cpu-acceptance.tap, evidence/E-validation-current.json, report/2026-10-23_逆向-钟乳洞PST宿主-report.md]
- evidence_ids: [E-native-projectiles, E-mission-cpu-acceptance, E-validation-current]
- linked_workitems: [WI-008, WI-009, WI-012, WI-013, WI-023, WI-027]
- decision_delta: [basic-dart-flight-functional, actual-cave-flight-and-occlusion-tested, source-path-walkable, natural-failure-and-restart-validated, isolated-win-not-full-live-ai-victory]
- next: 完成完整活AI实战通关，继续原GameRule、进阶投射/EF和机关伤害恢复；当前本地新增能力不由旧私有部署记录证明已上线。

## 2026-10-23 | quality_review / lead / mission_acceptance | 原机关伤害闭环与最终集成中
- action: 静态核实原事件0x1d到PST OnAttack的伤害参数；lead新增createNativeSceneDamageResolver和两项回调/数值测试，文档标注58项为此前已验证快照。
- command_or_ref: evidence/E-native-machine-damage.json；node --test tests/native-script.test.mjs。
- result_summary: 原伤害为nativePoseAttack，不减角色防御，不用队伍倍率、防御状态或HP除十；新增两测试通过，lead报告该模块12/12。默认引擎接入与最终全套检查当时仍在整合；本条不代表当前状态，2026-10-26已闭环并验证83/83，见后续记录。
- artifacts: [evidence/E-native-machine-damage.json, evidence/E-validation-current.json, report/2026-10-23_逆向-钟乳洞PST宿主-report.md, workitems.md]
- evidence_ids: [E-native-machine-damage, E-validation-current]
- linked_workitems: [WI-014, WI-024, WI-027]
- decision_delta: [native-machine-damage-argument-verified, old58-count-retained-as-snapshot, final-integrated-suite-pending, no-full-live-ai-win-claim]
- next: lead完成默认引擎接入后更新最终全套数量与机关运行证据；原接触体、事件频率、爆炸映射与完整机关物理仍按证据单独验证。


## 2026-10-26 | lead / jump_regression | 原版跳跃模型、碰撞体与镜头对齐
- action: 根据用户跳跃出屏反馈，读取真实SKC/BNC/AMB/POS追踪d_base场景位移；就地播放恢复各角色BNC原始基点，保留骨盆局部姿态、所有武器挂点与raw轨迹；镜头竖直跟随实际外层碰撞root。
- command_or_ref: node --test tests/native-jump-camera.test.mjs；旧HEAD b1ced130的engine/native-character在独立临时镜像运行相同测试。
- result_summary: 10/10通过，旧实现2通过8失败；跳跃模型相对碰撞root额外高度5.901924m→0，身体中心NDC y最大2.133273→-0.032444；外层跳跃高度和落地位置保持原Web物理值。覆盖平地、锁定、移动、近墙、落地、飞镖挂点与20人物d_base层级，保留P19非零BNC初值。浏览器平地和锁定跳跃截图均保持人物在画面内。
- artifacts: [evidence/E-jump-follow-2026-10-26.md, evidence/E-jump-follow-baseline-2026-10-26.tap, evidence/E-jump-follow-fixed-2026-10-26.tap, ../../artifacts/jump-follow-fixed.png, ../../artifacts/jump-lock-follow-fixed.png]
- evidence_ids: [E-jump-follow]
- linked_workitems: [WI-003, WI-009, WI-015, WI-022, WI-027]
- decision_delta: [scene-translation-collider-aligned, native-local-pose-preserved, vertical-camera-follows-root, old-snapshot-regression-demonstrated]
- next: 全套集成检查；不把Web物理适配宣称为原EXE完整物理恢复。

## 2026-10-26 | lead / quality_review / native_items | 原机关几何破坏链与首关肉包拾取
- action: 完成默认scene伤害resolver接入；用原sn01 DES/cmodel/FMC/POS/PST与真实连续扫掠验证石块受击、破碎和掉落激活；接入原RES type2/id1 Item01肉包的F/触屏拾取、可达性、恢复量、消费与重置。
- command_or_ref: node work/meteor-original/evidence/scene-machine-audit-2026-10-26.mjs；node --test tests/native-items.test.mjs；evidence/E-native-machine-damage.json。
- result_summary: 实际D_St20/Object02接收11发各49伤害，500HP→-39，原破碎pose1结束state3、隐藏并关闭碰撞、激活D_itSt20；源初始化恢复石块与隐藏掉落。该掉落为Item02，尚不支持拾取。另一真实石块的Item01掉落→原300HP恢复/上限夹取→单次消费→新局重置通过；9项肉包测试已纳入最终全套，其中新增引擎遮挡及状态/HUD接线验收，早期7项独立TAP仅作历史。演武禁用拾取，仅sn01单机可用。
- artifacts: [evidence/E-native-machine-damage.json, evidence/scene-machine-audit-2026-10-26.mjs, evidence/scene-machine-audit-2026-10-26.json, evidence/E-native-items-2026-10-26.md, evidence/native-runtime-current.tap]
- evidence_ids: [E-native-machine-damage, E-native-items, E-validation-current]
- linked_workitems: [WI-014, WI-016, WI-024, WI-027]
- decision_delta: [default-scene-damage-integrated, real-source-geometry-break-drop-verified, native-meatbun300-adapted, pickup-policy-labelled-web]
- next: 其他道具、原拾取半径/满血消耗/计时重生与完整机关语义保留open；几何探针不替代角色瞄准、步行路线或人工通关。

## 2026-10-26 | lead / jump_regression | 最终本地验证快照与发布边界
- action: 完成统一全套测试、运行模块语法与diff空白检查，更新当前快照及文档，保留旧38/58项为历史记录。
- command_or_ref: npm test；npm run check；git diff --check；evidence/native-runtime-current.tap；evidence/E-validation-current.json。
- result_summary: 83/83通过、0失败、26.870848917秒；11个运行模块语法检查与diff检查通过。包含10项跳跃、9项肉包、13项基础投射、7项首关CPU验收。完整活AI胜利与完整人工通关仍未取得。本次仅本地验证，外部上传曾被自动审批拒绝，仍缺明确用户授权，未更新线上部署；旧私有站点与登录门验证不能证明本轮能力上线。
- artifacts: [evidence/native-runtime-current.tap, evidence/E-validation-current.json, README.md, workitems.md]
- evidence_ids: [E-validation-current, E-web-deployment, E-jump-follow, E-native-items]
- linked_workitems: [WI-009, WI-010, WI-011, WI-014, WI-015, WI-016, WI-027]
- decision_delta: [83-test-local-final-snapshot, old58-historical-only, no-new-upload-or-deployment, full-live-ai-victory-open]
- next: 按未完成工单推进原版行为和完整活AI验收；外部发布须先取得明确授权，不把本地集成标为已上线。

## 2026-10-26 | lead / continuation_review | 原石块到肉包完整单链补证
- action: 使用真实D_St22碰撞三角、七星连续扫掠、原PST与FMC，补齐破坏到Item01拾取与重置的单一实例链。
- command_or_ref: node work/meteor-original/evidence/scene-meatbun-chain-2026-10-26.mjs。
- result_summary: 11次真实几何命中各49，石块500→-39；破碎结束后原肉包激活，真实地面探针位置/引擎遮挡检查通过，HP1000→1300、重复拒绝、原场景重置，diagnostics0。非普通步行/原手骨发射/浏览器F实机。
- artifacts: [evidence/scene-meatbun-chain-2026-10-26.mjs, evidence/scene-meatbun-chain-2026-10-26.json, evidence/E-local-package-2026-10-26.json]
- linked_workitems: [WI-014, WI-016, WI-024]
- next: 本地v0.3完整运行包已备，3962文件与源逐项一致；外部上传等待明确授权，未重试被拒绝的上传。

## 2026-11-05 | lead | 既有记录恢复与继续关卡
- action: 复用 case-init.sh 时该脚本覆盖了 scope、timeline、workitems 和案件 README；恢复 Git 中已存的原授权及历史正文。未提交的阶段记录按留存证据补录，以下为重建记录，不冒充原逐时记录。
- result_summary: 10月26日炎硫岛与机关/环境、10月29日招式/防御/投射、10月30日受击/击倒/反馈的阶段证据及报告仍完整保留。11月4日决死阵/飞鹏堡处于接线未验收；11月5日动作混合为进行中工作。
- artifacts: [evidence/E-validation-current.json, evidence/E-native-island-2026-10-26.md, evidence/E-manual-combos-validation-2026-10-29.json, evidence/E-combat-impact-integration-2026-10-30.md, evidence/mission-catalog-audit-2026-11-04.md]
- decision_delta: [existing-scope-restored, user-prioritizes-other-missions, preserve-combat-work]
- carry_forward_refs: [scope.md, evidence/E-new-mission-host-current-2026-11-04.json]
- next: 完成 sn09/sn15 原任务机制与独立验收。

## 2026-11-06 | lead | 决死阵与飞鹏堡阶段交付
- action: 接通两关原脚本/原资源；恢复两种RES脚本道具、原AMB起跳曲线与NPC登台请求；修复attacktarget被距离查询覆盖；区分援军阵营/HUD。
- result_summary: 决死阵原出生点正常输入+活AI约199.03秒胜利；飞鹏堡指定VIP7500HP真实伤害胜利链、实际原路径逃脱失败、原条件援军分别通过；冻结系统边界单列。最终228/228测试、19模块语法、3858资源记录核验通过。
- artifacts: [evidence/E-new-missions-2026-11-06.json, evidence/native-runtime-new-missions-2026-11-06.tap, report/2026-11-06_逆向-决死阵与飞鹏堡-report.md, diagrams/mission-expansion-2026-11-06.mmd]
- evidence_ids: [E-M01, E-M02, E-M03, E-M04, E-M05]
- linked_workitems: [WI-020, WI-022, WI-024, WI-027, WI-031, WI-032]
- decision_delta: [two-additional-playable-missions, preserve-native-objectives, snapshot-navigation-target, native-takeoff-to-collision-root, browser-verification-unavailable]
- carry_forward_refs: [scope.md, evidence/E-validation-current.json, evidence/E-new-missions-2026-11-06.json]
- limitations: 内置预览连接超时；Computer Use访问Chrome未批准且未给出进一步原因。无本轮浏览器试玩/人工通关/线上部署。全原版战斗还原目标与其余任务仍开放。Mermaid渲染器缺失，仅保留源码。
- next: 继续其余原剧情及火枪/飞轮/完整EF，恢复原战斗物理和输入语义；不将两关验收等同完整移植完成。

## 2026-11-06 | lead | 原场景位移与受击时长
- action: 只读追踪d_base/角色场景向量及Move/Value语法、消息、运动和计时链；接入原轨迹，统一碰撞/险地路径；修复原帧终点和跨落地队列。
- command_or_ref: combat-motion-source-audit-2026-11-06.py；既有Ghidra项目-readOnly/-noanalysis；npm test；npm run check；verify-recovered-assets.py。
- result_summary: 最终234/234通过、28.71611525秒；19运行模块语法、3858资源记录核验零异常。111可用指令从地面/自然起跳进入，移除旧目录额外100高度；原突刺、近墙、重锤反应、无攻击窗下降及匕首三空击覆盖。
- artifacts: [evidence/E-combat-motion-source-2026-11-06.json, evidence/native-runtime-motion-fidelity-2026-11-06.tap, report/2026-11-06_逆向-原位移与受击时长-report.md, field-journal/2026-11-06_combat-motion.md]
- evidence_ids: [E-MO01, E-MO02, E-MO03, E-MO04]
- linked_workitems: [WI-021, WI-022, WI-027, WI-032, WI-033]
- decision_delta: [d_base-not-pelvis-motion, move-multiplier-and-value-duration-separated, native-wire-float-rounding, exact-frame-terminal, accepted-continuation-survives-landing-web-policy]
- limitations: 完整向量生产、旋转/方向受击、护架运动、强制受击混合、原物理及EF仍未恢复。窄扫只命中无关骨骼加载字段，不误认producer。无新浏览器/人工/线上结论，未绕过此前访问拒绝。
- next: 继续完整战斗还原及其余原任务；总体目标保持active。

## 2026-11-06 | lead | 十二兵器、群战恢复输入与炽雪城
- action: 优先处理用户提出的围攻中持续打断与隐藏兵器选择；补全十二类UI/原动作入口、乾坤刀三架式、火铳/飞轮和27份原WAV；接入sn04原城门及落雪。
- command_or_ref: 既有Ghidra只读项目；r2只读004cc130/005aa8b8；npm test；npm run check；verify-recovered-assets.py。
- result_summary: 293/293通过、52.510207042秒；25运行模块语法、3885资产记录零新异常。68份代码/测试/导入脚本与5清单在全套前后保持一致。196目录入口中165可执行、31待补；不等同165完整技能。sn04隔离原兵器接触10000门耐久，经pose8/state3后127.50秒唯一胜利，7NPC存活/0击杀，重开通过。
- artifacts: [evidence/E-twelve-weapons-2026-11-06.json, evidence/native-runtime-twelve-weapons-2026-11-06.tap, report/2026-11-06_逆向-十二兵器与群战输入-report.md, field-journal/2026-11-06_twelve-weapons-input.md, diagrams/twelve-weapons-input-2026-11-06.mmd]
- evidence_ids: [E-TW01, E-TW02, E-TW03, E-TW04]
- linked_workitems: [WI-020, WI-021, WI-022, WI-023, WI-024, WI-027, WI-032, WI-034, WI-035, WI-036]
- decision_delta: [held-defense-survives-hitstun, expiring-recovery-attack-slot, unlocked-melee-preserves-facing, all-twelve-weapon-selection, qiankun-three-forms, sn04-source-gate-ending, explicit-web-projectile-physics]
- limitations: 原霸体/爆气/完整AI时序未确认；完整EF和原投射物理仍缺。sn04验收冻结NPC战斗/导航并放置玩家一次，不是出生点活AI通关。原vip/enemyvip区分阵营，现sn15选择器仍待完整恢复。原未播种钟乳洞停滞仍未解释。无浏览器、人工或线上新结论，未重试被拒绝的浏览器访问。
- next: 继续原打断状态、识别器、完整技能效果与其余剧情，保持总体目标active。

## 2026-11-07 | lead | 长枪气罩与原EF效果命中
- action: 按用户反馈恢复effect=0x1001攻击查询、原A/a攻击节点的球/柱/盒有向包围盒；共用原伤害/方向受击/AMB位移；分离EF秒时钟与POS帧速度，修正底端柱体锚点。
- command_or_ref: 既有Ghidra项目-readOnly/-noanalysis；npm test；npm run check；python3 scripts/analysis/verify-recovered-assets.py。
- result_summary: 新增11项，48项针对性检查通过。最初304项全套通过后工作区同期新增无限怒气UI/引擎/测试，再冻结74文件/5清单，最终306/306通过、49.282581秒；27模块语法与3885资产记录零新异常。三名3.5米处目标气罩命中后原轨迹外移约6.573米并倒地/起身；20米前方冲击命中，后方及侧面远处不命中，按原Attack身份去重。
- artifacts: [evidence/E-effect-contacts-2026-11-07.json, evidence/native-runtime-effect-contacts-final-2026-11-07.tap, report/2026-11-07_逆向-长枪气罩与效果命中-report.md, field-journal/2026-11-07_effect-contacts.md, diagrams/effect-contacts-2026-11-07.mmd]
- evidence_ids: [E-EF01, E-EF02, E-EF03, E-EF04]
- linked_workitems: [WI-021, WI-022, WI-023, WI-027, WI-032, WI-037]
- decision_delta: [native-effect-attack-node-path, native-oriented-bounds, shared-visual-contact-transforms, independent-effect-seconds, base-anchored-cylinder, preserve-concurrent-infinite-rage-debug, full-regression-after-concurrent-changes]
- corrections: 虚表候选更正为构造函数证明的005aa6a8，未据错误候选实现霸体；校验脚本真实路径含analysis/；浮点/视觉夹具失败均保留。最终全套后只改一处注释类型名，保留全套源副本并确认可执行语句未变，当前文件语法通过。
- limitations: CPU平面和暂停NPC反击/导航，不是浏览器或活AI人工通关；Web人物包围盒、插值和时间采样明确。其他EF类型/粒子、效果对机关、原穿墙/全局时钟、霸体/爆气/完整AI、其余技能及剧情仍开放，无上传或部署。
- next: 继续原效果分支、附加状态、原战斗/输入语义和完整实战验证；总体目标保持active。

## 2026-11-08 | lead / parallel audits | ACT组衔接与阎罗效果入口
- action: 按原0055d020/0055d130恢复组请求到实际允许成员的选择顺序，保留根指令context与单次扣怒；恢复匕首259原effect攻击盒、109反应及349收招，补生产输入长枪三连接294的实际命中检查。
- command_or_ref: 既有Ghidra项目只读导出；node work/combo-continuity-audit/integration-review-2026-11-08.mjs；npm test；npm run check；python3 scripts/analysis/verify-recovered-assets.py。
- result_summary: v0.7.2最终315/315通过、48.212891459秒；27运行模块语法、3885资产记录零新异常。75份代码/测试/导入脚本及5清单从全套开始保持一致。160组、191前招、43357次独立原ACT比对零差异；1005合法目录连接含136个不同实际成员。196目录入口现166可执行、30待补，不等同166完整技能。
- artifacts: [evidence/E-act-groups-2026-11-08.json, evidence/native-runtime-act-groups-2026-11-08.tap, report/2026-11-08_逆向-ACT连招与阎罗-report.md, field-journal/2026-11-08_act-groups.md, diagrams/act-groups-2026-11-08.mmd]
- evidence_ids: [E-AG01, E-AG02, E-AG03, E-AG04]
- linked_workitems: [WI-021, WI-022, WI-023, WI-027, WI-032, WI-038, WI-039]
- decision_delta: [original-group-order-not-root-only, preserve-root-context-and-one-payment, original-dagger-effect-entry, root-motion-required-for-range, independent-default-import-reproduction]
- corrections: 阎罗固定根探针不能代替突进实战射程；原d_base在攻击帧前进约7.281米，5米目标在生产输入下命中一次，夹具伤害794、原反应109、收招349。原state7为死亡、state9有死亡后等待入口，不能据此添加通用出招霸体。默认55EF/240纹理形状/49纹理记录（45PNG、4IFL），46生成文件隔离复现一致。
- limitations: 实际命中检查在CPU平面暂停NPC反击/导航，不是浏览器或活AI人工验收。八方绝与落樱雪的道具状态消费者未恢复，仍禁用；完整原输入、物理、保护掩码/爆气、AI及其他剧情继续开放。图渲染缺mmdc仅保留源与失败日志；无新浏览器访问、上传或部署。
- next: 继续开放工单；整体战斗还原目标保持active。

## 2026-11-08 | lead | 敌人发现后追击与七星暂停工作收尾
- action: 用户恢复目标并优先反馈开局全体围攻。追踪原View/前方/近处/遮挡/缓存与wait状态；修复演武无条件追踪、单机全向远处发现、wait不追击、出生朝向/行为及重生缓存。保留原剧情的明确追击和增援命令。
- command_or_ref: 既有Ghidra项目-readOnly/-noanalysis；ReadOnlyAwarenessTrace.java及ReadOnlyHitReactionTrace.java；node --test tests/native-awareness.test.mjs tests/native-mission-host.test.mjs；npm test；npm run check；verify-recovered-assets.py。
- result_summary: v0.7.3最后338/338通过、52.268831292秒；28模块语法、3885资产记录零新异常。79代码/测试/导入脚本和5清单全套前后一致。原sn06几何/碰撞/DES/正常start及三名活AI首秒位移5.095/0/0，仅一人发现；同原出生点CPU平面公开262→263通过。旧引擎隔离三个生产检查均失败，当前6项发现检查及20项发现/脚本专项通过。
- artifacts: [evidence/E-awareness-2026-11-08.json, evidence/native-runtime-awareness-delivery-2026-11-08.tap, report/2026-11-08_逆向-敌人发现与七星状态-report.md, field-journal/2026-11-08_awareness-and-status.md, diagrams/awareness-2026-11-08.mmd]
- evidence_ids: [E-AW01, E-AW02, E-AW03, E-AW04]
- linked_workitems: [WI-021, WI-022, WI-023, WI-024, WI-027, WI-032, WI-040, WI-041, WI-042]
- decision_delta: [perception-before-auto-pursuit, native-nearby-and-forward-gates, native-known-target-retention, source-wait-to-pursuit, preserve-explicit-script-orders, source-fixed-item-clock, exact-attack-item-order, independent-effect-parent-bases]
- corrections: 完成暂停前七星201/551/203及210附加状态整合；196入口中169可执行/27待补。蛊毒周期word3=2，原服务器/客户端固定.2f更新，计数先判后加、到期≤先删除；不沿用旧连续计时。初次337套1个旧断言仍把203当pending，改为同时验证可用203和仍待补567；337通过后补源wait追击，最终338通过。失败与各起点快照保留。
- limitations: 真实地图开局使用CPU运行，纹理/音频/渲染替代；技能命中夹具另暂停NPC反击/导航，二者不混称。眼点/射线、最近目标、观察时序、攻击决策/随机环顾/战术、完整原状态与粒子仍开放。原未播种钟乳洞停滞未被追溯解释。无新浏览器/人工/线上结论；缺mmdc只留图源与失败日志。
- next: 继续原AI决策/全部技能、原输入/物理与其余剧情；完整战斗目标保持active。


## 2026-11-09 | lead | rage-and-grip-fix
- action: inspect native rage gates, self items and qiankun visible grip
- command_or_ref: ReadOnlyProjectileTrace.java -readOnly -noanalysis; native-command-engine/effect-contacts; npm test; npm run check; verify-recovered-assets.py; npm run package
- result_summary: 10 pending怒招接通，原item34/40/13/37进入属性与计时；乾坤刀可见模型使用原RP/LP手部点，原R/L控制轨道保留。369/369测试、29模块、3885资产无问题；77测试输入冻结。v0.7.4本地包4088文件校验通过。
- evidence_ids: [E-RG01, E-RG02, E-RG03, E-RG04]
- artifacts: [evidence/E-rage-and-grip-2026-11-09.json, evidence/E-validation-rage-and-grip-2026-11-09.json, report/2026-11-09_逆向-五类怒招与乾坤刀握持-report.md]
- decision_delta: [restore-real-source-effect-contacts-before-enabling, deferred-self-buffs-on-completion, keep-weapon-baseline-speed, explicit-qiankun-mode-feedback, visible-palm-grip-binding]
- limitations: 原护体/霸体、PLANE/粒子/MODEL、完整原dummy补偿/触发时序/物理仍开放；仅本地交付，未远端发布。其他同期NPC修改保留，不归为本轮实现。


## 2026-11-09 | lead | qiankun-sheathing
- action: correct visible blade seating after public down-down-A
- command_or_ref: read-only Ghidra pose/loader exploration; native DES sockets/POS stages; grip-tests58; npm test; npm run check; verify-recovered-assets.py; npm run package
- result_summary: 举刀保持握持，431/441收刀、403待发、拔刀后485/486回鞘均有可见几何验收；四款刀，实际刀尖在鞘体内、刀柄外露。最终370/370、30模块、3885资产；77最终输入冻结；v0.7.5包4089文件校验。
- evidence_ids: [E-QS01, E-QS02, E-QS03]
- artifacts: [evidence/E-qiankun-sheathing-2026-11-09.json, evidence/E-validation-sheathing-2026-11-09.json, report/2026-11-09_逆向-乾坤刀收刀入鞘-report.md]
- corrections: 旧所有帧跟手断言漏测入鞘；另将单机无主动攻击验收与原受击身体撞伤区分，保留首次370中1失败与诊断，未改伤害规则。
- limitations: 原绑定/装载完整算法未恢复；收鞘插值标为Web适配。未远端发布。


## 2026-11-10 | lead | skill-vfx
- action: restore complete source-authored skill visual tails and original POS/DES weapon trails
- command_or_ref: node work/skill-vfx-2026-11-10/audit.mjs; npm test; npm run check; verify-recovered-assets.py; CUA dark/bright and weapon-trail comparison; npm run package
- result_summary: 审计32个怒招/76EF，修正20组视觉尾段截断；乾坤刀末击12个原刀光形状完整显示。143段原Drag窗接入柔边光带；一次扣怒、实际接触和收招保持。最终381/381、32模块、3885资产；79输入未变；v0.7.6包4095文件校验，含转换网格和16PNG。
- evidence_ids: [E-VFX01, E-VFX02, E-VFX03]
- artifacts: [evidence/E-skill-vfx-2026-11-10.json, evidence/E-validation-vfx-2026-11-10.json, report/2026-11-10_逆向-技能光效与刀光补全-report.md]
- corrections: 首轮380/381，给同期地图显示接口所需的旧投射物换图测试补renderer夹具及显示恢复检查，未改生产显示或战斗规则。失败TAP保留；原素材不变；同期地图/NPC工作保留。
- limitations: 亮度、脱离挂点和柔边光带为Web显示适配；完整PARTICLE/DONUT/MODEL/材质仍开放。未运行原EXE、上传或远端部署。

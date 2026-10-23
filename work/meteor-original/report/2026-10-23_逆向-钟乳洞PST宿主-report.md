# 钟乳洞原版 PST 宿主与验证报告

日期：2026-10-23。类型：普通逆向与 Web 移植，`flavor = null`。范围依据：[scope.md](../scope.md)。本次只读取授权的本地客户端，未执行原版 Windows EXE，也未改写原始 PST。

第一关已经由原 `Level/sn01_.pst`、三个 NPC 脚本、地图脚本和其 include 驱动，Web 引擎提供人物、地图碰撞、动作和对白显示。原始配置、原对白、巡逻路线及条件分支已实际执行；浏览器中已确认出生、1500 HP、原匕首、原对白、换七星、走上桥和锁定目标。**尚未人工完整通关，也不能据此宣称全游戏、原物理或 AI 已完整还原。**

## 运行与复现

在 `meteor-web` 项目目录执行：

```sh
npm run dev
```

打开 `http://localhost:4173`，选择钟乳洞的原版第一关任务。程序入口调用 `game.start({map:'sn01',mode:'story'})`，自动加载宿主；使用原 PlayerSpawn，而不是多人模式的 D_user 出生点。

```sh
npm test
npm run check
node scripts/verify-native-scenes.mjs
```

本次最终测试：38/38 通过；其中宿主测试 13 项，运行模块语法检查 9 项。测试使用仓库内真实源文件、WP、DES、武器清单；WebGL/图片加载在 Node 桥接测试中替换为资源桩。测试日志见 [native-mission-tests.tap](../evidence/native-mission-tests.tap)。浏览器验证由主代理单独完成，未把单元测试当作人工通关。

## 原版配置与执行顺序

| 角色 | 脚本 | Model | Weapon item | Spawn WP | HP |
|---|---|---:|---:|---:|---:|
| 孟星魂 | Level/sn01_.pst | 0 | 5，副武器 1 | 9，方向 90 | 1500 |
| 铁枪哨兵﹒甲 | Level/npc01_01.pst | 8 | 7 | 53 | 1000 |
| 铁枪哨兵﹒乙 | Level/npc01_02.pst | 8 | 7 | 80 | 1000 |
| 军枪哨兵长 | Level/npc01_03.pst | 8 | 16 | 32 | 2000 |

item 5/1/7/16 分别解析为原 `w1_0`、`w3_0`、`w7_0`、`w7_1` 模型。三个 NPC 共用 Model 8，但 `scriptId`、引擎运行 ID 和模型 ID 分离，`GetChar` 不会把三人合并。第一关 `Rule=10`、`RoundTime=10` 均从源文件读取。

宿主先加载 include，再执行 `Scene_OnLoad → Scene_OnInit → level.OnInit（若存在）→ level.OnStart`。`AddNPC` 异步读取 NPC 源配置，创建角色后执行该 NPC 的 `OnInit(scriptId) → OnStart`，所有创建完成后执行首个 `level.OnUpdate`。此后以 0.05 秒浏览器适配节奏执行关卡/NPC 更新、Scene_OnUpdate/Scene_OnIdle；对象 OnIdle 每 0.1 秒委托源回调。

甲的原巡逻路线为 `0,1,4,2,3`；乙为 `18,19,75,55,79,38,77,78,14,20`。路径连接与边长来自原 WP；浏览器用 Dijkstra 寻路。WP 的 `position` 保留原坐标，另将 `navigationPosition` 投影到真实碰撞地面以匹配人物脚底，避免 WP53 原高度 2.8 与实际脚底高度不同而永远无法抵达。地面偏移 0.015、抵达半径等是明确的宿主参数，并非已经恢复的原 AI 常量。

## 引擎接入接口

宿主模块为 `dist/native-mission-host.js`，解释器为 `dist/native-script.js`。解释器使用 tokenizer、AST 和受限执行器，未使用 `eval` 或 `new Function`。

| 接口 | 行为 |
|---|---|
| `NativeMissionHost.create(game,{mapId,sources?,fetcher?})` | 在已载入真实地图的 game 上加载关卡、场景及 includes；可注入源文本 Map |
| `await host.start()` | 按原配置放置玩家，执行初始化，创建原 NPC |
| `host.update(dt)` | 原条件分支、Perform 队列、感知、控制桥、完成状态 |
| `host.sceneItemAttack(nameOrId,attackerScriptId,damage)` | 执行真实对象的 `_OnAttack`；伤害必须由已明确的外部 resolver 提供 |
| `host.sceneItemIdle(nameOrId)` | 执行真实对象的 `_OnIdle` |
| `host.dispose()` | 停止脚本并清除控制；晚到的 NPC 加载会清理，避免切菜单后残留 |
| `host.levelVm / sceneVm / npcVms` | 调试原 globals、函数和实际宿主调用需求 |

引擎桥包括 `createScriptActor`、`placeScriptPlayer`、`removeScriptActor`、`hasScriptLineOfSight`、`finishStory`、场景对象与 pose/active/collision 方法。每个 NPC 获得 `scriptIntent` 和 `scriptControl`；引擎优先使用脚本的移动目标、攻击目标、暂停和防御，剧情角色死亡后不按演练模式重生。

对白通过 `game.onEvent({type:'dialogue',scriptId,speaker,text,duration,source})` 输出。`mission-diagnostic` 明示未实现 API/命令，失败回调会禁用，其他回调可继续。`Output/Print` 保存在 `host.stdout` 并输出 `script-output`。MakeString 使用解释器输出参数引用，支持原库的对象名生成。浏览器 fetch 保留 `globalThis` 接收者，防止 Window.fetch 的 Illegal invocation。

原源码的 `Perofrm`、`Distanve`、`InitBBoxs` 仅在宿主启用明确兼容映射，分别委托 Perform、Distance、InitBBoxes；源文件保持原样，映射记录在 compatibilityUsed。未知 API 不自动返回成功。

## 已验证的原脚本行为

13 项宿主测试覆盖：原 NPC 配置与 WP、Window.fetch 接收者、真实引擎放置/装备/不重生桥、原巡逻路线、WP 脚底投影、View 距离与视线、发现玩家与失踪、再次发现后逃向长官并报告、原生命阈值的撤退、长官临死对白、石块回调及实际道具激活、结算边界、加载中退出的清理。

场景 `D_St20` 原 HP 500；调用原 StoneOnAttack 后，原脚本关闭石块碰撞、播放 pose、激活真实 `D_itSt20`，OnIdle 再隐藏破坏完毕的石块。当前 DES 没有 `D_itSt01`，宿主不会补造同名物体。引擎已检测兵器/原骨点对实际 cmodel 三角形的接触；**机器伤害系数尚未证实，默认只报告 scene-contact/damagePending。** 因此 Node 测试显式传入 500 验证的是源回调，不代表浏览器已经拥有原机器伤害公式。

## 战斗公式与实现边界

角色伤害的数值依据是主代理恢复的原 EXE 分支，见 [原 EXE 数值报告](2026-10-23_逆向-MeteorEXE战斗数值-report.md)、[公式证据](../evidence/E-exe-combat-formulas.json)及[运行验证](../evidence/E-formula-runtime-verification.json)。当前代码从原 RES 读取武器/动作修正，先求有效攻击，再应用动作修正、减防御和队伍倍率，按原截断语义处理。HP 保持原内部整数单位，不能单独把伤害除以十。

数值分支已恢复，不等于所有战斗条件都恢复。原输入识别、投射物完整行为、击退/受击/防御条件、怒气消耗触发、所有物品效果、原物理和视锥仍有未完成部分。七星模型、动作和换装可见，不代表原飞镖弹道系统已经完整实现。对象机器伤害不能套用角色伤害公式。

宿主还保留以下明确边界：

- 第一关源脚本没有 GameOver；“所有敌对原 NPC 倒下即胜利”是标注 provenance 的 Rule10 适配推断。玩家死亡失败也是宿主适配。RoundTime 原值用于计时显示，超时结果尚未从原 GameRule 验证。
- View 数值按原单位乘 0.08，并查询真实地图/动态物体遮挡；原视角、巡逻策略和攻击等待时间尚未完整恢复。
- pause/guard 数值按秒适配，阅读时长是 Web 显示辅助。完整 PonEF 视觉渲染未完成，音效/效果事件已有桥。
- 当前完整接通的是 sn01。其他 PST 能解析不代表其他关卡已可通关；Misc、rand/Rand、SetScene、GameCallBack、GetLeader 等尚未接入的调用会明确报错。sn09 的 Misc 时间/随机序列需后续实现。

## Evidence → Finding → Path

| Evidence | source_ref / 复现 | 固定性 |
|---|---|---|
| E-mission-host | [E-mission-host.json](../evidence/E-mission-host.json)；`npm test` | SHA256 `7ff9d51e422e221cef6a04031499a353f2a9deb2c25953bdd01c590bd88deab1`；内含源文件和实现 SHA256 |
| E-pst-runtime | [E-pst-runtime.json](../evidence/E-pst-runtime.json)；`node --test tests/native-script.test.mjs` | 原 API、源位置、包含关系与 Def.h 参数 |
| E-exe-combat-formulas | [E-exe-combat-formulas.json](../evidence/E-exe-combat-formulas.json) | 原样本 SHA256 与地址、反汇编交叉核对；数值复现见上链报告 |

| Finding | 状态 / 置信度 | 证据与位置 |
|---|---|---|
| F-mission-source：第一关剧情由真实 PST 的 globals/functions/原分支驱动 | validated / high / n/a_re | E-mission-host + E-pst-runtime；native-mission-host.js、真实 Level/sn01_.pst、13 项测试。剩余风险：测试不能证明全部原 AI 与浏览器物理一致 |
| F-mission-identity：同模型多 NPC 保留独立身份、原物品 ID 与原 WP | validated / high / n/a_re | E-mission-host 的 source/config 与真实 engine bridge 测试 |
| F-mission-completion：Rule10 的现有完成策略属于适配推断 | candidate / medium / n/a_re | E-mission-host 的 provenance 与源 Level/sn01_.pst；仍需恢复原规则实现 |

P-mission，`path_type=callflow`：

1. 原 manifest 找到 Level、scene、NPC 和 includes（E-mission-host / F-mission-source）。
2. AST 解释器加载 globals/functions，调用 Scene 与 Level 生命周期（E-pst-runtime / F-mission-source）。
3. AddNPC 读取原配置，通过原 WP 与 weapon item 创建独立角色（E-mission-host / F-mission-identity）。
4. 原 OnUpdate 依据 GetEnemy/GetHP/Distance 改变行为，Perform/Say 生成对白和控制（E-mission-host / F-mission-source）。
5. 原角色伤害分支更新 HP；宿主完成策略明确附带推断来源（E-exe-combat-formulas、E-mission-host / F-mission-completion）。

时间线：2026-10-22 读取/导出资源并完成 PST 语法与 VM；2026-10-23 接通第一关宿主及引擎、修复浏览器 fetch 接收者和脚底 WP 高度、完成 38 项测试及有限浏览器交互验证。原时间线见 [timeline.md](../timeline.md)。本报告只总结当前可复现实现；后续应先恢复机器伤害、规则与投射物，再扩大原任务范围。

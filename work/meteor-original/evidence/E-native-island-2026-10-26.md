# 炎硫岛原任务接入与 CPU 验收

日期：2026-10-26（Asia/Shanghai）。本分项沿用 [scope](../scope.md) 的本地离线授权，只读原客户端，没有运行原 EXE。文件名中的 `mission02-` 是最初审计任务的工作编号，不表示已证明原剧情第二关。

## 原数据与命名

`Level/sn14_.pst` 的原任务为炎硫岛，Rule10、RoundTime10、PlayerSpawn34、朝向180、主武器6、副武器0、HP1000。`OnStart` 添加两份原 NPC 脚本；原 `OnUpdate` 控制对白、巡逻、发现/丢失/重见、同伴死亡报仇和死亡对白。

| 脚本 | 原配置 | 源 SHA-256 |
| --- | --- | --- |
| Level/sn14_.pst | 4645 bytes，原任务入口 | `2956d5024709ec2b5eb120dc412bc2f645f6e256b08be36b387a354f9ead8b5b` |
| Level/npc14_01.pst | 大刀哨兵，Model2，Weapon8，Weapon2=2，Team2，Spawn0，HP1000 | `5a2fc428062217748db007e8867ebd6c94ea4181cfe9e4c9b5205e0c674e2e48` |
| Level/npc14_02.pst | 铁枪哨兵，Model8，Weapon7，Weapon2=2，Team2，Spawn33，HP1000 | `c9aec3863d7cd78bf8cab09494c110f4cbb322a1c24f27a6bd8bc5bbffb72b31` |
| Level/sn02_.pst | 秦皇陵，Rule5，只有配置，无任务回调/NPC | `3a1c28bf1d11827b273c42e34c33a4d955fe7309ca69b4f1dfa7cb9c58ce7cae` |

以上 SHA 已与用户原目录逐项重新比较一致。原 `menu.res` 只按地图 ID 列出地图名，`singlerec.ini` 是十条 `level14` 保存记录，不能据此证明剧情顺序。当前开放内容应称“炎硫岛任务”，不能用 SN02 推出“第二关”。

## 新接线

原脚本在铁枪哨兵丢失后重见玩家时调用 `Perform(c,"attack")`。宿主把它适配为 NPC 的单次攻击请求，保留原 `patrol/follow/kill` 行为；引擎仍检查目标存活、正常兵器距离、场景视线、动作状态与 `canAttack`，接受原出招后才消费请求。`StopPerform`、死亡、移除和退出任务会取消请求。该请求时序是 Web 适配，尚非原 EXE `Perform` 内部实现；`PlayerPerform attack` 仍显式未支持。

原场景 `sn14/sn14.pst` 初始化箱、桌、椅、壶等库，源文件没有显式 `GameOver`。胜利沿用 Rule10 的“敌对 NPC 全部击败”宿主推断，并保留 1.2 秒结算延迟；不能称原 GameRule 已恢复。

## 6 项独立验收

复现命令从项目根目录执行：

```sh
node --test tests/native-mission-island.test.mjs
node work/meteor-original/evidence/mission02-sn14-readiness-2026-10-26.mjs
```

最终单文件 **6/6 通过，29,068.305041 ms**。原始 TAP：[mission02-sn14-tests-2026-10-26.tap](mission02-sn14-tests-2026-10-26.tap)，SHA-256 `a682eb222d651cfcb630d1a1ffad9d8b17648326256c58dd7e433588d53ae019`。

| 验收 | 通过的实际行为 | 边界 |
| --- | --- | --- |
| 原配置与开场 | 原两 NPC、原玩家 HP/兵器、真实地面、双方原对白、WP巡逻序列 | 未据此声称原完整 AI 一致 |
| 路线 | 普通前进输入从原 WP34 沿 34→4→31→0→33 走到两守卫源位置，全程没有重新放置玩家 | 冻结 NPC 反击，单独验证真实几何导航 |
| 原重见攻击 | 原 PST 确实执行丢失/重见分支，发请求后开始原姿态，保留 patrol/follow/kill；StopPerform/死亡/退出取消 | 使用附近探针位置触发原分支 |
| 攻击限制 | 请求不越距攻击，也不能穿过实际射线中的控制三角墙；正常条件接受后才消费 | 额外三角墙用于隔离遮挡判定 |
| 隔离胜利 | 正常原长剑攻击累计扣除真实2000 HP、两次击杀、两条原死亡对白、唯一推断胜利，重开恢复原配置 | 冻结敌方物理反击，玩家置于 NPC 原位置附近；不是完整活 AI 通关 |
| 自然失败 | 活原守卫实际造成伤害，88.70 模拟秒后 HP0、唯一失败；重开清怒气、接触计数和请求 | 玩家先置于守卫附近，30 FPS，测试进程固定随机源以稳定 Web AI 冷却间隔；没有直接赋值 HP/dead |

测试读取真实 GMB/DES/FMC、SKC/BNC/AMB/POS、武器和 RES/PST；仅图像解码、音频、标签画布和浏览器渲染循环被略去。原 scriptId 分配顺序独立于异步资源加载完成顺序，验收按 scriptId 比较原配置。

## 独立证据及剩余边界

[准备度探针 JSON](mission02-sn14-readiness-2026-10-26.json) 保存原配置、实际地面、原路线逐点行走位置、原死亡对白和正常剑攻击2000伤害的独立输出；[探针源码](mission02-sn14-readiness-2026-10-26.mjs) 可复现。它没有证明人工游玩或原 EXE 动态行为。

本地原曲 `music/s2.mp3` 为 1,659,820 bytes，SHA-256 `1b180691fe28564fd3270dc87f1e1f78aeb4bc42b2aad7af47f8fa602b7ba595`。仅核实原文件身份；sn14→S2 的关卡映射没有本地硬证据，当前属于 Web 配乐选择。

独立 [原hell语义证据](E-native-hell-semantics-2026-10-26.json) 已确认 `hell` 是直接死亡区域：00563300分类type4，00564ab0角色原包围体重叠返回result2，004ebc10发送0x18死亡事件、设置actorstate2并增加死亡计数。不是按周期扣血，也不经角色防御/阵营伤害公式；HP0是Web/PST状态映射。当前脚点连续段对原几何体的检测仍是Web适配，六项测试没有覆盖该独立运行链，不能冒称原完整碰撞算法。完整活 AI 人工胜利、原剧情顺序、完整原 NPC 物品/副武器策略和原 AI/物理仍未证明。浏览器视觉与全套最终验证由主代理另行记录。本分项没有上传或部署网站。

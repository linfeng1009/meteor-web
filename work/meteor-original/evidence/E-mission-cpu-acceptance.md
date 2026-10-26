# 原首关 CPU 联通验收

日期：2026-10-23（Asia/Shanghai）。验收入口：`tests/mission-acceptance.test.mjs`。

- id: E-mission-cpu-acceptance
- observed_at: 2026-10-23（运行日期；未记录开始时刻）
- source_type: command / log
- source_ref: `node --test tests/mission-acceptance.test.mjs`
- artifact_path: `evidence/mission-cpu-acceptance.tap`
- content_hash: `sha256:d9d150fbd1f8eb846f852f6994dc6f235020226d4e91603548a4bed6dcbe9d7d`
- linked_workitem: WI-013
- supersedes: none（补充原 E-mission-host，不覆盖历史 38 项记录）

最终独立验收 7/7 通过，耗时 25.55 秒；已验证的58项快照与后续机关集成状态见 [E-validation-current.json](E-validation-current.json)。

执行命令：

```sh
node --test tests/mission-acceptance.test.mjs
```

原始结果：同目录 `mission-cpu-acceptance.tap`。此验证不启动浏览器，不修改 Downloads 内原样本。

## 范围与证据

CPU harness 直接运行 `MeteorGame` 的原地图读取、人物创建、装备、关卡启动、移动碰撞、骨骼动画、命中、伤害和结束代码，以及实际 PST VM、POS/ACT、AMB/SKC/BNC、GMC、DES/T 地图三角形、WP 和 RES 数据。仅省略 WebGL 渲染、纹理解码、音频播放、名字贴图和浏览器事件循环。

1. 原首关玩家为孟星魂：1500 HP、item 5 匕首、item 1 七星副武器，出生 WP9。原三名 NPC 为 Model8，分别使用 item 7 / 7 / 16，HP 1000 / 1000 / 2000。四人均落在实际碰撞地面，原开场对白执行，PST diagnostics 为 0。
2. 在原 NPC 出生附近隔离验收匕首接触：通过原动作、骨骼、兵器几何和 RES 伤害解析，确实减少原 NPC HP。没有给 NPC HP 或 dead 标志赋值。
3. 真实副武器切换后，原 P0.POS200 窗口从实际 d_wpnR 手骨释放一枚原 W3_0。6 米外原 NPC 在释放时不扣 HP，实际飞行扫掠命中后才扣 HP，事件含 projectileId，投射物以 actor 原因消失。
4. 从 WP9 沿原图边走至 WP53，再至 WP80 和 WP32，运行真实玩家移动、重力、落地、台阶与地图碰撞。路线无需先破坏机关。WP9→WP53 为：9→11→5→6→7→1→4→74→63→65→64→37→67→32→53。
5. 玩家进入原 WP67 警戒区时，原巡逻/发现/报告控制能够接近并用真实攻击扣玩家 HP。
6. 胜利链隔离验收：冻结 NPC 物理反击，逐个在原出生位置附近以正常匕首攻击耗尽 1000+1000+2000 HP。关卡时钟、PST、原 HP 阈值和死亡对白继续更新；断言真实累计伤害恰为 4000、击杀 3、原哨兵长死亡台词执行、唯一胜利回调、停止更新、重新开始恢复原配置。没有直接设置 NPC HP/dead，也没有直接调用 kill/finish。
7. 自然失败链：不定位、不改 HP，从 WP9 使用普通前进输入沿原路径走到 WP53，再持续前进靠近活敌；玩家不攻击，由原敌实际命中耗尽 1500 HP。断言唯一失败、死亡不复活、重开后原 HP/武器/三 NPC/击杀死亡计数、怒气和接触计数恢复。

## 必须保留的边界

- 第 6 项冻结 NPC 反击，是伤害到完成结果的隔离验收，不能称作完整人工实战通关。
- 第 7 项是真实起点、真实路径、活敌和正常输入的失败流程；这证明联通性和失败恢复，不代表玩家战斗策略足以通关。
- Rule10 的“三名敌对 NPC 全部死亡即胜利”明确为浏览器宿主推断。`sn01_.pst` 本身没有 GameOver 调用，验收同时检查结果 provenance 保留 inference。
- 碰撞体、运动、投射物飞行常数仍是明确标注的浏览器适配；不能把 CPU 通过描述为完整还原了 EXE 所有物理/AI 内部实现。

## 探索性实战记录

`work/mission-live-probe.test.mjs` 是可选诊断脚本，不属于发布回归命令。它从原 WP9 真实步行，保持所有原 NPC AI 活动，仅使用移动、锁定、攻击和换武器。

- 匕首追击策略：约 53.85 秒玩家死亡，真实伤害 1002；没有完成通关。
- 七星保持 4–7 米策略：约 86.68 秒玩家死亡，击杀一名原 1000 HP 哨兵，真实伤害 2372；正常触发 player-death 失败回调。
- 更远距离策略在原洞穴地形中出现长时间无新增命中，已中断；不能据此断言投射物失效，实际原地图会遮挡飞行路线，正式第 3 项已在实际地形和人物上验证飞行命中。

旧“原 WP67 静止 90 秒必须被杀”的断言已移除：原 PST 报告后两哨兵 follow 哨兵长，哨兵长可能 wait，最终三人距静止玩家约 17 米。静止玩家未死符合该脚本状态，不能把它当持续接敌缺陷或通过改 HP 绕过。

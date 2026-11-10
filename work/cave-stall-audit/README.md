# 首关偶发停滞复现调查

结论：**没有复现此前玩家剩287HP的停滞，不能把该问题标为已修复。** 本轮只写了本目录的探针和记录，没有修改`dist/`、`tests/`或原客户端，也没有使用浏览器。

旧失败记录为`work/meteor-original/evidence/native-runtime-directional-guard-resumed-2026-11-06.tap`。当时没有记录随机序列、初始角色顺序和碰撞/脚本快照，仅靠HP287无法准确重放。

## 已完成的有限检查

- 公共生产式CPU夹具，jitter seed5–16：12例均正常受到原攻击并死亡，41.63–74.80模拟秒。
- seed5下，对原NPC PST读取按0/35/70ms错开，实际得到全部六种NPC数组顺序：6例均自然死亡。顺序确实改变战斗时序，例如123为46.13秒，321为61.63秒。
- 与原acceptance测试一样省略场景伤害resolver的夹具，seed5–16：12例也全部自然死亡，41.70–74.80秒。其中出现18次`damagePending`场景接触，涉及原石块/箱子。

所有驱动从源任务初始化后，只改变镜头朝向并发送正常前进输入。没有给HP、角色位置、dead、AI意图或胜负赋值。攻击判定、原武器/骨骼、PST和地图碰撞继续由实际运行代码执行。检查会在连续20模拟秒无掉血时记录停滞候选，但本轮30例均在此之前自然死亡。

## 已确认的两点

1. **固定jitter seed不等于完整重放。** `NativeMissionHost.addNpc/instantiateNpc`异步读取脚本、模型和装备；`game.enemies`以及宿主角色/VM容器的插入顺序受完成时序影响。引擎按数组顺序更新和分离角色，随机冷却也因此可能分配给不同NPC。本轮自然改变读文件时序已证实顺序和死亡时间会变，但未证明它造成旧停滞。
2. **acceptance夹具少了一项生产接线。** `tests/mission-acceptance.test.mjs`的`cave()`只安装角色伤害resolver；正常引擎初始化和公共夹具还安装`createNativeSceneDamageResolver`。缺少它时，NPC打中原石块/箱子只产生`scene-contact/damagePending`。这是真实夹具差异，但精确匹配该差异的12例仍正常死亡，因此不能称它是287HP的实因。

建议保留旧失败，未来失败时一并记录随机draw、初始engine角色顺序、宿主角色/VM顺序和LOS/碰撞/PST状态。可以独立修正acceptance夹具的场景resolver接线以与生产一致，但不要以此宣称停滞已解决，也不要改变源PST意图或强制伤害来让失败检查通过。

## 证据与重放

[结构化结论及逐文件SHA-256](summary.json)列出全部记录。`seed-*.json`为公共夹具，`order-*.json`为六种读取时序，`acceptance-seed-*.json`为省略场景resolver的匹配夹具；其中包含末态、过程快照和实际伤害事件。

```sh
node work/cave-stall-audit/probe.mjs 5 6 7 8 9 10 11 12 13 14 15 16
node work/cave-stall-audit/permutation-probe.mjs
node work/cave-stall-audit/acceptance-probe.mjs 5 6 7 8 9 10 11 12 13 14 15 16
```

命令会重新写入相应探针输出。源码指纹以`permutation-run-source-hashes.json`和`acceptance-run-source-hashes.json`标明；最初公共夹具的通用指纹文件后来被读取时序调查替换，不将它冒充首次运行的源码快照。

按父任务转向其他关卡的要求，本轮到此停止，不再扩大矩阵。有限样本通过不证明全部随机、加载顺序和玩家输入路径都没有停滞。

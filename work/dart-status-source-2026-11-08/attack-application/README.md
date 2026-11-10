# 招式附加道具的原命中链

2026-11-08，本地原样本只读静态审计。授权沿用 `work/meteor-original/scope.md`；未运行原 EXE、浏览器或网络请求，未修改运行代码与测试。原样本 SHA-256：`289afb0aa44a47921d167fc24d6d404c60d6d00c299ac27d45fc61e16231b498`。既有导入表锚点为 `work/meteor-original/evidence/E-imports.json`。

## 已确认的作用顺序

原服务端 `004af630` 从命中包解出实际姿态 `poseId = packet.word1 & 0x3ff`。攻击类型来自同一个包的位 10–15。它解析攻击者和目标，双方必须存在且其 `+0x200 == 1`；目标计时条件也先于下述分支。完整原目标筛选、联网反重放和计时生产者并非本次恢复范围。

1. 当攻击类型为零，且目标 `+0x20c == 1`，进入防御分支。该分支发送护架消息并可能给目标加怒；`004af87c` 直接跳到函数尾 `004afbf9`。**不会解析参数 16，不施加招式附带道具。** 原攻击类型允许破防时走普通受击分支。
2. 普通受击分支以攻击者原 stat virtual `+0x38` 扣目标 HP。同队掩码交叠时仅将直接伤害倍率改为 0.2。
3. 读取扣血后 HP，再以目标 stat virtual `+0x2c` 加受击怒气。原乘除链为 `floor(14 * (HPbefore - HPafter) / 100)`；它在附加道具之前执行。
4. HP 为零转死亡分支；不解析参数 16。HP 仍非零才继续发送受击反应，再调用目标 stat virtual `+0x48`（`004d5fc0`）查实际姿态的 type3 RES 参数 16。
5. `004d5fc0` 以该参数指向的 ID 读取 type2 道具，拷出原记录。不存在参数或道具时返回零。
6. `004afa65` 调 server virtual `+0xfc`。服务端虚表基址 `005a9bf8` 由构造/析构写入确认，槽地址 `005a9cf4` 的原指针为 `004afcf0`。
7. `004afcf0` 按目标 ID 找角色；重新读取 `(itemType,itemId)` 的 RES 记录；调用 `victim+0x88` 的 stat virtual `+0x24`，即 `004d59d0(record,0)`。成功后广播 `0x3d`。这段函数没有新增队伍、伤害量、霸体、时间或攻击者自身条件。

因此八方绝的 `item22` 应在正常受击加怒之后立即减怒，而不是先减再加；落樱雪的 `item12` 应在非防御且存活的命中后添加/刷新。普通分支没有“直接伤害必须大于零”的门，目标防御属性足够高导致 HP 未变也仍走附加道具。源中同队倍率也未阻止附加道具；宿主若另有敌我筛选，应与此服务端语义分开说明。

## 精确地址

| 位置 | 原行为 |
|---|---|
| `004af78a–004af7a0` | 选择零攻击类型且目标防御分支 |
| `004af879–004af87c` | 防御加怒后直接跳函数尾 |
| `004af90e` | 原直接伤害调用 |
| `004af921` | 读取伤害后目标 HP |
| `004af95f` | 目标受击加怒 |
| `004af964–004af966` | HP 非正转死亡；活着才处理附加道具 |
| `004afa48` | type3 真实姿态参数 16→type2 item |
| `004afa65` | server `+0xfc` 应用附加道具 |
| `004afd24–004afd2c` | 目标 ID 查找有效性 |
| `004afdcf–004afddd` | 原 RES item 查找 |
| `004afdfa–004afdff` | 目标 stat `+0x24` 添加/立即应用 |
| `004afe24` | 成功后广播 `0x3d` |

`004d59d0` 对 type2 且没有寿命参数 1 的记录，直接应用其有效非负 effect-type 条目，没有把它放入定时 active 列表；重复有效命中可再次应用这种即时效果。带寿命且已存在的相同 type2 ID 则更新原参数 2，而不新增第二份条目。其周期时钟和 clamp 的细节由同轮 `stat-consumer` 审计记录；本次不把定时刷新理解为叠层。

本次没有重新证明所有原几何接触频率或联网去重策略，不能从每次服务端有效命中都会施加道具，推导出每个粒子或每帧都可重复命中。现有宿主共享的攻击身份去重仍应保留。

## 证据与复现

- `pass1`：新导出 `004af630`、`004d5fc0` 的 C、ASM、引用与索引。
- `pass2-retry`：新导出服务端虚表写入者 `004abaa0`/`004abf50`、`004afcf0`、`004acae0`、`004d5fc0`，以及 `005a9bf8`/`005a9cf4` 数据和引用。
- `pass2.log`：另一个只读 Ghidra 任务持有项目锁时打开失败，exit 1；保留原失败记录。对方明确 exit 0 释放锁后，`pass2-retry.log` 顺序运行 exit 0，不删锁、不杀进程、不修改项目。
- `evidence.json`：原样本、源证据、导出与日志 SHA-256 索引。现存旧 stat 反编译作为参考，其关键命中顺序以本轮 ASM 为准。

在项目根目录复现（先确保其他 Ghidra 调用已退出）：

```sh
JAVA_HOME=/opt/homebrew/opt/openjdk@21/libexec/openjdk.jdk/Contents/Home \
JAVA_TOOL_OPTIONS=-Duser.home=/private/tmp/meteor-ghidra-fpu-home \
/opt/homebrew/Cellar/ghidra/12.1.4/libexec/support/analyzeHeadless \
  work/meteor-original/ghidra-project MeteorOriginal \
  -process Meteor.exe -readOnly -noanalysis -scriptPath scripts/analysis \
  -postScript ReadOnlyHitReactionTrace.java /private/tmp/meteor-attack-item-repro \
  004af630 004d5fc0 005a9bf8 005a9cf4 004afcf0
```

Evidence→Finding→Path：本轮原 C/ASM 与虚表数据 → 参数 16 是非防御存活受击后的目标道具路径，位于受击加怒之后 → 实际命中姿态→原 RES 引用→目标 stat 应用→广播。`severity=n/a_re`、`category=reverse_algo`、`status=validated`、`confidence=high`，限上述读取路径。完整原命中筛选、同步时序、附加道具视觉、所有状态与浏览器实战仍未验证。

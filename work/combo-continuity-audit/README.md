# ACT组成员与连招入口

2026-11-07。纯离线静态/CPU审计，沿用`work/meteor-original/scope.md`授权，不运行原客户端、不访问浏览器。

## 发现

当前输入目录把一个完整招式记作根姿态，但原ACT允许前招接入该招式的其他成员。例如枪挑281之后的万圣龙王破直接接294冲击段，不从293气罩起手；这是原动作分支，不应强行重放整套起手。

| 前招 | 输入指令的根姿态 | 原允许列表中的同组成员 | 修改前 | 修改后 |
|---|---:|---:|---|---|
| 剑264 | 368 | 369 | 拒绝 | 接入369 |
| 枪281 | 293 | 294 | 拒绝 | 接入294 |
| 刀299 | 310 | 313 | 拒绝 | 接入313 |
| 刀301 | 310 | 312 | 拒绝 | 接入312 |
| 双刺231 | 233 | 234 | 拒绝 | 接入234 |

## 原证据

`0055d020`接收group索引，首次/强制起手查`+644`的group表首成员；非强制路径和`0055d130`依次遍历当前姿态`+70`的允许目标列表，将每个目标的`pose+68 groupId`与请求group比较，首个匹配写入`controller+624`。`0055d450`随后播放实际目标的第一个Action，并沿用原过渡时间。既有导出路径及SHA-256在[evidence.json](evidence.json)中。

这不是把所有同组姿态互连：例如262不允许368所在组，279不允许293所在组；自动POS link本身也不是额外的ACT许可。请求264但当前为262时，原列表第一个匹配仍是263，不能按数值大小或优先精确请求成员跳过它。

## 修改

仅改`dist/native-combat.js`与新增`tests/native-act-group.test.mjs`。`parseAct`保留原literal `canLink`并添加`groupIds/resolveTransition`；busy `play`按原顺序解析实际成员，现有队列时机不变。`queued`保存实际成员，`queuedMove/currentMove`仍保留根指令context，怒气实际起手只扣一次。自动POS链、资源失效、受击中断及既有空中恢复/落地策略继续保留。

## 复现与验证

```sh
node work/combo-continuity-audit/probe-act-groups.mjs
node --test tests/native-act-group.test.mjs tests/native-combo-controller.test.mjs
node --test tests/native-command-engine.test.mjs tests/native-hit-reaction.test.mjs
```

[before.json](before.json)与[after.json](after.json)保存同一真实POS/ACT和生产控制器的前后结果。新增7项组语义检查+12项既有控制器检查，共19/19通过；既有引擎/受击检查42/42通过。两组不是额外独立的61项新增。运行模块语法与whitespace检查通过。

首次候选实现把公开`queued`标记仍写成指令根，测试抓出后改为实际成员；另一个测试误把0.5秒当作空中第二剑固定时长，改为正常推进直到原自动link出现。失败日志[group-tests-first.tap](group-tests-first.tap)保留，最终见[group-tests-final.tap](group-tests-final.tap)。

Evidence→Finding→Path：原ACT组与允许列表、0055d020/0055d130 → F-GROUP-01（原组入口遗漏，validated）→ 指令根映射group → 按前招允许列表首个同组成员 → 现有排队与一次耗怒 → 原动作与后续POS link。

未声称恢复完整原方向识别、全部耗怒触发链、群战AI或浏览器人工实战；root仍需完成本阶段总集成和全套回归。

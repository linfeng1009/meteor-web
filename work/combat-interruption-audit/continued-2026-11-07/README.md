# 原受击状态7/9与命中前过滤复核

2026-11-07。沿用[授权范围](../../meteor-original/scope.md)，仅本地原PE的Ghidra/r2只读分析；没有执行原EXE，也没有修改dist或tests。静态原样本SHA-256仍为`289afb0aa44a47921d167fc24d6d404c60d6d00c299ac27d45fc61e16231b498`。

## 结论

状态7已闭合为死亡动画路径，不能当普通招式霸体。004af630在原HP属性2归零时发送0x18；004ed9d0接收0x18后调用actor+dc=004f0140；后者调用controller+16c=004cc0a0，播放原pose117并通过setter写7。004cc130 case7执行004cde00，等待动画结束状态4后发送局部命令0x0f及0x15。

状态9存在已验证的死亡后等待入口：004cde00在死亡动画结束且局部0x15命令成功后写9。004efb20的0x15分支返回`manager(+2b4)(manager+2260)==0`；当前004cc130没有case9，因此这个更新分支不推进普通运动。尚未完整恢复manager判定及所有动态赋值，不把9的全局枚举名强定为“观战”或“重生”。它也不能证明普通攻击应带霸体。

普通受击包004f3f50直接调用controller+48=004d03f0；后者仅对7/9拒绝切反应，其他状态强制进入给定反应并置4。命中收集之前的004f3380+128经004f2ad0/004f2b10，仅在本次所读函数内体现角色存在、全局覆盖和掩码条件，没有按目标当前攻击姿态免打断的分支。掩码生产者、状态/脚本改写、其他碰撞分支尚未穷尽，所以这不是“原版不存在任何霸体”的结论。

原pose367确有“一般氣爆”标签及攻击体，但其输入、耗怒和可中断状态仍未闭合；actor局部0x10/0x11也是怒气门槛/消费相关通用分支，不能仅据数值直接映射到爆气解围。

## Evidence → Finding → Path

| Evidence | Finding | Path |
|---|---|---|
| 构造函数004cabd0/004cada0、原表005aa6a8及004d0500/004d0510 | 当前控制器状态在+dc；7/9判断不是旧错误虚表推断 | 正确虚表→+12c setter/+130 getter→004d03f0 |
| 原HP归零消息0x18、actor004f0140、controller004cc0a0与pose117 | F-AR01，validated/high/n/a_re：state7属于死亡动画入口 | HP归零→消息0x18→controller+16c→pose117→state7 |
| 004cde00与004efb20 case0x15 | F-AR02，validated/high/n/a_re（限此入口）：动画结束后条件进入9 | state7→动画finished→局部判定→state9等待；全局枚举名未证实 |
| 004f2ad0、004f2b10及004f3f50→004d03f0 | F-AR03，validated/high/n/a_re（限所读路径）：没有普通攻击姿态的专门免反应检查 | 存在/掩码过滤→命中包→普通反应；不能推广到全体特殊状态 |

完整原文件、反编译/汇编、命令日志及SHA-256在[evidence.json](evidence.json)。立即数候选扫描只发现两处：004cc0d1的PUSH7和004cde56的PUSH9；扫描不覆盖寄存器合成参数和远距离数据流，这个限制保留在证据中。源函数动态未执行。

## 复现

在`meteor-web`目录，以既有Ghidra项目运行（不重新导入或运行原EXE）：

```sh
JAVA_HOME=/opt/homebrew/opt/openjdk@21/libexec/openjdk.jdk/Contents/Home JAVA_TOOL_OPTIONS=-Duser.home=/private/tmp/meteor-ghidra-fpu-home /opt/homebrew/Cellar/ghidra/12.1.4/libexec/support/analyzeHeadless work/meteor-original/ghidra-project MeteorOriginal -process Meteor.exe -readOnly -noanalysis -scriptPath work/combat-interruption-audit/continued-2026-11-07 -postScript ReadOnlyControllerStateScan.java work/combat-interruption-audit/continued-2026-11-07/state-writes
```

下一步若继续原群战差异，应追掩码生产者/原AI出手调度或气爆输入，不能把死亡状态保护改成通用出招霸体。已交给主代理，不需要修改当前运行逻辑来“适配”7/9。

- [x] 现有授权、真实工具路径和只读样本哈希已复核。
- [x] 状态候选按控制器/actor对象分别核对，没有混用相同偏移。
- [x] 原C/ASM、引用、立即数扫描和未覆盖范围已保存。
- [x] Findings与调用Path已区分观察事实和待确认枚举。
- [ ] 原霸体、爆气输入、掩码生产者与完整群战AI仍未恢复。

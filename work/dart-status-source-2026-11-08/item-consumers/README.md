# 原附加道具消费者与时钟

2026-11-08，本地授权范围沿用 `work/meteor-original/scope.md`。只读静态检查原 `Meteor.exe` 与已保留的 `Meteor.res`，未运行原 EXE、浏览器或联网。未修改 `dist/`、测试或案件授权。所有新脚本、源导出和说明均在本目录。Ghidra 使用既有 `MeteorOriginal` 项目与 `-readOnly -noanalysis`；`scheduler-targets`/`death` 仅在内存中补建已有代码入口，日志确认退出时丢弃，不保存项目变更。

## 可实现规则

- **气丧 item22**：原参数1/2/8均0；effect `[2,0,6,0,0,0,-20,0,0,0]`。`004d59d0` 对 type2 先查已存在同ID；新item参数1为0时走立即效果，不插入定时列表；stat6减20。`004d4d30` 将stat6上限映射effective stat7，按当前base+extra+delta夹到0..max；`004d59d0` 将夹取后的delta加到base。不是空间吸引，也不是持续减怒。
- **怒气上限默认100**：`004d4a70` 初始化stat6为0、stat7为100。汇编 `004d4b45`写key6；`004d4b7e MOV EDI,0x64`、`004d4b85`写key7、`004d4b8d`写valueEDI。原stat7可经effective-stat路径变化，因此100是默认值，不是覆盖角色原stat7的硬上限。
- **蛊毒 item12**：参数1/2=600、8=10；effect `[2,0,2,2,1,0,-10,0,0,0]`。参数1>0走定时列表插入，无立即HP变化。word3=2是周期阈值，word4=1是效果类型；以前审计中的“每1秒”推断错误。原HP夹取沿stat2→effective stat1。原duration名义60秒。
- **七星 item11**：同一周期消费者，参数1/2=150、8=10；effect `[2,0,2,3,1,0,-10,0,0,0]`，名义15秒，周期词3。数据保存在 [原记录](original-item-records.json)。
- **刷新**：`004d59d0` 同type2同ID的已有记录仅复制新参数2的value和extra两个words；不复制effects、不叠加列表、不清空word9计数器。不同item11、12、14属于不同ID，可以并存。

## 原5Hz调度和精确顺序

服务器构造 `004abaa0` 使用虚表 `005a9bf8`，+4=`004b1d60`主更新、+b4=`004b24e0`属性更新、+c8=`004affd0`死亡检查；stats构造 `00492690` 最终表为 `005a9490`，+4=`004d5020`、+4c=`004d4e30`、+24=`004d59d0`。

1. `004abe80` 在 `004abec4` 将double5.0传给 `00549950`，ECX指向server+2a0。`00549950` 设置频率，并用QueryPerformanceFrequency/频率生成间隔。因此是5Hz。
2. `004b1d60`（server state3）在 `004b1e05` 对server+2a0调用 `005499a0`；成功后 `004b1e16 PUSH 0x3e4ccccd`，即float32(0.2)，`004b1e1d CALL server+b4`。
3. `004b24e0` 对树内每个actor调用stats+4(float0.2,0,0)，随后server+c8检查死亡。客户端 `0048aeb0` 也有同样5Hz timer和float0.2的独立表现更新。
4. `004d5020` **先判断寿命到期**。`004d50b1 FILD remaining; FCOMP; FNSTSW AX; TEST AH,0x41; JP continue`：有序有限比较中remaining**小于或等于**rate*dt均直接删除，不调用周期消费者；仅大于时用`remaining -= ftol(rate*dt)`后调用stats+4c。最初口头解读为严格小于已纠正，不能保留0到下一step。
5. `004d4e30` 在 `004d4e98 CMP counter,word3*10; JC accumulating`。进入调用时counter>=阈值才应用一次delta、将counter清零；小于时仅累积 `ftol(counter+10*dt)`。整体求和由 `004d4fb0 FLD dt; FMUL float10; FIADD oldcounter; CALL ftol; MOV counter,EAX`证明。一调用至多一次tick，不是无条件覆盖counter，也没有while补齐。

因此不能在每个RAF 1/60秒上直接照搬ftol；原生产调用使用专用0.2秒步进。按原步进、初始word9=0，独立 [算术oracle](source-clock-oracle.py) 得到 [输出](source-clock-oracle.json)：item12第11step首次变化、每11step一次（约2.2秒），60秒内27次；item11第16step首次变化、每16step一次（约3.2秒），15秒内4次。原全局tick相位决定命中后的实际首次等待时间；这些是源循环算术，不是运行原游戏的测量。

`005499a0`会返回逾期次数，但该server调用只判断非零并调用一次；OS卡顿时并不证明循环补齐全部丢失tick。Web独立actor时钟、保留跨渲染帧时间并补齐逻辑tick，仍是需要注明的时间宿主策略；不能因此声称完全恢复原QPC/全局调度。

## 死亡与来源

`004affd0` 只在actor+1e8状态1且effective HP为0时：发送目标消息0x18与广播0x2c(victimId)，置状态2，在允许计分模式下victim deaths+1，并重置其死亡计时器。它不接收施毒者ID，也不增加施毒者kills。普通攻击致死的 `004af630` 则直接用当前攻击者构造0x17(victimId,attackerId)并增加攻击者kills，两条路径不能混用。item附加消息只携带victim/item身份，不保存施毒者出处；不应凭推测给周期死亡添加原版玩家击杀归属。

原 `004b24e0` 遍历属性树没有HP/死亡跳过，`004affd0`的状态检查阻止重复死亡；`004d6400`清理active列表并重建默认属性。没有在这次检查证明“死亡当刻自动清除全部状态”；Web死亡暂停、重开清除的生命周期边界须单列。

客户端 `0048aeb0` 在周期返回stat2负delta时，调用actor+44返回对象的+48(0x5a,1,0,-1)，与原部分受击路径存在同样的pose90播放调用。它没有经过方向受击/击退/逻辑state链，不能由此制造通用硬直或打断。精确客户端表现与完整原调度不是这份源消费者检查的完成范围。

## 证据与复现

E-IS01 原数据：[original-item-records.json](original-item-records.json)。E-IS02 属性和刷新：[pass4/004d4d30_FUN_004d4d30.asm](pass4/004d4d30_FUN_004d4d30.asm)、[pass4/004d59d0_FUN_004d59d0.asm](pass4/004d59d0_FUN_004d59d0.asm)、[pass4/004d4a70_FUN_004d4a70.asm](pass4/004d4a70_FUN_004d4a70.asm)。E-IS03 时钟：[scheduler/004abe80_FUN_004abe80.asm](scheduler/004abe80_FUN_004abe80.asm)、[scheduler-targets/004b1d60_FUN_004b1d60.asm](scheduler-targets/004b1d60_FUN_004b1d60.asm)、[pass4/004b24e0_FUN_004b24e0.asm](pass4/004b24e0_FUN_004b24e0.asm)、[pass4/004d5020_FUN_004d5020.asm](pass4/004d5020_FUN_004d5020.asm)、[pass4/004d4e30_FUN_004d4e30.asm](pass4/004d4e30_FUN_004d4e30.asm)。E-IS04 死亡：[death/004affd0_FUN_004affd0.asm](death/004affd0_FUN_004affd0.asm)。

F-IS01（validated / high / reverse_algo）：stat6立即效果和type2周期、刷新、到期与原5Hz消费者现已静态证明。Path：原RES参数16引用item → 原命中应用（另见相邻attack-application证据）→ item22立即夹取减怒，或item11/12插入并保留计数的刷新 → server5Hz原周期delta → stat2夹取和独立环境死亡路径。静态证据不等同Web正常输入与活AI验收。

```sh
python3 work/dart-status-source-2026-11-08/item-consumers/source-clock-oracle.py
```

Ghidra重现用本目录两个Java脚本，以及既有 `scripts/analysis/ReadOnlyHitReactionTrace.java`；精确参数见各`.log`。pass1/pass2先检查了错误的+c候选槽，仅保留为排除记录；pass3以后根据构造函数校正为+4。没有据这些错误候选实现玩法。

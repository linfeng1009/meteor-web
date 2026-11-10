# 原 AttackType 的破防条件恢复

2026-10-29。原 POS 的 `attacktype=1` 会绕过守架扣血。此前 Web 命中无条件传入 `target.guard`，使原大刀下劈/冲昏和长枪绕圈/劈地等破防动作被当作普通可防攻击。本次恢复的是原解析→封包→HP分支的条件；没有另造伤害倍率。

授权沿用 [scope.md](../scope.md)；原 EXE 全程未执行。精确地址、源字节、规则表、SHA-256 及导出文件在 [E-guard-break-2026-10-29.json](E-guard-break-2026-10-29.json)。

## Evidence → Finding → Path

| Evidence | Finding | Path |
| --- | --- | --- |
| 原关键字记录005D1974=0x107、005D1978=`attacktype`；原Bison规则0x30为 `KEY_attacktype KEY_number → attacktype` | POS字段由原解析器识别，字段名没有靠猜测命名 | 0057AAF0的case0x30取整后写0072B950 |
| 0057B73A `MOV ECX,0072B920`，0057B73F调用00574C90初始化Attack；0057B58B写0072B950 | AttackType位于原Attack记录+0x30 | 原005754D0将该0x68字节记录加入攻击列表 |
| 004F3548取当前Attack+0x30；004F3555左移10位写命中包 | 发往HP逻辑的是该原字段，不是招式编号或近战/投射标记 | 004AF630解码 `(word1 >> 10) & 0x3f` |
| 004AF78A检查该值；非0跳004AF881正常伤害；值0再检查victim+0x20C==1 | 只有type低6位为0且处于守架态才进免HP的原防御分支 | Web计算有效guard，继续调用已恢复原HP公式 |

原数据中的1满足非零条件。按原6位封包语义，2–63同样绕过，64截断为0，65截断为1；实现无需硬编码“只认1”。

```js
const guarded = !!target.guard && ((attack.attacktype ?? 0) & 0x3f) === 0;
```

该值传入原伤害 resolver，并决定GD/BL命中音效。事件中的 `guardBypassed` 使测试和反馈能分辨当前是否绕过守架。`target.guard` 原布尔值保持原状：此HP分支不能单独证明一个永久取消守架的状态迁移。

## 验证

| 原武器与姿态 | 原Type | 守架目标防15时单窗扣血 |
| --- | --- | --- |
| 大刀298 空下劈 | 1 | 89 |
| 大刀300 冲昏 | 1 | 50 |
| 长枪286 旋风棍 | 1 | 每窗37，共两窗74 |
| 长枪291 劈地 | 1 | 122 |
| 大刀295 基本横斩 | 0 | 0，同时按原防御分支加怒1；无守架时44 |

`tests/native-guard-break.test.mjs` 调用生产 `_applyNativeHit`，使用保存的原POS/RES记录和已恢复原数值公式，检查HP、总伤害、守架怒气、原Type、有效GD/BL音效与事件；额外覆盖undefined/null/0/1/2/63/64/65的字段行为。7/7通过，原始 [TAP](native-guard-break-2026-10-29.tap) 已保存。

```bash
node --test tests/native-guard-break.test.mjs
python3 work/meteor-original/evidence/guard-break-audit-2026-10-29.py
```

审计脚本只读取原PE及其内置Bison调试表，断言规则、记录偏移、MOV与CALL源字节，不执行原二进制。新导出仅限已有命中函数和关键字引用，存于 [guard-break-native-2026-10-29](guard-break-native-2026-10-29/)，Ghidra以 `-readOnly -noanalysis` 退出。

原完整守架角度、受击动作、击退位移、动画状态切换和多人命中事件仍不由这次条件恢复宣称完成。这些数值测试也不替代浏览器中真实全人物的逐帧视觉验收。

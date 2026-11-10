# 飞镖方向输入的投射恢复与 EF 边界

2026-10-29。本增量把 `↑A`（209）和 `↓A`（210）接入现有连续投射系统，使用原七星模型、原攻击窗、原 RES 姿态攻击系数和原 EF 音效。两招均已实测发射、扣血、墙面遮挡和重复采样去重。三条复杂飞镖指令的效果体仍待移植，不能称作全部飞镖特效完成。

授权沿用 [scope.md](../scope.md) 的 granted/offline 样本范围；全程未执行原 Meteor.exe。结构化字节偏移、文件 SHA-256 和导出函数清单见 [E-command-projectiles-2026-10-29.json](E-command-projectiles-2026-10-29.json)。

## 已完成的方向投射

| 输入 | 原姿态 | 原攻击窗 | 原 EF 音效 | 原姿态攻击修饰 | 攻75、防15的单次伤害 |
| --- | --- | --- | --- | --- | --- |
| ↑A | 209 | 3550–3553 | W03FIR02.wav | 50% | 23 |
| ↓A | 210 | 3593–3596 | W03FIR03.wav | 50% | 23 |

原 POS 两姿均没有近战 bone，具有各自的一个攻击窗。Web 适配在攻击窗内从原 `d_wpnR` 发射一个原 `W3_0`，同一 serial/window 不重复生成；它复用已经实现的连续飞行、目标胶囊和地图三角面最近碰撞。一次原窗对应一次 Web 发射是已明示的适配，并非已恢复 EXE 发射器计数。速度、重力、半径、自旋和寿命仍沿用 [E-native-dart-trace.json](E-native-dart-trace.json) 所述的 Web 参数。

原 RES 209/210 的 parameter16 还分别引用 item10/item11。其持续属性传播、时限和完整受击附加状态不包含在本次飞行/伤害增量中。

## Evidence → Finding → Path

| Evidence | Finding | Path |
| --- | --- | --- |
| 原 P0.POS 209/210 的 start/end、Attack，原 Meteor.res type3 modifier50 | 原方向手势和命中时窗已存在，先前 profile 仅列200/202，使这两招空挥 | 将209/210列入 `NATIVE_DART_PROFILE.poseIds`，保留原时窗与数值链 |
| Pos209/Pos210.ef 保存字节，W03FIR02/W03FIR03 字符串 | 两姿使用独立原投射音效 | 沿用原姿态 EffectID→EF→WAV，不生成替代音效 |
| 原 EXE 0058A700→005D2F88 类型表；0056E490 读入流程 | EF 是有父节点绑定和动画通道的形状图，不是按招式名称决定发射数 | 解析原节点 inventory；复杂攻击形状保持未实现状态 |
| 原201/551各12个 `Attack*` SPHERE，绑定各自 `Rectangle_*` PLANE | “八方”名称不能证明八个等间隔飞镖，更不能证明同一帧/同一方向 | 保留201/551输入及未完成反馈，下一步恢复父链、通道时间与命中身份 |
| 原204有 `AttackBall` 和7个 `AttackWave*` CYLINDER（其中两个同名AttackWave06） | 怒招是多个独立带通道的攻击体，不能用一个普通镖替代 | 203→204→205怒招特效体仍待还原 |
| 原259只检查effect、349无攻击；Pos259.ef有绑定d_base的AttackBox | 匕首阎罗依赖原EF攻击盒，不能用人物骨骼代替 | 阎罗保持待恢复，拒绝出招与扣怒 |

## EXE 静态结论

`0058A700` 只匹配类型名称；`0058A6D0` 反查类型名称。原登记表共有12行：AUDIO、BOX、BILLBOARD、CYLINDER、DRAG、DONUT、MODEL、PARTICLE、PATH、PLANE、SPHERE、TRAPE。SPHERE=12、PLANE=11、CYLINDER=5，不能根据构造函数相邻地址互相混用。

`00582D50` 通过 `0058A620` 读取带长度的节点名，随后读取四个公共字段、两个绑定字符串，再读共享通道对象和节点动画通道列表。`00582B50` 从文件读取通道数，构造每个通道并调用其虚表 reader。`00589640` 是 PLANE 的公共字段之后的两数值 reader；`005892B0` 为 SPHERE/CYLINDER 使用的五数值 reader。原属性和通道对象不等于已确认的发射器速度或弹丸数量。

新只读导出保存在 [command-projectile-native-2026-10-29](command-projectile-native-2026-10-29/)，PLANE 的独立 reader 位于 [plane-reader](command-projectile-native-2026-10-29/plane-reader/)。既有读取链见 [E-native-dart-trace.json](E-native-dart-trace.json)。

## 保留的四个未完成效果指令

| 指令 | 原姿态 | 已核实 | 尚缺 |
| --- | --- | --- | --- |
| 地面 ↓↑A | 201 | 原动作、36个EF节点、12个攻击SPHERE及对应PLANE绑定 | 通道取样、父变换、原攻击形状和效果播放 |
| 空中 ↓↑A | 551 | 原动作、35个EF节点、12个攻击SPHERE及对应PLANE绑定 | 同上；不能假设与地面帧时完全相同 |
| 飞镖地面 ↓↑↑A | 203→204→205 | 原起手/衔接、AttackBall、7个AttackWave柱体 | 原通道时序、绑定世界变换、攻击体命中与效果播放 |
| 匕首地面 ↓↑↑A | 259→349 | 原effect攻击窗9551–9553；17个EF节点中的AttackBox绑定d_base | 原攻击盒通道时序、尺寸、世界变换与效果播放 |

这些记录是复杂效果未完成的可重现边界；已实现的免费方向投射209/210和其他近战方向技能不依赖它们。

匕首阎罗的原EF只有一个名为 `AttackBox` 的BOX（偏移15，两个绑定字符串均为 `d_base`），但它并非可直接用固定人物半径替代的近战攻击。原259的Attack只引用 `effect`，自动衔接349没有Attack；剩余16个EF节点包括 `KNightWave01` 柱、PLANE、音效和粒子。原盒的通道、随帧尺寸和完整世界变换尚未恢复，本轮维持待恢复并拒绝扣怒。该文件8351字节，SHA-256为 `74159af5f28d01f9cd54fadfeb9b1048cac4941fa5bde01bf203dde17b46217d`，完整节点信息已纳入JSON。

本轮招式总目录为83项，其中79项可起手、4项效果待恢复；这不等于原游戏全部特效和受击附加状态均已完成。

## 验证与复现

```bash
node --test tests/native-command-projectiles.test.mjs
python3 work/meteor-original/evidence/command-projectile-audit-2026-10-29.py
```

[原始 TAP](native-command-projectiles-2026-10-29.tap)：6/6 通过。测试核查209/210在原时窗之前不发射、原时窗内仅发射一次、使用共享原GMC几何与比例、各自原EffectID、单发扣23且不重复、墙面优先截获。另逐项核对复杂EF文件声明节点总数与已找到节点数相同，并确认12个SPHERE父绑定、7个柱体和阎罗原AttackBox绑定，防止将招式名字当作发射器证据。

这组碰撞测试使用原武器几何和固定手部/目标夹具，证明投射释放、飞行和伤害链；不声称为浏览器全人物逐帧视觉验收。Ghidra使用 `-readOnly -noanalysis`，原项目修改被丢弃，进程已退出，未强删锁。

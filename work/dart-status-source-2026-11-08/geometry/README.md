# 七星原效果几何与绑定修复

2026-11-08。本地原资源与Meteor.exe只读静态分析；复用已授权的[案件范围](../../meteor-original/scope.md)。没有执行原EXE、浏览器或网络操作。本目录探针只直接播放原pose，绕过仍在接入中的公开指令门槛；不能代表附加状态、实际伤害、活AI或人工验收。

## 原始数据与实质缺口

[source-effects.json](source-effects.json)由当前原EF解码器读取pos201/551/203/204，不改原键、父链或碰撞尺寸。201/551均是12个SPHERE攻击节点，经各自Rectangle PLANE→Sphere_3→Character父链；不是8个程序飞镖。204有AttackBall及7个CYLINDER，两条同名AttackWave06都保留在节点数组中。名字查询表用于父节点解析，不会删除攻击节点数组里的同名节点。

203原AttackBall绑定`b`/空字符串，204绑定`b`/`Character`。旧Web代码把空字符串映射为Character，还把key position按位置父骨的旋转变换；这两项都有真实源语义差异，球的对称外观不能证明实现正确。

原调用与证据如下：

| 地址 | 可以证明的原规则 | 留存证据 |
|---|---|---|
| 00582d50 | 四个源flags依次读入metadata+8/+c/+4/+24；flags[3]为后续位置相对模式 | [header-load](binding-header-load.r2.txt) |
| 00582880 | 分别解析并保存位置parent+1e4/矩阵+1dc与旋转parent+1e8/矩阵+1e0 | [setup](binding-setup.r2.txt) |
| 0056e0d0 | ROOT和未命名父节点不等同Character父对象 | [lookup](binding-lookup.r2.txt) |
| 0056e230 | 空字符串或ROOT明确返回owner+5c默认矩阵；Character另走原人物矩阵分支 | [matrix lookup](binding-matrix-lookup.r2.txt) |
| 00582120 | 位置父只贡献平移；旋转父及其矩阵均存在才复制完整旋转矩阵，否则调用00477200单位矩阵；随后替换平移行 | [base matrix](binding-load-and-matrix.r2.txt) |
| 00582210 | metadata+24为0时直接在世界轴加key position；非0调用004781d0相对位移 | [position branch](binding-resolvers.r2.txt) |
| 004781d0 | 参数0分支按原矩阵基向量计算位移后加入平移行 | [relative translation](relative-translation.r2.txt) |

以上r2命令均为只读，版本6.2.4；没有`-w`或修改原样本。构造/vtable及键更新关系另保留[vtables](effect-vtables.r2.txt)、[update](binding-functions.r2.txt)；导入表与全局样本范围沿用原案件证据。

## 修复与验证

`dist/native-effect-transforms.js`现在由旋转父的完整affine矩阵建立基，平移替换为位置父origin；空/ROOT旋转使用原世界轴的Web单位/坐标转换，保留flags[3]的世界/相对分支，不用decompose丢弃shear。视觉与攻击仍共享此函数。

新`tests/native-effect-transforms.test.mjs`有4项有意义的检查：原203空旋转+转身、原204独立绑定、固定非对称世界/相对位移坐标、独立shear父矩阵。新实现4/4通过；[隔离旧代码对照](check-before-regression.py)使同4项全部失败，旧模块副本与失败TAP保留。原接触/视觉20项回归也全部通过。这里没有将4+20当作完整项目验证，整体回归由主任务另行完成。

## 真实原时钟与原root motion下的几何探针

复现：`node work/dart-status-source-2026-11-08/geometry/probe-dart-effects.mjs`。这是原P0角色、生产引擎移动及当前接触体上的CPU平面探针，目标是静态宿主盒；没有直接设置角色高度。551先正常jump到约2.034米，再直接播放原551，最终551→211自然落地。探针独立采样每段EF秒时钟，不按POS帧号假定同速。

| 原pose | 实际采到的攻击形状秒区间 | 建议固定初始目标/结果 |
|---|---|---|
| 201 | .400000–.833333 | yaw0前方5米，约.406667由Attack101命中；8米约.540000、10米约.566667。后方及纯侧方示例不命中；转身形状随原父链旋转 |
| 551 | .433333–.966667 | 正常jump后前方5米地面目标约.633333由Attack301命中，8米约.658333。收段211且落地 |
| 203→204 | 每段分别约.003333–.933333 | 起手203可接触前方2米，前方5米不在起手球内；完整原root最高约13.510米，后段204的AttackWave06在其自身秒钟约.391667接触初始前方5米地面目标 |

204另有直接从地面播放的对照，其结果与203升空后的204不同；不能把该对照充作完整指令射程。精确实例值见[探针JSON](probe-dart-effects.json)的phaseGeometry。最初旧宿主探针输出保留在`probe-dart-effects.log`，修复后最终输出为`probe-dart-effects-final.log`。

Evidence→Finding→Path：上述地址/原EF与旧代码失败 → 独立父绑定和空旋转错误（逆向行为差异，非安全漏洞） → 原父解析/基础矩阵/位置分支 → 共享视觉和接触变换 → 原数据及非对称检查。完整原actor碰撞体、时间量化、IFL/粒子等仍是其他开放项；本目录没有补造或声称这些能力完成。

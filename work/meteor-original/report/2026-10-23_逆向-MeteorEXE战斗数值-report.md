# Meteor.exe 战斗数值与资源覆盖逆向报告

分析日期：2026-10-23。工具：Ghidra 12.1.4、radare2/rabin2 6.2.4、Python 3、Node.js。报告类型：普通离线 PE 格式与算法研究，flavor=null。

## 结论与范围

已从用户提供的原版 Meteor.exe 静态恢复攻击、防御、HP、阵营倍率、受击/防御加怒及属性上下界的运算链，当前 Web 模块通过全部 9 组独立推导样例。原始资源清单已逐项核对，共 3857 个列明文件条目无缺失或哈希错误；人物、场景模型和武器模型分别有独立清单。EXE 的反编译结果是带地址的伪代码及已验证运算语义，没有还原出原始 C++ 工程，也没有执行原 EXE。原输入选择器、方向序列到招式的完整映射，以及怒气消费事件到具体动作的对应关系尚未完成。本报告对这些项目保留未完成结论，不以公开招式表或资源已存在代替 EXE 语义证据。

授权与边界见 [scope.md](../scope.md)：auth.status=granted；in_scope 为用户提供的 Meteor.exe 与 lxhdj_ 本地客户端；活动为静态分析、资源解析、Web 移植与验证；目标分析 network_profile=offline。公开 LXRES 动作表仅用于此前的人物/动作命名交叉核验，不作为本报告公式的证据。

| 样本属性 | 值 |
|---|---|
| 文件 | Meteor.exe |
| 大小 | 1,945,600 bytes |
| 架构 | PE32 x86，machine=0x14c |
| ImageBase / 入口 | 0x400000 / 0x50982e |
| SHA-256 | `289afb0aa44a47921d167fc24d6d404c60d6d00c299ac27d45fc61e16231b498` |
| 反编译范围 | 主项目分析建立8532函数；本分项固定索引保全15个关键函数及汇编 |
| 静态依赖 | KERNEL32.dll, USER32.dll, d3d8.dll, WINMM.dll, DDRAW.dll, DINPUT.dll, DSOUND.dll, AVIFIL32.dll, GDI32.dll, ADVAPI32.dll, ole32.dll, WS2_32.dll, snmpapi.dll |

导入表原件见 E-301；其中 USER32.dll 的 GetAsyncKeyState/GetKeyState、DINPUT.dll、DirectDraw/DirectSound 等反映 Windows 原生输入和渲染依赖。未进行原 EXE 动态运行、Hook 或网络协议测试。

## 已验证运算

角色属性对象位于角色 `+0x88`，虚表为 `0x5a9490`。属性1/2是最大/当前HP，3/4是攻击/防御，6/7是当前/最大怒气。调试HUD直接以属性2/3/4/6显示相应数值；RES中的肉包、嗜战、铜皮与气元条目提供独立数据交叉核验。

| 原地址 | 运算语义 |
|---|---|
| 004d5de0 / 虚表+30 | 基础属性 base + delta；可选out返回base |
| 004d5e30 / +34 | 基础属性叠加当前武器和有效道具效果，最终下限0 |
| 004d61c0 / +40 | 有效攻击叠加姿态RES中的攻击效果 |
| 004d6190 / +3c | 姿态攻击减目标有效防御 |
| 004d5f70 / +38 | 正值伤害扣目标属性2，x87转整型向零截断 |
| 004af630 | 命中事件：正常倍率1、队伍mask相交倍率0.2；受击/防御加怒 |
| 004d4d30 | HP限制0..最大HP，怒气限制0..最大怒气 |

设有效攻击为 A，姿态系数为 c，P 为原float32常量 `0x3c23d70a`（约0.00999999977648）：

```text
mode0增量 = value
mode1增量 = trunc((value * P - 1) * basis)
姿态攻击 = A + 所有适用姿态攻击增量（basis=A）
预测伤害 = 姿态攻击 - 有效防御
实际扣血 = max(0, trunc(预测伤害 * 阵营倍率))
受击加怒 = floor(14 * (HP_before - HP_after) / 100)
防御分支加怒 = trunc(14 * 预测伤害 / 500)
```

防御分支只在预测伤害为正、阵营mask不相交时加怒；原分支还要求命中包指定field为0且受击者 `+0x20c==1`。从原始包构造到POS防御字段的完整追踪未在本分项完成，故这里不把该field擅自命名为某个POS字段。防御分支本身不执行该命中扣血。

`004d61c0` 容易被Ghidra隐藏x87参数的输出误导：004d6284把有效攻击保存于 `[esp+0x14]`；004d62ac的 `push ebp` 将栈移4字节；004d62f1的 `fimul [esp+0x18]` 仍指向该有效攻击返回值。不能将其误认成base-out，也不能把 `A+trunc((c*P-1)*A)` 换成 `floor(A*c/100)`。

普通武器对防御15、倍率1的例子（rawHP尺度）：

| 武器 | 姿态 | A | c | 姿态攻击 | 扣HP | 受击加怒 |
|---|---:|---:|---:|---:|---:|---:|
| sword | 262 | 110 | 35 | 39 | 24 | 3 |
| sword | 263 | 110 | 55 | 61 | 46 | 6 |
| sword | 264 | 110 | 65 | 72 | 57 | 7 |
| spear | 279 | 115 | 45 | 52 | 37 | 5 |
| spear | 280 | 115 | 55 | 64 | 49 | 6 |
| spear | 281 | 115 | 65 | 75 | 60 | 8 |
| blade | 295 | 130 | 45 | 59 | 44 | 6 |
| blade | 296 | 130 | 55 | 72 | 57 | 7 |
| blade | 297 | 130 | 70 | 91 | 76 | 10 |

当前 [native-combat.js](../../../dist/native-combat.js) 保留 `Math.fround(.01)` 和向零截断语义。E-304记录该文件哈希并逐一对照以上9个独立期望，全部通过。[engine.js](../../../dist/engine.js) 在扣血后按实际HP差计算加怒，因此致死截断不会多加怒；此处是移植代码验证，不是原EXE动态验证。

## HP与怒气附加效果

`004bf650` 在查关卡PST的 PlayerHP 前先写默认1000，字段存在才覆盖。`004d4a70` 用 `trunc(floatRatio*1000)` 同时初始化当前/最大HP。调用点004ac453先把整数配置乘0.01；`life_adjust` 在0045b0a0保存到配置对象+0x70，但从该对象字段到游戏对象+0x23c的完整传播链未完成。因此可确认原生默认HP为raw1000及百分比初始化运算，尚不宣称所有联机/模式配置路径均已恢复。

`004af630` 命中后调用**受击者**属性接口+48，由004d5fc0解析姿态parameter16引用的type2道具，再按受击者ID应用。item21(-10怒气)、item22(-20)、item37(-5)属于命中附加削怒效果，不能解释成攻击者出招消耗。服务端004ad530中已定位减60、满100清零、按payload减指定值的事件分支；这些事件到具体输入/动作的触发映射没有确认。

## 当前资源与实现覆盖

此表是E-305的四份清单快照（对应E-306原始源文件清单），统计不能相互替代：

| 清单 | 覆盖 | 大小/可用性 |
|---|---|---|
| [主manifest](../../../dist/assets/original/manifest.json) | 3036资产条目；22地图目录、143 UI、130音频条目、132脚本、1093特效定义 | 93,034,728 bytes；21可用地图 |
| [场景模型manifest](../../../dist/assets/original/scene-models/manifest.json) | 114模型、489独立文件、37 FMC | 12,427,636 bytes；114模型可用 |
| [武器模型manifest](../../../dist/assets/original/weapon-models/manifest.json) | 59道具、71模型、251资产文件 | 7,971,515 bytes；58道具可用 |
| [人物manifest](../../../dist/assets/original/characters/manifest.json) | p0..p19共20套真实SKC/BNC/AMB/POS、20头像；共享17061帧30FPS动画 | 人物树157文件、34,650,212 bytes；30骨骼+6 dummy |

当前原资源发布目录实际共有3936文件、152,507,312 bytes，含转换图像、元数据和各独立清单；并非原客户端650MB全部二进制拷贝。源客户端完整清单记录2090文件、649,397,713 bytes与28个PAK。

已保留的限制：sn22原GMB含非有限顶点，被标记不可用；w6_5缺源模型；场景实例w8_0、w8_3此前清单未找到精确同名cmodel，但追加核对确认其w8_0r/l、w8_3r/l双持组件均在，属于逻辑别名解析问题（见[E-missing-models-research.json](../evidence/E-missing-models-research.json)）；三处纹理n23r05.bmp、n23r06.bmp、n23w01.BMP缺失。缺失项未用程序模型伪称原版资源替代。

人物是原版蒙皮与原版动画；动作时间轴、攻击窗与连招可达图来自POS/ACT。当前模块实际声明的动作家族为 `dart, dagger, sword, spear, blade` 共5种。59个道具/71个武器模型的资源存在，不等于59个道具的所有操作行为均已恢复。COB碰撞单元、原任务VM与机关伤害（场景OnAttack的damage传参链未核实）、完整导航、投射物/全部特效行为、完整原AI与联机同步仍不能仅凭资源已导入宣称完成。

## Evidence → Finding → Path

证据字段原件：[E-301-exe-report-evidence.md](../evidence/E-301-exe-report-evidence.md)。下列命令在meteor-web目录运行；静态导出重做需要保留原样本、Ghidra项目及已安装工具。

| E-id | source_ref | content_hash（SHA-256） | repro_command |
|---|---|---|---|
| E-306 | [完整源客户端文件清单](../evidence/resource-inventory.json) | `9ed0975a4f40b0de39d3aa50ad492c995e0a66cc9632c4d1f3a1ebd1e20443ac` | `python3 -c "import json;d=json.load(open('work/meteor-original/evidence/resource-inventory.json'));print(d['stats'])"` |
| E-301 | [PE身份与导入表](../evidence/E-imports.json) | `b20e79118ee2432a31bb018c2f937fa13e6dfd118740523b74e8b824d3894c5f` | `python3 -c "import json;d=json.load(open('work/meteor-original/evidence/E-imports.json'));print(d['sha256'],d['machine'],d['entryPoint'])"` |
| E-302 | [原EXE属性及命中函数](../evidence/E-exe-decompilation-index.json) | `fff82aabfb9ab5c4f81f10379964b8548ac41e6ffe68fd920db6d19015e41895` | `python3 -c "import json;d=json.load(open('work/meteor-original/evidence/E-exe-decompilation-index.json'));print([(x['va'],x['sha256']) for x in d['functions']])"` |
| E-303 | [RES与x86公式交叉核验](../evidence/E-exe-combat-formulas.json) | `ed62a44fbea278976a36138e492505c0f1b3468afae57c70a52b5347ec2e851a` | `python3 scripts/analysis/document-combat-formulas.py` |
| E-304 | [当前JS与9组原公式样例核对](../evidence/E-formula-runtime-verification.json) | `56af305c23a19a2c8365bb386c816b80a27d6401af7bc143ba8a093060c5022e` | `node scripts/analysis/verify-exe-formulas.mjs` |
| E-305 | [当前四份资源清单文件校验](../evidence/E-asset-coverage-current.json) | `a8b7c49f45398a5453d5e844e07aff891d0bcb68ed3fa6546f7a8c6a0e04dea9` | `python3 scripts/analysis/verify-recovered-assets.py` |

| F-id | severity | evidence_ids | confidence | location | status / 结论 |
|---|---|---|---|---|---|
| F-301 | n/a_re | E-301,E-302,E-303 | high | 004d5e30..004d61c0、004af630 | validated：已恢复基础伤害与防御/受击加怒运算；无原EXE动态运行交叉验证 |
| F-302 | n/a_re | E-302,E-303 | high | 004bf650、004d4a70 | validated：PlayerHP默认raw1000，属性初始化含比率*1000；life_adjust完整字段传播仍未完成 |
| F-303 | n/a_re | E-302,E-303 | high | 004af630→004d5fc0 | validated：parameter16是受击对象附加效果，不能当攻击者成本 |
| F-304 | n/a_re | E-303,E-304 | high | dist/native-combat.js | validated：当前JS算术匹配9组原始样例；不包含原输入识别完整性证明 |
| F-305 | n/a_re | E-305,E-306 | high | dist/assets/original/ | validated：清单资产文件核验通过；资源覆盖与玩法覆盖分开登记 |
| F-306 | n/a_re | E-302,E-303 | medium | 输入selector、004ad530事件触发 | candidate / 未完成：不能确认原方向序列映射及具体动作耗怒 |

### P-301 原始调用链

- path_type: callflow
- start: 原始RES武器/姿态参数与角色属性对象
- goal: 形成可复查的HP损失与怒气变化
- steps:
  1. 从RES的type1武器、type3姿态读取带字节偏移的效果。evidence=E-303；finding=F-301。
  2. 004d5e30得到有效属性；004d61c0计算姿态攻击。evidence=E-302,E-303；finding=F-301。
  3. 004d6190扣防御；004d5f70应用倍率并扣正值HP。evidence=E-302；finding=F-301。
  4. 004af630根据实际损血或防御分支加怒；004d4d30限制属性范围。evidence=E-302,E-303；finding=F-301。
  5. 在Web模块执行9组独立样例并记录文件哈希；核对各资产清单的文件尺寸与哈希。evidence=E-304,E-305；finding=F-304,F-305。
- residual_risks: 无原EXE运行时对照；未完成的输入/耗怒/碰撞/任务/联机行为不在结论内。

## 时间线与复现

主case时间线见 [timeline.md](../timeline.md)。本分项关键记录：

| 时间 | 动作 | 证据/结果 |
|---|---|---|
| 2026-10-22 | 获得本地样本与离线授权，建立完整源文件清单 | scope.md、resource-inventory.json |
| 2026-10-22 | Ghidra建立主项目，恢复属性虚表与关键函数 | E-301,E-302；主项目初始8532函数，不外推完整覆盖率 |
| 2026-10-22 | 通过x87汇编和RES交叉核实公式、HP默认值、削怒目标 | E-303 |
| 2026-10-23 | 收尾时验证当前Web模块与资产清单 | E-304：9/9；E-305：3857条目、0问题 |

最小复现：

```sh
python3 scripts/analysis/document-combat-formulas.py
node scripts/analysis/verify-exe-formulas.mjs
python3 scripts/analysis/verify-recovered-assets.py
python3 scripts/analysis/finalize-exe-report.py
```

复查原反编译项目时，使用 [ExportRecoveredFunctions.java](../../../scripts/analysis/ExportRecoveredFunctions.java) 与 [AnnotateCombatCalls.java](../../../scripts/analysis/AnnotateCombatCalls.java)；Ghidra Java21路径、headless工具路径与项目参数保存在父任务工具清单/已有执行记录。Ghidra会写自身项目与用户缓存，不能把它描述成完全无文件写入；原样本始终只读。

复查导出（从meteor-web目录运行；会写Ghidra项目和用户缓存，原样本不变）：

```sh
JAVA_HOME=/opt/homebrew/opt/openjdk@21/libexec/openjdk.jdk/Contents/Home   /opt/homebrew/Cellar/ghidra/12.1.4/libexec/support/analyzeHeadless   work/meteor-original/ghidra-project MeteorOriginal   -process Meteor.exe -noanalysis -scriptPath scripts/analysis   -postScript ExportRecoveredFunctions.java work/meteor-original/evidence/decompiled   004d4a70 004d4d30 004d5de0 004d5e30 004d5f70 004d6190 004d61c0 004af630 004bf650
```

## 未完成项与收尾状态

本分项的数值公式、证据保全与覆盖核验已收尾。原输入selector、怒气消费到动作触发映射、完整life_adjust配置传播链明确未完成；没有继续以猜测补齐。恢复工作应从现有函数地址、ACT分组对象+0x644与已识别网络事件继续，保留现有证据即可，不需要重新从网站素材开始。完整游戏重构仍应以主任务实现/验证结果为准。

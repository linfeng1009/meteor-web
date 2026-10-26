# 原肉包拾取适配

日期：2026-10-26（Asia/Shanghai）。范围仅原 RES 的 type2 / id1 / Item01 肉包；`dist/native-items.js`，验收 `tests/native-items.test.mjs`。

## Evidence

- `dist/assets/original/characters/meteor-res-data.json` 的原记录 offset53055，名称肉包，model Item01；唯一 effect 为 statKey2、mode0、value300，原值偏移53204。模块通过真实 DES `source.properties.model` 与此 RES 记录匹配，未根据显示名称或网格名猜效果；其他物品不适配。
- `evidence/decompiled/004d4d30_FUN_004d4d30.c` 与 `E-exe-combat-formulas.json` 已证明属性2为当前HP、属性1为最大HP，当前HP调整夹取到0..有效最大HP。当前宿主 `actor.maxHp` 作为已接入的最大HP来源；尚未实现其他增加最大HP的物品。
- 原 `sn01/sn01.pst` `ActiveStoneItem` 激活 `D_itStNN` 并设 interactive1。真实 DES 的 D_itSt22、23、24、25、32 对应 Item01。`tests/native-items.test.mjs` 实际加载 sn01 地图、DES、cmodel、原场景PST，再通过 D_St22 原破坏回调使 D_itSt22 可拾。
- 已保留原 `005637d0` 场景注册反编译包含 `*_OnPickUp`。本轮搜索所有已保留 UTF8 PST/H：只有 sn02 的 `D_IPItem01_OnPickUp()` 声明此回调，sn01 肉包没有声明；因此首关不凭空执行回调或虚构参数。引擎可在成功后执行确实存在的原无参回调。
- `scene-machine-audit-2026-10-26.mjs` 另补真实几何链：实际 NativeProjectileSystem 连续扫掠11发击中 D_St20/Object02，原49伤害使500→-39，播放原破碎pose1、结束state3、隐藏并关闭碰撞，同时激活实际 D_itSt20。此物品为 Item02，不在本次拾取范围。原 Scene_OnInit 能恢复石块500HP、pose0、碰撞开启、掉落物隐藏。

## Finding → Path

原机关掉落激活链已可用，但未有物品消费宿主。新增 `NativeItemSystem.peek(actor)` 提供近处肉包信息，`tryPickup(actor)` 在实际范围与可达性检查后一次性恢复原300 raw HP（夹取到 actor.maxHp），隐藏/禁用该原场景实例；`reset()` 在源场景重新初始化后允许新一局再次消费。消费不改变击中、击杀、死亡与累计伤害。

模块通过 `canReach(actor,instance)` 注入引擎真实地图遮挡判断，通过 `onPickup(result)` 交回实际恢复值与源实例；引擎负责剧情/暂停/结束门、输入、提示、原存在的OnPickUp与HUD。模块自身不绑定DOM或输入。

## 公开的宿主选择

F/触屏显式拾取、水平1.8world范围、垂直2world阈值是Web适配，尚非EXE触发半径恢复。满血时保留肉包也是明确的Web适配；原满血消耗与重生时间尚未核实。当前肉包每个实例每局只消费一次，不擅自添加倒计时重生。其他即时道具、持续buff、武器拾取仍未支持。

## 验证

`node --test tests/native-items.test.mjs`：9/9通过。本轮最终独立重跑约0.34秒，原始输出见 `native-items-2026-10-26.tap`。覆盖真实RES身份和剂量、实际HP恢复/上限、单次消费、满血保留、隐藏/非interactive/距离/高度/遮挡/死亡门、伪装名称拒绝、最近可达选择、reset/dispose，以及真实首关PST掉落→拾取→重置链。

新增两项引擎接线验收：

1. 使用实际 THREE 几何和 `MeteorGame._canReachItem`，目标物品自身碰撞不阻挡拾取，途中静态墙体和其他原场景实例能够阻挡，检测后 raycaster.far 恢复 Infinity。
2. 执行真实 `MeteorGame._initialize` 的物品创建与 `onPickup` 回调，仅替换不相关的渲染/人物创建步骤。真实 `action('pickup')` 在暂停/演武时不恢复HP，剧情时1400→1500，恰发出一次“气血 +100”事件；重复输入不再消费。真实 `_hud` 附近物品仅保留 name/heal/full/distance/objectName，整个HUD可JSON序列化、不带循环instance，消费后pickup为null。

当前文件 SHA-256：

| 文件 | SHA-256 |
| --- | --- |
| `dist/native-items.js` | `28a207420285ea49374a75da718f41698dbb683837b88cd962e93d376b5220d6` |
| `tests/native-items.test.mjs` | `6ad990eb97cdbf93cd21f38c1e04860251faea5740ff93193ed81e3456dae3cb` |
| `evidence/native-items-2026-10-26.tap` | `5f0ea0a749c44cccff04a8c89f66be44f2980680a80890b8156ff72835c71bc0` |

`node --test tests/native-script.test.mjs tests/native-projectiles.test.mjs tests/native-mission-host.test.mjs`：此前只读审计38/38通过。

root已汇总全套83/83测试、11个运行模块语法检查通过。本节9项是单独可复跑的物品验收；38项旧审计记录不应误作最终全套数量。

CPU验收省略图像解码、音频与WebGL；实际人物瞄准/释放、步行抵达合成探针点、浏览器拾取交互、完整人工通关与EXE动态运行不在这些断言内。按钮click与键盘/触屏的完整浏览器拾取实机验收尚未取得，不将引擎action测试描述为浏览器人工拾取成功。

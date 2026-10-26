# 原版七星基础投射接入证据

范围沿用 [scope.md](../scope.md)，只读本地客户端资源。原程序未在本机执行；本记录不宣称完整恢复原投射引擎。

| Evidence | 原始观察 | 浏览器接入 |
| --- | --- | --- |
| E-DART-POS | P0.POS 200：Source0，3511–3533，Attack3517–3519；202：12270–12285，Attack12276–12279 | 每个原攻击窗首次进入时生成一枚投射物；窗口跨帧也能触发，不能把窗口时长当飞行寿命 |
| E-DART-RES | Meteor.res item1 七星/W3_0：攻击75、防御15；pose200/202 stat3 mode1=65（valueOffset20656/20852） | 复用已恢复的 EXE 伤害算式；75+trunc((65*f32(.01)-1)*75)=49，对防15造成34 rawHP |
| E-DART-GMC | cmodel/W3_0.GMC，156顶点、138三角；SHA256 `7be24e3d325796366f291eebd8a690280c81804e525c4fa31c2c04f5c890d136` | 独立飞行物使用原几何/原贴图，native scale0.08，只做一次Z-up→Y-up转换；从手挂模型克隆后取消其逆X旋转 |
| E-DART-EF | 原Pos200/202.ef含W03FIR01.wav | 发射时播放该原音效引用；EF内部完整轨迹/事件语义仍未全部恢复 |
| E-DART-CPU | tests/native-projectiles.test.mjs实际加载原SKC/BNC/AMB、d_wpnR、W3_0、sn01真实地图/动态碰撞；WP67锁WP53连续三发 | 三次真实动作发射均命中且各扣34，目标1000→898、命中3、伤害102。原frame3517手挂点高度约2.3889，脚底0.415；原WP9直走W12桥上每发由桥mesh T遮挡，开阔地与桥上两种情况均回归覆盖 |

## Findings 与运行路径

- F-DART-BASIC（validated，high）：基础地面/空中飞镖已从动作显示扩展为实际飞行与命中；证据E-DART-POS/RES/GMC/CPU。
- F-DART-LIFECYCLE（validated，high）：命中一次后移除；防御消耗弹体且不扣HP；致死只结算一次；暂停冻结飞行和年龄，换图/退出/重开/结束清除；发射后换兵器不会改变发射时RES、pose和team快照。由13项投射测试覆盖。
- P-DART-CALLFLOW：原POS窗口 → `MeteorGame._launchNativeProjectiles` → 原d_wpnR世界位置/原W3_0模型 → `NativeProjectileSystem`连续扫掠 → 最近墙/角色裁决 → `_applyNativeHit` → 原RES/EXE伤害resolver → HP/怒气/死亡/原剧情host。

## 明确的 Web 宿主适配

飞行速度50 world/s、半径0.12、寿命3秒、重力0、自旋28rad/s、容量64，是已公开provenance的Web适配参数，**不是**已证实的EXE常量。瞄准使用锁定目标胸口或角色正前方，无追踪修正。角色接触体为竖直胶囊；运动角色使用相对运动连续扫掠；地图中心线与四个半径偏移线连续检测原三角，最近墙优先于后方角色，距离相同则墙优先。该地图半径近似不等于原COB/原弹体碰撞体恢复。

基础200/202之外，201八方手里剑与203/204怒招EF仍标记`projectileSpecialsPending`。机关PST的damage入参随后完成EXE闭环：004af570 → 005643f0 → 00560500把attacker的nativePoseAttack原样传入OnAttack，无目标防御、无队伍系数；默认createNativeSceneDamageResolver已接入。详见E-native-machine-damage.json。七星对机关为49，原石块500HP经过11次该参数的真实PST回调后HP=-39、关闭碰撞并激活原物品；此两项新测试属于native-script测试集。

## 复现

在项目根目录运行：

```sh
node --test tests/native-projectiles.test.mjs
npm run check
```

真实资源CPU夹具省略图像解码、声音输出与浏览器渲染；骨架、动画、手挂点、武器几何、地图、伤害和飞行代码使用实际运行模块。它证明运行时行为，不等同于浏览器手动通关。

原长官item16偃月/W7_1防御为0（RES valueOffset3126），故同一飞镖得到49 rawHP，区别于普通哨兵W7_0的34。root浏览器已观察到七星命中长官2000→1804，4次各49；这是实际射击验证，不等于完整手动通关。

# E-jump-follow：原版跳跃模型与 Web 碰撞体、镜头对齐

日期：2026-10-26（Asia/Shanghai）。范围：用户反馈“跳跃时镜头未跟随，人物跳出画面”。本次只读取原版资源，没有运行原 EXE。

## 原因与来源

`createNativeCharacter({inPlace:true})` 原先只清除 BANIM 主 bone 的 x/y，保留其 z（骨盆局部高度），却仍应用 `d_base` 的全部场景平移。BNC 中 bone `b` 的 parent 为 `d_base`，后者 parent 为 `NULL`，运行时直接位于 `nativeSpace` 下；因此 `d_base` 同时平移整个蒙皮和所有武器挂点。

原版 P0.POS 的普通跳跃使用 source 0：Pose 151 为 655–669（link 152），Pose 152 为 670–674（link 180）。原始 common/character.amb 取样：

| 帧 | d_base.z 原单位 | 世界高度（×0.08） | bone b 局部 z 原单位 |
| --- | ---: | ---: | ---: |
| 655 | 0.0035665 | 0.000285 | 17.1570 |
| 663 | 72.9794006 | 5.838352 | 19.6710 |
| 669 | 69.6597672 | 5.572781 | 19.9717 |
| 670 | 67.3471069 | 5.387769 | 19.7761 |
| 674 | 18.9963398 | 1.519707 | 19.9846 |

外部 Web 物理又让 fighter.root 执行 `vy=12, gravity=34` 的抛物线；镜头只根据这个外部 root 加 1.65m 取眼点，导致模型比碰撞体额外高约 6m。原镜头目标与位置的双层阻尼又使快速上升时的竖直跟随落后。这里的速度、重力、相机行为属于 Web 适配，未宣称与 EXE 完全一致。

20 份原版 BNC 全部具有唯一根级 `d_base`，且第一个 bone 的 parent 为 `d_base`。P0–P18 的 BNC base pivot 为 `[0,0,0]`；P19（律香川）是 `[0.308,-0.265,0]`，所以适配必须恢复各角色自己的 BNC 初值，不能全部硬编码归零。

## 回归方法与对照

测试文件：`tests/native-jump-camera.test.mjs`。读取真实 P0 的 SKC/BNC/个人 AMB/公共 AMB/POS/ACT，通过实际 `action('jump')`、`_updateFighter`、`_tickCamera` 逐帧运行。只有地面与相机遮挡墙使用可控三角形，目的是单独验证适配；不替换蒙皮、骨骼、动作帧或角色移动。每次 120 帧、60 FPS，计算实时蒙皮包围盒的屏幕投影。

旧版本对照：将当前模块与相同测试放入独立 `/private/tmp` 镜像，只用以下命令取得旧的两个模块，原工作区不回退：

```sh
git show b1ced130b8f01d6d601f384bc264ee76c0e24ea2:dist/engine.js
git show b1ced130b8f01d6d601f384bc264ee76c0e24ea2:dist/native-character.js
```

镜像在 `/private/tmp/meteor-jump-baseline-iph_scmw`，运行命令为 `node --test tests/native-jump-camera.test.mjs`，退出码 1：**10 项中 2 通过、8 失败**。原始输出保存在 `E-jump-follow-baseline-2026-10-26.tap`。其中 frame 656 的场景 dummy 已额外移动 2.019m；向前跳跃第 3 帧身体中心投影 y=1.043，已经超出屏幕（NDC 可见区为 -1 至 1）。独立相机高度断言同样在第一帧失败。

修复工作区使用相同命令，退出码 0：**10 项全部通过**。原始输出保存在 `E-jump-follow-fixed-2026-10-26.tap`。为了保存诊断数值，两个镜像均在测试末尾追加相同的只读指标输出；正式测试文件没有日志注入。

| 实际平地 L 跳跃指标 | 旧实现 | 修复后 |
| --- | ---: | ---: |
| 模型场景 base 相对碰撞 root 最大额外高度 | 5.901924m | 0m |
| 身体中心投影 y 最大值 | 2.133273（画面外） | -0.032444 |
| 身体中心投影 y 最小值 | -0.232254 | -0.117424 |
| 碰撞 root 最大高度 | 2.033333m | 2.033333m |
| 落地 root 高度 | 0.015m | 0.015m |

## 已覆盖的约束

- 就地模式中的 151、152、180 保留骨盆局部高度与原始骨骼层级，场景平移与碰撞 root 对齐。
- 平地 L、锁定敌人 L、向前移动 L：实际离地、原始姿态切换、身体投影留在画面、自然落地。
- 近墙跳跃保持镜头在原三角墙的玩家侧；没有用镜头穿墙来掩盖蒙皮偏移。
- 无锁定时，相机与取景目标的竖直高度相对碰撞 root 维持稳定，水平方向仍保留原有平滑。
- 飞镖 200/202 原始手部挂点相对骨盆的向量与完整原始轨迹一致，整树平移不会让武器离手。
- 普通攻击 259 的 `d_base.y=-91.012688` 原单位场景偏移在就地模式中被消除；`inPlace:false` 或帧级 `rootMotion:true` 仍完整保留原始场景轨迹，且可切回 `rootMotion:false`。
- 全 20 个原版人物的 BNC 层级与 P19 非零 pivot 已检查。

浏览器实机截图由主代理另行验证：`artifacts/jump-follow-fixed.png`、`artifacts/jump-lock-follow-fixed.png`。本文件的 CPU 测试不替代真实地图、设备或全游戏流程验收。

## 输入资源 SHA-256

- `p0/p0.skc`：`044e29b3adf0c3207bd4681e5ec62820cbb0e274676679e15b814abcdbf5e34b`
- `p0/p0.bnc`：`1364f804c2703b91d373854c496c69b538fb098f348748281fc984017e0d2978`
- `p0/p0.pos`：`1e71f945afc6b701f86eb50e500feccca22f20b52f7f3bec073b0247d390a5fb`
- `common/character.amb`：`87f8b4d81160c924408f9d12bc73aa51b184ea69c31953c1236d8de97c03578a`

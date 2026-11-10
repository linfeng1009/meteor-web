# E-combat-impact-integration：受击动作、击倒与命中反馈接通

日期：2026-10-30。沿用 [scope.md](../scope.md) 的本地离线授权；原 EXE 未执行或修改。本证据记录 Web 宿主如何消费已经确认的原数据，不把宿主参数混入原版逆向结论。

## 缺口与实际行为

修复前，`MeteorGame._applyNativeHit` 已扣 HP、累计命中并按原 EF 引用播放声音，却没有消费 `Attack.TargetPose`；目标的追击、攻击和每帧待机选择也没有受击锁。单独强制播放一次受击动作仍会被下一帧待机覆盖。原来源证明这条链确实存在，见 [E-hit-reaction-source](E-hit-reaction-source-2026-10-30.md)。

当前接入分为以下几层：

| 层 | 实现与证据 | 限制 |
| --- | --- | --- |
| 原受击姿态 | 未成功防御且非致死时，传入该攻击原 `TargetPose`，立即显示第一原动画帧，丢弃受击者排队攻击 | 暂用基础 TargetPose，未移植原方向矩阵选择 |
| 动作占用 | `NativeCombatController.reacting` 纳入 `busy`；受击时跳过玩家移动与 AI 追击 / 出手 / 转向，禁止普通攻击、跳跃和护架取消 | 完整原状态 7 / 9、输入闪避与翻滚尚未恢复 |
| 原倒地与起身 | 原95/96→113、97/98/99→112；到卧地帧后保持，112→119、113→120使用原起身动画；卧地 / 起身期间轻击不强拉为站立 | 落地后自动等0.65秒是 Web 政策，不是已找出的原常数 |
| 场景运动 | 继续显示原骨架局部动作，应用原采样水平根位移并检查宿主墙面碰撞；空中卧地等待脚点接地 | 脚点地面物理、原 TargetMove / TargetValue 的完整距离和时间语义尚未恢复 |
| 优先级 | 成功防御不播普通倒地；致死优先Pose117；重开清除反应与命中停顿 | 不把击倒计作击杀，不新增额外伤害倍率 |
| 命中反馈 | 原BL/GD→WAV链继续使用；接触点火花、局部22/32/50毫秒停顿与微小镜头偏移 | 火花几何、时长与幅度明确是 Web 表现适配，非原EF渲染器 |

另一实际缺口是快速连续按 J：允许排队后，旧选择策略可能在当前招首个原攻击窗之前就切到下一招，前两下只见挥刀而没有接触。保留同一套原攻击窗口和 ACT 合法边，在 Web 控制器默认启用 `preserveQueuedStrikes`，普通下一式排队须至少保留当前首个攻击窗。隔离重放每100毫秒按一次公开attack时，旧策略只有264一击，新策略保留262 / 263 / 264三击；原损伤配置下为24 / 46 / 57，未改伤害公式。重放记录在 [E-hit-queue-replay](E-hit-queue-replay-2026-10-30.json)。这是明确的 Web 排队修复，原 `NextPose.Time` 的完整含义仍未证实。

## 验证与可复现命令

在项目根目录执行：

```sh
node --test tests/native-hit-reaction.test.mjs tests/native-environment.test.mjs
node --test tests/native-impact-feedback.test.mjs
node work/meteor-original/evidence/hit-reaction-source-audit-2026-10-30.mjs
```

较早第一组 **17/17**：受击8项、环境9项，原始输出为 [hit-reaction-environment TAP](hit-reaction-environment-2026-10-30.tap)。最终受击模块扩展为10项，补充真正接入反馈后的局部停顿、无关角色继续运行、空挥无反馈及死亡立即打断旧停顿，并进入最终全套。受击测试使用真实 POS / RES / SKC / BNC / AMB 和原武器模型，普通公开attack输入完成三式接触，目标按98→112→119倒地起身；测试还检查实际头骨卧地高度与起身高度变化，避免只验证一个数字ID。NPC反击、音频、GPU和复杂地图被隔离，测试地面为规则平面。环境组覆盖原hell触发接入的实际_move死亡、死亡姿态不被同帧覆盖、单次失败和重开等回归，不将它计作新的战斗击倒结论。

第二组 **4/4**：接触点、护架 / 普通 / 倒地反馈差异、停顿和微震上限、失效与GPU清理、无效坐标防NaN。独立模块证据见 [E-impact-feedback](E-impact-feedback-2026-10-30.json)。最终全套 **207/207**，0失败 / 跳过 / 取消，30.570101208秒；[最终TAP](native-runtime-hit-reaction-final-2026-10-30.tap)保留原输出。语法检查19个运行模块通过，原资产3858条覆盖核验零问题，diff空白检查通过。完整哈希与状态由 [E-validation-current](E-validation-current.json) 记录；首轮全套的203/205、两项失败不作为通过结果。

浏览器先通过正常 Q / W / J 按键实际接近并命中敌人，命中计数2，目标HP从1000变为952，截图为[初次实际命中](../../../artifacts/hit-reaction-live-2026-10-30.png)。随后在四方阵、原孟星魂 / 剑、正常活AI条件下，通过Q锁定、W接近、每100毫秒连续J，确认第三击“击倒·57”、目标HP825；用普通暂停菜单保存观察，恢复后普通K守架经过约650毫秒仍显示“倒地”，再过约750毫秒目标恢复站立追击。截图分别为[第三击](../../../artifacts/hit-reaction-desktop-2026-10-30.png)、[卧地](../../../artifacts/hit-knockdown-desktop-2026-10-30.png)、[起身](../../../artifacts/hit-getup-desktop-2026-10-30.png)，操作与哈希由 [浏览器证据](E-hit-reaction-browser-2026-10-30.json)记录。没有调试接口改HP、位置或单独冻结NPC；总命中计数9包含其他敌人，不解释成同一目标9击。该session错误 / 警告日志为空，限于本次操作覆盖；不称完整活AI通关或逐帧视听还原。

## Evidence → Finding → Path

| E-id | source_ref | repro_command | content_hash |
| --- | --- | --- | --- |
| E-H01 | [原反应状态与23份源导出哈希](E-hit-reaction-source-2026-10-30.json) | `node work/meteor-original/evidence/hit-reaction-source-audit-2026-10-30.mjs` | JSON逐源artifact SHA-256 |
| E-H02 | [真实资产受击 / 环境17项TAP](hit-reaction-environment-2026-10-30.tap) | 上述第一组命令 | `47df6d301dd4a02771206f9176549d1af43cff35d52dfbf3d2e8d4c58d500855` |
| E-H03 | [快速J新旧重放](E-hit-queue-replay-2026-10-30.json) | `node work/hit-queue-adapter-probe.mjs` | `91675622ee8f6a5dc41f9e40d07f84c7a2a3e3981d1217eafb89eb5fad6fd1cd` |
| E-H04 | [独立反馈模块证据](E-impact-feedback-2026-10-30.json) | 上述第二组命令 | `3e3fc62f1f54e2204fef1653ac1204fd2c7d4c8c3c18f032408c450415732960` |
| E-H05 | [浏览器普通按键实际命中截图](../../../artifacts/hit-reaction-live-2026-10-30.png) | `npm run dev` 后Q锁定、W接近、J攻击 | `2f75b055cda5972e861db33539ae198b650d96b0d453bd00a150bc5d1181bfe9` |
| E-H06 | [最终207项TAP](native-runtime-hit-reaction-final-2026-10-30.tap)及[浏览器击倒起身证据](E-hit-reaction-browser-2026-10-30.json) | `npm test`；正常Q / W / 连续J / K | 见最终验证快照及浏览器逐图SHA-256 |

| F-id | severity | evidence_ids | confidence | location | status |
| --- | --- | --- | --- | --- | --- |
| F-H01 | n/a_re | E-H01, E-H02 | high | `engine._applyNativeHit`、`NativeCombatController.react/update` | 原TargetPose与倒地 / 起身资源链已接通；精确物理和卧地时长仍属边界 |
| F-H02 | n/a_re | E-H02, E-H03 | high | `NativeCombatController._queuedStrikeEnd` | 快速普通输入保留三击；Web队列政策，不冒称原Time语义 |
| F-H03 | n/a_re | E-H04, E-H05, E-H06 | high | `native-impact-feedback.js`、原EF / WAV、浏览器 | 接触表现接入且有上限；普通输入下已实际击倒起身，完整实战通关未验收 |

P-H01，`path_type=callflow`：公开J输入 → 原POS攻击窗与真实武器 / 骨骼接触 → 原RES / EXE伤害 → 防御 / 致死优先级 → 原TargetPose受击锁 → 原POS倒地link → Web脚点落地与0.65秒等待 → 已确认的原起身Pose → 恢复操作。原声音与Web短促表现从接触处分支，任务时钟和无关角色不作全局暂停。

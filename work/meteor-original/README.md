# Case meteor-original

本地原客户端的离线静态分析、资源解析与Web移植记录。[授权范围](scope.md)为granted，原样本只读，未执行原EXE。

2026-10-26 当前本地进度：真实资源、已恢复数值分支、PST 解释器、第一关宿主、七星基础投射、原机关伤害默认接入与肉包拾取已完成本阶段集成。最终全套 **83/83 测试通过**（26.87 秒），11 个运行模块语法检查、diff 空白检查通过；原始全套输出已存档。10 项跳跃回归覆盖原 d_base / 蒙皮 / 碰撞体对齐和镜头跟随，9 项肉包测试覆盖原 RES +300、引擎输入门、遮挡及真实首关掉落→拾取→重置。真实地图几何另验收了石块受击到破碎、关闭碰撞和激活掉落的完整源脚本链。

13 项投射与 7 项首关 CPU 验收继续通过，包含原 WP 步行、自然死亡与重开，以及冻结反击的三 NPC 胜利链。**完整活 AI 实战通关仍未证明**；原输入 / 物理 / AI 完整行为、进阶投射与 EF、其他剧情、完整物品和场景交互、联网继续保留 open 工单。肉包当前仅支持 sn01 单机，演武不支持；显式拾取、范围、满血保留与无计时重生属于公开 Web 适配。

先前 38 项对应的私有发布记录与 58/58 本地验证均保留为历史快照，不能证明本次版本已上线。本次外部上传曾被自动审批拒绝，仍缺明确用户授权，因此未更新部署；线上此前只验证到私有登录门。

- [工作项与未完成范围](workitems.md)
- [阶段时间线与职责](timeline.md)
- [数值与资源报告](report/2026-10-23_逆向-MeteorEXE战斗数值-report.md)
- [第一关宿主报告及Mermaid](report/2026-10-23_逆向-钟乳洞PST宿主-report.md)
- [当前测试与验收快照](evidence/E-validation-current.json)
- [原七星基础投射证据](evidence/E-native-projectiles.md)
- [原机关攻击伤害入参证据](evidence/E-native-machine-damage.json)
- [跳跃与镜头跟随回归](evidence/E-jump-follow-2026-10-26.md)
- [肉包拾取与原资源链](evidence/E-native-items-2026-10-26.md)
- [真实机关几何破坏到掉落](evidence/scene-machine-audit-2026-10-26.json)
- [83 项最终全套 TAP](evidence/native-runtime-current.tap)
- [首关CPU验收及完整通关边界](evidence/E-mission-cpu-acceptance.md)
- [匿名field journal](field-journal/2026-10-23_native-game-port.md)
- [私有部署与验证边界](evidence/E-web-deployment.json)

新增证据继续保存到evidence，原始事实、实现适配和推断分开登记。相关细节不写外部技能目录或记忆。

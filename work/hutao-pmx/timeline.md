# Timeline (append-only)

## 2026-10-28T20:06:57+08:00 | lead | init
- action: case-init
- command_or_ref: skills/scripts/case-init.sh
- result_summary: case directory created; scope ready_for_act=true
- artifacts: [scope.md, workitems.md]
- evidence_ids: []
- decision_delta: [case_initialized]
- carry_forward_refs: [scope.md]
- next: open PRIMARY SKILL.md and ACT within scope

## 2026-10-28 | lead | complete-local
- action: PMX静态解析、Blender重绑、原动作适配、工坊与游戏接入
- result_summary: 完整胡桃可用；125测试及14模块语法通过；实际浏览器进入四方阵演武
- artifacts: [report/2026-10-28_模型转换-胡桃喵-report.md, evidence/validation.json, ../hutao-pmx-quality/审查记录.md]
- decision_delta: [采用整份PMX替换缺脸GIMI, 修复Blender零长骨方向, 连续躯干与衣根权重, 保留局部短裤变形限制]
- carry_forward_refs: [scope.md, ../hutao-import/scope.md, ../hutao-pmx-model/README.md]
- next: 本地交付；后续可精修短裤蒙皮及发尾衣摆物理

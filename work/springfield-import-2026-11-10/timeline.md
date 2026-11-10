# Timeline (append-only)

## 2026-11-10T12:07:11+08:00 | lead | init
- action: case-init
- command_or_ref: skills/scripts/case-init.sh
- result_summary: case directory created; scope ready_for_act=true
- artifacts: [scope.md, workitems.md]
- evidence_ids: []
- decision_delta: [case_initialized]
- carry_forward_refs: [scope.md]
- next: open PRIMARY SKILL.md and ACT within scope

## 2026-11-10T13:05:34+08:00 | lead | local import and source-quality correction
- action: 完整归档与初版导入后，按用户反馈修正压缩身材和材质通道。
- command_or_ref: README.md中的Blender重建、独立PMX核对、45采样、413测试、语法和打包。
- result_summary: 原网格等比保留；30显示骨骼+71发骨；原战斗骨架不变；Unity RG/AG法线与RMO红通道；新增原姿态工坊。
- artifacts: [source-copy.json, build-evidence.json, blend-validation.json, quality-full-tests.tap, quality-motion-summary.json, browser-validation.json, validation.json]
- evidence_ids: [E-001, E-002, E-003, E-004, E-005]
- decision_delta: [独立显示骨架替代初版分段网格压缩, 原贴图字节保留并修正读取, 仅本机适配]
- carry_forward_refs: [report/2026-11-10_模型适配-春田原比例与材质-report.md, field-journal/2026-11-10_source-proportions-and-packed-normals.md]
- next: 本轮完成；完整MMD着色、布料和表情为后续范围。

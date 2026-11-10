# Timeline (append-only)

## 2026-11-10T17:58:12+08:00 | lead | init
- action: case-init
- command_or_ref: skills/scripts/case-init.sh
- result_summary: case directory created; scope ready_for_act=true
- artifacts: [scope.md, workitems.md]
- evidence_ids: []
- decision_delta: [case_initialized]
- carry_forward_refs: [scope.md]
- next: open PRIMARY SKILL.md and ACT within scope

## 2026-11-10 | lead | PMX import completed
- action: 源PMX与纹理依赖审查、完整哈希归档、原比例显示骨架、原动作/显示武器及48发骨适配。
- command_or_ref: README.md中的Blender构建/重开、8专项、45采样、全回归和打包。
- result_summary: 全源25,219顶点、29,140面、25材质、5原2K图保留；8专项与46模块语法通过；首轮494/496，2项EPERM端口限制在两文件18项复验中均通过。
- artifacts: [source-copy.json, source-audit.json, build-evidence.json, blend-validation.json, motion-summary.json, browser-validation.json, validation.json]
- evidence_ids: [E-001, E-002, E-003, E-004, E-005]
- decision_delta: [PMX数据格式路由R0, 网格仅统一等比变换, 原低Alpha发光泽层保持透明pass, 本机端口限制采用定向复验]
- carry_forward_refs: [scope.md, report/2026-11-10_模型适配-八重神子-report.md, field-journal/2026-11-10_pmx_transparent_hair_highlights.md]
- limits: 后台浏览器未能锁定鼠标，实际演武的鼠标攻击/跳跃未计手动通过；工坊与CPU已覆盖动作几何；衣物和完整源着色仍简化。
- next: 本轮本地导入完成。

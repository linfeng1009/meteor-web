# Timeline (append-only)

## 2026-11-10T11:22:10+08:00 | lead | init
- action: case-init
- command_or_ref: skills/scripts/case-init.sh
- result_summary: case directory created; scope ready_for_act=true
- artifacts: [scope.md, workitems.md]
- evidence_ids: []
- decision_delta: [case_initialized]
- carry_forward_refs: [scope.md]
- next: open PRIMARY SKILL.md and ACT within scope

## 2026-11-10T12:05:44+08:00 | lead | source_archive_and_audit
- action: Copy all9 original files into the project-owned assets/source/doubao archive and verify byte lengths/SHA-256.
- artifacts: [source-copy.json, source-audit.json, 作者与使用说明.txt, blender-source-audit.json]
- evidence_ids: [E-001]
- decision_delta: Use archived PMX joints/weights and the original4K JPEG, retaining full geometry; no dependency on the original download directory.
- carry_forward_refs: [scope.md, route/route-scope.md]

## 2026-11-10T12:05:44+08:00 | lead | retarget_and_binding_repairs
- action: Retarget body to original30 BNC bones and9 restrained hair bones, bake4 native AMB sample actions, retain all180698 source triangles.
- result_summary: Original root/leg and torso/arm binding jumps caused skirt/armpit stretching. Welded seam influences, a dark-fabric mask and body displacement/weight smoothing reduced sampled worst edge growth from0.6405 to0.1307, with the complete head locked.
- artifacts: [build-evidence.json, motion-probe.json, 豆包-完整人物-流星动作适配.blend]
- evidence_ids: [E-002, E-003]
- decision_delta: Fix actual source weight transitions before accepting finite bounds alone as motion quality.
- carry_forward_refs: [E-001]

## 2026-11-10T12:05:44+08:00 | lead | independent_dependencies_and_validation
- action: Reopen the finished Blender file, verify embedded original JPEG, no linked libraries and4 editable actions; run full test suite and package all runtime files.
- result_summary:396/396 full tests and7 targeted tests passed;33 runtime modules syntax checked;45 motion samples finite with unchanged native joints. ZIP verifies4100 files and contains the Doubao mesh/JPEG, with no original PMX requirement.
- artifacts: [blend-validation.json, full-tests.tap, doubao-tests.tap, package.log, validation.json]
- evidence_ids: [E-002, E-003, E-004]
- decision_delta: Blender images decode lazily after reopening; force a pixel read before checking has_data. Archive and rebuilt runtime are self-contained; leave original Downloads untouched for user cleanup.
- carry_forward_refs: [scope.md, E-001]

## 2026-11-10T12:05:44+08:00 | lead | browser_handoff
- action: Validate workshop body/face/run/jump, choose Doubao, enter the actual arena, jump and execute an air attack; return to home and preserve game/workshop tabs.
- result_summary: Correct character selected and drawn; no consoleerror/warning. Native story identity remains Meng Xinghun while cosmetic identity is Doubao.
- artifacts: [workshop-preview.png, face-preview.png, character-selection.png, game-preview.png]
- evidence_ids: [E-005]
- decision_delta: All requested import/retarget/dependency work complete; no uploads or source deletions performed.
- carry_forward_refs: [E-004, validation.json]

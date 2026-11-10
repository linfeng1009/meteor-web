# Timeline (append-only)

## 2026-11-10T10:33:18+08:00 | lead | init
- action: case-init
- command_or_ref: skills/scripts/case-init.sh
- result_summary: case directory created; scope ready_for_act=true
- artifacts: [scope.md, workitems.md]
- evidence_ids: []
- decision_delta: [case_initialized]
- carry_forward_refs: [scope.md]
- next: open PRIMARY SKILL.md and ACT within scope

## 2026-11-10T11:17:35+08:00 | lead | reconstruction_and_validation
- action: Recover source hair chains, reconstruct hair-only weights and run cosmetic Web springs.
- artifacts: [*-asset.json, baseline/, hashes.json, scripts/blender/add_hair_springs.py]
- evidence_ids: [E-001, E-002]
- decision_delta: Original Downloads absent; archived positions/hierarchy suffice, original PMX vertex weights and MMD rigid bodies are not restored.
- carry_forward_refs: [scope.md]

## 2026-11-10T11:17:35+08:00 | lead | restrained_motion
- action: Respond to excessive hair sway with 98% driver transport, strong damping and a 0.04-radian whole-strand cone; refit collision clearances and cap collision correction.
- result_summary: Three model probes reduced peak mesh offsets about 66% from intermediate tuning; 8 hair tests passed. Browser run/jump/attack, toggles and switching checked; no console error/warning.
- artifacts: [restrained-motion.json, hair-tests.tap, restrained-hair-preview.png]
- evidence_ids: [E-002, E-003, E-005]
- decision_delta: Per-link angular constraints alone accumulate across long chains; constrain direction relative to the animated head as well.
- carry_forward_refs: [E-001]

## 2026-11-10T11:17:35+08:00 | lead | regression_and_handoff
- action: Run full suite serially under a 512MB heap cap, then recheck only affected test files.
- result_summary: First pass 387 successful, one outdated rigid-hair assertion, one 45s file timeout; head-descendant constraint update and 180s mission-file limit yielded 3/3 and 10/10 passes. All389 cases have passing coverage; 33 runtime modules syntax checked.
- artifacts: [full-tests.tap, raiden-recheck.tap, mission-recheck.tap, validation.json, README.md, 2026-11-10_模型适配-头发物理-report.md]
- evidence_ids: [E-004]
- decision_delta: Keep first-pass failures and rerun provenance; do not repeat already successful unrelated tests.
- carry_forward_refs: [E-002, E-003, E-005]

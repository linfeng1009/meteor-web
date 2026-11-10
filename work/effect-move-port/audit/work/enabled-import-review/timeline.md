# Timeline (append-only)

## 2026-11-08T16:23:25+08:00 | lead | init
- action: case-init
- command_or_ref: skills/scripts/case-init.sh
- result_summary: case directory created; scope ready_for_act=true
- artifacts: [scope.md, workitems.md]
- evidence_ids: []
- decision_delta: [case_initialized]
- carry_forward_refs: [scope.md]
- next: open PRIMARY SKILL.md and ACT within scope

## 2026-11-08 | audit | default import review
- action: isolated-root-default-import
- command_or_ref: python3 work/effect-move-port/audit/verify-default-import.py
- result_summary: Default output equals installed manifest plus45PNG;259 links349; no pending darts imported.
- evidence_ids: [E-IMPORT]
- decision_delta: [default_import_reproduced]
- carry_forward_refs: [scope.md]
- next: parent handoff

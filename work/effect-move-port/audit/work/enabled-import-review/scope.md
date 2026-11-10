# Case Scope

## meta
- case_id: enabled-import-review
- created: 2026-11-08T16:23:25+08:00
- operator: local
- project_root: /Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web/work/effect-move-port/audit
- primary_skill: case-review/SKILL.md
- primary_id: R40
- lead_role: lead
- specialist_roles: []
- hint: case-review evidence artifact hashes scope traceability 导入产物只读审查
- preset: offline-sample

## auth
- status: granted
- basis: own_system
- evidence_of_auth: Parent read-only local import audit; existing meteor-original scope granted; no dist writes
- MUST NOT proceed if status != granted

## in_scope
- assets:
  - /Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web/dist/assets/original/rage-vfx/manifest.json
- surfaces: []
- activities: []

## out_of_scope
- assets: []
- activities: [dos, phishing_real_users, unrestricted_exfil]

## network_profile
- mode: offline
- notes: |
    offline | lab_only | authorized_target_only | unrestricted_lab
    Change mode only after auth.status = granted.
    Presets: offline-sample | ctf-public | own-system

## deliverables
- report: true
- field_journal: true
- diagrams: true
- timeline: true

## constraints
- timebox: {}
- stealth: low
- data_handling: anonymize

## signoff
- ready_for_act: true
- checklist:
  - [x] auth.status = granted
  - [x] in_scope.assets non-empty OR offline sample path set
  - [x] network_profile.mode chosen
  - [ ] out_of_scope reviewed
  - [ ] roles assigned (see skills/ops/role-map.md)

## ops_refs
- skills/ops/scope-contract.md
- skills/ops/evidence-finding-path.md
- skills/ops/role-map.md
- skills/ops/timeline-workitem.md
- skills/ops/IDENTITY.md

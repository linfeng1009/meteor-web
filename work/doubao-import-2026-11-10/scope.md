# Case Scope

## meta
- case_id: doubao-import-2026-11-10
- created: 2026-11-10T11:22:10+08:00
- operator: local
- project_root: /Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web
- primary_skill: reverse-engineering/SKILL.md
- primary_id: R0
- lead_role: lead
- specialist_roles: []
- hint: Offline PMX model audit and native action retarget for Doubao
- preset: offline-sample

## auth
- status: granted
- basis: own_system
- evidence_of_auth: User requests copying and importing their local Doubao model, including native actions and self-contained project assets.
- MUST NOT proceed if status != granted

## in_scope
- assets:
  - /Users/dulinfeng/Downloads/豆包角色绑定/豆包模型.pmx
  - /Users/dulinfeng/Downloads/豆包角色绑定
  - /Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web
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

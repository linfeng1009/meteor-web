# Case Scope

## meta
- case_id: springfield-import-2026-11-10
- created: 2026-11-10T12:07:11+08:00
- operator: local
- project_root: /Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web
- primary_skill: reverse-engineering/SKILL.md
- primary_id: R0
- lead_role: lead
- specialist_roles: []
- hint: Offline PMX Springfield swimsuit model import and native action retarget
- preset: offline-sample

## auth
- status: granted
- basis: own_system
- evidence_of_auth: User requests importing their local model into the existing game; previous instructions require project-owned resources and native action adaptation.
- MUST NOT proceed if status != granted

## in_scope
- assets:
  - /Users/dulinfeng/Downloads/春田_泳衣_全P3_刘海物理优化/春田_泳衣_全P3_刘海物理优化.pmx
  - /Users/dulinfeng/Downloads/春田_泳衣_全P3_刘海物理优化
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

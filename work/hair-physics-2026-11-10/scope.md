# Case Scope

## meta
- case_id: hair-physics-2026-11-10
- created: 2026-11-10T10:33:18+08:00
- operator: local
- project_root: /Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web
- primary_skill: reverse-engineering/SKILL.md
- primary_id: R0
- lead_role: lead
- specialist_roles: []
- hint: local model rig reconstruction from recovered skeleton metadata for Web spring physics
- preset: offline-sample

## auth
- status: granted
- basis: own_system
- evidence_of_auth: 用户要求改善已导入模型的头发僵硬；本地重建发束骨链、浏览器弹簧惯性与基础碰撞，仅修改本项目，原模型和原战斗骨架保留，不上传
- MUST NOT proceed if status != granted

## in_scope
- assets:
  - /Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web/dist/assets/enhanced/emilia/mesh.json
  - /Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web/dist/assets/enhanced
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

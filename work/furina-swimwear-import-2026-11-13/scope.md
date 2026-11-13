# Case Scope

## meta
- case_id: furina-swimwear-import-2026-11-13
- created: 2026-11-13T16:59:02+08:00
- operator: local
- project_root: /Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web
- primary_skill: reverse-engineering/SKILL.md
- primary_id: R0
- lead_role: lead
- specialist_roles: []
- hint: 通用逆向 本地 GIMI 模型自定义文件格式分析 资源提取 本地离线样本
- preset: offline-sample

## auth
- status: granted
- basis: own_system
- evidence_of_auth: User supplied the local GIMI model and requested integrating it as a second Furina appearance in their local Web game.
- MUST NOT proceed if status != granted

## in_scope
- assets:
  - /Users/dulinfeng/Downloads/人物模型/芙宁娜泳装/FurinaDarkPosition.buf
  - /Users/dulinfeng/Downloads/人物模型/芙宁娜泳装
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

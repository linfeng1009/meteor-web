# Case Scope

## meta
- case_id: furina-import-2026-11-10
- created: 2026-11-10T18:03:01+08:00
- operator: local
- project_root: /Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web
- primary_skill: reverse-engineering/SKILL.md
- primary_id: R0
- lead_role: lead
- specialist_roles: []
- hint: 通用逆向 PMX模型自定义文件格式分析 资源提取 本地离线样本
- preset: offline-sample

## auth
- status: granted
- basis: own_system
- evidence_of_auth: User requested importing the local Furina model folder into their local Web game; authorized project-local conversion, animation and rendering verification of both included model variants.
- MUST NOT proceed if status != granted

## in_scope
- assets:
  - /Users/dulinfeng/Downloads/人物模型/芙宁娜_by_原神_dd7a8a03e7a7dfa6593053d639fa3025/【芙宁娜_荒】.pmx
  - /Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web
  - /Users/dulinfeng/Downloads/人物模型/芙宁娜_by_原神_dd7a8a03e7a7dfa6593053d639fa3025
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

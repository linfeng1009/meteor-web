# Case Scope

## meta
- case_id: raiden-pmx
- created: 2026-10-28T20:31:55+08:00
- operator: local
- project_root: /Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web
- primary_skill: reverse-engineering/SKILL.md
- primary_id: R0
- lead_role: lead
- specialist_roles: []
- hint: local PMX binary static parse Blender retarget web game
- preset: offline-sample

## auth
- status: granted
- basis: own_system
- evidence_of_auth: 用户提供YS-影本地PMX目录并明确要求增加到本人Web游戏；离线读取、Blender适配与本地验证，原文件只读，不上传
- MUST NOT proceed if status != granted

## in_scope
- assets:
  - /Users/dulinfeng/Downloads/礼服影_by_花咲十七夜_4563f538fa1cd21a941a22201f942acc/礼服影/礼服影.pmx
  - /Users/dulinfeng/Downloads/礼服影_by_花咲十七夜_4563f538fa1cd21a941a22201f942acc
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

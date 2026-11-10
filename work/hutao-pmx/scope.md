# Case Scope

## meta
- case_id: hutao-pmx
- created: 2026-10-28T20:06:57+08:00
- operator: local
- project_root: /Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web
- primary_skill: reverse-engineering/SKILL.md
- primary_id: R0
- lead_role: lead
- specialist_roles: []
- hint: local PMX binary static parse Blender skeletal retarget web game
- preset: offline-sample

## auth
- status: granted
- basis: own_system
- evidence_of_auth: 用户提供本地完整胡桃PMX模型用于接入本人Web游戏；仅静态转换及本地预览，不改源文件、不上传
- MUST NOT proceed if status != granted

## in_scope
- assets:
  - /Users/dulinfeng/Downloads/胡桃喵_by_摸鱼大水怪_0a83a5cf9e74a157fa2c751ce7b84384/胡桃喵1.0.pmx
  - /Users/dulinfeng/Downloads/胡桃喵_by_摸鱼大水怪_0a83a5cf9e74a157fa2c751ce7b84384
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

# Case Scope

## meta
- case_id: rage-vfx
- created: 2026-11-06T20:40:53+08:00
- operator: local
- project_root: .
- primary_skill: reverse-engineering/SKILL.md
- primary_id: R0
- lead_role: lead
- specialist_roles: []
- hint: local game asset format reverse engineering PonEF particle data
- preset: offline-sample

## auth
- status: granted
- basis: own_system
- evidence_of_auth: preset:offline-sample (owner-operated local file)
- MUST NOT proceed if status != granted

## in_scope
- assets:
  - /Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web/dist/assets/original/sounds/definitions/pos571.ef
  - /Users/dulinfeng/Downloads/流星86726/lxhdj_/SFX
  - 本项目 dist/assets/original/sounds/definitions/
  - 用户原客户端 ETexture.pak / TexturePatch.pak
  - 本项目原版 weapon-models DES 与 POS/ACT 数据
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

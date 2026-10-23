# Case Scope

## meta
- case_id: meteor-original
- created: 2026-10-22T16:55:08+08:00
- operator: local
- project_root: /Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web
- primary_skill: ida-reverse/SKILL.md
- primary_id: R6
- lead_role: lead
- specialist_roles: [binary-analysis, character-formats, combat-rules, resource-import]
- hint: native Windows PE Meteor.exe 反编译 游戏引擎 资源格式 web移植
- preset: offline-sample

## auth
- status: granted
- basis: own_system
- evidence_of_auth: 用户明确要求对其下载的本地流星蝴蝶剑客户端反编译并移植Web，优先复用原版资源。
- MUST NOT proceed if status != granted

## in_scope
- assets:
  - /Users/dulinfeng/Downloads/流星86726/lxhdj_/Meteor.exe
  - /Users/dulinfeng/Downloads/流星86726/lxhdj_
- surfaces: [binary, local-assets]
- activities: [static_reverse, resource_parse, web_port, validation]

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
  - [x] out_of_scope reviewed
  - [x] roles assigned (root: binary; resource_research: characters; game_engine: combat; quality_review: importer)

## ops_refs
- skills/ops/scope-contract.md
- skills/ops/evidence-finding-path.md
- skills/ops/role-map.md
- skills/ops/timeline-workitem.md
- skills/ops/IDENTITY.md

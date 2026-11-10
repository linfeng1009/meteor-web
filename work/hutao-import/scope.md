# Case Scope

## meta
- case_id: hutao-import
- created: 2026-10-27T12:10:36+08:00
- operator: local
- project_root: /Users/dulinfeng/Desktop/linf_Ai_projects/陨星/meteor-web
- primary_skill: reverse-engineering/SKILL.md
- primary_id: R0
- lead_role: lead
- specialist_roles: []
- hint: GIMI local model buffer Blender web port
- preset: offline-sample

## auth
- status: granted
- basis: own_system
- evidence_of_auth: 用户提供本地胡桃MOD目录并要求引入其Web游戏；本地静态解析、资源转换、Blender重绑与验证。公开官方GIMI文档及缺失静态数据仅用于格式核实与依赖补齐，不执行下载代码，不上传项目。
- MUST NOT proceed if status != granted

## in_scope
- assets:
  - /Users/dulinfeng/Downloads/hutao_black_stockings_mod_4k/HuTaoMod4K/HuTao.ini
  - /Users/dulinfeng/Downloads/hutao_black_stockings_mod_4k
  - https://github.com/SilentNightSound/GI-Model-Importer
  - https://github.com/SilentNightSound/GI-Model-Importer-Assets
  - https://raw.githubusercontent.com/SilentNightSound/GI-Model-Importer-Assets/
- surfaces: []
- activities: []

## out_of_scope
- assets: []
- activities: [dos, phishing_real_users, unrestricted_exfil]

## network_profile
- mode: authorized_target_only
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

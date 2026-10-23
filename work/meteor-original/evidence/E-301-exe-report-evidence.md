# 原客户端 EXE 数值与资源覆盖证据

### E-306
- title: 完整源客户端文件清单
- observed_at: 2026-10-23T13:58:33.538949+08:00
- source_type: file
- source_ref: evidence/resource-inventory.json
- content_hash: 9ed0975a4f40b0de39d3aa50ad492c995e0a66cc9632c4d1f3a1ebd1e20443ac
- artifact_path: evidence/resource-inventory.json
- repro_command: `python3 -c "import json;d=json.load(open('work/meteor-original/evidence/resource-inventory.json'));print(d['stats'])"`（在 meteor-web/ 下运行；需保留原离线样本）
- raw_excerpt: 完整源客户端文件清单；详见结构化原件。
- linked_workitem: n/a（本次分项收尾，主case工作项由lead维护）
- supersedes: none

### E-301
- title: PE身份与导入表
- observed_at: 2026-10-23T13:58:33.538949+08:00
- source_type: file
- source_ref: evidence/E-imports.json
- content_hash: b20e79118ee2432a31bb018c2f937fa13e6dfd118740523b74e8b824d3894c5f
- artifact_path: evidence/E-imports.json
- repro_command: `python3 -c "import json;d=json.load(open('work/meteor-original/evidence/E-imports.json'));print(d['sha256'],d['machine'],d['entryPoint'])"`（在 meteor-web/ 下运行；需保留原离线样本）
- raw_excerpt: PE身份与导入表；详见结构化原件。
- linked_workitem: n/a（本次分项收尾，主case工作项由lead维护）
- supersedes: none

### E-302
- title: 原EXE属性及命中函数
- observed_at: 2026-10-23T13:58:33.538949+08:00
- source_type: file
- source_ref: evidence/E-exe-decompilation-index.json
- content_hash: fff82aabfb9ab5c4f81f10379964b8548ac41e6ffe68fd920db6d19015e41895
- artifact_path: evidence/E-exe-decompilation-index.json
- repro_command: `python3 -c "import json;d=json.load(open('work/meteor-original/evidence/E-exe-decompilation-index.json'));print([(x['va'],x['sha256']) for x in d['functions']])"`（在 meteor-web/ 下运行；需保留原离线样本）
- raw_excerpt: 原EXE属性及命中函数；详见结构化原件。
- linked_workitem: n/a（本次分项收尾，主case工作项由lead维护）
- supersedes: none

### E-303
- title: RES与x86公式交叉核验
- observed_at: 2026-10-23T13:58:33.538949+08:00
- source_type: file
- source_ref: evidence/E-exe-combat-formulas.json
- content_hash: ed62a44fbea278976a36138e492505c0f1b3468afae57c70a52b5347ec2e851a
- artifact_path: evidence/E-exe-combat-formulas.json
- repro_command: `python3 scripts/analysis/document-combat-formulas.py`（在 meteor-web/ 下运行；需保留原离线样本）
- raw_excerpt: RES与x86公式交叉核验；详见结构化原件。
- linked_workitem: n/a（本次分项收尾，主case工作项由lead维护）
- supersedes: none

### E-304
- title: 当前JS与9组原公式样例核对
- observed_at: 2026-10-23T13:58:33.538949+08:00
- source_type: file
- source_ref: evidence/E-formula-runtime-verification.json
- content_hash: 56af305c23a19a2c8365bb386c816b80a27d6401af7bc143ba8a093060c5022e
- artifact_path: evidence/E-formula-runtime-verification.json
- repro_command: `node scripts/analysis/verify-exe-formulas.mjs`（在 meteor-web/ 下运行；需保留原离线样本）
- raw_excerpt: 当前JS与9组原公式样例核对；详见结构化原件。
- linked_workitem: n/a（本次分项收尾，主case工作项由lead维护）
- supersedes: none

### E-305
- title: 当前四份资源清单文件校验
- observed_at: 2026-10-23T13:58:33.538949+08:00
- source_type: file
- source_ref: evidence/E-asset-coverage-current.json
- content_hash: a8b7c49f45398a5453d5e844e07aff891d0bcb68ed3fa6546f7a8c6a0e04dea9
- artifact_path: evidence/E-asset-coverage-current.json
- repro_command: `python3 scripts/analysis/verify-recovered-assets.py`（在 meteor-web/ 下运行；需保留原离线样本）
- raw_excerpt: 当前四份资源清单文件校验；详见结构化原件。
- linked_workitem: n/a（本次分项收尾，主case工作项由lead维护）
- supersedes: none


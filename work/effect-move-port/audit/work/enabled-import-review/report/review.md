# 默认启用目录审查

### F-IMPORT 默认导入可重现
- severity: n/a_re
- evidence_ids: [E-IMPORT]
- confidence: high
- location: scripts/import-rage-vfx.py; dist/assets/original/rage-vfx/manifest.json
- status: validated

原脚本的默认运行在隔离ROOT生成55EF、240纹理形状、45PNG和4IFL；manifest及PNG全部逐字节匹配当前目录。259已启用且链到349，349原本没有EffectID；201/551/203/204没有被默认导入。catalog/guide不再标阎罗为pending。

### P-IMPORT 启用目录到原资源
- path_type: callflow
- evidence_ids: [E-IMPORT]

NATIVE_MOVE_CATALOG rage且非pending → POS自动Link链 → 原EffectID → EF原节点及纹理 → manifest与PNG。

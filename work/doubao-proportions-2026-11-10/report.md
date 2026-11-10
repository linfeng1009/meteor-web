# 豆包体型与身高：核查和修正

2026-11-10；离线模型适配；flavor=null。沿用[已授权范围](../doubao-import-2026-11-10/scope.md)，仅操作用户模型的项目归档与本地游戏；没有上传或发布。

豆包确实有与春田同类的原比例丢失。把原PMX等比归一到同一目标高度后，旧适配的肩关节跨度增加37.38%、头部缩小9.25%，静止总高度只增加0.47%。固定源顶点截面也显示躯干横向约增加34%—37%、前后厚度减小约9%—13%。因此“粗壮”的主要来源是几何比例改变，原4096²JPEG和全部107,855顶点/180,698三角面此前并没有丢失。

用户要求继续后，已将豆包改为保留原表面的单一等比变换。新增源比例的30根显示身体骨骼，由原AMB/POS旋转驱动；已有显示挂点适配跟随新的手掌，原30战斗骨骼、6挂点、任务身份和战斗时序保持。9根短发骨沿用轻微弹簧。原自动绑定的下半身枢轴高于大腿根部，显示骨盆采用左右源大腿关节中点，避免围绕不合适位置转动；其余关节间距来自源骨骼。裙摆、腋下只平滑权重，完整坐标、法线与UV不再受分段变换或位移场平滑影响。

Blender共用制作函数增加标签参数，豆包和春田分别保留自己的编辑骨架名称，不改变既有春田数学。豆包工程仍位于原导入目录，原图内嵌，四段动作已重新烘焙。工坊自动提供「原模型姿态」。运行与重建仍只依赖项目内副本。

## Evidence → Finding → Path

| E-id | source_ref | repro_command | content_hash |
|---|---|---|---|
| E-001 | before/proportions.json、before/mesh.json、原导入source-copy.json | 原比例审查及源哈希核对 | validation.json、原source-copy.json |
| E-002 | build.log、原导入build-evidence.json与blend-validation.json | README中的Blender构建/重开命令 | validation.json |
| E-003 | character-tests.tap、full-tests.tap、motion-summary.json | README中的专项、完整测试和probe | validation.json |
| E-004 | proportions.json、source-vs-current.png | audit_doubao_proportions.py -- --render | validation.json |
| E-005 | browser-validation.json、source-pose-preview.png、face/run/jump/attack/game预览 | 工坊对照，实际演武L跃起/J空中A | validation.json |

| F-id | severity | evidence_ids | confidence | location | status |
|---|---|---|---|---|---|
| F-001 旧分段尺度显著改变原头身比和宽度 | n/a_re | E-001/E-004 | high | 旧build_doubao的width/head/height映射 | fixed |
| F-002 当前源网格形状、法线和UV逐顶点保留 | n/a_re | E-002/E-003/E-004 | high | 新build_doubao、独立PMX顶点核对 | validated |
| F-003 原动作、战斗骨骼和武器兼容 | n/a_re | E-002/E-003/E-005 | high | source display rig、原AMB/POS和显示挂点 | validated |
| F-004 原4K图完整保留、项目副本独立 | n/a_re | E-001/E-002/E-003 | high | assets/source/doubao、dist与Blender | validated |
| F-005 未恢复完整布料、手指和表情 | n/a_re | E-002/E-005 | high | manifest.provenance.limits | accepted_risk |

P-001，path_type=callflow：项目内源PMX/4K图 → 固定等比变换（F-002）→ 源关节长度显示骨架与仅权重平滑 → 原AMB/POS旋转、轻微发骨及显示武器（F-003）→ 原姿态/动作/实际演武 → 独立本地运行包（F-004）。旧分段坐标变换及位移场平滑已从本人物构建过程移除（F-001）。

## 验收与限制

本次启动的完整测试快照415/415通过（178.817秒），豆包和春田20项专项通过；36运行模块语法通过。独立解析原PMX，核对每个源顶点、法线、UV；原姿态蒙皮最大偏差2.7147e-7世界单位。45组动作采样全部有限、原关节矩阵不变，最大测得边增长约0.11311世界单位；原裙摆三项接缝回归保持通过。该观察值不代表全部动作上限。

Blender保存并重开确认107,855顶点、180,698三角面、39显示骨骼、四段编辑动作、4096²JPEG原字节内嵌且无链接库。静止与烘焙矩阵误差约6.71e-6和7.63e-6。日志中的缩略图缓存写入提示没有影响工程保存和重开。

浏览器验证了原姿态、脸部、跑步、跳跃、出招，及炼铁狱实际入场、L跳跃、J空中A；页面控制台无error/warn。临时验收对局关闭，人物选择恢复为原来的孟星魂，工坊保留原姿态预览。

本地运行包的文件数、字节数、SHA-256及与当前dist的逐文件一致性记录见validation.json。原署名：版权归属《豆包》，建模sdn1111，绑定鹿铃；使用说明保留。源下载目录未被本轮删除。

显示骨架和衣物权重仍是适配；抬腿、屈膝等大幅动作有衣裙穿插，未恢复布料、独立手指、表情或完整MMD物理。源单位没有核实为现实厘米，报告不推断真实身高。

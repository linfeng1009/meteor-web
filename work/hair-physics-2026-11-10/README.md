# 导入人物的轻微头发物理

胡桃、影、爱蜜莉雅均已接入独立发束骨骼。根据实机反馈，默认使用克制的跟随参数：98%驱动运动传递、较强阻尼、整束方向最多偏转0.04弧度（约2.3°）。游戏中默认启用，人物工坊可用「头发物理」按钮开关比较。

| 人物 | 新增发束骨骼 | 发链根数 | 重新绑定的头发顶点 |
|---|---:|---:|---:|
| 胡桃 | 58 | 6 | 2,304 |
| 影 | 33 | 3 | 4,244 |
| 爱蜜莉雅 | 20 | 4 | 1,562 |

原30根身体骨骼、动作与武器挂点保持原有数据。新增骨骼只用于外观渲染。几何、法线、UV、三角面和非头发权重与基线一致。

本目录的 `hutao-弹簧发束.blend`、`raiden-弹簧发束.blend`、`emilia-弹簧发束.blend` 保留可编辑发骨和权重。物理在 Web 运行，未烘焙为 Blender/MMD 物理动画。

在项目根目录重建：

```sh
/Applications/Blender.app/Contents/MacOS/Blender --background --python scripts/blender/add_hair_springs.py
node --max-old-space-size=512 scripts/probe-hair-motion.mjs
node --max-old-space-size=512 --test --test-concurrency=1 --test-timeout=45000 tests/native-hair-springs.test.mjs
```

脚本使用现有转换网格和 `work/*-pmx-model/source-audit.json` 中的骨骼位置、层级重建平滑邻近权重，不需要已清理的 Downloads 原目录。若运行旧 `build_*_pmx.py` 重建全身，随后必须再运行头发脚本。`baseline/` 为首次处理前的绑定基线，请保留以验证身体权重。

8项头发专项通过，33个运行模块语法检查通过。完整389项测试的首轮出现一项旧的“头发只能刚性绑定头骨”断言，以及一个45秒文件级超时；更新断言为“仅允许头骨及其发束后代”，并对长时关卡使用180秒上限后，两组定向复验分别3/3、10/10通过，其余已通过项目未重复运行。详见[技术记录](2026-11-10_模型适配-头发物理-report.md)、[专项TAP](hair-tests.tap)、[完整首轮TAP](full-tests.tap)、[关卡复验](mission-recheck.tap)、[影资产复验](raiden-recheck.tap)和[验证摘要](validation.json)。

仍为简化弹簧与身体代理碰撞；未实现原MMD刚体系统、衣裙物理、发束自碰撞及场景障碍碰撞。大幅姿势仍可能局部穿插。

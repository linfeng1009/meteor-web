# 芙宁娜泳装资源转换记录

「芙宁娜 · 泳装」和「芙宁娜 · 常服」共用芙宁娜的人物身份与《流星》动作。演武选角可选择任一外观，人物工坊选中泳装时会并排显示常服。泳装原始包和可编辑 Blender 文件已存入项目。

## 范围

在用户授权范围内离线读取本地泳装包，复用项目中的芙宁娜脸部资产，转换到本地 Web 游戏。见[范围与授权](../work/furina-swimwear-import-2026-11-13/scope.md)和[时间线](../work/furina-swimwear-import-2026-11-13/timeline.md)。

## 证据与结果

| 证据 | 复查来源 | 观察 |
|---|---|---|
| E-001 | [原包文件与 SHA-256](../work/furina-swimwear-import-2026-11-13/source-copy.json) | 19 个文件，包含顶点、权重、UV 三份流及两个有效索引流。INI 指定的步长分别为 40、32、20 字节，Body 索引流长度为零。 |
| E-002 | [构建记录与运行时哈希](../work/furina-swimwear-import-2026-11-13/build-evidence.json) | 读入 43,336 个源顶点与 71,492 个三角形。转换后有 45,893 顶点、74,958 三角形、30 个动作骨骼和 6 个短发弹簧骨骼。 |
| E-003 | [Blender 正面站姿预览](../work/furina-swimwear-import-2026-11-13/preview.png) | 检查了脸部与颈部衔接、泳装和饰物，以及站姿、跑步、跳跃和出招的关键帧。 |
| E-004 | [人物运行时测试](../tests/native-furina-character.test.mjs) | 运行时可以加载并来回切换两套外观，切换保存同一原版骨架的当前姿态。面部贴图能从常服资源目录解析。 |

- F-001（已验证，高置信度，n/a_re，E-001、E-002）泳装、短发和饰物由 `Head.ib` 提取，`Dress.ib` 提供半透明叠层。Head 色图来自 `HeadLightMap.dds`，Dress 色图来自 `DressDiffuse.dds`。两份色图以 2048×2048 输出。
- F-002（已验证，高置信度，n/a_re，E-001、E-002、E-003）原包的脸部覆盖项只给出替换贴图。Web 版沿用常服版芙宁娜的脸部网格、异色眼睛和两份共享贴图，清理了脸部已有的重叠三角形。
- F-003（已验证，高置信度，n/a_re，E-002、E-004）泳装网格按统一比例转换。根据权重分布定位关节，复用常服所接入的 30 槽骨架和原版动作，并为呆毛和两侧发梢补充弹簧骨骼。

P-001（资源数据流）项目内归档 → 读取 GIMI 网格与权重 → 合入常服脸部并适配动作 → 写入 `dist/assets/enhanced/furina-swimwear` → 选角与工坊共用游戏外观加载器。薄纱跟随身体权重，材质和骨架均按 Web 运行条件近似还原。

## 复现

在项目根目录执行下列命令。生成的 Blender 文件位于 `assets/source/furina/swimwear/芙宁娜泳装.blend`，打开时显示无武器站姿，动作编辑器中可选择四组烘焙动作。

```sh
/Applications/Blender.app/Contents/MacOS/Blender --background --factory-startup --disable-autoexec --python-exit-code 1 --python scripts/blender/build_furina_swimwear.py
node --test tests/native-furina-character.test.mjs tests/native-hutao-character.test.mjs tests/native-appearance-runtime.test.mjs
```

构建后如需更新压缩产物，运行 `npm run optimize:precompress`。本地运行时和 Blender 文件可使用项目内的归档与已转换资源。

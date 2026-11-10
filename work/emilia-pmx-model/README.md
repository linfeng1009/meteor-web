# RE0-爱蜜莉雅完整模型本地适配

本地源 `Emilia_v1.pmx` 已作为整个人物适配《流星蝴蝶剑.net》p0骨架。原PMX含16,493顶点、23,854三角面、9材质、174骨。Web为16,493顶点、14,236三角面、8材质、30原骨架与6挂点；其中6,494点仅来自省略的原重复渲染层，保留在导出数组以保持原顶点索引追溯，实际面引用9,999点。

## 源透明着色层

SHADING材质的9,618面与Cloth+Skin的9,618面位置、UV、骨权重完全对应，独立最近匹配位置/UV误差≤1.907e-6。SDW.png是透明颜色覆盖层，不是法线/粗糙图。它按原alpha覆于CLOTH.png形成cloth-composed.png，再省略重复SHADING面，避免普通Web PBR重复共面导致闪烁。实际身体与服装基础表面、完整Face/Face_NoOutline/EYEBROW共1,982面全部保留。

五张原图均只读并记录SHA。运行使用4图：合成cloth-composed 2048²，原face/hair 1024²，原accessories 512²。原Hair的alpha为229..255，没有将其错误裁切成缺发。

## Blender与动作

源文件 `爱蜜莉雅-完整模型-流星动作适配.blend` 打包运行贴图、完整人物、原p0骨架与Pose6待机／144跑步／151跳跃局部姿势／262持剑攻击四段可编辑动作。跳跃世界位移由Web宿主驱动，Blender保留原局部姿态。

```sh
/Applications/Blender.app/Contents/MacOS/Blender -b --factory-startup --python scripts/blender/build_emilia_pmx.py -- --skip-render
/Applications/Blender.app/Contents/MacOS/Blender -b --factory-startup --python scripts/blender/render_emilia_pmx.py
```

Blender 5.4.0 Alpha。有效head/tail+roll对齐后实际rest矩阵误差8.39e-6，原AMB姿态误差3.81e-6。按此源模型关节独立映射；源上半身b、无足D等骨名差异已处理。腹部源thigh权重延伸至hip上方的局部拉伸，采用rest位置与权重同步连续过渡修复；上半段大腿按本源关节长度平滑过渡。Cloth腰臀近中线、跨双腿的公共布片按源hip宽度与高度平滑融合到pelvis/torso，并乘源左右腿权重混合度4·wL·wR/(wL+wR)²；纯单腿布片不应用这一融合，避免抬腿时被两根大腿反向拉扯或误改单腿蒙皮。

## 当前边界

头发刚性随头、长袖随前臂，衣裙采用简化蒙皮；尚未接入MMD物理、面部morph、独立手指抓握、原作游戏技能或着色器。大动作仍可能有局部衣物形变、穿插。最终独立45帧检查中，脸部与头发网格边长恒定；衣物边99%分位伸长约1.88倍。纯单腿布片误归pelvis的回归已消除，但一处公共衣布边仍可由172.6mm拉至453.2mm（增加28.1cm），皮肤局部最大增加约15.5cm；这不是零拉伸或完整布物理适配。原SDW透明覆色已烘焙到颜色图，不能当作原游戏动态光照复现。浏览器直接读取原AMB，不依赖烘焙Action。

## 来源与署名

PMX内嵌原文：Games: Re:Zero Infinity & Witch's Resurrection；credit: Skymoons / Elemental Craft / Kadokawa corp / chenxs / 陈心舒。原文见 `原模型使用说明.txt`。该包未提供明确使用许可证，不推断可再分发或商业使用。本次按用户要求只在本地转换，未上传，Downloads原文件未修改，也未执行模型包内任何程序或第三方导入插件。

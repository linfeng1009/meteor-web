# YS-胡桃完整模型本地适配

用户提供的 `胡桃喵1.0.pmx` 已作为**整个人物**适配《流星蝴蝶剑.net》Web版 p0 骨架；未拆取脸部拼入旧GIMI MOD。早期4K MOD缺原生脸部，现以完整PMX的身体、脸部、头发、衣装、猫耳及五张原贴图替换该不完整预览。

- 原PMX：20,521点、27,026三角面、248骨。
- Web：20,521点、23,686三角面、21材质、30骨及6原版dummy挂点。
- 完整保留面、面1、白目、目、睫、口舌、二重、眉、齿、目星共3,102三角面。
- 减少的3,340面仅为MMD `发sp+` 特殊加法高光pass，与发完全重复，直接作为普通PBR表面会z-fighting；普通Web材质光照取代这一pass。
- 五张2K原色贴图：`face.png`、`hair-hat.png`、`hair.png`、`body.png`、`cat-ears.png`。所有源颜色贴图alpha均255，不把sphere-map透明通道当普通贴图。
- UV与早期4K GIMI MOD非同构，未混用4K材质。
- 原模型文件与下载目录保持只读，未执行MOD注入代码或第三方Blender插件。

## Blender源文件与复现

`胡桃喵-完整模型-流星动作适配.blend` 内含已打包贴图、完整人物、原p0绑定骨架及四段可编辑动作：Pose6待机、144跑步、151跳跃局部姿势、262持剑攻击。浏览器直接采样原AMB，不依赖Blender烘焙Action。跳跃世界位移由浏览器游戏控制器应用，Blender动作保留原局部骨骼运动。

在项目根目录运行：

```sh
/Applications/Blender.app/Contents/MacOS/Blender -b --factory-startup --python scripts/blender/build_hutao_pmx.py
```

使用本机Blender 5.4.0 Alpha（2026-10-23构建）。`-- --skip-render`可省略渲染。`pmx_reader.py`只读取PMX几何/材质/骨架数据前缀，未执行文件中的程序。

目标绑定在创建有效head/tail后设置roll，退出EditMode后实际 `bone.matrix_local` 与 `REST@C` 最大误差8.39e-6；原AMB姿势最大矩阵误差3.82e-6。短间距源PMX躯干骨不直接硬映到长间距p0躯干；改为按native实际高度连续分配pelvis/spine/spine1/neck/head权重，减少腰部相邻面拉伸，并消除耳侧肌肤的torso残留影响。

## 着色与当前边界

原模型为MMD toon用法线与材质，Cycles物理光照下脸部会产生部分三角形明暗边界。`face-emission-only.png`显示原贴图和几何本身完整；不以更改UV、删面或涂抹贴图来隐藏。Web工作坊的光照更接近角色预览。

目前使用原版《流星》角色动画、碰撞、移动和武器挂点。头发、衣摆为随躯干/头部的近似蒙皮；未实现原神/MMD物理、面部表情morph、完整手指动画或原神战斗技能。四肢按源PMX关节与native骨架做rest-space重定位，动作幅度很大时长发/衣摆仍可能穿插。

## 署名与原模型说明

原PMX内嵌说明署名：模型提供 miHoYo，模型改造 观海（Bilibili：观海子）；用户提供文件夹另署 摸鱼大水怪，两者均保留。原文见 `原模型使用说明.txt` 与 `source-audit.json`。

原说明允许完善物理、修复权重/表情等问题、适度改色改衣，要求非商业使用，禁止二次配布及拆取部件改造其他模型。本次结果仅保存在用户本机项目，未上传或发布。

早期不完整GIMI的manifest/mesh/贴图保存在此目录的 `old-incomplete-*` 与 `old-incomplete-textures/`，可追溯对照。

## 独立验证

独立源/资产检查3项通过；15动作首中尾共45帧全部20,521顶点检查通过，脸部三角边长保持一致，未出现整体爆炸。连续躯干和cloth-root权重修复后，先前腰背/耳侧/衣根接缝高伸长已消除，最大边伸长比约4.88，来自极短的短裤/上腿关节边（约16.5mm→80.6mm），属于首版动作适配仍需继续精修的局部形变；99%边约2.34以内。证据见相邻`work/hutao-pmx-quality/`目录的独立audit与测试记录。

# 素材与格式来源

更新：2026-10-23。当前构建优先读取用户提供的本地《流星蝴蝶剑.net》客户端 `lxhdj_`。源目录只读，没有执行客户端。

## 当前运行素材

原游戏：昱泉国际 / Interserv，《流星蝴蝶剑.net》。模型、地图、人物、动作、脚本、图像和声音的权利归各自原权利人。

- `original/manifest.json`：地图 GMB / DES / COB、地图脚本、Level / PScriptLib、UI、音频、EF 定义和贴图；3,036 个主清单条目。
- `original/characters/manifest.json`：20 套人物 SKC / BNC / AMB / POS、原人物传记图和贴图、Common 原动作。
- `original/characters/meteor-res-data.json`：完整 Meteor.res，保留偏移、物品、动作和数值字段。
- `original/weapon-models/manifest.json`：59 个物品、71 个模型，含原型号与左右手变体；w6_5 源文件缺失。
- `original/scene-models/manifest.json`：114 种模型记录均有原文件（双刺前缀别名解析为实际 r/l 型号）；3 张缺失贴图显式记录。
- `native/combat/`：原 POS / ACT 文件和动作证据。

清单保留原文件路径、尺寸与 SHA-256。BMP / TGA 转为浏览器 PNG 时保留原文件和转换记录。提供的目录包含松散文件与 PAK，优先级及差异见提取报告；没有声称它等同于认证的纯净官方发行版。

## 格式与动作交叉核对

- [流星资源网](https://www.lxres.com/)，原资源缺失时的补充来源。
- [GMC 地图结构](https://www.lxres.com/LiuXingBiJi/1566.html)，漠之北。
- [DES 地图结构](https://www.lxres.com/LiuXingBiJi/1569.html)。
- [兵器招式表](https://www.lxres.com/LiuXingBiJi/1559.html)。
- [Pose 动作资料](https://www.lxres.com/LiuXingBiJi/1758.html)。
- [AMB 格式读取器](https://github.com/IceRiverr/Meteor/blob/master/Tools/AmbToTxt/compile_amb.cpp)：仅核对固定宽度 dummy 父骨骼字段，没有复制实现代码。该仓库许可未确认，使用自行编写的解析器。

格式资料与 EXE 证据分别记录。攻击帧、骨骼、位移、ACT 连接读取本地原文件；气血、伤害和基础怒气增量由本地 EXE 反编译核实。完整输入识别、AI、物理和网络协议仍待还原。

## 研究阶段素材

最初研究下载过唐家笑三少的「超清官方原味四方阵」与太阳依然和谐的「好贱」社区剑模型。改用本地原版后，当前引擎不再使用这两套资源；研究记录保留在本地 `assets/source/`，无需发布。

## 运行库

[Three.js r170](https://github.com/mrdoob/three.js/tree/r170)，MIT 许可。许可文件：`../vendor/LICENSE-three.txt`。


## 本地人物工坊（2026-10-28）

- `enhanced/hutao/`：用户提供的完整「胡桃喵1.0.pmx」转换，源目录标注摸鱼大水怪，PMX内嵌说明署名模型提供 miHoYo、模型改造观海。保留完整模型造型，本地适配《流星》骨架。来源与完整说明见本地 `work/hutao-pmx-quality/source-audit.json`。
- 先前 `HuTaoMod4K` GIMI包不包含脸部几何，且UV与此PMX不同；未与PMX拼接，不作为当前可玩角色素材。

胡桃模型内嵌说明要求非商业、不可二次配布。本次转换仅供用户本机使用，未上传或更新线上站点。原MMD物理、表情、sphere/toon着色与《流星》动作的材质及骨架适配有差异。


## YS-影本地外观（2026-10-28）

`enhanced/raiden/` 来自用户提供的「礼服影.pmx」及配套贴图。原24,203顶点、30,604三角面完整保留，27材质、7张源颜色图（6张2K、1张1K），沿用原p0骨架与游戏动作。肌肤贴花保留原透明裁切。

原readme署名：头部 miHoYo／ota／ash.k／manashiku；身体 miHoYo／观海子；改模 花咲十七夜。原说明注明非商业、不可二次配布。本次只读原包，转换结果保存在本机，未上传。模型内的MMD物理与表情尚未接入；完整来源与检查见本地`work/raiden-pmx-quality/`及`work/raiden-pmx-model/`。


## RE0-爱蜜莉雅本地外观（2026-10-29）

`enhanced/emilia/` 来自用户提供的「Emilia_v1.pmx」。源16,493顶点、23,854三角；运行14,236三角、8材质。原SHADING的9,618面与Cloth+Skin的位置、UV和权重一致，已将SDW透明阴影图合成至CLOTH，避免重合表面闪烁；完整Face、Cloth、Skin及其他实际表面保留。4张运行颜色图由5张源PNG转换，原FACE/HAIR/ACCS内容保留。

原包内嵌署名为 Skymoons／Elemental Craft／Kadokawa corp／chenxs（陈心舒），没有明示使用许可。署名与原说明保存在本地工作目录。本次是用户指定本地模型的离线转换，未上传站点。MMD物理、表情与完整手指尚未接入，头发与衣袖采用简化骨骼适配。


## 2026-11-06 关卡扩展复用

决死阵 sn09 与飞鹏堡 sn15 复用本地原地图 GMB/DES/WP、cmodel/FMC、Level/NPC PST、人物与兵器资源，没有下载或生成替代模型。脚本道具身份与数值来自已导出的 Meteor.res type2/id4、id14。两关配乐选用本地原 s1.mp3 / s2.mp3，具体曲目对应关系为 Web 选择，未声称由 EXE 恢复。

## 霜翎凤鸣枪外观（2026-11-06）

依据用户提供的双尖冰晶凤翼长枪概念图制作，运行模型为 `dist/phoenix-spear.js` 中的三维几何与程序纹理。图中背面、厚度、凤羽与挂饰连接按游戏模型需要推测；未直接使用画面背景或将概念图贴在平面上。外观沿用原版 W7_0 的握持方向与长度，原版模型继续承担攻击范围计算。参考图、几何导出、实际模型预览及 Blender 工程保存在 `work/phoenix-spear/`。


## 栖云古庭原创战场（2026-11-10）

`enhanced/maps/qiyun/` 的场景模型由本项目的 `scripts/blender/build_qiyun_courtyard.py` 在本机 Blender 中程序建模，包含石板庭院、山门、亭台、树木、植被、岩壁和远山。石材颜色贴图通过内置 image_gen 生成，最终提示词保存在 `work/qiyun-courtyard/stone-texture-prompt.txt`。运行模型按材质合批，并独立制作地面、台阶和建筑碰撞。天空、雾、水流与风由 `dist/qiyun-courtyard.js` 实现。可编辑 Blender 工程、GLB、预览和验收记录保存在 `work/qiyun-courtyard/`。

## 雷电影佩刀本地外观（2026-11-10）

`enhanced/weapons/raiden-sword/` 来自用户提供的「【模之屋】雷电将军」包中独立的 `武器.pmx`，原包署名模型提供 miHoYo、模型改造观海（观海子）。保留原弯刃几何、UV 与 2048×2048 颜色贴图；源 1,566 顶点、1,850 三角，42 个重合发光面合并至同一表面，运行 1,808 三角。原发光图按透明度合成后低强度使用，MMD sphere 通道改为克制的 PBR 反射，非完整 MMD 着色复现。

原包说明要求非商业、不可二次配布，完整说明及源文件哈希保存在本地 `work/raiden-sword/`。本次为本机显示适配，未上传。握持挂点与长度对齐原长剑，攻击范围、伤害与特效端点仍使用原版 W0_0。导入脚本为 `scripts/import-raiden-sword.py`，可编辑 Blender 工程与预览一并保留在工作目录。

## 怒气技能视觉层（2026-11-06）

2026-11-10 修正：乾坤刀末击的SLASH01–06及SLASH_L01–06均沿用原EF键和`LIGHTa00.bmp`转换贴图，按可绘制节点末键延长视觉播放，防止POS动画先结束而漏掉刀光。普通挥砍和怒招拖尾读取原POS Drag时间窗/颜色/时长与原武器DES端点，使用Web柔边光带绘制。亮度、拖尾采样/渐隐、完成后的挂点快照属于显示适配；本轮未新增或替换原纹理，也未改变攻击碰撞、伤害和怒气规则。原粒子发射、DONUT及完整材质通道仍未完全恢复。

`original/rage-vfx/` 来自用户本地客户端的 PonEF V1.00 定义、`ETexture.pak` 和 `TexturePatch.pak`。`scripts/import-rage-vfx.py` 按当前可用怒气招式与自动衔接动作导出 54 组定义、236 个带贴图的形状节点、49 项贴图/序列引用；BMP/TGA 无损转 PNG，保留原尺寸与透明度。每个 EF 及纹理归档成员的 SHA-256 保存在清单中。武器特效挂点取原版 DES，与外观皮肤独立。

Web 视觉播放器读取原关键帧位置、旋转、缩放、透明度，使用基本形状表现蓄力光、旋风、光刃与冲击波。插值、形状网格构建、亮度上限与 IFL 30fps 播放是明确的 Web 适配；原版粒子发射、DONUT、完整材质通道语义及特效专属远程碰撞仍未完全恢复。不会将视觉形状直接作为攻击范围。恢复记录在 `work/rage-vfx/2026-11-06_逆向-怒气特效-report.md`。

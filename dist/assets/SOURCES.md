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

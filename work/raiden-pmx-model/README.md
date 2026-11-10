# YS-影 · 礼服模型本地适配

用户提供的完整「礼服影.pmx」已作为独立外观 `raiden` 适配《流星蝴蝶剑.net》p0骨架，胡桃与原版人物资源保留。

- 源：24,203顶点、30,604三角、27材质、363骨。Web完整保留所有顶点、面、材质；不是用程序占位人物。
- 面、面2、星目、口舌、二重、白目、睫、眉、齒、目共3,278三角完整保留，面部顶点纯原p0 Head(13)绑定。
- 7张原PNG颜色图：6张2K、1张1K，直接复制保留SHA256及UV。肌/肌2确有被模型使用的透明像素，采用alphaTest .35、transparent=false、depthWrite=true；Blender也用Alpha硬裁切。没有把toon/sphere map当PBR法线。
- 使用原p0 30骨与6挂点，原AMB实时驱动。原模型身高、手臂/腿长与胡桃不同，依其头、首、肩、肘、腕、髋、膝、踝关节重新建立rest-space映射，躯干与裙根按实际高度连续分配权重。
- 长发英文Hair骨链、繁体裙擺骨、胸部与袖配重均识别；长发使用统一头骨绑定，避免跨头/脊柱权重在攻击时将发尾拉成橡皮；衣袖/裙摆现为骨骼近似跟随，尚未实现325刚体/348关节的MMD物理。

## Blender编辑与重建

`雷神影-礼服模型-流星动作适配.blend` 已打包贴图，保留4段可编辑Action：6持剑待机、144跑步、151跳跃局部姿势、262持剑攻击。世界跳跃仍由Web碰撞/镜头宿主控制。绑定采用有效head/tail与align_roll，actual rest矩阵误差8.39e-6，姿态矩阵误差3.81e-6。

```sh
/Applications/Blender.app/Contents/MacOS/Blender -b --factory-startup --python scripts/blender/build_raiden_pmx.py -- --skip-render
/Applications/Blender.app/Contents/MacOS/Blender -b --python scripts/blender/render_raiden_pmx.py
```

使用本机Blender 5.4.0 Alpha。PMX由项目内纯数据读取器解析，没有执行下载模型中的代码或外部插件。Downloads原文件只读。

## 来源与使用说明

源文件及贴图SHA256见 `source-audit.json` 和运行manifest。模型外附readme署名：头部miHoYo／ota, ash.k, manashiku；身体miHoYo／观海子；改模花咲十七夜。PMX内嵌comment署名miHoYo／观海／花咲十七夜，两者均保存于 `原模型使用说明.txt` 与.blend。

原说明允许修物理/权重/表情bug、改色与适度衣装调整，并注明非商业、不可二次配布。本次转换只保存在用户本机，没有上传或更新站点。

## 当前边界

这是原版动作的首版骨骼适配；未实现MMD/原神物理、面部morph、完整手指与原神战斗技能。源角色长发和飘带本身呈明显向后的静态展形，当前保留此造型；大幅动作仍可能与身体穿插。Cycles物理光照下的脸部面层有局部三角明暗边界，与MMD toon原着色不同；没有删脸面或更改UV来掩盖。

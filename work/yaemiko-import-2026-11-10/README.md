# 八重神子人物导入

八重神子已接入首页「选择人物」、设置「人物外观」和人物工坊。保留原模型身材比例、25,219顶点、29,140三角面、25材质与5张原2048²PNG；原动作与武器已适配，长发和发绳使用48根轻微弹簧骨骼。工坊可点「原模型姿态」查看原造型。

- 运行资源：`dist/assets/enhanced/yaemiko/`，只依赖项目dist。
- 完整源归档：`assets/source/yaemiko/`，12个源文件共8,490,371字节，逐文件SHA-256与用户目录一致；系统.DS_Store不作为模型资源。运行和重建不依赖Downloads。
- 编辑工程：[八重神子-流星动作适配.blend](八重神子-流星动作适配.blend)。原5张2K图全部内嵌，无链接库，30根显示身体骨骼加48发骨，含站姿、跑步、跳跃局部姿势和持剑攻击四段动作。
- 本地运行包：`artifacts/meteor-web-v0.7.6.zip`，包含转换网格、原贴图及当前游戏运行资源，4,182文件核验。未发布或上传。
- 作者：模型提供miHoYo，模型改造观海（BiliBili：观海子）。[原说明](原始配布Readme.txt)与署名随资源保留。

## 验收

8项八重神子专项通过。逐顶点独立核对原PMX形状、法线与UV，证明使用同一等比变换，没有单独压缩头部、腰腹或四肢。45组动作采样全部有限，原30身体骨骼与6挂点矩阵不变，原姿态蒙皮最大偏差1.8988e-7世界单位；静止与烘焙矩阵误差约3.04e-6、7.63e-6。Blender重开确认5图内嵌、78骨骼、四段动作及无外部链接。

当次完整测试快照496项中494通过，2项HTTP联机测试因沙箱禁止本机监听而报EPERM；允许回环端口后，其所在两文件18项全部通过，原两项均获得通过覆盖。46个运行模块语法通过。保留首轮失败记录和复验记录，不将其描述成单次全套无失败。

浏览器检查了原姿态、脸部、跑步、跳跃、出招、透明发光泽层，以及炼铁狱实际载入、材质和武器显示。后台浏览器无法锁定鼠标，当前鼠标攻击/跳跃绑定未触发，因此未把这两项计作实际演武手动验收；动作兼容由工坊及CPU采样覆盖。临时对局关闭并恢复此前人物选择，工坊保留。详见[验证摘要](validation.json)、[浏览器记录](browser-validation.json)、[技术报告](report/2026-11-10_模型适配-八重神子-report.md)。

预览：[原模型姿态](source-pose-preview.png)、[脸部](face-preview.png)、[跑步](run-preview.png)、[跳跃](jump-preview.png)、[出招](attack-preview.png)、[实际演武](game-preview.png)。

## 重建

项目根目录执行：

```sh
/Applications/Blender.app/Contents/MacOS/Blender --background --factory-startup --disable-autoexec --python scripts/blender/build_yaemiko.py
/Applications/Blender.app/Contents/MacOS/Blender --background --factory-startup --disable-autoexec --python scripts/blender/check_yaemiko_build.py
node --max-old-space-size=512 scripts/probe-yaemiko.mjs
node --max-old-space-size=512 --test tests/native-yaemiko-character.test.mjs
node --max-old-space-size=512 --test --test-concurrency=1 --test-timeout=240000 tests/*.test.mjs
npm run check
npm run package
```

原髪+/前髪+是透明高光层，spa_h的Alpha只有0—41，已保留为不写深度的透明pass；原网格和原图不改绘。原toon与sphere完整着色未复现。袖摆、裙摆、流苏仅随各自源父骨区域，尚无布料模拟；表情和独立逐指控制仍简化，大幅动作可能局部穿插。源单位没有现实厘米标定，不宣称真实身高。

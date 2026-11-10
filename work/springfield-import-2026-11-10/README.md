# 春田导入与原比例修正

春田已接入人物选择、设置、工坊与演武。针对初版躯干压缩、皮肤粗糙的问题，改为保留原网格的等比形状，让原动作驱动独立显示骨架；修正Unity打包法线和RMO粗糙度的通道读取。工坊的「原模型姿态」显示原始造型，播放或选择动作可返回动作预览。

- 完整源归档：`assets/source/springfield/`，43文件共24,551,400字节，逐文件SHA-256与源目录核对一致。运行和重建均不依赖下载目录。
- 运行资源：`dist/assets/enhanced/springfield/`，61,222顶点、81,307默认可见三角面、36材质、33原贴图、30显示身体骨骼加71发骨。
- 编辑文件：[春田-泳装P3-流星动作适配.blend](春田-泳装P3-流星动作适配.blend)，33张原贴图内嵌、无链接库，含待机、跑步、跳跃局部姿势和攻击四段可编辑动作。
- 预览：[原模型比例](source-proportions-preview.png)、[脸部](quality-face-preview.png)、[跑步](quality-run-preview.png)、[跳跃](quality-jump-preview.png)、[出招](quality-attack-preview.png)、[演武](quality-game-preview.png)。
- 原作者：Sunborn Network Technology；绑定修正：DesmondChan／摸鱼的可露凯。[原配布说明](原始配布Readme.txt)保留。原说明对再配布、商业及MMD用途有限制；本轮未发布或上传模型。

完整回归413/413通过，春田专项11/11通过，36个运行模块语法通过。45个动作采样坐标有限，原30身体骨骼及6挂点数值不变；原姿态蒙皮误差最大2.3034e-7世界单位。包内4,144文件核验通过。详见[验证摘要](validation.json)、[技术记录](report/2026-11-10_模型适配-春田原比例与材质-report.md)及[浏览器记录](browser-validation.json)。

在项目根目录复现：

```sh
/Applications/Blender.app/Contents/MacOS/Blender --background --factory-startup --disable-autoexec --python scripts/blender/build_springfield.py
/Applications/Blender.app/Contents/MacOS/Blender --background --factory-startup --disable-autoexec --python scripts/blender/check_springfield_build.py
node --max-old-space-size=512 scripts/probe-springfield.mjs
node --test tests/native-springfield-character.test.mjs
node --max-old-space-size=512 --test --test-concurrency=1 --test-timeout=180000 tests/*.test.mjs
npm run check
npm run package
```

身体原贴图1024²，头发贴图2048²，没有AI改绘、减面或虚构4K。光照与着色仍和原MMD/源游戏渲染不同；衣物、表情、独立手指及完整MMD物理未接入，大幅动作可能局部穿插。头发沿用克制的Web弹簧参数。

`baseline-compressed/`和未带`quality-`前缀的早期测试/截图保留初版过程，不作为当前画质验收依据。

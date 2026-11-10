# 豆包人物导入

同日后续已修正原身材比例，当前使用独立显示骨架保留源网格形状；本目录的Blender工程、build-evidence、blend-validation和motion-probe已更新。下文396项验收和旧适配描述为初次导入快照，修正前资产另存。当前验收、对比图及限制见[原比例修正记录](../doubao-proportions-2026-11-10/README.md)。

首页「选择人物」、设置「人物外观」和人物工坊均可选择「豆包」。完整模型、4K贴图、原版身体动作和武器挂点已接入，头发采用轻微弹簧跟随。作者署名：版权归属《豆包》；建模sdn1111；绑定鹿铃。

- 游戏资源：`dist/assets/enhanced/doubao/`，运行只加载项目dist资源。
- 完整原始归档：`assets/source/doubao/`，9个文件共110,009,311字节，复制后逐文件SHA-256与用户提供的源文件核对一致。
- 动作适配Blender：本目录的 `豆包-完整人物-流星动作适配.blend`，原4K贴图内嵌，保留待机、跑步、跳跃局部姿势、攻击四段可编辑动作。
- 原模型独立编辑副本：`豆包-源模型-贴图已内嵌.blend`。运行采用上面的转换结果，不需要此文件。
- 本地运行包：`artifacts/meteor-web-v0.7.6.zip`，包含豆包JSON网格、JPEG贴图及全部原版运行资源；原PMX和下载目录均不是运行依赖。

用户可以删除下载目录中的源文件。项目归档、转换后资源与Blender编辑文件均已保留；本轮没有删除用户下载文件。

在项目根目录重建：

```sh
/Applications/Blender.app/Contents/MacOS/Blender --background --factory-startup --disable-autoexec --python scripts/blender/build_doubao.py
/Applications/Blender.app/Contents/MacOS/Blender --background --factory-startup --disable-autoexec --python scripts/blender/check_doubao_build.py
node --max-old-space-size=512 scripts/probe-doubao.mjs
node --max-old-space-size=512 --test --test-concurrency=1 --test-timeout=180000 tests/*.test.mjs
npm run check
npm run package
```

验证：396/396测试通过；7项豆包专项通过；45个动作采样坐标有限、原关节不变；33个运行模块语法通过。Blender重开后确认无链接库、贴图全部内嵌；运行包4,100个文件核验通过。详见[验证摘要](validation.json)、[技术记录](2026-11-10_模型适配-豆包-report.md)、[完整TAP](full-tests.tap)、[Blender校验](blend-validation.json)和[浏览器预览](workshop-preview.png)。

仍是原版比例与动作的适配：衣物没有布料模拟，手指整体随手掌，未接面部表情；大幅动作可能有局部穿插。原18万三角面完整保留，因此几何开销高于此前几个导入人物。

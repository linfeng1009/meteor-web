# 月蝶剑试版

依据用户提供的单张正面图片制作，游戏模型位于 `dist/butterfly-sword.js`。剑身、蝶翼护手、金色纹路、蓝色飘带和红色剑穗是三维几何；遮挡和背面按参考图推测。当前是轮廓试版，尚未复现图片中的复杂纹理、动态飘带、蝶群与挥剑粒子。

从首页「游戏设置」→「长剑外观」可在月蝶剑与原版长剑间切换。新外观只作用于玩家手中的剑，原始武器模型继续承担战斗判定；游戏动作、攻击距离和伤害数据不变。

Blender 文件由游戏几何导出，便于查看与后续编辑。重新生成：

```sh
node scripts/blender/export_butterfly_sword.mjs
/Applications/Blender.app/Contents/MacOS/Blender -b --factory-startup --python scripts/blender/render_butterfly_sword.py
```

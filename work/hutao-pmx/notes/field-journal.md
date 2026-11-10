# 本地PMX导入经验 · 2026-10-28

用户提供完整YS-胡桃PMX后，改用整份模型，避免将面部拆进另一套GIMI MOD。两套UV不同，不能按贴图分辨率替换。静态解析验证了完整面部、248骨和所有贴图引用；未执行用户包内任何代码。

Blender新建editBone的初始长度为零，直接赋matrix后再改length会丢失预期方向。应先建好层级，再由目标矩阵列向量显式设head/tail与align_roll；必须比较actual bone.matrix_local与native rest，而非仅检查姿态矩阵。新方法已用于胡桃构建，并回修孟星魂HD工程。

旧partial资源仍保存于work/hutao-pmx-model，未假装提供完整脸部。运行时保留每次启用前的完整性检查，以及切换失败保留当前外观的行为。游戏外观只是p0外观层，剧情身份、数值与武器挂点不改变。

# 原场景缓存状态生命周期修复

日期：2026-10-26。使用本地原资源，不执行或修改原 EXE，不涉及 HD 角色并行修改。

## Evidence → Finding → Path

基线探针使用实际 sn01 地图、DES/cmodel/FMC、原场景 PST 与生产 `menu` / `start`。仅略去纹理解码、渲染和人物构造，以合成人物对象隔离场景生命周期。基线结果保存在 `scene-lifecycle-audit-baseline-2026-10-26.json`：`D_St22` 原回调损坏并完成破碎后 active/collision=0，`D_itSt22` active/interactive=1；退出剧情到菜单再进入同图演武后，这些状态仍存在。重新开始剧情会由原 `Scene_OnInit` 正确恢复，故没有把正常的剧情重开误报成 bug。

发现：地图几何与实例被缓存，原 PST 对 mutable props 的修改也随之保留；原 `items.reset()` 只清消费记录，不恢复场景。修复路径：加载每个原实例时保存来源基态 → `props.reset()` 原位还原 → 引擎在缓存地图激活、开始新局和菜单转换边界调用 → 进入剧情时仍执行原 `Scene_OnInit` 设置任务专属状态。

## 重置契约

- `props.reset()` 同步还原所有已导入实例，返回数量；不重载地图、模型或纹理。
- 属性恢复最初的对象本身，清除新局前遗留字段，即便某调用曾替换 `instance.attributes`；保留 PST 对原属性对象的引用。
- 恢复 root 的原位置、四元数、缩放、可见性；恢复原 pose/frame/time/state/playing/loop、网格矩阵和可见性、碰撞矩阵与包围盒。
- 基态为原加载完成状态：原来 pose0 就在播放的动画按 fresh-load 状态恢复，不擅自全局冻结原本活动的动画；上一局破碎或移动地板的 pose1/loop 不延续。
- 保留 scene instance、model、mesh、geometry、material、collider、空间索引和原始 DES 引用；reset 不 dispose GPU 资源。

## 验证

`node --test tests/native-scene-lifecycle.test.mjs`：**5/5通过**，原始输出见 `native-scene-lifecycle-2026-10-26.tap`。覆盖真实首关破坏与原回调再次初始化、属性引用被替换后还原、共享资源和碰撞索引引用不变、幂等性与静态物件动画停止、sn09真实移动地板 FMC 和 collider 矩阵还原，以及生产 menu→同图training→story 的转换链。

当前 `node work/meteor-original/evidence/scene-lifecycle-audit-2026-10-26.mjs` 输出 `leakPresent:false`，保存在 `scene-lifecycle-audit-2026-10-26.json`。独立相关物品/任务宿主测试22/22通过。运行模块语法和局部diff空白检查通过。

这不是普通玩家步行、完整活 AI 战斗或浏览器渲染验收；主代理负责全套回归与页面联调。

## 校验

| 文件 | SHA-256 |
| --- | --- |
| `dist/native-scene-models.js` | `a2fa31f694b7576ed8fc628fcf8d4994f278b7e17d059a8e538405bd02d0b468` |
| `tests/native-scene-lifecycle.test.mjs` | `261cd127927461a3caad2a41871cebcfb40cfd1bb7bede1feab7db6f183dc0ae` |
| `work/meteor-original/evidence/native-scene-lifecycle-2026-10-26.tap` | `bfdb06bbb5b011bcdf71b11c0d20f8b3063ccf2d4f6562a8cef25326e687a516` |
| `work/meteor-original/evidence/scene-lifecycle-audit-baseline-2026-10-26.json` | `a8b081f639be2226125e800f20c3edf4b4dbc09946f7657d4b24e9cdf678e57e` |
| `work/meteor-original/evidence/scene-lifecycle-audit-2026-10-26.json` | `4464e76702da7f1ccf6c33cb7b66d99c76a1d29cb7e1766a36b68b6550322880` |

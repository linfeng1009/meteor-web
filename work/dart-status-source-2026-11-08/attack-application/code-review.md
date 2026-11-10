# 附加道具运行接线只读复核

2026-11-08。本复核仅阅读 `dist/native-items.js` 的 `useNativeAttackItem`/`useNativeScriptItem` 和 `dist/engine.js` 的 `_applyNativeHit`，不改运行文件或测试，不重写已封存的原函数导出与 `evidence.json`。

已确认代码读取真实 `state.poseId` 的 type3 记录，取原参数16第一个匹配项；实际 item 按已实现消费者和原字段验证。应用位于正常直接伤害与受击加怒之后，成功防御、致死、无有效数值伤害路径跳过；非防御零伤害但存活时仍应用。item22直接改怒气而不留定时active条目，item11/12同ID仅刷新寿命，保留各自周期进度。上述主链与 `004af630 → 004d5fc0 → 004afcf0 → 004d59d0` 一致。

发现并向主代理报告一处实际遗漏：初次接线的受击加怒仍是 `clamp(...,0,100)`，而item22减怒已经使用effective stat7。原 `004d4d30` 要在**每次**stat6调整时按effective stat7限制；事后item22的限制不能补回先前错误上限。

例如stat7为50，当前怒气45，本次受击加怒10：原顺序为先限制到50、再减20，结果30；固定100上限的旧接线会先到55、再减20，错误结果35。stat7高于100时也会提前截断。主代理已接收此问题，将通过共享 `nativeRageMaximum` 同时修正加怒与减怒；最终修复结果和测试由主代理新验证快照记录，本文件不冒充已执行最终回归。

item22自身的上限读取包含当前 `weaponRecord` 与 `activeItems` 的原modifier。生产actor未显式提供nativeStats7时回退100，符合 `004d4a70` 的原初始化。既有modifier筛选及百分比运算沿用 `nativeEffectiveStat`，没有将poison周期效果误当静态modifier。

初次复核时周期道具仍使用明确的Web elapsed-time策略。同期只读stat审计随后确认原server固定0.2秒更新，主代理正在替换旧策略；周期调度不在本次代码复核完成声明内。原始source结论仍保留于 [README](README.md) 和 [evidence.json](evidence.json)。本轮没有新增浏览器、原EXE运行、活AI或人工实战验收。

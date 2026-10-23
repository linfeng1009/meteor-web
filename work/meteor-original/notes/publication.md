# 私有发布交接

2026-10-23 发布已成功，身份与校验结果见 `../evidence/E-web-deployment.json`。

- 项目 `.openai/hosting.json` 的 project_id 保持不变。
- 已同步源码位于项目内 `.sites-checkout/`，它是独立 Git checkout，已被外层仓库忽略。
- 已发布源提交：`ce1c35f2bf126589d6e05af8a7eb3d113e784452`。
- 外层本地研究仓库曾因单次推送大小超限保留一个未推送的大提交；不要强推覆盖线上历史。后续使用 `.sites-checkout/` 的远端连续历史，或按 Sites skill 在空目录重新打开该 Site。
- 上传采用九批连续提交，最终 3953 个运行文件与外层 dist 的 SHA-256 逐项一致。只部署最终完整包，未部署中间批次。
- 预览保持 owner-private。浏览器确认到登录门，未代用户登录；本地实机验证与线上部署验证分开记录。
- 凭证只通过进程 stdin 传入，未保存到项目文件。再次同步时为同一 project_id 申请新凭证。

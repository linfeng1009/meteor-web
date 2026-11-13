# 3 Mbit 服务器部署优化

2026-11-12。目标：让用户尽快看到大厅，其余按需加载。

## 前后对比（Chromium 限速 3 Mbit / 40 ms RTT，缓存禁用）

| 指标 | 优化前 | 优化后 |
|---|---:|---:|
| 大厅可交互时间 | ~155 s | **39.0 s** |
| 首屏传输量 | 58.36 MB | **13.11 MB** |
| 进入对局后追加 | — | +3.48 MB（所选角色，后台补齐） |
| 重复访问 | 每次全量 | ETag 命中 304，0 字节 |

## 做了什么

### 1. 服务端压缩（`network-server.mjs`）
- 优先发送构建期生成的 `.br`/`.gz` 同名旁路文件，运行时零 CPU；
- 没有旁路文件时退回内存压缩（按 path+mtime 缓存）；
- 文本类与项目自有的数值文本（`.amb/.pos/.pst/.gmc/.gmb/.bnc/.skc`）都压缩，图片等已压缩格式跳过；
- 加 `ETag` + `Cache-Control`：HTML `no-cache`，其余 `public, max-age=3600`，再次访问走 304。

实测：`mesh.json` 19.78 MB → 2.66 MB，`character.amb` 11.90 → 7.02 MB，`manifest.json` 3.13 → 0.20 MB。

### 2. 构建期预压缩（`scripts/precompress.mjs`，`npm run optimize:precompress`）
遍历 `dist/`，为可压缩文件生成 brotli q11 + gzip 旁路：684 个文件，204 MB → 46.3 MB（23%）。有 mtime 检查，重复运行只处理变化的文件。

### 3. 贴图转 WebP（`scripts/convert_textures_webp.py`，`npm run optimize:textures`）
118 张贴图，134 MB → 17.6 MB（13%）。
- 保留 alpha 通道；
- 每张都测 PSNR（忽略全透明像素），低于 34 dB 时改用无损 WebP；再不合格就保留 PNG；
- 转换后重写 `mesh.json`/`manifest.json` 里的引用，并同步 `.png` 引用到 `.webp`；
- 同时更新 `sourceFiles`：`sha256/bytes` 记**原始归档文件**，`runtimeSha256/runtimeBytes/encoding` 记**实际下发的文件**，两套哈希分开校验。

### 4. 首屏按需加载（`dist/app.js`）
- `game.ready` 完成后立刻撤掉加载页，不再等所选地图/外观；
- 启动时用内置原生角色（`game.characterAppearance='original'`），所选高清外观推迟到 2.5 s 后空闲时后台加载；
- 用户点「开始游戏」时 `start()` 本来就会加载目标地图与外观，并通过 `sessionRequest` 让后台那次预热自动失效，不会重复堆积。

实测首屏因此从 16.59 MB 降到 13.11 MB，大厅时间从 49 s 降到 39 s。

## 现在的首屏构成

| 资源 | 大小 | 说明 |
|---|---:|---|
| `character.amb` | 7.02 MB | 原版动作数据，**当前最大单项** |
| 地图 sn06 贴图 | ~1.3 MB | 大厅背景所在战场 |
| `p0.amb` | 0.29 MB | 主角动作 |
| 其它 | ~4.5 MB | 引擎、清单、武器、菜单图 |

## 还能继续压的空间（按性价比排序）

1. **`character.amb` 7 MB（54%）**：11.9 MB 文本浮点数据，brotli 只能到 59%。改成二进制（float32 + 量化）预计可到 1.5–2.5 MB，首屏能再省约 5 MB（≈13 s）。需要改加载器 + 重新导出，属于中等风险改动。
2. **动作数据按需切分**：大厅只需要待机/走路，招式表可以对局时再取。同样需要加载器支持分段。
3. **地图贴图转 WebP**：原版地图还是 jpg，`sn06` 的 1.3 MB 可再压一半；风险低，只是这类图有 1200+ 张，转换耗时长。
4. **文件名加内容哈希 + 长缓存**：现在靠 ETag 重验证，命中 304 仍需一次 RTT。加哈希后可 `immutable` 一年，弱网首屏更稳。
5. **HTTP/2 或 HTTP/3**：3 Mbit 下多路复用能减少队头阻塞，nginx 一行配置。

## 部署到自己的服务器时

如果生产环境用 nginx 而不是 `node server.mjs`，等价配置：

```nginx
gzip on;
gzip_comp_level 6;
gzip_types text/css text/javascript application/javascript application/json image/svg+xml;
# 若装了 brotli 模块：
brotli on;
brotli_comp_level 6;
brotli_types text/css text/javascript application/javascript application/json image/svg+xml;

location /assets/ {
  add_header Cache-Control "public, max-age=3600";
  etag on;
}
location ~ \.html$ {
  add_header Cache-Control "no-cache";
}
```

`node server.mjs` 已经内置了同样的逻辑（含 `.br` 旁路），可直接用于生产。

## 复现

```sh
npm run optimize          # 贴图转 WebP + 预压缩（新导入角色后重跑）
node server.mjs           # 带压缩与 ETag 的静态服务
npm test                  # 658 项
```

## 验证

- 全量测试 **658 项全部通过**（转换后修正了测试里对 PNG 魔数/字节恒等的假设）
- 限速实测脚本：`/tmp/measure-throttled.mjs`（CDP `Network.emulateNetworkConditions`，3 Mbit）
- 功能回归：大厅可交互、点击开始能正常进入对局、角色外观在开局时正确加载、控制台零异常
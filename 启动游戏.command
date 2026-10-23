#!/bin/zsh
cd -- "$(dirname -- "$0")" || exit 1
if ! command -v node >/dev/null 2>&1; then
  print '需要 Node.js 20 或更新版本。安装后再打开此文件。'
  read 'reply?按回车关闭…'
  exit 1
fi
if curl -fsS http://127.0.0.1:4173/ >/dev/null 2>&1; then
  print '本地服务已经运行：http://localhost:4173/'
  open http://localhost:4173/
  exit 0
fi
print '游戏地址：http://localhost:4173/'
print '请保留本窗口；按 Control+C 可关闭服务。'
(sleep 1; open http://localhost:4173/) &
node server.mjs

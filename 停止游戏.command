#!/bin/zsh
# Only stop this project's Node server, never arbitrary listeners on the port.
cd -- "$(dirname -- "$0")" || exit 1
project_dir=$(pwd -P)
port=${METEOR_STOP_PORT:-4173}
if [[ ! "$port" =~ '^[0-9]+$' ]] || (( port < 1 || port > 65535 )); then
  print '端口号无效。'
  exit 1
fi

stopped=0
for pid in ${(f)"$(lsof -nP -t -a -u "$(id -un)" -c node -iTCP:"$port" -sTCP:LISTEN 2>/dev/null | sort -u)"}; do
  [[ "$pid" == <-> ]] || continue
  process_dir=$(lsof -a -p "$pid" -d cwd -Fn 2>/dev/null | sed -n 's/^n//p')
  [[ "$process_dir" == "$project_dir" ]] || continue
  command_line=$(ps -p "$pid" -o args= 2>/dev/null) || continue
  words=("${(z)command_line}")
  matched=0
  for arg in "${words[@]:1}"; do
    if [[ "$arg" == server.mjs || "$arg" == "$project_dir/server.mjs" || "$arg" == ./server.mjs ]]; then
      matched=1
      break
    fi
  done
  (( matched )) || continue
  if kill -TERM "$pid" 2>/dev/null; then
    print "已停止游戏服务（进程 $pid，端口 $port）。"
    (( stopped++ ))
  else
    print "无法停止游戏服务（进程 $pid）。"
  fi
done
if (( stopped == 0 )); then
  print "没有发现本项目正在运行的游戏服务（端口 $port）。"
fi
if [[ -t 0 ]]; then read 'reply?按回车关闭窗口…'; fi

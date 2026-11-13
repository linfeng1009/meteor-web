#!/bin/sh
set -eu
base=/var/www/meteor-web
stage=/tmp/meteor-ui-20261113
old=$(readlink "$base/current")
case "$old" in releases/*/dist) ;; *) echo 'Unexpected current release'; exit 1;; esac
[ "$(sha256sum "$base/current/index.html" | cut -d' ' -f1)" = 2a9d29ce0ef307d5f08cd19341a8c0fd5d8526f3b3cb0a2dbcdd26e7015d5bf1 ] || { echo 'Live index changed; abort'; exit 1; }
[ "$(sha256sum "$base/current/game-shell.css" | cut -d' ' -f1)" = 10e79e46aa370233fecbd3c1d9e01b1484ba3b3f9c1c9ed34d483490ab3894ba ] || { echo 'Live stylesheet changed; abort'; exit 1; }
[ "$(sha256sum "$stage/index.html" | cut -d' ' -f1)" = f4ad089578973d895bfbfab0f511ffd6021c463af45f82135b624469e15cf2bd ]
[ "$(sha256sum "$stage/game-shell.css" | cut -d' ' -f1)" = bc2f901c8f7b8589241d9542c38fb042af1d6d8028b46257a4b519ef147a3b91 ]
gzip -t "$stage/index.html.gz" "$stage/game-shell.css.gz"
[ "$(gzip -dc "$stage/index.html.gz" | sha256sum | cut -d' ' -f1)" = f4ad089578973d895bfbfab0f511ffd6021c463af45f82135b624469e15cf2bd ]
[ "$(gzip -dc "$stage/game-shell.css.gz" | sha256sum | cut -d' ' -f1)" = bc2f901c8f7b8589241d9542c38fb042af1d6d8028b46257a4b519ef147a3b91 ]
release="meteor-web-ui-$(date +%Y%m%d%H%M%S)"
mkdir -p "$base/releases/$release/dist"
cp -al "$base/current/." "$base/releases/$release/dist/"
for file in index.html index.html.gz game-shell.css game-shell.css.gz; do
  rm -f "$base/releases/$release/dist/$file"
  install -m 644 "$stage/$file" "$base/releases/$release/dist/$file"
done
ln -s "releases/$release/dist" "$base/current.next-ui"
mv -Tf "$base/current.next-ui" "$base/current"
printf 'previous=%s\ncurrent=%s\n' "$old" "releases/$release/dist"

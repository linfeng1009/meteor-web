# 人物显示名修正记录

2026-11-06。保留新显示名，并将文件路径与原始来源记录恢复为真实值。

| 外观 ID | 当前显示名 | 头像印章 | 原始文件名 |
| --- | --- | --- | --- |
| `hutao` | YS-胡桃 | 胡 | `胡桃喵1.0.pmx`、`胡桃喵-完整模型-流星动作适配.blend` |
| `raiden` | YS-影 | 影 | `礼服影.pmx`、`雷神影-礼服模型-流星动作适配.blend` |
| `emilia` | RE0-爱蜜莉雅 | 爱 | `Emilia_v1.pmx`、`爱蜜莉雅-完整模型-流星动作适配.blend` |

外观 ID、存档键、加载目录及网格/贴图文件名沿用原值。「礼服适配」的显示文案保持为「模型适配」。头像印章单独配置，不再从显示名称前缀截取。

Blender 构建、渲染和校验脚本继续使用磁盘上现有的原文件名；源 PMX 文件名、README 报告链接及来源说明同样按实际文件恢复。没有重新导出模型或重建动作。

原构建日志、审计 JSON 和原始输出恢复为改名前的记录。三套原始校验快照及其对应的原 manifest 字节保存于 [history/](history/)，以免用新名称改写历史构建事实：

- [胡桃历史校验](history/hutao/final-hashes.json)、[原 manifest](history/hutao/manifest.json)
- [影历史校验](history/raiden/final-hashes.json)、[原 manifest](history/raiden/manifest.json)
- [爱蜜莉雅历史校验](history/emilia/final-hashes.json)、[原 manifest](history/emilia/manifest.json)

各 `work/*-pmx-quality/final-hashes.json` 已重新计算当前文件哈希，注明本次仅更新显示元数据与路径，旧 Blender 骨架、渲染和动作验收结论见归档。模型网格及 `.blend` 的字节与历史哈希一致。

[repair-record.json](repair-record.json) 列出恢复的历史记录和修正路径的文件；[validation.json](validation.json) 保存本次检查结果。

胡桃 PMX 的原下载路径在替换前就已缺失，在 Downloads/Desktop 中按源模型文件名查找也未找到。脚本已恢复最后确认的原来源路径；重新从 PMX 转换需要先恢复源包。游戏使用已导出的 JSON/PNG，现有 Blender 文件也仍在，因此这项缺失不影响当前游戏外观加载。

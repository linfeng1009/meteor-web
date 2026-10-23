# 武器模型缺失与双持别名核对

原目录始终只读，本轮未下载远端二进制。

- `w8_0`：sn02 DES中D_wpBBox12的逻辑型号。RES道具4“峨嵋”真实型号W8_0r；本地w8_0r/l.GMC与DES均在，weapon-models清单也已导入。这是场景导入器未解析双持逻辑别名，不是原模型缺失。
- `w8_3`：sn10 DES中D_Wp06的逻辑型号，ticket=6。RES道具31“虎爪”真实型号W8_3r；本地w8_3r/l.GMC与DES均在，同样属于别名解析问题。
- 原EXE场景展示时只显示r件还是组合双件，本轮没有证明；宿主可组合实际源模型，但应说明该展示选择。
- `w6_5`：RES道具59“熱力輪”引用W6_5，本地cmodel中无同名模型，28个PAK的成员目录也无该名。本轮定向LXRES检索未找到能确认的独立原模型。

LXRES的[八个武器模型安装说明](https://d.lxres.com/RenWuWuQi/ZiZhiWuQi/397.html)明确双刺中庸/敏捷文件名为W8_0r/W8_3r；[多刺飞盘说明](https://www.lxres.com/RenWuWuQi/ZiZhiWuQi/1071.html)也列双刺r后缀。这两页用于命名交叉核验，没有下载或替代其社区自制模型。

可供后续核验的官方来源是[官方全版本](https://www.lxres.com/ZhuKeHuDuan/GuanFangYuanBan/31.html)（450.84 MB，页面另列各版补丁）及[1.08完整版](https://www.lxres.com/ZhuKeHuDuan/GuanFangYuanBan/639.html)（409.65 MB）。页面没有w6_5文件清单，不能声称其中必有该文件；依任务边界未下载完整客户端。

本地引用坐标、组件哈希、RES条目和查询词见 [E-missing-models-research.json](E-missing-models-research.json)。

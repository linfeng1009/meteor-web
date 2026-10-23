# 四方阵资源来源

资源核对日期：2026-10-22。

## 实际使用的地图和贴图

- 资源站：https://www.lxres.com/
- 资源页：[超清官方原味四方阵](https://www.lxres.com/DiTuXiaZai/YuanBanMeiHua/4798.html)
- 发布作者：唐家笑三少。
- 页面说明：保留官方地图，修理细节并替换材质。
- 原始下载：https://www.lxres.com/d/file/DiTuXiaZai/YuanBanMeiHua/2026-01-08/超清官方原味四方阵.rar
- 原地图模型及游戏：《流星蝴蝶剑.net》，昱泉国际 / Interserv。
- 下载包为 RAR，其中 `sn06.pak` 是标准 ZIP；本地仅解包数据文件，没有执行任何下载程序。
- 本目录 `sn06.gmb`、`sn06.des`、`sn06.cob` 来自该包；JPG 贴图被缩至不超过 1024px，文件名统一小写以适配 Web 服务器。
- 地图有 106 个物件、8,389 个顶点、6,530 个三角面。
- `gmc-loader.js` 直接在浏览器读取 GMB，保留原 UV、顶点色与材质分组；坐标从原生 Z 向上转换为 Three.js Y 向上。
- 地图文件中的顶点已经位于世界坐标，不能再次叠加 DES 的物件位置。

## 音乐

- 资源页：[流星蝴蝶剑原声背景音乐](https://www.lxres.com/YingYinLuXiang/YouXiYinYue/99.html)
- 页面署名：昱泉国际。
- `menu.mp3`：https://www.lxres.com/d/file/YingYinLuXiang/YouXiYinYue/2020-01-06/menu.mp3
- `s6.mp3`：https://www.lxres.com/d/file/YingYinLuXiang/YouXiYinYue/2020-01-06/s6.mp3

## 格式参考

- [地图 GMC 结构](https://www.lxres.com/LiuXingBiJi/1566.html)，漠之北。
- [地图 DES 结构](https://www.lxres.com/LiuXingBiJi/1569.html)。
- [武器安装说明](https://www.lxres.com/LiuXingBiJi/1759.html)：GMC / GMB、PAK 与 JPG / BMP / TGA / IFL。
- [武器招式表](https://www.lxres.com/LiuXingBiJi/1559.html)。
- [pose 动作资料表](https://www.lxres.com/LiuXingBiJi/1758.html)。

站点注明内容从网络收集，版权归原作者和出版社。这里保留来源与署名，下载开放不代表资源采用开源许可证；本地演示没有取得对外商业发行授权。

## 社区武器模型

- 资源页：[好贱（剑模型）](https://www.lxres.com/RenWuWuQi/ZiZhiWuQi/635.html)
- 作者：太阳依然和谐。
- 原始下载：https://www.lxres.com/d/file/资源/h.皮肤模型/好贱.7z
- `../weapons/qingfeng.gmc` 是包内 `w0_0.gmc` 的本地文件别名；没有修改原模型。配套纹理 `gjj01.jpg`。
- 2,718 顶点 / 5,470 面（其中 12 面是隐藏碰撞包围盒，渲染时排除）；由同一 loader 的 `loadGmc` 读取。

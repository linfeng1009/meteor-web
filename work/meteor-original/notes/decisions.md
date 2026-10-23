# 2026-10-22 原版移植决策

- 用户否定了此前的近似玩法原型，明确要求从本地Windows原版反编译移植，原版资源优先，资源站仅补缺失。
- 原型保留作接口验证；不可将程序角色/新战斗规则宣称为原版还原。
- PRIMARY R6 ida-reverse；刷新tool-index确认本机没有IDA。按技能下游使用Ghidra开源反编译，已调用manifest bootstrap，不假设商业许可证。
- EXE SHA256与导入表在 evidence/E-imports.json。它是PE32 x86，依赖Direct3D8、DirectInput、DirectSound与Win32，不是.NET；转换需将平台API重写到WebGL/WebAudio/浏览器输入。
- 各原格式解析与原规则参数须保留证据，推断项不可伪装为原EXE验证。

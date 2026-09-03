# Snack 项目日志

> 本文件是"跨设备共享记忆"：每台电脑/每个账户开工前先读它，收工后更新它，然后提交推送到 GitHub。

## 一句话简介
控制台贪吃蛇（C++ / STL，VS 工程 Snack.sln + VSCode MinGW 双构建，简历向项目）。Snack 类 7 方法实现 + 键盘操控 demo（WASD + 方向键）已在双机实机验收通过、中文输出正常；控制台完整版（地图/食物/碰撞/计分）未开始。

## 协作约定
- VS2022 主力机 + 另一台电脑（VSCode）经 GitHub 协作，远程已统一为 HTTPS（22 端口被墙，SSH 不可用，勿折腾）。
- 仓库为 **public**：新电脑 clone/pull 免登录；push 需 GitHub 凭据（Windows Git Credential Manager 浏览器授权一次，或 PAT）。
- 所有代码改动由本人亲自完成，AI 助手只负责：读代码、指出问题、解释原理、给手把手的改法。一次只给一个任务。
- 调试以实际运行为准，不盲信任何"口头诊断"。
- AI 只读 Snack 相关文件，不碰工作区里其他项目。
- 源文件编码统一 UTF-8（g++ 用 -finput/-fexec-charset=UTF-8；MSVC 用 /utf-8），中文注释/输出安全。**MSVC 侧 /utf-8 已于主力机配置（2026-09-03，Debug 需确认 Release 同配）**
- **本文件 PROJECT_NOTES.md 固定维护在仓库根目录**（就是它现在所在的位置，和 Snack.sln 同级的是工程子目录，别放进去）——用户明确选定的位置，Anime_Archive_Z 多套一层属失误。

## 当前状态（今天更新）
### 已完成
- [x] 仓库建立并推送 GitHub（HTTPS 正常）
- [x] Point.h / Point.cpp：Point 实现完成（默认参数构造 + operator==），正确
- [x] Snack.h：类骨架定稿并实现——std::deque<Point> 蛇身 + Direction 方向 + 成长标志，7 个方法全部实现
- [x] 方向升级为 `enum class Direction`（顶层枚举，Anime_Archive_Z 同款风格）：Up=0 Right=1 Down=2 Left=3，与旧 int 约定数值一致，右转 90°=(值+1)%4
- [x] Snack.cpp 六方法实现并自测通过（输出逐行核对）：构造（初始 1 节、Up、不成长）/ isHeadAt / getBody / getDirection / move（弹尾+插头）/ grow（打标记，move 里消化）
- [x] setDirection 加入（7 个方法）：长度 >1 时禁止 180° 掉头；长度 =1 允许（头尾同格无自撞风险）
- [x] VSCode 构建环境就位：.vscode 配置从 Anime_Archive_Z 复制改造（tasks/launch 输出名改 Snack.exe；MinGW g++ 16.1 实测可用）；编译、F5 调试流程跑通
- [x] 控制台中文显示方案：main 开头 `SetConsoleOutputCP(CP_UTF8)` + `SetConsoleCP(CP_UTF8)`（Anime 同款），本机实测中文正常
- [x] 键盘 demo main 替换完成：conio.h `_getch()` 无回车读键 + WASD 映射，编译通过
- [x] **setDirection fallthrough bug 已修**（Snack.cpp 各 case 已补 break，代码核对确认）
- [x] **main.cpp 方向键 bug 已修**（`ch == 0 || ch == 224` 前缀判断 + `ch = _getch()` 赋值，代码核对确认）
- [x] **键盘 demo 主力机实机验收通过（2026-09-03）**：WASD + 方向键均能控蛇、长度>1 时 180° 掉头被正确拒绝、Q 退出正常
- [x] **MSVC 中文乱码修复**：Snack.vcxproj 配置 /utf-8 后 F5 输出中文正常（SetConsoleOutputCP 只解决运行期，编译期编码靠 /utf-8）

### 待办（下次严格按此顺序）
- [ ] **确认 Release 配置也加了 /utf-8**（Debug 已配，主力机 MSVC 中文正常；Release 没配的话以后编译中文会复发）
- [ ] 控制台完整版：地图渲染（二维格子、行=y 列=x）→ 食物生成（随机、不与蛇身重叠）→ 自动移动（延时循环）→ 键盘方向（复用 demo 读取）→ 碰撞判定（撞墙/咬自己 → 结束）→ 计分（吃一个 +1）
- [ ] 工程化：编码统一 → 日志 → CMake → 单元测试（把当年删掉的 main 自测正式化）→ README（参考 Anime_Archive_Z 已验证流程）
- [ ] 可选加分：SFML 图形版（游戏循环/事件/碰撞/存档）

## 关键决定记录
- 远程用 HTTPS：22 端口被墙，SSH 不可用
- 仓库公开：另一台电脑免登录拉取；推送需凭据
- 蛇身用 std::deque<Point>：头在 front、尾在 back，move 的天然结构是"弹尾 + 插头"（push_front/pop_back 均 O(1)）
- 方向用 `enum class Direction`（Anime 同款顶层风格），消灭魔法数字；显式写 =0/1/2/3 保序防插项
- 成长标志 m_isGrow：先标记再在 move 里消化（grow 只置位，move 见标志则不弹尾并复位）
- setDirection 掉头规则：长度 >1 禁止 180°；长度 =1 放行（头尾同格无自撞风险）
- 键盘输入用 conio.h 的 `_getch()`（MinGW/MSVC 都有，无回车；cin 做不到实时游戏）
- Windows 方向键是两字节：`_getch()` 先返回 0 或 224，再返回扫描码 72↑ 75← 77→ 80↓
- 控制台坐标系：y 是行（向下增）、x 是列；"上"= y-1
- 踩坑库共享兄弟项目 Anime_Archive_Z（见下节），遇到类似问题直接引用

## 踩坑库（共享自 Anime_Archive_Z，教科书级，反复看）
1. C++11 起：数值提取失败时，目标变量被写成 0（int/float 都是，不是保持不变）
2. do-while 里 `continue` 跳到条件求值，不是循环体开头
3. Windows 上 std::rename 不覆盖已存在的目标文件
4. MSVC 对无 BOM 源码默认按系统编码（GBK）读 → 中文乱码，用 /utf-8 统一
5. `cin >> int` 只吃数字前缀："0abc" 会解析成 0——要"整行合法"必须读整行再完整校验
6. 改了代码没 Ctrl+S，磁盘上还是旧文件——排查"改了没反应"前先检查保存
7. 浏览器能上 GitHub ≠ git 能上：浏览器走代理/加速，git 直连可能超时
8. **switch 里 case 分支忘写 break → 悄悄 fallthrough 到下一个 case**，逻辑错得无声无息（本次 setDirection 中招：只拦了不该拦的）
9. **想赋值却写成比较**：`ch == _getch()` 读走了键但没存 → 方向键全部"没反应"（本次 main.cpp 中招）
10. **头文件声明了方法、.cpp 忘了写定义** → 编译全过、链接报 `undefined reference to Snack::xxx()`（grow() 那次"调试失败"真凶）
11. Windows 控制台默认代码页 GBK：exe 里 UTF-8 中文输出会乱码，程序开头 SetConsoleOutputCP(CP_UTF8) 解决

## 常用命令备忘
- 结束一天：更新本文件 → git add -A → git commit -m "docs: 更新项目日志" → git push
- 新电脑首次拉取：git clone https://github.com/yanluxiaocen/Snack.git
- 每日开工：git pull 拿到最新进度，先读 PROJECT_NOTES.md
- VSCode 机编译/调试：打开仓库根目录，活动文件切到某个 .cpp，F5（tasks 会编译该目录下所有 .cpp 成 Snack.exe）

# Snack 项目日志

> 本文件是"跨设备共享记忆"：每台电脑/每个账户开工前先读它，收工后更新它，然后提交推送到 GitHub。

## 一句话简介
控制台贪吃蛇（C++ / STL，VS 工程 Snack.sln + VSCode MinGW 双构建，简历向项目）。Snack 类 7 方法实现 + 键盘操控 demo（WASD + 方向键）已在双机实机验收通过、中文输出正常；控制台完整版进行中：地图渲染 + 自动移动 + 撞墙已完成（UI 已拆分为 UI.h/UI.cpp），食物/计分/自撞未做。

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
- [x] **UI 职责拆分**（本机编译通过、exe 已构建）：draw() 移入新建 UI.h/UI.cpp（含 constexpr PLAY_WIDTH=20 / PLAY_HEIGHT=10 尺寸常量，main 共享），main.cpp 只留游戏循环 main
- [x] **控制台雏形第一块**（本机编译通过、exe 已构建）：地图边框渲染（grid 二维缓冲 + 三元运算符画边框 #、蛇身 o / 蛇头 @）+ 自动移动循环（_kbhit() 轮询不阻塞 + Sleep 150ms 帧间隔）+ 撞墙 Game Over（头出活动区即死，防 grid 越界写）
- [x] **主力机交接完成（2026-09-07）**：git pull 拿到 UI 拆分代码；Snack.vcxproj 已添加 UI.cpp / UI.h；F5 实测正常（蛇自动移动、WASD/方向键转向、撞墙退出）——两机行为一致

### 待办（下次严格按此顺序）
- [ ] 食物 + 计分：随机生成不压蛇身的食物（画在 grid 上）→ 头吃到食物 → grow() + 分数 +1 → 生成新食物（计划在 VSCode 机做）
- [ ] 自撞判定 + 重开：新头咬到身体即 Game Over（长度>1 时即将移走的尾格不算撞）→ 结束后按 R 再来一局
- [ ] 工程化：编码统一 → 日志 → CMake → 单元测试（把当年删掉的 main 自测正式化）→ README（参考 Anime_Archive_Z 已验证流程）
- [ ] 可选加分：SFML 图形版（游戏循环/事件/碰撞/存档）
- [ ] （主力机小尾巴）确认 Release 配置也加了 /utf-8——Debug 已配并实测正常，Release 当时没确认

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
- UI 拆分为 UI.h/UI.cpp：draw() 只管画（grid 二维缓冲 + system("cls") 整帧重绘），main 只管循环/输入/规则；constexpr 尺寸常量放 UI.h 由两文件共享（头文件里的 constexpr 每个 .cpp 独立拷贝，无重复定义问题）
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
- push/pull 前先开 Steam++ 加速（Anime 双机经验：浏览器能开 GitHub ≠ git 能连）；2026-09-04 本机 fetch 实测报 schannel SEC_E_NO_CREDENTIALS，若开加速仍报错 → 查 GCM 凭据/PAT
- 新电脑首次拉取：git clone https://github.com/yanluxiaocen/Snack.git
- 每日开工：git pull 拿到最新进度，先读 PROJECT_NOTES.md
- VSCode 机编译/调试：打开仓库根目录，活动文件切到某个 .cpp，F5（tasks 会编译该目录下所有 .cpp 成 Snack.exe）

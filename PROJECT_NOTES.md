# Snack 项目日志

> 本文件是"跨设备共享记忆"：每台电脑/每个账户开工前先读它，收工后更新它，然后提交推送到 GitHub。

## 一句话简介
控制台贪吃蛇（C++ / STL，**CMake 双机构建**，简历向项目）。游戏规则已闭环（自动移动/转向/成长/撞墙/自撞/计分/R 重开）+ 手感优化完成；**工程化四件套齐活**：目录拍平（src/include）→ sln 退役 → CMake 管线 → doctest 单测（11 用例 / 16 断言全绿）→ README。**图形版（SFML）路线待定**，见待办决策项。

## 协作约定
- VS2022 主力机 + 另一台电脑（VSCode）经 GitHub 协作，远程已统一为 HTTPS（22 端口被墙，SSH 不可用，勿折腾）。
- 仓库为 **public**：新电脑 clone/pull 免登录；push 需 GitHub 凭据（Windows Git Credential Manager 浏览器授权一次，或 PAT）。
- 所有代码改动由本人亲自完成，AI 助手只负责：读代码、指出问题、解释原理、给手把手的改法。一次只给一个任务。
- 调试以实际运行为准，不盲信任何"口头诊断"。
- AI 只读 Snack 相关文件，不碰工作区里其他项目。
- 源文件编码统一 UTF-8（g++ 用 -finput/-fexec-charset=UTF-8；MSVC 用 /utf-8），中文注释/输出安全。**MSVC 侧 /utf-8 已于主力机配置（2026-09-03，Debug 需确认 Release 同配）**
- **本文件 PROJECT_NOTES.md 固定维护在仓库根目录**（与 src/ include/ CMakeLists.txt 同级）——用户明确选定的位置，Anime_Archive_Z 多套一层属失误。

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
- [x] **食物 + 计分完成（2026-09-08，VSCode 机）**：随机食物不压蛇身（do-while 重抽 + isOnSnake 过滤）；吃到 → grow() 标记 + 分数 +1 + 换新食物；draw 签名改为 (snake, food, score) 三处同步；撞墙显示最终得分。实机体验正常，顺带验证了长度>1 后 180° 掉头保护
- [x] **手感三件套（2026-09-09）**：① draw 改光标回位覆盖画（SetConsoleCursorPosition 回 0,0）替代 system("cls")，不清屏不闪；② 活动区放大 PLAY_WIDTH 20→32、PLAY_HEIGHT 10→16；③ 输入改 do-while 清空排队键、每帧只认最后一次按键。实测：屏闪好转、场地舒服、转向精准
- [x] **自撞判定 + R 重开（2026-09-09）**：move 后查头 vs body[1..]（跳过第 0 节=头自己；尾格因"先 move 后判定"时序天然不误报）；外层局循环 + 内层本局循环，结束按 R 重开 / Q 退出。**游戏规则闭环**
- [x] **目录拍平 + 退役 sln（2026-09-09）**：git mv 源码 → src/、头文件 → include/（tests/ 预建）；删除 Snack.sln / .vcxproj / .filters
- [x] **CMake 接入（2026-09-09）**：CMakeLists.txt 本人手写（C++17 + 按编译器分编码参数：MSVC /utf-8、g++ -finput/-fexec-charset=UTF-8）；CMake 4.4.3 绿色版装 D:\Tool\CMake（winget 本机损坏、无外网直连，浏览器校园网下载）；cmake -G "MinGW Makefiles" 配置+构建 → build\Snack.exe 跑通（mingw64 不在 PATH → 显式 -DCMAKE_CXX_COMPILER/-DCMAKE_MAKE_PROGRAM）；F5 已接线（tasks 换 CMake 构建/首次配置，launch 指向 build\Snack.exe，任意文件可 F5）
- [x] **本机整体验收（2026-09-09）**：CMake 产物运行正常、F5 调试流程正常
- [x] **doctest 单元测试接入（2026-09-10）**：doctest.h 2.4.11 从 Anime tests/ 拷入（本地复制）；tests/test_main.cpp（DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 入口）+ test_point.cpp（3 用例）+ test_snack.cpp（8 用例：初始状态 / 四方向 move / grow 只打标记时序 / 长度>1 反向被拒 / 90° 允许）；CMakeLists 加 enable_testing + unit_tests target（tests + src/Point.cpp + src/Snack.cpp，**不含 main.cpp / UI.cpp**）+ add_test；编码参数抽成 SNACK_UTF8_FLAGS 变量供两 target 复用
- [x] **单测全绿（2026-09-10）**：11 用例 / 16 断言全部通过，ctest --test-dir build 1/1 Passed（首轮跑就绿）
- [x] **cmake/ctest 加入用户 PATH（2026-09-10）**：D:\Tool\CMake\...\bin，命令行可直接调用；**mingw64 故意不加 PATH**（避免工具链打架，CMake 配置里已显式指定编译器路径）
- [x] **README 完成（2026-09-10）**：8 板块（简介/功能/ASCII 画面示意/操作表/技术栈/构建运行/项目结构/后续计划），棋盘示意图 34 字符精确对齐；ASCII 示意可后续换真截图。**工程化四件套（目录/CMake/单测/README）就此收官**

### 待办（下次严格按此顺序）
- [ ] **提交推送 README**（唯一未提交项）；本机校园网连不上 GitHub → 开 Steam++ 或到主力机推（上午的单测提交 377f5e0 同样待推送确认）
- [ ] **主力机交接**：pull 后别开 .sln（已退役），VS"打开文件夹"→ CMake（MSVC kit）；跑一次单测确认同样 11 用例 / 16 断言全绿
- [ ] **待决策：图形版（SFML）还是结项换项目**——先别写代码，二选一后开工：
  - 路线①：**1 小时低成本试水**——主力机只验证"SFML 空窗口能编能跑"，不通过就停（项目已完整，零损失）
  - 路线②：直接结项，转下一个项目
  - 关键风险：**SFML 官方无 GCC 16 预编译包**，本机 MinGW 机 ABI 风险高 → 若做，走主力机 MSVC + 官方 VS2022 二进制最稳
  - 备选玩法（结合 PAT 算法学习）：给现有项目加 **BFS 自动寻路 AI 模式**（机器自己找最短路径吃食物）
- [ ] 可选小项：补"长度 1 时反向放行"用例（setDirection 规则第三分支）；GitHub Actions CI（ctest + README 徽章）；rand 换 `<random>`；读键封装成函数；真截图替换 ASCII 示意图

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
- UI 拆分为 UI.h/UI.cpp：draw() 只管画（grid 二维缓冲 + 整帧重绘），main 只管循环/输入/规则；constexpr 尺寸常量放 UI.h 由两文件共享（头文件里的 constexpr 每个 .cpp 独立拷贝，无重复定义问题）
- 工程构建从 sln/vcxproj 切换到 **CMake**（退役 sln）：两机共用同一份 CMakeLists.txt；主力机 VS"打开文件夹"模式 + MSVC，VSCode 机命令行/cmake-tools + MinGW；编码参数按编译器分支（if(MSVC) /utf-8 else() -finput/-fexec-charset=UTF-8）
- mingw64 与 cmake 都不在 PATH → cmake 配置显式传 -DCMAKE_CXX_COMPILER / -DCMAKE_MAKE_PROGRAM（Anime 坑 #14 同款：工具不在 PATH）
- .vscode 配置含本机绝对路径（D:\Tool\CMake、D:\Tool\VSCode\mingw64），主力机不用 .vscode，无冲突
- build/ 产物目录 gitignore；Snack.exe 不再生成在源码目录
- 单元测试用 **doctest**（单头文件、Anime 同款已验证）：unit_tests 是独立可执行文件，**只编被测源文件（src/Point.cpp + src/Snack.cpp）**，绝不含 src/main.cpp（main 冲突）与 UI.cpp（测试不画图）
- 编码参数抽成 `SNACK_UTF8_FLAGS` 变量（set + ${} 取值），Snack 与 unit_tests 两个 target 复用同一份定义
- cmake/ctest 加入用户 PATH；mingw64 不加 PATH（编译器路径在 CMake 配置时显式传，避免全局工具链冲突）
- **图形版路线未定（2026-09-10 讨论）**：做 SFML 只需改"显示 + 输入"层——Snack / Point / 11 个单测**一行都不用动**（分层设计的回报）；但 SFML 官方无 GCC 16 预编译包，本机 MinGW 有 ABI 风险 → 若做，优先主力机 MSVC + 官方 VS2022 二进制；决策方式 = 先花 1 小时只验"空窗口能编能跑"，不通过就停（项目已完整，零损失）
- **不做"算法可视化"类展示型项目**（2026-09-10）：用户的算法目标是 PAT / 竞赛，纯展示型项目对目标无收益；若要结合算法，优先在现有项目内加 **BFS 自动寻路 AI 模式**（备选，未决）
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
12. PowerShell Get-Content 默认按 GBK 读 UTF-8 无 BOM 文件 → 校验 JSON 假报错（"Unterminated string"），加 -Encoding UTF8（Anime 坑 #10 本机复现）
13. CMake 命令拼写：`cmake_minimum_require` 少个 d → `Unknown CMake command`（CMake 头号拼写坑）；CMake 4.x 还强制最低版本 ≥3.5
14. 抄 CMakeLists 忘改 target 名（把 Anime_Archive_Z 抄进 Snack）→ target_compile_options 指向不存在的 target 报错
15. build 目录 CMakeCache.txt 丢失 → cmake --build 报 "not a CMake build directory" → 重跑一次配置即可
16. winget 在本机损坏（命令返回负数退出码、--version 也无输出）→ 备用方案：浏览器直接下绿色版解压（不用装系统）
17. **`enum class` 不能从 int 构造**：`Direction(0)` 编译错，必须写 `Direction::Up`（强类型的代价，也是它的价值——魔法数字写不进来）
18. **容器对象不能和 int 比较**：`s.getBody() == 1` 编译错，要比长度得 `.size()`（返回的是 deque 本身，不是个数）
19. **C++17 里 `x != y` 需要显式 `operator!=`**（"有 == 就自动有 !="是 C++20 特性）→ 测试里写 `CHECK_FALSE(x == y)`；原则：测试适应接口，别为测试改接口
20. **CMake 文件名拼错** → `Cannot find source file: tests/tests_main.cpp`（本次多打一个 s）；报这类错先核对文件名与目录
21. **CMake 未定义变量 `${XXX}` 静默展开为空** → target 少配置且不报错（本次 SNACK_UTF8_FLAGS 忘了 set，unit_tests 就漏了编码参数）；写 `${}` 前先确认对应 `set()` 存在
22. **单元测试 target 混入含 main() 的源文件** → 重复定义 main、链接失败（doctest 自己提供 main）
23. **PowerShell 终端显示中文乱码** → `[Console]::OutputEncoding = [System.Text.Encoding]::UTF8`（注意与 #11 区分：#11 是程序内输出编码，这条是终端显示编码）

## 知识点地图（2026-09-08 小结，供复习/面试用，详细版在当天聊天里）
**C++ 语言**：constexpr（类型化编译期常量，不用 #define——宏无类型/无作用域/不可调试）；enum class（作用域+强类型，打印用 static_cast）；声明 vs 定义（链接错误 undefined reference）；运算符重载 operator==；初始化列表按声明顺序；const 成员函数；const& 返回防拷贝（getBody）
**STL**：std::deque 双端队列（front/back、push_front/pop_back 均 O(1)，选它因为蛇"头进尾出"）；范围 for 引用遍历；**引用失效规则**（move() 先拷贝 head 再动容器：pop 可能弹掉引用指向的元素、push_front 可能重分配）
**语法细节**：switch 每个 case 要 break（fallthrough 静默错）；三元运算符 ?:（是表达式不是 lambda）；do-while 先做后查（生成食物"先抽再查"）；= 赋值 vs == 比较
**Windows 控制台**：_getch 无回车读键；_kbhit 非阻塞轮询（实时游戏必须用）；方向键两字节（0/224 前缀 + 72↑ 75← 77→ 80↓）；Sleep 毫秒延时；system("cls") 清屏；SetConsoleOutputCP(CP_UTF8) 解决中文乱码
**随机数**：rand 伪随机（LCG 确定性序列）→ srand(time(nullptr)) 播种；rand()%N+1 压范围（有微小取模偏差）；工程化换 <random>（mt19937 + uniform_int_distribution）
**设计思想**：游戏主循环骨架（输入→更新→渲染→延时，所有游戏通用）；状态与显示分离（分数/食物在 main，UI 只读画）；成长标志"先标记、move 里消化"；规则按游戏状态分级（长度1 可掉头 / >1 禁止）；生成合法性过滤（食物不压蛇身）；增量开发每步有验收
**测试与构建（2026-09-10 补充）**：doctest 三件套（`TEST_CASE` / `CHECK` / `CHECK_FALSE`，`REQUIRE` 失败即中止）；AAA 三段式（准备→动作→断言）与"用例互相独立"原则；doctest 参数 `--success` / `-tc="名字"` / `--list-test-cases`；ctest 批量 `--test-dir build --output-on-failure`；CMake `enable_testing` / `add_test` / `set` 变量 + `${}` 复用；单元测试 target 只编被测源文件（不含 main）

## 常用命令备忘
- 结束一天：更新本文件 → git add -A → git commit -m "docs: 更新项目日志" → git push
- push/pull 前先开 Steam++ 加速（Anime 双机经验：浏览器能开 GitHub ≠ git 能连）；2026-09-04 本机 fetch 实测报 schannel SEC_E_NO_CREDENTIALS，若开加速仍报错 → 查 GCM 凭据/PAT
- 新电脑首次拉取：git clone https://github.com/yanluxiaocen/Snack.git
- 每日开工：git pull 拿到最新进度，先读 PROJECT_NOTES.md
- VSCode 机编译/调试：**F5** = `CMake: 构建` 任务 + 启动 build\Snack.exe（任意文件上 F5 均可）；新机器/删了 build 目录先跑任务 `CMake: 首次配置`
- VSCode 机手动构建：cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=D:/Tool/VSCode/mingw64/bin/g++.exe -DCMAKE_MAKE_PROGRAM=D:/Tool/VSCode/mingw64/bin/mingw32-make.exe，然后 cmake --build build（cmake/ctest 已于 2026-09-10 加入用户 PATH，可直接敲）
- 跑单测（详细输出，日常）：`.\build\unit_tests.exe`（可加 --success 看通过项、-tc="Snack：grow*" 只跑匹配用例、--list-test-cases 列用例）
- 跑单测（批量/CI 用）：`ctest --test-dir build --output-on-failure`
- 终端看中文测试名先敲：`[Console]::OutputEncoding = [System.Text.Encoding]::UTF8`

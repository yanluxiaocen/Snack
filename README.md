# Snack · 控制台贪吃蛇

一款由 **C++17** 编写的控制台贪吃蛇小游戏：STL `deque` 承载蛇身、键盘实时操控、食物计分、撞墙与自撞判定、死亡后一键重开；使用 **CMake** 构建（MSVC / MinGW 双编译器验证通过），**doctest** 单元测试全绿。

## ✨ 功能

- ⌨️ **实时操控**：WASD / 方向键转向，无需按回车（`_kbhit` 非阻塞轮询）
- 🐍 **自动移动**：150ms 一帧，蛇身"头进尾出"（`deque` 两端插入删除均为 O(1)）
- 🍎 **食物与计分**：随机生成且不压蛇身，吃到身体变长、分数 +1
- 💀 **碰撞判定**：撞墙或咬到自己即 Game Over，并显示最终得分
- 🔁 **重开**：死亡后按 R 再来一局，Q 随时退出
- 🎯 **手感细节**：光标回位覆盖重绘（不闪屏）、按键防排队（每帧只认最后一次操作）、长度 >1 时禁止 180° 掉头

## 📸 画面示意

```text
分数：3   WASD/方向键 转向 · Q 退出
##################################
#                                #
#                                #
#                    ooo         #
#                    o@*         #
#                                #
#                                #
#                                #
##################################
```

（`@` 蛇头 · `o` 蛇身 · `*` 食物 · `#` 墙）

## 🎮 操作

| 按键 | 作用 |
|------|------|
| `W` / `↑` | 向上 |
| `S` / `↓` | 向下 |
| `A` / `←` | 向左 |
| `D` / `→` | 向右 |
| `Q` | 退出游戏 |
| `R` | 死亡后重开一局 |

## 🛠 技术栈

- **语言**：C++17
- **构建**：CMake ≥ 3.20（MSVC 与 MinGW 双编译器验证通过）
- **测试**：doctest 单头文件框架（11 用例 / 16 断言，接入 ctest）
- **STL**：`deque`（蛇身：头在 front、尾在 back）、范围 for 引用遍历
- **Windows 控制台 API**：`_kbhit` / `_getch` 非阻塞读键、`SetConsoleCursorPosition` 覆盖重绘、`SetConsoleOutputCP(CP_UTF8)` 中文输出
- **工程实践**：`enum class Direction` 消灭魔法数字；成长标志"先标记、move 里消化"避免同帧竞争；UI 与游戏逻辑分层（UI 只读状态）；UTF-8 源码统一

## 🔨 构建与运行

**环境**：CMake ≥ 3.20 + 支持 C++17 的编译器

```bash
cmake -S . -B build
cmake --build build
```

运行与测试（产物路径随生成器不同）：

```bash
./build/Snack.exe          # MinGW 单配置生成器
./build/Debug/Snack.exe    # MSVC / Visual Studio 多配置生成器
./build/unit_tests.exe     # 运行单元测试
ctest --test-dir build --output-on-failure   # 或用 ctest 批量运行
```

## 📁 项目结构

```text
├── src/               # main.cpp / Point.cpp / Snack.cpp / UI.cpp
├── include/           # Point.h / Snack.h / UI.h
├── tests/             # test_main.cpp / test_point.cpp / test_snack.cpp + doctest.h
├── CMakeLists.txt
└── PROJECT_NOTES.md   # 开发日志：决策记录与踩坑库
```

`build/` 为构建产物，不纳入版本控制。

## 🗺 后续计划

- SFML 图形版（窗口渲染 / 事件循环 / 存档）
- GitHub Actions CI（push 自动构建 + ctest）

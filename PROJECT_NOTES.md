# Snack 项目日志

> 本文件是"跨设备共享记忆"：每台电脑/每个账户开工前先读它，收工后更新它，然后提交推送到 GitHub。

## 一句话简介
控制台贪吃蛇（C++ / STL，VS 工程 Snack.sln，简历向项目），处于"类设计定稿、实现未动"的早期阶段；控制台版跑通后可升级 SFML 图形版。

## 协作约定
- VS2022 主力机 + 另一台电脑（VSCode）经 GitHub 协作，远程已统一为 HTTPS（22 端口被墙，SSH 不可用，勿折腾）。
- 仓库为 **public**：新电脑 clone/pull 免登录；push 需 GitHub 凭据（Windows Git Credential Manager 浏览器授权一次，或 PAT）。
- 所有代码改动由本人亲自完成，AI 助手只负责：读代码、指出问题、解释原理、给手把手的改法。一次只给一个任务。
- 调试以实际运行为准，不盲信任何"口头诊断"。
- AI 只读 Snack 相关文件，不碰工作区里其他项目。
- 源文件编码最终统一 UTF-8（/utf-8），注释出现中文前暂无乱码风险，注意保持。

## 当前状态（今天更新）
### 已完成
- [x] 仓库建立并推送 GitHub（HTTPS 正常）
- [x] Point.h / Point.cpp：Point 实现完成（默认参数构造 + operator==），正确
- [x] Snack.h：类骨架定稿——std::deque<Point> 蛇身 + int 方向 + 成长标志，声明 6 个方法
- [x] 方向约定定下：m_direction，0=上 1=右 2=下 3=左（顺时针，工程化阶段升级 enum class）

### 待办（下次按顺序）
- [ ] **提交推送 Snack.h**：本地有未提交改动，远端最新提交（e8e2beb "3"）里还是空壳
- [ ] 实现 Snack.cpp 前四个方法：构造函数（初始 1 节、m_direction=0、m_isGrow=false）+ isHeadAt / getBody / getDirection
- [ ] 实现 move() / grow()
- [ ] 控制台完整版：地图/食物/键盘方向/碰撞判定/计分
- [ ] 工程化：编码统一 → 日志 → CMake → 单元测试 → README（参考 Anime_Archive_Z 已验证流程）
- [ ] 可选加分：SFML 图形版（游戏循环/事件/碰撞/存档）

## 关键决定记录
- 远程用 HTTPS：22 端口被墙，SSH 不可用
- 仓库公开：另一台电脑免登录拉取；推送需凭据
- 蛇身用 std::deque<Point>：头在 front、尾在 back，move 的天然结构是"弹尾 + 插头"
- 方向暂用 int + 约定注释，工程化时换 enum class（消灭魔法数字）
- 成长标志 m_isGrow：先标记再在 move 里消化，避免"吃食物瞬间和移动抢同一帧"
- 踩坑库共享兄弟项目 Anime_Archive_Z（见下节），遇到类似问题直接引用

## 踩坑库（共享自 Anime_Archive_Z，教科书级，反复看）
1. C++11 起：数值提取失败时，目标变量被写成 0（int/float 都是，不是保持不变）
2. do-while 里 `continue` 跳到条件求值，不是循环体开头
3. Windows 上 std::rename 不覆盖已存在的目标文件
4. MSVC 对无 BOM 源码默认按系统编码（GBK）读 → 中文乱码，用 /utf-8 统一
5. `cin >> int` 只吃数字前缀："0abc" 会解析成 0——要"整行合法"必须读整行再完整校验
6. 改了代码没 Ctrl+S，磁盘上还是旧文件——排查"改了没反应"前先检查保存
7. 浏览器能上 GitHub ≠ git 能上：浏览器走代理/加速，git 直连可能超时

## 常用命令备忘
- 结束一天：更新本文件 → git add -A → git commit -m "docs: 更新项目日志" → git push
- 新电脑首次拉取：git clone https://github.com/yanluxiaocen/Snack.git
- 每日开工：git pull 拿到最新进度，先读 PROJECT_NOTES.md

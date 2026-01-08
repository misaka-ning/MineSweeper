# MineSweeper (Qt 扫雷游戏)

一个基于 **C++** 和 **Qt 框架** 实现的经典扫雷游戏复刻，致敬微软原版。

## 📋 项目概述

本项目是一个使用现代 C++ 与 Qt 图形界面库开发的扫雷游戏。它完美复刻了经典 Windows 扫雷的玩法与界面，提供了熟悉的游戏体验，并具备清晰的代码结构，适合学习 Qt 图形编程与游戏逻辑设计。

## 🛠️ 运行要求

在编译和运行本项目前，请确保您的开发环境已满足以下条件：
*   **C++编译器**：支持 C++11 或以上版本的编译器（如 GCC, Clang, MSVC）。
*   **Qt 开发框架**：需要安装 **Qt 5** 或 **Qt 6** 库及相应的开发工具。
*   **CMake** (推荐)：用于构建项目。或使用 **qmake**，具体取决于项目配置。
*   **Git**：用于克隆代码仓库。

## ⚙️ 安装与构建

请按照以下步骤在本地构建并运行游戏：

### 1. 克隆仓库
```bash
git clone https://github.com/misaka-ning/MineSweeper.git
cd MineSweeper
```

### 2. 使用 CMake 构建 (示例)
```bash
# 创建一个构建目录
mkdir build
cd build

# 生成构建文件 (请将路径替换为您的 Qt 安装路径)
cmake .. -DCMAKE_PREFIX_PATH="您的Qt安装路径/lib/cmake"

# 编译项目
make  # 在Windows的MinGW中使用 mingw32-make， 在MSVC中使用 cmake --build .
```

### 3. 运行游戏
编译完成后，在 `build` 目录或生成的可执行文件目录中找到 `MineSweeper` (或 `MineSweeper.exe`) 并运行。

*(如果项目使用 `qmake` 管理，则使用 `qmake ../MineSweeper.pro` 和 `make` 命令进行构建。)*

## 🎮 使用方法

1.  **启动游戏**：运行程序后，将出现游戏主界面。
2.  **开始游戏**：
    *   **左键点击**：揭开方块。
    *   **右键点击**：标记地雷（插上小旗）或标记疑问。
    *   **点击笑脸**：重新开始当前难度的游戏。
3.  **选择难度**：通常通过菜单或按钮可以选择 **初级**、**中级**、**高级** 或自定义难度。

## ✨ 功能特性

*   **经典玩法复刻**：完全还原 Windows 经典扫雷的核心规则与交互。
*   **多难度支持**：提供初级（9x9）、中级（16x16）、高级（16x30）等标准模式。
*   **直观的界面**：基于 Qt 实现的图形界面，包含计时器、地雷计数器和重置按钮。
*   **高效的逻辑**：使用 C++ 编写的高效游戏核心算法。
*   **跨平台**：基于 Qt 框架，理论上支持 Windows、Linux 和 macOS。

## 🤝 如何贡献

我们欢迎任何形式的贡献，包括修复 Bug、改进功能或优化文档。

1.  **Fork 本仓库**。
2.  创建您的功能分支 (`git checkout -b feature/AmazingFeature`)。
3.  提交您的更改 (`git commit -m 'Add: Some AmazingFeature'`)。
4.  推送到分支 (`git push origin feature/AmazingFeature`)。
5.  开启一个 **Pull Request**。

请确保您的代码风格与项目现有代码保持一致。

## 📄 许可证

本项目采用 **MIT 许可证**。详情请参阅 [LICENSE](LICENSE) 文件。

## 📬 联系与反馈

*   **项目维护者**：misaka-ning
*   **项目主页**：[https://github.com/misaka-ning/MineSweeper](https://github.com/misaka-ning/MineSweeper)
*   如果您有任何问题、建议或发现了 Bug，欢迎在项目的 [Issues](https://github.com/misaka-ning/MineSweeper/issues) 页面提出。

#include "minesweeper.h"
#include "ui_minesweeper.h"
#include <QMessageBox>

MineSweeper::MineSweeper(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MineSweeper)
    , settingDialog(new SettingDialog(this)) // 初始化对话框
{
    ui->setupUi(this);
    SweeperInit();
    // 连接设置按钮信号
    connect(titleBar, &GameTitleBar::settingBtnClicked, this, &MineSweeper::onSettingBtnClicked);
    // 连接难度选择信号
    connect(settingDialog, &SettingDialog::difficultySelected, this, &MineSweeper::onDifficultySelected);
    connect(gamepanel, &GameCore::firstCellOpened, titleBar, &GameTitleBar::startGameTimer);
    connect(gamepanel, &GameCore::gameReset, titleBar, &GameTitleBar::resetGameTimer);
    connect(gamepanel, &GameCore::gameWin, this, &MineSweeper::onGameWin);
}

void MineSweeper::onGameWin()
{
    // 获取计时秒数并格式化
    int totalSec = titleBar->getElapsedSeconds();
    int minutes = totalSec / 60;
    int seconds = totalSec % 60;
    QString timeStr = QString("%1分%2秒").arg(minutes).arg(seconds, 2, 10, QChar('0'));
    // 显示包含时间的胜利提示
    QMessageBox::warning(nullptr, "游戏胜利", QString("恭喜你打开了所有的格子并标记了全部地雷！\n游戏胜利！\n本次消耗时间：%1").arg(timeStr));
}

MineSweeper::~MineSweeper()
{
    delete gamepanel;
    delete titleBar;
    delete settingDialog; // 释放对话框
    delete ui;
}

void MineSweeper::SweeperInit()
{
    // 窗口大小：棋盘宽度 × (棋盘高度 + 标题栏高度)
    setFixedSize(GameConfig::colCount() * GameConfig::cellPixel(),
                 GameConfig::rowCount() * GameConfig::cellPixel() + GameConfig::titlePixel());

    // 初始化标题栏
    titleBar = new GameTitleBar(this);
    titleBar->setFixedSize(GameConfig::colCount() * GameConfig::cellPixel(), GameConfig::titlePixel());
    titleBar->move(0, 0);
    titleBar->show();

    // 初始化游戏核心
    gamepanel = new GameCore(this);
}

// 弹出设置对话框
void MineSweeper::onSettingBtnClicked()
{
    settingDialog->show();
}

// 响应难度选择，更新配置并重置游戏
void MineSweeper::onDifficultySelected(GameConfig::Difficulty diff)
{
    // 更新全局难度配置
    GameConfig::setDifficulty(diff);

    QString titleText;
    switch (diff) {
    case GameConfig::Difficulty::Easy: titleText = "扫雷 - 初级"; break;
    case GameConfig::Difficulty::Medium: titleText = "扫雷 - 中级"; break;
    case GameConfig::Difficulty::Hard: titleText = "扫雷 - 高级"; break;
    default: titleText = "扫雷 - 初级"; // 默认初级
    }
    titleBar->setTitleText(titleText); // 调用setTitleText更新

    // 重置游戏面板
    resetGamePanel();
}

// 重新初始化游戏面板（删除旧面板→调整窗口大小→创建新面板）
void MineSweeper::resetGamePanel()
{
    // 1. 删除旧的游戏核心（自动释放GameBoard）
    delete gamepanel;
    gamepanel = nullptr;
    // 2. 调整主窗口和标题栏大小（适配新难度的棋盘）
    setFixedSize(GameConfig::colCount() * GameConfig::cellPixel(), GameConfig::rowCount() * GameConfig::cellPixel() + GameConfig::titlePixel());
    titleBar->setFixedSize(GameConfig::colCount() * GameConfig::cellPixel(), GameConfig::titlePixel());
    // 3. 创建新的游戏核心（自动初始化新棋盘）
    gamepanel = new GameCore(this);
    // 重新连接新游戏核心的信号（旧核心已被删除）
    connect(gamepanel, &GameCore::firstCellOpened, titleBar, &GameTitleBar::startGameTimer);
    connect(gamepanel, &GameCore::gameReset, titleBar, &GameTitleBar::resetGameTimer);
    connect(gamepanel, &GameCore::gameWin, this, &MineSweeper::onGameWin);
    // 切换难度后重置计时器
    titleBar->resetGameTimer();
}

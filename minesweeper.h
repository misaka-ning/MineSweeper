#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include <QMainWindow>
#include "gamecore.h"
#include "gameconfig.h"
#include "gametitlebar.h"
#include "SettingDialog.h" // 包含设置对话框头文件

QT_BEGIN_NAMESPACE
namespace Ui {
class MineSweeper;
}
QT_END_NAMESPACE

class MineSweeper : public QMainWindow
{
    Q_OBJECT
public:
    MineSweeper(QWidget *parent = nullptr);
    ~MineSweeper();

private slots:
    // 响应设置按钮点击（弹出对话框）
    void onSettingBtnClicked();
    // 响应难度选择（更新游戏配置）
    void onDifficultySelected(GameConfig::Difficulty diff);
    void onGameWin();

private:
    Ui::MineSweeper *ui;
    GameCore *gamepanel;
    GameTitleBar *titleBar;
    SettingDialog *settingDialog; // 设置对话框实例

    void SweeperInit();
    void initLayout();
    // 重新初始化游戏面板（难度切换后调用）
    void resetGamePanel();
};

#endif // MINESWEEPER_H

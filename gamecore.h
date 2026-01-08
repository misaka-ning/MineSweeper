#ifndef GAMECORE_H
#define GAMECORE_H
#include "gameboard.h"
#include "GameConfig.h"
#include <QObject>
class GameCore : public QObject {
    Q_OBJECT
public:
    explicit GameCore(QWidget *parent = nullptr);
    ~GameCore();
public slots:
    void processChordOpen(QPoint pos); // 批量翻开核心处理函数
private slots:
    // 槽函数：处理「格子翻开」事件（参数与信号一致）
    void handleCellUncovered(QPoint pos);
signals:
    // 第一次翻开格子时触发（启动计时器）
    void firstCellOpened();
    // 游戏重启时触发（重置计时器）
    void gameReset();
    void gameWin();
private:
    GameBoard* GameBoard_m;
    bool first_hit_m; // 第一次点击（可避免第一次踩雷）
    int opencnt;
    void FloodFill(QPoint p);
    int countSurroundFlag(QPoint pos); // 统计指定格子周围8邻域的红旗数量
    void openSurroundCells(QPoint pos); // 翻开指定格子周围所有符合条件的格子
};
#endif // GAMECORE_H

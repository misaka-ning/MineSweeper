#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "minecell.h"
#include "GameConfig.h"
#include <QVector>
#include <QSet>
#include <QWidget>

class GameBoard : public QWidget {
    Q_OBJECT
public:
    explicit GameBoard(QWidget *parent = nullptr);
    ~GameBoard();

    void MinePosisionInit(QPoint point);
    bool isMineAt(QPoint pos) { return mine_posision_m.contains(pos); } // 判断是否是地雷
    void BoardSetState(int x, int y, CellState state);
    void UpdatePointStyle(QPoint point);
    int GetPointNumber(QPoint point);
    bool CheckPointOut(QPoint point);
    CellState GetPointState(QPoint point);
    MineCell* getCell(QPoint point);

signals:
    void cellUncovered(QPoint pos); // 转发 MineCell 的信号
    void handleCellFlagged(QPoint pos);
    void chordOpenRequest(QPoint pos);

private:
    QVector<QVector<MineCell*>> BoardVector_m;  // 存储地雷格子数组
    QWidget *Sweeper_m;
    QSet<QPoint> mine_posision_m;

    // 保存当前对象创建时的行列数（不依赖全局配置）
    int selfRowCount;
    int selfColCount;

    void GameBoardInit();
    int GetAroundMineNum(QPoint p);
    inline bool CheckOut(int x, int y);
};
#endif // GAMEBOARD_H

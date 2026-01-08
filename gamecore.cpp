#include "gamecore.h"
#include <QDebug>
#include "minecell.h"
#include <QMessageBox>
#include "gameconfig.h"

// 游戏核心逻辑类
GameCore::GameCore(QWidget *parent)
    : QObject(parent), first_hit_m(true), opencnt(0)
{
    // 创建 GameBoard，父对象由 GameCore 管理
    GameBoard_m = new GameBoard(parent);
    GameBoard_m->show();

    // 连接 GameBoard 信号到 GameCore 槽函数
    connect(GameBoard_m, &GameBoard::cellUncovered, this, &GameCore::handleCellUncovered);
    connect(GameBoard_m, &GameBoard::chordOpenRequest, this, &GameCore::processChordOpen);
}

GameCore::~GameCore()
{
    delete GameBoard_m;
    GameBoard_m = nullptr;
}


// 处理格子翻开逻辑
void GameCore::handleCellUncovered(QPoint pos)
{
    if(GameBoard_m->GetPointState(pos) == FLAGGED || GameBoard_m->GetPointState(pos) == UNCOVERED) return;
    if(first_hit_m)
    {
        GameBoard_m->MinePosisionInit(pos);
        first_hit_m = false;
        emit firstCellOpened(); // 第一次点击后发射（启动计时器）
    }
    if(GameBoard_m->GetPointNumber(pos) == 0) // 点击空白
    {
        FloodFill(pos);
    }
    else if(GameBoard_m->GetPointNumber(pos) == 11) // 点击地雷
    {
        GameBoard_m->BoardSetState(pos.x(), pos.y(), UNCOVERED);
        QMessageBox::warning(nullptr, "游戏失败", "你踩到地雷了！游戏结束！");
        GameBoard_m->MinePosisionInit(pos);
        first_hit_m = true;
        opencnt = 0;
        emit gameReset(); // 游戏失败后发射（重置计时器）
    }
    else
    {
        GameBoard_m->BoardSetState(pos.x(), pos.y(), UNCOVERED);
        opencnt++;
    }
    if(opencnt >= GameConfig::safeCellCount())
    {
        // QMessageBox::warning(nullptr, "游戏胜利", "恭喜你打开了所有的格子并标记了全部地雷！游戏胜利！");
        emit gameWin(); // 触发弹窗（阻塞后续代码，直到用户关闭弹窗）
        GameBoard_m->MinePosisionInit(pos);
        first_hit_m = true;
        opencnt = 0;
        emit gameReset();
    }
}

void GameCore::FloodFill(QPoint p)
{
    GameBoard_m->BoardSetState(p.x(), p.y(), UNCOVERED);
    opencnt++;
    if(GameBoard_m->GetPointNumber(p) == 0)
    {
        for(int i = 0; i < 8; ++i)
        {
            QPoint temp(p.x() + GameConfig::dx().at(i), p.y() + GameConfig::dy().at(i));
            if(GameBoard_m->CheckPointOut(temp)) continue;
            if(GameBoard_m->GetPointState(temp) == COVERED) FloodFill(temp);
        }
    }
}

// 统计【指定坐标】周围8个方向的 红旗标记数量
int GameCore::countSurroundFlag(QPoint pos)
{
    int flagCount = 0;
    int x = pos.x();
    int y = pos.y();

    for(int i=0; i<8; i++)
    {
        int nx = x + GameConfig::dx().at(i);
        int ny = y + GameConfig::dy().at(i);
        QPoint npos(nx, ny);
        // 坐标合法 + 获取格子 + 格子是红旗状态 → 计数+1
        if(!GameBoard_m->CheckPointOut(npos))
        {
            MineCell* cell = GameBoard_m->getCell(npos); // 已有获取格子的接口
            if(cell->State() == CellState::FLAGGED)
            {
                flagCount++;
            }
        }
    }
    return flagCount;
}

// 翻开【指定坐标】周围8个方向的所有符合条件的格子
void GameCore::openSurroundCells(QPoint pos)
{
    int x = pos.x();
    int y = pos.y();

    for(int i=0; i<8; i++)
    {
        int nx = x + GameConfig::dx().at(i);
        int ny = y + GameConfig::dy().at(i);
        QPoint npos(nx, ny);
        if(GameBoard_m->CheckPointOut(npos)) continue; // 越界跳过

        MineCell* cell = GameBoard_m->getCell(npos);
        // 只翻开：【未翻开】+【未标记红旗】的格子（红旗/已翻开 都不处理）
        if(cell->State() == CellState::COVERED && cell->State() != CellState::FLAGGED)
        {
            // 复用原有的单个翻开逻辑
            handleCellUncovered(npos);
            // handleCellUncovered里已经有「踩雷→游戏失败」逻辑
            if(first_hit_m) return;
        }
    }
}

// 核心处理函数：批量翻开的总入口
void GameCore::processChordOpen(QPoint pos)
{
    // 获取当前操作的格子
    MineCell* curCell = GameBoard_m->getCell(pos);
    if(curCell == nullptr) return;

    // 核心判定：周围红旗数 == 格子数字 → 执行翻开
    int surrFlagCnt = countSurroundFlag(pos);
    int cellNumber = curCell->MineNum();
    if(surrFlagCnt == cellNumber)
    {
        // 满足条件，翻开周围所有符合条件的格子
        openSurroundCells(pos);
    }
    // 不满足条件 → 无任何操作
    return;
}

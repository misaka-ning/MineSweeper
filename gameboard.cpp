#include "gameboard.h"
#include <QRandomGenerator>

// 游戏棋盘类
GameBoard::GameBoard(QWidget *parent)
    : QWidget(parent)
{
    selfRowCount = GameConfig::rowCount();
    selfColCount = GameConfig::colCount();

    // 棋盘大小：列数×格子像素（宽），行数×格子像素（高）
    setFixedSize(GameConfig::colCount() * GameConfig::cellPixel(), GameConfig::rowCount() * GameConfig::cellPixel());
    // 棋盘位置：x=0，y=标题栏高度
    move(0, GameConfig::titlePixel());
    // 初始化棋盘（创建棋子）
    GameBoardInit();
}


GameBoard::~GameBoard() {
    for (int i = 1; i <= selfRowCount; ++i) {
        for (int j = 1; j <= selfColCount; ++j) {
            delete BoardVector_m[i][j];
            BoardVector_m[i][j] = nullptr;
        }
    }
    BoardVector_m.clear();
}

// 更新炸弹位置、重新开始游戏均调用此api
// point -> 初次点击的位置
void GameBoard::MinePosisionInit(QPoint point)
{
    mine_posision_m.clear();
    int maxRetry = GameConfig::totalCellCount() * 2; // 最大重试次数
    int retryCount = 0;
    while(mine_posision_m.size() < GameConfig::mineCount() && retryCount < maxRetry)
    {
        retryCount++;
        // gameboard.cpp MinePosisionInit 函数
        int row = QRandomGenerator::global()->bounded(1, selfRowCount + 1); // 行号（1-16）
        int col = QRandomGenerator::global()->bounded(1, selfColCount + 1); // 列号（1-30）
        QPoint p(row, col); // 统一为（行号，列号）
        if((row >= point.x() - 2 && row <= point.x() + 2) && (col >= point.y() - 2 && col <= point.y() + 2)) continue;
        if(mine_posision_m.contains(p)) continue;
        else mine_posision_m.insert(p);
    }
    // 异常处理：若重试1000次仍未生成足够地雷，打印警告并调整地雷数
    if (mine_posision_m.size() < GameConfig::mineCount()) {
        qWarning() << "地雷生成失败，可用位置不足，自动调整地雷数为" << mine_posision_m.size();
    }

    for(int i = 1; i <= selfRowCount; ++i)
    {
        for(int j = 1; j <= selfColCount; ++j)
        {
            QPoint p(i, j);
            if(mine_posision_m.contains(p))
            {
                BoardVector_m[i][j]->SetMineFlag(true);
                BoardVector_m[i][j]->SetMineNum(11);
            }
            else
            {
                BoardVector_m[i][j]->SetMineFlag(false);
                BoardVector_m[i][j]->SetMineNum(GetAroundMineNum(p));
            }
            BoardVector_m[i][j]->SetState(COVERED);
            BoardVector_m[i][j]->updateStyle();
        }
    }
}

void GameBoard::BoardSetState(int x, int y, CellState state)
{
    BoardVector_m[x][y]->SetState(state);
    BoardVector_m[x][y]->updateStyle();
}

void GameBoard::UpdatePointStyle(QPoint point)
{
    BoardVector_m[point.x()][point.y()]->updateStyle();
}

int GameBoard::GetPointNumber(QPoint point)
{
    return BoardVector_m[point.x()][point.y()]->MineNum();
}

bool GameBoard::CheckPointOut(QPoint point)
{
    return CheckOut(point.x(), point.y());
}

CellState GameBoard::GetPointState(QPoint point)
{
    return BoardVector_m[point.x()][point.y()]->State();
}

MineCell *GameBoard::getCell(QPoint point)
{
    return BoardVector_m[point.x()][point.y()];
}


void GameBoard::GameBoardInit()
{
    // 用自身保存的行列数resize容器
    BoardVector_m.resize(selfRowCount + 1, QVector<MineCell*>(selfColCount + 1));
    // 循环条件使用自身成员变量
    for(int i = 1; i <= selfRowCount; ++i)
    {
        for(int j = 1; j <= selfColCount; ++j)
        {
            BoardVector_m[i][j] = new MineCell(QPoint(i, j), false, 0, this);
            BoardVector_m[i][j]->move((j - 1) * GameConfig::cellPixel(), (i - 1) * GameConfig::cellPixel());
            connect(BoardVector_m[i][j], &MineCell::cellUncovered, this, &GameBoard::cellUncovered);
            connect(BoardVector_m[i][j], &MineCell::cellFlagged, this, &GameBoard::handleCellFlagged);
            connect(BoardVector_m[i][j], &MineCell::chordOpenRequest, this, &GameBoard::chordOpenRequest);
            BoardVector_m[i][j]->show();
        }
    }
}

inline bool GameBoard::CheckOut(int x, int y)
{
    if(x < 1 || y < 1 || x > GameConfig::rowCount() || y > GameConfig::colCount()) return true;
    return false;
}

int GameBoard::GetAroundMineNum(QPoint p)
{
    int cnt = 0;
    for(int i = 0; i < 8; ++i)
    {
        int x = p.x() + GameConfig::dx().at(i);
        int y = p.y() + GameConfig::dy().at(i);
        if(CheckOut(x, y)) continue;
        if(mine_posision_m.contains(QPoint(x, y))) cnt++;
    }
    return cnt;
}

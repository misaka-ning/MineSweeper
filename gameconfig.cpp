#include "GameConfig.h"

// ========== 初始化所有静态成员变量 ==========
GameConfig::Difficulty GameConfig::s_currentDifficulty = GameConfig::Medium;
int GameConfig::s_rowCount = 16;
int GameConfig::s_colCount = 16;
int GameConfig::s_mineCount = 40;
int GameConfig::s_cellPixel = 50;
int GameConfig::s_titlePixel = 80;

// 8方向偏移量 固定值：上、下、左、右、左上、右上、左下、右下
const QVector<int> GameConfig::s_dx = { -1, 1, 0, 0, -1, -1, 1, 1 };
const QVector<int> GameConfig::s_dy = { 0, 0, -1, 1, -1, 1, -1, 1 };

// ========== 实现所有静态成员方法 ==========
void GameConfig::setDifficulty(Difficulty diff)
{
    s_currentDifficulty = diff;
    // 根据难度赋值对应的 行/列/地雷数
    switch (diff) {
    case Easy:
        s_rowCount = 9;
        s_colCount = 9;
        s_mineCount = 10;
        break;
    case Medium:
        s_rowCount = 16;
        s_colCount = 16;
        s_mineCount = 40;
        break;
    case Hard:
        s_rowCount = 16;
        s_colCount = 30;
        s_mineCount = 99;
        break;
    }
}

int GameConfig::rowCount() { return s_rowCount; }
int GameConfig::colCount() { return s_colCount; }
int GameConfig::mineCount() { return s_mineCount; }

int GameConfig::cellPixel(){ return s_cellPixel; }
int GameConfig::titlePixel(){ return s_titlePixel; }
const QVector<int>& GameConfig::dx() { return s_dx; }
const QVector<int>& GameConfig::dy() { return s_dy; }
int GameConfig::totalCellCount() { return s_rowCount * s_colCount; }
int GameConfig::safeCellCount() { return totalCellCount() - s_mineCount; }

bool GameConfig::isPosValid(int row, int col)
{
    return row >= 1 && row <= s_rowCount && col >=1 && col <= s_colCount;
}

bool GameConfig::isPosValid(const QPoint& pos)
{
    return isPosValid(pos.x(), pos.y());
}

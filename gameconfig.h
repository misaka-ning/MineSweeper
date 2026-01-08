#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <QVector>
#include <QPoint>

// 扫雷全局配置类 - 集中管理所有常量/配置，彻底解决重复定义问题
class GameConfig
{
public:
    // 扫雷难度枚举
    enum Difficulty {
        Easy,      // 初级：9*9 格子，10个地雷
        Medium,    // 中级：16*16 格子，40个地雷 (默认值)
        Hard       // 高级：16*30 格子，99个地雷
    };

    // ========== 核心对外调用接口 ==========
    // 设置游戏难度，切换难度后全局生效
    static void setDifficulty(Difficulty diff);
    // 获取当前行数
    static int rowCount();
    // 获取当前列数
    static int colCount();
    // 获取当前地雷总数
    static int mineCount();
    // 获取单个格子的像素大小
    static int cellPixel();
    // 获取顶部标题栏的像素高度
    static int titlePixel();
    // 获取8方向偏移量X轴
    static const QVector<int>& dx();
    // 获取8方向偏移量Y轴
    static const QVector<int>& dy();
    // 计算棋盘总格子数
    static int totalCellCount();
    // 计算安全格子数（总格子-地雷数
    static int safeCellCount();
    // 校验坐标是否在棋盘范围内 - 全局通用，避免每个类都写一遍判断逻辑
    static bool isPosValid(int row, int col);
    static bool isPosValid(const QPoint& pos);

    static Difficulty getCurrentDifficulty() {return s_currentDifficulty; }
    static void setCurrentDifficulty(Difficulty diff) { s_currentDifficulty = diff; }


private:
    // 私有静态成员变量，仅内部修改，外部只读
    static Difficulty s_currentDifficulty;  // 当前选中难度
    static int s_rowCount;                  // 当前行数
    static int s_colCount;                  // 当前列数
    static int s_mineCount;                 // 当前地雷数
    static int s_cellPixel;                 // 每个格子的像素大小
    static int s_titlePixel;                // 顶部标题栏的的像素高度
    // 8个方向的偏移量 (扫雷核心，上下左右+四个斜角)
    static const QVector<int> s_dx;
    static const QVector<int> s_dy;
};

#endif // GAMECONFIG_H

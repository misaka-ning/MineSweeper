#ifndef MINECELL_H
#define MINECELL_H

#include <QWidget>
#include <QPushButton>
#include <QMap>
#include <QIcon>
#include <QPoint>
#include <QMouseEvent>
#include "gameconfig.h"

// 格子状态枚举
enum CellState {
    COVERED,      // 未翻开（默认）
    UNCOVERED,    // 已翻开
    FLAGGED,      // 标记为地雷
    QUESTIONED    // 标记为问号
};


namespace Ui {
class MineCell;
}

class MineCell : public QPushButton
{
    Q_OBJECT

public:
    explicit MineCell(QWidget *parent = nullptr);
    explicit MineCell(QPoint posision, bool flag, int num, QWidget *parent = nullptr);
    ~MineCell();

    void SetMineFlag(const bool flag);
    bool MineFlag();
    void SetMineNum(const int num);
    int MineNum();
    void SetState(const CellState state);
    CellState State();
    void updateStyle();

signals:
    void cellUncovered(QPoint position);
    void cellFlagged(QPoint pos);
    void chordOpenRequest(QPoint cellPos);

protected:
    // 重写鼠标按下事件，用于处理右键点击
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseLeaveEvent(QMouseEvent *event);

private:
    Ui::MineCell *ui;
    QMap<int, QIcon> icon_map_m;
    bool mine_flag_m;
    int mine_num_m;
    QPoint posision_m;
    QIcon icon_m;
    CellState state_m;
    bool isHovered_m;           // 是否悬停
    bool isPressedVisual_m;     // 视觉上的按下状态
    bool isLeftPressed_m;

    void CellInit();
    void IconMapInit();
    void updateVisualStyle();

};

#endif // MINECELL_H

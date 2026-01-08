#include "minecell.h"
#include "ui_minecell.h"

#include <QIcon>
#include <QString>
#include <QSize>

// 地雷格子类
MineCell::MineCell(QWidget *parent)
    : QPushButton(parent)
    , ui(new Ui::MineCell), posision_m(QPoint(0, 0)), mine_flag_m(false), mine_num_m(0), state_m(COVERED), isLeftPressed_m(false)
{
    ui->setupUi(this);

    CellInit();
}

MineCell::MineCell(QPoint posision, bool flag, int num, QWidget *parent)
    : QPushButton(parent)
    , ui(new Ui::MineCell), posision_m(posision), mine_flag_m(flag), mine_num_m(num), state_m(COVERED), isLeftPressed_m(false)
{
    ui->setupUi(this);

    CellInit();
}

MineCell::~MineCell()
{
    delete ui;
}

void MineCell::SetMineFlag(const bool flag)
{
    mine_flag_m = flag;
}

bool MineCell::MineFlag()
{
    return mine_flag_m;
}

void MineCell::SetMineNum(const int num)
{
    mine_num_m = num;
}

int MineCell::MineNum()
{
    return mine_num_m;
}

void MineCell::SetState(const CellState state)
{
    state_m = state;
}

CellState MineCell::State()
{
    return state_m;
}

void MineCell::updateStyle()
{
    updateVisualStyle();
}

void MineCell::mousePressEvent(QMouseEvent *e)
{
    bool isChordOperation = false;
    if (e->button() == Qt::RightButton && isLeftPressed_m)
    {
        // 当前格子必须是【已翻开】+【有数字(1-8)】，空白格(0)无此功能
        if (state_m == CellState::UNCOVERED && mine_num_m >= 1 && mine_num_m <=8)
        {
            // 发送批量翻开请求，把当前格子坐标传给GameBoard
            emit chordOpenRequest(posision_m);
            isChordOperation = true;
        }
    }

    // 处理右键点击
    if (e->button() == Qt::RightButton && !isChordOperation)
    {
        // 根据当前状态切换标记（扫雷常见逻辑：未标记→红旗→问号→未标记）
        if (state_m == COVERED)
        {
            state_m = FLAGGED;  // 未翻开→标记红旗
        }
        else if (state_m == FLAGGED)
        {
            state_m = QUESTIONED;  // 红旗→问号
        }
        else if (state_m == QUESTIONED)
        {
            state_m = COVERED;  // 问号→未标记
        }
        updateVisualStyle();  // 更新视觉样式
        emit cellFlagged(posision_m);
        return;  // 处理完毕，无需继续传递事件
    }

    // 左键点击交给父类处理（触发默认的clicked()信号等）
    if (e->button() == Qt::LeftButton)
    {
        isLeftPressed_m = true;
        emit cellUncovered(posision_m);
        // updateVisualStyle();
    }
}

void MineCell::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isLeftPressed_m = false;
    }
}

void MineCell::mouseLeaveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    isLeftPressed_m = false;
}

void MineCell::CellInit()
{
    IconMapInit();
    icon_m = icon_map_m[mine_num_m];
    setIcon(icon_m);
    setIconSize(QSize(GameConfig::cellPixel(), GameConfig::cellPixel()));
    setFixedSize(GameConfig::cellPixel(), GameConfig::cellPixel());
    setFlat(true);  // 使按钮看起来扁平，移除3D效果
    updateVisualStyle();
}

void MineCell::IconMapInit()
{
    for(int i = 1; i <= 8; ++i)
    {
        QString temp = QString(":/res/num%1.png").arg(i);
        icon_map_m[i] = QIcon(temp);
    }
    icon_map_m[0] = QIcon();
    icon_map_m[9] = QIcon(":/res/redflag.png");
    icon_map_m[10] = QIcon(":/res/quemark.png");
    icon_map_m[11] = QIcon(":/res/mine.png");
}

// 样式表方法更新视觉样式 - 高对比度清晰配色版(by豆包)
void MineCell::updateVisualStyle()
{
    // 基础样式：统一保留扁平+图标尺寸，扫雷核心基础样式【未修改】
    setFlat(true);
    setIconSize(QSize(GameConfig::cellPixel() / 2, GameConfig::cellPixel() / 2));
    QString cellStyle;

    // ========== 分支1：格子【已翻开】状态 UNCOVERED ==========
    if (state_m == UNCOVERED)
    {
        if (mine_flag_m)
        {
            cellStyle = "QPushButton { border: 1px solid #888888; background-color: #FFD0D0; }";
            setIcon(QIcon(":/res/mine.png"));
        }
        else
        {
            cellStyle = "QPushButton { border: 1px solid #888888; background-color: #D0D0D0; }";
            setIcon(mine_num_m > 0 ? icon_map_m[mine_num_m] : QIcon());
        }
    }

    // ========== 分支2：格子【未翻开】系列状态 (COVERED/FLAGGED/QUESTIONED) ==========
    else
    {
        cellStyle = "QPushButton { border: 2px outset #808080; background-color: #BFBFBF; }"
                    "QPushButton:hover { background-color: #B0B0B0; }"
                    "QPushButton:pressed { border: 1px inset #707070; background-color: #A0A0A0; }";
        if (state_m == FLAGGED)
        {
            setIcon(icon_map_m[9]);
        }
        else if (state_m == QUESTIONED)
        {
            setIcon(icon_map_m[10]);
        }
        else
        {
            setIcon(QIcon());
        }
    }

    // 应用最终样式表【未修改】
    this->setStyleSheet(cellStyle);
}

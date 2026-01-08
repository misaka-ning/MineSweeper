#include "gametitlebar.h"
#include <QHBoxLayout>
#include <QTime>
#include <QStyle>
#include <QPainter>
#include <QMouseEvent>

GameTitleBar::GameTitleBar(QWidget *parent)
    : QWidget(parent)
    , elapsedSeconds(0)
{
    // ========== 1. 整体样式美化 ==========
    // 标题栏背景：柔和渐变灰 + 圆角 + 轻微阴影
    setStyleSheet(R"(
        QWidget {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #f5f5f5, stop:1 #e8e8e8);
            border-radius: 8px 8px 0 0;  // 仅顶部圆角，贴合窗口
            border-bottom: 1px solid #dcdcdc;
        }
    )");
    setFixedHeight(48);  // 适度增高，提升视觉舒适度
    setAttribute(Qt::WA_StyledBackground, true);  // 确保背景样式生效

    // ========== 2. 标题标签美化 ==========
    titleLabel = new QLabel("扫雷 - 中级", this);
    titleLabel->setStyleSheet(R"(
        QLabel {
            font-family: "Microsoft YaHei", "Arial";  // 适配中英文
            font-size: 18px;
            font-weight: 600;  // 半粗体，比bold更柔和
            color: #333333;     // 深灰，避免纯黑刺眼
            padding-left: 8px;
        }
    )");
    titleLabel->setAlignment(Qt::AlignVCenter);  // 垂直居中

    // ========== 3. 设置按钮美化 ==========
    settingBtn = new QPushButton(this);
    settingBtn->setIcon(style()->standardIcon(QStyle::SP_FileDialogDetailedView));
    settingBtn->setToolTip("游戏设置");
    // 按钮样式：圆角 + 悬停效果 + 无外边框
    settingBtn->setStyleSheet(R"(
        QPushButton {
            border: none;
            border-radius: 15px;  // 圆形按钮
            background: transparent;
            padding: 4px;
        }
        QPushButton:hover {
            background: #d0d0d0;  // 悬停浅灰背景
        }
        QPushButton:pressed {
            background: #b8b8b8;  // 按下深色背景
        }
    )");
    settingBtn->setFixedSize(30, 30);  // 保持按钮大小
    connect(settingBtn, &QPushButton::clicked, this, &GameTitleBar::onSettingBtnClicked);

    // ========== 4. 计时器标签美化 ==========
    timerLabel = new QLabel("00:00", this);
    timerLabel->setStyleSheet(R"(
        QLabel {
            font-family: "Consolas", "Microsoft YaHei";  // 等宽字体，计时更整齐
            font-size: 16px;
            font-weight: 600;
            color: #2188ff;  // 蓝色，突出计时但不刺眼
            background: #ffffff;
            border: 1px solid #e0e0e0;
            border-radius: 6px;
            padding: 4px 12px;
            min-width: 80px;
            text-align: center;
        }
    )");
    timerLabel->setAlignment(Qt::AlignCenter);

    // ========== 5. 布局精细化调整 ==========
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(16, 8, 16, 8);  // 上下左右内边距更均匀
    mainLayout->setSpacing(12);  // 元素间距统一

    // 布局顺序：标题 → 拉伸 → 设置按钮 → 计时器
    mainLayout->addWidget(titleLabel);
    mainLayout->addStretch(1);  // 拉伸占比1，让标题靠左，右侧元素紧凑
    mainLayout->addWidget(settingBtn);
    mainLayout->addSpacing(8);  // 设置按钮和计时器之间额外间距
    mainLayout->addWidget(timerLabel);

    setLayout(mainLayout);
    // 初始化计时器
    gameTimer = new QTimer(this);
    gameTimer->setInterval(1000);
    connect(gameTimer, &QTimer::timeout, this, &GameTitleBar::updateTimerDisplay);
}

GameTitleBar::~GameTitleBar() = default;

// 原有功能：设置标题文本
void GameTitleBar::setTitleText(const QString &text)
{
    titleLabel->setText(text);
}

// 原有功能：设置按钮点击处理
void GameTitleBar::onSettingBtnClicked()
{
    emit settingBtnClicked();
}

// 计时器更新（保留原有逻辑）
void GameTitleBar::updateTimerDisplay()
{
    elapsedSeconds++;
    int minutes = elapsedSeconds / 60;
    int seconds = elapsedSeconds % 60;
    timerLabel->setText(QString("%1:%2")
                            .arg(minutes, 2, 10, QChar('0'))
                            .arg(seconds, 2, 10, QChar('0')));
}

// 启动计时器
void GameTitleBar::startGameTimer()
{
    if (!gameTimer->isActive()) {
        gameTimer->start();
    }
}

// 重置计时器
void GameTitleBar::resetGameTimer()
{
    gameTimer->stop();
    elapsedSeconds = 0;
    timerLabel->setText("00:00");
}

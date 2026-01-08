#include "SettingDialog.h"
#include <QLabel>

SettingDialog::SettingDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("游戏设置");
    setFixedSize(200, 180); // 固定对话框大小
    initUI();
}

void SettingDialog::initUI()
{
    // 创建难度单选按钮（默认选中当前难度）
    rbEasy = new QRadioButton("初级 (9×9 · 10地雷)", this);
    rbMedium = new QRadioButton("中级 (16×16 · 40地雷)", this);
    rbHard = new QRadioButton("高级 (16×30 · 99地雷)", this);

    // 根据当前配置选中对应单选按钮
    switch (GameConfig::getCurrentDifficulty()) {
    case GameConfig::Easy:
        rbEasy->setChecked(true);
        break;
    case GameConfig::Medium:
        rbMedium->setChecked(true);
        break;
    case GameConfig::Hard:
        rbHard->setChecked(true);
        break;
    }

    // 创建按钮
    btnConfirm = new QPushButton("确认", this);
    btnCancel = new QPushButton("取消", this);
    btnConfirm->setFixedSize(80, 30);
    btnCancel->setFixedSize(80, 30);

    // 布局管理
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    QHBoxLayout *btnLayout = new QHBoxLayout();

    vLayout->addWidget(new QLabel("选择难度", this));
    vLayout->addWidget(rbEasy);
    vLayout->addWidget(rbMedium);
    vLayout->addWidget(rbHard);
    vLayout->addStretch();

    btnLayout->addStretch();
    btnLayout->addWidget(btnConfirm);
    btnLayout->addSpacing(20);
    btnLayout->addWidget(btnCancel);
    btnLayout->addStretch();

    vLayout->addLayout(btnLayout);
    vLayout->setContentsMargins(20, 20, 20, 20);
    vLayout->setSpacing(15);

    // 连接信号槽
    connect(btnConfirm, &QPushButton::clicked, this, &SettingDialog::onConfirmClicked);
    connect(btnCancel, &QPushButton::clicked, this, &SettingDialog::onCancelClicked);
}

void SettingDialog::onConfirmClicked()
{
    // 获取选中的难度
    GameConfig::Difficulty selectedDiff = GameConfig::Medium;
    if (rbEasy->isChecked()) {
        selectedDiff = GameConfig::Easy;
    } else if (rbHard->isChecked()) {
        selectedDiff = GameConfig::Hard;
    }

    // 发送选中信号并关闭对话框
    emit difficultySelected(selectedDiff);
    close();
}

void SettingDialog::onCancelClicked()
{
    close();
}

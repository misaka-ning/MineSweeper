#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H
#include <QDialog>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "gameconfig.h"

class SettingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog() = default;

signals:
    // 选中难度后发送此信号（参数为选中的难度）
    void difficultySelected(GameConfig::Difficulty diff);

private slots:
    // 确认按钮点击事件
    void onConfirmClicked();
    // 取消按钮点击事件
    void onCancelClicked();

private:
    // 初始化UI组件
    void initUI();

    // 单选按钮组
    QRadioButton *rbEasy;
    QRadioButton *rbMedium;
    QRadioButton *rbHard;
    // 按钮
    QPushButton *btnConfirm;
    QPushButton *btnCancel;
};

#endif // SETTINGDIALOG_H

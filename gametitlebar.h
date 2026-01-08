#ifndef GAMETITLEBAR_H
#define GAMETITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QMouseEvent>

class GameTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit GameTitleBar(QWidget *parent = nullptr);
    ~GameTitleBar() override;
    void setTitleText(const QString &text);
    int getElapsedSeconds() const { return elapsedSeconds; }

signals:
    void settingBtnClicked();

private:
    QLabel *titleLabel;
    QPushButton *settingBtn;
    QLabel *timerLabel;
    QTimer *gameTimer;
    int elapsedSeconds;

private slots:
    void updateTimerDisplay();

public slots:
    void startGameTimer();
    void resetGameTimer();
    void onSettingBtnClicked();
};

#endif // GAMETITLEBAR_H

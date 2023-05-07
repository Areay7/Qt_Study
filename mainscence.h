#ifndef MAINSCENCE_H
#define MAINSCENCE_H

#include <QMainWindow>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QSoundEffect>

#include "mypushbutton.h"
#include "chooselevelscene.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainScence; }
QT_END_NAMESPACE

class MainScence : public QMainWindow
{
    Q_OBJECT

public:
    MainScence(QWidget *parent = nullptr);
    ~MainScence();

    // 重写paintEvent事件  画背景图
    void paintEvent(QPaintEvent *);

    // 选择场景
    ChooseLevelScene * chooseScene = NULL;

private:
    Ui::MainScence *ui;
};
#endif // MAINSCENCE_H

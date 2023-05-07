#ifndef PLAYSCENE_H
#define PLAYSCENE_H

class MyCoin;

#include <QMainWindow>
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSoundEffect>

#include "mypushbutton.h"
#include "mycoin.h"
#include "dataconfig.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int levelNum);

    MyCoin * coinBtn[4][4];

    int levelIndex;  // 内部成员属性  记录所选的关卡

    // 重写paintEvent事件  画背景图
    void paintEvent(QPaintEvent *);

    int gameArray[4][4];  // 二维数组维护每个关卡具体数据

    // 是否胜利标志
    bool isWin;

signals:
    // 写一个自定义的信号， 告诉主场景  点击了返回
    void ChooseSceneBack();

};

#endif // PLAYSCENE_H

#ifndef MYCOIN_H
#define MYCOIN_H

class playscene;

#include <QPushButton>
#include <QDebug>
#include <QPixmap>
#include <QTimer>
#include <QMouseEvent>

#include "playscene.h"

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);

    // 参数代表  传入金币到路径 OR  银币路径
    MyCoin(QString btnImg);

    // 金币的属性
    int posX;  // X坐标位置
    int posY;  // Y坐标位置
    bool flag;  // 正反标志

    // 改变标志的方法
    void changeFlag();

    QTimer * timer1;  // 正面翻反面
    QTimer * timer2;  // 反面翻正面

    int min = 1;
    int max = 8;

    // 执行动画的标志
    bool isAnimation = false;

    // 重写  按下
    void mousePressEvent(QMouseEvent *e);

    // 是否胜利标志
    bool notPress = false;

signals:

};

#endif // MYCOIN_H

#include "mainscence.h"

#include <QApplication>
#include <QDebug>

#include "dataconfig.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScence w;
    w.show();

//    // 测试关卡数据
//    dataConfig dataConfig;
//    for (int i = 0; i < 4; i++)
//    {
//        for (int j = 0; j < 4; j++) {
//            qDebug() << dataConfig.mData[1][i][j];
//        }
//        qDebug() << "";
//    }

    return a.exec();
}

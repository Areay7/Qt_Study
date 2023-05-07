/********************************************************************************
** Form generated from reading UI file 'mainscence.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINSCENCE_H
#define UI_MAINSCENCE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainScence
{
public:
    QAction *actionquit;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;

    void setupUi(QMainWindow *MainScence)
    {
        if (MainScence->objectName().isEmpty())
            MainScence->setObjectName("MainScence");
        MainScence->resize(643, 453);
        actionquit = new QAction(MainScence);
        actionquit->setObjectName("actionquit");
        centralwidget = new QWidget(MainScence);
        centralwidget->setObjectName("centralwidget");
        MainScence->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainScence);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 643, 22));
        menubar->setNativeMenuBar(false);
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        MainScence->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionquit);

        retranslateUi(MainScence);

        QMetaObject::connectSlotsByName(MainScence);
    } // setupUi

    void retranslateUi(QMainWindow *MainScence)
    {
        MainScence->setWindowTitle(QCoreApplication::translate("MainScence", "MainScence", nullptr));
        actionquit->setText(QCoreApplication::translate("MainScence", "\351\200\200  \345\207\272", nullptr));
        actionquit->setIconText(QCoreApplication::translate("MainScence", "quit", nullptr));
        menu->setTitle(QCoreApplication::translate("MainScence", "\345\274\200  \345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainScence: public Ui_MainScence {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSCENCE_H

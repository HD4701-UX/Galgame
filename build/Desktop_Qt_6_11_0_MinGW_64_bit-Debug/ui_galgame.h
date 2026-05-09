/********************************************************************************
** Form generated from reading UI file 'galgame.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GALGAME_H
#define UI_GALGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_galgame
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *galgame)
    {
        if (galgame->objectName().isEmpty())
            galgame->setObjectName("galgame");
        galgame->resize(800, 600);
        centralwidget = new QWidget(galgame);
        centralwidget->setObjectName("centralwidget");
        galgame->setCentralWidget(centralwidget);
        menubar = new QMenuBar(galgame);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        galgame->setMenuBar(menubar);
        statusbar = new QStatusBar(galgame);
        statusbar->setObjectName("statusbar");
        galgame->setStatusBar(statusbar);

        retranslateUi(galgame);

        QMetaObject::connectSlotsByName(galgame);
    } // setupUi

    void retranslateUi(QMainWindow *galgame)
    {
        galgame->setWindowTitle(QCoreApplication::translate("galgame", "galgame", nullptr));
    } // retranslateUi

};

namespace Ui {
    class galgame: public Ui_galgame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GALGAME_H

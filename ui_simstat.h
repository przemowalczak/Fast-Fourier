/********************************************************************************
** Form generated from reading UI file 'simstat.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMSTAT_H
#define UI_SIMSTAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimStat
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SimStat)
    {
        if (SimStat->objectName().isEmpty())
            SimStat->setObjectName(QString::fromUtf8("SimStat"));
        SimStat->resize(800, 600);
        menubar = new QMenuBar(SimStat);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        SimStat->setMenuBar(menubar);
        centralwidget = new QWidget(SimStat);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        SimStat->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(SimStat);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SimStat->setStatusBar(statusbar);

        retranslateUi(SimStat);

        QMetaObject::connectSlotsByName(SimStat);
    } // setupUi

    void retranslateUi(QMainWindow *SimStat)
    {
        SimStat->setWindowTitle(QCoreApplication::translate("SimStat", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimStat: public Ui_SimStat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMSTAT_H

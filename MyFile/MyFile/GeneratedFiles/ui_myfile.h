/********************************************************************************
** Form generated from reading UI file 'myfile.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFILE_H
#define UI_MYFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyFileClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyFileClass)
    {
        if (MyFileClass->objectName().isEmpty())
            MyFileClass->setObjectName(QStringLiteral("MyFileClass"));
        MyFileClass->resize(600, 400);
        menuBar = new QMenuBar(MyFileClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        MyFileClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyFileClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MyFileClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MyFileClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MyFileClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MyFileClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MyFileClass->setStatusBar(statusBar);

        retranslateUi(MyFileClass);

        QMetaObject::connectSlotsByName(MyFileClass);
    } // setupUi

    void retranslateUi(QMainWindow *MyFileClass)
    {
        MyFileClass->setWindowTitle(QApplication::translate("MyFileClass", "MyFile", 0));
    } // retranslateUi

};

namespace Ui {
    class MyFileClass: public Ui_MyFileClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFILE_H

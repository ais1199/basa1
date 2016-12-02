/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QWidget *centralWidget;
    QFrame *frame;
    QPushButton *finish;
    QLineEdit *newobtipe;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *newobname;
    QPushButton *pushButton;
    QLineEdit *newob;
    QLabel *label_3;
    QFrame *frame_2;
    QPushButton *createbase;
    QLineEdit *nbtipe;
    QLabel *label_4;
    QLabel *label_6;
    QLineEdit *nbplase;
    QPushButton *pushButton_2;
    QFrame *frame_3;
    QLabel *label_5;
    QLabel *Curbase;
    QLabel *label_7;
    QLabel *Curbasetipe;
    QPushButton *adddata;
    QPlainTextEdit *data;
    QPushButton *savenew;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 0, 311, 121));
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Raised);
        finish = new QPushButton(frame);
        finish->setObjectName(QStringLiteral("finish"));
        finish->setGeometry(QRect(180, 70, 121, 23));
        newobtipe = new QLineEdit(frame);
        newobtipe->setObjectName(QStringLiteral("newobtipe"));
        newobtipe->setGeometry(QRect(40, 10, 113, 20));
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 21, 16));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 40, 21, 16));
        newobname = new QLineEdit(frame);
        newobname->setObjectName(QStringLiteral("newobname"));
        newobname->setGeometry(QRect(40, 40, 113, 20));
        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 70, 151, 23));
        newob = new QLineEdit(frame);
        newob->setObjectName(QStringLiteral("newob"));
        newob->setGeometry(QRect(180, 40, 113, 20));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(190, 10, 121, 16));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(0, 120, 311, 81));
        frame_2->setFrameShape(QFrame::WinPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_2->setLineWidth(1);
        createbase = new QPushButton(frame_2);
        createbase->setObjectName(QStringLiteral("createbase"));
        createbase->setGeometry(QRect(10, 10, 101, 23));
        nbtipe = new QLineEdit(frame_2);
        nbtipe->setObjectName(QStringLiteral("nbtipe"));
        nbtipe->setGeometry(QRect(190, 10, 113, 20));
        label_4 = new QLabel(frame_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(150, 10, 31, 16));
        label_6 = new QLabel(frame_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(130, 50, 47, 13));
        nbplase = new QLineEdit(frame_2);
        nbplase->setObjectName(QStringLiteral("nbplase"));
        nbplase->setGeometry(QRect(190, 50, 113, 20));
        pushButton_2 = new QPushButton(frame_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 40, 101, 23));
        frame_3 = new QFrame(centralWidget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(0, 200, 311, 341));
        frame_3->setFrameShape(QFrame::WinPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        label_5 = new QLabel(frame_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 10, 81, 16));
        Curbase = new QLabel(frame_3);
        Curbase->setObjectName(QStringLiteral("Curbase"));
        Curbase->setGeometry(QRect(120, 10, 181, 16));
        label_7 = new QLabel(frame_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 40, 51, 16));
        Curbasetipe = new QLabel(frame_3);
        Curbasetipe->setObjectName(QStringLiteral("Curbasetipe"));
        Curbasetipe->setGeometry(QRect(120, 40, 171, 16));
        adddata = new QPushButton(frame_3);
        adddata->setObjectName(QStringLiteral("adddata"));
        adddata->setGeometry(QRect(160, 300, 131, 23));
        data = new QPlainTextEdit(frame_3);
        data->setObjectName(QStringLiteral("data"));
        data->setGeometry(QRect(20, 60, 271, 241));
        savenew = new QPushButton(frame_3);
        savenew->setObjectName(QStringLiteral("savenew"));
        savenew->setGeometry(QRect(20, 300, 111, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(action);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action->setText(QApplication::translate("MainWindow", "\320\235\320\276\320\262\321\213\320\271 \321\202\320\270\320\277 \320\276\320\261\321\212\320\265\320\272\321\202\320\260", 0));
        finish->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\236\320\261\321\212\320\265\320\272\321\202", 0));
        label->setText(QApplication::translate("MainWindow", "\320\242\320\270\320\277", 0));
        label_2->setText(QApplication::translate("MainWindow", "\320\230\320\274\321\217", 0));
        pushButton->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\277\320\276\320\264\320\276\320\261\321\212\320\265\320\272\321\202", 0));
        label_3->setText(QApplication::translate("MainWindow", "\320\230\320\274\321\217 \320\236\320\261\321\212\320\265\320\272\321\202\320\260", 0));
        createbase->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\261\320\260\320\267\321\203", 0));
        label_4->setText(QApplication::translate("MainWindow", "\320\242\320\270\320\277", 0));
        label_6->setText(QApplication::translate("MainWindow", "\320\230\320\274\321\217", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", 0));
        label_5->setText(QApplication::translate("MainWindow", "\320\242\320\265\320\272\321\203\321\211\320\260\321\217 \320\261\320\260\320\267\320\260:", 0));
        Curbase->setText(QApplication::translate("MainWindow", "\320\235\320\265 \320\267\320\260\320\264\320\260\320\275\320\260", 0));
        label_7->setText(QApplication::translate("MainWindow", "\320\242\320\270\320\277:", 0));
        Curbasetipe->setText(QApplication::translate("MainWindow", "\320\235\320\265 \320\267\320\260\320\264\320\260\320\275", 0));
        adddata->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\215\320\273\320\265\320\274\320\265\320\275\321\202", 0));
        data->setPlainText(QString());
        savenew->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\320\234\320\265\320\275\321\216", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

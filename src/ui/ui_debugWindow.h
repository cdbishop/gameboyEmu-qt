/********************************************************************************
** Form generated from reading UI file 'debugWindowjyeZII.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DEBUGWINDOWJYEZII_H
#define DEBUGWINDOWJYEZII_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QTextEdit *textEdit;
    QPushButton *btn_Next;
    QPushButton *btn_Run;
    QHBoxLayout *horizontalLayout_2;
    QFrame *frame_2;
    QLabel *lblRegA;
    QLineEdit *lineEditRegA;
    QLineEdit *lineEditRegB;
    QLabel *lblRegB;
    QLabel *lblRegC;
    QLineEdit *lineEditRegC;
    QLineEdit *lineEditRegD;
    QLabel *lblRegD;
    QLineEdit *lineEditRegE;
    QLabel *lblRegE;
    QLineEdit *lineEditRegH;
    QLabel *lblRegH;
    QLineEdit *lineEditRegL;
    QLabel *lblRegL;
    QLineEdit *lineEditRegFlag;
    QLabel *lblRegFlag;
    QLabel *lblRegPC;
    QLineEdit *lineEditRegPC;
    QLabel *lblRegSP;
    QLineEdit *lineEditRegSP;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(832, 589);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        textEdit = new QTextEdit(frame);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(0, 0, 401, 501));
        textEdit->setReadOnly(true);
        textEdit->setAcceptRichText(false);
        btn_Next = new QPushButton(frame);
        btn_Next->setObjectName(QStringLiteral("btn_Next"));
        btn_Next->setGeometry(QRect(0, 510, 31, 23));
        btn_Run = new QPushButton(frame);
        btn_Run->setObjectName(QStringLiteral("btn_Run"));
        btn_Run->setGeometry(QRect(40, 510, 31, 23));

        horizontalLayout->addWidget(frame);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        lblRegA = new QLabel(frame_2);
        lblRegA->setObjectName(QStringLiteral("lblRegA"));
        lblRegA->setGeometry(QRect(10, 20, 47, 13));
        lineEditRegA = new QLineEdit(frame_2);
        lineEditRegA->setObjectName(QStringLiteral("lineEditRegA"));
        lineEditRegA->setGeometry(QRect(20, 20, 31, 20));
        lineEditRegB = new QLineEdit(frame_2);
        lineEditRegB->setObjectName(QStringLiteral("lineEditRegB"));
        lineEditRegB->setGeometry(QRect(20, 50, 31, 20));
        lblRegB = new QLabel(frame_2);
        lblRegB->setObjectName(QStringLiteral("lblRegB"));
        lblRegB->setGeometry(QRect(10, 50, 16, 16));
        lblRegC = new QLabel(frame_2);
        lblRegC->setObjectName(QStringLiteral("lblRegC"));
        lblRegC->setGeometry(QRect(10, 80, 16, 16));
        lineEditRegC = new QLineEdit(frame_2);
        lineEditRegC->setObjectName(QStringLiteral("lineEditRegC"));
        lineEditRegC->setGeometry(QRect(20, 80, 31, 20));
        lineEditRegD = new QLineEdit(frame_2);
        lineEditRegD->setObjectName(QStringLiteral("lineEditRegD"));
        lineEditRegD->setGeometry(QRect(20, 110, 31, 20));
        lblRegD = new QLabel(frame_2);
        lblRegD->setObjectName(QStringLiteral("lblRegD"));
        lblRegD->setGeometry(QRect(10, 110, 16, 16));
        lineEditRegE = new QLineEdit(frame_2);
        lineEditRegE->setObjectName(QStringLiteral("lineEditRegE"));
        lineEditRegE->setGeometry(QRect(20, 140, 31, 20));
        lblRegE = new QLabel(frame_2);
        lblRegE->setObjectName(QStringLiteral("lblRegE"));
        lblRegE->setGeometry(QRect(10, 140, 16, 16));
        lineEditRegH = new QLineEdit(frame_2);
        lineEditRegH->setObjectName(QStringLiteral("lineEditRegH"));
        lineEditRegH->setGeometry(QRect(20, 170, 31, 20));
        lblRegH = new QLabel(frame_2);
        lblRegH->setObjectName(QStringLiteral("lblRegH"));
        lblRegH->setGeometry(QRect(10, 170, 16, 16));
        lineEditRegL = new QLineEdit(frame_2);
        lineEditRegL->setObjectName(QStringLiteral("lineEditRegL"));
        lineEditRegL->setGeometry(QRect(20, 200, 31, 20));
        lblRegL = new QLabel(frame_2);
        lblRegL->setObjectName(QStringLiteral("lblRegL"));
        lblRegL->setGeometry(QRect(10, 200, 16, 16));
        lineEditRegFlag = new QLineEdit(frame_2);
        lineEditRegFlag->setObjectName(QStringLiteral("lineEditRegFlag"));
        lineEditRegFlag->setGeometry(QRect(110, 20, 31, 20));
        lblRegFlag = new QLabel(frame_2);
        lblRegFlag->setObjectName(QStringLiteral("lblRegFlag"));
        lblRegFlag->setGeometry(QRect(80, 20, 31, 16));
        lblRegPC = new QLabel(frame_2);
        lblRegPC->setObjectName(QStringLiteral("lblRegPC"));
        lblRegPC->setGeometry(QRect(180, 20, 31, 16));
        lineEditRegPC = new QLineEdit(frame_2);
        lineEditRegPC->setObjectName(QStringLiteral("lineEditRegPC"));
        lineEditRegPC->setGeometry(QRect(210, 20, 31, 20));
        lblRegSP = new QLabel(frame_2);
        lblRegSP->setObjectName(QStringLiteral("lblRegSP"));
        lblRegSP->setGeometry(QRect(180, 60, 31, 16));
        lineEditRegSP = new QLineEdit(frame_2);
        lineEditRegSP->setObjectName(QStringLiteral("lineEditRegSP"));
        lineEditRegSP->setGeometry(QRect(210, 60, 31, 20));

        horizontalLayout_2->addWidget(frame_2);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 832, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        btn_Next->setText(QApplication::translate("MainWindow", ">", nullptr));
        btn_Run->setText(QApplication::translate("MainWindow", ">>", nullptr));
        lblRegA->setText(QApplication::translate("MainWindow", "A", nullptr));
        lblRegB->setText(QApplication::translate("MainWindow", "B", nullptr));
        lblRegC->setText(QApplication::translate("MainWindow", "C", nullptr));
        lblRegD->setText(QApplication::translate("MainWindow", "D", nullptr));
        lblRegE->setText(QApplication::translate("MainWindow", "E", nullptr));
        lblRegH->setText(QApplication::translate("MainWindow", "H", nullptr));
        lblRegL->setText(QApplication::translate("MainWindow", "L", nullptr));
        lblRegFlag->setText(QApplication::translate("MainWindow", "Flag", nullptr));
        lblRegPC->setText(QApplication::translate("MainWindow", "PC", nullptr));
        lblRegSP->setText(QApplication::translate("MainWindow", "SP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DEBUGWINDOWJYEZII_H

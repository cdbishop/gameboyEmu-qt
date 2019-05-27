/********************************************************************************
** Form generated from reading UI file 'debugWindowlSCfsz.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DEBUGWINDOWLSCFSZ_H
#define DEBUGWINDOWLSCFSZ_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QPushButton *btn_Next;
    QPushButton *btn_Run;
    QListWidget *lst_History;
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
    QLineEdit *lineEditRegBC;
    QLabel *lblRegBC;
    QLineEdit *lineEditRegDE;
    QLabel *lblRegDE;
    QLabel *lblRegHL;
    QLineEdit *lineEditRegHL;
    QGroupBox *groupBox_debugSection;
    QLabel *lbl_breakOnPC;
    QLineEdit *lineEdit_BreakPCValue;
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
        btn_Next = new QPushButton(frame);
        btn_Next->setObjectName(QStringLiteral("btn_Next"));
        btn_Next->setGeometry(QRect(0, 510, 31, 23));
        btn_Run = new QPushButton(frame);
        btn_Run->setObjectName(QStringLiteral("btn_Run"));
        btn_Run->setGeometry(QRect(40, 510, 31, 23));
        lst_History = new QListWidget(frame);
        lst_History->setObjectName(QStringLiteral("lst_History"));
        lst_History->setGeometry(QRect(0, 0, 401, 501));

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
        lineEditRegA->setReadOnly(true);
        lineEditRegB = new QLineEdit(frame_2);
        lineEditRegB->setObjectName(QStringLiteral("lineEditRegB"));
        lineEditRegB->setGeometry(QRect(20, 50, 31, 20));
        lineEditRegB->setReadOnly(true);
        lblRegB = new QLabel(frame_2);
        lblRegB->setObjectName(QStringLiteral("lblRegB"));
        lblRegB->setGeometry(QRect(10, 50, 16, 16));
        lblRegC = new QLabel(frame_2);
        lblRegC->setObjectName(QStringLiteral("lblRegC"));
        lblRegC->setGeometry(QRect(10, 80, 16, 16));
        lineEditRegC = new QLineEdit(frame_2);
        lineEditRegC->setObjectName(QStringLiteral("lineEditRegC"));
        lineEditRegC->setGeometry(QRect(20, 80, 31, 20));
        lineEditRegC->setReadOnly(true);
        lineEditRegD = new QLineEdit(frame_2);
        lineEditRegD->setObjectName(QStringLiteral("lineEditRegD"));
        lineEditRegD->setGeometry(QRect(20, 110, 31, 20));
        lineEditRegD->setReadOnly(true);
        lblRegD = new QLabel(frame_2);
        lblRegD->setObjectName(QStringLiteral("lblRegD"));
        lblRegD->setGeometry(QRect(10, 110, 16, 16));
        lineEditRegE = new QLineEdit(frame_2);
        lineEditRegE->setObjectName(QStringLiteral("lineEditRegE"));
        lineEditRegE->setGeometry(QRect(20, 140, 31, 20));
        lineEditRegE->setReadOnly(true);
        lblRegE = new QLabel(frame_2);
        lblRegE->setObjectName(QStringLiteral("lblRegE"));
        lblRegE->setGeometry(QRect(10, 140, 16, 16));
        lineEditRegH = new QLineEdit(frame_2);
        lineEditRegH->setObjectName(QStringLiteral("lineEditRegH"));
        lineEditRegH->setGeometry(QRect(20, 170, 31, 20));
        lineEditRegH->setReadOnly(true);
        lblRegH = new QLabel(frame_2);
        lblRegH->setObjectName(QStringLiteral("lblRegH"));
        lblRegH->setGeometry(QRect(10, 170, 16, 16));
        lineEditRegL = new QLineEdit(frame_2);
        lineEditRegL->setObjectName(QStringLiteral("lineEditRegL"));
        lineEditRegL->setGeometry(QRect(20, 200, 31, 20));
        lineEditRegL->setReadOnly(true);
        lblRegL = new QLabel(frame_2);
        lblRegL->setObjectName(QStringLiteral("lblRegL"));
        lblRegL->setGeometry(QRect(10, 200, 16, 16));
        lineEditRegFlag = new QLineEdit(frame_2);
        lineEditRegFlag->setObjectName(QStringLiteral("lineEditRegFlag"));
        lineEditRegFlag->setGeometry(QRect(110, 20, 31, 20));
        lineEditRegFlag->setReadOnly(true);
        lblRegFlag = new QLabel(frame_2);
        lblRegFlag->setObjectName(QStringLiteral("lblRegFlag"));
        lblRegFlag->setGeometry(QRect(80, 20, 31, 16));
        lblRegPC = new QLabel(frame_2);
        lblRegPC->setObjectName(QStringLiteral("lblRegPC"));
        lblRegPC->setGeometry(QRect(80, 50, 31, 16));
        lineEditRegPC = new QLineEdit(frame_2);
        lineEditRegPC->setObjectName(QStringLiteral("lineEditRegPC"));
        lineEditRegPC->setGeometry(QRect(110, 50, 41, 20));
        lineEditRegPC->setReadOnly(true);
        lblRegSP = new QLabel(frame_2);
        lblRegSP->setObjectName(QStringLiteral("lblRegSP"));
        lblRegSP->setGeometry(QRect(80, 80, 31, 16));
        lineEditRegSP = new QLineEdit(frame_2);
        lineEditRegSP->setObjectName(QStringLiteral("lineEditRegSP"));
        lineEditRegSP->setGeometry(QRect(110, 80, 41, 20));
        lineEditRegSP->setReadOnly(true);
        lineEditRegBC = new QLineEdit(frame_2);
        lineEditRegBC->setObjectName(QStringLiteral("lineEditRegBC"));
        lineEditRegBC->setGeometry(QRect(220, 20, 41, 20));
        lineEditRegBC->setReadOnly(true);
        lblRegBC = new QLabel(frame_2);
        lblRegBC->setObjectName(QStringLiteral("lblRegBC"));
        lblRegBC->setGeometry(QRect(190, 20, 31, 16));
        lineEditRegDE = new QLineEdit(frame_2);
        lineEditRegDE->setObjectName(QStringLiteral("lineEditRegDE"));
        lineEditRegDE->setGeometry(QRect(220, 50, 41, 20));
        lineEditRegDE->setReadOnly(true);
        lblRegDE = new QLabel(frame_2);
        lblRegDE->setObjectName(QStringLiteral("lblRegDE"));
        lblRegDE->setGeometry(QRect(190, 50, 31, 16));
        lblRegHL = new QLabel(frame_2);
        lblRegHL->setObjectName(QStringLiteral("lblRegHL"));
        lblRegHL->setGeometry(QRect(190, 80, 31, 16));
        lineEditRegHL = new QLineEdit(frame_2);
        lineEditRegHL->setObjectName(QStringLiteral("lineEditRegHL"));
        lineEditRegHL->setGeometry(QRect(220, 80, 41, 20));
        lineEditRegHL->setReadOnly(true);
        groupBox_debugSection = new QGroupBox(frame_2);
        groupBox_debugSection->setObjectName(QStringLiteral("groupBox_debugSection"));
        groupBox_debugSection->setGeometry(QRect(10, 430, 381, 80));
        lbl_breakOnPC = new QLabel(groupBox_debugSection);
        lbl_breakOnPC->setObjectName(QStringLiteral("lbl_breakOnPC"));
        lbl_breakOnPC->setGeometry(QRect(10, 30, 71, 16));
        lineEdit_BreakPCValue = new QLineEdit(groupBox_debugSection);
        lineEdit_BreakPCValue->setObjectName(QStringLiteral("lineEdit_BreakPCValue"));
        lineEdit_BreakPCValue->setGeometry(QRect(70, 30, 41, 20));

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
        lblRegBC->setText(QApplication::translate("MainWindow", "BC", nullptr));
        lblRegDE->setText(QApplication::translate("MainWindow", "DE", nullptr));
        lblRegHL->setText(QApplication::translate("MainWindow", "HL", nullptr));
        groupBox_debugSection->setTitle(QApplication::translate("MainWindow", "Debug", nullptr));
        lbl_breakOnPC->setText(QApplication::translate("MainWindow", "Break on PC", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DEBUGWINDOWLSCFSZ_H

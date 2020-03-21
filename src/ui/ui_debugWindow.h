/********************************************************************************
** Form generated from reading UI file 'debugWindowYJOFKs.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DEBUGWINDOWYJOFKS_H
#define DEBUGWINDOWYJOFKS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
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
    QPushButton *btn_Pause;
    QListWidget *lst_rom;
    QComboBox *cmbo_RunSpeed;
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
    QComboBox *cmbo_BreakRegSelect;
    QLabel *lblBreakOnReg;
    QLabel *lbl_BreakRegVal;
    QLineEdit *lineEdit_BreakRegVal;
    QPushButton *btn_AddPCBreak;
    QPushButton *btn_AddRegBreak;
    QPushButton *btn_RemoveBreak;
    QTableWidget *tbl_Breaks;
    QCheckBox *chk_flagCarry;
    QCheckBox *chk_flagHalfCarry;
    QCheckBox *chk_flagSubOp;
    QCheckBox *chk_flagZero;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1103, 700);
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
        btn_Next->setGeometry(QRect(10, 340, 31, 23));
        btn_Run = new QPushButton(frame);
        btn_Run->setObjectName(QStringLiteral("btn_Run"));
        btn_Run->setGeometry(QRect(50, 340, 31, 23));
        lst_History = new QListWidget(frame);
        lst_History->setObjectName(QStringLiteral("lst_History"));
        lst_History->setGeometry(QRect(0, 0, 401, 331));
        btn_Pause = new QPushButton(frame);
        btn_Pause->setObjectName(QStringLiteral("btn_Pause"));
        btn_Pause->setGeometry(QRect(170, 340, 31, 23));
        lst_rom = new QListWidget(frame);
        lst_rom->setObjectName(QStringLiteral("lst_rom"));
        lst_rom->setGeometry(QRect(0, 390, 401, 241));
        cmbo_RunSpeed = new QComboBox(frame);
        cmbo_RunSpeed->addItem(QString());
        cmbo_RunSpeed->addItem(QString());
        cmbo_RunSpeed->setObjectName(QStringLiteral("cmbo_RunSpeed"));
        cmbo_RunSpeed->setGeometry(QRect(90, 340, 69, 22));

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
        lblRegPC->setGeometry(QRect(190, 170, 31, 16));
        lineEditRegPC = new QLineEdit(frame_2);
        lineEditRegPC->setObjectName(QStringLiteral("lineEditRegPC"));
        lineEditRegPC->setGeometry(QRect(220, 170, 41, 20));
        lineEditRegPC->setReadOnly(true);
        lblRegSP = new QLabel(frame_2);
        lblRegSP->setObjectName(QStringLiteral("lblRegSP"));
        lblRegSP->setGeometry(QRect(190, 200, 31, 16));
        lineEditRegSP = new QLineEdit(frame_2);
        lineEditRegSP->setObjectName(QStringLiteral("lineEditRegSP"));
        lineEditRegSP->setGeometry(QRect(220, 200, 41, 20));
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
        groupBox_debugSection->setGeometry(QRect(10, 359, 381, 171));
        lbl_breakOnPC = new QLabel(groupBox_debugSection);
        lbl_breakOnPC->setObjectName(QStringLiteral("lbl_breakOnPC"));
        lbl_breakOnPC->setGeometry(QRect(10, 20, 71, 16));
        lineEdit_BreakPCValue = new QLineEdit(groupBox_debugSection);
        lineEdit_BreakPCValue->setObjectName(QStringLiteral("lineEdit_BreakPCValue"));
        lineEdit_BreakPCValue->setGeometry(QRect(100, 20, 41, 20));
        cmbo_BreakRegSelect = new QComboBox(groupBox_debugSection);
        cmbo_BreakRegSelect->addItem(QString());
        cmbo_BreakRegSelect->addItem(QString());
        cmbo_BreakRegSelect->addItem(QString());
        cmbo_BreakRegSelect->addItem(QString());
        cmbo_BreakRegSelect->addItem(QString());
        cmbo_BreakRegSelect->addItem(QString());
        cmbo_BreakRegSelect->addItem(QString());
        cmbo_BreakRegSelect->addItem(QString());
        cmbo_BreakRegSelect->addItem(QString());
        cmbo_BreakRegSelect->addItem(QString());
        cmbo_BreakRegSelect->setObjectName(QStringLiteral("cmbo_BreakRegSelect"));
        cmbo_BreakRegSelect->setGeometry(QRect(100, 40, 41, 22));
        lblBreakOnReg = new QLabel(groupBox_debugSection);
        lblBreakOnReg->setObjectName(QStringLiteral("lblBreakOnReg"));
        lblBreakOnReg->setGeometry(QRect(10, 40, 91, 16));
        lbl_BreakRegVal = new QLabel(groupBox_debugSection);
        lbl_BreakRegVal->setObjectName(QStringLiteral("lbl_BreakRegVal"));
        lbl_BreakRegVal->setGeometry(QRect(150, 41, 31, 16));
        lineEdit_BreakRegVal = new QLineEdit(groupBox_debugSection);
        lineEdit_BreakRegVal->setObjectName(QStringLiteral("lineEdit_BreakRegVal"));
        lineEdit_BreakRegVal->setGeometry(QRect(180, 40, 41, 20));
        btn_AddPCBreak = new QPushButton(groupBox_debugSection);
        btn_AddPCBreak->setObjectName(QStringLiteral("btn_AddPCBreak"));
        btn_AddPCBreak->setEnabled(false);
        btn_AddPCBreak->setGeometry(QRect(230, 20, 41, 23));
        btn_AddRegBreak = new QPushButton(groupBox_debugSection);
        btn_AddRegBreak->setObjectName(QStringLiteral("btn_AddRegBreak"));
        btn_AddRegBreak->setEnabled(false);
        btn_AddRegBreak->setGeometry(QRect(230, 40, 41, 23));
        btn_RemoveBreak = new QPushButton(groupBox_debugSection);
        btn_RemoveBreak->setObjectName(QStringLiteral("btn_RemoveBreak"));
        btn_RemoveBreak->setEnabled(false);
        btn_RemoveBreak->setGeometry(QRect(324, 70, 51, 23));
        tbl_Breaks = new QTableWidget(groupBox_debugSection);
        if (tbl_Breaks->columnCount() < 2)
            tbl_Breaks->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbl_Breaks->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbl_Breaks->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tbl_Breaks->setObjectName(QStringLiteral("tbl_Breaks"));
        tbl_Breaks->setGeometry(QRect(10, 70, 311, 91));
        tbl_Breaks->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbl_Breaks->setSelectionMode(QAbstractItemView::SingleSelection);
        tbl_Breaks->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbl_Breaks->horizontalHeader()->setDefaultSectionSize(154);
        tbl_Breaks->horizontalHeader()->setHighlightSections(true);
        chk_flagCarry = new QCheckBox(frame_2);
        chk_flagCarry->setObjectName(QStringLiteral("chk_flagCarry"));
        chk_flagCarry->setGeometry(QRect(90, 50, 70, 17));
        chk_flagHalfCarry = new QCheckBox(frame_2);
        chk_flagHalfCarry->setObjectName(QStringLiteral("chk_flagHalfCarry"));
        chk_flagHalfCarry->setGeometry(QRect(90, 80, 70, 17));
        chk_flagSubOp = new QCheckBox(frame_2);
        chk_flagSubOp->setObjectName(QStringLiteral("chk_flagSubOp"));
        chk_flagSubOp->setGeometry(QRect(90, 110, 70, 17));
        chk_flagZero = new QCheckBox(frame_2);
        chk_flagZero->setObjectName(QStringLiteral("chk_flagZero"));
        chk_flagZero->setGeometry(QRect(90, 140, 70, 17));

        horizontalLayout_2->addWidget(frame_2);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1103, 21));
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
        btn_Pause->setText(QApplication::translate("MainWindow", "||", nullptr));
        cmbo_RunSpeed->setItemText(0, QApplication::translate("MainWindow", "Debug", nullptr));
        cmbo_RunSpeed->setItemText(1, QApplication::translate("MainWindow", "Full", nullptr));

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
        cmbo_BreakRegSelect->setItemText(0, QApplication::translate("MainWindow", "A", nullptr));
        cmbo_BreakRegSelect->setItemText(1, QApplication::translate("MainWindow", "B", nullptr));
        cmbo_BreakRegSelect->setItemText(2, QApplication::translate("MainWindow", "C", nullptr));
        cmbo_BreakRegSelect->setItemText(3, QApplication::translate("MainWindow", "D", nullptr));
        cmbo_BreakRegSelect->setItemText(4, QApplication::translate("MainWindow", "E", nullptr));
        cmbo_BreakRegSelect->setItemText(5, QApplication::translate("MainWindow", "H", nullptr));
        cmbo_BreakRegSelect->setItemText(6, QApplication::translate("MainWindow", "L", nullptr));
        cmbo_BreakRegSelect->setItemText(7, QApplication::translate("MainWindow", "BC", nullptr));
        cmbo_BreakRegSelect->setItemText(8, QApplication::translate("MainWindow", "DE", nullptr));
        cmbo_BreakRegSelect->setItemText(9, QApplication::translate("MainWindow", "HL", nullptr));

        lblBreakOnReg->setText(QApplication::translate("MainWindow", "Break on Register", nullptr));
        lbl_BreakRegVal->setText(QApplication::translate("MainWindow", "Value", nullptr));
        btn_AddPCBreak->setText(QApplication::translate("MainWindow", "Add", nullptr));
        btn_AddRegBreak->setText(QApplication::translate("MainWindow", "Add", nullptr));
        btn_RemoveBreak->setText(QApplication::translate("MainWindow", "Remove", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tbl_Breaks->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Reg", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tbl_Breaks->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Value", nullptr));
        chk_flagCarry->setText(QApplication::translate("MainWindow", "Carry", nullptr));
        chk_flagHalfCarry->setText(QApplication::translate("MainWindow", "Half Carry", nullptr));
        chk_flagSubOp->setText(QApplication::translate("MainWindow", "Sub", nullptr));
        chk_flagZero->setText(QApplication::translate("MainWindow", "Zero", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DEBUGWINDOWYJOFKS_H

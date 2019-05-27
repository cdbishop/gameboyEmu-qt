#include "DebugWindow.hpp"

#include "Registers.hpp"

#include <QtUiTools/quiloader.h>
#include <QtCore/qfile.h>
#include <qboxlayout.h>
#include <qpushbutton.h>

#include "spdlog/spdlog.h"

#include <sstream>

template<typename T>
QString FormatValueHex(const T& value) {
  return QString("%1").arg(value, 0, 16);
}

DebugWindow::DebugWindow(QApplication* app, QWidget *parent)
  :QMainWindow(parent),
  _app(app)
{
  ui.setupUi(this);
  connect(ui.btn_Next, &QPushButton::clicked, this, &DebugWindow::onNextBtnClicked);
  connect(ui.btn_Run, &QPushButton::clicked, this, &DebugWindow::OnRunBtnClicked);
  connect(ui.lineEdit_BreakPCValue, &QLineEdit::editingFinished, this, &DebugWindow::OnPCBreakEditingFinnished);
  connect(ui.lineEdit_BreakRegVal, &QLineEdit::editingFinished, this, &DebugWindow::OnRegBreakEditingFinnished);
  connect(ui.btn_AddPCBreak, &QPushButton::clicked, this, &DebugWindow::OnPCBreakAdd);
  connect(ui.btn_AddRegBreak, &QPushButton::clicked, this, &DebugWindow::OnRegBreakAdd);
  connect(ui.tbl_Breaks, &QTableWidget::itemSelectionChanged, this, &DebugWindow::OnBreakSelected);
  connect(ui.btn_RemoveBreak, &QPushButton::clicked, this, &DebugWindow::OnBreakRemove);
}

void DebugWindow::UpdateState(const cpu::State& state)
{
  ui.lineEditRegA->setText(FormatValueHex(state._a));
  ui.lineEditRegB->setText(FormatValueHex(state._b));
  ui.lineEditRegC->setText(FormatValueHex(state._c));
  ui.lineEditRegD->setText(FormatValueHex(state._d));
  ui.lineEditRegE->setText(FormatValueHex(state._e));
  ui.lineEditRegFlag->setText(FormatValueHex(state._flag));
  ui.lineEditRegH->setText(FormatValueHex(state._h));
  ui.lineEditRegL->setText(FormatValueHex(state._l));
  ui.lineEditRegPC->setText(FormatValueHex(state._pc));
  ui.lineEditRegSP->setText(FormatValueHex(state._sp));

  ui.lineEditRegBC->setText(FormatValueHex(state.ReadRegister(Register16::BC)));
  ui.lineEditRegDE->setText(FormatValueHex(state.ReadRegister(Register16::DE)));
  ui.lineEditRegHL->setText(FormatValueHex(state.ReadRegister(Register16::HL)));

  //ui.textEdit->clear();
  //for (auto&& inst : state._history) {
  //  std::ostringstream ss;
  //  ss << inst;
  //  ui.textEdit->append(QString(ss.str().c_str()));
  //}
  ui.lst_History->clear();
  for (auto&& inst : state._history) {
    std::ostringstream ss;
    ss << inst;
    ui.lst_History->addItem(QString(ss.str().c_str()));
  }
}

void DebugWindow::onNextBtnClicked()
{
  spdlog::get("console")->debug("Next clicked!");
  emit Next();
}

void DebugWindow::OnRunBtnClicked()
{
  spdlog::get("console")->debug("Run clicked!");
  emit Run();
}

void DebugWindow::OnPCBreakEditingFinnished()
{
  if (ui.lineEdit_BreakPCValue->text().length() > 0) {
    ui.btn_AddPCBreak->setEnabled(true);
  }
  else {
    ui.btn_AddPCBreak->setEnabled(false);
  }
}

void DebugWindow::OnRegBreakEditingFinnished()
{
  if (ui.lineEdit_BreakRegVal->text().length() > 0) {
    ui.btn_AddRegBreak->setEnabled(true);
  }
  else {
    ui.btn_AddRegBreak->setEnabled(false);
  }
}

void DebugWindow::OnPCBreakAdd()
{
  QString txt = std::move(ui.lineEdit_BreakPCValue->text());
  bool ok = false;
  unsigned int targetPC = txt.toUInt(&ok, 16);
  if (ok) {
    spdlog::get("console")->debug("setting pc break point to {}", targetPC);
    emit SetPCBreak(targetPC);
  }
  else {
    spdlog::get("console")->debug("failed to parse input as hex: {}", txt.toStdString());
  }

  ui.tbl_Breaks->insertRow(ui.tbl_Breaks->rowCount());
  ui.tbl_Breaks->setItem(ui.tbl_Breaks->rowCount() - 1, 0, new QTableWidgetItem("PC"));
  ui.tbl_Breaks->setItem(ui.tbl_Breaks->rowCount() - 1, 1, new QTableWidgetItem(txt));
}

void DebugWindow::OnRegBreakAdd()
{
  QString reg = ui.cmbo_BreakRegSelect->itemText(ui.cmbo_BreakRegSelect->currentIndex());
  QString value = std::move(ui.lineEdit_BreakRegVal->text());
  bool ok = false;
  unsigned int targetValue = value.toUInt(&ok, 16);
  if (ok) {
    spdlog::get("console")->debug("setting reg break point on {} to {}", reg.toStdString(), targetValue);
    emit SetRegBreak(reg.toStdString(), targetValue);
  }
  else {
    spdlog::get("console")->debug("failed to parse input as hex: {}", value.toStdString());
  }

  ui.tbl_Breaks->insertRow(ui.tbl_Breaks->rowCount());
  ui.tbl_Breaks->setItem(ui.tbl_Breaks->rowCount() - 1, 0, new QTableWidgetItem(reg));
  ui.tbl_Breaks->setItem(ui.tbl_Breaks->rowCount() - 1, 1, new QTableWidgetItem(value));
}

void DebugWindow::OnBreakSelected()
{
  auto item = ui.tbl_Breaks->currentItem();
  ui.btn_RemoveBreak->setEnabled(item != nullptr);
}

void DebugWindow::OnBreakRemove()
{
  auto item = ui.tbl_Breaks->currentItem();
  ui.tbl_Breaks->removeRow(item->row());
}

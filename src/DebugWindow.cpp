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
  spdlog::get("console")->debug("settings pc break point");
  emit SetPCBreak();
}

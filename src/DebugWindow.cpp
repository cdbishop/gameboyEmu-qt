#include "DebugWindow.hpp"

#include <QtUiTools/quiloader.h>
#include <QtCore/qfile.h>

#include <qboxlayout.h>
#include <qpushbutton.h>

#include "spdlog/spdlog.h"

#include <sstream>

DebugWindow::DebugWindow(QApplication* app, QWidget *parent)
  :QMainWindow(parent),
  _app(app)
{
  ui.setupUi(this);
  connect(ui.btn_Next, &QPushButton::clicked, this, &DebugWindow::onNextBtnClicked);
  connect(ui.btn_Run, &QPushButton::clicked, this, &DebugWindow::OnRunBtnClicked);
}

void DebugWindow::UpdateState(const cpu::State& state)
{
  ui.lineEditRegA->setText(QString("%1").arg(state._a, 0, 16));
  ui.lineEditRegB->setText(QString("%1").arg(state._b, 0, 16));
  ui.lineEditRegC->setText(QString("%1").arg(state._c, 0, 16));
  ui.lineEditRegD->setText(QString("%1").arg(state._d, 0, 16));
  ui.lineEditRegE->setText(QString("%1").arg(state._e, 0, 16));
  ui.lineEditRegFlag->setText(QString("%1").arg(state._flag, 0, 16));
  ui.lineEditRegH->setText(QString("%1").arg(state._h, 0, 16));
  ui.lineEditRegL->setText(QString("%1").arg(state._l, 0, 16));
  ui.lineEditRegPC->setText(QString("%1").arg(state._pc, 0, 16));
  ui.lineEditRegSP->setText(QString("%1").arg(state._sp, 0, 16));

  ui.textEdit->clear();
  for (auto&& inst : state._history) {
    std::ostringstream ss;
    ss << inst;
    ui.textEdit->append(QString(ss.str().c_str()));
  }
}

void DebugWindow::onNextBtnClicked()
{
  spdlog::get("console")->debug("Next clicked!");
  
}

void DebugWindow::OnRunBtnClicked()
{
  spdlog::get("console")->debug("Run clicked!");
}

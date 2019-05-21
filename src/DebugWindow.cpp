#include "DebugWindow.hpp"

#include <QtUiTools/quiloader.h>
#include <QtCore/qfile.h>

#include <qboxlayout.h>
#include <qpushbutton.h>

#include "spdlog/spdlog.h"

DebugWindow::DebugWindow(QWidget *parent)
  :QMainWindow(parent)
{
  ui.setupUi(this);
  connect(ui.btn_Next, &QPushButton::clicked, this, &DebugWindow::onNextBtnClicked);
}

void DebugWindow::onNextBtnClicked() {
  spdlog::get("console")->debug("Next clicked!");
}

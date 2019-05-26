#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qmenu.h>

#include "ui/ui_debugWindow.h"

#include "CpuState.hpp"
#include "CpuStateNotifierQt.hpp"

class DebugWindow : public QMainWindow
{
public:
  DebugWindow(QApplication* app, QWidget *parent = 0);

  void UpdateState(const cpu::State& state);

private:
  void onNextBtnClicked();
  void OnRunBtnClicked();

private:
  Ui::MainWindow ui;
  QApplication* _app;
};


#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qmenu.h>

#include "ui/ui_debugWindow.h"

#include "CpuState.hpp"
#include "CpuStateNotifierQt.hpp"

class DebugWindow : public QMainWindow
{
  Q_OBJECT
public:
  DebugWindow(QApplication* app, QWidget *parent = 0);

  void UpdateState(const cpu::State& state);

private:
  void onNextBtnClicked();
  void OnRunBtnClicked();
  void OnPCBreakEditingFinnished();
  void OnRegBreakEditingFinnished();
  void OnPCBreakAdd();
  void OnRegBreakAdd();
  void OnBreakSelected();
  void OnBreakRemove();

signals:
  void Next();
  void Run();
  void SetPCBreak(unsigned int pcTarget);
  void SetRegBreak(std::string reg, unsigned int value);

private:
  Ui::MainWindow ui;
  QApplication* _app;
};


#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qmenu.h>

#include "ui/ui_debugWindow.h"

class DebugWindow : public QMainWindow
{
public:
  DebugWindow(QWidget *parent = 0);

private:
  void onNextBtnClicked();

private:
  Ui::MainWindow ui;
};


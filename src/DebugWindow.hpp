#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qmenu.h>

class DebugWindow : public QWidget
{
public:
  DebugWindow(QWidget* parent = 0);
  ~DebugWindow();
};


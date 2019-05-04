#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qmenu.h>

#include "SFMLCanvasTest.hpp"

class RenderWindow : public QWidget
{
public:
  RenderWindow(QWidget* parent = 0);
  ~RenderWindow();

private slots:
  void OpenFile();

private:
  SFMLCanvasTest* _canvasTest;
  
  QMenuBar* _fileMenu;
  QAction* _openAction;
};


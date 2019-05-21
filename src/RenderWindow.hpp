#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qmenu.h>

#include "SFMLCanvasTest.hpp"

class Cart;
class Cpu;

class RenderWindow : public QWidget
{
public:
  RenderWindow(QWidget* parent = 0);
  ~RenderWindow();

  void CpuStep();
  void CpuRun();

private slots:
  void OpenFile();

private:
  SFMLCanvasTest* _canvasTest;
  
  QMenuBar* _fileMenu;
  QAction* _openAction;

  std::shared_ptr<Cart> _cart;
  std::shared_ptr<Cpu> _cpu;
};


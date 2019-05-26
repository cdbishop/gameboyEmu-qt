#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qmenu.h>

#include "SFMLCanvasTest.hpp"
#include "CpuStateNotifierQt.hpp"

class Cart;
class Cpu;

class RenderWindow : public QWidget
{
public:
  RenderWindow(std::unique_ptr<CpuStateNotifierQt> notifier, QWidget* parent = 0);
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
  std::unique_ptr<CpuStateNotifierQt> _stateNotifier;
};


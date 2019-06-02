#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qmenu.h>

#include "SFMLCanvasTest.hpp"
#include "CpuStateNotifierQt.hpp"

class Cart;
class Cpu;
class DebugWindow;

class RenderWindow : public QWidget
{
public:
  RenderWindow(std::unique_ptr<CpuStateNotifierQt> notifier, DebugWindow* debugWindow, QWidget* parent = 0);
  ~RenderWindow();

  void CpuStep();
  void CpuRun();

private slots:
  void OpenFile();
  void OnNext();
  void OnSetPCBreak(unsigned int pcTarget);
  void OnSetRegBreak(std::string regValue, unsigned int targetValue);
  void OnRemovePCBreak();
  void OnRemoveRegBreak(std::string regValue);

private:
  SFMLCanvasTest* _canvasTest;
  
  QMenuBar* _fileMenu;
  QAction* _openAction;

  DebugWindow* _debugWindow;

  std::shared_ptr<Cart> _cart;
  std::shared_ptr<Cpu> _cpu;
  std::unique_ptr<CpuStateNotifierQt> _stateNotifier;
};


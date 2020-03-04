#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qmenu.h>

#include "SFMLCanvasTest.hpp"
#include "CpuStateNotifierQt.hpp"
#include "CpuManager.hpp"

class Cart;
class Cpu;
class DebugWindow;

class RenderWindow : public QWidget
{
public:
  RenderWindow(std::shared_ptr<cpu::Manager> cpuManager, DebugWindow* debugWindow, QWidget* parent = 0);
  ~RenderWindow();

  void CpuStep();
  void CpuRun();
  void CpuPause();

private slots:
  void OpenFile();
  void OnNext();
  void OnSetPCBreak(unsigned int pcTarget);
  void OnSetRegBreak(const std::string& regValue, unsigned int targetValue);
  void OnRemovePCBreak();
  void OnRemoveRegBreak(const std::string& regValue);

private:
  SFMLCanvasTest* _canvasTest;
  
  QMenuBar* _fileMenu;
  QAction* _openAction;

  DebugWindow* _debugWindow;

  std::shared_ptr<cpu::Manager> _cpuManager;
  std::unique_ptr<CpuStateNotifierQt> _stateNotifier;
};


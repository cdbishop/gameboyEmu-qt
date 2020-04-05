#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qmenu.h>

//#include "SFMLCanvasTest.hpp"
#include "SFMLBuffer.hpp"
#include "CpuStateNotifierQt.hpp"
#include "CpuManager.hpp"
#include "RunSpeed.hpp"
#include "gpu/ScreenData.hpp"

class Cart;
class Cpu;
class DebugWindow;

class RenderWindow : public QWidget
{
public:
  RenderWindow(std::shared_ptr<cpu::Manager> cpuManager, DebugWindow* debugWindow, QWidget* parent = 0);
  ~RenderWindow();

  void CpuStep();
  void CpuRun(RunSpeed speed);
  void CpuPause();

  void SetStateNotifier(std::shared_ptr<CpuStateNotifierQt> notifier);

private:
  void OnNotifyScreenDataSignal(const gpu::ScreenData& data);

private slots:
  void OpenFile();
  void OnNext();
  void OnSetPCBreak(unsigned int pcTarget);
  void OnSetRegBreak(const std::string& regValue, unsigned int targetValue);
  void OnRemovePCBreak();
  void OnRemoveRegBreak(const std::string& regValue);

private:
  SFMLBuffer* _renderBuffer;
  
  QMenuBar* _fileMenu;
  QAction* _openAction;

  DebugWindow* _debugWindow;

  std::shared_ptr<cpu::Manager> _cpuManager;
  std::unique_ptr<CpuStateNotifierQt> _stateNotifier;
};


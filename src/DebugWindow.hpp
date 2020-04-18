#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qmenu.h>

#include "ui/ui_debugWindow.h"

#include "CpuState.hpp"
#include "CpuStateNotifierQt.hpp"
#include "RunSpeed.hpp"

#include <thread>
#include <mutex>
#include <set>

class DebugWindow : public QMainWindow
{
  Q_OBJECT
public:
  DebugWindow(QApplication* app, QWidget *parent = 0);

  void SetStateNotifier(std::shared_ptr<CpuStateNotifierQt> notifier);

  void UpdateState(const cpu::State& state, const cpu::StateHistory& history, const std::string& memory_dump);
  void UpdateRomData(const std::vector<Cpu::RomInstruction>& instructions);

  void SetState(const cpu::State& state);

  void OnNotifyStateSignal(const cpu::State& state, const cpu::StateHistory& history, const std::string& memory_dump);
  void OnNotifyRomDataSignal(const std::vector<Cpu::RomInstruction>& instructions);

private:
  void onNextBtnClicked();
  void OnRunBtnClicked();
  void OnPauseBtnClicked();
  void OnPCBreakEditingFinnished();
  void OnRegBreakEditingFinnished();
  void OnPCBreakAdd();
  void OnRegBreakAdd();
  void OnBreakSelected();
  void OnBreakRemove();
  void OnPreviousStateSelected(const QModelIndex& index);
  void OnRomInstructionDoubleClicked(const QModelIndex& index);

signals:
  void Next();
  void Run(RunSpeed speed);
  void Pause();
  void SetPCBreak(unsigned int pcTarget);
  void SetRegBreak(std::string reg, unsigned int value);
  void RemoveRegBreak(std::string reg);
  void RemovePCBreak();

private:
  Ui::MainWindow ui;
  QApplication* _app;
  cpu::StateHistory _cpuHistory;
  std::map<unsigned short, int> _pcIndexLookup;
  std::mutex _stateMutex;
  std::set<int> _pcBreakpoints;
};

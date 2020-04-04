#pragma once
#include <CpuStateNotifier.hpp>
#include "cpu/StateHistory.hpp"

#include <thread>
#include <condition_variable>

#include <qobject.h>

class DebugWindow;

class CpuStateNotifierQt final : public QObject, public CpuStateNotifier {
  Q_OBJECT
public:
  enum UpdateFlag {
    UpdateFlag_State = 1 << 1,
    UpdateFlag_RomData = 1 << 2
  };

  CpuStateNotifierQt(DebugWindow* window);

  void NotifyState(const cpu::State& state, std::shared_ptr<const cpu::StateHistory> history);
  void NotifyRomData(const std::vector<Cpu::RomInstruction>& instructions);

signals:
  void NotifyStateSignal(const cpu::State& state, const cpu::StateHistory& history);
  void NotifyRomDataSignal(const std::vector<Cpu::RomInstruction>& instructions);

private:
  void ThreadMain();

private:
  DebugWindow* _window;

  bool _threadRunning;  
  std::condition_variable _notifyCv;
  std::mutex _notifyMutex;
  bool _notified;

  cpu::State _nextState;
  cpu::StateHistory _nextStateHistory;
  std::vector<Cpu::RomInstruction> _nextInstructionState;

  std::thread _notifyThread;
  int _updateFlag;
};
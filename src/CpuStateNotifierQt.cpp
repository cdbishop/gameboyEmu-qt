#include "CpuStateNotifierQt.hpp"
#include "DebugWindow.hpp"

#include "CpuState.hpp"

#include <qmetatype.h>

CpuStateNotifierQt::CpuStateNotifierQt(DebugWindow* window)
  :QObject(),
   _window(window),
   _threadRunning(true),
   _notifyThread(&CpuStateNotifierQt::ThreadMain, this),
   _notified(false),
  _updateFlag(0)
{
  qRegisterMetaType<Cpu::RomInstruction>("CpuRomInstruction");
  qRegisterMetaType<cpu::State>("cpu::State");
  qRegisterMetaType<cpu::StateHistory>("cpu::StateHistory");
  qRegisterMetaType<std::vector<Cpu::RomInstruction>>("std::vector<Cpu::RomInstruction>");
}

void CpuStateNotifierQt::NotifyState(const cpu::State& state, const cpu::StateHistory& history)
{
  _updateFlag |= UpdateFlag_State;

  std::unique_lock lk(_notifyMutex);  
  _nextState = state;
  _nextStateHistory = history;
  _notified = true;
  _notifyCv.notify_one();
}

void CpuStateNotifierQt::NotifyRomData(const std::vector<Cpu::RomInstruction>& instructions)
{
  _updateFlag |= UpdateFlag_RomData;

  std::unique_lock lk(_notifyMutex);  
  _nextInstructionState = instructions;
  _notified = true;
  _notifyCv.notify_one();
}

void CpuStateNotifierQt::ThreadMain() {
  while (_threadRunning) {
    std::unique_lock lk(_notifyMutex);
    while (!_notified) {
      _notifyCv.wait(lk);
    }

    //TODO: emit signal here
    if (_updateFlag & UpdateFlag_State)
      emit NotifyStateSignal(_nextState, _nextStateHistory);

    if (_updateFlag & UpdateFlag_RomData)
      emit NotifyRomDataSignal(_nextInstructionState);

    _notified = false;
    _updateFlag = 0;
  }
}

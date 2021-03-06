#include "CpuStateNotifierQt.hpp"
#include "DebugWindow.hpp"

#include "CpuState.hpp"

#include <qmetatype.h>

Q_DECLARE_METATYPE(std::string);

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
  qRegisterMetaType<gpu::ScreenData>("gpu::ScreenData");
  qRegisterMetaType<cpu::StateHistory>("cpu::StateHistory");
  qRegisterMetaType<std::vector<Cpu::RomInstruction>>("std::vector<Cpu::RomInstruction>");
  qRegisterMetaType<gpu::TilesetDump>("gpu::TilesetDump");
  qRegisterMetaType<std::string>("std::string");
}

void CpuStateNotifierQt::NotifyState(const cpu::State& state, std::shared_ptr<const cpu::StateHistory> history,
  std::shared_ptr<MemoryController> memory_ctrl)
{
  std::unique_lock lk(_notifyMutex);
  _updateFlag |= UpdateFlag_State;

  _nextState = state;

  if (history) {
    _nextStateHistory = *history;
    _memory_dump = memory_ctrl->ToString();
  }

  _notified = true;
  _notifyCv.notify_one();
}

void CpuStateNotifierQt::NotifyRomData(const std::vector<Cpu::RomInstruction>& instructions)
{
  std::unique_lock lk(_notifyMutex);
  _updateFlag |= UpdateFlag_RomData;

 
  _nextInstructionState = instructions;
  _notified = true;
  _notifyCv.notify_one();
}

void CpuStateNotifierQt::NotifyScreenData(const gpu::ScreenData& data) {
  std::unique_lock lk(_notifyMutex);

  _updateFlag |= UpdateFlag_Screen;

  _screenData = data;
  _notified = true;
  _notifyCv.notify_one();  
}

void CpuStateNotifierQt::NotifyTilesetData(const gpu::TilesetDump& data) {
  std::unique_lock lk(_notifyMutex);

  _updateFlag |= UpdateFlag_TilesetDebug;

  _tilesetData = data;
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
      emit NotifyStateSignal(_nextState, _nextStateHistory, _memory_dump);

    if (_updateFlag & UpdateFlag_RomData)
      emit NotifyRomDataSignal(_nextInstructionState);

    if (_updateFlag & UpdateFlag_Screen)
      emit NotifyScreenDataSignal(_screenData);

    if (_updateFlag & UpdateFlag_TilesetDebug)
      emit NotifyTileDataSignal(_tilesetData);

    _notified = false;
    _updateFlag = 0;
  }
}

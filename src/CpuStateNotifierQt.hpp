#pragma once
#include <CpuStateNotifier.hpp>
#include "cpu/StateHistory.hpp"
#include "MemoryController.hpp"

#include "gpu/ScreenData.hpp"

#include <thread>
#include <condition_variable>

#include <qobject.h>

class DebugWindow;

class CpuStateNotifierQt final : public QObject, public CpuStateNotifier {
  Q_OBJECT
public:
  enum UpdateFlag {
    UpdateFlag_State          = 1 << 1,
    UpdateFlag_RomData        = 1 << 2,
    UpdateFlag_Screen         = 1 << 3,
    UpdateFlag_TilesetDebug   = 1 << 4,
  };

  CpuStateNotifierQt(DebugWindow* window);

  void NotifyState(const cpu::State& state, std::shared_ptr<const cpu::StateHistory> history,
    std::shared_ptr<MemoryController> memory_ctrl);
  void NotifyRomData(const std::vector<Cpu::RomInstruction>& instructions);
  void NotifyScreenData(const gpu::ScreenData& data);
  void NotifyTilesetData(const gpu::TilesetDump& data);

signals:
  void NotifyStateSignal(const cpu::State& state, const cpu::StateHistory& history, const std::string& memory_dump);
  void NotifyRomDataSignal(const std::vector<Cpu::RomInstruction>& instructions);
  void NotifyScreenDataSignal(const gpu::ScreenData& data);
  void NotifyTileDataSignal(const gpu::TilesetDump& data);

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

  gpu::ScreenData _screenData;

  std::thread _notifyThread;
  int _updateFlag;

  gpu::TilesetDump _tilesetData;

  std::string _memory_dump;
};
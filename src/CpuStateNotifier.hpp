#pragma once

#include "cpu/StateHistory.hpp"
#include "Cpu.hpp"
#include "gpu/ScreenData.hpp"

namespace cpu {
class State;
}
class CpuStateNotifier {
public:
  CpuStateNotifier() { }
  virtual ~CpuStateNotifier() { }

  virtual void NotifyState(const cpu::State& state, std::shared_ptr<const cpu::StateHistory> history) = 0;
  virtual void NotifyRomData(const std::vector<Cpu::RomInstruction>& instructions) = 0;
  virtual void NotifyScreenData(const gpu::ScreenData& data) = 0;
  virtual void NotifyTilesetData(const gpu::TilesetDump& data) = 0;
};
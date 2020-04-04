#pragma once

#include "cpu/StateHistory.hpp"
#include "Cpu.hpp"

namespace cpu {
class State;
}
class CpuStateNotifier {
public:
  CpuStateNotifier() { }
  virtual ~CpuStateNotifier() { }

  virtual void NotifyState(const cpu::State& state, std::shared_ptr<const cpu::StateHistory> history) = 0;
  virtual void NotifyRomData(const std::vector<Cpu::RomInstruction>& instructions) = 0;
};
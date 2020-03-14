#pragma once

#include "cpu/StateHistory.hpp"

namespace cpu {
class State;
}
class CpuStateNotifier {
public:
  CpuStateNotifier() { }
  virtual ~CpuStateNotifier() { }

  virtual void NotifyState(const cpu::State& state, const cpu::StateHistory& history) = 0;
};
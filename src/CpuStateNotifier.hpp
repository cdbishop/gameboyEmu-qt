#pragma once

namespace cpu {
class State;
}
class CpuStateNotifier {
public:
  CpuStateNotifier() { }
  virtual ~CpuStateNotifier() { }

  virtual void NotifyState(const cpu::State& state) = 0;
};
#pragma once
#include "CpuState.hpp"

class CpuStateNotifier {
public:
  CpuStateNotifier() { }
  virtual ~CpuStateNotifier() { }

  virtual void NotifyState(const cpu::State& state) = 0;
};
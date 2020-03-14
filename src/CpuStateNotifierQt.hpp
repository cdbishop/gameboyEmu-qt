#pragma once
#include <CpuStateNotifier.hpp>
#include "cpu/StateHistory.hpp"

class DebugWindow;

class CpuStateNotifierQt final : public CpuStateNotifier {
public:
  CpuStateNotifierQt(DebugWindow* window);

  void NotifyState(const cpu::State& state, const cpu::StateHistory& history);

private:
  DebugWindow* _window;
};
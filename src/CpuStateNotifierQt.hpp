#pragma once
#include <CpuStateNotifier.hpp>

class DebugWindow;

class CpuStateNotifierQt final : public CpuStateNotifier {
public:
  CpuStateNotifierQt(DebugWindow* window);

  void NotifyState(const cpu::State& state);

private:
  DebugWindow* _window;
};
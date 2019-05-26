#include "CpuStateNotifierQt.hpp"
#include "DebugWindow.hpp"

CpuStateNotifierQt::CpuStateNotifierQt(DebugWindow* window)
  :_window(window)
{
}

void CpuStateNotifierQt::NotifyState(const cpu::State & state)
{
  _window->UpdateState(state);
}

#include "CpuDebug.hpp"

namespace cpu {

Debug::Debug()
  :_pcBreakTarget(0),
  _pcTargetSet(false)
{
}

void Debug::SetPCTarget(unsigned short pc)
{
  _pcBreakTarget = pc;
  _pcTargetSet = true;
}

void Debug::ClearPCTarget()
{
  _pcBreakTarget = 0;
  _pcTargetSet = false;
}

bool Debug::IsPCTargetReached(unsigned short curPC)
{
  return _pcTargetSet && _pcBreakTarget == curPC;
}

void Debug::SetRegTarget(Register8 reg, unsigned char target)
{
  _register8BreakTargets.insert(std::make_pair(reg, target));
}

void Debug::SetRegTarget(Register16 reg, unsigned short target)
{
  _register16BreakTargets.insert(std::make_pair(reg, target));
}

bool Debug::TestRegBreakTargets(const cpu::State & state)
{
  for (auto&& breaks : _register8BreakTargets) {
    if (state.ReadRegister(breaks.first) == breaks.second) {
      return true;
    }
  }

  for (auto&& breaks : _register16BreakTargets) {
    if (state.ReadRegister(breaks.first) == breaks.second) {
      return true;
    }
  }

  return false;
}

}

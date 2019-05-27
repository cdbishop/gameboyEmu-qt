#pragma once

#include "Registers.hpp"
#include "CpuState.hpp"

#include <map>

namespace cpu {

class Debug final {
public:
  Debug();

  void SetPCTarget(unsigned short pc);
  void ClearPCTarget();
  
  bool IsPCTargetReached(unsigned short curPC);

  void SetRegTarget(Register8 reg, unsigned char target);
  void SetRegTarget(Register16 reg, unsigned short target);

  bool TestRegBreakTargets(const cpu::State& state);

private:
  unsigned int _pcBreakTarget;
  bool _pcTargetSet;

  std::map<Register8, unsigned char> _register8BreakTargets;
  std::map<Register16, unsigned short> _register16BreakTargets;
};

}
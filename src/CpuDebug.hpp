#pragma once

#include "Registers.hpp"

#include <map>

namespace cpu {

class State;

class Debug final {
public:
  Debug();

  void SetPCTarget(unsigned short pc);
  void ClearPCTarget();
  
  bool IsPCTargetReached(unsigned short curPC);

  void SetRegTarget(Register8 reg, unsigned char target);
  void SetRegTarget(Register16 reg, unsigned short target);

  void RemoveRegTarget(Register8 reg);
  void RemoveRegTarget(Register16 reg);

  bool TestRegBreakTargets(const cpu::State& state);

private:
  unsigned int _pcBreakTarget;
  bool _pcTargetSet;

  std::map<Register8, unsigned char> _register8BreakTargets;
  std::map<Register16, unsigned short> _register16BreakTargets;
};

}

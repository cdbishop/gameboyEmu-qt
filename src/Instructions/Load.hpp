#pragma once
#include "Registers.hpp"

class Cpu;

namespace Instructions {
  void LoadImmediate8(Cpu* cpu, Register8 target);
  void LoadImmediate16(Cpu* cpu, Register16 target);
  void LoadFromAddress(Cpu* cpu, Register8 target, Register16 addressRegister);
}
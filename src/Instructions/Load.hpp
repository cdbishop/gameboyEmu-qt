#pragma once
#include "Registers.hpp"

class Cpu;

namespace Instructions {
  void LoadImmediate8(Cpu* cpu, Register8 target);
  void LoadImmediate16(Cpu* cpu, Register16 target);
  void WriteToAddressAndDec(Cpu* cpu, Register8 src, Register16 targetAddressRegister);
}
#pragma once
#include "Registers.hpp"

class Cpu;

namespace Instructions {
  void Sub8(Cpu* cpu, Register8 src, Register8 target);
  void SubFromAddr8(Cpu* cpu, Register8 target, Register16 addressSrc);

  void Sub8_Immediate(Cpu* cpu, Register8 src);

  void SubCarry8(Cpu* cpu, Register8 src, Register8 target);
  void SubCarryFromAddr8(Cpu* cpu, Register8 target, Register16 addressSrc);

  void SubCarry8_Immediate(Cpu* cpu, Register8 src);
}
#pragma once
#include "Registers.hpp"

class Cpu;

namespace Instructions {
  void Add8(Cpu* cpu, Register8 src, Register8 target);
  void Add16(Cpu* cpu, Register16 src, Register16 target);

  void Add16_SignedImmediate(Cpu* cpu, Register16 src);

  void Add8_Immediate(Cpu* cpu, Register8 target);
  void AddCarry8_Immediate(Cpu* cpu, Register8 target);

  void AddCarry8(Cpu* cpu, Register8 src, Register8 target);

  void AddFromAddr8(Cpu* cpu, Register8 target, Register16 addressSrc);
  void AddCarryFromAddr8(Cpu* cpu, Register8 target, Register16 addressSrc);
}
#pragma once

class Cpu;

#include "Register.hpp"

namespace Instructions {
  void JmpRelative_immediate8(Cpu* cpu);

  void JmpImmediate16(Cpu* cpu);
  void JmpImmediate16_Zero(Cpu* cpu);
  void JmpImmediate16_NotZero(Cpu* cpu);

  void JmpImmediate16_Carry(Cpu* cpu);
  void JmpImmediate16_NotCarry(Cpu* cpu);

  void JmpRelative_NotZero(Cpu* cpu);
  void JmpRelative_Zero(Cpu* cpu);

  void JmpRelative_NotCarry(Cpu* cpu);
  void JmpRelative_Carry(Cpu* cpu);

  void JmpRegister(Cpu* cpu, Register16 reg);
}
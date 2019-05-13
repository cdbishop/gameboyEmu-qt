#pragma once

class Cpu;

namespace Instructions {
  void Jmp_immediate(Cpu* cpu);
  void JmpRelative_NotZero(Cpu* cpu);
  void JmpRelative_Zero(Cpu* cpu);
}
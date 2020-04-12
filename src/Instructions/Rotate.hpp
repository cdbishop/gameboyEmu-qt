#pragma once
#include "Register.hpp"

class Cpu;

namespace Instructions {
  void RotateLeft(Cpu* cpu, Register8 reg, bool carry, bool zero);
  void RotateRight(Cpu* cpu, Register8 reg, bool carry, bool zero);
}
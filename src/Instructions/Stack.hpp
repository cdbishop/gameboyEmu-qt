#pragma once
#include "Registers.hpp"

class Cpu;

namespace Instructions {
  void Pop16(Cpu* cpu, Register16 reg);
  void Push16(Cpu* cpu, Register16 reg);
}
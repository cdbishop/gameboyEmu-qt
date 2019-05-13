#pragma once
#include "Registers.hpp"

class Cpu;

namespace Instructions {
  void Inc8(Cpu* cpu, Register8 target);
  void Dec8(Cpu* cpu, Register8 target);

  void Inc16(Cpu* cpu, Register16 target);
  void Dec16(Cpu* cpu, Register16 target);
}
#pragma once
#include "Registers.hpp"

class Cpu;

namespace Instructions {
  void WriteAddress(Cpu* cpu, Register16 targetAddress, Register8 src);
}
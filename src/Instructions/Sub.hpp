#pragma once
#include "Registers.hpp"

class Cpu;

namespace Instructions {
  void Sub(Cpu* cpu, Register8 src, Register8 target);
}
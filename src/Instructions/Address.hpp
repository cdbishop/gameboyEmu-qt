#pragma once
#include "Registers.hpp"

class Cpu;

namespace Instructions {
  void WriteAddress(Cpu* cpu, Register16 targetAddress, Register8 src);
  void WriteAddressImmediate(Cpu* cpu, Register16 src);

  void WriteRegisterAddressImmediate(Cpu* cpu, Register16 target);

  void IncAddressValue(Cpu* cpu, Register16 address);
  void DecAddressValue(Cpu* cpu, Register16 address);
}
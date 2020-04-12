#pragma once
#include "Registers.hpp"

class Cpu;

namespace Instructions {
void CompareRegisterImmediate(Cpu * cpu, Register8 src);
void CompareRegister(Cpu * cpu, Register8 src, Register8 target);
void CompareAddressRegister(Cpu * cpu, Register8 src, Register16 targetAddress);
}
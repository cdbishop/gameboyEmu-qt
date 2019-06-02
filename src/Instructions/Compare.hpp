#pragma once
#include "Registers.hpp"

class Cpu;

namespace Instructions {
void CompareRegisterImmediate(Cpu * cpu, Register8 src);
}
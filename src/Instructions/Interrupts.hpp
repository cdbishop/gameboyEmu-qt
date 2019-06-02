#pragma once
#include "Registers.hpp"

class Cpu;

namespace Instructions {
void EnableInterrupts(Cpu* cpu);
void DisableInterrupts(Cpu* cpu);
}
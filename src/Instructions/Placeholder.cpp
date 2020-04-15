#include "Placeholder.hpp"

#include "Cpu.hpp"

#include <stdexcept>

void Instructions::Placeholder(Cpu* cpu)
{
  throw std::runtime_error("Placeholder");
}

void Instructions::Removed(Cpu * cpu) {
  throw std::runtime_error("Instruction code removed - Should never be called!");
}

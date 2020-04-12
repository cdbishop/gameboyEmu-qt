#include "Flag.hpp"

#include "Cpu.hpp"

namespace Instructions {

void SetCarryFlag(Cpu* cpu) {
  cpu->SetFlag(cpu::Flag::Carry);
}

void ClearCarryFlag(Cpu* cpu) {
  cpu->ClearFlag(cpu::Flag::Carry);
}

}

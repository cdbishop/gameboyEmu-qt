#include "Rotate.hpp"

#include "Cpu.hpp"
#include "MemoryController.hpp"

#include "Rotate.hpp"

namespace Instructions {

void RotateLeft(Cpu* cpu, Register8 reg, bool carry, bool zero) {
  unsigned char value = cpu->GetRegister(reg);
  unsigned char carry_bit = ((value & 0x80) >> 7);

  unsigned char result = (value << 1);
  result += carry_bit;

  if (carry && carry_bit > 0) {
    cpu->SetFlag(cpu::Flag::Carry);
  }

  if (result == 0 && zero) {
    cpu->SetFlag(cpu::Flag::Zero);
  }

  cpu->SetRegister(reg, value);
}

void RotateRight(Cpu* cpu, Register8 reg, bool carry, bool zero) {
  unsigned char value = cpu->GetRegister(reg);

  unsigned char result = (value >> 1);

  if (carry && result > 0) {
    cpu->SetFlag(cpu::Flag::Carry);
  }

  if (result == 0 && zero) {
    cpu->SetFlag(cpu::Flag::Zero);
  }

  if (carry) {
    value |= 0x80;
  }

  cpu->SetRegister(reg, value);
}

}

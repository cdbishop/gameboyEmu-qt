#include "Compare.hpp"
#include "Cpu.hpp"

#include <stdexcept>

void Instructions::CompareRegisterImmediate(Cpu * cpu, Register8 src)
{
  unsigned char srcValue = cpu->GetRegister(src);
  unsigned char immediate = cpu->ReadByteOffset(1);

  short signed_src = static_cast<short>(srcValue);
  short signed_immediate = static_cast<short>(immediate);

  short result = signed_src - signed_immediate;

  if ((signed_src & 0xF) - (signed_immediate & 0xF) < 0) {
    cpu->SetFlag(Cpu::Flag::HalfCarry);
  } else {
    cpu->ClearFlag(Cpu::Flag::HalfCarry);
  }

  if (result < 0) {
    cpu->SetFlag(Cpu::Flag::Carry);
  } else {
    cpu->ClearFlag(Cpu::Flag::Carry);
  }

  cpu->SetFlag(Cpu::Flag::SubOp);

  if ((result & 0xFF) == 0) {
    cpu->SetFlag(Cpu::Flag::Zero);
  } else {
    cpu->ClearFlag(Cpu::Flag::Zero);
  }
}

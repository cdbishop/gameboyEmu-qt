#include "Compare.hpp"
#include "Cpu.hpp"
#include "MemoryController.hpp"

#include <stdexcept>

void PerformCompare(Cpu* cpu, unsigned char lhs, unsigned char rhs) {
  short signed_lhs = static_cast<short>(lhs);
  short signed_rhs = static_cast<short>(rhs);

  short result = signed_lhs - signed_rhs;
  
  if ((signed_lhs & 0xF) - (signed_rhs & 0xF) < 0) {
    cpu->SetFlag(cpu::Flag::HalfCarry);
  } else {
    cpu->ClearFlag(cpu::Flag::HalfCarry);
  }

  if (result < 0) {
    cpu->SetFlag(cpu::Flag::Carry);
  } else {
    cpu->ClearFlag(cpu::Flag::Carry);
  }

  cpu->SetFlag(cpu::Flag::SubOp);

  if ((result & 0xFF) == 0) {
    cpu->SetFlag(cpu::Flag::Zero);
  } else {
    cpu->ClearFlag(cpu::Flag::Zero);
  }
}

void Instructions::CompareRegisterImmediate(Cpu* cpu, Register8 src)
{
  unsigned char srcValue = cpu->GetRegister(src);
  unsigned char immediate = cpu->ReadByteOffset(1);

  PerformCompare(cpu, srcValue, immediate);
}

void Instructions::CompareRegister(Cpu* cpu, Register8 src, Register8 target) {
  unsigned char srcValue = cpu->GetRegister(src);
  unsigned char targetValue = cpu->GetRegister(target);

  PerformCompare(cpu, srcValue, targetValue);
}

void Instructions::CompareAddressRegister(Cpu* cpu, Register8 src, Register16 targetAddress) {
  unsigned char srcValue = cpu->GetRegister(src);
  unsigned short address = cpu->GetRegister(targetAddress);
  unsigned char targetValue = cpu->GetMemoryController()->ReadByte(address);

  PerformCompare(cpu, srcValue, targetValue);
}

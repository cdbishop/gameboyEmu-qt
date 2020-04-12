#include "Sub.hpp"

#include "Cpu.hpp"
#include "MemoryController.hpp"

short PerformSub8(Cpu* cpu, short lhs, short rhs, bool subCarry) {
  short result = lhs - rhs;
  short half_carry = (lhs & 0xF - rhs & 0xF);

  if (subCarry) {
    if (cpu->TestFlag(cpu::Flag::Carry)) {
      result--;
    }
  }

  if (half_carry < 0) {
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

  return result;
}

//subtract the value in target from src (store in src)
void Instructions::Sub8(Cpu * cpu, Register8 src, Register8 target) {
  short target_value = static_cast<short>(cpu->GetRegister(target));
  short src_value = static_cast<short>(cpu->GetRegister(src));

  short result = PerformSub8(cpu, src_value, target_value, false);

  cpu->SetRegister(src, static_cast<unsigned char>(result));
}

void Instructions::SubFromAddr8(Cpu * cpu, Register8 target, Register16 addressSrc) {
  unsigned char target_value = cpu->GetRegister(target);
  unsigned short address = cpu->GetRegister(addressSrc);
  unsigned char val = cpu->GetMemoryController()->ReadByte(address);

  unsigned short result = PerformSub8(cpu, val, target_value, false);
  cpu->SetRegister(target, static_cast<unsigned char>(result));
}

void Instructions::Sub8_Immediate(Cpu * cpu, Register8 src) {
  auto immediate = cpu->ReadByteOffset(1);
  auto targetValue = cpu->GetRegister(src);

  auto result = PerformSub8(cpu, targetValue, immediate, false);
  cpu->SetRegister(src, static_cast<unsigned char>(result));
}

void Instructions::SubCarry8(Cpu * cpu, Register8 src, Register8 target) {
  short target_value = static_cast<short>(cpu->GetRegister(target));
  short src_value = static_cast<short>(cpu->GetRegister(src));

  short result = PerformSub8(cpu, src_value, target_value, true);

  cpu->SetRegister(src, static_cast<unsigned char>(result));
}

void Instructions::SubCarryFromAddr8(Cpu* cpu, Register8 target, Register16 addressSrc) {
  unsigned char target_value = cpu->GetRegister(target);
  unsigned short address = cpu->GetRegister(addressSrc);
  unsigned char val = cpu->GetMemoryController()->ReadByte(address);

  unsigned short result = PerformSub8(cpu, val, target_value, true);
  cpu->SetRegister(target, static_cast<unsigned char>(result));
}

void Instructions::SubCarry8_Immediate(Cpu * cpu, Register8 src) {
  auto immediate = cpu->ReadByteOffset(1);
  short src_value = static_cast<short>(cpu->GetRegister(src));

  short result = PerformSub8(cpu, src_value, immediate, true);

  cpu->SetRegister(src, static_cast<unsigned char>(result));
}

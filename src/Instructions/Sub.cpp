#include "Sub.hpp"

#include "Cpu.hpp"

//subtract the value in target from src (store in src)
void Instructions::Sub(Cpu * cpu, Register8 src, Register8 target) {
  short target_value = static_cast<short>(cpu->GetRegister(target));
  short src_value = static_cast<short>(cpu->GetRegister(src));

  short result = src_value - target_value;
  short half_carry = (src_value & 0xF - target_value & 0xF);

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

  cpu->SetRegister(src, static_cast<unsigned char>(result));
}

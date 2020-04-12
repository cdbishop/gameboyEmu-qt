#include "Add.hpp"

#include "Cpu.hpp"
#include "MemoryController.hpp"

unsigned short PerformAdd8(Cpu* cpu, unsigned char lh, unsigned char rh, bool addCarry) {
  unsigned short result = lh + rh;

  if (addCarry) {
    if (cpu->TestFlag(cpu::Flag::Carry)) {
      result++;
    }
  }

  if ((rh & 0xF) + (lh & 0xF) > 0xF) {
    cpu->SetFlag(cpu::Flag::HalfCarry);
  } else {
    cpu->ClearFlag(cpu::Flag::HalfCarry);
  }

  if (result > 0xFF) {
    cpu->SetFlag(cpu::Flag::Carry);
  } else {
    cpu->ClearFlag(cpu::Flag::Carry);
  }

  if (result == 0) {
    cpu->SetFlag(cpu::Flag::Zero);
  } else {
    cpu->ClearFlag(cpu::Flag::Zero);
  }

  cpu->ClearFlag(cpu::Flag::SubOp);

  return result;
}

//add the value in target to src (store in src)
void Instructions::Add8(Cpu* cpu, Register8 src, Register8 target) {
  unsigned char target_value = cpu->GetRegister(target);
  unsigned char src_value = cpu->GetRegister(src);

 /* unsigned short result = src_value + target_value;

  if ((target_value & 0xF) + (src_value & 0xF) > 0xF) {
    cpu->SetFlag(cpu::Flag::HalfCarry);
  } else {
    cpu->ClearFlag(cpu::Flag::HalfCarry);
  }

  if (result > 0xFF) {
    cpu->SetFlag(cpu::Flag::Carry);
  } else {
    cpu->ClearFlag(cpu::Flag::Carry);
  }

  if (result == 0) {
    cpu->SetFlag(cpu::Flag::Zero);
  } else {
    cpu->ClearFlag(cpu::Flag::Zero);
  }

  cpu->ClearFlag(cpu::Flag::SubOp);*/


  unsigned short result = PerformAdd8(cpu, src_value, target_value, false);

  cpu->SetRegister(src, static_cast<unsigned char>(result));
}

void Instructions::Add16(Cpu* cpu, Register16 src, Register16 target) {
  unsigned short src_value = cpu->GetRegister(src);
  unsigned short target_value = cpu->GetRegister(target);

  unsigned int result = src_value + target_value;

  if (result > 0x800) {
    cpu->SetFlag(cpu::Flag::HalfCarry);
  } else {
    cpu->ClearFlag(cpu::Flag::HalfCarry);
  }

  if (result > 0xFF) {
    cpu->SetFlag(cpu::Flag::Carry);
  } else {
    cpu->ClearFlag(cpu::Flag::Carry);
  } 

  cpu->SetRegister(src, static_cast<unsigned short>(result));
}

void Instructions::Add16_SignedImmediate(Cpu * cpu, Register16 src) {
  unsigned short src_value = cpu->GetRegister(src);
  signed short immediate = static_cast<signed short>(cpu->ReadByteOffset(1));

  int result = src_value + immediate;

  if (result > 0x800) {
    cpu->SetFlag(cpu::Flag::HalfCarry);
  } else {
    cpu->ClearFlag(cpu::Flag::HalfCarry);
  }

  if (result > 0xFF) {
    cpu->SetFlag(cpu::Flag::Carry);
  } else {
    cpu->ClearFlag(cpu::Flag::Carry);
  }

  cpu->SetRegister(src, static_cast<unsigned short>(result));
}

void Instructions::Add8_Immediate(Cpu* cpu, Register8 target) {
  auto immediate = cpu->ReadByteOffset(1);
  auto targetValue = cpu->GetRegister(target);

  auto result = PerformAdd8(cpu, targetValue, immediate, false);
  cpu->SetRegister(target, static_cast<unsigned char>(result));
}

void Instructions::AddCarry8_Immediate(Cpu * cpu, Register8 target) {
  auto immediate = cpu->ReadByteOffset(1);
  auto targetValue = cpu->GetRegister(target);

  auto result = PerformAdd8(cpu, targetValue, immediate, true);
  cpu->SetRegister(target, static_cast<unsigned char>(result));
}

void Instructions::AddCarry8(Cpu* cpu, Register8 src, Register8 target) {
  unsigned char target_value = cpu->GetRegister(target);
  unsigned char src_value = cpu->GetRegister(src);

  unsigned short result = PerformAdd8(cpu, src_value, target_value, true);
  cpu->SetRegister(src, static_cast<unsigned char>(result));
}

void Instructions::AddFromAddr8(Cpu* cpu, Register8 target, Register16 addressSrc) {
  unsigned char target_value = cpu->GetRegister(target);
  unsigned short address = cpu->GetRegister(addressSrc);
  unsigned char val = cpu->GetMemoryController()->ReadByte(address);

  unsigned short result = PerformAdd8(cpu, val, target_value, false);
  cpu->SetRegister(target, static_cast<unsigned char>(result));
}

void Instructions::AddCarryFromAddr8(Cpu* cpu, Register8 target, Register16 addressSrc) {
  unsigned char target_value = cpu->GetRegister(target);
  unsigned short address = cpu->GetRegister(addressSrc);
  unsigned char val = cpu->GetMemoryController()->ReadByte(address);

  unsigned short result = PerformAdd8(cpu, val, target_value, true);
  cpu->SetRegister(target, static_cast<unsigned char>(result));
}

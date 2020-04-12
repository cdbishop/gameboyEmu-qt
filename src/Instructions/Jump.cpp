#include "Jump.hpp"

#include "Cpu.hpp"

void Instructions::JmpRelative_immediate8(Cpu * cpu) {
  short offset = (short)cpu->ReadByteOffset(1);
  cpu->SetPC(cpu->GetPC() + offset);
}

void Instructions::JmpImmediate16(Cpu * cpu)
{
  unsigned short target = cpu->ReadWordOffset(1);
  cpu->SetPC(target);
}

void Instructions::JmpImmediate16_Zero(Cpu * cpu)
{
  if (cpu->TestFlag(cpu::Flag::Zero)) {
    JmpImmediate16(cpu);
  }
}

void Instructions::JmpImmediate16_NotZero(Cpu * cpu) 
{
  unsigned char upper = cpu->ReadByteOffset(1);
  if (!cpu->TestFlag(cpu::Flag::Zero)) {
    cpu->SetPC(cpu->GetPC() + (char)upper);
  }
}

void Instructions::JmpImmediate16_Carry(Cpu * cpu) 
{
  unsigned char upper = cpu->ReadByteOffset(1);
  if (cpu->TestFlag(cpu::Flag::Carry)) {
    cpu->SetPC(cpu->GetPC() + (char)upper);
  }
}

void Instructions::JmpImmediate16_NotCarry(Cpu * cpu) 
{
  unsigned char upper = cpu->ReadByteOffset(1);
  if (!cpu->TestFlag(cpu::Flag::Carry)) {
    cpu->SetPC(cpu->GetPC() + (char)upper);
  }
}

void Instructions::JmpRelative_NotZero(Cpu * cpu)
{
  unsigned char upper = cpu->ReadByteOffset(1);
  if (!cpu->TestFlag(cpu::Flag::Zero)) {
    cpu->SetPC(cpu->GetPC() + (char)upper);
  }
}

void Instructions::JmpRelative_Zero(Cpu * cpu)
{
  unsigned short target = cpu->ReadWordOffset(1);
  if (cpu->TestFlag(cpu::Flag::Zero)) {
    cpu->SetPC(target);
  }
}

void Instructions::JmpRelative_NotCarry(Cpu * cpu) {
  unsigned short target = cpu->ReadWordOffset(1);
  if (!cpu->TestFlag(cpu::Flag::Carry)) {
    cpu->SetPC(target);
  }
}

void Instructions::JmpRelative_Carry(Cpu * cpu) {
  unsigned short target = cpu->ReadWordOffset(1);
  if (cpu->TestFlag(cpu::Flag::Carry)) {
    cpu->SetPC(target);
  }
}

void Instructions::JmpRegister(Cpu* cpu, Register16 reg) {
  auto target = cpu->GetRegister(reg);
  cpu->SetPC(target);
}

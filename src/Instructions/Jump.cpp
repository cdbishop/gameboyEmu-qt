#include "Jump.hpp"

#include "Cpu.hpp"

void Instructions::Jmp_immediate(Cpu * cpu)
{
  unsigned char upper = cpu->ReadByteOffset(1);
  unsigned char lower = cpu->ReadByteOffset(2);
  unsigned short combined = (unsigned short)lower << 8 | upper;
  cpu->SetPC(combined);
}

void Instructions::JmpRelative_NotZero(Cpu * cpu)
{
  unsigned char upper = cpu->ReadByteOffset(1);
  unsigned char lower = cpu->ReadByteOffset(2);
  unsigned short combined = (unsigned short)lower << 8 | upper;
  if (!cpu->TestFlag(Cpu::Flag::Zero)) {
    cpu->SetPC(combined);
  }
}

void Instructions::JmpRelative_Zero(Cpu * cpu)
{
  unsigned char upper = cpu->ReadByteOffset(1);
  unsigned char lower = cpu->ReadByteOffset(2);
  unsigned short combined = (unsigned short)lower << 8 | upper;
  if (cpu->TestFlag(Cpu::Flag::Zero)) {
    cpu->SetPC(combined);
  }
}

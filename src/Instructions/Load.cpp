#include "Load.hpp"
#include "Cpu.hpp"

#include <stdexcept>

void Instructions::LoadImmediate8(Cpu * cpu, Register8 target)
{
  unsigned char immediate = cpu->ReadByteOffset(1);
  cpu->SetRegister(target, immediate);
}

void Instructions::LoadImmediate16(Cpu * cpu, Register16 target)
{
  unsigned char upper = cpu->ReadByteOffset(1);
  unsigned char lower = cpu->ReadByteOffset(2);
  unsigned short combined = (unsigned short)lower << 8 | upper;
  cpu->SetRegister(target, combined);
}

void Instructions::LoadFromAddress(Cpu * cpu, Register8 target, Register16 addressRegister)
{
  unsigned short address = cpu->GetRegister(addressRegister);

}

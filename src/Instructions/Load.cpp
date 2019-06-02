#include "Load.hpp"
#include "Cpu.hpp"
#include "MemoryController.hpp"

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

void Instructions::WriteToAddressAndDec(Cpu * cpu, Register8 src, Register16 targetAddressRegister)
{
  auto val = cpu->GetRegister(src);
  auto addr = cpu->GetRegister(targetAddressRegister);
  cpu->GetMemoryController()->WriteByte(addr, val);
  cpu->DecRegister(targetAddressRegister);
}

void Instructions::WriteToAddressOffset(Cpu * cpu, Register8 src, uint16_t targetBaseAddress)
{
  auto val = cpu->GetRegister(src);
  unsigned char immediate = cpu->ReadByteOffset(1);
  unsigned short offset = targetBaseAddress + immediate;
  cpu->GetMemoryController()->WriteByte(offset, val);
}

void Instructions::ReadFromAddressOffset(Cpu * cpu, Register8 src, uint16_t targetBaseAddress)
{
  unsigned char immediate = cpu->ReadByteOffset(1);
  unsigned short offset = targetBaseAddress + immediate;
  auto val = cpu->GetMemoryController()->ReadByte(offset);
  cpu->SetRegister(src, val);
}

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

void Instructions::LoadAddressRegister(Cpu * cpu, Register8 target, Register16 address_src) {
  unsigned short address = cpu->GetRegister(address_src);
  unsigned char value = cpu->GetMemoryController()->ReadByte(address);
  cpu->SetRegister(target, value);
}

void Instructions::LoadFromRegister8(Cpu * cpu, Register8 target, Register8 src) {
  auto val = cpu->GetRegister(src);
  cpu->SetRegister(target, val);
}

void Instructions::LoadFromRegister16(Cpu * cpu, Register16 target, Register16 src) {
  auto val = cpu->GetRegister(src);
  cpu->SetRegister(target, val);
}

void Instructions::LoadFromRegisterAddress(Cpu * cpu, Register8 target, Register16 address_src) {
  auto addr = cpu->GetRegister(address_src);
  auto val = cpu->GetMemoryController()->ReadByte(addr);
  cpu->SetRegister(target, val);
}

void Instructions::LoadFromImmediateAddress(Cpu * cpu, Register8 target) {
  auto addr = cpu->ReadWordOffset(1);
  auto value = cpu->GetMemoryController()->ReadByte(addr);
  cpu->SetRegister(target, value);
}

void Instructions::WriteToImmediateAddress(Cpu * cpu, Register8 target) {
  auto addr = cpu->ReadWordOffset(1);
  auto value = cpu->GetRegister(target);

  cpu->GetMemoryController()->WriteByte(addr, value);
}

void Instructions::WriteToAddressAndDec(Cpu * cpu, Register8 src, Register16 targetAddressRegister)
{
  auto val = cpu->GetRegister(src);
  auto addr = cpu->GetRegister(targetAddressRegister);
  cpu->GetMemoryController()->WriteByte(addr, val);
  cpu->DecRegister(targetAddressRegister);
}

void Instructions::WriteToAddressAndInc(Cpu * cpu, Register8 src, Register16 targetAddressRegister) {
  auto val = cpu->GetRegister(src);
  auto addr = cpu->GetRegister(targetAddressRegister);
  cpu->GetMemoryController()->WriteByte(addr, val);
  cpu->IncRegister(targetAddressRegister);
}

void Instructions::ReadFromAddressAndDec(Cpu * cpu, Register8 target, Register16 srcAddressRegister) {
  auto addr = cpu->GetRegister(srcAddressRegister);
  auto val = cpu->GetMemoryController()->ReadByte(addr);
  cpu->SetRegister(target, val);

  cpu->DecRegister(srcAddressRegister);
}

void Instructions::ReadFromAddressAndInc(Cpu * cpu, Register8 target, Register16 srcAddressRegister) {
  auto addr = cpu->GetRegister(srcAddressRegister);
  auto val = cpu->GetMemoryController()->ReadByte(addr);
  cpu->SetRegister(target, val);

  cpu->IncRegister(srcAddressRegister);
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

void Instructions::WriteToAddressOffsetReg(Cpu * cpu, Register8 src, uint16_t targetBaseAddress, Register8 offset)
{
  unsigned short offset_value = cpu->GetRegister(offset);
  unsigned char value = cpu->GetRegister(src);
  cpu->GetMemoryController()->WriteByte(targetBaseAddress + offset_value, value);
}

void Instructions::LoadFromSPOffset(Cpu* cpu, Register16 target)
{
  char offset = static_cast<char>(cpu->ReadByteOffset(1));
  auto sp = cpu->GetRegister(Register16::SP);
  auto value = sp + offset;
  cpu->SetRegister(target, value);
}

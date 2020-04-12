#include "Load.hpp"
#include "Cpu.hpp"
#include "MemoryController.hpp"

#include <stdexcept>
#include "Address.hpp"
#include "Address.hpp"

void Instructions::WriteAddress(Cpu* cpu, Register16 targetAddress, Register8 src) {
  unsigned char value = cpu->GetRegister(src);
  unsigned short addr = cpu->GetRegister(targetAddress);
  cpu->GetMemoryController()->WriteByte(addr, value);
}

void Instructions::WriteAddressImmediate(Cpu* cpu, Register16 src) {
  unsigned short addr = cpu->ReadWordOffset(1);
  unsigned char value = cpu->GetRegister(src);
  cpu->GetMemoryController()->WriteWord(addr, value);
}

void Instructions::WriteRegisterAddressImmediate(Cpu* cpu, Register16 target) {
  unsigned char value = cpu->ReadByteOffset(1);
  unsigned short addr = cpu->GetRegister(target);

  cpu->GetMemoryController()->WriteByte(addr, value);
}

void Instructions::IncAddressValue(Cpu* cpu, Register16 address) {
  unsigned short addr = cpu->GetRegister(address);

  auto value = cpu->GetMemoryController()->ReadByte(addr);
  value++;

  cpu->GetMemoryController()->WriteByte(addr, value);
}

void Instructions::DecAddressValue(Cpu * cpu, Register16 address) {
  unsigned short addr = cpu->GetRegister(address);

  auto value = cpu->GetMemoryController()->ReadByte(addr);
  value--;

  cpu->GetMemoryController()->WriteByte(addr, value);
}

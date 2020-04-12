#pragma once
#include "Registers.hpp"

class Cpu;

namespace Instructions {
  void LoadImmediate8(Cpu* cpu, Register8 target);
  void LoadImmediate16(Cpu* cpu, Register16 target);
  void LoadAddressRegister(Cpu* cpu, Register8 target, Register16 address_src);
  void LoadFromRegister8(Cpu* cpu, Register8 target, Register8 src);
  void LoadFromRegister16(Cpu* cpu, Register16 target, Register16 src);
  void LoadFromRegisterAddress(Cpu* cpu, Register8 target, Register16 address_src);
  void LoadFromImmediateAddress(Cpu* cpu, Register8 target);

  void WriteToImmediateAddress(Cpu* cpu, Register8 target);

  void WriteToAddressAndDec(Cpu* cpu, Register8 src, Register16 targetAddressRegister);
  void WriteToAddressAndInc(Cpu* cpu, Register8 src, Register16 targetAddressRegister);

  void ReadFromAddressAndDec(Cpu* cpu, Register8 target, Register16 srcAddressRegister);
  void ReadFromAddressAndInc(Cpu* cpu, Register8 target, Register16 srcAddressRegister);

  void WriteToAddressOffset(Cpu* cpu, Register8 src, uint16_t targetBaseAddress);
  void ReadFromAddressOffset(Cpu* cpu, Register8 src, uint16_t targetBaseAddress);

  void WriteToAddressOffsetReg(Cpu* cpu, Register8 src, uint16_t targetBaseAddress, Register8 offset);

  void LoadFromSPOffset(Cpu* cpu, Register16 target);
}
#include "LogicalOp.hpp"
#include "Cpu.hpp"
#include "MemoryController.hpp"

#include <stdexcept>

void Instructions::LogicalOp(Cpu* cpu, Register8 src, Register8 target, Op op)
{
  switch (op) {
    case Op::Xor: {
      unsigned char result = cpu->GetRegister(target) ^ cpu->GetRegister(src);
      cpu->SetRegister(target, result);

      cpu->ClearFlags();
      if (result == 0) {
        cpu->SetFlag(cpu::Flag::Zero);
      } else {
        cpu->ClearFlag(cpu::Flag::Zero);
      }
    }
    break;

    case Op::Or: {
      unsigned char result = cpu->GetRegister(target) | cpu->GetRegister(src);
      cpu->SetRegister(target, result);

      cpu->ClearFlags();
      if (result == 0) {
        cpu->SetFlag(cpu::Flag::Zero);
      } else {
        cpu->ClearFlag(cpu::Flag::Zero);
      }
    }
    break;

    case Op::And: {
      unsigned char result = cpu->GetRegister(target) & cpu->GetRegister(src);
      cpu->SetRegister(target, result);

      cpu->ClearFlags();
      if (result == 0) {
        cpu->SetFlag(cpu::Flag::Zero);
      } else {
        cpu->ClearFlag(cpu::Flag::Zero);
      }

      cpu->SetFlag(cpu::Flag::HalfCarry);
    }
    break;
  }
}

void Instructions::LogicalOpImmediate(Cpu * cpu, Register8 src, Op op) {
  switch (op) {
    case Op::Xor: {
      unsigned char immediate = cpu->ReadByteOffset(1);
      unsigned char result = cpu->GetRegister(src) ^ immediate;
      cpu->SetRegister(src, result);

      cpu->ClearFlags();
      if (result == 0) {
        cpu->SetFlag(cpu::Flag::Zero);
      } else {
        cpu->ClearFlag(cpu::Flag::Zero);
      }
    }
    break;

    case Op::And: {
      unsigned char immediate = cpu->ReadByteOffset(1);
      unsigned char result = cpu->GetRegister(src) & immediate;
      cpu->SetRegister(src, result);

      cpu->ClearFlags();
      if (result == 0) {
        cpu->SetFlag(cpu::Flag::Zero);
      } else {
        cpu->ClearFlag(cpu::Flag::Zero);
      }

      cpu->SetFlag(cpu::Flag::HalfCarry);
    }
    break;

    case Op::Or: {
      unsigned char immediate = cpu->ReadByteOffset(1);
      unsigned char result = cpu->GetRegister(src) | immediate;
      cpu->SetRegister(src, result);

      cpu->ClearFlags();
      if (result == 0) {
        cpu->SetFlag(cpu::Flag::Zero);
      } else {
        cpu->ClearFlag(cpu::Flag::Zero);
      }
    }
    break;
  }
}

void Instructions::LogicalOpAddr(Cpu * cpu, Register16 addressSrc, Register8 target, Op op) {
  switch (op) {
    case Op::Xor:
    {
      unsigned char addr = cpu->GetRegister(addressSrc);
      unsigned char rhs = cpu->GetMemoryController()->ReadByte(addr);
      unsigned char result = cpu->GetRegister(target) ^ rhs;
      cpu->SetRegister(target, result);

      cpu->ClearFlags();
      if (result == 0) {
        cpu->SetFlag(cpu::Flag::Zero);
      } else {
        cpu->ClearFlag(cpu::Flag::Zero);
      }
    }
    break;

    case Op::Or:
    {
      unsigned char addr = cpu->GetRegister(addressSrc);
      unsigned char rhs = cpu->GetMemoryController()->ReadByte(addr);
      unsigned char result = cpu->GetRegister(target) | rhs;
      cpu->SetRegister(target, result);

      cpu->ClearFlags();
      if (result == 0) {
        cpu->SetFlag(cpu::Flag::Zero);
      } else {
        cpu->ClearFlag(cpu::Flag::Zero);
      }
    }
    break;

    case Op::And:
    {
      unsigned char addr = cpu->GetRegister(addressSrc);
      unsigned char rhs = cpu->GetMemoryController()->ReadByte(addr);
      unsigned char result = cpu->GetRegister(target) & rhs;
      cpu->SetRegister(target, result);

      cpu->ClearFlags();
      if (result == 0) {
        cpu->SetFlag(cpu::Flag::Zero);
      } else {
        cpu->ClearFlag(cpu::Flag::Zero);
      }

      cpu->SetFlag(cpu::Flag::HalfCarry);
    }
    break;
  }
}

#include "Stack.hpp"

#include "Cpu.hpp"
#include "MemoryController.hpp"

#include "Jump.hpp"
#include "Subroutine.hpp"

namespace Instructions {
  void Pop16(Cpu * cpu, Register16 reg) {
    auto addr = cpu->GetRegister(Register16::SP);
    auto value = cpu->GetMemoryController()->ReadWord(addr);
    cpu->SetRegister(reg, value);
    cpu->SetRegister(Register16::SP, addr + 2);
  }

  void Push16(Cpu* cpu, Register16 reg) {
    auto addr = cpu->GetRegister(Register16::SP);
    auto val = cpu->GetRegister(reg);
    addr -= 2;
    cpu->GetMemoryController()->WriteWord(addr, val);
    cpu->SetRegister(Register16::SP, addr);
  }
}

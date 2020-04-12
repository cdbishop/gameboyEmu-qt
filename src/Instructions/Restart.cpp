#include "Restart.hpp"

#include "Cpu.hpp"
#include "MemoryController.hpp"

void Instructions::Restart(Cpu* cpu, unsigned short target) {
  auto addr = cpu->GetRegister(Register16::SP);
  cpu->GetMemoryController()->WriteWord(addr, cpu->GetPC());

  cpu->SetPC(target);

  cpu->SetRegister(Register16::SP, addr - 2);
}

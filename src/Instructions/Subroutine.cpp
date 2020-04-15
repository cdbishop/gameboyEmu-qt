#include "Subroutine.hpp"

#include "Cpu.hpp"
#include "MemoryController.hpp"

#include "Jump.hpp"
#include "Subroutine.hpp"

namespace Instructions {
  void Call(Cpu* cpu) {
    auto pc = cpu->GetPC();    
    pc += 3; //1-byte call instruction 2-bytes addr
    auto sp = cpu->GetRegister(Register16::SP);
    sp -= 2;
    cpu->GetMemoryController()->WriteWord(sp, pc);

    // decrement sp    
    cpu->SetRegister(Register16::SP, sp);

    JmpImmediate16(cpu);    
  }

  void CallNotZero(Cpu * cpu) {
    if (!cpu->TestFlag(cpu::Flag::Zero)) {
      Call(cpu);
    }
  }

  void CallZero(Cpu * cpu) {
    if (cpu->TestFlag(cpu::Flag::Zero)) {
      Call(cpu);
    }
  }

  void CallNotCarry(Cpu * cpu) {
    if (!cpu->TestFlag(cpu::Flag::Carry)) {
      Call(cpu);
    }
  }

  void CallCarry(Cpu * cpu) {
    if (cpu->TestFlag(cpu::Flag::Carry)) {
      Call(cpu);
    }
  }

  void Ret(Cpu * cpu) {
    auto sp = cpu->GetRegister(Register16::SP);
    auto pc = cpu->GetMemoryController()->ReadWord(sp);

    cpu->SetRegister(Register16::SP, sp + 2);
    cpu->SetPC(pc);
  }

  void RetNotZero(Cpu* cpu) {
    if (!cpu->TestFlag(cpu::Flag::Zero)) {
      Ret(cpu);
    }
  }

  void RetZero(Cpu* cpu) {
    if (cpu->TestFlag(cpu::Flag::Zero)) {
      Ret(cpu);
    }
  }

  void RetCarry(Cpu* cpu) {
    if (cpu->TestFlag(cpu::Flag::Carry)) {
      Ret(cpu);
    }
  }

  void RetNotCarry(Cpu* cpu) {
    if (!cpu->TestFlag(cpu::Flag::Carry)) {
      Ret(cpu);
    }
  }

  void RetEnableInterrupts(Cpu * cpu) {
    Ret(cpu);
    cpu->EnableInterrupts();
  }
}

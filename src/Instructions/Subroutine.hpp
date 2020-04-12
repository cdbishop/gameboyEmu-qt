#pragma once

class Cpu;

namespace Instructions {
  void Call(Cpu* cpu);
  void CallNotZero(Cpu* cpu);
  void CallZero(Cpu* cpu);
  void CallNotCarry(Cpu* cpu);
  void CallCarry(Cpu* cpu);

  void Ret(Cpu* cpu);
  void RetNotZero(Cpu* cpu);
  void RetZero(Cpu* cpu);
  void RetCarry(Cpu* cpu);
  void RetNotCarry(Cpu* cpu);

  void RetEnableInterrupts(Cpu* cpu);
}
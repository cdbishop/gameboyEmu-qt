#pragma once

#include <Instruction.hpp>
#include "Registers.hpp"
#include "Cpu.hpp"

namespace cpu {
class State {
public:
  State()
    :_a(0x01),
    _b(0x00),
    _c(0x13),
    _d(0x00),
    _e(0xd8),
    _flag(0xb0),
    _h(0x01),
    _l(0x4d),
    _pc(0x100),
    _sp(0xfffe),
    _interruptsEnabled(true) {}

  unsigned char ReadRegister(Register8 reg) const;

  unsigned short ReadRegister(Register16 reg) const;

  bool TestFlag(Cpu::Flag flag) const;

  void EnabledInterrupts();
  void DisableInterrupts();
  bool InterruptsEnabled();

public:
  unsigned int _pc;
  unsigned int _sp;

  unsigned int _a;
  unsigned int _b;
  unsigned int _c;
  unsigned int _d;
  unsigned int _e;
  unsigned int _h;
  unsigned int _l;

  unsigned int _flag;

  bool _interruptsEnabled;

  std::vector<Instruction> _history;

};
}
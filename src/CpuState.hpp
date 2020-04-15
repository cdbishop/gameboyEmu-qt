#pragma once

#include <Instruction.hpp>
#include "Registers.hpp"
#include "Cpu.hpp"
#include "cpu/flag.hpp"

#include <qmetatype.h>
#include <boost/circular_buffer.hpp>

namespace cpu {
class State {
public:
  struct Clock {
    unsigned int _m;
    unsigned int _t;

    Clock() :_m(0), _t(0) {}
  };

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
    _interruptsEnabled(true),
    _history(50) {}

  unsigned char ReadRegister(Register8 reg) const;

  unsigned short ReadRegister(Register16 reg) const;

  bool TestFlag(cpu::Flag flag) const;

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

  //boost::circular_buffer<Instruction> _history;
  boost::circular_buffer<std::pair<unsigned short, Instruction>> _history;

  unsigned int _numCycles;
  Clock _clock;
};
}

Q_DECLARE_METATYPE(cpu::State)
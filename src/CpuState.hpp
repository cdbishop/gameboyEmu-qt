#pragma once

#include <Instruction.hpp>
#include "Registers.hpp"

namespace cpu {
  struct State {
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

    std::vector<Instruction> _history;

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
      _sp(0xfffe) {}

    unsigned char ReadRegister(Register8 reg) const {
      switch (reg) {
        case Register8::A:
          return _a;
          break;

        case Register8::B:
          return _b;
          break;

        case Register8::C:
          return _c;
          break;

        case Register8::D:
          return _d;
          break;

        case Register8::E:
          return _e;
          break;

        case Register8::H:
          return _h;
          break;

        case Register8::L:
          return _l;
          break;

        default:
          throw std::invalid_argument("Unknown register");
      }
    }

    unsigned short ReadRegister(Register16 reg) const {
      switch (reg) {
      case Register16::BC:
        return _b << 8 | _c;
        break;

      case Register16::DE:
        return _d << 8 | _e;
        break;

      case Register16::HL:
        return _h << 8 | _l;
        break;

      case Register16::SP:
        return _sp;
        break;

      default:
        throw std::runtime_error("Unknown register");
      }
    }
  };
}
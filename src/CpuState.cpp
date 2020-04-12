#pragma once

#include <Instruction.hpp>
#include "Registers.hpp"
#include "CpuState.hpp"

namespace cpu {
    unsigned char State::ReadRegister(Register8 reg) const {
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

    unsigned short State::ReadRegister(Register16 reg) const {
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

      case Register16::AF:
        return _a << 8 | _flag;
        break;

      case Register16::SP:
        return _sp;
        break;
      

      default:
        throw std::runtime_error("Unknown register");
      }
    }

    bool State::TestFlag(cpu::Flag flag) const {
      switch (flag) {
      case cpu::Flag::Carry:
        return (_flag & 0x10) == 0x10;

      case cpu::Flag::HalfCarry:
        return (_flag & 0x20) == 0x20;

      case cpu::Flag::SubOp:
        return (_flag & 0x40) == 0x40;

      case cpu::Flag::Zero:
        return (_flag & 0x80) == 0x80;

      default:
        throw std::invalid_argument("unknown flag");
      }
    }
    void State::EnabledInterrupts()
    {
      _interruptsEnabled = true;
    }

    void State::DisableInterrupts()
    {
      _interruptsEnabled = false;
    }

    bool State::InterruptsEnabled()
    {
      return _interruptsEnabled;
    }
}
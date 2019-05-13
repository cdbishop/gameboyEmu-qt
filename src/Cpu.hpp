#pragma once
#include "Cart.hpp"
#include "Instruction.hpp"
#include "Registers.hpp"

class Cpu {
public:
  Cpu(const std::shared_ptr<Cart> cart);

  void Step();

  unsigned char ReadByteOffset(unsigned int offset);

  void SetPC(unsigned int address);

  unsigned char GetRegister(Register8 reg);
  void SetRegister(Register8 reg, unsigned char);

  unsigned short GetRegister(Register16 reg);
  void SetRegister(Register16 reg, unsigned short);

private:
  void AdvanceState(const Instruction& instruction);

private:
  std::shared_ptr<Cart> _cart;

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

  unsigned int _numCycles;

  unsigned int _clock_m;
  unsigned int _clock_t;
};
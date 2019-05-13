#pragma once
#include "Cart.hpp"
#include "Instruction.hpp"
#include "Registers.hpp"

class MemoryController;

class Cpu {
public:
  enum class Flag {
    Zero,
    SubOp,
    HalfCarry,
    Carry
  };

  Cpu(const std::shared_ptr<Cart> cart);

  void Step();

  unsigned char ReadByteOffset(unsigned int offset);

  void SetPC(unsigned int address);

  unsigned char GetRegister(Register8 reg);
  void SetRegister(Register8 reg, unsigned char);

  unsigned short GetRegister(Register16 reg);
  void SetRegister(Register16 reg, unsigned short);

  std::shared_ptr<MemoryController> GetMemoryController() {
    return _memoryController;
  }

  void DecRegister(Register8 reg);
  void DecRegister(Register16 reg);

  void IncRegister(Register8 reg);
  void IncRegister(Register16 reg);

  void ClearFlag();  
  void SetFlag(Flag flag);
  bool TestFlag(Flag flag);

private:
  void AdvanceState(const Instruction& instruction);

private:
  std::shared_ptr<Cart> _cart;
  std::shared_ptr<MemoryController> _memoryController;

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
#pragma once
#include "Cart.hpp"
#include "Instruction.hpp"
#include "Registers.hpp"
#include "CpuState.hpp"
#include "CpuStateNotifier.hpp"

class MemoryController;

class Cpu {
public:
  enum class Flag {
    Zero,
    SubOp,
    HalfCarry,
    Carry
  };

  struct Clock {
    unsigned int _m;
    unsigned int _t;

    Clock() :_m(0), _t(0) {}
  };

  Cpu(const std::shared_ptr<Cart> cart, std::unique_ptr<CpuStateNotifier> notifier);

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

  bool Running();

private:
  void AdvanceState(const Instruction& instruction);

private:
  std::shared_ptr<Cart> _cart;
  std::shared_ptr<MemoryController> _memoryController;
  std::unique_ptr<CpuStateNotifier> _stateNotifier;

  cpu::State _state;

  unsigned int _numCycles;

  Clock _clock;
};
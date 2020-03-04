#pragma once
#include "Cart.hpp"
#include "Instruction.hpp"
#include "Registers.hpp"
#include "CpuStateNotifier.hpp"
#include "CpuDebug.hpp"

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

  Cpu(const std::shared_ptr<Cart> cart, std::shared_ptr<CpuStateNotifier> notifier);

  void Step();

  unsigned char ReadByteOffset(unsigned int offset);

  void SetPC(unsigned int address);
  unsigned int GetPC() const;

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

  void ClearFlags();  
  void SetFlag(Flag flag);
  bool TestFlag(Flag flag);
  void ClearFlag(Flag flag);

  bool Running();
  bool Stepping();
  void EnableStepping(bool enable);

  void SetPCDebug(unsigned short pcTarget);
  void SetRegisterDebug(Register8 reg, unsigned char targetValue);
  void SetRegisterDebug(Register16 reg, unsigned short targetValue);

  void RemovePCDebug();
  void RemoveRegisterDebug(Register8 reg);
  void RemoveRegisterDebug(Register16 reg);

  void EnableInterrupts();
  void DisableInterrupts();

private:
  void AdvanceState(const Instruction& instruction);

private:
  std::shared_ptr<Cart> _cart;
  std::shared_ptr<MemoryController> _memoryController;
  std::shared_ptr<CpuStateNotifier> _stateNotifier;

  std::shared_ptr<cpu::State> _state;

  unsigned int _numCycles;

  Clock _clock;

  unsigned int _pcBreakTarget;

  cpu::Debug _debug;

  bool _running;
  bool _stepping;
};
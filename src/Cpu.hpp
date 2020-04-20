#pragma once
#include "Cart.hpp"
#include "Instruction.hpp"
#include "Registers.hpp"
#include "CpuDebug.hpp"
#include "cpu/StateHistory.hpp"
#include "CpuState.hpp"
#include "cpu/flag.hpp"
#include "Input.hpp"

#include <qmetatype.h>

class MemoryController;
class CpuStateNotifier;

class Cpu {
public:  
  using RomInstruction = std::pair<unsigned short, Instruction>;

  Cpu(const std::shared_ptr<Cart> cart, std::shared_ptr<CpuStateNotifier> notifier,
    std::shared_ptr<MemoryController> memoryController);

  void Step();

  std::vector<RomInstruction> DumpRom();

  unsigned char ReadByteOffset(unsigned int offset);
  unsigned short ReadWordOffset(unsigned int offset);

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
  void SetFlag(cpu::Flag flag);
  bool TestFlag(cpu::Flag flag);
  void ClearFlag(cpu::Flag flag);

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

  bool BreakpointHit() const;

  void ResetBreakpointFlag();

  std::shared_ptr<cpu::State> GetState();

  void Stop();

  void UpdateInput(input::State state);

private:
  void AdvanceState(const Instruction& instruction);

private:
  std::shared_ptr<Cart> _cart;
  std::shared_ptr<MemoryController> _memoryController;
  std::shared_ptr<CpuStateNotifier> _stateNotifier;

  std::shared_ptr<cpu::State> _state;
  std::shared_ptr<cpu::StateHistory> _history;

  unsigned int _pcBreakTarget;

  cpu::Debug _debug;

  bool _running;
  bool _stepping;
  bool _breakpoint_hit;
};
#include "Instruction.hpp"

Instruction::Instruction()
  :_asmInstruction("NOOP"),
  _code(0),
  _pcAdvance(0),
  _cycles(0) {}
   

Instruction::Instruction(std::string instruction, int code, unsigned int pcAdvance, int cycles, int size, ExecuteFn impl, OpOrder opOrder)
  :_asmInstruction(instruction),
  _code(code),
  _pcAdvance(pcAdvance),
  _cycles(cycles),
  _size(size),
  _implFn(impl),
  _opOrder(opOrder)
{

}

int Instruction::GetPCAdvance() const
{
  return _pcAdvance;
}

int Instruction::GetCycles() const
{
  return _cycles;
}

int Instruction::GetSize() const 
{
  return _size;
}

Instruction::OpOrder Instruction::GetOpOrder() const
{
  return _opOrder;
}

void Instruction::Execute(Cpu* cpu) const
{
  _implFn(cpu);
}

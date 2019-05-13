#include "Instruction.hpp"

Instruction::Instruction(std::string instruction, int code, unsigned int pcAdvance, int cycles, ExecuteFn impl, OpOrder opOrder)
  :_asmInstruction(instruction),
  _code(code),
  _pcAdvance(pcAdvance),
  _cycles(cycles),
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

Instruction::OpOrder Instruction::GetOpOrder() const
{
  return _opOrder;
}

void Instruction::Execute(Cpu* cpu) const
{
  _implFn(cpu);
}

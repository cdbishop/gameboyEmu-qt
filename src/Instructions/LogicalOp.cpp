#include "LogicalOp.hpp"
#include "Cpu.hpp"

#include <stdexcept>

void Instructions::LogicalOp(Cpu* cpu, Register8 src, Register8 target, Op op)
{
  switch (op) {
    case Op::Xor:
      unsigned char result = cpu->GetRegister(target) ^ cpu->GetRegister(src);
      cpu->SetRegister(target, result);
    break;
  }
}

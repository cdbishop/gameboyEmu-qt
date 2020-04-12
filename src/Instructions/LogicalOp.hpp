#pragma once
#include "Registers.hpp"

class Cpu;

enum class Op {
  Xor,
  And,
  Or
};

namespace Instructions {
  void LogicalOp(Cpu* cpu, Register8 src, Register8 target, Op op);
  void LogicalOpImmediate(Cpu* cpu, Register8 src, Op op);

  void LogicalOpAddr(Cpu* cpu, Register16 addressSrc, Register8 target, Op op);
}
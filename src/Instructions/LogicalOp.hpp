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
}
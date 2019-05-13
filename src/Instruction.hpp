#pragma once
#include <string>
#include <functional>

class Cpu;

class Instruction {
public:
  enum class OpOrder {
    Pre,
    Post
  };

  typedef std::function<void(Cpu*)> ExecuteFn;

  Instruction(std::string instruction, unsigned int pcAdvance, int cycles, ExecuteFn impl, OpOrder opOrder = OpOrder::Post);

  int GetPCAdvance() const;
  int GetCycles() const;
  OpOrder GetOpOrder() const;

  void Execute(Cpu*) const;

private:
  std::string _asmInstruction;
  unsigned int _pcAdvance;
  unsigned int _cycles;
  ExecuteFn _implFn;
  OpOrder  _opOrder;
};
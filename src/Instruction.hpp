#pragma once
#include <string>
#include <functional>
#include <spdlog/fmt/ostr.h>

class Cpu;

class Instruction {
public:
  enum class OpOrder {
    Pre,
    Post
  };

  typedef std::function<void(Cpu*)> ExecuteFn;

  Instruction(std::string instruction, int code, unsigned int pcAdvance, int cycles, ExecuteFn impl, OpOrder opOrder = OpOrder::Post);

  int GetPCAdvance() const;
  int GetCycles() const;
  OpOrder GetOpOrder() const;

  void Execute(Cpu*) const;

  template<typename OStream>
  friend OStream& operator<<(OStream& os, const Instruction& instruction)
  {
    return os << "[asm: " << instruction._asmInstruction << ", code: " << std::hex << instruction._code << "]";
  }

private:
  std::string _asmInstruction;
  int _code;
  unsigned int _pcAdvance;
  unsigned int _cycles;
  ExecuteFn _implFn;
  OpOrder  _opOrder;
};
#pragma once
#include <string>
#include <functional>
#include <spdlog/fmt/ostr.h>

#include <qmetatype.h>

class Cpu;

class Instruction {
public:
  enum class OpOrder {
    Pre,
    Post,
    None
  };

  typedef std::function<void(Cpu*)> ExecuteFn;

  Instruction();
  Instruction(std::string instruction, int code, unsigned int pcAdvance, int cycles, int size, ExecuteFn impl, OpOrder opOrder = OpOrder::Post);  

  int GetPCAdvance() const;
  int GetCycles() const;
  int GetSize() const;
  OpOrder GetOpOrder() const;

  void Execute(Cpu*) const;

  friend std::ostream& operator<<(std::ostream& os, const Instruction& instruction)
  {
    return os << "[asm: " << instruction._asmInstruction << ", code: " << std::hex << instruction._code << "]";
  }

private:
  std::string _asmInstruction;
  int _code;
  unsigned int _pcAdvance;
  unsigned int _cycles;
  unsigned int _size;
  ExecuteFn _implFn;
  OpOrder  _opOrder;
};

Q_DECLARE_METATYPE(Instruction)
#include "Register.hpp"
#include "Cpu.hpp"

#include <stdexcept>

void Instructions::Inc8(Cpu * cpu, Register8 target)
{
  cpu->IncRegister(target);
}

void Instructions::Dec8(Cpu * cpu, Register8 target)
{
  cpu->DecRegister(target);
}

void Instructions::Inc16(Cpu * cpu, Register16 target)
{
  cpu->IncRegister(target);
}

void Instructions::Dec16(Cpu * cpu, Register16 target)
{
  cpu->DecRegister(target);
}

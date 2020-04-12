#pragma once

class Cpu;

namespace Instructions {
  void SetCarryFlag(Cpu* cpu);
  void ClearCarryFlag(Cpu* cpu);
}
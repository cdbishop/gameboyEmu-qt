#pragma once

class Cpu;

namespace Instructions {
  void Restart(Cpu* cpu, unsigned short target);
}
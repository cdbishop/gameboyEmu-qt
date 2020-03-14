#pragma once

#include <vector>

class Instruction;

namespace cpu {

class State;
using StateHistory = std::vector<std::pair<Instruction, cpu::State>>;

}
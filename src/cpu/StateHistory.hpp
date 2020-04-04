#pragma once

#include <vector>

#include <boost/circular_buffer.hpp>

class Instruction;

namespace cpu {

class State;
//using StateHistory = std::vector<std::pair<Instruction, cpu::State>>;
using StateHistory = boost::circular_buffer<std::pair<Instruction, cpu::State>>;
}
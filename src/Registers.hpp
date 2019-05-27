#pragma once
#include <string>

enum class Register8 {
  A,
  B,
  C,
  D,
  E,
  H,
  L
};

enum class Register16 {
  BC,
  DE,
  HL,
  SP
};

Register8 Register8FromString(const std::string& str);

Register16 Register16FromString(const std::string& str);

#pragma once

#include "Registers.hpp"

Register8 Register8FromString(const std::string& str) {
  switch (str[0]) {
    case 'A':
      return Register8::A;

    case 'B':
      return Register8::B;

    case 'C':
      return Register8::C;

    case 'D':
      return Register8::D;

    case 'E':
      return Register8::E;

    case 'H':
      return Register8::H;

    case 'L':
      return Register8::L;

    default:
      throw std::invalid_argument("Unknown register");
  }
}

Register16 Register16FromString(const std::string& str) {
  switch (str[0]) {
    case 'B':
      return Register16::BC;

    case 'D':
      return Register16::DE;

    case 'H':
      return Register16::HL;

    case 'S':
      return Register16::SP;

    case 'A':
      return Register16::AF;

    default:
      throw std::invalid_argument("Unknown register");
  }
}
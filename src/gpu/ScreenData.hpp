#pragma once

#include <array>

namespace gpu {
  const unsigned int Width = 160;
  const unsigned int Height = 144;
  using ScreenData = std::array<std::array<int, Width>, Height>;
}
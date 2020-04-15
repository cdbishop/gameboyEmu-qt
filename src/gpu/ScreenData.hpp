#pragma once

#include <array>
#include <qmetatype.h>

namespace gpu {
  const unsigned int Width = 160;
  const unsigned int Height = 144;
  using ScreenData = std::array<std::array<int, Width>, Height>;

  using TilesetDump = std::array<unsigned int, 8 * 8 * 384>;
}

Q_DECLARE_METATYPE(gpu::ScreenData)
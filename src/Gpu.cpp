#include <Gpu.hpp>

Gpu::Gpu() {
}

void Gpu::Reset() {
  for (int i = 0; i < _screen.max_size(); ++i) {
    _screen[i].fill(0xFFFFFFFF); //RGBA white as bits
  }

  for (int i = 0; i < _tileset.max_size(); ++i) {
    _tileset[i].fill(0);
  }

  _scx = 0;
  _scy = 0;
  _bgmap = false;

  //todo: notify screen data
}

void Gpu::Step(std::shared_ptr<Cpu> cpu) {
  _clock += cpu->GetState()->_clock._t;

  switch(_mode) {
    case Mode::OamRead:
      if (_clock >= 80) {
        _mode = Mode::VramRead;
        _clock = 0;
      }
      break;

    case Mode::VramRead:
      if (_clock >= 172) {
        _mode = Mode::HBlank;
        _clock = 0;

        RenderScanline();
      }
      break;

    case Mode::HBlank:
      if (_clock >= 204) {
        _clock = 0;
        _scanline++;

        if (_scanline == 143) {
          _mode = Mode::VBlank;
          // do something with screen data?
        } else {
          _mode = Mode::OamRead;
        }
      }
      break;

    case Mode::VBlank:
      if (_clock >= 456) {
        _clock = 0;
        _scanline++;

        if (_scanline > 153) {
          _mode = Mode::HBlank;
          _scanline = 0;
        }
      }
      break;
  }
}

void Gpu::WriteVRAMByte(unsigned short address, unsigned char value) {
  _vram[address] = value;
  UpdateTile(address, value);
}

unsigned char Gpu::ReadVRAMByte(unsigned short address) {
  return _vram[address];
}

void Gpu::RenderScanline() {
  //Get VRAM offset for the tilemap
  int map_offset = _bgmap ? 0x1c00 : 0x1800;
  map_offset += ((_scanline + _scy) & 255) >> 3;

  int line_offset = (_scx >> 3);

  int y = (_scanline + _scy) & 7;
  int x = _scx & 7;

  int col = 0;
  int tile = _vram[map_offset + line_offset];

  // compensate for the fact that tileset 1 has signed integer
  if (_bgtile == 1 && tile < 128) tile += 256;

  for (int i = 0; i < 160; ++i) {
    int tile_value = _tileset[tile][y];
    int pallet_idx = (tile_value >> (7 - x));
    int colour = 0;
    switch (pallet_idx) {
      case 0:
        colour = 0xFFFFFFFF;
        break;

      case 1:
        colour = 0xC0C0C0FF;
        break;

      case 2:
        colour = 0x606060FF;
        break;

      case 3:
        colour = 0;
        break;
    }

    _screen[y][x] = colour;

    ++x;

    if (x == 8) {
      x = 0;
      line_offset = (line_offset + 1) & 0x1F;
      tile = _vram[map_offset + line_offset];
      if (_bgtile == 1 && tile < 128) tile += 256;
    }
  }
}

void Gpu::UpdateTile(unsigned short address, unsigned char /*value*/) {
  //update tileset representation based on vram

  // 8000 - 87FF = tileset 1: tiles 0-127
  // 8800 - 8FFF = tileset 1: tiles 128-255
  //             = tileset 0: tiles -1 - -128
  // 9000 - 97FF = tileset 0: tiles 0-127
  // 9800 - 9BFF = tilemap 0
  // 9C00 - 9FFF = tilemap 1

  unsigned short tile = (address >> 4) & 0x1FF; // 0001 1111 1111
  unsigned short y = (address >> 1) & 0x7; // 0111

  unsigned int sx;
  unsigned char value = 0;
  for (unsigned char x = 0; x < 8; ++x) {
    sx = 1 << (7 - x);

    // colour value is stored across two bytes + is the combination of both bits
    // to prodoce value between 0 -3 (representing the 4 grayscale colours)
    // e.g.
    // 0x803E 0 1 0 0 1 1 1 0
    // 0x803F 1 0 0 0 1 0 1 1
    //   =    2 1 0 0 3 1 3 2

    unsigned char bit = _vram[address] & sx ? 1 : 0 +
                          _vram[address + 1] & sx ? 2 : 0;
    value |= (bit << (7 - x));
  }

  _tileset[tile][y] = value;
}

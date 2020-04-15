#include <Gpu.hpp>

#include <spdlog/spdlog.h>

const std::array<unsigned char, 4> PixelWhite = { 255,255,255,255 };
const std::array<unsigned char, 4> PixelLightGrey = { 192,192,192,255 };
const std::array<unsigned char, 4> PixelDarkGrey = { 96,96,96,255 };
const std::array<unsigned char, 4> PixelBlack = { 0,0,0,255 };

Gpu::Gpu(std::shared_ptr<CpuStateNotifier> notifier)
  :_notifier(notifier),
   _mode(Mode::OamRead),
   _clock(0),
   _scanline(0),
   _scx(0),
   _scy(0),
   _bgmap(false),
   _bgtile(false),
   _switchBg(false),
   _switchLcd(false) {
  Reset();
}

void Gpu::Reset() {
  for (int i = 0; i < _screen.max_size(); ++i) {
    _screen[i].fill(0xFFFFFFFF); //RGBA white as bits
  }

  for (int i = 0; i < _tileset.max_size(); ++i) {
    for (int j = 0; j < _tileset[i].max_size(); ++j) {
      _tileset[i][j].fill(0);
    }
  }

  _scx = 0;
  _scy = 0;
  _bgmap = false;

  _notifier->NotifyScreenData(_screen);

  gpu::TilesetDump dump;
  dump.fill(0xFFFFFFFF);
  _notifier->NotifyTilesetData(dump);

  _pallets[0] = PixelWhite;
  _pallets[1] = PixelLightGrey;
  _pallets[2] = PixelDarkGrey;
  _pallets[3] = PixelBlack;
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
          _notifier->NotifyScreenData(_screen);
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
  switch (address & 0xF000) {
    case 0x8000:
    case 0x9000:
      _vram[address & 0x1FFF] = value;
      UpdateTile(address);
      break;

    default:
      throw std::runtime_error("TODO: implement me!");
  }
}

unsigned char Gpu::ReadVRAMByte(unsigned short address) {
  return _vram[address];
}

void Gpu::WriteVRAMWord(unsigned short address, unsigned short value) {
  auto lo = value & 0xFF;
  auto hi = value >> 8;

  _vram[address] = lo;
  _vram[address+1] = hi;

  // TODO: is this needed?
  UpdateTile(address);
  UpdateTile(address+1);
}

unsigned char Gpu::ReadVRAMWord(unsigned short address) {
  unsigned short value = ((unsigned short)_vram[address]) << 8;
  value |= _vram[address + 1];
  return value;
}

void Gpu::WriteRegister(unsigned short address, unsigned char value) {
  switch (address) {
    case 0xFF40:
      _switchBg = (value & 0x01);
      _bgmap = (value & 0x08);
      _bgtile = (value & 0x10);
      _switchLcd = (value & 0x80);
      break;

    case 0xFF42:
      _scy = value;
      break;

    case 0xFF43:
      _scx = value;
      break;

    case 0xFF47:
      for (int i = 0; i < 4; ++i) {
        switch ((value >> (i * 2)) & 3) {
          case 0:
            _pallets[i] = PixelWhite;
            break;

          case 1:
            _pallets[i] = PixelLightGrey;
            break;

          case 2:
            _pallets[i] = PixelDarkGrey;
            break;

          case 3:
            _pallets[i] = PixelBlack;
            break;
        }
      }
      break;
  }
}

unsigned char Gpu::ReadRegister(unsigned short address) {
  switch (address) {
    case 0xFF40:
      return (_switchBg ? 0x01 : 0x00) |
        (_bgmap ? 0x08 : 0x00) |
        (_bgtile ? 0x10 : 0x00) |
        (_switchLcd ? 0x80 : 0x00);
      break;

    case 0xFF42:
      return _scy;
      break;

    case 0xFF43:
      return _scx;
      break;

    case 0xFF44:
      return _scanline;
      break;
  }

  //throw std::runtime_error("Error unexpected address");
}

const gpu::ScreenData & Gpu::GetScreenData() const {
  return _screen;
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
    //int tile_value = _tileset[tile][y];
    //int pallet_idx = (tile_value >> (7 - x));
    int pallet_idx = _tileset[tile][y][x];
    int colour = 0;
    colour |= _pallets[pallet_idx][0] << 24;
    colour |= _pallets[pallet_idx][1] << 16;
    colour |= _pallets[pallet_idx][2] << 8;
    colour |= _pallets[pallet_idx][3];
        
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

void Gpu::UpdateTile(unsigned short address) {
  //update tileset representation based on vram

  // 8000 - 87FF = tileset 1: tiles 0-127
  // 8800 - 8FFF = tileset 1: tiles 128-255
  //             = tileset 0: tiles -1 - -128
  // 9000 - 97FF = tileset 0: tiles 0-127
  // 9800 - 9BFF = tilemap 0
  // 9C00 - 9FFF = tilemap 1

  unsigned address_masked = address & 0x1FFE;

  unsigned short tile = (address_masked >> 4) & 0x1FF; // 0001 1111 1111
  unsigned short y = (address_masked >> 1) & 0x7; // 0111

  //TODO: Hack: tile exceeds limits - probably because of
  //unimplemented parts?
  if (tile >= 0x180) {
    return;
  }

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

    unsigned char bit = (_vram[address_masked] & sx) ? 1 : 0 +
                          (_vram[address_masked + 1] & sx) ? 2 : 0;

    _tileset[tile][y][x] = bit;        

    //DumpTilesets();
  }

  //DumpTilesets();
}

void Gpu::DumpTilesets() const {
  gpu::TilesetDump dump;
  dump.fill(0);

  //TODO: make tileset dump work for all tiles
  //for (auto tile = 0; tile < _tileset.size(); ++tile) {
  for (auto tile = 0; tile < 300; ++tile) {
    for (auto y = 0; y < _tileset[tile].size(); ++y) {
      for (auto x = 0; x < 8; ++x) {
        
        int tile_value = _tileset[tile][y][x];
        //int pallet_idx = (tile_value >> (7 - x));
        int pallet_idx = tile_value;
        unsigned int colour = 0;

        colour |= _pallets[pallet_idx][0] << 24;
        colour |= _pallets[pallet_idx][1] << 16;
        colour |= _pallets[pallet_idx][2] << 8;
        colour |= _pallets[pallet_idx][3];
                
        //unsigned int pixel_idx = (tile * 8) + (y * 192) + x;
        unsigned int pixel_idx = (x + (tile * 8) + (y * 128));
        pixel_idx += (tile / 16) * 128 * 8;

        dump[pixel_idx] = colour;
      }
    }
  }

  //const unsigned int RED = 255 << 24 | 255;
  //const unsigned int GREEN = 255 << 16 | 255;
  //const unsigned int BLUE = 255 << 8 | 255;

  //std::array<unsigned int, 3> cols = { RED, GREEN, BLUE };

  //// fill dump with checkered pattern of 384 8x8 pixels
  ////for (int i = 0; i < 384; ++i) {
  //for (int i = 0; i < 300; ++i) {
  //  for (int y = 0; y < 8; ++y) {
  //    for (int x = 0; x < 8; ++x) {
  //      //unsigned int pixel_idx = x + (y * 384) 
  //      unsigned int pixel_idx = (x + (i * 8) + (y * 128));
  //      //when i > 16, offset needs to include row of tiles
  //      pixel_idx += ((i - 1) / 16) * 128 * 8;        

  //      auto color = cols[i % 3];

  //      dump[pixel_idx] = color;
  //    }
  //  }
  //}


  _notifier->NotifyTilesetData(dump);
}

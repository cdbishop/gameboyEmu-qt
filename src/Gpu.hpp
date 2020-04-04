#pragma once

#include <memory>
#include <array>

#include "Cpu.hpp"

class Gpu {
public:
  enum class Mode {
    OamRead,
    VramRead,
    HBlank,
    VBlank
  };

  explicit Gpu(std::shared_ptr<MemoryController> memoryController);

  void Reset();
  void Step(std::shared_ptr<Cpu> cpu);

  void WriteVRAMByte(unsigned short address, unsigned char value);
  unsigned char ReadVRAMByte(unsigned short address);

private:
  void RenderScanline();
  void UpdateTile(unsigned short address, unsigned char value);

private:
  std::shared_ptr<MemoryController> _memoryController;
  Mode _mode;
  int _clock;
  int _scanline;
  int _scx;
  int _scy;

  std::array<unsigned char, 0x2000> _vram;
  std::array<std::array<int, 160>, 144> _screen;
  std::array<std::array<unsigned char, 8>, 384> _tileset;

  bool _bgmap;
  bool _bgtile;
};
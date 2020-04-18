#pragma once

#include <memory>
#include <array>

#include "Cpu.hpp"
#include "CpuStateNotifier.hpp"
#include "gpu/ScreenData.hpp"

class Gpu {
public:
  enum class Mode {
    OamRead,
    VramRead,
    HBlank,
    VBlank
  };

  explicit Gpu(std::shared_ptr<CpuStateNotifier> notifier);

  void Reset();
  void Step(std::shared_ptr<Cpu> cpu);

  void WriteVRAMByte(unsigned short address, unsigned char value);
  unsigned char ReadVRAMByte(unsigned short address);

  void WriteVRAMWord(unsigned short address, unsigned short value);
  unsigned char ReadVRAMWord(unsigned short address);

  void WriteRegister(unsigned short address, unsigned char value);
  unsigned char ReadRegister(unsigned short address);

  const gpu::ScreenData& GetScreenData() const;

  void DumpTilesets() const;

  const std::array<unsigned char, 0x2000>& GetData() const;

private:
  void RenderScanline();
  void UpdateTile(unsigned short address);

private:
  std::shared_ptr<CpuStateNotifier> _notifier;

  Mode _mode;
  int _clock;
  int _scanline;
  int _scx;
  int _scy;

  std::array<unsigned char, 0x2000> _vram;
  gpu::ScreenData _screen;
  std::array<std::array<std::array<unsigned char, 8>, 8>, 384> _tileset;
  std::array<std::array<unsigned char, 4>, 4> _pallets;

  bool _bgmap;
  bool _bgtile;
  bool _switchBg;
  bool _switchLcd;
};
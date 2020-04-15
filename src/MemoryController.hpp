#pragma once
#include <vector>
#include <Gpu.hpp>

class MemoryController {
public:
  enum class AddressRange {
    BIOS,
    ROM0,
    ROM1,
    VRAM,
    OAM,
    IO,
    ERAM,
    WRAM,
    ZRAM,
  };

  explicit MemoryController(std::shared_ptr<Gpu> gpu);
  ~MemoryController();

  void MapCartData(const std::vector<unsigned char>& data);

  void WriteByte(unsigned short address, unsigned char value);
  void WriteWord(unsigned short address, unsigned short value);

  unsigned char ReadByte(unsigned short address);
  unsigned short ReadWord(unsigned short address);

private:
  AddressRange GetAddressRange(unsigned short address);

private:
  std::shared_ptr<Gpu> _gpu;

  bool _inbios;
  std::vector<unsigned char> _bios;
  std::vector<unsigned char> _rom;
  std::vector<unsigned char> _wram;
  std::vector<unsigned char> _eram;
  std::vector<unsigned char> _zram;
};
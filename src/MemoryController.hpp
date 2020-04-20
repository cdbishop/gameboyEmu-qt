#pragma once
#include <vector>
#include <Gpu.hpp>
#include <qmetatype.h>

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

  MemoryController();

  explicit MemoryController(std::shared_ptr<Gpu> gpu);
  ~MemoryController();

  MemoryController(const MemoryController&) = default;
  MemoryController& operator=(const MemoryController&) = default;

  void MapCartData(const std::vector<unsigned char>& data);

  void WriteByte(unsigned short address, unsigned char value);
  void WriteWord(unsigned short address, unsigned short value);

  unsigned char ReadByte(unsigned short address);
  unsigned short ReadWord(unsigned short address);

  std::string ToString();

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

  unsigned char _input;
};
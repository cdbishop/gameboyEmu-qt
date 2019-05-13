#pragma once
#include <vector>

class MemoryController {
public:
  enum class AddressRange {
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
  ~MemoryController();

  void WriteByte(unsigned short address, unsigned char value);
  void WriteWord(unsigned short address, unsigned short value);

  unsigned char ReadByte(unsigned short address);
  unsigned short ReadWord(unsigned short address);

private:
  AddressRange GetAddressRange(unsigned short address);

private:
  std::vector<unsigned char> _rom;
  std::vector<unsigned char> _wram;
  std::vector<unsigned char> _eram;
  std::vector<unsigned char> _zram;
};
#include "MemoryController.hpp"

MemoryController::MemoryController()
{
}

MemoryController::~MemoryController()
{
}

void MemoryController::WriteByte(unsigned short address, unsigned char value)
{
}

void MemoryController::WriteWord(unsigned short address, unsigned short value)
{
}

unsigned char MemoryController::ReadByte(unsigned short address)
{
  return 0;
}

unsigned short MemoryController::ReadWord(unsigned short address)
{
  return 0;
}

MemoryController::AddressRange MemoryController::GetAddressRange(unsigned short address)
{
  auto matchExtendedRange = [&]() -> AddressRange {
    switch (address & 0x0F00) {
      case 0x000: case 0x100: case 0x200: case 0x300: case 0x400: case 0x500: case 0x600: 
      case 0x700: case 0x800: case 0x900: case 0xA00: case 0xB00: case 0xC00: case 0xD00:
        return AddressRange::WRAM;

      case 0xE00:
        if (address < 0xFEA0) {
          return AddressRange::OAM;
        } else {
          throw std::runtime_error("Unknown address range");
        }
        break;

      case 0xF00:
        if (address >= 0xFF80) {
          return AddressRange::ZRAM;
        }
        else {
          return AddressRange::IO;
        }
        break;

      default:
        throw std::runtime_error("Unknown address range");
    }
  };

  switch (address & 0xF000) {
    case 0x0000:
    case 0x1000:
    case 0x2000:
    case 0x3000:
      return AddressRange::ROM0;

    case 0x4000:
    case 0x5000:
    case 0x6000:
    case 0x7000:
      return AddressRange::ROM1;

    case 0x8000:
    case 0x9000:
      return AddressRange::VRAM;

    case 0xA000:
    case 0xB000:
      return AddressRange::ERAM;

    case 0xC000:
    case 0xD000:
      return AddressRange::WRAM;

    case 0xE000:
      return AddressRange::WRAM;

    case 0xF000:
      return matchExtendedRange();
      break;

    default:
      throw std::runtime_error("Unknown address range");
  }
}

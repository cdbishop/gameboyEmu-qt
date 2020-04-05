#include "MemoryController.hpp"

MemoryController::MemoryController(std::shared_ptr<Gpu> gpu)
  :_inbios(true),
   _gpu(gpu) {
  _bios.resize(0xFF, 0);
  _rom.resize(0x8000, 0);
  _wram.resize(0x4000, 0);
  _eram.resize(0x2000, 0);
  _zram.resize(0x80, 0);
}

MemoryController::~MemoryController()
{
}

void MemoryController::WriteByte(unsigned short address, unsigned char value)
{
  auto range = GetAddressRange(address);
  switch (range) {
    case AddressRange::BIOS:
      throw std::runtime_error("not implemented");
      if (_inbios) {
        //TODO:
      }
    case AddressRange::ROM0:
    case AddressRange::ROM1:
      _rom[address] = value;
      break;

    case AddressRange::VRAM:
      _gpu->WriteVRAMByte(address & 0x1FFF, value);
      break;

    case AddressRange::OAM:
      throw std::runtime_error("not implemented");
      break;

    case AddressRange::IO:
      switch (address & 0x00F0) {
        case 0x40:
        case 0x50:
        case 0x60:
        case 0x70:
          _gpu->WriteRegister(address, value);
      }
      break;

    case AddressRange::ERAM:
      _eram[address & 0x1FFF] = value;
      break;

    case AddressRange::WRAM:
      _wram[address & 0x1FFF] = value;
      break;

    case AddressRange::ZRAM:
      _zram[address & 0x7F] = value;
      break;
    
    default:
      throw std::runtime_error("Unhandled enum case");
      break;
  }
}

void MemoryController::WriteWord(unsigned short address, unsigned short value)
{
  throw std::runtime_error("Not implemented!");
}

unsigned char MemoryController::ReadByte(unsigned short address)
{
  throw std::runtime_error("Not implemented!");
}

unsigned short MemoryController::ReadWord(unsigned short address)
{
  throw std::runtime_error("Not implemented!");
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

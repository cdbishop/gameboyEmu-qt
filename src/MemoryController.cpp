#include "MemoryController.hpp"

#include <sstream>

MemoryController::MemoryController()
  :_inbios(true),
  _gpu(nullptr),
  _input(0) {
  _bios.resize(0xFF, 0);
  _rom.resize(0x8000, 0);
  _wram.resize(0x4000, 0);
  _eram.resize(0x2000, 0);
  _zram.resize(0x80, 0);
}

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

void MemoryController::MapCartData(const std::vector<unsigned char>& data) {
  _rom = data;
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
      _gpu->WriteVRAMByte(address, value);
      break;

    case AddressRange::OAM:
      //throw std::runtime_error("not implemented");
      break;

    case AddressRange::IO:
      switch (address & 0x00F0) {
        case 0x00:
          _input = value;
          break;

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
  auto range = GetAddressRange(address);
  auto lo = value & 0xFF;
  auto hi = value >> 8;

  switch (range) {
  case AddressRange::BIOS:
    throw std::runtime_error("not implemented");
    if (_inbios) {
      //TODO:
    }
  case AddressRange::ROM0:
  case AddressRange::ROM1:
    _rom[address] = lo;
    _rom[address + 1] = hi;
    break;

  case AddressRange::VRAM:
    _gpu->WriteVRAMWord(address & 0x1FFF, value);
    break;

  case AddressRange::OAM:
    throw std::runtime_error("not implemented");
    break;

  case AddressRange::IO:
    throw std::runtime_error("not implemented");
    break;

  case AddressRange::ERAM:
    _rom[address & 0x1FFF] = lo;
    _rom[(address + 1) & 0x1FFF] = hi;
    break;

  case AddressRange::WRAM:
    _wram[address & 0x1FFF] = lo;
    _wram[(address + 1) & 0x1FFF] = hi;
    break;

  case AddressRange::ZRAM:
    _zram[address & 0x7F] = lo;
    _zram[(address + 1) & 0x7F] = hi;
    break;

  default:
    throw std::runtime_error("Unhandled enum case");
    break;
  }
}

unsigned char MemoryController::ReadByte(unsigned short address)
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
    return _rom[address];
    break;

  case AddressRange::VRAM:
    return _gpu->ReadVRAMByte(address & 0x1FFF);
    break;

  case AddressRange::OAM:
    throw std::runtime_error("not implemented");
    break;

  case AddressRange::IO:
    switch (address & 0x00F0) {
    case 0x00:
      return _input;
      break;

      case 0x40:
      case 0x50:
      case 0x60:
      case 0x70:
        return _gpu->ReadRegister(address);
    }
    break;

  case AddressRange::ERAM:
    return _eram[address & 0x1FFF];
    break;

  case AddressRange::WRAM:
    return _wram[address & 0x1FFF];
    break;

  case AddressRange::ZRAM:
    return _zram[address & 0x7F];
    break;

  default:
    throw std::runtime_error("Unhandled enum case");
    break;
  }
}

unsigned short MemoryController::ReadWord(unsigned short address)
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
    {
      unsigned short value = (_rom[address] << 8);
      value |= _rom[address + 1];
      return value;
    }
    break;

  case AddressRange::VRAM:
    return _gpu->ReadVRAMWord(address & 0x1FFF);
    break;

  case AddressRange::OAM:
    throw std::runtime_error("not implemented");
    break;

  case AddressRange::IO:
    throw std::runtime_error("not implemented");
    break;

  case AddressRange::ERAM:
    {
      unsigned short value = (_eram[address + 1 & 0x1FFF] << 8);
      value |= _eram[address & 0x1FFF];
      return value;
    }
    break;

  case AddressRange::WRAM:
    {
      unsigned short value = (_wram[address + 1 & 0x1FFF] << 8);
      value |= _wram[address & 0x1FFF];
      return value;
    }
    break;

  case AddressRange::ZRAM:
    {
      unsigned short value = (_zram[address + 1 & 0x7F] << 8);
      value |= _zram[address & 0x7F];
      return value;
    }
    break;

  default:
    throw std::runtime_error("Unhandled enum case");
    break;
  }
}

std::string MemoryController::ToString() {
  std::stringstream ss;
  const int line_length = 0x10;
  for (int i = 0; i < _rom.size(); i += line_length) {
    ss << std::hex << i << ": ";
    for (int c = 0; c < line_length; ++c) {
      if ((i + c) >= _rom.size())
        break;
      ss << std::hex << static_cast<unsigned int>(_rom[i + c]) << " ";
    }
    ss << std::endl;
  }
  
  const auto& vram = _gpu->GetData();
  int offset = _rom.size();
  for (int i = 0; i < vram.size(); i += line_length) {
    ss << std::hex << offset + i << ": ";
    for (int c = 0; c < line_length; ++c) {
      if ((i + c) >= vram.size())
        break;
      ss << std::hex << static_cast<unsigned int>(vram[i + c]) << " ";
    }
    ss << std::endl;
  }

  offset += vram.size();
  for (int i = 0; i < _eram.size(); i += line_length) {
    ss << std::hex << offset + i << ": ";
    for (int c = 0; c < line_length; ++c) {
      if ((i + c) >= _eram.size())
        break;
      ss << std::hex << static_cast<unsigned int>(_eram[i + c]) << " ";
    }
    ss << std::endl;
  }

  offset += _eram.size();
  for (int i = 0; i < _wram.size(); i += line_length) {
    ss << std::hex << offset + i << ": ";
    for (int c = 0; c < line_length; ++c) {
      if ((i + c) >= _wram.size())
        break;
      ss << std::hex << static_cast<unsigned int>(_wram[i + c]) << " ";
    }
    ss << std::endl;
  }

  offset += _wram.size();
  for (int i = 0; i < _zram.size(); i += line_length) {
    ss << std::hex << offset + i << ": ";
    for (int c = 0; c < line_length; ++c) {
      if ((i + c) >= _zram.size())
        break;
      ss << std::hex << static_cast<unsigned int>(_zram[i + c]) << " ";
    }
    ss << std::endl;
  }

  return ss.str();
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

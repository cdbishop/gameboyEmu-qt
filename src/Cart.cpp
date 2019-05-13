#include "Cart.hpp"

#include <fstream>
#include <map>

enum class RomDataOffset {
  NameStart = 0x134,
  NameEnd = 0x142,
  SysType = 0x143,
  FunctionReq = 0x146,
  CartType = 0x147,
  RomSize = 0x148,
  RomBanks = 0x149
};

static std::map<unsigned int, Cart::RomType> s_romTypeLookup;

Cart::Cart(std::string filename) {
  std::ifstream file(filename, std::ios::binary);
  file.seekg(0, std::ios::end);
  std::streampos fileSize = file.tellg();
  file.seekg(0, std::ios::beg);

  _buffer.resize(fileSize);
  file.read(reinterpret_cast<char*>(&_buffer[0]), fileSize);
  file.close();

  ReadName();
  ReadHeader();
}

unsigned char Cart::ReadByte(unsigned short address)
{
  return _buffer[address];
}

void Cart::ReadName() {
  // name
  std::vector<unsigned char>::const_iterator first = _buffer.begin() + (int)RomDataOffset::NameStart;
  std::vector<unsigned char>::const_iterator last = _buffer.begin() + (int)RomDataOffset::NameEnd;
  std::vector<unsigned char> name(first, last);
  _name = std::string(name.begin(), name.end());
}

void Cart::ReadHeader() {
  if (_buffer[(int)RomDataOffset::SysType] == 0x80) {
    _type = SysType::GBC;
  }
  else {
    _type = SysType::GB;
  }

  _sgb = _buffer[(int)RomDataOffset::FunctionReq] == 0x3;
  _romType = s_romTypeLookup[_buffer[(int)RomDataOffset::CartType]];
  _size = _buffer[(int)RomDataOffset::RomSize];
  switch (_buffer[(int)RomDataOffset::RomBanks]) {
    case 0:
      _numBanks = 0;
      _ramSize = 0;
      break;

    case 1:
      _numBanks = 1;
      _ramSize = 2;
      break;

    case 2:
      _numBanks = 1;
      _ramSize = 8;
      break;

    case 3:
      _numBanks = 4;
      _ramSize = 32;
      break;

    case 4:
      _numBanks = 16;
      _ramSize = 128;
      break;

    default:
      throw std::runtime_error("Error reading rombanks");
      break;
  }
}
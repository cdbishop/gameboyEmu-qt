#pragma once
#include <string>
#include <vector>

class Cart {
public:
  enum class SysType {
    GB,
    GBC
  };

  enum class RomType {
    Rom,
    RomMBC1,
    RomMBC1_RAM,
    RomMBC1_RAM_BATT,
    RomMBC2,
    RomMBC2_BATT,
    RomRAM,
    RomRAM_BATT,
    RomMMM01,
    RomMMM01_SRM,
    RomMMM01_SRM_BATT,
    RomMBC3_TIMER_BATT,
    RomMBC3_TIMER_RAM_BATT,
    RomMBC3,
    RomMBC3_RAM,
    RomMBC3_RAM_BATT,
    RomMBC5,
    RomMBC5_RAM,
    RomMBC5_RAM_BATT,
    RomMBC5_RUMBLE,
    RomMBC5_RUBMLE_SRM,
    RomMBC5_RUMBLE_SRM_BATT,
    PocketCamera,
    Bandi_TAMA5,
    Hudson_HuC_3,
    Hudson_Huc_1
  };

  Cart(std::string filename);

  unsigned char ReadByte(unsigned short address);

private:
  void ReadName();
  void ReadHeader();

private:
  std::vector<unsigned char> _buffer;
  std::string _name;
  SysType _type;
  bool _sgb;
  RomType _romType;
  unsigned int _size;
  unsigned int _numBanks;
  unsigned int _ramSize;
};
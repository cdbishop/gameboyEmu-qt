#include "CpuManager.hpp"
#include "spdlog/spdlog.h"

namespace cpu {

Manager::Manager(std::shared_ptr<CpuStateNotifierQt> notifier)
  :_stateNotifier(notifier),
   _threadRunning(false) {
}

void Manager::LoadFile(const std::string& file) {
  _cart = std::make_shared<Cart>(file);
  _cpu = std::make_shared<Cpu>(_cart, _stateNotifier);

  auto rom_instructions = _cpu->DumpRom();
  _stateNotifier->NotifyRomData(rom_instructions);

  _runThread = std::thread([&]() {
    while (true) {
      while (_threadRunning && _cpu->Running() && !_cpu->Stepping()) {
        std::lock_guard lk(_lock);
        _cpu->Step();
      }
    }
  });
}

void Manager::Step() {
  std::lock_guard lk(_lock);
  _cpu->Step();
}

void Manager::Run() {
  if (_threadRunning)
    return;

  std::lock_guard lk(_lock);
  _threadRunning = true;

  // TODO: this needs to be separate thread.
  spdlog::get("console")->debug("Received Run signal");
  _cpu->EnableStepping(false);
}

void Manager::Pause() {
  std::lock_guard lk(_lock);
  _threadRunning = false;
  _cpu->EnableStepping(true);
}

void Manager::SetPCBreak(unsigned int pcTarget) {
  std::lock_guard lk(_lock);
  _cpu->SetPCDebug(pcTarget);
}

void Manager::SetRegBreak(const std::string& regValue, unsigned int targetValue) {
  std::lock_guard lk(_lock);
  if (regValue.length() == 1) {
    Register8 reg = Register8FromString(regValue);
    _cpu->SetRegisterDebug(reg, targetValue);
  } else if (regValue.length() == 2) {
    Register16 reg = Register16FromString(regValue);
    _cpu->SetRegisterDebug(reg, targetValue);
  } else {
    throw std::invalid_argument("Unknown reg type");
  }

}

void Manager::RemoveRegBreak(const std::string& regValue) {
  std::lock_guard lk(_lock);
  if (regValue.length() == 1) {
    Register8 reg = Register8FromString(regValue);
    _cpu->RemoveRegisterDebug(reg);
  } else if (regValue.length() == 2) {
    if (regValue == "PC") {
      _cpu->RemovePCDebug();
    } else {
      Register16 reg = Register16FromString(regValue);
      _cpu->RemoveRegisterDebug(reg);
    }
  } else {
    throw std::invalid_argument("Unknown reg type");
  }
}

}  // namespace cpu

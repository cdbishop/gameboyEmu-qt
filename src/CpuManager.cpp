#include "CpuManager.hpp"
#include "spdlog/spdlog.h"

namespace cpu {

Manager::Manager(std::shared_ptr<CpuStateNotifierQt> notifier)
  :_stateNotifier(notifier),
   _threadRunning(false) {
}

void Manager::LoadFile(const std::string& file) {
  _cart = std::make_shared<Cart>(file);
  _memoryController = std::make_shared<MemoryController>();
  _cpu = std::make_shared<Cpu>(_cart, _stateNotifier, _memoryController);
  _gpu = std::make_shared<Gpu>(_memoryController);

  auto rom_instructions = _cpu->DumpRom();
  _stateNotifier->NotifyRomData(rom_instructions);

  _runThread = std::thread([&]() {
    while (true) {
      while (_threadRunning && _cpu->Running()) {
        if (_currentRunSpeed == RunSpeed::Stepping)
          std::this_thread::sleep_for(std::chrono::seconds(1));
        else
          std::this_thread::sleep_for(std::chrono::milliseconds(10));

        std::lock_guard lk(_lock);
        // TODO: cpu needs proper timing
        _cpu->Step();

        if (_cpu->BreakpointHit()) {
          _threadRunning = false;
          _cpu->EnableStepping(true);
        }

        _cpu->ResetBreakpointFlag();
      }
    }
  });
}

void Manager::Step() {
  std::lock_guard lk(_lock);
  _cpu->Step();
  _cpu->ResetBreakpointFlag();

  _gpu->Step(_cpu);
}

void Manager::Run(RunSpeed speed) {
  if (_threadRunning)
    return;

  std::lock_guard lk(_lock);
  _threadRunning = true;

  _currentRunSpeed = speed;

  // TODO: this needs to be separate thread.
  spdlog::get("console")->debug("Received Run signal");
  _cpu->EnableStepping(_currentRunSpeed == RunSpeed::Stepping);
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

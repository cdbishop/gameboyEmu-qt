#pragma once
#include <memory>
#include <string>
#include <CpuStateNotifierQt.hpp>
#include <Cpu.hpp>
#include <Gpu.hpp>
#include <Cart.hpp>
#include <RunSpeed.hpp>
#include <MemoryController.hpp>

#include <thread>
#include <mutex>
#include <atomic>

namespace cpu {

class Manager final {
public:
  Manager(std::shared_ptr<CpuStateNotifierQt> notifier);

  void LoadFile(const std::string& file);

  void Step();

  void Run(RunSpeed speed);

  void Pause();

  void SetPCBreak(unsigned int pcTarget);

  void SetRegBreak(const std::string& regValue, unsigned int targetValue);

  void RemoveRegBreak(const std::string& regValue);

private:
  std::mutex _lock;
  std::shared_ptr<MemoryController> _memoryController;
  std::shared_ptr<Cart> _cart;
  std::shared_ptr<Cpu> _cpu;
  std::shared_ptr<Gpu> _gpu;
  std::shared_ptr<CpuStateNotifierQt> _stateNotifier;

  std::thread _runThread;
  std::atomic<bool> _threadRunning;
  RunSpeed _currentRunSpeed;
  unsigned int _clocksPerFrame;
};

}

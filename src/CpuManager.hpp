#pragma once
#include <memory>
#include <string>
#include <CpuStateNotifierQt.hpp>
#include <Cpu.hpp>
#include <Cart.hpp>

#include <thread>
#include <mutex>
#include <atomic>

namespace cpu {

class Manager final {
public:
  Manager(std::shared_ptr<CpuStateNotifierQt> notifier);

  void LoadFile(const std::string& file);

  void Step();

  void Run();

  void Pause();

  void SetPCBreak(unsigned int pcTarget);

  void SetRegBreak(const std::string& regValue, unsigned int targetValue);

  void RemoveRegBreak(const std::string& regValue);

private:
  std::mutex _lock;
  std::shared_ptr<Cart> _cart;
  std::shared_ptr<Cpu> _cpu;
  std::shared_ptr<CpuStateNotifierQt> _stateNotifier;

  std::thread _runThread;
  std::atomic<bool> _threadRunning;
};

}

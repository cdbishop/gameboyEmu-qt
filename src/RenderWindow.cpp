#include "RenderWindow.hpp"

#include "Cart.hpp"
#include "Cpu.hpp"
#include "DebugWindow.hpp"

#include <qmenubar.h>
#include <qmenu.h>
#include <qboxlayout.h>

#include "spdlog/spdlog.h"

#include <memory>

RenderWindow::RenderWindow(std::shared_ptr<cpu::Manager> cpuManager, DebugWindow* debugWindow, QWidget* parent)
  :QWidget(parent),
   _cpuManager(cpuManager),
  _debugWindow(debugWindow) {
  
  _canvasTest = new SFMLCanvasTest(this, QPoint(0, 0), QSize(360, 360));
  _canvasTest->show();

  resize(QSize(360, 360));

  _openAction = new QAction(tr("&New"), this);
  _openAction->setStatusTip(tr("Open rom file"));
  connect(_openAction, &QAction::triggered, this, &RenderWindow::OpenFile);

  _fileMenu = new QMenuBar();
  auto file = new QMenu(tr("Open"));

  _fileMenu->addMenu(file);
  file->addAction(_openAction);

  QVBoxLayout* layout = new QVBoxLayout();
  layout->setMenuBar(_fileMenu);

  setLayout(layout);

  connect(_debugWindow, &DebugWindow::Next, this, &RenderWindow::OnNext);
  connect(_debugWindow, &DebugWindow::Run, this, &RenderWindow::CpuRun);
  connect(_debugWindow, &DebugWindow::Pause, this, &RenderWindow::CpuPause);
  connect(_debugWindow, &DebugWindow::SetPCBreak, this, &RenderWindow::OnSetPCBreak);
  connect(_debugWindow, &DebugWindow::SetRegBreak, this, &RenderWindow::OnSetRegBreak);

  connect(_debugWindow, &DebugWindow::RemovePCBreak, this, &RenderWindow::OnRemovePCBreak);
  connect(_debugWindow, &DebugWindow::RemoveRegBreak, this, &RenderWindow::OnRemoveRegBreak);
}

RenderWindow::~RenderWindow()
{
}

void RenderWindow::CpuStep()
{
  _cpuManager->Step();
}

void RenderWindow::CpuRun()
{
  _cpuManager->Run();
}

void RenderWindow::CpuPause()
{
  _cpuManager->Pause();
}

void RenderWindow::OnNext()
{
  spdlog::get("console")->debug("Recieved Next Signal from debug");
  CpuStep();
}

void RenderWindow::OnSetPCBreak(unsigned int pcTarget)
{
  spdlog::get("console")->debug("SetPCBreak signal: breaking on {}", pcTarget);
  _cpuManager->SetPCBreak(pcTarget);
}

void RenderWindow::OnSetRegBreak(const std::string& regValue, unsigned int targetValue)
{
  _cpuManager->SetRegBreak(regValue, targetValue);
}

void RenderWindow::OnRemovePCBreak()
{
}

void RenderWindow::OnRemoveRegBreak(const std::string& regValue)
{

  _cpuManager->RemoveRegBreak(regValue);
}

void RenderWindow::OpenFile()
{
  _cpuManager->LoadFile("roms\\tetris.gb");
}

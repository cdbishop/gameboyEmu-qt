#include "RenderWindow.hpp"

#include "Cart.hpp"
#include "Cpu.hpp"
#include "Gpu.hpp"
#include "DebugWindow.hpp"

#include <qmenubar.h>
#include <qmenu.h>
#include <qboxlayout.h>
#include <qevent.h>

#include "spdlog/spdlog.h"

#include <memory>

RenderWindow::RenderWindow(std::shared_ptr<cpu::Manager> cpuManager, DebugWindow* debugWindow, QWidget* parent)
  :QWidget(parent),
   _cpuManager(cpuManager),
  _debugWindow(debugWindow) {

  static const unsigned int MenuBarHeight = 20;
  _renderBuffer = new SFMLBuffer(this, QPoint(0, MenuBarHeight), QSize(gpu::Width, gpu::Height));
  _renderBuffer->show();

  resize(QSize(gpu::Width, gpu::Height + MenuBarHeight));

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

void RenderWindow::CpuRun(RunSpeed speed)
{
  _cpuManager->Run(speed);
}

void RenderWindow::CpuPause()
{
  _cpuManager->Pause();
}

void RenderWindow::SetStateNotifier(std::shared_ptr<CpuStateNotifierQt> notifier) {
  bool ret = connect(notifier.get(), &CpuStateNotifierQt::NotifyScreenDataSignal, this, &RenderWindow::OnNotifyScreenDataSignal);
}

void RenderWindow::keyPressEvent(QKeyEvent* event) {
  auto key = event->key();
  input::State state = _cpuManager->GetInput();

  if (event->isAutoRepeat())
    return;
  
  switch (key) {
    case Qt::Key_Up:
      state |= input::button::Up;
      break;

    case Qt::Key_Down:
      state |= input::button::Down;
      break;

    case Qt::Key_Left:
      state |= input::button::Left;
      break;

    case Qt::Key_Right:
      state |= input::button::Right;
      break;

    case Qt::Key_Z:
      state |= input::button::A;
      //A
      break;

    case Qt::Key_X:
      state |= input::button::B;
      //B
      break;

    case Qt::Key_A:
      state |= input::button::Select;
      //Select
      break;

    case Qt::Key_S:
      state |= input::button::Start;
      //Start
      break;
  }

  _cpuManager->UpdateInput(state);
}

void RenderWindow::keyReleaseEvent(QKeyEvent * event) {
  auto key = event->key();
  auto state = _cpuManager->GetInput();

  if (event->isAutoRepeat())
    return;

  switch (key) {
    case Qt::Key_Up:
      state &= ~input::button::Up;
      break;

    case Qt::Key_Down:
      state &= ~input::button::Down;
      break;

    case Qt::Key_Left:
      state &= ~input::button::Left;
      break;

    case Qt::Key_Right:
      state &= ~input::button::Right;
      break;

    case Qt::Key_Z:      
      //A
      state &= ~input::button::A;
      break;

    case Qt::Key_X:
      //B
      state &= ~input::button::B;
      break;

    case Qt::Key_A:
      //Select
      state &= ~input::button::Select;
      break;

    case Qt::Key_S:
      //Start
      state &= ~input::button::Start;
      break;
  }

  _cpuManager->UpdateInput(state);
}

void RenderWindow::OnNotifyScreenDataSignal(const gpu::ScreenData& data) {
  _renderBuffer->Draw(data);
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
  //_cpuManager->LoadFile("roms\\tetris.gb");
  //_cpuManager->LoadFile("roms\\opusgames_test5.gb");
  //_cpuManager->LoadFile("roms\\opusgames_test1.gb");
  //_cpuManager->LoadFile("roms\\01-special.gb");

  // this is the same test rom as imran
  _cpuManager->LoadFile("roms\\opus5.gb");
}

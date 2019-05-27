#include "RenderWindow.hpp"

#include "Cart.hpp"
#include "Cpu.hpp"
#include "DebugWindow.hpp"

#include <qmenubar.h>
#include <qmenu.h>
#include <qboxlayout.h>

#include "spdlog/spdlog.h"

#include <memory>

RenderWindow::RenderWindow(std::unique_ptr<CpuStateNotifierQt> notifier, DebugWindow* debugWindow, QWidget* parent)
  :QWidget(parent),
   _cart(nullptr), 
   _cpu(nullptr),
  _stateNotifier(std::move(notifier)),
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
}

RenderWindow::~RenderWindow()
{
}

void RenderWindow::CpuStep()
{
  _cpu->Step();
}

void RenderWindow::CpuRun()
{
  while (_cpu->Running()) {
    _cpu->Step();
  }
}

void RenderWindow::OnNext()
{
  spdlog::get("console")->debug("Recieved Next Signal from debug");
  CpuStep();
}

void RenderWindow::OpenFile()
{
  /*std::shared_ptr<Cart> cart = std::make_shared<Cart>("roms\\tetris.gb");
  Cpu cpu(cart);*/

  //while (true) {
  //  cpu.Step();
  //}

  _cart = std::make_shared<Cart>("roms\\tetris.gb");  
  _cpu = std::make_shared<Cpu>(_cart, std::move(_stateNotifier));
  _stateNotifier = nullptr;
}

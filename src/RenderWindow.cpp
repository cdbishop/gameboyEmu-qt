#include "RenderWindow.hpp"

#include "Cart.hpp"
#include "Cpu.hpp"

#include <qmenubar.h>
#include <qmenu.h>
#include <qboxlayout.h>

#include <memory>

RenderWindow::RenderWindow(QWidget* parent)
  :QWidget(parent) {
  
  _canvasTest = new SFMLCanvasTest(this, QPoint(0, 0), QSize(360, 360));
  _canvasTest->show();

  resize(QSize(360, 360));

  _openAction = new QAction(tr("&New"), this);
  _openAction->setStatusTip(tr("Open rom file"));
  connect(_openAction, &QAction::triggered, this, &RenderWindow::OpenFile);

  _fileMenu = new QMenuBar();
  auto file = new QMenu(tr("Open"));

  //_fileMenu->addMenu("&File");
  _fileMenu->addMenu(file);
  file->addAction(_openAction);

  QVBoxLayout* layout = new QVBoxLayout();
  layout->setMenuBar(_fileMenu);

  setLayout(layout);
}

RenderWindow::~RenderWindow()
{
}

void RenderWindow::OpenFile()
{
  std::shared_ptr<Cart> cart = std::make_shared<Cart>("roms\\tetris.gb");
  Cpu cpu(cart);

  while (true) {
    cpu.Step();
  }
}

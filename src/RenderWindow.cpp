#include "RenderWindow.hpp"

#include <qmenubar.h>
#include <qboxlayout.h>

RenderWindow::RenderWindow(QWidget* parent)
  :QWidget(parent) {
  
  _canvasTest = new SFMLCanvasTest(this, QPoint(0, 0), QSize(360, 360));
  _canvasTest->show();

  resize(QSize(360, 360));

  _openAction = new QAction(tr("&New"), this);
  _openAction->setStatusTip(tr("Open rom file"));
  connect(_openAction, &QAction::triggered, this, &RenderWindow::OpenFile);

  _fileMenu = new QMenuBar();
  _fileMenu->addMenu("&File");

  QVBoxLayout* layout = new QVBoxLayout();
  layout->setMenuBar(_fileMenu);

  setLayout(layout);
}

RenderWindow::~RenderWindow()
{
}

void RenderWindow::OpenFile()
{

}

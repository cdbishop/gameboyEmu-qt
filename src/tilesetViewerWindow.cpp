#include "TilesetViewerWindow.hpp"

#include "Cart.hpp"
#include "Cpu.hpp"
#include "Gpu.hpp"
#include "DebugWindow.hpp"

#include <qmenubar.h>
#include <qmenu.h>
#include <qboxlayout.h>

#include "spdlog/spdlog.h"

#include <memory>

TilesetViewerWindow::TilesetViewerWindow(QWidget* parent)
  :QWidget(parent) {

  _renderBuffer = new SFMLBuffer(this, QPoint(0, 0), QSize(128, 192));
  _renderBuffer->show();

  resize(QSize(128, 192));
}

TilesetViewerWindow::~TilesetViewerWindow()
{
}

void TilesetViewerWindow::SetStateNotifier(std::shared_ptr<CpuStateNotifierQt> notifier) {
  bool ret = connect(notifier.get(), &CpuStateNotifierQt::NotifyTileDataSignal, this, &TilesetViewerWindow::OnNotifyTileDataSignal);
}

void TilesetViewerWindow::OnNotifyTileDataSignal(const gpu::TilesetDump& data) {
  _renderBuffer->Draw(data);
}


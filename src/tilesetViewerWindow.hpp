#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qmenu.h>

#include "SFMLBuffer.hpp"
#include "CpuStateNotifierQt.hpp"


class TilesetViewerWindow : public QWidget
{
  Q_OBJECT
public:
  TilesetViewerWindow(QWidget* parent = 0);
  ~TilesetViewerWindow();

  void SetStateNotifier(std::shared_ptr<CpuStateNotifierQt> notifier);

private:
  void OnNotifyTileDataSignal(const gpu::TilesetDump& data);

private:
  SFMLBuffer* _renderBuffer;
  
  std::unique_ptr<CpuStateNotifierQt> _stateNotifier;
};


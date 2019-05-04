#pragma once
#include <SFML/Graphics.hpp>
#include <QtWidgets/qwidget.h>
#include <qtimer.h>

class SFMLCanvas : public QWidget, public sf::RenderWindow
{
public:
  SFMLCanvas(QWidget* parent, const QPoint& position, const QSize& size, unsigned int frameTime = 0);

  virtual ~SFMLCanvas();

private:
  virtual void OnInit();

  virtual void OnUpdate();

  virtual QPaintEngine* paintEngine() const;

  virtual void showEvent(QShowEvent*);

  virtual void paintEvent(QPaintEvent*);

private:
  QTimer _updateTimer;
  bool _initialised;
};
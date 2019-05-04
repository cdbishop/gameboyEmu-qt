#pragma once
#include "SFMLCanvas.hpp"

class SFMLCanvasTest : public SFMLCanvas
{
public:
  SFMLCanvasTest(QWidget* parent, const QPoint& position, const QSize& size);

  virtual ~SFMLCanvasTest();

private:
  void OnInit();
  void OnUpdate();

private:
  sf::RectangleShape _pixel;
};
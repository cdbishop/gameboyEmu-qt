#include "SFMLCanvasTest.hpp"

SFMLCanvasTest::SFMLCanvasTest(QWidget * parent, const QPoint & position, const QSize & size)
  :SFMLCanvas(parent, position, size)
{
}

SFMLCanvasTest::~SFMLCanvasTest()
{
  
}

void SFMLCanvasTest::OnInit()
{
  _pixel.setPosition(sf::Vector2f(30, 30));
  _pixel.setSize(sf::Vector2f(10, 10));
  _pixel.setFillColor(sf::Color(255, 255, 255));
}

void SFMLCanvasTest::OnUpdate()
{
  clear(sf::Color(0, 128, 0));

  draw(_pixel);
}

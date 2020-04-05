#pragma once
#include "SFMLCanvas.hpp"

#include "gpu/ScreenData.hpp"

class SFMLBuffer : public SFMLCanvas
{
public:
  SFMLBuffer(QWidget* parent, const QPoint& position, const QSize& size);

  virtual ~SFMLBuffer();

  void Draw(const gpu::ScreenData& data);

private:
  void OnInit();
  void OnUpdate();

private:
  std::array<sf::Uint8, gpu::Width * gpu::Height * 4> _pixels;
  sf::Texture _texture;
  sf::Sprite _buffer;
};
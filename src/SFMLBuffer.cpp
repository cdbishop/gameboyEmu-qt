#include "SFMLBuffer.hpp"

SFMLBuffer::SFMLBuffer(QWidget* parent, const QPoint& position, const QSize& size)
  :SFMLCanvas(parent, position, size)
{
  _pixels.resize(size.width() * size.height() * 4, 0);
}

SFMLBuffer::~SFMLBuffer()
{
  
}
void SFMLBuffer::Draw(const gpu::ScreenData& data) {
  std::fill(_pixels.begin(), _pixels.end(), 0);

  unsigned int pixel_idx = 0;
  for (auto i = 0; i < data.size(); ++i) {
    for (auto j = 0; j < data[i].size(); ++j) {
      _pixels[pixel_idx++] = (data[i][j] >> 24) & 0xFF;
      _pixels[pixel_idx++] = (data[i][j] >> 16) & 0xFF;
      _pixels[pixel_idx++] = (data[i][j] >> 8) & 0xFF;
      _pixels[pixel_idx++] = data[i][j] & 0xFF;
    }
  }

  _texture.update(_pixels.data());
}

void SFMLBuffer::OnInit()
{
  _texture.create(getSize().x, getSize().y);
  _buffer.setTexture(_texture);
}

void SFMLBuffer::OnUpdate()
{
  clear(sf::Color(0, 0, 0));

  draw(_buffer);
}

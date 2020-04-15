#pragma once
#include "SFMLCanvas.hpp"

#include "gpu/ScreenData.hpp"

class SFMLBuffer : public SFMLCanvas
{
public:
  SFMLBuffer(QWidget* parent, const QPoint& position, const QSize& size);

  virtual ~SFMLBuffer();

  void Draw(const gpu::ScreenData& data);

  template<size_t Size>
  void Draw(const std::array<unsigned int, Size>& data);

private:
  void OnInit();
  void OnUpdate();

private:
  //std::array<sf::Uint8, gpu::Width * gpu::Height * 4> _pixels;
  std::vector<sf::Uint8> _pixels;
  sf::Texture _texture;
  sf::Sprite _buffer;
};

template<size_t Size>
inline void SFMLBuffer::Draw(const std::array<unsigned int, Size>& data) {
  std::fill(_pixels.begin(), _pixels.end(), 0);

  unsigned int pixel_idx = 0;
  for (auto i = 0; i < data.size(); ++i) {
    _pixels[pixel_idx++] = (data[i] >> 24) & 0xFF;
    _pixels[pixel_idx++] = (data[i] >> 16) & 0xFF;
    _pixels[pixel_idx++] = (data[i] >> 8) & 0xFF;
    _pixels[pixel_idx++] = data[i] & 0xFF;
  }

  _texture.update(_pixels.data());
}

#include "SFMLCanvas.hpp"

SFMLCanvas::SFMLCanvas(QWidget * parent, const QPoint & position, const QSize & size, unsigned int frameTime)
  :QWidget(parent),
  _initialised(false)
{
  // disables Qt paint functions
  setAttribute(Qt::WA_PaintOnScreen);
  setAttribute(Qt::WA_OpaquePaintEvent);
  setAttribute(Qt::WA_NoSystemBackground);

  // Required for keyboard events?
  setFocusPolicy(Qt::StrongFocus);

  move(position);
  resize(size);

  _updateTimer.setInterval(frameTime);
}

SFMLCanvas::~SFMLCanvas()
{
}

void SFMLCanvas::OnInit()
{
}

void SFMLCanvas::OnUpdate()
{
}

QPaintEngine * SFMLCanvas::paintEngine() const
{
  //ensures any qt paint requests are disabled
  return 0;
}

void SFMLCanvas::showEvent(QShowEvent *)
{
  if (!_initialised) {    
    sf::Window::create(reinterpret_cast<sf::WindowHandle>(winId()));

    OnInit();

    connect(&_updateTimer, SIGNAL(timeout()), this, SLOT(repaint()));
    _updateTimer.start();

    _initialised = true;
  }
}

void SFMLCanvas::paintEvent(QPaintEvent *)
{
  OnUpdate();

  display();
}

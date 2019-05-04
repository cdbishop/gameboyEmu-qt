#include <QtWidgets/qapplication.h>
#include <QtWidgets/qpushbutton.h>

#include "RenderWindow.hpp"
#include "DebugWindow.hpp"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  RenderWindow mw;
  mw.show();

  DebugWindow debugWindow;
  debugWindow.show();

  return app.exec();
  
}
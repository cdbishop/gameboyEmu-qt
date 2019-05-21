#include <QtWidgets/qapplication.h>
#include <QtWidgets/qpushbutton.h>

#include "RenderWindow.hpp"
#include "DebugWindow.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

int main(int argc, char** argv) {
  spdlog::stdout_color_mt("console");
  spdlog::set_level(spdlog::level::debug);

  QApplication app(argc, argv);
  RenderWindow renderWindow;
  renderWindow.show();

  //QMainWindow* mainWin = new QMainWindow();
  //DebugWindow debugWindow;
  //debugWindow.setupUi(mainWin);
  //mainWin->show();

  DebugWindow debugWindow;
  debugWindow.show();

  return app.exec();
  
}
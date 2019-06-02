#include <QtWidgets/qapplication.h>
#include <QtWidgets/qpushbutton.h>

#include "RenderWindow.hpp"
#include "DebugWindow.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

int main(int argc, char** argv) {
  spdlog::init_thread_pool(8192, 1);
  spdlog::stdout_color_mt("console");
  spdlog::set_level(spdlog::level::debug);

  QApplication app(argc, argv);  

  DebugWindow debugWindow(&app);
  debugWindow.show();

  std::unique_ptr<CpuStateNotifierQt> state = std::make_unique<CpuStateNotifierQt>(&debugWindow);

  RenderWindow renderWindow(std::move(state), &debugWindow);
  renderWindow.show();

  //QMainWindow* mainWin = new QMainWindow();
  //DebugWindow debugWindow;
  //debugWindow.setupUi(mainWin);
  //mainWin->show();

  

  return app.exec();
  
}
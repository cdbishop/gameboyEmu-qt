#include <QtWidgets/qapplication.h>
#include <QtWidgets/qpushbutton.h>

#include <memory>

#include "RenderWindow.hpp"
#include "DebugWindow.hpp"
#include "CpuManager.hpp"
#include "tilesetViewerWindow.hpp"

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

  std::shared_ptr<CpuStateNotifierQt> state = std::make_shared<CpuStateNotifierQt>(&debugWindow);  

  std::shared_ptr<cpu::Manager> cpuManager = std::make_shared<cpu::Manager>(state);
  debugWindow.SetStateNotifier(state);

  RenderWindow renderWindow(cpuManager, &debugWindow);
  renderWindow.show();

  renderWindow.SetStateNotifier(state);

  TilesetViewerWindow tilesetWindow;
  tilesetWindow.show();
  tilesetWindow.SetStateNotifier(state);

  tilesetWindow.move(debugWindow.x() - tilesetWindow.width() - 5, debugWindow.y());
  //renderWindow.move(tilesetWindow.x(), tilesetWindow.y() + tilesetWindow.height() + 30);
  renderWindow.move(0, 0);

  return app.exec();
  
}
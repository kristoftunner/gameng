#pragma once
#include <memory>
#include "window/window.hpp"

namespace gameng {

class Application{
public:
  Application();
  ~Application();
  void Run();
private:
  std::unique_ptr<Window> m_window;
  bool m_running = true;
};

/**
 * @brief function defined by the client
 * 
 * @return Application* 
 */
Application* CreateApplication();
} // namespace gameng
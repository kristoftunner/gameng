#pragma once
#include <memory>
#include "window/window.hpp"
#include "application_event.hpp"

namespace gameng {

class Application{
public:
  Application();
  ~Application();
  void Run();
  void OnEvent(Event& e);
private:
  bool OnWindowClosed(WindowCloseEvent& e);
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
#pragma once
#include <memory>
#include "window.hpp"
#include "application_event.hpp"
#include "layer.hpp"
#include "layerstack.hpp"
namespace gameng {

class Application{
public:
  Application();
  ~Application();
  void Run();
  void OnEvent(Event& e);
  void PushLayer(Layer* layer);
  void PushOverlay(Layer* layer);
private:
  bool OnWindowClosed(WindowCloseEvent& e);
  std::unique_ptr<Window> m_window;
  bool m_running = true;
  LayerStack m_layerStack;
};

/**
 * @brief function defined by the client
 * 
 * @return Application* 
 */
Application* CreateApplication();
} // namespace gameng
#pragma once
#include <memory>
#include "gameng/window.hpp"
#include "gameng/application_event.hpp"
#include "gameng/layer.hpp"
#include "gameng/layerstack.hpp"
namespace gameng {


class Application{
public:
  Application();
  ~Application();
  void Run();
  void OnEvent(Event& e);
  void PushLayer(Layer* layer);
  void PushOverlay(Layer* layer);
  static inline Application& GetInstance() { return *s_instance; }
  inline Window& GetWindow(){ return *m_window; }
private:
  bool OnWindowClosed(WindowCloseEvent& e);
  std::unique_ptr<Window> m_window;
  bool m_running = true;
  LayerStack m_layerStack;
  static Application* s_instance;
};

/**
 * @brief function defined by the client
 * 
 * @return Application* 
 */
Application* CreateApplication();
} // namespace gameng

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "applicaiton.hpp"
#include "application_event.hpp"
#include "log.hpp"

namespace gameng
{

#define BIND_EVENT_FN(func) std::bind(&func, this, std::placeholders::_1)
Application::Application()
{
  m_window = std::unique_ptr<Window>(Window::Create());
  m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
}

Application::~Application()
{

}

void Application::PushLayer(Layer* layer)
{
  m_layerStack.PushLayer(layer);
}

void Application::PushOverlay(Layer* layer)
{
  m_layerStack.PushOverlay(layer);
}

void Application::OnEvent(Event& e)
{
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));

  for(auto it = m_layerStack.end(); it != m_layerStack.begin();)
  {
    (*--it)->OnEvent(e);
    if(e.Handled())
      break;
  }

  GAMENG_CORE_INFO("{0}",e);
}

bool Application::OnWindowClosed(WindowCloseEvent& e)
{
  m_running = false;
  return true;
}

void Application::Run()
{
  WindowResizeEvent e(1200,800);
  GAMENG_CORE_TRACE(e);
  
  while(m_running)
  {
    glClearColor(1,0,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    for(Layer* layer : m_layerStack)
    {
      layer->OnUpdate();
    }
    m_window->OnUpdate(); 
  }
}
} // namespace gameng

#include "applicaiton.hpp"
#include "application_event.hpp"
#include "log.hpp"
#include "GLFW/glfw3.h"
namespace gameng
{

Application::Application()
{
  m_window = std::unique_ptr<Window>(Window::Create());
}

Application::~Application()
{

}

void Application::Run()
{
  WindowResizeEvent e(1200,800);
  GAMENG_CORE_TRACE(e);
  
  while(m_running)
  {
    glClearColor(1,0,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    m_window->OnUpdate(); 
  }
}
} // namespace gameng

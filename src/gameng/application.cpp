#include "applicaiton.hpp"
#include "application_event.hpp"
#include "log.hpp"

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
    m_window->OnUpdate(); 
  }
}
} // namespace gameng

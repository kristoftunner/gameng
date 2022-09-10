#include "linux_window.hpp"
#include "../../log.hpp"

namespace gameng
{
  static bool s_GLFWInitialized = false;

  Window* Window::Create(const WindowProps& props)
  {
    return new LinuxWindow(props);
  }

  LinuxWindow::LinuxWindow(const WindowProps& props)
  {
    Init(props);
  }

  LinuxWindow::~LinuxWindow()
  {
    Shutdown();
  }

  void LinuxWindow::Init(const WindowProps& props)
  {
    m_data.title = props.title;
    m_data.width = props.width;
    m_data.heigth = props.heigth;
    GAMENG_CORE_INFO("Creating window {0} ({1} {2})", props.title, props.width, props.heigth);

    if(!s_GLFWInitialized)
    {
      int success = glfwInit();
      if(success != 0)
        GAMENG_CORE_ERR("Could not initialize GLFW");
      s_GLFWInitialized = true;
    }

    m_window = glfwCreateWindow((int)props.width, (int)props.heigth, m_data.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, &m_data);
    SetVSync(true);
  }

  void LinuxWindow::Shutdown()
  {
    glfwDestroyWindow(m_window);
  }

  void LinuxWindow::OnUpdate()
  {
    glfwPollEvents();
    glfwSwapBuffers(m_window);
  }

  void LinuxWindow::SetVSync(bool enabled)
  {
    if(enabled)
      glfwSwapInterval(1);
    else
      glfwSwapInterval(0);

    m_data.vsync = enabled;
  }

  bool LinuxWindow::IsVSync() const{
    return m_data.vsync;
  }
}//namespace gameng
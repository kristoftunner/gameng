#include "linux_window.hpp"
#include "../../mouse_event.hpp"
#include "../../application_event.hpp"
#include "../../key_event.hpp"
#include "../../log.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

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
  void GLFWErrorCallback(int error_code, const char* description)
  {
    GAMENG_CLIENT_ERR("GLFW error:({0}) description:{1}", error_code, description);
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
      if(success != 1)
        GAMENG_CORE_ERR("Could not initialize GLFW");
      glfwSetErrorCallback(GLFWErrorCallback);
      s_GLFWInitialized = true;
    }

    m_window = glfwCreateWindow((int)props.width, (int)props.heigth, m_data.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    //int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glfwSetWindowUserPointer(m_window, &m_data);
    SetVSync(true);

    // set glfw callbacks
    glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int heigth)
    {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      data.heigth = heigth;
      data.width = width;
      
      WindowResizeEvent event(width, heigth);
      data.eventCallback(event);
    });

    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
    {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      WindowCloseEvent event;
      data.eventCallback(event); 
    });

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

      switch(action)
      {
        case GLFW_PRESS:
        {
          KeyPressedEvent event(key, 0);
          data.eventCallback(event);
          break;
        }
        case GLFW_RELEASE:
        {
          KeyReleasedEvent event(key);
          data.eventCallback(event);
          break;
        }
        case GLFW_REPEAT:
        {
          KeyPressedEvent event(key, 1);
          data.eventCallback(event);
          break;
        }
      }
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
    {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      switch(action)
      {
        case GLFW_PRESS:
        {
          MouseButtonPressedEvent event(button);
          data.eventCallback(event);
          break;
        }
        case GLFW_RELEASE:
        {
          MouseButtonReleasedEvent event(button);
          data.eventCallback(event);
          break;
        }
      }
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
    {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      MouseScrolledEvent event((float)xOffset, (float)yOffset);
      data.eventCallback(event);
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
    {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      MouseMovedEvent event((float)xPos, (float)yPos);
      data.eventCallback(event);
    });
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
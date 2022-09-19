#include "gameng/platform/opengl/opengl_context.hpp"
#include "gameng/log.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace gameng
{
  OpenglContext::OpenglContext(GLFWwindow* windowHandle) : m_windowHandle(windowHandle)
  {
    if(!windowHandle)
      GAMENG_CORE_ERR("Window handle is null");
  }

  void OpenglContext::Init()
  {
    glfwMakeContextCurrent(m_windowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if(status == 0)
      GAMENG_CORE_ERR("Could not load GL with GLAD");

    GAMENG_CORE_INFO("OpenGL vendor: {0}",glGetString(GL_VENDOR));
    GAMENG_CORE_INFO("OpenGL renderer: {0}",glGetString(GL_RENDERER));
    GAMENG_CORE_INFO("OpenGL version: {0}",glGetString(GL_VERSION));
  } 

  void OpenglContext::SwapBuffers()
  {
    glfwSwapBuffers(m_windowHandle);
  }
} // namespace gameng

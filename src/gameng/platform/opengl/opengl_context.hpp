#pragma once

#include "gameng/renderer/graphic_context.hpp"

struct GLFWwindow;

namespace gameng
{
class OpenglContext : public GraphicsContext
{
public:
  OpenglContext(GLFWwindow* windowHandle);
  virtual void Init() override;
  virtual void SwapBuffers() override;
private:
  GLFWwindow* m_windowHandle;
}; 
} // namespace gameng

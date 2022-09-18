#include "gameng/platform/linux/linux_input.hpp"
#include "gameng/applicaiton.hpp"

#include "GLFW/glfw3.h"

namespace gameng
{

Input* Input::s_instance = new LinuxInput();

bool LinuxInput::IsKeyPressedImpl(int keycode)
{
  auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
  auto status = glfwGetKey(window, keycode); 
  return status == GLFW_PRESS || status == GLFW_REPEAT;
}

bool LinuxInput::IsMouseButtonPressedImpl(int button) 
{
  auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
  auto status = glfwGetMouseButton(window, button); 
  return status == GLFW_PRESS;
}

std::pair<float, float> LinuxInput::GetMousePositionImpl()
{
  auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
  double x,y;
  glfwGetCursorPos(window, &x, &y);
  return {(float)x, (float)y};
}

float LinuxInput::GetMouseXImpl()
{
  auto[x,y] = GetMousePositionImpl();
  return x;
} 

float LinuxInput::GetMouseYImpl()
{
  auto[x,y] = GetMousePositionImpl();
  return y;
}
} // namespace gameng

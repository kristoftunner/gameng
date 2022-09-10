#pragma once
#include "../window.hpp"
#include "GLFW/glfw3.h"
namespace gameng
{

class LinuxWindow : public Window
{
public:
  LinuxWindow(const WindowProps& props);
  ~LinuxWindow();
  inline unsigned int GetWindowWidth() const override { return m_width;}
  inline unsigned int GetWindowHeigth() const override { return m_heigth;}
  void OnUpdate() override;
  inline void SetEventCallback(const EventCallbackFn& callback) override {m_data.eventCallback = callback; }
  void SetVSync(bool enabled) override;
  bool IsVSync() const override;

private:
  virtual void Init(const WindowProps& props);
  virtual void Shutdown();
private:
  GLFWwindow* m_window;

  struct WindowData
  {
    std::string title;
    unsigned int width, heigth;
    bool vsync;
    EventCallbackFn eventCallback;
  };

  WindowData m_data;
};

}//namespace gameng
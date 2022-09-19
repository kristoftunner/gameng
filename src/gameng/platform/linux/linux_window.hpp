#pragma once

#include "gameng/window.hpp"
#include "gameng/renderer/graphic_context.hpp"

struct GLFWwindow;

namespace gameng
{

class LinuxWindow : public Window
{
public:
  LinuxWindow(const WindowProps& props);
  ~LinuxWindow();
  inline unsigned int GetWindowWidth() const override { return m_data.width;}
  inline unsigned int GetWindowHeigth() const override { return m_data.heigth;}
  void OnUpdate() override;
  inline void SetEventCallback(const EventCallbackFn& callback) override {m_data.eventCallback = callback; }
  void SetVSync(bool enabled) override;
  bool IsVSync() const override;
  void* GetNativeWindow() const override {return m_window;}

private:
  virtual void Init(const WindowProps& props);
  virtual void Shutdown();
private:
  GLFWwindow* m_window;
  GraphicsContext* m_context;

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
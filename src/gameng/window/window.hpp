#pragma once
#include <functional>
#include "../event.hpp"
namespace gameng{

struct WindowProps{
  std::string title;
  unsigned int width;
  unsigned int heigth;

  WindowProps(const std::string& title = "Gameng engine",
              unsigned int width = 1280, unsigned int heigth = 720)
            : title(title), width(width), heigth(heigth){}
};

class Window{
public:
  Window() = default;
  virtual ~Window(){};
  using EventCallbackFn = std::function<void(Event&)>;
  virtual unsigned int GetWindowWidth() const = 0;
  virtual unsigned int GetWindowHeigth() const = 0;
  virtual void OnUpdate() = 0;
  virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
  virtual void SetVSync(bool enabled) = 0;
  virtual bool IsVSync() const = 0;
  static Window* Create(const WindowProps& props = WindowProps());
protected:
  int m_width, m_heigth;
};
}//namespace gameng
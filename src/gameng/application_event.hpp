#pragma once

#include "gameng/event.hpp"
#include <sstream>

namespace gameng
{

class WindowResizeEvent : public Event
{
public:
  WindowResizeEvent(int width, int heigth) : m_width(width), m_heigth(heigth) {}
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
  EVENT_CLASS_TYPE(WindowResize)
  inline unsigned int GetWidth(){ return m_width; }
  inline unsigned int GetHeigth() { return m_heigth; }

  std::string ToString() const override 
  {
    std::stringstream ss;
    ss << "WindowResizeEvent: width:" << m_width << " heigth:" << m_heigth;
    return ss.str(); 
  }
private:
  int m_width, m_heigth;
};

class WindowCloseEvent : public Event
{
public:
  WindowCloseEvent(){}

  EVENT_CLASS_CATEGORY(EventCategoryApplication)
  EVENT_CLASS_TYPE(WindowClose)
};

class AppTickEvent : public Event{
public:
  AppTickEvent() {}
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
  EVENT_CLASS_TYPE(AppTick)
};

class AppUpdateEvent : public Event
{
public:
  AppUpdateEvent() {}
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
  EVENT_CLASS_TYPE(AppUpdate)
};

class AppRenderEvent : public Event
{
public:
  AppRenderEvent() {}
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
  EVENT_CLASS_TYPE(AppRender)
};

} // namespace gameng

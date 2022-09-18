#pragma once
#include <sstream>
#include "gameng/event.hpp"

namespace gameng
{
class MouseMovedEvent : public Event
{
public:  
  MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {}
  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
  EVENT_CLASS_TYPE(MouseMoved)

  std::string ToString() const override
  {
    std::stringstream ss;
    ss << "MouseMovedEvent: x:" << m_mouseX << " y:" << m_mouseY;
    return ss.str();
  }

  inline float GetX(){ return m_mouseX; }
  inline float GetY(){ return m_mouseY; }

private:
  float m_mouseX, m_mouseY;
};

class MouseScrolledEvent : public Event
{
public:  
  MouseScrolledEvent(float xOffset, float yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {}
  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
  EVENT_CLASS_TYPE(MouseMoved)

  std::string ToString() const override
  {
    std::stringstream ss;
    ss << "MouseScrolledEvent: x:" << m_xOffset << " y:" << m_yOffset;
    return ss.str();
  }

  inline float GetXOffset(){ return m_xOffset; }
  inline float GetYOffset(){ return m_yOffset; }

private:
  float m_xOffset, m_yOffset;
};


class MouseButtonEvent : public Event
{
public:
  MouseButtonEvent(int buttonCode) : m_buttonCode(buttonCode) {}
  ~MouseButtonEvent(){}
  EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
  inline int GetButtonCode() { return m_buttonCode; }
protected:
  int m_buttonCode;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
  MouseButtonPressedEvent(int buttonCode) : MouseButtonEvent(buttonCode) {}
  EVENT_CLASS_TYPE(MouseButtonPressed)
  std::string ToString() const override
  {
    std::stringstream ss;
    ss << "MouseButtonPressedEvent: buttonCode:" << m_buttonCode;
    return ss.str();
  }
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
  MouseButtonReleasedEvent(int buttonCode) : MouseButtonEvent(buttonCode) {}
  EVENT_CLASS_TYPE(MouseButtonPressed)
  std::string ToString() const override
  {
    std::stringstream ss;
    ss << "MouseButtonPressedEvent: buttonCode:" << m_buttonCode;
    return ss.str();
  }
};
} // namespace gameng
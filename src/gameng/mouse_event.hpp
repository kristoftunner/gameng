#pragma once

#include "event.hpp"

namespace gameng
{
class MouseMovedEvent : public Event
{
public:  
  MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {}
  EVENT_CLASS_CATEGORY(EventCategoryMouse || EventCategoryInput);
  EVENT_CLASS_TYPE(EventType::MouseMoved)

  inline float GetX(){ return m_mouseX; }
  inline float GetY(){ return m_mouseY; }

private:
  float m_mouseX, m_mouseY;
}
} // namespace gameng
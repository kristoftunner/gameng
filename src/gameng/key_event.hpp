#pragma once

#include "event.hpp"

namespace gameng
{

class KeyEvent : public Event
{
public:
  KeyEvent(int keycode) : m_keycode(keycode) {}
  EVENT_CLASS_CATEGORY(EventCategoryInput || EventCategoryKeyboard)
  int GetKeycode(){return m_keycode}

protected:
  int m_keycode;
}

class KeyPressedEvent : public KeyEvent
{
public:
  KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode) ,m_repeateCount(repeatCount) {}
  EVENT_CLASS_TYPE(EventType::KeyPressed)
  inline int GetRepeatCount() { return m_repeateCount; }
  std::string ToString() const override
  {
    std::stringstream ss;
    ss << "KeyPressedEvent: keycode:" << m_keycode << " repeatcount:" << m_repeateCount;
    return ss.string();
  }
private:
  int m_repeateCount;
}

class KeyReleasedEvent : KeyEvent
{
  KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}
  EVENT_CLASS_TYPE(EventType::KeyReleased)
  std::string ToString() const override
  {
    std::stringstream ss;
    ss << "KeyReleased: keycode:" << m_keycode;
    return ss.string();
  }
}
} // namespace gameng

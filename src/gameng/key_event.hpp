#pragma once

#include "gameng/event.hpp"
#include <sstream>
namespace gameng
{

class KeyEvent : public Event
{
public:
  KeyEvent(int keycode) : m_keycode(keycode) {}
  EVENT_CLASS_CATEGORY(EventCategoryInput || EventCategoryKeyboard)
  int GetKeycode(){return m_keycode;}

protected:
  int m_keycode;
};

class KeyPressedEvent : public KeyEvent
{
public:
  KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode) ,m_repeateCount(repeatCount) {}
  EVENT_CLASS_TYPE(KeyPressed)
  inline int GetRepeatCount() { return m_repeateCount; }
  std::string ToString() const override
  {
    std::stringstream ss;
    ss << "KeyPressedEvent: keycode:" << m_keycode << " repeatcount:" << m_repeateCount;
    return ss.str();
  }
private:
  int m_repeateCount;
};

class KeyReleasedEvent : public KeyEvent
{
public:
  KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}
  EVENT_CLASS_TYPE(KeyReleased)
  std::string ToString() const override
  {
    std::stringstream ss;
    ss << "KeyReleased: keycode:" << m_keycode;
    return ss.str();
  }
};

class KeyTypedEvent : public KeyEvent
{
public:
  KeyTypedEvent(int keycode) : KeyEvent(keycode)  {}
  EVENT_CLASS_TYPE(KeyTyped)
  std::string ToString() const override
  {
    std::stringstream ss;
    ss << "KeyTypedEvent: keycode:" << m_keycode;
    return ss.str();
  }
private:
  int m_repeateCount;
};
} // namespace gameng

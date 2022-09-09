#pragma once

#include <functional>

#define BIT(x) (1<<x)
namespace gameng
{

enum class EventType
{
  None = 0,
  WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
  AppTick, AppUpdate, AppRender,
  KeyPressed, KeyReleased, 
  MousePressed, MouseReleased,
  MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EventCategory
{
  None = 0,
  EventCategoryApplication = BIT(0),
  EventCategoryInput = BIT(1),
  EventCategoryKeyboard = BIT(2),
  EventCategoryMouse = BIT(3),
  EventCategoryMouseButton = BIT(4)
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){return EventType::##type;} \
                              virtual EventType GetType() const override {return GetStaticType();} \
                              virtual const char* GetName(){ return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

class Event {
  friend class EventDispatcher;
public:
  Event() = default;
  ~Event(){}
  virtual EventType GetEventType() = 0;
  virtual EventCategory GetCategoryFlags() = 0;
  inline bool IsInCategory(EventCategory category)
  {
    return GetCategoryFlags() & category;
  }
protected:
  bool m_handled = false;
};

class EventDispatcher
{

template<class T>
using EventFn = std::functional<T>;
public:
  EventDispatcher(Event& event) : m_event(event){}
  template<T>
  bool Dispatch(EventFn<T> func)
  {
    if(m_event.GetEventType() == T::GetStaticType())
    {
      m_event.m_handled = func(*(T*)&m_event);
      return true;
    }
    else 
      return false;
  }
private:
  Event m_event;
};
}// namespace gameng
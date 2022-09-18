#pragma once

#include "layer.hpp"
#include "application_event.hpp"
#include "mouse_event.hpp"
#include "key_event.hpp"

namespace gameng
{

class ImguiLayer : public Layer
{
public:
  ImguiLayer();
  ~ImguiLayer();
  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate() override;
  void OnEvent(Event& event) override;
  bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
  bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
  bool OnMouseMovedEvent(MouseMovedEvent& evet);
  bool OnMouseScrolledEvent(MouseScrolledEvent& event);
  bool OnKeyPressedEvent(KeyPressedEvent& event);
  bool OnKeyReleasedEvent(KeyReleasedEvent& event);
  bool OnKeyTypedEvent(KeyTypedEvent& event);
  bool OnWindowResizedEvent(WindowResizeEvent& event);
private:
  float m_time = 0.0f;
};

} // namespace gameng

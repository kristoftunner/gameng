#pragma once

#include "layer.hpp"

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

private:
  bool OnKeyPressed();
  bool OnKeyReleased();
  bool OnMouseButtonPressed();
  bool OnMouseButtonReleased();
  bool OnMouseScrollEvent();
  bool OnMouseMovedEvent(MouseMovedEvent& event);

private:
  float m_time = 0.0f;
};

} // namespace gameng

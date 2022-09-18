#pragma once

#include "gameng/layer.hpp"
#include "gameng/application_event.hpp"
#include "gameng/mouse_event.hpp"
#include "gameng/key_event.hpp"

namespace gameng
{

class ImguiLayer : public Layer
{
public:
  ImguiLayer();
  ~ImguiLayer();
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate() override;
private:
  float m_time = 0.0f;
};

} // namespace gameng

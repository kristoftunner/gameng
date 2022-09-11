#pragma once

#include "layer.hpp"

namespace gameng
{

class ImguiLayer : public Layer
{
  ImguiLayer();
  ~ImguiLayer();
  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate() override;
  void OnEvent(Event& event) override;
};

} // namespace gameng

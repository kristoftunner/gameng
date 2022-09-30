#pragma once
#include <string>
#include "gameng/event.hpp"
#include "gameng/core/timestep.hpp"

namespace gameng
{

class Layer {
public:
  Layer(const std::string& name = "Layer");
  virtual ~Layer();

  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnUpdate(Timestep ts) {}
  virtual void OnEvent(Event& event) {}
  virtual void OnImguiRender(){}

  inline const std::string& GetName() {return m_debugName; }
protected:
  std::string m_debugName;
};
}// namespace gameng
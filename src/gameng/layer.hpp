#pragma once
#include <string>
#include "gameng/event.hpp"

namespace gameng
{

class Layer {
public:
  Layer(const std::string& name = "Layer");
  virtual ~Layer();

  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnUpdate() {}
  virtual void OnEvent(Event& event) {}

  inline const std::string& GetName() {return m_debugName; }
protected:
  std::string m_debugName;
};
}// namespace gameng
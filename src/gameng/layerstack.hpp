#pragma once
#include <vector>

#include "layer.hpp"

namespace gameng
{

class LayerStack
{
public:
  LayerStack();
  ~LayerStack();

  void PushLayer(Layer* layer);
  void PopLayer(Layer* layer);
  void PushOverlay(Layer* layer);
  void PopOverlay(Layer* layer);

  std::vector<Layer*>::iterator begin() {return m_layers.begin();}
  std::vector<Layer*>::iterator end() {return m_layers.end();}
private:
  std::vector<Layer*> m_layers;
  std::vector<Layer*>::iterator m_layerInsert;
};

}//namespace gameng
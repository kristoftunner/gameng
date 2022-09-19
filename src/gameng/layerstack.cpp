#include <algorithm>

#include "gameng/layerstack.hpp"

namespace gameng
{
  LayerStack::LayerStack(){
  } 

  LayerStack::~LayerStack()
  {
    for(Layer* layer : m_layers)
    {
      delete layer;
    }
  }

  void LayerStack::PushLayer(Layer* layer)
  {
    m_layers.emplace(m_layers.begin() + m_layerInsert, layer);
    m_layerInsert++; 
  }

  void LayerStack::PushOverlay(Layer* layer)
  {
    m_layers.emplace_back(layer);
  }

  void LayerStack::PopLayer(Layer* layer)
  {
    auto it = std::find(m_layers.begin(), m_layers.end(), layer);
    if(it != m_layers.end())
    {
      m_layers.erase(it);
      m_layerInsert--;
    }
  }

  void LayerStack::PopOverlay(Layer* layer)
  {
    auto it = std::find(m_layers.begin(), m_layers.end(), layer);
    if(it != m_layers.end())
    {
      m_layers.erase(it);
    }

  }
} // namespace gameng

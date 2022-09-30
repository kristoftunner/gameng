#pragma once

#include <memory>

#include "gameng/renderer/buffer.hpp"

namespace gameng
{

class VertexArray
{
public:
  virtual ~VertexArray(){}

  virtual void Bind() const  = 0;
  virtual void UnBind() const = 0;
  virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer) = 0; 
  virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> vertexBuffer) = 0; 
  static VertexArray* Create();
};

} // namespace gameng

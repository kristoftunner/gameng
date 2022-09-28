#pragma once

#include <stdint.h>

namespace gameng
{

class VertexBuffer
{
public:
  ~VertexBuffer(){}
  
  virtual void Bind() const {}
  virtual void UnBind() const {};

  static VertexBuffer* Create(float* vertices, uint32_t size);
};

class IndexBuffer
{
public:
  ~IndexBuffer(){}
  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;

  virtual uint32_t GetCount() const  = 0;

  static IndexBuffer* Create(uint32_t* indices, uint32_t size);
};

} // namespace gameng

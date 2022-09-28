#pragma once

#include "gameng/renderer/buffer.hpp"

namespace gameng
{

class OpenGLVertexBuffer : public VertexBuffer
{
public:
  OpenGLVertexBuffer(float* vertices, uint32_t size);
  virtual ~OpenGLVertexBuffer();

  virtual void Bind() const override;
  virtual void UnBind() const override;
private:
  uint32_t m_rendererId;
};

class OpenGLIndexBuffer : public IndexBuffer
{
public:
  OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
  virtual ~OpenGLIndexBuffer();

  virtual void Bind() const override;
  virtual void UnBind() const override;
  virtual uint32_t GetCount() const override {return m_count;};
private:
  uint32_t m_rendererId, m_count;
};

} // namespace gameng

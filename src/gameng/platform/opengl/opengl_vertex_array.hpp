#include "gameng/renderer/vertex_array.hpp"
#include "gameng/core.hpp"

namespace gameng
{

class OpenGLVertexArray : public VertexArray
{
public:
  virtual ~OpenGLVertexArray();
  OpenGLVertexArray();
  virtual void Bind() const  override;
  virtual void UnBind() const override;
  virtual void AddVertexBuffer(const Ref<VertexBuffer> vertexBuffer) override; 
  virtual void SetIndexBuffer(const Ref<IndexBuffer> vertexBuffer) override; 
  virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_vertexBuffers; }
  virtual const Ref<IndexBuffer>& GetIndexBuffer() const override {return m_indexBuffer; }
private:
  uint32_t m_rendererId;
  std::vector<Ref<VertexBuffer>> m_vertexBuffers;
  Ref<IndexBuffer> m_indexBuffer;
};

} // namespace gameng

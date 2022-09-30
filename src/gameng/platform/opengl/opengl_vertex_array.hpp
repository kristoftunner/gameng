#include "gameng/renderer/vertex_array.hpp"


namespace gameng
{

class OpenGLVertexArray : public VertexArray
{
public:
  virtual ~OpenGLVertexArray();
  OpenGLVertexArray();
  virtual void Bind() const  override;
  virtual void UnBind() const override;
  virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer) override; 
  virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> vertexBuffer) override; 
  virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return m_vertexBuffers; }
  virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override {return m_indexBuffer; }
private:
  uint32_t m_rendererId;
  std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
  std::shared_ptr<IndexBuffer> m_indexBuffer;
};

} // namespace gameng
#include "gameng/renderer/renderer.hpp"
#include "gameng/renderer/buffer.hpp"
#include "gameng/log.hpp"
#include "gameng/platform/opengl/opengl_buffer.hpp"

namespace gameng
{
  VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
  {
    switch(Renderer::GetAPI())
    {
      case RendererAPI::API::None: GAMENG_CORE_ERR("Renderer API is not supported"); return nullptr;
      case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
      default: GAMENG_CORE_ERR("Unknown renderer API"); return nullptr;
    }
    return nullptr;
  }
  
  IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
  {
    switch(Renderer::GetAPI())
    {
      case RendererAPI::API::None: GAMENG_CORE_ERR("Renderer API is not supported"); return nullptr;
      case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
      default: GAMENG_CORE_ERR("Unknown renderer API"); return nullptr;
    }
    return nullptr;

  }
   
} // namespace gameng

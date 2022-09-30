#include "gameng/renderer/vertex_array.hpp"
#include "gameng/renderer/renderer.hpp"
#include "gameng/platform/opengl/opengl_vertex_array.hpp"

namespace gameng
{
  VertexArray* VertexArray::Create()
  {
    switch(Renderer::GetAPI())
    {
      case RendererAPI::API::None: GAMENG_CORE_ERR("Renderer API is not supported"); return nullptr;
      case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
      default: GAMENG_CORE_ERR("Unknown renderer API"); return nullptr;
    }
    return nullptr;
  }

} // namespace gameng

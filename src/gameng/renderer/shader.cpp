
#include "gameng/renderer/renderer.hpp"
#include "gameng/renderer/shader.hpp"
#include "gameng/platform/opengl/opengl_shader.hpp"
namespace gameng
{
  Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
  {
    switch(Renderer::GetAPI())
    {
      case RendererAPI::API::None: GAMENG_CORE_ERR("Renderer API is not supported"); return nullptr;
      case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSource, fragmentSource);
      default: GAMENG_CORE_ERR("Unknown renderer API"); return nullptr;
    }
    return nullptr;
  }

} // namespace gameng

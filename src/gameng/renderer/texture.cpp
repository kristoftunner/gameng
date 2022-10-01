#include "renderer.hpp"
#include "texture.hpp"
#include "gameng/platform/opengl/opengl_texture.hpp"
namespace gameng
{

Ref<Texture2D> Texture2D::Create(const std::string& path)
{
  switch(Renderer::GetAPI())
  {
    case RendererAPI::API::None: GAMENG_CORE_ERR("Renderer API is not supported"); return nullptr;
    case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
    default: GAMENG_CORE_ERR("Unknown renderer API"); return nullptr;
  }
  return nullptr;

}

} // namespace gameng

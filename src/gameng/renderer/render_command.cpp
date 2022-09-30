#include "gameng/renderer/render_command.hpp"
#include "gameng/platform/opengl/opengl_renderer_api.hpp"


namespace gameng
{
  RendererAPI* RenderCommand::s_rendererAPI = new OpenGLRendererAPI; 
} // namespace gameng

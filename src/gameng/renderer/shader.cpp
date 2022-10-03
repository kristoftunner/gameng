
#include "gameng/renderer/renderer.hpp"
#include "gameng/renderer/shader.hpp"
#include "gameng/platform/opengl/opengl_shader.hpp"
namespace gameng
{
Ref<Shader> Shader::Create(const std::string& filepath)
{
  switch(Renderer::GetAPI())
  {
    case RendererAPI::API::None: GAMENG_CORE_ERR("Renderer API is not supported"); return nullptr;
    case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath);
    default: GAMENG_CORE_ERR("Unknown renderer API"); return nullptr;
  }
  return nullptr;
}
  
Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
{
  switch(Renderer::GetAPI())
  {
    case RendererAPI::API::None: GAMENG_CORE_ERR("Renderer API is not supported"); return nullptr;
    case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSource, fragmentSource);
    default: GAMENG_CORE_ERR("Unknown renderer API"); return nullptr;
  }
  return nullptr;
}

void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
{
  if(!Exists(name))
  {
    m_shaders[name] = shader;
  }
  else
    GAMENG_CORE_ERR("Shader with name:{0} added twice into the shader lib", name);
}

void ShaderLibrary::Add(const Ref<Shader>& shader)
{
  auto& name = shader->GetName();
  Add(name, shader);
}

Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
{
  auto shader = Shader::Create(filepath);
  Add(shader);
  return shader;
}

Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
{
  auto shader = Shader::Create(filepath);
  Add(name, shader);
  return shader;
}

Ref<Shader> ShaderLibrary::Get(const std::string& name)
{
  if(!Exists(name))
  {
    GAMENG_CORE_ERR("Did not found shader with name:{0}", name);
  }
  else
    return m_shaders[name];
}

bool ShaderLibrary::Exists(const std::string& name)
{
  return m_shaders.find(name) != m_shaders.end();
}

} // namespace gameng

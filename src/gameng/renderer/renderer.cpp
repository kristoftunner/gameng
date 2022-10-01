#include "gameng/renderer/renderer.hpp"
#include "gameng/platform/opengl/opengl_shader.hpp"

#include <memory>

namespace gameng
{
  Renderer::SceneData* Renderer::s_sceneData = new Renderer::SceneData;

  void Renderer::BeginScene(OrtographicCamera& camera)
  {
    s_sceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
  }

  void Renderer::EndScene()
  {
  }

  void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
  {
    std::dynamic_pointer_cast<OpenGLShader>(shader)->Bind();
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_viewProjection", s_sceneData->viewProjectionMatrix);
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_transform", transform); // model matrix of the object/s that are rendered
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
  }

} // namespace gameng

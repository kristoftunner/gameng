#include "renderer.hpp"

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

  void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
  {
    shader->Bind();
    shader->UploadUniformMat4("u_viewProjection", s_sceneData->viewProjectionMatrix);

    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
  }

} // namespace gameng

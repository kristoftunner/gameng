#pragma once

#include <memory>

#include "gameng/renderer/render_command.hpp"
#include "gameng/renderer/ortographic_camera.hpp"
#include "gameng/renderer/shader.hpp"

namespace gameng
{

class Renderer
{
public:
  static void BeginScene(OrtographicCamera& camera);
  static void EndScene();
  static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
  inline static RendererAPI::API GetAPI(){return RendererAPI::GetAPI();}
private:
  struct SceneData
  {
    glm::mat4 viewProjectionMatrix;
  };

  static SceneData* s_sceneData;
};

} // namespace gameng

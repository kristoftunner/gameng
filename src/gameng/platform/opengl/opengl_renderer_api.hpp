#pragma once

#include "gameng/renderer/renderer_api.hpp"

namespace gameng
{

class OpenGLRendererAPI : public RendererAPI
{
public:
  virtual void SetClearColor(const glm::vec4& color) override;
  virtual void Clear() override;
  virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

};

} // namespace gameng

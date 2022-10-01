#pragma once

#include <string>
#include "glm/glm.hpp"

namespace gameng
{

class Shader
{
public:
  virtual ~Shader() = default;

  void Bind() const;
  void UnBind() const;

  static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
private:
  uint32_t m_rendererId;
};
}// namespace gameng
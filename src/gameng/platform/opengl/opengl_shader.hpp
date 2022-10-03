#pragma once

#include "gameng/renderer/shader.hpp"

#include <unordered_map>
#include "glad/glad.h"

namespace gameng
{
class OpenGLShader : public Shader
{
public:
  OpenGLShader(const std::string& filepath);
  OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
  virtual ~OpenGLShader();

  void Bind() const;
  void UnBind() const;

  void UploadUniformFloat(const std::string& name, float value);
  void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
  void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
  void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
  
  void UploadUniformInt(const std::string& name, int value);
  
  void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
  void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
private:
  std::string ReadFile(const std::string& filepath);
  std::unordered_map<GLenum, std::string> PreProcess(const std::string& stringSource);
  void Compile(const std::unordered_map<GLenum, std::string>& shaderSource);
private:
  uint32_t m_rendererId;
};
  
} // namespace gameng

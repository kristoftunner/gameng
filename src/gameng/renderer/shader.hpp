#pragma once

#include "gameng/core.hpp"

#include <string>
#include "glm/glm.hpp"
#include <unordered_map>

namespace gameng
{

class Shader
{
public:
  virtual ~Shader() = default;

  void Bind() const;
  void UnBind() const;

  virtual const std::string& GetName() const = 0;

  static Ref<Shader> Create(const std::string& filepath);
  static Ref<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
private:
  uint32_t m_rendererId;
};

class ShaderLibrary
{
public:
  void Add(const Ref<Shader>& shader);
  void Add(const std::string& name, const Ref<Shader>& shader);
  Ref<Shader> Load(const std::string& filepath);
  Ref<Shader> Load(const std::string& name, const std::string& filepath);

  Ref<Shader> Get(const std::string& name);
  bool Exists(const std::string& name);
private:
  std::unordered_map<std::string, Ref<Shader>> m_shaders;
};

}// namespace gameng
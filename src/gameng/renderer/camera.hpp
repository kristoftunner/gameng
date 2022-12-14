#pragma once

#include "glm/glm.hpp"

namespace gameng
{

class Camera
{
public:
  Camera() = default; 

  const glm::vec3& GetPosition(){return m_position;}
  void SetPosition(const glm::vec3& position) { m_position = position; UpdateView();}

  const glm::mat4& GetProjectionMatrix(){return m_projectionMatrix;}
  const glm::mat4& GetViewMatrix(){return m_viewMatrix;}
  const glm::mat4& GetViewProjectionMatrix(){return m_viewProjMatrix;}
protected:
  virtual void UpdateView() = 0;
protected:
  glm::mat4 m_projectionMatrix;
  glm::mat4 m_viewMatrix;
  glm::mat4 m_viewProjMatrix; 
  glm::vec3 m_position = {0.0f,0.0f,0.0f};
};
} // namespace gameng

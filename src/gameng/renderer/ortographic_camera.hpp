#pragma once

#include "glm/glm.hpp"

namespace gameng
{

class OrtographicCamera
{
public:
  OrtographicCamera(float left, float right, float bottom, float top);

  const glm::vec3& GetPosition(){return m_position;}
  void SetPosition(const glm::vec3& position) { m_position = position; RecalculateViewMatrix();}
  void SetRotation(const float& rotation) { m_rotation = rotation; RecalculateViewMatrix();}
  const float& GetRotation(){return m_rotation;}

  const glm::mat4& GetProjectionMatrix(){return m_projectionMatrix;}
  const glm::mat4& GetViewMatrix(){return m_viewMatrix;}
  const glm::mat4& GetViewProjectionMatrix(){return m_viewProjMatrix;}
private:
  void RecalculateViewMatrix();
private:
  glm::mat4 m_projectionMatrix;
  glm::mat4 m_viewMatrix;
  glm::mat4 m_viewProjMatrix; 
  glm::vec3 m_position = {0.0f,0.0f,0.0f};
  float m_rotation = 0.0f;
};

} // namespace gameng

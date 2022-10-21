#include "perspective_camera.hpp"
#include "glm/ext.hpp"

namespace gameng
{

PerspectiveCamera::PerspectiveCamera(const float aspectRatio, const float fov, const float nearClip, const float farClip)
  : m_projectionMatrix(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip)), m_viewMatrix(1.0f)
{
  m_viewProjMatrix = m_projectionMatrix * m_viewMatrix;
}

void PerspectiveCamera::RecalculateViewMatrix()
{
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0,0,1));
  m_viewMatrix = glm::inverse(transform);
  m_viewProjMatrix = m_projectionMatrix * m_viewMatrix;
}
  
} // namespace gameng

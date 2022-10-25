#include "perspective_camera.hpp"
#include "gameng/log.hpp"
#include "gameng/input.hpp"
#include "gameng/keycodes.hpp"
#include "gameng/mousebutton_codes.hpp"

#include "glm/ext.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

namespace gameng
{

PerspectiveCamera::PerspectiveCamera(const float aspectRatio, const float fov, const float nearClip, const float farClip)
  : m_aspectRatio(aspectRatio), m_fov(fov), m_nearClip(nearClip), m_farClip(farClip)
{
  m_projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);  
  m_viewMatrix = glm::mat4(1.0f);
  m_viewProjMatrix = m_projectionMatrix * m_viewMatrix;
}

void PerspectiveCamera::OnUpdate(Timestep ts)
{
  if(Input::IsKeyPressed(GAMENG_KEY_LEFT_ALT))
  {
    const glm::vec2& mouse{Input::GetMouseX(), Input::GetMouseY()};
    glm::vec2 delta = (mouse - m_initialMousePosition) * 0.003f;
    m_initialMousePosition = mouse;

    if(Input::IsMouseButtonPressed(GAMENG_MOUSE_BUTTON_MIDDLE))
      MousePan(delta);
    else if(Input::IsMouseButtonPressed(GAMENG_MOUSE_BUTTON_LEFT))
      MouseRotate(delta);
    else if(Input::IsMouseButtonPressed(GAMENG_MOUSE_BUTTON_RIGHT))
      MouseZoom(delta.y);
  }

  UpdateView();
}

glm::vec3 PerspectiveCamera::GetFrontVector() const
{
  return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
} 

glm::vec3 PerspectiveCamera::GetRightVector() const
{
  return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::vec3 PerspectiveCamera::GetUpVector() const
{
  return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::quat PerspectiveCamera::GetOrientation() const
{
  return glm::quat(glm::vec3(-m_pitch, -m_yaw, 0.0f));
}

void PerspectiveCamera::UpdateProjection()
{
  m_aspectRatio = m_viewPortWidth / m_viewPortHeight;
  m_projectionMatrix = glm::perspective(m_fov, m_aspectRatio, m_nearClip, m_farClip);
}

void PerspectiveCamera::UpdateView()
{
  m_position = CalculatePosition();
  glm::quat orientation = GetOrientation();
  m_viewMatrix = glm::translate(glm::mat4(1.0f), m_position) * glm::toMat4(orientation);
  m_viewMatrix = glm::inverse(m_viewMatrix);
  m_viewProjMatrix = m_projectionMatrix * m_viewMatrix;
}

void PerspectiveCamera::MousePan(const glm::vec2 delta)
{

}

void PerspectiveCamera::MouseRotate(const glm::vec2& delta)
{
  m_pitch += delta.y * m_rotationSpeed;
  m_yaw += delta.x * m_rotationSpeed;
}

void PerspectiveCamera::MouseZoom(float delta)
{
  
  m_distance -= delta * ZoomSpeed();
  // in case we zoomed in too much->fall back to starting position
  if(m_distance < 1.0f)
  {
    m_focalPoint += GetFrontVector();
    m_distance = 1.0f;
  }
}

float PerspectiveCamera::ZoomSpeed() const
{
	float distance = m_distance * 0.2f;
	distance = std::max(distance, 0.0f);
	float speed = distance * distance;
	speed = std::min(speed, 100.0f); // max speed = 100
	return speed;
}

glm::vec3 PerspectiveCamera::CalculatePosition() const
{
  return m_focalPoint - GetFrontVector() * m_distance;
}
  
} // namespace gameng

#pragma once

#include "camera.hpp"
#include "gameng/core/timestep.hpp"
namespace gameng
{

class PerspectiveCamera : public Camera
{
public:
  PerspectiveCamera(const float aspectRatio, const float fov, const float nearClip, const float farClip);
  
  void OnUpdate(Timestep ts);

  glm::vec3 GetFrontVector() const; 
  glm::vec3 GetRightVector() const; 
  glm::vec3 GetUpVector() const; 
  glm::quat GetOrientation() const;


private:
  void UpdateProjection();
  void UpdateView() override;

  void MousePan(const glm::vec2 delta);
  void MouseRotate(const glm::vec2& delta);
  void MouseZoom(float delta);

  glm::vec3 CalculatePosition() const;
private:
  // perspective projection related members
  float m_fov = 45.0f, m_aspectRatio = 1, m_nearClip = 0.1f, m_farClip = 100.0f;
  
  float m_pitch = 0.0f, m_yaw = 0.0f;
  float m_viewPortWidth = 800, m_viewPortHeight = 800;
  float m_distance = 10.0f;
  glm::vec3 m_focalPoint = {0.0f, 0.0f, 0.0f};

  float m_rotationSpeed = 0.8f;

  glm::vec2 m_initialMousePosition = {0.0f, 0.0f};
};

} // namespace gameng

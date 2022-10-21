#pragma once

#include "camera.hpp"

namespace gameng
{

class PerspectiveCamera : public Camera
{
public:
  PerspectiveCamera(const float aspectRatio, const float fov, const float nearClip, const float farClip);
private:
  void RecalculateViewMatrix() override;
};

} // namespace gameng

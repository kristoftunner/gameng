#pragma once

#include "camera.hpp"

namespace gameng
{

class OrtographicCamera : public Camera
{
public:
  OrtographicCamera(float left, float right, float bottom, float top);
private:
  void RecalculateViewMatrix() override;
};

} // namespace gameng

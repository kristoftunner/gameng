#pragma once

#include "camera.hpp"

namespace gameng
{

class OrtographicCamera : public Camera
{
public:
  OrtographicCamera(float left, float right, float bottom, float top);
  void SetRotation(const float& rotation) { m_rotation = rotation; UpdateView();}
  const float& GetRotation(){return m_rotation;}
private:
  void UpdateView() override;
};

} // namespace gameng

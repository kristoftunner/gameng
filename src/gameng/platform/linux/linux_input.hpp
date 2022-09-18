#pragma once

#include "gameng/input.hpp"

namespace gameng
{


class LinuxInput : public Input
{
public:
  virtual bool IsKeyPressedImpl(int keycode) override;
  virtual bool IsMouseButtonPressedImpl(int button) override;
  virtual std::pair<float, float> GetMousePositionImpl() override;
  virtual float GetMouseXImpl() override;
  virtual float GetMouseYImpl() override;
};

} // namespace gameng

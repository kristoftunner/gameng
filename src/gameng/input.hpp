#pragma once
#if 0
#include "gameng/applicaiton.hpp"

namespace gameng
{

class Input
{
public:
  inline static bool IsKeyPressed(int keycode){return s_instance->IsKeyPressedImpl();}
  inline static bool IsMouseButtonPressed(int keycode){return s_instance->IsMouseButtonPressedImpl();}
  inline static std::pair<float,float> GetMousePosition(){return s_instance->GetMousePositionImpl();}
  inline static float GetMouseX(){return s_instance->GetMouseXImpl();}
  inline static float GetMouseY(){return s_instance->GetMouseYImpl();}
protected:
  virtual bool IsKeyPressedImpl(int keycode) = 0;
private:
  static Input* s_instance;
};
} // namespace gameng
#endif
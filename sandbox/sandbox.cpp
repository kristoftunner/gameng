#include "gameng.hpp"
#include <iostream>

class ExampleLayer : public gameng::Layer
{
public:
  ExampleLayer() : Layer("Example")
  {
  }

  void OnUpdate() override
  {
    if(gameng::Input::IsKeyPressed(GAMENG_KEY_TAB))
      GAMENG_CORE_INFO("TAB key is pressed");
  }

  void OnEvent(gameng::Event& event) override{
    GAMENG_CORE_INFO("example layer: {0}", event);
  }
};
class Sandbox : public gameng::Application{
public:
  Sandbox()
  {
    PushLayer(new ExampleLayer());
    PushOverlay(new gameng::ImguiLayer());
  }
  ~Sandbox(){}
};

gameng::Application* gameng::CreateApplication()
{
  std::cout << "sandbox is created" << std::endl;
  return new Sandbox();
}
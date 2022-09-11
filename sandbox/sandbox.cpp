#include "gameng.hpp"

#include "gameng.hpp"
#include <iostream>

class ExampleLayer : public gameng::Layer
{
public:
  ExampleLayer() : Layer("Example"){}

  void OnUpdate() override
  {
    GAMENG_CORE_INFO("Example layer update");
  }

  void OnEvent(gameng::Event& event) override{
    GAMENG_CORE_INFO("{0}", event);
  }
};
class Sandbox : public gameng::Application{
public:
  Sandbox()
  {
    PushLayer(new ExampleLayer());
  }
  ~Sandbox(){}
};

gameng::Application* gameng::CreateApplication()
{
  std::cout << "sandbox is created" << std::endl;
  return new Sandbox();
}
#include "gameng.hpp"

#include "gameng.hpp"
#include <iostream>

class Sandbox : public gameng::Application{
public:
  Sandbox(){}
  ~Sandbox(){}
};

gameng::Application* gameng::CreateApplication()
{
  std::cout << "sandbox is created" << std::endl;
  return new Sandbox();
}
#pragma once

#include "gameng/applicaiton.hpp"
#include "gameng/log.hpp"

extern gameng::Application* gameng::CreateApplication();

int main(int argc, char** argv)
{
  gameng::Logger::Init();
  auto app = gameng::CreateApplication();
  app->Run();
  delete app;
}
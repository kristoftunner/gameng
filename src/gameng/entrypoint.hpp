#pragma once

#include "gameng/applicaiton.hpp"
#include "gameng/log.hpp"

extern gameng::Application* gameng::CreateApplication();

int main(int argc, char** argv)
{
  gameng::Logger::Init();
  GAMENG_CORE_ERR("error from core");
  GAMENG_CLIENT_WARN("warning from client");
  GAMENG_CORE_INFO("info from core");
  auto app = gameng::CreateApplication();
  app->Run();
  delete app;
}
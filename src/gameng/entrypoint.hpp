#pragma once

#include "applicaiton.hpp"

extern gameng::Application* gameng::CreateApplication();

int main(int argc, char** argv)
{
  auto app = gameng::CreateApplication();
  app->Run();
  delete app;
}
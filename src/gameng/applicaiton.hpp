#pragma once

namespace gameng {

class Application{
public:
  Application(){}
  ~Application(){}
  void Run();
};

/**
 * @brief function defined by the client
 * 
 * @return Application* 
 */
Application* CreateApplication();
} // namespace gameng
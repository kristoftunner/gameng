#pragma once
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
namespace gameng
{
class Logger {
public:
  Logger(){};
  inline static std::shared_ptr<spdlog::logger>& GetClientLogger(){return s_clientLogger;}
  inline static std::shared_ptr<spdlog::logger>& GetCoreLogger(){return s_coreLogger;}
  static void Init();
private:
  static std::shared_ptr<spdlog::logger> s_coreLogger;
  static std::shared_ptr<spdlog::logger> s_clientLogger;
}; 
} // namespace gameng

// Core logger defines
#define GAMENG_CORE_TRACE(...)  ::gameng::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define GAMENG_CORE_INFO(...)   ::gameng::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define GAMENG_CORE_WARN(...)   ::gameng::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define GAMENG_CORE_ERR(...)    ::gameng::Logger::GetCoreLogger()->error(__VA_ARGS__)

// Client logger defines
#define GAMENG_CLIENT_TRACE(...)  ::gameng::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define GAMENG_CLIENT_INFO(...)   ::gameng::Logger::GetClientLogger()->info(__VA_ARGS__)
#define GAMENG_CLIENT_WARN(...)   ::gameng::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define GAMENG_CLIENT_ERR(...)    ::gameng::Logger::GetClientLogger()->error(__VA_ARGS__)

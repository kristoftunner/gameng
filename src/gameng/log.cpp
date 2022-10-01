#include "gameng/log.hpp"
#include "gameng/core.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace gameng
{
  gameng::Ref<spdlog::logger> Logger::s_coreLogger;
  gameng::Ref<spdlog::logger> Logger::s_clientLogger;

  void Logger::Init()
  {
    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_coreLogger = spdlog::stdout_color_mt("core");  
    s_clientLogger = spdlog::stdout_color_mt("client"); 
    s_coreLogger->set_level(spdlog::level::trace);
    s_clientLogger->set_level(spdlog::level::info); 
  } 
} // namespace gameng

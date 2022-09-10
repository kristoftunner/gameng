
if(WIN32)
  set(GAMENG_PLATFORM "windows")
elseif(UNIX)
  set(GAMENG_PLATFORM "linux")
endif()

message(STATUS "GAMENG_PLATFORM:${GAMENG_PLATFORM}")
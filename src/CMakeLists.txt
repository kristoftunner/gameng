cmake_minimum_required(VERSION 3.16)

# get the sources
file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/gameng/*.cpp)
file(GLOB includes ${CMAKE_CURRENT_SOURCE_DIR}/gameng/*.hpp)
list(APPEND includes ${CMAKE_CURRENT_SOURCE_DIR}/gameng.hpp)
message(STATUS "collected source are ${sources}")
message(STATUS "collected includes are ${includes}")
set(GAMENG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "some docs")
message(STATUS "--------GAMENG variables------")
message(STATUS "GAMENG_INCLUDE_DIR is:${GAMENG_INCLUDE_DIR}")

add_library(gameng STATIC "")
target_sources(gameng PUBLIC ${sources})
target_sources(gameng PUBLIC ${includes})

target_link_libraries(gameng PUBLIC spdlog::spdlog)
target_include_directories(gameng PUBLIC ${PROJECT_SOURCE_DIR}/ext/spdlog/include)

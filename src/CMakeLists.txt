cmake_minimum_required(VERSION 3.16)

# get the dependecies
find_package(OpenGL REQUIRED) # this is required to link because glfw uses it

# get the sources
file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/gameng/*.cpp)
file(GLOB includes ${CMAKE_CURRENT_SOURCE_DIR}/gameng/*.hpp)
list(APPEND includes ${CMAKE_CURRENT_SOURCE_DIR}/gameng.hpp)
set(GAMENG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "some docs")

# get the window sources
list(APPEND includes ${CMAKE_CURRENT_SOURCE_DIR}/gameng/window/window.hpp)
file(GLOB src ${CMAKE_CURRENT_SOURCE_DIR}/gameng/window/${GAMENG_PLATFORM}/*.cpp)
file(GLOB inc ${CMAKE_CURRENT_SOURCE_DIR}/gameng/window/${GAMENG_PLATFORM}/*.hpp)
list(APPEND sources ${src})
list(APPEND includes ${inc})

# debug messages
#message(STATUS "--------GAMENG variables------")
#message(STATUS "GAMENG_INCLUDE_DIR is:${GAMENG_INCLUDE_DIR}")
message(STATUS "collected source are ${sources}")
message(STATUS "collected includes are ${includes}")

add_library(gameng STATIC "")
target_sources(gameng PUBLIC ${sources})
target_sources(gameng PUBLIC ${includes})

target_link_libraries(gameng PUBLIC spdlog::spdlog glfw ${OPENGL_LIBRARIES} glad)

target_include_directories(gameng 
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/ext/spdlog/include
  ${PROJECT_SOURCE_DIR}/ext/glfw/include
)

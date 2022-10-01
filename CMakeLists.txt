cmake_minimum_required(VERSION 3.16)

project("gameng" CXX C)
include(cmake/env_setup.cmake)
set (CMAKE_CXX_STANDARD 20)

# build the dependecies
add_subdirectory(ext/spdlog)
add_subdirectory(ext/glfw)
set(GLFW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/glfw/include)
add_subdirectory(ext/GLAD)
add_subdirectory(ext/imgui)
add_subdirectory(ext/glm)
add_subdirectory(ext/stb)
# actual project
add_subdirectory(src)
add_subdirectory(sandbox)
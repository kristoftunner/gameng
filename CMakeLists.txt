cmake_minimum_required(VERSION 3.16)

project("gameng" CXX C)
include(cmake/env_setup.cmake)

# build the dependecies
add_subdirectory(ext/spdlog)
add_subdirectory(ext/glfw)
add_subdirectory(ext/GLAD)

# actual project
add_subdirectory(src)
add_subdirectory(sandbox)
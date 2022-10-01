cmake_minimum_required(VERSION 3.16)

add_library(stb_image STATIC ${CMAKE_CURRENT_SOURCE_DIR}/stb_image.cpp)
target_include_directories(stb_image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

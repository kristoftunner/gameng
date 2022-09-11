cmake_minimum_required(VERSION 3.16)
find_package(OpenGL REQUIRED) # this is required to link because glfw uses it
add_library(glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c)
target_link_libraries(glad PUBLIC ${OPENGL_LIBRARIES} dl)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
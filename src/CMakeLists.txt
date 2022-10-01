cmake_minimum_required(VERSION 3.16)

# get the dependecies
find_package(OpenGL REQUIRED) # this is required to link because glfw uses it

# get the common sources
file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/gameng/*.cpp)
set(GAMENG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "some docs")

# get the core sources
file(GLOB src ${CMAKE_CURRENT_SOURCE_DIR}/gameng/core/${GAMENG_PLATFORM}/*.cpp)
list(APPEND sources ${src})

# get the window sources
file(GLOB src ${CMAKE_CURRENT_SOURCE_DIR}/gameng/platform/${GAMENG_PLATFORM}/*.cpp)
list(APPEND sources ${src})

# get the opengl sources
file(GLOB src ${CMAKE_CURRENT_SOURCE_DIR}/gameng/platform/opengl/*.cpp)
list(APPEND sources ${src})

# get the renderer sources
file(GLOB src ${CMAKE_CURRENT_SOURCE_DIR}/gameng/renderer/*.cpp)
list(APPEND sources ${src})

# get imgui sources
file(GLOB src ${CMAKE_CURRENT_SOURCE_DIR}/gameng/imgui/*.cpp)
list(APPEND sources ${src})

# debug messages
message(STATUS "----------- collected sources ----------")
foreach(src ${sources})
  message(STATUS "${src}")
endforeach()

add_library(gameng STATIC "")
target_sources(gameng PUBLIC ${sources})
target_sources(gameng PUBLIC ${includes})

target_link_libraries(gameng PUBLIC spdlog::spdlog glfw ${OPENGL_LIBRARIES} glad dl imgui glm stb_image)

target_include_directories(gameng 
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/ext/spdlog/include
  ${GLFW_INCLUDE_DIR}
  ${IMGUI_DIR}
  ${GAMENG_INCLUDE_DIR}
)

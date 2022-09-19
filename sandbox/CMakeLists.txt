cmake_minimum_required(VERSION 3.16)

add_executable(sandbox sandbox.cpp)
target_link_libraries(sandbox PRIVATE gameng)
target_include_directories(sandbox PRIVATE ${GAMENG_INCLUDE_DIR} ${IMGUI_DIR})
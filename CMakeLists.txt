cmake_minimum_required(VERSION 4.0)
project(Silnk2D)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/raylib)

add_executable(Silnk2D src/main.cpp
        src/Engine.cpp
        src/Engine.h)

target_link_libraries(Silnk2D PRIVATE raylib)
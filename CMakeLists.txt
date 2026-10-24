cmake_minimum_required(VERSION 3.20)

project(Alexs3DWorld LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(Alexs3DWorld main.cpp player.cpp renderer3d.cpp floor.cpp projection.cpp level1.cpp level2.cpp)

find_package(SDL3 REQUIRED CONFIG)

target_link_libraries(Alexs3DWorld PRIVATE SDL3::SDL3)


cmake_minimum_required(VERSION 3.20)

project(Alexs3DWorld LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")
endif()

add_executable(Alexs3DWorld main.cpp player.cpp renderer3d.cpp floor.cpp projection.cpp level1.cpp level2.cpp)

if(EMSCRIPTEN)
    add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
else()
    find_package(SDL3 REQUIRED CONFIG)
endif()

target_link_libraries(Alexs3DWorld PRIVATE SDL3::SDL3)


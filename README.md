Hello!

Welcome to Alex's 3d World (creative I know)

In truth I am not too sure what this project will become yet, however for a long time I have wanted to create a 3d game and graphics engine so here we are.

Before starting this project, I explored computer grpahics through resources succh as https://raytracing.github.io/books/RayTracingInOneWeekend.html. This helped spark my interest in the maths and programming behind 3D graphics.

If you would like to try something similar to this project i'd recommend exploring these resources first:

https://raytracing.github.io/books/RayTracingInOneWeekend.html

[SDL3 documentation ](https://wiki.libsdl.org/SDL3/FrontPage)


##Play

Browser demo: wip

##Controls

W/A/S/D = Move

Mouse = Look around

Walk into portal cube = Travel to other level

Esc = Quit

##Building Locally

The project uses C++20, Cmake, and SDL3

1. Install a C++ complier, Cmake and SDL3 (I used vcpkg)
2. Clone this repository 
3. Configure CMake with a toolchain that can find SDL3, then build 

For a windows setup using vcpkg:

cmake -S . -B build-windows -DCMAKE_TOOLCHAIN_FILE="C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake"
cmake --build build-windows
.\build-windows\Alexs3DWorld.exe

!Replace the example toolchain path with your own!


Built for Hack Club Terra (:

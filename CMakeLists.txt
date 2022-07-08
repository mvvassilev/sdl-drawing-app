cmake_minimum_required(VERSION 3.0.0)
project(sdl-drawing-app VERSION 0.1.0)

add_executable(sdl-drawing-app src/main.cpp src/app-window.cpp src/draw.cpp)
target_link_libraries(sdl-drawing-app SDL2main SDL2 GL SDL2_image)
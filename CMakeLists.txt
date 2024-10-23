cmake_minimum_required(VERSION 3.26)
project(BreakoutProject C)

set(CMAKE_C_STANDARD 23)

add_executable(BreakoutApp
        src/Game.c
        src/Game.h
        src/EntryPoint.c
        src/Logger.h
        )

add_subdirectory(vendor/SDL)
target_include_directories(BreakoutApp PUBLIC vendor/SDL/include)
target_link_libraries(BreakoutApp PUBLIC SDL2::SDL2main SDL2::SDL2-static)

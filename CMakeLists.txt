cmake_minimum_required(VERSION 3.26)
project(BreakoutProject C)

set(CMAKE_C_STANDARD 23)

add_executable(LastAttack
        src/Game.c
        src/Game.h
        src/EntryPoint.c
        src/Logger.h
        src/Window.c
        src/Window.h
        src/Events.c
        src/Events.h
        src/Callbacks/InputCallbacks.c
        src/Callbacks/InputCallbacks.h
)

add_subdirectory(vendor/SDL)
target_include_directories(LastAttack PUBLIC vendor/SDL/include)
target_link_libraries(LastAttack PUBLIC SDL2::SDL2main SDL2::SDL2-static)

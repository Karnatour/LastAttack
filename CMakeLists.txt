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
        src/Texture.c
        src/Texture.h
        src/Enemy.c
        src/Enemy.h
        src/MapLoader.c
        src/MapLoader.h
        src/Utils.c
        src/Utils.h
        src/Config.h
        src/Towers.c
        src/Towers.h
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_gfx REQUIRED)

add_subdirectory(tmx-tmx_1.10.0)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    get_property(_targets DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY IMPORTED_TARGETS)
    message(STATUS "Imported targets: ${_targets}")
    target_compile_definitions(LastAttack PRIVATE LASTATTACK_DEBUG)
endif ()

target_include_directories(LastAttack PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(LastAttack PRIVATE
        SDL2::Main SDL2::Image SDL2::GFX tmx m
)


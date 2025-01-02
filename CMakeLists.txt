cmake_minimum_required(VERSION 3.26)
project(BreakoutProject C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g")

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
        src/Wave.c
        src/Wave.h
        src/Time.c
        src/Time.h
        src/Font.c
        src/Font.h
        src/Level.c
        src/Level.h
        src/MainMenu.c
        src/MainMenu.h
)


if (UNIX)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
    add_subdirectory(tmx-tmx_1.10.0)
endif (UNIX)

if (UNIX)
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(SDL2_gfx REQUIRED)
elseif (MSVC)
    find_package(SDL2 CONFIG REQUIRED)
    find_package(SDL2_image CONFIG REQUIRED)
    find_package(SDL2_ttf CONFIG REQUIRED)
    find_package(sdl2-gfx CONFIG REQUIRED)
    find_package(tmx CONFIG REQUIRED)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    get_property(_targets DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY IMPORTED_TARGETS)
    message(STATUS "Imported targets: ${_targets}")
    target_compile_definitions(LastAttack PRIVATE LASTATTACK_DEBUG)
endif ()

target_include_directories(LastAttack PRIVATE ${SDL2_INCLUDE_DIRS})

if (UNIX)
    target_link_libraries(LastAttack PRIVATE SDL2::Main SDL2::Image SDL2::TTF SDL2::GFX tmx m)
elseif (MSVC)
    target_link_libraries(LastAttack PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf SDL2::SDL2_gfx tmx)
endif ()

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Tiled_files DESTINATION ${CMAKE_BINARY_DIR})

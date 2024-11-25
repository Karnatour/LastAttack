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
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(LastAttack PRIVATE LASTATTACK_DEBUG)
endif()

find_package(tmx REQUIRED)


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_include_directories(LastAttack PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(LastAttack PRIVATE
        SDL2::SDL2main
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        tmx
)

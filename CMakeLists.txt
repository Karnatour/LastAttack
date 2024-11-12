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
)

add_subdirectory(vendor/SDL)
target_include_directories(LastAttack PUBLIC vendor/SDL/include)

add_subdirectory(vendor/SDL_image)
target_include_directories(LastAttack PUBLIC vendor/SDL_image/include)

set(SDL2TTF_VENDORED ON)
add_subdirectory(vendor/SDL_ttf)
target_include_directories(LastAttack PUBLIC vendor/SDL_ttf)


if (TARGET SDL2::SDL2main)
    target_link_libraries(LastAttack PRIVATE SDL2::SDL2main)
endif ()

target_link_libraries(LastAttack PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)

if (WIN32)
    add_custom_command(
            TARGET LastAttack POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:LastAttack>"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2_image::SDL2_image>" "$<TARGET_FILE_DIR:LastAttack>"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2_ttf::SDL2_ttf>" "$<TARGET_FILE_DIR:LastAttack>"
            VERBATIM
    )
endif ()

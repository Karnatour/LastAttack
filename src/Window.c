#include "Window.h"
#include "Logger.h"
#include "SDL.h"

void createWindow(SDL_Window *window) {
    if ((window = SDL_CreateWindow("Last attack", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN)) == nullptr) {
        LOG_ERROR("Unable to create SDL window %s\n", SDL_GetError());
    } else {
        LOG_INFO("Created SDL window\n");
    }
}

void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        LOG_INFO("SDL Initialized\n");
    } else {
        LOG_ERROR("Unable to init SDL %s \n", SDL_GetError());
    }
}

void destroyWindow(SDL_Window *window) {
    SDL_DestroyWindow(window);
}

void exitSDL() {
    SDL_Quit();
}
#include "Window.h"

#include <SDL_ttf.h>

#include "Config.h"
#include "Logger.h"
#include "SDL.h"
#include "SDL_image.h"
SDL_Window *createWindow() {
    SDL_Window *window = SDL_CreateWindow("Last attack", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        LOG_ERROR("Unable to create SDL window %s\n", SDL_GetError());
    } else {
        LOG_INFO("[WINDOW] 1/1 Created SDL window\n");
    }
    return window;
}

SDL_Renderer *createRenderer(SDL_Window *window) {
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        LOG_ERROR("Unable to create SDL renderer %s\n", SDL_GetError());
    } else {
        LOG_INFO("[RENDERER] 1/2 Created SDL Renderer\n");
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if(!(IMG_Init(IMG_INIT_PNG))){
        LOG_ERROR("Unable to init SDL image %s\n",SDL_GetError());
    }
    else{
        LOG_INFO("[RENDERER] 2/2 Initialized SDL Image\n");
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    return renderer;
}

void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        LOG_INFO("[SDL] 1/2 SDL Initialized\n");
    } else {
        LOG_ERROR("Unable to init SDL %s \n", SDL_GetError());
    }
    if (TTF_Init() == 0) {
        LOG_INFO("[SDL] 2/2 SDL TTF Initialized\n");
    }
    else {
        LOG_ERROR("Unable to init SDL TTF %s \n", TTF_GetError());
    }
}

void destroyRenderer(SDL_Renderer *renderer) {
    SDL_DestroyRenderer(renderer);
    LOG_INFO("[WINDOW] 1/2 Destryoed SDL Renderer\n");
}

void changeTitle(SDL_Window* window, const char* title) {
    SDL_SetWindowTitle(window,title);
}

void destroyWindow(SDL_Window *window) {
    SDL_DestroyWindow(window);
    LOG_INFO("[WINDOW] 2/2 Destroyed SDL Window\n");
}

#pragma once

#include "SDL_render.h"

typedef struct{
    SDL_Texture* texture;
}Texture;

SDL_Texture* createTexture(const char* path);
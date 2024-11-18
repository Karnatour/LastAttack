#pragma once

#include "SDL_render.h"

typedef struct{
    SDL_Texture* texture;
}Texture;

Texture* createAndLoadTexture(SDL_Renderer* renderer, const char* path);
void renderTexture(SDL_Renderer* renderer, const Texture* texture);
void destroyTexture(Texture* texture);
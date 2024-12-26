#pragma once

#include "SDL_render.h"

SDL_Texture* createAndLoadTexture(SDL_Renderer* renderer, const char* path);
void renderTexture(SDL_Renderer* renderer,SDL_Texture* texture);
void destroyTexture(SDL_Texture* texture);
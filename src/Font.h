#pragma once
#include <SDL_render.h>
#include <SDL_ttf.h>

SDL_Texture* createMessageTexture(SDL_Renderer* renderer, const char* fontPath, int fontSize, const char* text, int r, int g, int b, SDL_Rect* rect);

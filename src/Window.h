#pragma once

#include "SDL_video.h"

void initSDL();
void createWindow(SDL_Window* window);

SDL_Surface* getWindowSurface(SDL_Window* window);
void updateWindowSurface(SDL_Window* window);

void destroyWindow(SDL_Window* window);
void exitSDL();

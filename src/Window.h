#pragma once

#include <SDL_video.h>
#include <SDL_render.h>

void initSDL();
SDL_Window * createWindow();
//TODO: Move to Renderer.h
SDL_Renderer * createRenderer(SDL_Window *window);

SDL_Surface* getWindowSurface(SDL_Window* window);
void updateWindowSurface(SDL_Window* window);
void changeTitle(SDL_Window* window, const char* title);


void destroyWindow(SDL_Window* window);
void destroyRenderer(SDL_Renderer *renderer);

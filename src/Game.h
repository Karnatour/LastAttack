#pragma once
#include <stdbool.h>
#include "SDL_render.h"
#include "SDL_video.h"

typedef struct{
    SDL_Renderer *renderer;
    SDL_Window *window;
    bool isRunning;
} Game;

Game* allocateGame();

void initGame(Game* game);
void runGame(Game* game);
void exitGame(Game* game);
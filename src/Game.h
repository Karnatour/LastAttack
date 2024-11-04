#pragma once
#include <stdbool.h>
#include "SDL_render.h"
#include "SDL_video.h"
#include "Callbacks/InputCallbacks.h"

struct EventHandler;

typedef struct Game{
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Surface *surface;
    bool isRunning;
    struct EventHandler *eventHandler;
    KeyCallback onKeyPressed;
} Game;

Game* allocateGame();
static void freeGame(Game* game);

void initGame(Game* game);
void runGame(Game* game);
void exitGame(Game* game);

static void testNullCallbacksAssign(Game *game);
static void assignCallbacks(Game* game);
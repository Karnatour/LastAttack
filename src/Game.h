#pragma once

#include "SDL_render.h"
#include "SDL_video.h"
#include "Callbacks/InputCallbacks.h"

struct EventHandler;

typedef struct Game {
    SDL_Renderer *renderer;
    SDL_Window *window;
    bool isRunning;
    struct EventHandler *eventHandler;
    //TODO: Probably move KeyCallback to Callback handler
    KeyCallback onKeyPressed;
    double deltaTime;
    Uint64 last;
} Game;

Game *allocateGame();

static void freeGame(Game *game);

void initGame(Game *game);

void runGame(Game *game);

void exitGame(Game *game);

static void assignCallbacks(Game *game);
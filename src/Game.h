#pragma once

#include "Events.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include "Callbacks/InputCallbacks.h"
#include <stdbool.h>

#include "Enemy.h"
#include "MapLoader.h"
#include "Towers.h"

struct EventHandler;

typedef struct Game {
    SDL_Renderer *renderer;
    SDL_Window *window;
    bool isRunning;
    EventHandler eventHandler;
    //TODO: Probably move KeyCallback to Callback handler
    KeyCallback onKeyPressed;
    MouseCallback onMousePressed;
    //TODO: Create Time struct
    float deltaTime;
    Uint64 last;
    Map map;
    Paths paths;
    Tower towers[5];
} Game;

Game *allocateGame();

void freeGame(Game *game);

void initGame(Game *game);

void runGame(Game *game);

void exitGame(Game *game);

void assignCallbacks(Game *game);

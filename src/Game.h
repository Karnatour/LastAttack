#pragma once

#include "Events.h"
#include <SDL_render.h>
#include <SDL_video.h>
#include "Callbacks/InputCallbacks.h"
#include <stdbool.h>

#include "Enemy.h"
#include "Level.h"
#include "MainMenu.h"
#include "MapLoader.h"
#include "Time.h"
#include "Towers.h"

struct EventHandler;

typedef enum {
    INGAME,
    MAINMENU
}GameState;



typedef struct Game{
    SDL_Renderer* renderer;
    SDL_Window* window;
    bool isRunning;
    EventHandler eventHandler;
    KeyCallback onKeyPressed;
    MouseCallback onMousePressed;
    MouseCallback onMouseMoved;
    Time time;
    Map map;
    Paths paths;
    Tower towers[5];
    bool toggleVision;
    Level level;
    GameState state;
    MainMenu mainMenu;
} Game;

Game* allocateGame();

void freeGame(Game* game);

void initGame(Game* game);

void runGame(Game* game);

void exitGame(Game* game);

void assignCallbacks(Game* game);

void renderGame(Game* game);

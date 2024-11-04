#pragma once
#include "SDL_events.h"
#include "Game.h"


typedef struct EventHandler{
    SDL_Event event;
} EventHandler;

int poolEvent(SDL_Event* event);
void handleEvent(Game* game);

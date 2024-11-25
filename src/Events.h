#pragma once
#include "SDL_events.h"

struct Game;

typedef struct EventHandler{
    SDL_Event event;
} EventHandler;

int poolEvent(SDL_Event* event);
void handleEvent(struct Game* game);

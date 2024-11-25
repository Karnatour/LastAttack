#pragma once

#include "SDL_keyboard.h"

struct Game;

typedef void (*KeyCallback)(SDL_Keysym key,struct Game* game);
typedef void (*MouseCallback)(struct Game* game);

void keyPressed(SDL_Keysym key,struct Game* game);
#pragma once

#include "SDL_keyboard.h"

typedef void (*KeyCallback)(SDL_Keysym key);

void keyPressed(SDL_Keysym key);
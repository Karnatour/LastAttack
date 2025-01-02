#pragma once

#include "SDL_keyboard.h"

struct Game;

typedef void (*KeyCallback)(SDL_Keysym key, struct Game *game);

typedef void (*MouseCallback)(int x, int y, struct Game *game);

void keyPressed(SDL_Keysym key, struct Game *game);
void mousePressed(int x,int y,struct Game* game);
void mouseMoved(int x, int y, struct Game* game);
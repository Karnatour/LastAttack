#pragma once
#include <SDL_stdinc.h>

typedef struct {
    float deltaTime;
    Uint64 last;
} Time;

void initTime(Time* time);
void updateTime(Time* time);

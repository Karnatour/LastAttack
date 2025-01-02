#include "Time.h"

#include <SDL_timer.h>

void updateTime(Time* time) {
    const Uint64 currentTime = SDL_GetPerformanceCounter();
    time->deltaTime = (float)(currentTime - time->last) / (float)SDL_GetPerformanceFrequency();
    time->last = currentTime;
}

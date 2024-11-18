#include "Events.h"
#include "Logger.h"
#include "Game.h"

int poolEvent(SDL_Event *event) {
    return SDL_PollEvent(event);
}

void handleEvent(Game *game) {
    switch (game->eventHandler->event.type) {
        case SDL_QUIT:
            LOG_INFO("Recived EVENT: SDL_QUIT\n");
            game->isRunning = false;
            break;
        case SDL_KEYDOWN:
            LOG_INFO("Recived EVENT: SDL_KEYDOWN KEY: %c\n",game->eventHandler->event.key.keysym.sym);
            game->onKeyPressed(game->eventHandler->event.key.keysym,game);
            break;
        case SDL_KEYUP:
            LOG_INFO("Recived EVENT: SDL_KEYUP KEY: %c\n",game->eventHandler->event.key.keysym.sym);
            break;
    }
}

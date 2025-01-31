#include "Events.h"
#include "Logger.h"
#include "Game.h"

int poolEvent(SDL_Event* event) {
    return SDL_PollEvent(event);
}

void handleEvent(Game* game) {
    switch (game->eventHandler.event.type) {
        case SDL_QUIT:
            LOG_DEBUG("Recived EVENT: SDL_QUIT\n");
            game->isRunning = false;
            break;
        case SDL_KEYDOWN:
            LOG_DEBUG("Recived EVENT: SDL_KEYDOWN KEY: %c\n", game->eventHandler.event.key.keysym.sym);
            game->onKeyPressed(game->eventHandler.event.key.keysym, game);
            break;
        case SDL_KEYUP:
            LOG_DEBUG("Recived EVENT: SDL_KEYUP KEY: %c\n", game->eventHandler.event.key.keysym.sym);
            break;
        case SDL_MOUSEMOTION:
            //LOG_DEBUG("Recived EVENT: SDL_MOUSEMOTION X:%d Y:%d\n",game->eventHandler.event.motion.x,game->eventHandler.event.motion.y);
            game->onMouseMoved(game->eventHandler.event.motion.x, game->eventHandler.event.motion.y, game);
            break;
        case SDL_MOUSEBUTTONUP:
            //LOG_DEBUG("Recived EVENT: SDL_MOUSEBUTTONUP BUTTON: %d\n",game->eventHandler.event.button.button);
            game->onMousePressed(game->eventHandler.event.motion.x, game->eventHandler.event.motion.y, game);
            break;
        case SDL_MOUSEBUTTONDOWN:
            //LOG_DEBUG("Recived EVENT: SDL_MOUSEBUTTDOWN BUTTON: %d\n", game->eventHandler.event.button.button);
            break;
    }
}

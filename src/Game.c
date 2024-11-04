#include <SDL.h>
#include "Game.h"
#include "Events.h"
#include "Logger.h"
#include "Window.h"

Game *allocateGame() {
    Game *game = malloc(sizeof(Game));
    if (game) {
        LOG_INFO("Allocated memory for game struct\n");
    } else {
        LOG_ERROR("Error while allocating memory for game struct\n");
        return nullptr;
    }

    game->eventHandler = malloc(sizeof(EventHandler));
    if (game->eventHandler) {
        LOG_INFO("Allocated memory for game->eventHandler struct\n");
    } else {
        LOG_ERROR("Error while allocating memory for game->eventHandler struct\n");
        free(game);
        return nullptr;
    }
    return game;
}

void initGame(Game *game) {
    SDL_SetMainReady();
    //assignCallbacks(game);
    testNullCallbacksAssign(game);
    initSDL();
    createWindow(game->window);

    LOG_INFO("Game initialized\n");

    game->isRunning = true;
}

void runGame(Game *game) {
    while(poolEvent(&game->eventHandler->event)) {
        handleEvent(game);
    }
}

void exitGame(Game *game) {
    if (game->isRunning) {
        LOG_WARNING("Trying to exit game while still in running state,aborting...\n");
        return;
    }
    destroyWindow(game->window);
    exitSDL();

    freeGame(game);
}

void freeGame(Game *game) {
    free(game->eventHandler);
    LOG_INFO("Released memory of game->eventHandler struct\n");
    free(game);
    LOG_INFO("Released memory of game struct\n");
}

void assignCallbacks(Game *game) {
    game->onKeyPressed = keyPressed;
}

//TODO: FIX WHY IS IGNORED THE IF NULL
void testNullCallbacksAssign(Game *game) {
    if (game->onKeyPressed == nullptr){
        LOG_ERROR("Callback onKeyPressed is null\n");
    }
}

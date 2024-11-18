#include <SDL.h>
#include "Game.h"

#include <SDL_image.h>

#include "Events.h"
#include "Logger.h"
#include "Texture.h"
#include "Window.h"

Game* allocateGame() {
    Game* game = malloc(sizeof(Game));
    if (game) {
        LOG_INFO("[ALLOCATION] 1/2 Allocated memory for game struct\n");
    }
    else {
        LOG_ERROR("Error while allocating memory for game struct\n");
        return nullptr;
    }

    game->eventHandler = malloc(sizeof(EventHandler));
    if (game->eventHandler) {
        LOG_INFO("[ALLOCATION] 2/2 Allocated memory for game->eventHandler struct\n");
    }
    else {
        LOG_ERROR("Error while allocating memory for game->eventHandler struct\n");
        free(game);
        return nullptr;
    }
    return game;
}

void initGame(Game* game) {
    SDL_SetMainReady();
    assignCallbacks(game);
    initSDL();
    game->window = createWindow();
    game->renderer = createRenderer(game->window);

    game->isRunning = true;
    game->deltaTime = 0;
    game->last = SDL_GetPerformanceCounter();
    LOG_INFO("----------Game initialized------------\n");
}


void runGame(Game* game) {
    while (poolEvent(&game->eventHandler->event)) {
        handleEvent(game);
    }

    //TODO: Remove in release
    //--------------------------------------------
    Uint64 currentTime = SDL_GetPerformanceCounter();
    game->deltaTime = (currentTime - game->last) / (double)SDL_GetPerformanceFrequency();
    game->last = currentTime;
    char title[128];
    sprintf(title, "%.1f", 1 / game->deltaTime);
    changeTitle(game->window, title);
    //--------------------------------------------


    SDL_Rect fillRect = {50, 50, 50, 50};
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(game->renderer, &fillRect);


    SDL_RenderPresent(game->renderer);
}

void exitGame(Game* game) {
    if (game->isRunning) {
        LOG_WARNING("Trying to exit game while still in running state,aborting...\n");
        return;
    }
    destroyRenderer(game->renderer);
    destroyWindow(game->window);
    IMG_Quit();
    SDL_Quit();

    freeGame(game);
}

void freeGame(Game* game) {
    free(game->eventHandler);
    LOG_INFO("[DEALLOCATION] 1/2 Released memory of game->eventHandler struct\n");
    free(game);
    LOG_INFO("[DEALLOCATION] 2/2 Released memory of game struct\n");
}

void assignCallbacks(Game* game) {
    game->onKeyPressed = keyPressed;
}

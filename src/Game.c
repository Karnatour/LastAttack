#include <SDL.h>
#include "Game.h"

#include <SDL_image.h>

#include "Enemy.h"
#include "Events.h"
#include "Logger.h"
#include "Texture.h"
#include "Window.h"

Texture* temp;

Vec2 path[4] = {{100.0f, 100.0f}, {400.0f, 100.0f}, {600.0f, 500.0f}, {800.0f, 500.0f}};
Enemy enemyTest;

Game* allocateGame() {
    Game* game = malloc(sizeof(Game));
    if (game) {
        LOG_INFO("[ALLOCATION] 1/1 Allocated memory for game struct\n");
    }
    else {
        LOG_ERROR("Error while allocating memory for game struct\n");
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
    temp = createAndLoadTexture(game->renderer, "../assets/brick.png");
    enemyTest.speed = 100.0f;
    enemyTest.pathIndex = 0;
    enemyTest.coords.x = 0;
    enemyTest.coords.y = 100;
}



void runGame(Game* game) {
    while (poolEvent(&game->eventHandler.event)) {
        handleEvent(game);
    }

    SDL_RenderClear(game->renderer);

    //TODO: Remove in release
    //--------------------------------------------
    Uint64 currentTime = SDL_GetPerformanceCounter();
    game->deltaTime = (float)(currentTime - game->last) / (float)SDL_GetPerformanceFrequency();
    game->last = currentTime;
    char title[128];
    sprintf(title, "%.1f", 1 / game->deltaTime);
    changeTitle(game->window, title);
    //--------------------------------------------

    printf("%f %f\n",enemyTest.coords.x,enemyTest.coords.y);

    if (enemyTest.pathIndex < 4){
    moveEnemy(&enemyTest, path, game->deltaTime);
    }
    SDL_Rect fillRect = {(int)enemyTest.coords.x, (int)enemyTest.coords.y, 32*3, 32*3};
    SDL_RenderFillRect(game->renderer, &fillRect);
    SDL_RenderCopy(game->renderer, temp->texture, nullptr, &fillRect);

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
    free(game);
    LOG_INFO("[DEALLOCATION] 1/1 Released memory of game struct\n");
}

void assignCallbacks(Game* game) {
    game->onKeyPressed = keyPressed;
}

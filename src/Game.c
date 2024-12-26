#include <SDL.h>
#include "Game.h"

#include <SDL_image.h>
#include <stdbool.h>

#include "Config.h"
#include "Enemy.h"
#include "Events.h"
#include "Logger.h"
#include "MapLoader.h"
#include "Texture.h"
#include "Window.h"

SDL_Texture* temp;
Enemy* enemyTest = NULL;
Enemy* enemyTest2 = NULL;
Enemy* enemyTest3 = NULL;

Game* allocateGame() {
    Game* game = malloc(sizeof(Game));
    if (game) {
        LOG_INFO("[ALLOCATION] 1/1 Allocated memory for game struct\n");
    }
    else {
        LOG_ERROR("Error while allocating memory for game struct\n");
        return NULL;
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

    setPaths(&game->paths);
    temp = createAndLoadTexture(game->renderer, "../assets/orc1_walk_full.png");
    SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_BLEND);

    enemyTest = createEnemy(LOCATION_TOP, TOP_SPAWN_POINT.x, TOP_SPAWN_POINT.y, 100.0f, 100.0f);
    enemyTest2 = createEnemy(LOCATION_TOP, LAKE_SPAWN_POINT.x, LAKE_SPAWN_POINT.y, 100.0f, 100.0f);
    enemyTest3 = createEnemy(LOCATION_TOP, BOTTOM_SPAWN_POINT.x, BOTTOM_SPAWN_POINT.y, 100.0f, 100.0f);

    initMapLoader(game);
    game->map.tmxMap = loadMap("Tiled_files/Undead_land.tmx");
}

void runGame(Game* game) {
    while (poolEvent(&game->eventHandler.event)) {
        handleEvent(game);
    }

    SDL_RenderClear(game->renderer);

    Uint64 currentTime = SDL_GetPerformanceCounter();
    game->deltaTime = (float)(currentTime - game->last) / (float)SDL_GetPerformanceFrequency();
    game->last = currentTime;

    char title[128];
    if (game->deltaTime > 0) {
        sprintf(title, "%.1f FPS", 1.0f / game->deltaTime);
    }
    else {
        sprintf(title, "FPS: N/A");
    }
    changeTitle(game->window, title);
    if (enemyTest->pathIndex < TOP_PATH_LENGTH) {
        moveEnemy(enemyTest, game->paths.topPath, game->deltaTime);
    }
    if (enemyTest2->pathIndex < LAKE_PATH_LENGTH) {
        moveEnemy(enemyTest2, game->paths.lakePath, game->deltaTime);
    }
    if (enemyTest3->pathIndex < BOTTOM_PATH_LENGTH) {
        moveEnemy(enemyTest3, game->paths.bottomPath, game->deltaTime);
    }
    renderMap(&game->map, game->renderer,game->deltaTime);
    renderEnemy(enemyTest,game->renderer,&game->paths,game->deltaTime,temp);
    renderEnemy(enemyTest2,game->renderer,&game->paths,game->deltaTime,temp);
    renderEnemy(enemyTest3,game->renderer,&game->paths,game->deltaTime,temp);
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


    free(enemyTest);
    freeMap(&game->map);
    freePaths(&game->paths);
    freeGame(game);
}

void freeGame(Game* game) {
    free(game);
    LOG_INFO("[DEALLOCATION] 1/1 Released memory of game struct\n");
}

void assignCallbacks(Game* game) {
    game->onKeyPressed = keyPressed;
}

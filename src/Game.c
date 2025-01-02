#include <SDL.h>
#include "Game.h"

#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include <stdbool.h>

#include "Config.h"
#include "Enemy.h"
#include "Events.h"
#include "Font.h"
#include "Logger.h"
#include "MapLoader.h"
#include "Texture.h"
#include "Window.h"

SDL_Texture* temp;
Enemy* enemyTest = NULL;
Enemy* enemyTest2 = NULL;
Enemy* enemyTest3 = NULL;
Wave wave;

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
    game->toggleVision = false;
    game->window = createWindow();
    game->renderer = createRenderer(game->window);
    game->isRunning = true;
    game->time.deltaTime = 0;
    game->time.last = SDL_GetPerformanceCounter();
    LOG_INFO("----------Game initialized------------\n");
    initTowerArray(game->renderer, game->towers);
    setPaths(&game->paths);
    temp = createAndLoadTexture(game->renderer, "../assets/orc1_walk_full.png");
    SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_BLEND);
    initLevel(game->renderer, &game->level);
    enemyTest = createEnemy(LOCATION_TOP, TOP_SPAWN_POINT.x, TOP_SPAWN_POINT.y, 100.0f, 50.0f);
    enemyTest2 = createEnemy(LOCATION_LAKE, LAKE_SPAWN_POINT.x, LAKE_SPAWN_POINT.y, 100.0f, 150.0f);
    enemyTest3 = createEnemy(LOCATION_BOTTOM, BOTTOM_SPAWN_POINT.x, BOTTOM_SPAWN_POINT.y, 100.0f, 100.0f);
    wave.enemies[0] = enemyTest;
    wave.enemies[1] = enemyTest2;
    wave.enemies[2] = enemyTest3;
    wave.numEnemies = wave.numAliveEnemies = 3;
    wave.texture = temp;
    initMapLoader(game);
    game->map.tmxMap = loadMap("Tiled_files/Undead_land.tmx");
}

void runGame(Game* game) {
    while (poolEvent(&game->eventHandler.event)) {
        handleEvent(game);
    }

    SDL_RenderClear(game->renderer);

    updateTime(&game->time);

    if (enemyTest->pathIndex < TOP_PATH_LENGTH && enemyTest->active) {
        moveEnemy(enemyTest, game->paths.topPath, game->time.deltaTime, &game->level.hp);
    }
    if (enemyTest2->pathIndex < LAKE_PATH_LENGTH && enemyTest2->active) {
        moveEnemy(enemyTest2, game->paths.lakePath, game->time.deltaTime, &game->level.hp);
    }
    if (enemyTest3->pathIndex < BOTTOM_PATH_LENGTH && enemyTest3->active) {
        moveEnemy(enemyTest3, game->paths.bottomPath, game->time.deltaTime, &game->level.hp);
    }
    renderMap(&game->map, game->renderer, game->time.deltaTime);

    renderWave(game->renderer,&wave);

    for (int i = 0; i < 5; ++i) {
        if (game->towers[i].occupied) {
            renderTower(game->renderer, &game->towers[i]);
            handleTowerProjectiles(&game->towers[i], &wave, game->time.deltaTime, game->renderer,&game->level);
        }

        if (game->towers[i].clicked && !game->towers[i].occupied) {
            renderTowerBuyMenu(game->renderer, &game->towers[i].buyMenu);
        }
        else if (game->towers[i].clicked && game->towers[i].occupied) {
            renderTowerUpgradeMenu(game->renderer, &game->towers[i].upgradeMenu);
        }

        if (game->towers[i].occupied && game->towers[i].hovered && game->toggleVision) {
            renderTowerRange(game->renderer, &game->towers[i]);
        }
    }

    char message[16];
    sprintf(message, "%d", game->level.hp);
    SDL_Texture *heartTexture = createMessageTexture(game->renderer,"assets/gui/fonts/OpenSans-Regular.ttf",80,message,255,25,25,&game->level.heartValueRect);

    sprintf(message, "%d", game->level.coins);
    SDL_Texture *coinTexture = createMessageTexture(game->renderer,"assets/gui/fonts/OpenSans-Regular.ttf",80,message,255,255,0,&game->level.coinValueRect);

    updateUITextures(heartTexture,coinTexture, &game->level);

    renderUI(game->renderer,&game->level);

    SDL_RenderPresent(game->renderer);
}

void exitGame(Game* game) {
    if (game->isRunning) {
        LOG_WARNING("Trying to exit game while still in running state,aborting...\n");
        return;
    }
    destroyRenderer(game->renderer);
    destroyWindow(game->window);

    freeEnemy(enemyTest);
    freeEnemy(enemyTest2);
    freeEnemy(enemyTest3);
    freeMap(&game->map);
    freePaths(&game->paths);
    freeGame(game);

    IMG_Quit();
    SDL_Quit();
}

void freeGame(Game* game) {
    free(game);
    LOG_INFO("[DEALLOCATION] 1/1 Released memory of game struct\n");
}

void assignCallbacks(Game* game) {
    game->onKeyPressed = keyPressed;
    game->onMousePressed = mousePressed;
    game->onMouseMoved = mouseMoved;
}

#include <SDL.h>
#include "Game.h"

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
    game->isRunning = true;

    SDL_SetMainReady();
    initSDL();
    game->window = createWindow();
    game->renderer = createRenderer(game->window);

    assignCallbacks(game);
    initTime(&game->time);

    initMainMenu(game->renderer, &game->mainMenu);
    initMapLoader(game);
    initTowerArray(game->renderer, game->towers);
    initLevel(game->renderer, &game->level);
    setPaths(&game->paths);

    game->map.tmxMap = loadMap("Tiled_files/Undead_land.tmx");

    game->toggleVision = false;
    game->state = MAINMENU;
    LOG_INFO("----------Game initialized------------\n");
}

void runGame(Game* game) {
    while (poolEvent(&game->eventHandler.event)) {
        handleEvent(game);
    }

    SDL_RenderClear(game->renderer);

    updateTime(&game->time);
    renderMap(&game->map, game->renderer, game->time.deltaTime);

    switch (game->state) {
        case INGAME:
            renderGame(game);
            break;
        case MAINMENU:
            renderMainMenu(game);
            break;
    }

    SDL_RenderPresent(game->renderer);
}

void exitGame(Game* game) {
    if (game->isRunning) {
        LOG_WARNING("Trying to exit game while still in running state,aborting...\n");
        return;
    }
    destroyRenderer(game->renderer);
    destroyWindow(game->window);

    clearTowerArray(game->towers);
    clearWaves(game->level.waves);
    freeMap(&game->map);
    freePaths(&game->paths);
    freeGame(game);

    IMG_Quit();
    TTF_Quit();
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

void renderGame(Game* game) {
    updateWave(&game->level.waves[game->level.currentWave - 1], game->paths, game->time.deltaTime, &game->level.hp, &game->level.hp);
    renderWave(game->renderer, &game->level.waves[game->level.currentWave - 1]);

    for (int i = 0; i < 5; ++i) {
        if (game->towers[i].occupied) {
            renderTower(game->renderer, &game->towers[i]);
            handleTowerProjectiles(&game->towers[i], &game->level.waves[game->level.currentWave - 1], game->time.deltaTime, game->renderer, &game->level);
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
    SDL_Texture* heartTexture = createMessageTexture(game->renderer, "assets/gui/fonts/OpenSans-Regular.ttf", 80, message, 255, 25, 25, &game->level.heartValueRect);

    sprintf(message, "%d", game->level.coins);
    SDL_Texture* coinTexture = createMessageTexture(game->renderer, "assets/gui/fonts/OpenSans-Regular.ttf", 80, message, 255, 255, 0, &game->level.coinValueRect);

    updateUITextures(heartTexture, coinTexture, &game->level);
    renderUI(game->renderer, &game->level);

    if (game->level.waves[game->level.currentWave - 1].numAliveEnemies == 0) {
        if (game->level.currentWave != 3) {
            ++game->level.currentWave;
        }
        else {
            endLevel(VICTORY, game);
        }
    }

    if (game->level.hp == 0) {
        endLevel(DEFEAT, game);
    }
}

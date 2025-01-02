#include "InputCallbacks.h"

#include "../Game.h"
#include "../Logger.h"

void keyPressed(const SDL_Keysym key, Game* game) {
    switch (key.sym) {
        case SDLK_ESCAPE:
            game->isRunning = false;
            break;
        case SDLK_v:
            if (game->toggleVision) {
                game->toggleVision = false;
            }
            else {
                game->toggleVision = true;
            }
            break;
    }
}

void mousePressed(int x, int y, struct Game* game) {
    SDL_Point point;
    point.x = x;
    point.y = y;

    switch (game->state) {
        case INGAME:
            for (int i = 0; i < 5; ++i) {
                handleTowerClick(game->renderer, &game->towers[i].buyMenu, &game->towers[i], point);
                if (!game->towers[i].occupied && game->towers[i].clicked) {
                    handleTowerBuyMenuClick(game->renderer, &game->towers[i], point, &game->level.coins);
                }
                else if (game->towers[i].occupied && game->towers[i].clicked) {
                    handleTowerUpgradeMenuClick(&game->towers[i], point, &game->level.coins);
                }
            }
            break;
        case MAINMENU:
            handleMainMenuClick(game, point);
            break;
    }
}

void mouseMoved(int x, int y, struct Game* game) {
    SDL_Point point;
    point.x = x;
    point.y = y;
    for (int i = 0; i < 5; ++i) {
        if (game->towers[i].occupied) {
            handleTowerHover(point, &game->towers[i]);
        }
    }
}

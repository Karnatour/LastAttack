#include "InputCallbacks.h"

#include "../Game.h"
#include "../Logger.h"

void keyPressed(const SDL_Keysym key, Game *game) {
    switch (key.sym) {
        case SDLK_ESCAPE:
            game->isRunning = false;
            break;
    }
}

void mousePressed(int x, int y, struct Game *game) {
    SDL_Point point;
    point.x = x;
    point.y = y;

    for (int i = 0; i < 5; ++i) {
        handleTowerClick(game->renderer, &game->towers[i].buyMenu, &game->towers[i], point);
        if (!game->towers[i].occupied){
        handleTowerBuyMenuClick(game->renderer, &game->towers[i], point);
        }
        else{
            handleTowerUpgradeMenuClick(game->renderer, &game->towers[i],point);
        }
    }
}




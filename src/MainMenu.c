#include "MainMenu.h"

#include "Config.h"
#include "Game.h"
#include "Texture.h"

void initMainMenu(SDL_Renderer* renderer, MainMenu* menu) {
    menu->logoTexture = createAndLoadTexture(renderer, "assets/gui/logo.png");
    menu->playTexture = createAndLoadTexture(renderer, "assets/gui/play.png");
    menu->quitTexture = createAndLoadTexture(renderer, "assets/gui/quit.png");

    menu->mainMenuRect.w = 1400;
    menu->mainMenuRect.h = 200;
    menu->mainMenuRect.x = SCREEN_WIDTH / 2 - menu->mainMenuRect.w / 2;
    menu->mainMenuRect.y = SCREEN_HEIGHT / 2 - 300;

    menu->playRect.w = 266;
    menu->playRect.h = 102;
    menu->playRect.x = SCREEN_WIDTH / 2 - menu->playRect.w / 2;
    menu->playRect.y = SCREEN_HEIGHT / 2 - menu->playRect.h + 80;

    menu->quitRect.w = 266;
    menu->quitRect.h = 127;
    menu->quitRect.x = SCREEN_WIDTH / 2 - menu->quitRect.w / 2;
    menu->quitRect.y = SCREEN_HEIGHT / 2 + 200;
}

void handleMainMenuClick(Game* game, SDL_Point point) {
    if (SDL_PointInRect(&point, &game->mainMenu.playRect)) {
        game->state = INGAME;
    }
    else if (SDL_PointInRect(&point, &game->mainMenu.quitRect)) {
        game->isRunning = false;
    }
}

void destroyMainMenu(MainMenu* menu) {
    destroyTexture(menu->logoTexture);
}

void renderMainMenu(Game* game) {
    SDL_RenderCopy(game->renderer, game->mainMenu.logoTexture,NULL, &game->mainMenu.mainMenuRect);
    SDL_RenderCopy(game->renderer, game->mainMenu.playTexture,NULL, &game->mainMenu.playRect);
    SDL_RenderCopy(game->renderer, game->mainMenu.quitTexture,NULL, &game->mainMenu.quitRect);
}
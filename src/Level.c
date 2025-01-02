#include "Level.h"

#include "Config.h"
#include "Font.h"
#include "Game.h"
#include "Logger.h"
#include "Texture.h"
#include "Towers.h"

void initLevel(SDL_Renderer* renderer, Level* level) {
    level->hp = HP;
    level->coins = 10;
    level->heartRect.w = 64;
    level->heartRect.h = 64;
    level->heartRect.y = 725;
    level->heartRect.x = 0;
    level->heartTexture = createAndLoadTexture(renderer, "assets/gui/heart.png");

    level->heartValueRect.x = level->heartRect.x + level->heartRect.w + 5;
    level->heartValueRect.y = 700;
    level->heartValueTexture = NULL;

    level->coinRect.w = 64;
    level->coinRect.h = 64;
    level->coinRect.y = 725 + 64;
    level->coinRect.x = 0;
    level->coinTexture = createAndLoadTexture(renderer, "assets/gui/coin.png");

    level->coinValueRect.x = level->coinRect.x + level->coinRect.w + 5;
    level->coinValueRect.y = 700 + 64;
    level->coinValueTexture = NULL;

    level->currentWave = 1;
    loadWaves(renderer, level->waves);
}

void renderUI(SDL_Renderer* renderer, const Level* level) {
    SDL_RenderCopy(renderer, level->heartTexture,NULL, &level->heartRect);
    SDL_RenderCopy(renderer, level->heartValueTexture,NULL, &level->heartValueRect);

    SDL_RenderCopy(renderer, level->coinTexture,NULL, &level->coinRect);
    SDL_RenderCopy(renderer, level->coinValueTexture,NULL, &level->coinValueRect);
}

void updateUITextures(SDL_Texture* newHeartTexture, SDL_Texture* newCoinTexture, Level* level) {
    if (level->heartValueTexture != NULL) {
        destroyTexture(level->heartValueTexture);
    }
    if (level->coinValueTexture != NULL) {
        destroyTexture(level->coinValueTexture);
    }
    level->heartValueTexture = newHeartTexture;
    level->coinValueTexture = newCoinTexture;
}

void destroyLevel(Level* level) {
    destroyTexture(level->heartValueTexture);
    destroyTexture(level->coinValueTexture);
    destroyTexture(level->heartTexture);
}

void endLevel(EndingType endingType, struct Game* game) {
    switch (endingType) {
        case VICTORY:
            SDL_Rect victoryRect;
            SDL_Texture* victoryTexture = createMessageTexture(game->renderer, "assets/gui/fonts/OpenSans-Regular.ttf", 256, "Victory!", 25, 255, 25, &victoryRect);
            victoryRect.x = SCREEN_WIDTH / 2 - victoryRect.w / 2;
            victoryRect.y = SCREEN_HEIGHT / 2 - victoryRect.h / 2;
            SDL_RenderCopy(game->renderer, victoryTexture,NULL, &victoryRect);
            break;
        case DEFEAT:
            SDL_Rect defeatRect;
            SDL_Texture* defeatTexture = createMessageTexture(game->renderer, "assets/gui/fonts/OpenSans-Regular.ttf", 256, "Defeat!", 255, 25, 25, &defeatRect);
            defeatRect.x = SCREEN_WIDTH / 2 - defeatRect.w / 2;
            defeatRect.y = SCREEN_HEIGHT / 2 - defeatRect.h / 2;
            SDL_RenderCopy(game->renderer, defeatTexture,NULL, &defeatRect);
            break;
    }
    game->state = MAINMENU;
    SDL_RenderPresent(game->renderer);
    SDL_Delay(3000);
    prepareForNextLevel(game);
}

void prepareForNextLevel(struct Game* game) {
    clearTowerArray(game->towers);
    clearLevel(&game->level);

    initTowerArray(game->renderer, game->towers);
    initLevel(game->renderer, &game->level);
}

void clearLevel(Level* level) {
    clearWaves(level->waves);
    destroyTexture(level->coinTexture);
    destroyTexture(level->heartTexture);
    destroyTexture(level->coinValueTexture);
    destroyTexture(level->heartValueTexture);
}

#include "Level.h"

#include "Config.h"
#include "Font.h"
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
    loadWaves(level->waves);
}

void loadWaves(Wave* waves) {
    const SpawnLocation spawnLocations[] = {LOCATION_TOP, LOCATION_LAKE, LOCATION_BOTTOM};
    const Vec2 spawnPoints[] = {TOP_SPAWN_POINT, LAKE_SPAWN_POINT, BOTTOM_SPAWN_POINT};
    const int numLocations = 3;
    const float spawnDelays[] = {0.5f, 0.25f, 0.125f};

    //5,25,125 enemies
    for (int i = 0; i < 3; ++i) {
        int numEnemies = pow(5, i);
        waves[i].numEnemies = numEnemies;
        waves[i].numAliveEnemies = numEnemies;
        waves[i].spawnDelay = spawnDelays[i];
        waves[i].timeSinceLastSpawn = 0.0f;

        for (int j = 0; j < numEnemies; ++j) {
            // Alternate spawn location every 5 enemies
            const int locationIndex = (j / 5) % numLocations;

            waves[i].enemies[j] = createEnemy(
                spawnLocations[locationIndex],
                spawnPoints[locationIndex].x,
                spawnPoints[locationIndex].y,
                100.0f + i * 50,
                50.0f + i * 25.0f
            );
            waves[i].enemies[j]->active = false; // Inactive until it's time to spawn
        }
    }
}

void updateWave(Wave* wave, float deltaTime) {
    wave->timeSinceLastSpawn += deltaTime;

    for (int i = 0; i < wave->numEnemies; ++i) {
        // Check if the enemy is inactive and the spawn timer has passed the delay
        if (!wave->enemies[i]->active && wave->timeSinceLastSpawn >= wave->spawnDelay) {
            wave->enemies[i]->active = true;
            wave->timeSinceLastSpawn = 0.0f;

            // Spawn only one enemy at a time
            break;
        }
    }
}

void nextWave() {
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

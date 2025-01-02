#include "Wave.h"

#include <stdbool.h>
#include "Config.h"
#include "Logger.h"
#include "Texture.h"

void loadWaves(SDL_Renderer* renderer, Wave* waves) {
    const SpawnLocation spawnLocations[] = {LOCATION_TOP, LOCATION_LAKE, LOCATION_BOTTOM};
    const Vec2 spawnPoints[] = {TOP_SPAWN_POINT, LAKE_SPAWN_POINT, BOTTOM_SPAWN_POINT};
    const int numLocations = 3;
    const float spawnDelays[] = {1.5f, 0.5f, 0.15f};

    //5,25,125 enemies
    for (int i = 0; i < 3; ++i) {
        int numEnemies = (int)pow(5, i + 1);
        waves[i].numEnemies = numEnemies;
        waves[i].numAliveEnemies = numEnemies;
        waves[i].spawnDelay = spawnDelays[i];
        waves[i].timeSinceLastSpawn = 0.0f;
        waves[i].texture = createAndLoadTexture(renderer, "../assets/orc1_walk_full.png");
        for (int j = 0; j < numEnemies; ++j) {
            // Alternate spawn location every 5 enemies
            const int locationIndex = (j / 1) % numLocations;

            waves[i].enemies[j] = createEnemy(
                spawnLocations[locationIndex],
                spawnPoints[locationIndex].x,
                spawnPoints[locationIndex].y,
                100.0f + i * 150,
                50.0f + i * 20.0f
            );
            waves[i].enemies[j]->active = false;
        }
    }
}

void clearWaves(Wave* waves) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < waves[i].numEnemies; ++j) {
            freeEnemy(waves[i].enemies[j]);
        }
        SDL_DestroyTexture(waves[i].texture);
    }
}

void renderWave(SDL_Renderer* renderer, const Wave* wave) {
    for (int i = 0; i < wave->numEnemies; ++i) {
        if (wave->enemies[i]->active) {
            renderEnemy(wave->enemies[i], renderer, wave->texture);
        }
    }
}

void updateWave(Wave* wave, Paths paths, float deltaTime, int* levelHp, int* coins) {
    wave->timeSinceLastSpawn += deltaTime;

    // Spawning Logic
    for (int i = 0; i < wave->numEnemies; ++i) {
        // Only spawn inactive enemies that have not been killed and reached the end
        if (wave->enemies[i]->active == false && wave->enemies[i]->hp > 0.0f && wave->enemies[i]->reachedEnd == 0 && wave->timeSinceLastSpawn >= wave->spawnDelay) {
            wave->enemies[i]->active = true;
            wave->timeSinceLastSpawn = 0.0f;
            break;
        }
    }

    // Movement Logic
    for (int i = 0; i < wave->numEnemies; ++i) {
        if (wave->enemies[i]->active) {
            switch (wave->enemies[i]->location) {
                case LOCATION_TOP:
                    if (wave->enemies[i]->pathIndex < TOP_PATH_LENGTH) {
                        moveEnemy(wave->enemies[i], paths.topPath, deltaTime, levelHp, &wave->numAliveEnemies);
                    }
                    break;
                case LOCATION_LAKE:
                    if (wave->enemies[i]->pathIndex < LAKE_PATH_LENGTH) {
                        moveEnemy(wave->enemies[i], paths.lakePath, deltaTime, levelHp, &wave->numAliveEnemies);
                    }
                    break;
                case LOCATION_BOTTOM:
                    if (wave->enemies[i]->pathIndex < BOTTOM_PATH_LENGTH) {
                        moveEnemy(wave->enemies[i], paths.bottomPath, deltaTime, levelHp, &wave->numAliveEnemies);
                    }
                    break;
            }
        }
    }

    // Update poison
    for (int enemyIndex = 0; enemyIndex < wave->numEnemies; ++enemyIndex) {
        Enemy* enemy = wave->enemies[enemyIndex];
        if (enemy->active && enemy->poisoned) {
            enemy->poisonedTimer += deltaTime;
            if (enemy->poisonedTimer >= 0.125f) {
                enemy->hp -= POISON_DAMAGE;
                //Enemy killed by poison
                if (enemy->hp <= 0 && enemy->active) {
                    enemy->active = false;
                    --wave->numAliveEnemies;
                    *coins = *coins + 20;
                }

                // Reset the poison timer
                enemy->poisonedTimer = 0.0f;
            }
        }
    }
}

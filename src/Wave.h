#pragma once
#include <stdbool.h>

#include "Enemy.h"

typedef struct {
    int numEnemies;
    int numAliveEnemies;
    Enemy* enemies[164];
    SDL_Texture *texture;
    float spawnDelay;
    float timeSinceLastSpawn;
} Wave;

void renderWave(SDL_Renderer* renderer, const Wave *wave);
void updateWave(Wave* wave, Paths paths, float deltaTime, int* levelHp, int* coins);
void loadWaves(SDL_Renderer* renderer, Wave *waves);
void clearWaves(Wave *waves);
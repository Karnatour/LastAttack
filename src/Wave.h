#pragma once
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
void updateWave(Wave* wave, float deltaTime);
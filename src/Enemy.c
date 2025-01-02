#include "Enemy.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Config.h"
#include "Logger.h"


Enemy* createEnemy(SpawnLocation spawnLocation, const float x, const float y, const float hp, const float speed) {
    static int id = 0;
    Enemy* enemy = NULL;
    enemy = (Enemy*)malloc(sizeof(Enemy));
    enemy->active = true;
    enemy->pathIndex = 0;
    enemy->hp = hp;
    enemy->speed = speed;
    enemy->coords.x = x;
    enemy->coords.y = y;
    enemy->rect.x = (int)x;
    enemy->rect.y = (int)y;
    enemy->rect.w = 128;
    enemy->rect.h = 128;
    enemy->id = id;
    ++id;
    //TODO: Set direction by spawn
    enemy->location = spawnLocation;
    switch (enemy->location) {
        case LOCATION_TOP:
            enemy->direction = DIRECTION_DOWN;
            break;
        case LOCATION_LAKE:
            enemy->direction = DIRECTION_UP;
            break;
        case LOCATION_BOTTOM:
            enemy->direction = DIRECTION_LEFT;
            break;
    }
    return enemy;
}

void moveEnemy(Enemy* enemy, const Vec2* path, const float deltaTime, int* hp) {
    if (fabsf(enemy->coords.x - CAPITOL_LOCATION.x) <= 10 && fabsf(enemy->coords.y - CAPITOL_LOCATION.y) <= 10) {
        enemy->active = false;
        *hp = *hp - 1;
    }
    Vec2 target = path[enemy->pathIndex];
    Vec2 directionVec;
    directionVec.x = target.x - enemy->coords.x;
    directionVec.y = target.y - enemy->coords.y;
    float distance = sqrtf(directionVec.x * directionVec.x + directionVec.y * directionVec.y);

    float moveDistance = fmaxf(enemy->speed * deltaTime, MIN_THRESHOLD);

    if (moveDistance >= distance) {
        enemy->coords.x = target.x;
        enemy->coords.y = target.y;
        ++enemy->pathIndex;
    }
    else {
        Vec2 normalizedDistanceVec;
        normalizedDistanceVec.x = directionVec.x / distance;
        normalizedDistanceVec.y = directionVec.y / distance;

        enemy->coords.x += normalizedDistanceVec.x * moveDistance;
        enemy->coords.y += normalizedDistanceVec.y * moveDistance;
    }
}

void renderEnemy(Enemy* enemy, SDL_Renderer* renderer, SDL_Texture* texture) {
    SDL_Rect srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 64;
    srcRect.h = 64;

    enemy->rect.x = (int)enemy->coords.x;
    enemy->rect.y = (int)enemy->coords.y;
    SDL_RenderCopy(renderer, texture, &srcRect, &enemy->rect);
}

void setPaths(Paths* paths) {
    paths->topPath = malloc(sizeof(Vec2) * TOP_PATH_LENGTH);
    for (int i = 0; i < TOP_PATH_LENGTH; ++i) {
        paths->topPath[i] = TOP_PATH_POINTS[i];
    }
    paths->topLength = TOP_PATH_LENGTH;

    paths->lakePath = malloc(sizeof(Vec2) * LAKE_PATH_LENGTH);
    for (int i = 0; i < LAKE_PATH_LENGTH; ++i) {
        paths->lakePath[i] = LAKE_PATH_POINTS[i];
    }
    paths->lakeLength = LAKE_PATH_LENGTH;

    paths->bottomPath = malloc(sizeof(Vec2) * BOTTOM_PATH_LENGTH);
    for (int i = 0; i < BOTTOM_PATH_LENGTH; ++i) {
        paths->bottomPath[i] = BOTTOM_PATH_POINTS[i];
    }
    paths->bottomLength = BOTTOM_PATH_LENGTH;
}

void freePaths(Paths* paths) {
    if (paths->topPath) {
        LOG_DEBUG("Destryoed topPath\n");
        free(paths->topPath);
        paths->topPath = NULL;
    }
    else {
        LOG_ERROR("Trying to free topPath pointer\n");
    }

    if (paths->lakePath) {
        LOG_DEBUG("Destryoed lakePath\n");
        free(paths->lakePath);
        paths->lakePath = NULL;
    }
    else {
        LOG_ERROR("Trying to free lakePath pointer\n");
    }

    if (paths->bottomPath) {
        LOG_DEBUG("Destryoed bottomPath\n");
        free(paths->bottomPath);
        paths->bottomPath = NULL;
    }
    else {
        LOG_ERROR("Trying to free bottomPath pointer\n");
    }
}

void freeEnemy(Enemy* enemy) {
    if (enemy) {
        LOG_DEBUG("Destryoed enemy\n");
        free(enemy);
        enemy = NULL;
    }
    else {
        LOG_ERROR("Trying to free NULL enemy pointer\n");
    }
}

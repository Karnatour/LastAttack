#include "Enemy.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Config.h"
#include "Logger.h"



Enemy* createEnemy(SpawnLocation spawnLocation, const float x, const float y, const float hp, const float speed) {
    Enemy* enemy = NULL;
    enemy = (Enemy*)malloc(sizeof(Enemy));
    enemy->active = true;
    enemy->pathIndex = 0;
    enemy->hp = hp;
    enemy->speed = speed;
    enemy->coords.x = x;
    enemy->coords.y = y;
    //TODO: Set direction by spawn
    enemy->direction = DIRECTION_RIGHT;
    return enemy;
}

void moveEnemy(Enemy* enemy, const Vec2* path, const float deltaTime) {
    Vec2 target = path[enemy->pathIndex];
    Vec2 distanceVec;
    distanceVec.x = target.x - enemy->coords.x;
    distanceVec.y = target.y - enemy->coords.y;
    float distance = sqrtf(distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y);

    if (distance < MIN_THRESHOLD) { // Snap to target if very close
        enemy->coords.x = target.x;
        enemy->coords.y = target.y;
        ++enemy->pathIndex;
        return;
    }

    float moveDistance = fmaxf(enemy->speed * deltaTime, MIN_THRESHOLD);

    if (moveDistance >= distance) {
        enemy->coords.x = target.x;
        enemy->coords.y = target.y;
        ++enemy->pathIndex;
    } else {
        Vec2 normalizedDistanceVec;
        normalizedDistanceVec.x = distanceVec.x / distance;
        normalizedDistanceVec.y = distanceVec.y / distance;

        enemy->coords.x += normalizedDistanceVec.x * moveDistance;
        enemy->coords.y += normalizedDistanceVec.y * moveDistance;
    }
}

void renderEnemy(Enemy* enemy, SDL_Renderer* renderer, const Paths* paths, const float deltaTime, SDL_Texture* texture) {
    const Vec2* path = NULL;
    switch (enemy->location) {
        case LOCATION_TOP:
            path = paths->topPath;
            break;
        case LOCATION_LAKE:
            path = paths->lakePath;
            break;
        case LOCATION_BOTTOM:
            path = paths->bottomPath;
            break;
    }

    SDL_Rect srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 64;
    srcRect.h = 64;

    SDL_Rect fillRect = {(int)enemy->coords.x, (int)enemy->coords.y, 128, 128};

    SDL_RenderFillRect(renderer, &fillRect);
    SDL_RenderCopy(renderer, texture, &srcRect, &fillRect);
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

void freePaths(const Paths* paths) {
    free(paths->topPath);
    free(paths->lakePath);
    free(paths->bottomPath);
}

void freeEnemy(Enemy* enemy) {
    if (enemy) {
        free(enemy);
    }
    else {
        LOG_ERROR("Trying to free NULL enemy pointer\n");
    }
}

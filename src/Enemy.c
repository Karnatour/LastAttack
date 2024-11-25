#include "Enemy.h"

#include <math.h>

#include "Logger.h"

#define MIN_MOVE_DISTANCE 0.1f

void moveEnemy(Enemy* enemy, const Vec2* path, const float deltaTime) {
    Vec2 target = path[enemy->pathIndex];
    Vec2 distanceVec;
    distanceVec.x = target.x - enemy->coords.x;
    distanceVec.y = target.y - enemy->coords.y;
    float distance = sqrtf(distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y);

    if (distance < MIN_MOVE_DISTANCE) {
        ++enemy->pathIndex;
    }
    else {
        Vec2 normalizedDistanceVec;
        normalizedDistanceVec.x = distanceVec.x / distance;
        normalizedDistanceVec.y = distanceVec.y / distance;

        float moveDistance = enemy->speed * deltaTime;

        if (moveDistance < MIN_MOVE_DISTANCE) {
            moveDistance = MIN_MOVE_DISTANCE;
        }

        enemy->coords.x += normalizedDistanceVec.x * moveDistance;
        enemy->coords.y += normalizedDistanceVec.y * moveDistance;
    }
}
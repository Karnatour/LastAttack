#pragma once

typedef struct {
    float x, y;
} Vec2;

typedef enum {
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT
} Direction;

typedef struct {
    Vec2 coords;
    int pathIndex;
    Direction direction;
    float hp;
    float speed;
    int active;
} Enemy;

typedef enum {
    LOCATION_TOP,
    LOCATION_CAVE,
    LOCATION_TEMPLE,
} SpawnLocation;

Enemy* createEnemy();
void moveEnemy(Enemy* enemy, const Vec2* path, float deltaTime);

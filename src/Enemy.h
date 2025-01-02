#pragma once
#include <SDL_render.h>
#include <stdbool.h>

#include "Utils.h"

typedef enum {
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT
} Direction;

typedef enum {
    LOCATION_TOP,
    LOCATION_LAKE,
    LOCATION_BOTTOM,
} SpawnLocation;

typedef struct {
    int id;
    SDL_Rect rect;
    Vec2 coords;
    int pathIndex;
    Direction direction;
    float hp;
    float speed;
    float originalSpeed;
    bool active;
    bool reachedEnd;
    bool poisoned;
    float poisonedTimer;
    SpawnLocation location;
} Enemy;


//Not ideal solution if we would have way more paths
typedef struct {
    Vec2* topPath;
    Vec2* lakePath;
    Vec2* bottomPath;

    int topLength;
    int lakeLength;
    int bottomLength;
} Paths;

Enemy* createEnemy(SpawnLocation spawnLocation, float x, float y, float hp, float speed);
void moveEnemy(Enemy* enemy, const Vec2* path, float deltaTime, int* hp, int* numAliveEnemies);
void renderEnemy(Enemy* enemy, SDL_Renderer* renderer, SDL_Texture* texture);
void setPaths(Paths* paths);
void freeEnemy(Enemy* enemy);
void freePaths(Paths* paths);

#pragma once
#include <SDL_render.h>

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
    Vec2 coords;
    int pathIndex;
    Direction direction;
    float hp;
    float speed;
    int active;
    SpawnLocation location;
    SDL_Rect rect;
} Enemy;


//Not ideal solution if we would have way too more paths
typedef struct {
    Vec2* topPath;
    Vec2* lakePath;
    Vec2* bottomPath;

    int topLength;
    int lakeLength;
    int bottomLength;
} Paths;

Enemy* createEnemy(SpawnLocation spawnLocation, float x, float y, const float hp, const float speed);
void moveEnemy(Enemy* enemy, const Vec2* path, float deltaTime);
void renderEnemy(Enemy* enemy, SDL_Renderer* renderer, const Paths* paths, const float deltaTime, SDL_Texture* texture);
void setPaths(Paths* paths);
void freeEnemy(Enemy* enemy);
void freePaths(const Paths* paths);

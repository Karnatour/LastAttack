#pragma once

typedef struct{
    int x,y;
}Point;

typedef struct{
    float x,y;
}Vec2;

typedef enum {
  DIRECTION_UP,
  DIRECTION_DOWN,
  DIRECTION_LEFT,
  DIRECTION_RIGHT
} Direction;

typedef struct{
    Point coords;
    int pathIndex;
    float hp;
    float speed;
    Direction direction;
    int active;
    Point* path;
}Enemy;

typedef enum{
    LOCATION_TOP,
    LOCATION_CAVE,
    LOCATION_SHIP,
}SpawnLocation;

Enemy* createEnemy();
void moveEnemy(Enemy*enemy,Point* path,double deltaTime);
#pragma once

#include <SDL_render.h>
#include <stdbool.h>

#include "Utils.h"
#include "Enemy.h"
#include "Level.h"
#include "Wave.h"

typedef enum {
    FIRE,
    POISON,
    ICE,
    NOT_SPAWNED
} TowerType;

typedef struct {
    SDL_Texture *fireTex;
    SDL_Texture *iceTex;
    SDL_Texture *poisonTex;
    SDL_Rect fireRect;
    SDL_Rect iceRect;
    SDL_Rect poisonRect;
} TowerBuyMenu;

typedef struct {
    SDL_Texture *damageTex;
    SDL_Texture *fireRateTex;
    SDL_Texture *rangeTex;
    int damageTier;
    int fireRateTier;
    int rangeTier;
    SDL_Rect damageRect;
    SDL_Rect fireRateRect;
    SDL_Rect rangeRect;
} TowerUpgradeMenu;

typedef struct {
    Vec2 coords;
    SDL_Rect rect;
    TowerType type;
    SDL_Texture *texture;
    TowerBuyMenu buyMenu;
    TowerUpgradeMenu upgradeMenu;
    bool occupied;
    Vec2 projectile;
    Vec2 projectileDirection;

    int enemyQueue[128];
    int enemyQueueIndex;
    int enemyQueueClearedIndex;
    int currentEnemyID;

    float damage;
    float fireRate;
    float range;

    int bonusMovementReduction; // ICE % value 0-100
    int bonusDamage; // POISON

    bool clicked;
    bool hovered;
} Tower;

void initTowerBuyMenu(SDL_Renderer *renderer, TowerBuyMenu *menu);
void initTowerUpgradeMenu(SDL_Renderer *renderer, TowerUpgradeMenu* menu);
void initTowerArray(SDL_Renderer *renderer, Tower *towers);

void setTowerBuyMenuPos(TowerBuyMenu *menu, int x, int y);
void setTowerUpgradeMenuPos(TowerUpgradeMenu *menu,int x, int y);

void handleTowerProjectiles(Tower* towers, Wave* wave, float deltaTime, SDL_Renderer* renderer, Level * level);
bool isEnemyInRange(Vec2 turretPos,Vec2 enemyPos, float range);
bool isEnemyHit(Vec2 projectilePos, const SDL_Rect* enemyRect);
Vec2 calculateDirectionVector(Vec2 turretPos, Vec2 enemyPos);
void moveProjectile(Vec2* projectilePos, Vec2 directionPos, float speed, float deltaTime);
void addEnemyToQueue(Tower* tower,int enemyID);
int getNextEnemyIDFromQueue(Tower* tower, Wave* wave);
Enemy* getEnemyByID(Wave* wave, int enemyID);
void cleanupEnemyQueue(Tower* tower, Wave* wave);
void resetProjectilePos(Tower* tower);

void renderProjectile(SDL_Renderer* renderer, Vec2 projectilePos, TowerType type);
void renderTower(SDL_Renderer *renderer, Tower *tower);
void renderTowerUpgradeMenu(SDL_Renderer *renderer, TowerUpgradeMenu *menu);
void renderTowerBuyMenu(SDL_Renderer *renderer, TowerBuyMenu *menu);
void renderTowerRange(SDL_Renderer* renderer, const Tower* tower);

void handleTowerClick(SDL_Renderer *renderer, TowerBuyMenu *towerBuyMenu, Tower *tower, SDL_Point point);
void handleTowerBuyMenuClick(SDL_Renderer *renderer, Tower *tower, SDL_Point point, int* coins);
void handleTowerUpgradeMenuClick(Tower *tower, SDL_Point point, int* coins);

void handleTowerHover(SDL_Point point, Tower* tower);

void setTowerValuesByType(SDL_Renderer *renderer, Tower *tower, TowerType towerType);

void destroyTowerBuyMenuTex(TowerBuyMenu *menu);
void destroyTowerUpgradeMenu(TowerUpgradeMenu *menu);
void destroyTowersTex(Tower *towers);
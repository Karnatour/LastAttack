#pragma once

#include <SDL_render.h>
#include "Utils.h"
#include "Enemy.h"

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
    SDL_Texture *numberOfTargetsTex;
    int damageTier;
    int fireRateTier;
    int numberOfTargetsTier;
    SDL_Rect damageRect;
    SDL_Rect fireRateRect;
    SDL_Rect numberOfTargetsRect;
} TowerUpgradeMenu;

typedef struct {
    Vec2 coords;
    SDL_Rect rect;
    TowerType type;
    SDL_Texture *texture;
    TowerBuyMenu buyMenu;
    TowerUpgradeMenu upgradeMenu;
    bool occupied;

    Vec2 projectilesCoords[5];
    Enemy targets[5];

    float damage;
    float fireRate;
    int numberOfTargets;
    float range;

    int bonusMovementReduction; // ICE % value 0-100
    int bonusDamage; // POISON

    bool clicked;
} Tower;

void initTowerBuyMenu(SDL_Renderer *renderer, TowerBuyMenu *menu);
void initTowerUpgradeMenu(SDL_Renderer *renderer, TowerUpgradeMenu* menu);
void initTowerArray(SDL_Renderer *renderer, Tower *towers);

void setTowerBuyMenuPos(TowerBuyMenu *menu, int x, int y);
void setTowerUpgradeMenuPos(TowerUpgradeMenu *menu,int x, int y);

bool isEnemyInRange(Vec2 turretPos,Vec2 enemyPos, float range);
Vec2 calculateDirectionVector(Vec2 turretPos, Vec2 enemyPos);
Vec2 moveProjectile(Vec2 projectilePos, Vec2 directionPos, float speed, float deltaTime);

void renderTower(SDL_Renderer *renderer, Tower *tower);
void renderTowerUpgradeMenu(SDL_Renderer *renderer, TowerUpgradeMenu *menu);
void renderTowerBuyMenu(SDL_Renderer *renderer, TowerBuyMenu *menu);

void handleTowerClick(SDL_Renderer *renderer, TowerBuyMenu *towerBuyMenu, Tower *tower, SDL_Point point);
void handleTowerBuyMenuClick(SDL_Renderer *renderer, Tower *tower, SDL_Point point);
void handleTowerUpgradeMenuClick(SDL_Renderer *renderer,Tower *tower,SDL_Point point);

void setTowerValuesByType(SDL_Renderer *renderer, Tower *tower, TowerType towerType);

void destroyTowerBuyMenuTex(TowerBuyMenu *menu);
void destroyTowerUpgradeMenu(TowerUpgradeMenu *menu);
void destroyTowersTex(Tower *towers);
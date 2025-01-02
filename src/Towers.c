#include "Towers.h"

#include <SDL2_gfxPrimitives.h>

#include "Config.h"
#include "Level.h"
#include "Logger.h"
#include "Texture.h"
#include "Wave.h"

void initTowerArray(SDL_Renderer* renderer, Tower* towers) {
    for (int i = 0; i < 5; ++i) {
        towers[i].coords = TOWER_LOCATIONS[i];
        SDL_Rect rect;
        rect.x = (int)towers[i].coords.x;
        rect.y = (int)towers[i].coords.y;
        rect.w = 128;
        rect.h = 128;

        initTowerBuyMenu(renderer, &towers[i].buyMenu);
        setTowerBuyMenuPos(&towers[i].buyMenu, rect.x, rect.y);

        initTowerUpgradeMenu(renderer, &towers[i].upgradeMenu);
        setTowerUpgradeMenuPos(&towers[i].upgradeMenu, rect.x, rect.y);

        towers[i].rect = rect;
        towers[i].type = NOT_SPAWNED;
        towers[i].texture = NULL;
        towers[i].occupied = false;

        towers[i].range = 300.0f;
        towers[i].damage = 0.0f;
        towers[i].fireRate = 0.0f;
        towers[i].bonusDamage = 0;
        towers[i].bonusMovementReduction = 0;
        towers[i].clicked = false;

        towers[i].enemyQueueIndex = 0;
        towers[i].enemyQueueClearedIndex = 0;

        towers[i].projectile.x = (float)towers[i].rect.x + (float)towers[i].rect.w / 2;
        towers[i].projectile.y = (float)towers[i].rect.y + (float)towers[i].rect.h / 2;

        towers[i].projectileDirection.x = 0;
        towers[i].projectileDirection.y = 0;

        towers[i].currentEnemyID = -1;

        towers[i].hovered = false;
    }
    LOG_DEBUG("Towers initialized\n");
}

void initTowerBuyMenu(SDL_Renderer* renderer, TowerBuyMenu* menu) {
    menu->fireTex = createAndLoadTexture(renderer, "../assets/towers/fire_tower.png");
    menu->iceTex = createAndLoadTexture(renderer, "../assets/towers/ice_tower.png");
    menu->poisonTex = createAndLoadTexture(renderer, "../assets/towers/poison_tower.png");
}


void initTowerUpgradeMenu(SDL_Renderer* renderer, TowerUpgradeMenu* menu) {
    menu->damageTex = createAndLoadTexture(renderer, "../assets/towers/sword.png");
    menu->fireRateTex = createAndLoadTexture(renderer, "../assets/towers/fire_rate.png");
    menu->rangeTex = createAndLoadTexture(renderer, "../assets/towers/range.png");
    menu->damageTier = 1;
    menu->fireRateTier = 1;
    menu->rangeTier = 1;
}

void setTowerBuyMenuPos(TowerBuyMenu* menu, int x, int y) {
    int offset = 32;
    menu->fireRect.x = x + offset;
    menu->fireRect.y = y - 128;
    menu->fireRect.w = 96;
    menu->fireRect.h = 96;

    menu->iceRect.x = x - 128 + offset;
    menu->iceRect.y = y - 96;
    menu->iceRect.w = 96;
    menu->iceRect.h = 96;

    menu->poisonRect.x = x + 128 + offset;
    menu->poisonRect.y = y - 96;
    menu->poisonRect.w = 96;
    menu->poisonRect.h = 96;
}

void setTowerUpgradeMenuPos(TowerUpgradeMenu* menu, int x, int y) {
    int offset = 32;
    menu->damageRect.x = x + offset;
    menu->damageRect.y = y - 128;
    menu->damageRect.w = 96;
    menu->damageRect.h = 96;

    menu->fireRateRect.x = x - 128 + offset;
    menu->fireRateRect.y = y - 96;
    menu->fireRateRect.w = 96;
    menu->fireRateRect.h = 96;

    menu->rangeRect.x = x + 128 + offset;
    menu->rangeRect.y = y - 96;
    menu->rangeRect.w = 96;
    menu->rangeRect.h = 96;
}

void handleTowerProjectiles(Tower* tower, Wave* wave, const float deltaTime, SDL_Renderer* renderer, Level* level) {
    // Add enemies from wave to queue if they are in range
    for (int enemyIndex = 0; enemyIndex < wave->numEnemies; ++enemyIndex) {
        Enemy* enemy = wave->enemies[enemyIndex];

        if (isEnemyInRange(tower->coords, enemy->coords, tower->range)) {
            bool alreadyInQueue = false;
            for (int queueIndex = tower->enemyQueueClearedIndex; queueIndex < tower->enemyQueueIndex; ++queueIndex) {
                if (enemy->id == tower->enemyQueue[queueIndex]) {
                    alreadyInQueue = true;
                    break;
                }
            }
            if (!alreadyInQueue) {
                addEnemyToQueue(tower, enemy->id);
            }
        }
    }

    // Remove enemies that are out of range or dead
    cleanupEnemyQueue(tower, wave);

    // Get next target from queue if tower doesnt have any
    if (tower->currentEnemyID == -1) {
        tower->currentEnemyID = getNextEnemyIDFromQueue(tower, wave);
    }

    // Get current enemy
    Enemy* targetEnemy = getEnemyByID(wave, tower->currentEnemyID);

    if (targetEnemy != NULL) {
        tower->projectileDirection = calculateDirectionVector(tower->coords, targetEnemy->coords);
        moveProjectile(&tower->projectile, tower->projectileDirection, tower->fireRate, deltaTime);

        // Calculate the distance from the tower to the projectile
        float distance = sqrtf(
            powf(tower->projectile.x - (float)((float)tower->rect.x + (float)tower->rect.w / 2), 2) + powf(
                tower->projectile.y - (float)((float)tower->rect.y + (float)tower->rect.h / 2), 2));

        if (distance > tower->range) {
            // Reset the projectile if it is out of range
            LOG_DEBUG("%f %f\n", distance, tower->range);
            resetProjectilePos(tower);
            tower->currentEnemyID = -1;
        }
        else if (isEnemyHit(tower->projectile, &targetEnemy->rect)) {
            resetProjectilePos(tower);
            targetEnemy->hp -= tower->damage;
            if (targetEnemy->hp <= 0) {
                // Enemy is dead
                if (wave->numAliveEnemies != 0) {
                    --wave->numAliveEnemies;
                    level->coins += 20;
                }
                targetEnemy->active = false;
                tower->currentEnemyID = getNextEnemyIDFromQueue(tower, wave);
            }
        }

        renderProjectile(renderer, tower->projectile, tower->type);
    }
    else {
        tower->currentEnemyID = -1;
    }
}


void renderTowerBuyMenu(SDL_Renderer* renderer, TowerBuyMenu* menu) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    SDL_RenderFillRect(renderer, &menu->fireRect);
    SDL_RenderFillRect(renderer, &menu->iceRect);
    SDL_RenderFillRect(renderer, &menu->poisonRect);
    SDL_RenderCopy(renderer, menu->fireTex, NULL, &menu->fireRect);
    SDL_RenderCopy(renderer, menu->iceTex, NULL, &menu->iceRect);
    SDL_RenderCopy(renderer, menu->poisonTex, NULL, &menu->poisonRect);
}

void renderTowerUpgradeMenu(SDL_Renderer* renderer, TowerUpgradeMenu* menu) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    SDL_RenderFillRect(renderer, &menu->damageRect);
    SDL_RenderFillRect(renderer, &menu->fireRateRect);
    SDL_RenderFillRect(renderer, &menu->rangeRect);
    SDL_RenderCopy(renderer, menu->damageTex, NULL, &menu->damageRect);
    SDL_RenderCopy(renderer, menu->fireRateTex, NULL, &menu->fireRateRect);
    SDL_RenderCopy(renderer, menu->rangeTex, NULL, &menu->rangeRect);
}

void handleTowerClick(SDL_Renderer* renderer, TowerBuyMenu* towerBuyMenu, Tower* tower, SDL_Point point) {
    if (SDL_PointInRect(&point, &tower->rect)) {
        if (tower->clicked) {
            tower->clicked = false; // On second click hide the menu
        }
        else {
            tower->clicked = true;
        }
    }
}

void handleTowerBuyMenuClick(SDL_Renderer* renderer, Tower* tower, SDL_Point point, int* coins) {
    if (SDL_PointInRect(&point, &tower->buyMenu.fireRect)) {
        if (*coins >= 5) {
            setTowerValuesByType(renderer, tower, FIRE);
            *coins = *coins - 5;
        }
    }
    else if (SDL_PointInRect(&point, &tower->buyMenu.iceRect)) {
        if (*coins >= 5) {
            setTowerValuesByType(renderer, tower, ICE);
            *coins = *coins - 5;
        }
    }
    else if (SDL_PointInRect(&point, &tower->buyMenu.poisonRect)) {
        if (*coins >= 4) {
            setTowerValuesByType(renderer, tower, POISON);
            *coins = *coins - 5;
        }
    }
}

void handleTowerUpgradeMenuClick(Tower* tower, SDL_Point point, int* coins) {
    if (SDL_PointInRect(&point, &tower->upgradeMenu.damageRect)) {
        if (tower->upgradeMenu.damageTier != 5 && *coins >= 10) {
            *coins = *coins - 10;
            ++tower->upgradeMenu.damageTier;
            tower->damage += 10;
        }
    }
    else if (SDL_PointInRect(&point, &tower->upgradeMenu.fireRateRect)) {
        if (tower->upgradeMenu.fireRateTier != 5 && *coins >= 10) {
            *coins = *coins - 10;
            ++tower->upgradeMenu.fireRateTier;
            tower->fireRate += 500;
        }
    }
    else if (SDL_PointInRect(&point, &tower->upgradeMenu.rangeRect)) {
        if (tower->upgradeMenu.rangeTier != 5 && *coins >= 10) {
            *coins = *coins - 10;
            ++tower->upgradeMenu.rangeTier;
            tower->range += 20;
        }
    }
}

void handleTowerHover(const SDL_Point point, Tower* tower) {
    if (SDL_PointInRect(&point, &tower->rect)) {
        tower->hovered = true;
    }
    else {
        tower->hovered = false;
    }
}

void renderTowerRange(SDL_Renderer* renderer, const Tower* tower) {
    const int towerCenterX = tower->rect.x + (tower->rect.w / 2);
    const int towerCenterY = tower->rect.y + (tower->rect.h / 2);

    // Background circle
    filledCircleRGBA(renderer, (Sint16)towerCenterX, (Sint16)towerCenterY, (Sint16)tower->range, 0, 0, 50, 48);

    // Range circle
    circleRGBA(renderer, (Sint16)towerCenterX, (Sint16)towerCenterY, (Sint16)tower->range, 0, 0, 0, 128);
}

void renderTower(SDL_Renderer* renderer, Tower* tower) {
    SDL_RenderCopy(renderer, tower->texture, NULL, &tower->rect);
}

void setTowerValuesByType(SDL_Renderer* renderer, Tower* tower, TowerType towerType) {
    switch (towerType) {
        case FIRE:
            tower->type = FIRE;
            tower->texture = createAndLoadTexture(renderer, "../assets/towers/fire_tower.png");
            tower->damage = 25;
            tower->fireRate = 200.5f;
            tower->occupied = true;
            break;
        case ICE:
            tower->type = ICE;
            tower->texture = createAndLoadTexture(renderer, "../assets/towers/ice_tower.png");
            tower->damage = 15;
            tower->fireRate = 200.0f;
            tower->bonusMovementReduction = 20;
            tower->occupied = true;
            break;
        case POISON:
            tower->type = POISON;
            tower->texture = createAndLoadTexture(renderer, "../assets/towers/poison_tower.png");
            tower->damage = 15;
            tower->fireRate = 200.0f;
            tower->bonusDamage = 10;
            tower->occupied = true;
            break;
        case NOT_SPAWNED:
            LOG_WARNING("setTowerValuesByType called for NOT_SPAWNED tower\n");
            break;
    }
}

void destroyTowerBuyMenuTex(TowerBuyMenu* menu) {
    if (menu) {
        destroyTexture(menu->fireTex);
        destroyTexture(menu->iceTex);
        destroyTexture(menu->poisonTex);
        LOG_DEBUG("Destryoed TowerBuyMenu textures\n");
    }
}

void destroyTowersTex(Tower* towers) {
    for (int i = 0; i < 5; ++i) {
        if (towers[i].texture) {
            destroyTexture(towers[i].texture);
            LOG_DEBUG("Destroyed Tower texture with ID %d", i);
        }
    }
}

bool isEnemyInRange(const Vec2 turretPos, const Vec2 enemyPos, const float range) {
    Vec2 directionVec;
    directionVec.x = enemyPos.x - turretPos.x;
    directionVec.y = enemyPos.y - turretPos.y;
    const float distance = sqrtf(directionVec.x * directionVec.x + directionVec.y * directionVec.y);
    return distance <= range;
}

bool isEnemyHit(const Vec2 projectilePos, const SDL_Rect* enemyRect) {
    //22,28 is real size of the goblin since texture is 32x32 dont want to check hit with "air"
    float enemyCenterX = (float)enemyRect->x + (float)(enemyRect->w - 22) / 2;
    float enemyCenterY = (float)enemyRect->y + (float)(enemyRect->h - 28) / 2;

    SDL_Rect hitbox = {
        (int)enemyCenterX,
        (int)enemyCenterY,
        22,
        28
    };

    SDL_Point point;
    point.x = (int)projectilePos.x;
    point.y = (int)projectilePos.y;

    if (SDL_PointInRect(&point, &hitbox)) {
        return true;
    }

    return false;
}

Vec2 calculateDirectionVector(Vec2 turretPos, Vec2 enemyPos) {
    Vec2 direction;
    Vec2 directionVec;
    directionVec.x = enemyPos.x - turretPos.x;
    directionVec.y = enemyPos.y - turretPos.y;
    const float distance = sqrtf(directionVec.x * directionVec.x + directionVec.y * directionVec.y);

    if (distance == 0) {
        direction.x = 0;
        direction.y = 0;
    }
    else {
        direction.x = directionVec.x / distance;
        direction.y = directionVec.y / distance;
    }
    return direction;
}

void moveProjectile(Vec2* projectilePos, const Vec2 directionPos, const float speed, const float deltaTime) {
    projectilePos->x += directionPos.x * speed * deltaTime;
    projectilePos->y += directionPos.y * speed * deltaTime;
}

void addEnemyToQueue(Tower* tower, const int enemyID) {
    if (tower->enemyQueueIndex == 255) {
        LOG_ERROR("Enemy queue is full\n");
    }
    tower->enemyQueue[tower->enemyQueueIndex] = enemyID;
    tower->enemyQueueIndex++;
}

Enemy* getEnemyByID(Wave* wave, int enemyID) {
    for (int i = 0; i < wave->numEnemies; ++i) {
        if (wave->enemies[i]->id == enemyID) {
            return wave->enemies[i];
        }
    }
    return NULL;
}

int getNextEnemyIDFromQueue(Tower* tower, Wave* wave) {
    while (tower->enemyQueueClearedIndex < tower->enemyQueueIndex) {
        int enemyID = tower->enemyQueue[tower->enemyQueueClearedIndex];
        ++tower->enemyQueueClearedIndex;

        Enemy* enemy = getEnemyByID(wave, enemyID);

        if (enemy != NULL && enemy->hp > 0 && isEnemyInRange(tower->coords, enemy->coords, tower->range)) {
            return enemyID;
        }
    }

    // No valid enemies in the queue
    return -1;
}


void cleanupEnemyQueue(Tower* tower, Wave* wave) {
    int newIndex = 0;
    for (int i = tower->enemyQueueClearedIndex; i < tower->enemyQueueIndex; ++i) {
        int enemyID = tower->enemyQueue[i];
        Enemy* enemy = getEnemyByID(wave, enemyID);

        // Keep only enemies that are in range and alive
        if (enemy != NULL && enemy->hp > 0 && isEnemyInRange(tower->coords, enemy->coords, tower->range)) {
            tower->enemyQueue[newIndex] = enemyID;
            ++newIndex;
        }
    }

    tower->enemyQueueClearedIndex = 0;
    tower->enemyQueueIndex = newIndex;
}

void resetProjectilePos(Tower* tower) {
    tower->projectile.x = (float)tower->rect.x + (float)tower->rect.w / 2;
    tower->projectile.y = (float)tower->rect.y + (float)tower->rect.h / 2;
}

void renderProjectile(SDL_Renderer* renderer, Vec2 projectilePos, TowerType type) {
    const SDL_Rect projectileRect = {(int)projectilePos.x, (int)projectilePos.y, 10, 10};
    const SDL_Rect borderRect = {(int)projectilePos.x - 1, (int)projectilePos.y - 1, 12, 12};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &borderRect);

    switch (type) {
        case FIRE:
            SDL_SetRenderDrawColor(renderer, 214, 0, 0, 255);
            break;
        case POISON:
            SDL_SetRenderDrawColor(renderer, 147, 229, 30, 255);
            break;
        case ICE:
            SDL_SetRenderDrawColor(renderer, 185, 232, 234, 255);
            break;
    }
    SDL_RenderFillRect(renderer, &projectileRect);
}

void destroyTowerUpgradeMenu(TowerUpgradeMenu* menu) {
    if (menu) {
        destroyTexture(menu->damageTex);
        destroyTexture(menu->fireRateTex);
        destroyTexture(menu->rangeTex);
        LOG_DEBUG("Destryoed TowerBuyMenu textures\n");
    }
}

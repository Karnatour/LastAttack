#include "Towers.h"
#include "Config.h"
#include "Logger.h"
#include "Texture.h"

void initTowerArray(SDL_Renderer *renderer, Tower *towers) {
    for (int i = 0; i < 5; ++i) {
        towers[i].coords = TOWER_LOCATIONS[i];
        SDL_Rect rect;
        rect.x = (int) towers[i].coords.x;
        rect.y = (int) towers[i].coords.y;
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

        towers[i].range = 500.0f;
        towers[i].damage = 0.0f;
        towers[i].fireRate = 0.0f;
        towers[i].numberOfTargets = 1;
        towers[i].bonusDamage = 0;
        towers[i].bonusMovementReduction = 0;
        towers[i].clicked = false;
    }
    LOG_DEBUG("Towers initialized\n");
}

void initTowerBuyMenu(SDL_Renderer *renderer, TowerBuyMenu *menu) {
    menu->fireTex = createAndLoadTexture(renderer, "../assets/towers/fire_tower.png");
    menu->iceTex = createAndLoadTexture(renderer, "../assets/towers/fire_tower.png");
    menu->poisonTex = createAndLoadTexture(renderer, "../assets/towers/fire_tower.png");
}


void initTowerUpgradeMenu(SDL_Renderer *renderer, TowerUpgradeMenu *menu) {
    menu->damageTex = createAndLoadTexture(renderer, "../assets/towers/star.png");
    menu->fireRateTex = createAndLoadTexture(renderer, "../assets/towers/star.png");
    menu->numberOfTargetsTex = createAndLoadTexture(renderer, "../assets/towers/star.png");
    menu->damageTier = 1;
    menu->fireRateTier = 1;
    menu->numberOfTargetsTier = 1;
}

void setTowerBuyMenuPos(TowerBuyMenu *menu, int x, int y) {
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

void setTowerUpgradeMenuPos(TowerUpgradeMenu *menu, int x, int y) {
    int offset = 32;
    menu->damageRect.x = x + offset;
    menu->damageRect.y = y - 128;
    menu->damageRect.w = 96;
    menu->damageRect.h = 96;

    menu->fireRateRect.x = x - 128 + offset;
    menu->fireRateRect.y = y - 96;
    menu->fireRateRect.w = 96;
    menu->fireRateRect.h = 96;

    menu->numberOfTargetsRect.x = x + 128 + offset;
    menu->numberOfTargetsRect.y = y - 96;
    menu->numberOfTargetsRect.w = 96;
    menu->numberOfTargetsRect.h = 96;
}

void renderTowerBuyMenu(SDL_Renderer *renderer, TowerBuyMenu *menu) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    SDL_RenderFillRect(renderer, &menu->fireRect);
    SDL_RenderFillRect(renderer, &menu->iceRect);
    SDL_RenderFillRect(renderer, &menu->poisonRect);
    SDL_RenderCopy(renderer, menu->fireTex, NULL, &menu->fireRect);
    SDL_RenderCopy(renderer, menu->iceTex, NULL, &menu->iceRect);
    SDL_RenderCopy(renderer, menu->poisonTex, NULL, &menu->poisonRect);
}

void renderTowerUpgradeMenu(SDL_Renderer *renderer, TowerUpgradeMenu *menu) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    SDL_RenderFillRect(renderer, &menu->damageRect);
    SDL_RenderFillRect(renderer, &menu->fireRateRect);
    SDL_RenderFillRect(renderer, &menu->numberOfTargetsRect);
    SDL_RenderCopy(renderer, menu->damageTex, NULL, &menu->damageRect);
    SDL_RenderCopy(renderer, menu->fireRateTex, NULL, &menu->fireRateRect);
    SDL_RenderCopy(renderer, menu->numberOfTargetsTex, NULL, &menu->numberOfTargetsRect);
}

void handleTowerClick(SDL_Renderer *renderer, TowerBuyMenu *towerBuyMenu, Tower *tower, SDL_Point point) {
    if (SDL_PointInRect(&point, &tower->rect)) {
        if (tower->clicked) {
            tower->clicked = false; // On second click hide the menu
        } else {
            tower->clicked = true;
        }
    } else {
        tower->clicked = false;
    }
}

void handleTowerBuyMenuClick(SDL_Renderer *renderer, Tower *tower, SDL_Point point) {
    if (SDL_PointInRect(&point, &tower->buyMenu.fireRect)) {
        setTowerValuesByType(renderer, tower, FIRE);
    } else if (SDL_PointInRect(&point, &tower->buyMenu.iceRect)) {
        setTowerValuesByType(renderer, tower, ICE);
    } else if (SDL_PointInRect(&point, &tower->buyMenu.poisonRect)) {
        setTowerValuesByType(renderer, tower, POISON);
    }
}

void handleTowerUpgradeMenuClick(SDL_Renderer *renderer, Tower *tower, SDL_Point point) {
    if (SDL_PointInRect(&point, &tower->upgradeMenu.damageRect)) {
        if (tower->upgradeMenu.damageTier != 5) {
            ++tower->upgradeMenu.damageTier;
        }
    } else if (SDL_PointInRect(&point, &tower->upgradeMenu.fireRateRect)) {
        if (tower->upgradeMenu.fireRateTier != 5) {
            ++tower->upgradeMenu.fireRateTier;
        }

    } else if (SDL_PointInRect(&point, &tower->upgradeMenu.numberOfTargetsRect)) {
        if (tower->upgradeMenu.numberOfTargetsTier != 5) {
            ++tower->upgradeMenu.numberOfTargetsTier;
        }
    }
}

void renderTower(SDL_Renderer *renderer, Tower *tower) {
    SDL_RenderCopy(renderer, tower->texture, NULL, &tower->rect);
}

void setTowerValuesByType(SDL_Renderer *renderer, Tower *tower, TowerType towerType) {
    switch (towerType) {
        case FIRE:
            tower->type = FIRE;
            tower->texture = createAndLoadTexture(renderer, "../assets/towers/fire_tower.png");
            tower->damage = 100;
            tower->fireRate = 0.5f;
            tower->occupied = true;
            break;
        case ICE:
            tower->type = ICE;
            tower->texture = createAndLoadTexture(renderer, "../assets/towers/fire_tower.png");
            tower->damage = 50;
            tower->fireRate = 1.0f;
            tower->bonusMovementReduction = 20;
            tower->occupied = true;
            break;
        case POISON:
            tower->type = POISON;
            tower->texture = createAndLoadTexture(renderer, "../assets/towers/fire_tower.png");
            tower->damage = 50;
            tower->fireRate = 1.0f;
            tower->bonusDamage = 10;
            tower->occupied = true;
            break;
        case NOT_SPAWNED:
            LOG_WARNING("setTowerValuesByType called for NOT_SPAWNED tower\n");
            break;
    }
}

void destroyTowerBuyMenuTex(TowerBuyMenu *menu) {
    if (menu) {
        destroyTexture(menu->fireTex);
        destroyTexture(menu->iceTex);
        destroyTexture(menu->poisonTex);
        LOG_DEBUG("Destryoed TowerBuyMenu textures\n");
    }
}

void destroyTowersTex(Tower *towers) {
    for (int i = 0; i < 5; ++i) {
        if (towers[i].texture) {
            destroyTexture(towers[i].texture);
            LOG_DEBUG("Destroyed Tower texture with ID %d", i);
        }
    }
}

bool isEnemyInRange(Vec2 turretPos, Vec2 enemyPos, float range) {
    Vec2 directionVec;
    directionVec.x = enemyPos.x - turretPos.x;
    directionVec.y = enemyPos.y - turretPos.y;
    float distance = sqrtf(directionVec.x * directionVec.x + directionVec.y * directionVec.y);
    return distance <= range;
}

Vec2 calculateDirectionVector(Vec2 turretPos, Vec2 enemyPos) {
    Vec2 direction;
    Vec2 directionVec;
    directionVec.x = enemyPos.x - turretPos.x;
    directionVec.y = enemyPos.y - turretPos.y;
    float distance = sqrtf(directionVec.x * directionVec.x + directionVec.y * directionVec.y);

    if (distance == 0) { // Avoid division by zero
        direction.x = 0;
        direction.y = 0;
    } else {
        direction.x = directionVec.x / distance;
        direction.y = directionVec.y / distance;
    }
    return direction;
}

Vec2 moveProjectile(Vec2 projectilePos, Vec2 directionPos, float speed, float deltaTime) {
    projectilePos.x += directionPos.x * speed * deltaTime;
    projectilePos.y += directionPos.y * speed * deltaTime;
    return projectilePos;
}

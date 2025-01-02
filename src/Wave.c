#include "Wave.h"

void renderWave(SDL_Renderer* renderer, const Wave* wave) {
    for (int i = 0; i < wave->numEnemies; ++i) {
        if (wave->enemies[i]->active) {
            renderEnemy(wave->enemies[i], renderer, wave->texture);
        }
    }
}

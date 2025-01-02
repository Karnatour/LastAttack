#pragma once
#include <SDL_render.h>

#include "Wave.h"

struct Game;

typedef enum {
    VICTORY,
    DEFEAT
} EndingType;

typedef struct {
    int hp;
    int coins;
    SDL_Rect heartRect;
    SDL_Texture* heartTexture;
    SDL_Rect heartValueRect;
    SDL_Texture* heartValueTexture;

    SDL_Rect coinRect;
    SDL_Texture* coinTexture;
    SDL_Rect coinValueRect;
    SDL_Texture* coinValueTexture;

    int currentWave;
    Wave waves[3];
} Level;

void initLevel(SDL_Renderer* renderer, Level* level);
void renderUI(SDL_Renderer* renderer, const Level* level);
void updateUITextures(SDL_Texture* newHeartTexture, SDL_Texture* newCoinTexture, Level* level);
void destroyLevel(Level* level);
void endLevel(EndingType endingType, struct Game* game);
void prepareForNextLevel(struct Game* game);
void clearLevel(Level* level);

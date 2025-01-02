#pragma once
#include <SDL_render.h>

struct Game;

typedef struct {
    SDL_Rect mainMenuRect;
    SDL_Rect playRect;
    SDL_Rect quitRect;
    SDL_Texture* logoTexture;
    SDL_Texture* playTexture;
    SDL_Texture* quitTexture;
} MainMenu;


void initMainMenu(SDL_Renderer* renderer, MainMenu* menu);

void handleMainMenuClick(struct Game* game, SDL_Point point);

void destroyMainMenu(MainMenu* menu);

void renderMainMenu(struct Game *game);


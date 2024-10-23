#include <SDL.h>
#include "Game.h"
#include "Logger.h"

Game *allocateGame()
{
    Game *game = malloc(sizeof(Game));
    if (game)
    {
        LOG_INFO("Allocated memory for game struct")
    } else
    {
        LOG_ERROR("Error while allocating memory for game struct")
    }
    return game;
}

void initGame(Game *game)
{
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);
    LOG_INFO("Game initialized successfuly")
    game->isRunning = true;
}

void runGame(Game *game)
{
    game->isRunning = false;
}

void exitGame(Game *game)
{
    SDL_Quit();
}

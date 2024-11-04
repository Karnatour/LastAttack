#include "Game.h"

int SDL_main(int argc, char *argv[])
{
    Game* game = allocateGame();

    initGame(game);

    while (game->isRunning){
        runGame(game);
    }

    exitGame(game);
    return 0;
}
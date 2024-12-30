#include "Game.h"

#ifdef _MSC_VER
int SDL_main(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
    Game* game = allocateGame();

    initGame(game);

    while (game->isRunning){
        runGame(game);
    }

    exitGame(game);
    return 0;
}
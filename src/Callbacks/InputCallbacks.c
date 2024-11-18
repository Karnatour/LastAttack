#include "InputCallbacks.h"

#include "../Game.h"

void keyPressed(const SDL_Keysym key, Game* game) {
    switch (key.sym) {
        case SDLK_ESCAPE:
            game->isRunning = false;
            break;
    }
}

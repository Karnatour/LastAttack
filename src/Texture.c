#include "Texture.h"
#include <SDL_image.h>
#include "Logger.h"

SDL_Texture* createAndLoadTexture(SDL_Renderer* renderer, const char* path) {
    SDL_Texture* texture = IMG_LoadTexture(renderer,path);
    if (texture == NULL) {
        LOG_ERROR("Unable to load texture with path %s error: %s\n", path, IMG_GetError());
        return NULL;
    }
    return texture;
}

void renderTexture(SDL_Renderer* renderer,SDL_Texture* texture) {
    SDL_RenderCopy(renderer,texture,NULL,NULL);
}

void destroyTexture(SDL_Texture* texture) {
    SDL_DestroyTexture(texture);
}

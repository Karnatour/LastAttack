#include "Texture.h"
#include <SDL_image.h>
#include "Logger.h"

Texture* createAndLoadTexture(SDL_Renderer* renderer, const char* path) {
    SDL_Surface* tempSurface = IMG_Load(path);
    if (tempSurface == nullptr) {
        LOG_ERROR("Unable to load image with path %s error: %s", path, IMG_GetError());
        return nullptr;
    }

    Texture* texture = malloc(sizeof texture);
    texture->texture = nullptr;

    texture->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    if (texture->texture == nullptr) {
        LOG_ERROR("Unable to create texture with path %s error: %s", path, SDL_GetError());
    }
    SDL_FreeSurface(tempSurface);
    return texture;
}

void renderTexture(SDL_Renderer* renderer, const Texture* texture) {
    SDL_RenderCopy(renderer,texture->texture,nullptr,nullptr);
}

void destroyTexture(Texture* texture) {
    SDL_DestroyTexture(texture->texture);
    free(texture);
}

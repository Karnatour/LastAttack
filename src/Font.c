#include "Font.h"

#include "Logger.h"

SDL_Texture* createMessageTexture(SDL_Renderer* renderer, const char* fontPath, const int fontSize, const char* text, int r, int g, int b, SDL_Rect* rect) {
    TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
    if (font == NULL) {
        LOG_ERROR("Unable to load font with path %s error: %s\n", fontPath, TTF_GetError());
        return NULL;
    }
    const SDL_Color fg = {r, g, b};
    SDL_Surface* surface = TTF_RenderText_Blended(font, text,fg);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect->w = surface->w;
    rect->h = surface->h;
    SDL_FreeSurface(surface);;
    TTF_CloseFont(font);
    return texture;
}

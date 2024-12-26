#pragma once
#include <SDL_render.h>
#include <stdbool.h>

#include "tmx.h"

typedef struct {
    unsigned int x, y;
    unsigned int dx,dy;
    unsigned int w, h;
    unsigned int tileID;
    unsigned int gid;
    unsigned int gridID;
    SDL_Texture* texture;
    //anim = Animation
    unsigned int animLength;
    unsigned int currentAnimIndex;
    bool animated;
} Tile;

typedef struct {
    Tile* tiles;
    tmx_map* tmxMap;
    unsigned int tileIndex;
} Map;

void initMapLoader(struct Game* game);
void* mapTexLoadFun(const char *path);

tmx_map* loadMap(const char* path);
void freeMap(Map* map);

void loadAndCacheTiles(Map* map, const tmx_layer* layerList);
void loadLayer(Map* map, const tmx_layer* layer);

void updateAnimatedTile(Map* map,Tile* tile);

void renderMap(Map* map, SDL_Renderer* renderer,float deltaTime);
void renderTile(Tile* tile, SDL_Renderer* renderer);

tmx_col_bytes convertColorToBytes(const int color);

int getIndex(int i, int j, unsigned int width);
void getRendererColor(SDL_Renderer *renderer, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a);
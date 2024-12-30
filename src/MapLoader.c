#include "MapLoader.h"
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include <stdbool.h>
#include "Game.h"
#include "Logger.h"

//I really dont like this idea but tmx library force me to do it
static SDL_Renderer *mapRenderer = NULL;

void initMapLoader(Game *game) {
    mapRenderer = game->renderer;
    tmx_img_load_func = mapTexLoadFun;
    tmx_img_free_func = (void (*)(void *)) SDL_DestroyTexture;
}

void *mapTexLoadFun(const char *path) {
    return IMG_LoadTexture(mapRenderer, path);
}

tmx_map *loadMap(const char *path) {
    tmx_map *map = NULL;
    map = tmx_load(path);
    if (!map) {
        LOG_ERROR("Cannot load map: %s\n", tmx_strerr());
    }

    return map;
}

void freeMap(Map *map) {
    if (map) {
        free(map->tiles);
        tmx_map_free(map->tmxMap);
        map = NULL;
        LOG_DEBUG("Destryoed map\n");
    } else {
        LOG_ERROR("Trying to free NULL map pointer\n");
    }
}

void renderMap(Map *map, SDL_Renderer *renderer, const float deltaTime) {
    static bool firstRender = true;
    static float animationTimer = 0.0f;
    const float frameDuration = 0.150f;

    const tmx_col_bytes colorBytes = convertColorToBytes((int) map->tmxMap->backgroundcolor);
    SDL_SetRenderDrawColor(renderer, colorBytes.r, colorBytes.g, colorBytes.b, colorBytes.a);

    if (firstRender) {
        map->tileIndex = 0;
        map->tiles = malloc(sizeof(Tile) * map->tmxMap->tilecount);
        loadAndCacheTiles(map, map->tmxMap->ly_head);
        firstRender = false;
    }

    for (int i = 0; i < map->tileIndex; ++i) {
        renderTile(&map->tiles[i], renderer);
    }

    animationTimer += deltaTime;
    if (animationTimer >= frameDuration) {
        for (int i = 0; i < map->tileIndex; ++i) {
            if (map->tiles[i].animated) {
                updateAnimatedTile(map, &map->tiles[i]);
            }
        }
        animationTimer -= frameDuration;
    }
}

void loadAndCacheTiles(Map *map, const tmx_layer *layerList) {
    while (layerList != NULL) {
        switch (layerList->type) {
            case L_GROUP:
                loadAndCacheTiles(map, layerList->content.group_head);
                break;
            case L_LAYER:
                loadLayer(map, layerList);
                break;
            default:
                break;
        }
        layerList = layerList->next;
    }
}

void loadLayer(Map *map, const tmx_layer *layer) {
    for (int i = 0; i < map->tmxMap->height; ++i) {
        for (int j = 0; j < map->tmxMap->width; ++j) {
            Tile *tile = &map->tiles[map->tileIndex];
            const unsigned int index = getIndex(i, j, map->tmxMap->width);
            tile->gid = layer->content.gids[index];
            tile->gridID = tile->gid & TMX_FLIP_BITS_REMOVAL;
            if (map->tmxMap->tiles[tile->gridID] != NULL) {
                tile->x = map->tmxMap->tiles[tile->gridID]->ul_x;
                tile->y = map->tmxMap->tiles[tile->gridID]->ul_y;
                tile->w = map->tmxMap->tiles[tile->gridID]->width;
                tile->h = map->tmxMap->tiles[tile->gridID]->height;
                tile->dx = j;
                tile->dy = i;
                if (map->tmxMap->tiles[tile->gridID]->animation) {
                    tile->animated = true;
                    tile->currentAnimIndex = 0;
                    tile->animLength = map->tmxMap->tiles[tile->gridID]->animation_len;
                    tile->tileID = map->tmxMap->tiles[tile->gridID]->animation[tile->currentAnimIndex].tile_id;
                    tile->texture = map->tmxMap->tiles[tile->gridID]->tileset->image->resource_image;
                } else {
                    tile->animated = false;
                    tile->animLength = 0;
                    tile->texture = map->tmxMap->tiles[tile->gridID]->tileset->image->resource_image;
                }

                ++map->tileIndex;
            }
        }
    }
}


void updateAnimatedTile(Map *map, Tile *tile) {
    tile->currentAnimIndex = (tile->currentAnimIndex + 1) % tile->animLength;

    const unsigned int tileID = map->tmxMap->tiles[tile->gridID]->animation[tile->currentAnimIndex].tile_id;

    tile->x = map->tmxMap->tiles[tile->gridID]->tileset->tiles[tileID].ul_x;
    tile->y = map->tmxMap->tiles[tile->gridID]->tileset->tiles[tileID].ul_y;
}

void renderTile(Tile *tile, SDL_Renderer *renderer) {
    SDL_Rect srcRect;
    srcRect.x = (int) tile->x;
    srcRect.y = (int) tile->y;
    srcRect.w = (int) tile->w;
    srcRect.h = (int) tile->h;

    SDL_Rect destRect;
    destRect.x = (int) (tile->dx * tile->w * 2);
    destRect.y = (int) (tile->dy * tile->h * 2);
    destRect.w = (int) tile->w * 2;
    destRect.h = (int) tile->h * 2;

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double angle = 0.0;

    if (tile->gid & TMX_FLIPPED_HORIZONTALLY) {
        flip = (SDL_RendererFlip) (flip | SDL_FLIP_HORIZONTAL);
    }
    if (tile->gid & TMX_FLIPPED_VERTICALLY) {
        flip = (SDL_RendererFlip) (flip | SDL_FLIP_VERTICAL);
    }

    if (tile->gid & TMX_FLIPPED_DIAGONALLY) {
        if (tile->gid & TMX_FLIPPED_VERTICALLY) {
            angle = 270;
        } else {
            angle = 90;
        }
        flip = SDL_FLIP_NONE;
    }
    SDL_RenderCopyEx(renderer, (SDL_Texture *) tile->texture, &srcRect, &destRect, angle, NULL, flip);
}


int getIndex(const int i, const int j, const unsigned int width) {
    return (i * (int) width) + j;
}

tmx_col_bytes convertColorToBytes(const int color) {
    const tmx_col_bytes byteColor = tmx_col_to_bytes(color);
    return byteColor;
}

void getRendererColor(SDL_Renderer *renderer, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a) {
    SDL_GetRenderDrawColor(renderer, r, g, b, a);
}
